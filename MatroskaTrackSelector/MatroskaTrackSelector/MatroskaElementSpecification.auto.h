/*   
 *   Matroska track setter  Copyright (C) 2021  Kyoya2
 *   
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *   
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *   
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#pragma once

/*
 *  DISCLAIMER: This file was generated automatically by "generate_element_specification.py"
 */

#define DECL_ELEMENT_ID(name, value) static constexpr EbmlElementIDType name##_ID = value

// Element IDs
DECL_ELEMENT_ID(EBML, 0x1a45dfa3);
DECL_ELEMENT_ID(EBMLVersion, 0x4286);
DECL_ELEMENT_ID(EBMLReadVersion, 0x42f7);
DECL_ELEMENT_ID(DocType, 0x4282);
DECL_ELEMENT_ID(DocTypeVersion, 0x4287);
DECL_ELEMENT_ID(DocTypeReadVersion, 0x4285);
DECL_ELEMENT_ID(DocTypeExtension, 0x4281);
DECL_ELEMENT_ID(DocTypeExtensionName, 0x4283);
DECL_ELEMENT_ID(DocTypeExtensionVersion, 0x4284);
DECL_ELEMENT_ID(CRC_32, 0xbf);
DECL_ELEMENT_ID(Void, 0xec);
DECL_ELEMENT_ID(EBMLMaxIDLength, 0x42f2);
DECL_ELEMENT_ID(EBMLMaxSizeLength, 0x42f3);
DECL_ELEMENT_ID(Segment, 0x18538067);
DECL_ELEMENT_ID(SeekHead, 0x114d9b74);
DECL_ELEMENT_ID(Seek, 0x4dbb);
DECL_ELEMENT_ID(SeekID, 0x53ab);
DECL_ELEMENT_ID(SeekPosition, 0x53ac);
DECL_ELEMENT_ID(Info, 0x1549a966);
DECL_ELEMENT_ID(SegmentUID, 0x73a4);
DECL_ELEMENT_ID(SegmentFilename, 0x7384);
DECL_ELEMENT_ID(PrevUID, 0x3cb923);
DECL_ELEMENT_ID(PrevFilename, 0x3c83ab);
DECL_ELEMENT_ID(NextUID, 0x3eb923);
DECL_ELEMENT_ID(NextFilename, 0x3e83bb);
DECL_ELEMENT_ID(SegmentFamily, 0x4444);
DECL_ELEMENT_ID(ChapterTranslate, 0x6924);
DECL_ELEMENT_ID(ChapterTranslateID, 0x69a5);
DECL_ELEMENT_ID(ChapterTranslateCodec, 0x69bf);
DECL_ELEMENT_ID(ChapterTranslateEditionUID, 0x69fc);
DECL_ELEMENT_ID(TimestampScale, 0x2ad7b1);
DECL_ELEMENT_ID(Duration, 0x4489);
DECL_ELEMENT_ID(DateUTC, 0x4461);
DECL_ELEMENT_ID(Title, 0x7ba9);
DECL_ELEMENT_ID(MuxingApp, 0x4d80);
DECL_ELEMENT_ID(WritingApp, 0x5741);
DECL_ELEMENT_ID(Cluster, 0x1f43b675);
DECL_ELEMENT_ID(Timestamp, 0xe7);
DECL_ELEMENT_ID(SilentTracks, 0x5854);
DECL_ELEMENT_ID(SilentTrackNumber, 0x58d7);
DECL_ELEMENT_ID(Position, 0xa7);
DECL_ELEMENT_ID(PrevSize, 0xab);
DECL_ELEMENT_ID(SimpleBlock, 0xa3);
DECL_ELEMENT_ID(BlockGroup, 0xa0);
DECL_ELEMENT_ID(Block, 0xa1);
DECL_ELEMENT_ID(BlockVirtual, 0xa2);
DECL_ELEMENT_ID(BlockAdditions, 0x75a1);
DECL_ELEMENT_ID(BlockMore, 0xa6);
DECL_ELEMENT_ID(BlockAddID, 0xee);
DECL_ELEMENT_ID(BlockAdditional, 0xa5);
DECL_ELEMENT_ID(BlockDuration, 0x9b);
DECL_ELEMENT_ID(ReferencePriority, 0xfa);
DECL_ELEMENT_ID(ReferenceBlock, 0xfb);
DECL_ELEMENT_ID(ReferenceVirtual, 0xfd);
DECL_ELEMENT_ID(CodecState, 0xa4);
DECL_ELEMENT_ID(DiscardPadding, 0x75a2);
DECL_ELEMENT_ID(Slices, 0x8e);
DECL_ELEMENT_ID(TimeSlice, 0xe8);
DECL_ELEMENT_ID(LaceNumber, 0xcc);
DECL_ELEMENT_ID(FrameNumber, 0xcd);
DECL_ELEMENT_ID(BlockAdditionID, 0xcb);
DECL_ELEMENT_ID(Delay, 0xce);
DECL_ELEMENT_ID(SliceDuration, 0xcf);
DECL_ELEMENT_ID(ReferenceFrame, 0xc8);
DECL_ELEMENT_ID(ReferenceOffset, 0xc9);
DECL_ELEMENT_ID(ReferenceTimestamp, 0xca);
DECL_ELEMENT_ID(EncryptedBlock, 0xaf);
DECL_ELEMENT_ID(Tracks, 0x1654ae6b);
DECL_ELEMENT_ID(TrackEntry, 0xae);
DECL_ELEMENT_ID(TrackNumber, 0xd7);
DECL_ELEMENT_ID(TrackUID, 0x73c5);
DECL_ELEMENT_ID(TrackType, 0x83);
DECL_ELEMENT_ID(FlagEnabled, 0xb9);
DECL_ELEMENT_ID(FlagDefault, 0x88);
DECL_ELEMENT_ID(FlagForced, 0x55aa);
DECL_ELEMENT_ID(FlagHearingImpaired, 0x55ab);
DECL_ELEMENT_ID(FlagVisualImpaired, 0x55ac);
DECL_ELEMENT_ID(FlagTextDescriptions, 0x55ad);
DECL_ELEMENT_ID(FlagOriginal, 0x55ae);
DECL_ELEMENT_ID(FlagCommentary, 0x55af);
DECL_ELEMENT_ID(FlagLacing, 0x9c);
DECL_ELEMENT_ID(MinCache, 0x6de7);
DECL_ELEMENT_ID(MaxCache, 0x6df8);
DECL_ELEMENT_ID(DefaultDuration, 0x23e383);
DECL_ELEMENT_ID(DefaultDecodedFieldDuration, 0x234e7a);
DECL_ELEMENT_ID(TrackTimestampScale, 0x23314f);
DECL_ELEMENT_ID(TrackOffset, 0x537f);
DECL_ELEMENT_ID(MaxBlockAdditionID, 0x55ee);
DECL_ELEMENT_ID(BlockAdditionMapping, 0x41e4);
DECL_ELEMENT_ID(BlockAddIDValue, 0x41f0);
DECL_ELEMENT_ID(BlockAddIDName, 0x41a4);
DECL_ELEMENT_ID(BlockAddIDType, 0x41e7);
DECL_ELEMENT_ID(BlockAddIDExtraData, 0x41ed);
DECL_ELEMENT_ID(Name, 0x536e);
DECL_ELEMENT_ID(Language, 0x22b59c);
DECL_ELEMENT_ID(LanguageIETF, 0x22b59d);
DECL_ELEMENT_ID(CodecID, 0x86);
DECL_ELEMENT_ID(CodecPrivate, 0x63a2);
DECL_ELEMENT_ID(CodecName, 0x258688);
DECL_ELEMENT_ID(AttachmentLink, 0x7446);
DECL_ELEMENT_ID(CodecSettings, 0x3a9697);
DECL_ELEMENT_ID(CodecInfoURL, 0x3b4040);
DECL_ELEMENT_ID(CodecDownloadURL, 0x26b240);
DECL_ELEMENT_ID(CodecDecodeAll, 0xaa);
DECL_ELEMENT_ID(TrackOverlay, 0x6fab);
DECL_ELEMENT_ID(CodecDelay, 0x56aa);
DECL_ELEMENT_ID(SeekPreRoll, 0x56bb);
DECL_ELEMENT_ID(TrackTranslate, 0x6624);
DECL_ELEMENT_ID(TrackTranslateTrackID, 0x66a5);
DECL_ELEMENT_ID(TrackTranslateCodec, 0x66bf);
DECL_ELEMENT_ID(TrackTranslateEditionUID, 0x66fc);
DECL_ELEMENT_ID(Video, 0xe0);
DECL_ELEMENT_ID(FlagInterlaced, 0x9a);
DECL_ELEMENT_ID(FieldOrder, 0x9d);
DECL_ELEMENT_ID(StereoMode, 0x53b8);
DECL_ELEMENT_ID(AlphaMode, 0x53c0);
DECL_ELEMENT_ID(OldStereoMode, 0x53b9);
DECL_ELEMENT_ID(PixelWidth, 0xb0);
DECL_ELEMENT_ID(PixelHeight, 0xba);
DECL_ELEMENT_ID(PixelCropBottom, 0x54aa);
DECL_ELEMENT_ID(PixelCropTop, 0x54bb);
DECL_ELEMENT_ID(PixelCropLeft, 0x54cc);
DECL_ELEMENT_ID(PixelCropRight, 0x54dd);
DECL_ELEMENT_ID(DisplayWidth, 0x54b0);
DECL_ELEMENT_ID(DisplayHeight, 0x54ba);
DECL_ELEMENT_ID(DisplayUnit, 0x54b2);
DECL_ELEMENT_ID(AspectRatioType, 0x54b3);
DECL_ELEMENT_ID(UncompressedFourCC, 0x2eb524);
DECL_ELEMENT_ID(GammaValue, 0x2fb523);
DECL_ELEMENT_ID(FrameRate, 0x2383e3);
DECL_ELEMENT_ID(Colour, 0x55b0);
DECL_ELEMENT_ID(MatrixCoefficients, 0x55b1);
DECL_ELEMENT_ID(BitsPerChannel, 0x55b2);
DECL_ELEMENT_ID(ChromaSubsamplingHorz, 0x55b3);
DECL_ELEMENT_ID(ChromaSubsamplingVert, 0x55b4);
DECL_ELEMENT_ID(CbSubsamplingHorz, 0x55b5);
DECL_ELEMENT_ID(CbSubsamplingVert, 0x55b6);
DECL_ELEMENT_ID(ChromaSitingHorz, 0x55b7);
DECL_ELEMENT_ID(ChromaSitingVert, 0x55b8);
DECL_ELEMENT_ID(Range, 0x55b9);
DECL_ELEMENT_ID(TransferCharacteristics, 0x55ba);
DECL_ELEMENT_ID(Primaries, 0x55bb);
DECL_ELEMENT_ID(MaxCLL, 0x55bc);
DECL_ELEMENT_ID(MaxFALL, 0x55bd);
DECL_ELEMENT_ID(MasteringMetadata, 0x55d0);
DECL_ELEMENT_ID(PrimaryRChromaticityX, 0x55d1);
DECL_ELEMENT_ID(PrimaryRChromaticityY, 0x55d2);
DECL_ELEMENT_ID(PrimaryGChromaticityX, 0x55d3);
DECL_ELEMENT_ID(PrimaryGChromaticityY, 0x55d4);
DECL_ELEMENT_ID(PrimaryBChromaticityX, 0x55d5);
DECL_ELEMENT_ID(PrimaryBChromaticityY, 0x55d6);
DECL_ELEMENT_ID(WhitePointChromaticityX, 0x55d7);
DECL_ELEMENT_ID(WhitePointChromaticityY, 0x55d8);
DECL_ELEMENT_ID(LuminanceMax, 0x55d9);
DECL_ELEMENT_ID(LuminanceMin, 0x55da);
DECL_ELEMENT_ID(Projection, 0x7670);
DECL_ELEMENT_ID(ProjectionType, 0x7671);
DECL_ELEMENT_ID(ProjectionPrivate, 0x7672);
DECL_ELEMENT_ID(ProjectionPoseYaw, 0x7673);
DECL_ELEMENT_ID(ProjectionPosePitch, 0x7674);
DECL_ELEMENT_ID(ProjectionPoseRoll, 0x7675);
DECL_ELEMENT_ID(Audio, 0xe1);
DECL_ELEMENT_ID(SamplingFrequency, 0xb5);
DECL_ELEMENT_ID(OutputSamplingFrequency, 0x78b5);
DECL_ELEMENT_ID(Channels, 0x9f);
DECL_ELEMENT_ID(ChannelPositions, 0x7d7b);
DECL_ELEMENT_ID(BitDepth, 0x6264);
DECL_ELEMENT_ID(TrackOperation, 0xe2);
DECL_ELEMENT_ID(TrackCombinePlanes, 0xe3);
DECL_ELEMENT_ID(TrackPlane, 0xe4);
DECL_ELEMENT_ID(TrackPlaneUID, 0xe5);
DECL_ELEMENT_ID(TrackPlaneType, 0xe6);
DECL_ELEMENT_ID(TrackJoinBlocks, 0xe9);
DECL_ELEMENT_ID(TrackJoinUID, 0xed);
DECL_ELEMENT_ID(TrickTrackUID, 0xc0);
DECL_ELEMENT_ID(TrickTrackSegmentUID, 0xc1);
DECL_ELEMENT_ID(TrickTrackFlag, 0xc6);
DECL_ELEMENT_ID(TrickMasterTrackUID, 0xc7);
DECL_ELEMENT_ID(TrickMasterTrackSegmentUID, 0xc4);
DECL_ELEMENT_ID(ContentEncodings, 0x6d80);
DECL_ELEMENT_ID(ContentEncoding, 0x6240);
DECL_ELEMENT_ID(ContentEncodingOrder, 0x5031);
DECL_ELEMENT_ID(ContentEncodingScope, 0x5032);
DECL_ELEMENT_ID(ContentEncodingType, 0x5033);
DECL_ELEMENT_ID(ContentCompression, 0x5034);
DECL_ELEMENT_ID(ContentCompAlgo, 0x4254);
DECL_ELEMENT_ID(ContentCompSettings, 0x4255);
DECL_ELEMENT_ID(ContentEncryption, 0x5035);
DECL_ELEMENT_ID(ContentEncAlgo, 0x47e1);
DECL_ELEMENT_ID(ContentEncKeyID, 0x47e2);
DECL_ELEMENT_ID(ContentEncAESSettings, 0x47e7);
DECL_ELEMENT_ID(AESSettingsCipherMode, 0x47e8);
DECL_ELEMENT_ID(ContentSignature, 0x47e3);
DECL_ELEMENT_ID(ContentSigKeyID, 0x47e4);
DECL_ELEMENT_ID(ContentSigAlgo, 0x47e5);
DECL_ELEMENT_ID(ContentSigHashAlgo, 0x47e6);
DECL_ELEMENT_ID(Cues, 0x1c53bb6b);
DECL_ELEMENT_ID(CuePoint, 0xbb);
DECL_ELEMENT_ID(CueTime, 0xb3);
DECL_ELEMENT_ID(CueTrackPositions, 0xb7);
DECL_ELEMENT_ID(CueTrack, 0xf7);
DECL_ELEMENT_ID(CueClusterPosition, 0xf1);
DECL_ELEMENT_ID(CueRelativePosition, 0xf0);
DECL_ELEMENT_ID(CueDuration, 0xb2);
DECL_ELEMENT_ID(CueBlockNumber, 0x5378);
DECL_ELEMENT_ID(CueCodecState, 0xea);
DECL_ELEMENT_ID(CueReference, 0xdb);
DECL_ELEMENT_ID(CueRefTime, 0x96);
DECL_ELEMENT_ID(CueRefCluster, 0x97);
DECL_ELEMENT_ID(CueRefNumber, 0x535f);
DECL_ELEMENT_ID(CueRefCodecState, 0xeb);
DECL_ELEMENT_ID(Attachments, 0x1941a469);
DECL_ELEMENT_ID(AttachedFile, 0x61a7);
DECL_ELEMENT_ID(FileDescription, 0x467e);
DECL_ELEMENT_ID(FileName, 0x466e);
DECL_ELEMENT_ID(FileMimeType, 0x4660);
DECL_ELEMENT_ID(FileData, 0x465c);
DECL_ELEMENT_ID(FileUID, 0x46ae);
DECL_ELEMENT_ID(FileReferral, 0x4675);
DECL_ELEMENT_ID(FileUsedStartTime, 0x4661);
DECL_ELEMENT_ID(FileUsedEndTime, 0x4662);
DECL_ELEMENT_ID(Chapters, 0x1043a770);
DECL_ELEMENT_ID(EditionEntry, 0x45b9);
DECL_ELEMENT_ID(EditionUID, 0x45bc);
DECL_ELEMENT_ID(EditionFlagHidden, 0x45bd);
DECL_ELEMENT_ID(EditionFlagDefault, 0x45db);
DECL_ELEMENT_ID(EditionFlagOrdered, 0x45dd);
DECL_ELEMENT_ID(ChapterAtom, 0xb6);
DECL_ELEMENT_ID(ChapterUID, 0x73c4);
DECL_ELEMENT_ID(ChapterStringUID, 0x5654);
DECL_ELEMENT_ID(ChapterTimeStart, 0x91);
DECL_ELEMENT_ID(ChapterTimeEnd, 0x92);
DECL_ELEMENT_ID(ChapterFlagHidden, 0x98);
DECL_ELEMENT_ID(ChapterFlagEnabled, 0x4598);
DECL_ELEMENT_ID(ChapterSegmentUID, 0x6e67);
DECL_ELEMENT_ID(ChapterSegmentEditionUID, 0x6ebc);
DECL_ELEMENT_ID(ChapterPhysicalEquiv, 0x63c3);
DECL_ELEMENT_ID(ChapterTrack, 0x8f);
DECL_ELEMENT_ID(ChapterTrackUID, 0x89);
DECL_ELEMENT_ID(ChapterDisplay, 0x80);
DECL_ELEMENT_ID(ChapString, 0x85);
DECL_ELEMENT_ID(ChapLanguage, 0x437c);
DECL_ELEMENT_ID(ChapLanguageIETF, 0x437d);
DECL_ELEMENT_ID(ChapCountry, 0x437e);
DECL_ELEMENT_ID(ChapProcess, 0x6944);
DECL_ELEMENT_ID(ChapProcessCodecID, 0x6955);
DECL_ELEMENT_ID(ChapProcessPrivate, 0x450d);
DECL_ELEMENT_ID(ChapProcessCommand, 0x6911);
DECL_ELEMENT_ID(ChapProcessTime, 0x6922);
DECL_ELEMENT_ID(ChapProcessData, 0x6933);
DECL_ELEMENT_ID(Tags, 0x1254c367);
DECL_ELEMENT_ID(Tag, 0x7373);
DECL_ELEMENT_ID(Targets, 0x63c0);
DECL_ELEMENT_ID(TargetTypeValue, 0x68ca);
DECL_ELEMENT_ID(TargetType, 0x63ca);
DECL_ELEMENT_ID(TagTrackUID, 0x63c5);
DECL_ELEMENT_ID(TagEditionUID, 0x63c9);
DECL_ELEMENT_ID(TagChapterUID, 0x63c4);
DECL_ELEMENT_ID(TagAttachmentUID, 0x63c6);
DECL_ELEMENT_ID(SimpleTag, 0x67c8);
DECL_ELEMENT_ID(TagName, 0x45a3);
DECL_ELEMENT_ID(TagLanguage, 0x447a);
DECL_ELEMENT_ID(TagLanguageIETF, 0x447b);
DECL_ELEMENT_ID(TagDefault, 0x4484);
DECL_ELEMENT_ID(TagDefaultBogus, 0x44b4);
DECL_ELEMENT_ID(TagString, 0x4487);
DECL_ELEMENT_ID(TagBinary, 0x4485);

// Enum element values
enum class ChapterTranslateCodec {
    MatroskaScript = 0,
    DvdMenu = 1
};
enum class TrackType {
    Video = 1,
    Audio = 2,
    Complex = 3,
    Logo = 16,
    Subtitle = 17,
    Buttons = 18,
    Control = 32,
    Metadata = 33
};
enum class TrackTranslateCodec {
    MatroskaScript = 0,
    DvdMenu = 1
};
enum class FlagInterlaced {
    Undetermined = 0,
    Interlaced = 1,
    Progressive = 2
};
enum class FieldOrder {
    Progressive = 0,
    Tff = 1,
    Undetermined = 2,
    Bff = 6,
    BffSwapped = 9,
    TffSwapped = 14
};
enum class StereoMode {
    Mono = 0,
    SideBySideLeftEyeFirst = 1,
    TopToBottomRightEyeIsFirst = 2,
    TopToBottomLeftEyeIsFirst = 3,
    CheckboardRightEyeIsFirst = 4,
    CheckboardLeftEyeIsFirst = 5,
    RowInterleavedRightEyeIsFirst = 6,
    RowInterleavedLeftEyeIsFirst = 7,
    ColumnInterleavedRightEyeIsFirst = 8,
    ColumnInterleavedLeftEyeIsFirst = 9,
    AnaglyphCyanOrRed = 10,
    SideBySideRightEyeFirst = 11,
    AnaglyphGreenOrMagenta = 12,
    BothEyesLacedInOneBlockLeftEyeIsFirst = 13,
    BothEyesLacedInOneBlockRightEyeIsFirst = 14
};
enum class AlphaMode {
    None = 0,
    Present = 1
};
enum class OldStereoMode {
    Mono = 0,
    RightEye = 1,
    LeftEye = 2,
    BothEyes = 3
};
enum class DisplayUnit {
    Pixels = 0,
    Centimeters = 1,
    Inches = 2,
    DisplayAspectRatio = 3,
    Unknown = 4
};
enum class AspectRatioType {
    FreeResizing = 0,
    KeepAspectRatio = 1,
    Fixed = 2
};
enum class MatrixCoefficients {
    Identity = 0,
    ItuRBt_709 = 1,
    Unspecified = 2,
    Reserved = 3,
    UsFcc73_682 = 4,
    ItuRBt_470bg = 5,
    Smpte170m = 6,
    Smpte240m = 7,
    Ycocg = 8,
    Bt2020NonConstantLuminance = 9,
    Bt2020ConstantLuminance = 10,
    SmpteSt2085 = 11,
    ChromaDerivedNonConstantLuminance = 12,
    ChromaDerivedConstantLuminance = 13,
    ItuRBt_21000 = 14
};
enum class ChromaSitingHorz {
    Unspecified = 0,
    LeftCollocated = 1,
    Half = 2
};
enum class ChromaSitingVert {
    Unspecified = 0,
    TopCollocated = 1,
    Half = 2
};
enum class Range {
    Unspecified = 0,
    BroadcastRange = 1,
    FullRangeNoClipping = 2,
    DefinedByMatrixcoefficientsOrTransfercharacteristics = 3
};
enum class TransferCharacteristics {
    Reserved = 0,
    ItuRBt_709 = 1,
    Unspecified = 2,
    Reserved2 = 3,
    Gamma2_2CurveToBt_470m = 4,
    Gamma2_8CurveToBt_470bg = 5,
    Smpte170m = 6,
    Smpte240m = 7,
    Linear = 8,
    Log = 9,
    LogSqrt = 10,
    Iec6196624 = 11,
    ItuRBt_1361ExtendedColourGamut = 12,
    Iec6196621 = 13,
    ItuRBt_202010Bit = 14,
    ItuRBt_202012Bit = 15,
    ItuRBt_2100PerceptualQuantization = 16,
    SmpteSt4281 = 17,
    AribStdB67Hlg = 18
};
enum class Primaries {
    Reserved = 0,
    ItuRBt_709 = 1,
    Unspecified = 2,
    Reserved2 = 3,
    ItuRBt_470m = 4,
    ItuRBt_470bgToBt_601625 = 5,
    ItuRBt_601525ToSmpte170m = 6,
    Smpte240m = 7,
    Film = 8,
    ItuRBt_2020 = 9,
    SmpteSt4281 = 10,
    SmpteRp4322 = 11,
    SmpteEg4322 = 12,
    EbuTech_3213EToJedecP22Phosphors = 22
};
enum class ProjectionType {
    Rectangular = 0,
    Equirectangular = 1,
    Cubemap = 2,
    Mesh = 3
};
enum class TrackPlaneType {
    LeftEye = 0,
    RightEye = 1,
    Background = 2
};
enum class ContentEncodingScope {
    Block = 1,
    Private = 2,
    Next = 4
};
enum class ContentEncodingType {
    Compression = 0,
    Encryption = 1
};
enum class ContentCompAlgo {
    Zlib = 0,
    Bzlib = 1,
    Lzo1x = 2,
    HeaderStripping = 3
};
enum class ContentEncAlgo {
    NotEncrypted = 0,
    Des = 1,
    _3des = 2,
    Twofish = 3,
    Blowfish = 4,
    Aes = 5
};
enum class AESSettingsCipherMode {
    AesCtr = 1,
    AesCbc = 2
};
enum class ContentSigAlgo {
    NotSigned = 0,
    Rsa = 1
};
enum class ContentSigHashAlgo {
    NotSigned = 0,
    Sha1160 = 1,
    Md5 = 2
};
enum class ChapProcessTime {
    DuringTheWholeChapter = 0,
    BeforeStartingPlayback = 1,
    AfterPlaybackOfTheChapter = 2
};
enum class TargetTypeValue {
    Collection = 70,
    EditionOrIssueOrVolumeOrOpusOrSeasonOrSequel = 60,
    AlbumOrOperaOrConcertOrMovieOrEpisode = 50,
    PartOrSession = 40,
    TrackOrSongOrChapter = 30,
    SubtrackOrPartOrMovementOrScene = 20,
    Shot = 10
};
/*enum class TargetType {
    Collection = 'COLLECTION',
    Edition = 'EDITION',
    Issue = 'ISSUE',
    Volume = 'VOLUME',
    Opus = 'OPUS',
    Season = 'SEASON',
    Sequel = 'SEQUEL',
    Album = 'ALBUM',
    Opera = 'OPERA',
    Concert = 'CONCERT',
    Movie = 'MOVIE',
    Episode = 'EPISODE',
    Part = 'PART',
    Session = 'SESSION',
    Track = 'TRACK',
    Song = 'SONG',
    Chapter = 'CHAPTER',
    Subtrack = 'SUBTRACK',
    Movement = 'MOVEMENT',
    Scene = 'SCENE',
    Shot = 'SHOT'
};*/