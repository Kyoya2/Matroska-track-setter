This project is unfinished because I decided to write it in C++ https://github.com/Kyoya2/Matroska-track-setter.

Some research I did:

There are currently 2 ways for making a video player select a track be default:
1. Setting FD (FlagDefault) of the desired track to 1 and FD of all other tracks to 0.
2. Setting FF (FlagForced) of the desired track to 1 and FF of all other tracks to 0.

Considerations for selecting one of the two methods:
- When a FD element is not present within a track element, it's default value is 1. This means that if an
    MKV file has more than 2 tracks without an FD elementm we need to add one for each track (except for the
    desired track) and set it's value to 0.
- The Matroshka element specification specifies that when FF=1, it will override the selections of any other
    tracks with FD=1. When an FF element is not present, it's default value is 0.
- The Matroshka element specification specifies that FF applies to subtitles only. With that in mind,
    VLC Media Player will still select an audio track with FF=1 when there's another track with FD=1
    so sometimes the script WILL add a FF element to an audio track.
- When multiple subtitle tracks have FD=1 VLC Media Player will select the subtitle track that has both
	FD=1 and the largest track number.
- When multiple subtitle tracks have FD=1 VLC Media Player will select the audio track that has both FD=1
	and the smallest track number.


Preferred ways for making a desired track selected bu the player by default, sorted by priority:
1) If the desired track already has FF, set it to 1.
2) If all tracks except the desired track have a FD element, set them all to 0. If the desired track has an FD, set it to 1.
3) If the desired track has both 'Language' and 'LanguageIETF' elements, convert 'Language' to FF. That should
    leave more than 2 extra bytes so that the rest can be converted to a Void element.
4) If the desired track has either a 'Language' or 'LanguageIETF' set to english, overwrite it with FF
5) If another track has 'FF' and the current track can contain an extra 4 bytes without expanding the encoding of the
    size VINT, move it to the current track.
6) Try step 4 on the closest track and then step 6.
7) Try step 5 on the closest track and then step 6.
8) Take some bytes from the closest top-level Void element and add a FF element to the desired track (set it to 1).

When chosing any of the above options, remember to ALWAYS set FF of other tracks (if they exist) to 0.

If a track has both FD and FF elements and we need to convert one of them to the other. Convert the one to a
Void Element instead and operate on the existing other.

Some of the above options require 'adding' an element, in order to add an element to the file we need to make
space for it, here is a list of ways for acquiring free space, sorted by priority:
1) If a track has both FD and FF, FD can be used as free space.
2) If a track has both 'Language' and 'LanguageIETF' elements, 'Language' can be used as free space.
3) If a track has a Name element, it can be shortened by 3 bytes to create a new FF or FD, or the Name element 
    can be entirely erased for extra space.
4) Use a part of the closest Void element as free space. This will require shifting the whole Tracks element
    and adjusting a Seek element.
5) If any of the above conditions are satisfied for another element, we can shrink that element by 'moving' the
    free space that was created by the above options to the desired element. Note that it will require adjusting
    the size of both track elements that were participating in the exchange.
6) Last resort: expand the file, this will require shifting most of the files' data, this is a very expensive
    operation and should be avoided at all cost.

In some cases, the element that we remove in order to make space for and FF element is bigger than an FF element.
In that case we can use any combination of have the following options:
1. Replace the remaining space with a 'Void' element. The remaining space must be at least 2 bytes long.
2. Extend the VINT that represents the length of some element (before the desired track) to be bigger, but
still represent the same value - e.g., 0x81 -> 0x4001.
3. Not sure if possible, extend the value of FF that we are adding - e.g., 0x0001 instead of 0x01.

When changing element sizes (by adding/editing/removing children) we need to keep an eye on the VINT that
represents the length of that element because it is possible that the size of the element won't be able to be
represented by a VINT of the same size, this is not a problem if the size of the element was reduced becase it's
possible to represent a small integer by a VINT whose size is bigger than the minimal size. However, this becomes
a problem if the element grew in size and the size of the length VINT needs to be increased


Note that when performing actions that change the position of a 'SeekHead' element or the position of a
top level element(*6) that is pointed by a certain 'SeekHead', the 'SeekPosition' of the affected 'SeekHead'
must be adjusted such that 'SeekPosition' will contain the offset of the top level element that is pointed by
that 'SeekHead' relative to the beginning(*7) of the 'SeekHead' element.

Remarks:

(*1) In the Matroshka Element Specificationm it is described that FF value overrides FD.

(*2) In the Matroshka Element Specification, it is described that a LANG element must be ignored when a LANGI element is present.

(*3) I write 'probably' because if the element-to-be-removed is a child of our desired track, no shifting needs to be done at all and all we have to do is to replace that element with a FF.

(*4) This may happen only if none of the option listed above above are available.

(*5) Each element whose size VINT can longer be encoded in their original length.

(*6) A top level element is a first-degree child of the 'Segment' element.

(*7) The offset in the file where the ID of the element begins.

Interesting functions in the VLC 3.0.16 source code:
```
File					Function name
matroska_segment_parse.cpp 		matroska_segment_c::ParseTrackEntry
matroska_segment.cpp 			matroska_segment_c::ComputeTrackPriority
```

Helpful links:

RFC 8794 Extensible Binary Meta Language - https://www.rfc-editor.org/rfc/rfc8794.html

Matroska element specification - https://www.matroska.org/technical/elements.html
