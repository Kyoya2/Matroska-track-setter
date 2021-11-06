#pragma once
#include "Common.h"
#include "EbmlElementID.h"

enum class EbmlElementType
{
    Master,
    Int,
    UInt,
    Float,
    AsciiString,
    Utf8String,
    Date,
    Binary
};

#pragma pack(push, 1)
struct EbmlElementSpecification
{
    const std::string_view name;
    const EbmlElementType element_type;
};
#pragma pack(pop)

namespace EbmlElements
{
    const std::unordered_map<EbmlElementIDType, EbmlElementSpecification> ELEMENTS
    {
        {0x1a45dfa3, {"EBML", EbmlElementType::Master}},
        {0x4286    , {"EBMLVersion", EbmlElementType::UInt}},
        {0x42f7    , {"EBMLReadVersion", EbmlElementType::UInt}},
        {0x4282    , {"DocType", EbmlElementType::AsciiString}},
        {0x4287    , {"DocTypeVersion", EbmlElementType::UInt}},
        {0x4285    , {"DocTypeReadVersion", EbmlElementType::UInt}},
        {0x4281    , {"DocTypeExtension", EbmlElementType::Master}},
        {0x4283    , {"DocTypeExtensionName", EbmlElementType::AsciiString}},
        {0x4284    , {"DocTypeExtensionVersion", EbmlElementType::UInt}},
        {0xbf      , {"CRC-32", EbmlElementType::Binary}},
        {0xec      , {"Void", EbmlElementType::Binary}},
        {0x42f2    , {"EBMLMaxIDLength", EbmlElementType::UInt}},
        {0x42f3    , {"EBMLMaxSizeLength", EbmlElementType::UInt}},
        {0x18538067, {"Segment", EbmlElementType::Master}},
        {0x114d9b74, {"SeekHead", EbmlElementType::Master}},
        {0x4dbb    , {"Seek", EbmlElementType::Master}},
        {0x53ab    , {"SeekID", EbmlElementType::Binary}},
        {0x53ac    , {"SeekPosition", EbmlElementType::UInt}},
        {0x1549a966, {"Info", EbmlElementType::Master}},
        {0x73a4    , {"SegmentUID", EbmlElementType::Binary}},
        {0x7384    , {"SegmentFilename", EbmlElementType::Utf8String}},
        {0x3cb923  , {"PrevUID", EbmlElementType::Binary}},
        {0x3c83ab  , {"PrevFilename", EbmlElementType::Utf8String}},
        {0x3eb923  , {"NextUID", EbmlElementType::Binary}},
        {0x3e83bb  , {"NextFilename", EbmlElementType::Utf8String}},
        {0x4444    , {"SegmentFamily", EbmlElementType::Binary}},
        {0x6924    , {"ChapterTranslate", EbmlElementType::Master}},
        {0x69a5    , {"ChapterTranslateID", EbmlElementType::Binary}},
        {0x69bf    , {"ChapterTranslateCodec", EbmlElementType::UInt}},
        {0x69fc    , {"ChapterTranslateEditionUID", EbmlElementType::UInt}},
        {0x2ad7b1  , {"TimestampScale", EbmlElementType::UInt}},
        {0x4489    , {"Duration", EbmlElementType::Float}},
        {0x4461    , {"DateUTC", EbmlElementType::Date}},
        {0x7ba9    , {"Title", EbmlElementType::Utf8String}},
        {0x4d80    , {"MuxingApp", EbmlElementType::Utf8String}},
        {0x5741    , {"WritingApp", EbmlElementType::Utf8String}},
        {0x1f43b675, {"Cluster", EbmlElementType::Master}},
        {0xe7      , {"Timestamp", EbmlElementType::UInt}},
        {0x5854    , {"SilentTracks", EbmlElementType::Master}},
        {0x58d7    , {"SilentTrackNumber", EbmlElementType::UInt}},
        {0xa7      , {"Position", EbmlElementType::UInt}},
        {0xab      , {"PrevSize", EbmlElementType::UInt}},
        {0xa3      , {"SimpleBlock", EbmlElementType::Binary}},
        {0xa0      , {"BlockGroup", EbmlElementType::Master}},
        {0xa1      , {"Block", EbmlElementType::Binary}},
        {0xa2      , {"BlockVirtual", EbmlElementType::Binary}},
        {0x75a1    , {"BlockAdditions", EbmlElementType::Master}},
        {0xa6      , {"BlockMore", EbmlElementType::Master}},
        {0xee      , {"BlockAddID", EbmlElementType::UInt}},
        {0xa5      , {"BlockAdditional", EbmlElementType::Binary}},
        {0x9b      , {"BlockDuration", EbmlElementType::UInt}},
        {0xfa      , {"ReferencePriority", EbmlElementType::UInt}},
        {0xfb      , {"ReferenceBlock", EbmlElementType::Int}},
        {0xfd      , {"ReferenceVirtual", EbmlElementType::Int}},
        {0xa4      , {"CodecState", EbmlElementType::Binary}},
        {0x75a2    , {"DiscardPadding", EbmlElementType::Int}},
        {0x8e      , {"Slices", EbmlElementType::Master}},
        {0xe8      , {"TimeSlice", EbmlElementType::Master}},
        {0xcc      , {"LaceNumber", EbmlElementType::UInt}},
        {0xcd      , {"FrameNumber", EbmlElementType::UInt}},
        {0xcb      , {"BlockAdditionID", EbmlElementType::UInt}},
        {0xce      , {"Delay", EbmlElementType::UInt}},
        {0xcf      , {"SliceDuration", EbmlElementType::UInt}},
        {0xc8      , {"ReferenceFrame", EbmlElementType::Master}},
        {0xc9      , {"ReferenceOffset", EbmlElementType::UInt}},
        {0xca      , {"ReferenceTimestamp", EbmlElementType::UInt}},
        {0xaf      , {"EncryptedBlock", EbmlElementType::Binary}},
        {0x1654ae6b, {"Tracks", EbmlElementType::Master}},
        {0xae      , {"TrackEntry", EbmlElementType::Master}},
        {0xd7      , {"TrackNumber", EbmlElementType::UInt}},
        {0x73c5    , {"TrackUID", EbmlElementType::UInt}},
        {0x83      , {"TrackType", EbmlElementType::UInt}},
        {0xb9      , {"FlagEnabled", EbmlElementType::UInt}},
        {0x88      , {"FlagDefault", EbmlElementType::UInt}},
        {0x55aa    , {"FlagForced", EbmlElementType::UInt}},
        {0x55ab    , {"FlagHearingImpaired", EbmlElementType::UInt}},
        {0x55ac    , {"FlagVisualImpaired", EbmlElementType::UInt}},
        {0x55ad    , {"FlagTextDescriptions", EbmlElementType::UInt}},
        {0x55ae    , {"FlagOriginal", EbmlElementType::UInt}},
        {0x55af    , {"FlagCommentary", EbmlElementType::UInt}},
        {0x9c      , {"FlagLacing", EbmlElementType::UInt}},
        {0x6de7    , {"MinCache", EbmlElementType::UInt}},
        {0x6df8    , {"MaxCache", EbmlElementType::UInt}},
        {0x23e383  , {"DefaultDuration", EbmlElementType::UInt}},
        {0x234e7a  , {"DefaultDecodedFieldDuration", EbmlElementType::UInt}},
        {0x23314f  , {"TrackTimestampScale", EbmlElementType::Float}},
        {0x537f    , {"TrackOffset", EbmlElementType::Int}},
        {0x55ee    , {"MaxBlockAdditionID", EbmlElementType::UInt}},
        {0x41e4    , {"BlockAdditionMapping", EbmlElementType::Master}},
        {0x41f0    , {"BlockAddIDValue", EbmlElementType::UInt}},
        {0x41a4    , {"BlockAddIDName", EbmlElementType::AsciiString}},
        {0x41e7    , {"BlockAddIDType", EbmlElementType::UInt}},
        {0x41ed    , {"BlockAddIDExtraData", EbmlElementType::Binary}},
        {0x536e    , {"Name", EbmlElementType::Utf8String}},
        {0x22b59c  , {"Language", EbmlElementType::AsciiString}},
        {0x22b59d  , {"LanguageIETF", EbmlElementType::AsciiString}},
        {0x86      , {"CodecID", EbmlElementType::AsciiString}},
        {0x63a2    , {"CodecPrivate", EbmlElementType::Binary}},
        {0x258688  , {"CodecName", EbmlElementType::Utf8String}},
        {0x7446    , {"AttachmentLink", EbmlElementType::UInt}},
        {0x3a9697  , {"CodecSettings", EbmlElementType::Utf8String}},
        {0x3b4040  , {"CodecInfoURL", EbmlElementType::AsciiString}},
        {0x26b240  , {"CodecDownloadURL", EbmlElementType::AsciiString}},
        {0xaa      , {"CodecDecodeAll", EbmlElementType::UInt}},
        {0x6fab    , {"TrackOverlay", EbmlElementType::UInt}},
        {0x56aa    , {"CodecDelay", EbmlElementType::UInt}},
        {0x56bb    , {"SeekPreRoll", EbmlElementType::UInt}},
        {0x6624    , {"TrackTranslate", EbmlElementType::Master}},
        {0x66a5    , {"TrackTranslateTrackID", EbmlElementType::Binary}},
        {0x66bf    , {"TrackTranslateCodec", EbmlElementType::UInt}},
        {0x66fc    , {"TrackTranslateEditionUID", EbmlElementType::UInt}},
        {0xe0      , {"Video", EbmlElementType::Master}},
        {0x9a      , {"FlagInterlaced", EbmlElementType::UInt}},
        {0x9d      , {"FieldOrder", EbmlElementType::UInt}},
        {0x53b8    , {"StereoMode", EbmlElementType::UInt}},
        {0x53c0    , {"AlphaMode", EbmlElementType::UInt}},
        {0x53b9    , {"OldStereoMode", EbmlElementType::UInt}},
        {0xb0      , {"PixelWidth", EbmlElementType::UInt}},
        {0xba      , {"PixelHeight", EbmlElementType::UInt}},
        {0x54aa    , {"PixelCropBottom", EbmlElementType::UInt}},
        {0x54bb    , {"PixelCropTop", EbmlElementType::UInt}},
        {0x54cc    , {"PixelCropLeft", EbmlElementType::UInt}},
        {0x54dd    , {"PixelCropRight", EbmlElementType::UInt}},
        {0x54b0    , {"DisplayWidth", EbmlElementType::UInt}},
        {0x54ba    , {"DisplayHeight", EbmlElementType::UInt}},
        {0x54b2    , {"DisplayUnit", EbmlElementType::UInt}},
        {0x54b3    , {"AspectRatioType", EbmlElementType::UInt}},
        {0x2eb524  , {"UncompressedFourCC", EbmlElementType::Binary}},
        {0x2fb523  , {"GammaValue", EbmlElementType::Float}},
        {0x2383e3  , {"FrameRate", EbmlElementType::Float}},
        {0x55b0    , {"Colour", EbmlElementType::Master}},
        {0x55b1    , {"MatrixCoefficients", EbmlElementType::UInt}},
        {0x55b2    , {"BitsPerChannel", EbmlElementType::UInt}},
        {0x55b3    , {"ChromaSubsamplingHorz", EbmlElementType::UInt}},
        {0x55b4    , {"ChromaSubsamplingVert", EbmlElementType::UInt}},
        {0x55b5    , {"CbSubsamplingHorz", EbmlElementType::UInt}},
        {0x55b6    , {"CbSubsamplingVert", EbmlElementType::UInt}},
        {0x55b7    , {"ChromaSitingHorz", EbmlElementType::UInt}},
        {0x55b8    , {"ChromaSitingVert", EbmlElementType::UInt}},
        {0x55b9    , {"Range", EbmlElementType::UInt}},
        {0x55ba    , {"TransferCharacteristics", EbmlElementType::UInt}},
        {0x55bb    , {"Primaries", EbmlElementType::UInt}},
        {0x55bc    , {"MaxCLL", EbmlElementType::UInt}},
        {0x55bd    , {"MaxFALL", EbmlElementType::UInt}},
        {0x55d0    , {"MasteringMetadata", EbmlElementType::Master}},
        {0x55d1    , {"PrimaryRChromaticityX", EbmlElementType::Float}},
        {0x55d2    , {"PrimaryRChromaticityY", EbmlElementType::Float}},
        {0x55d3    , {"PrimaryGChromaticityX", EbmlElementType::Float}},
        {0x55d4    , {"PrimaryGChromaticityY", EbmlElementType::Float}},
        {0x55d5    , {"PrimaryBChromaticityX", EbmlElementType::Float}},
        {0x55d6    , {"PrimaryBChromaticityY", EbmlElementType::Float}},
        {0x55d7    , {"WhitePointChromaticityX", EbmlElementType::Float}},
        {0x55d8    , {"WhitePointChromaticityY", EbmlElementType::Float}},
        {0x55d9    , {"LuminanceMax", EbmlElementType::Float}},
        {0x55da    , {"LuminanceMin", EbmlElementType::Float}},
        {0x7670    , {"Projection", EbmlElementType::Master}},
        {0x7671    , {"ProjectionType", EbmlElementType::UInt}},
        {0x7672    , {"ProjectionPrivate", EbmlElementType::Binary}},
        {0x7673    , {"ProjectionPoseYaw", EbmlElementType::Float}},
        {0x7674    , {"ProjectionPosePitch", EbmlElementType::Float}},
        {0x7675    , {"ProjectionPoseRoll", EbmlElementType::Float}},
        {0xe1      , {"Audio", EbmlElementType::Master}},
        {0xb5      , {"SamplingFrequency", EbmlElementType::Float}},
        {0x78b5    , {"OutputSamplingFrequency", EbmlElementType::Float}},
        {0x9f      , {"Channels", EbmlElementType::UInt}},
        {0x7d7b    , {"ChannelPositions", EbmlElementType::Binary}},
        {0x6264    , {"BitDepth", EbmlElementType::UInt}},
        {0xe2      , {"TrackOperation", EbmlElementType::Master}},
        {0xe3      , {"TrackCombinePlanes", EbmlElementType::Master}},
        {0xe4      , {"TrackPlane", EbmlElementType::Master}},
        {0xe5      , {"TrackPlaneUID", EbmlElementType::UInt}},
        {0xe6      , {"TrackPlaneType", EbmlElementType::UInt}},
        {0xe9      , {"TrackJoinBlocks", EbmlElementType::Master}},
        {0xed      , {"TrackJoinUID", EbmlElementType::UInt}},
        {0xc0      , {"TrickTrackUID", EbmlElementType::UInt}},
        {0xc1      , {"TrickTrackSegmentUID", EbmlElementType::Binary}},
        {0xc6      , {"TrickTrackFlag", EbmlElementType::UInt}},
        {0xc7      , {"TrickMasterTrackUID", EbmlElementType::UInt}},
        {0xc4      , {"TrickMasterTrackSegmentUID", EbmlElementType::Binary}},
        {0x6d80    , {"ContentEncodings", EbmlElementType::Master}},
        {0x6240    , {"ContentEncoding", EbmlElementType::Master}},
        {0x5031    , {"ContentEncodingOrder", EbmlElementType::UInt}},
        {0x5032    , {"ContentEncodingScope", EbmlElementType::UInt}},
        {0x5033    , {"ContentEncodingType", EbmlElementType::UInt}},
        {0x5034    , {"ContentCompression", EbmlElementType::Master}},
        {0x4254    , {"ContentCompAlgo", EbmlElementType::UInt}},
        {0x4255    , {"ContentCompSettings", EbmlElementType::Binary}},
        {0x5035    , {"ContentEncryption", EbmlElementType::Master}},
        {0x47e1    , {"ContentEncAlgo", EbmlElementType::UInt}},
        {0x47e2    , {"ContentEncKeyID", EbmlElementType::Binary}},
        {0x47e7    , {"ContentEncAESSettings", EbmlElementType::Master}},
        {0x47e8    , {"AESSettingsCipherMode", EbmlElementType::UInt}},
        {0x47e3    , {"ContentSignature", EbmlElementType::Binary}},
        {0x47e4    , {"ContentSigKeyID", EbmlElementType::Binary}},
        {0x47e5    , {"ContentSigAlgo", EbmlElementType::UInt}},
        {0x47e6    , {"ContentSigHashAlgo", EbmlElementType::UInt}},
        {0x1c53bb6b, {"Cues", EbmlElementType::Master}},
        {0xbb      , {"CuePoint", EbmlElementType::Master}},
        {0xb3      , {"CueTime", EbmlElementType::UInt}},
        {0xb7      , {"CueTrackPositions", EbmlElementType::Master}},
        {0xf7      , {"CueTrack", EbmlElementType::UInt}},
        {0xf1      , {"CueClusterPosition", EbmlElementType::UInt}},
        {0xf0      , {"CueRelativePosition", EbmlElementType::UInt}},
        {0xb2      , {"CueDuration", EbmlElementType::UInt}},
        {0x5378    , {"CueBlockNumber", EbmlElementType::UInt}},
        {0xea      , {"CueCodecState", EbmlElementType::UInt}},
        {0xdb      , {"CueReference", EbmlElementType::Master}},
        {0x96      , {"CueRefTime", EbmlElementType::UInt}},
        {0x97      , {"CueRefCluster", EbmlElementType::UInt}},
        {0x535f    , {"CueRefNumber", EbmlElementType::UInt}},
        {0xeb      , {"CueRefCodecState", EbmlElementType::UInt}},
        {0x1941a469, {"Attachments", EbmlElementType::Master}},
        {0x61a7    , {"AttachedFile", EbmlElementType::Master}},
        {0x467e    , {"FileDescription", EbmlElementType::Utf8String}},
        {0x466e    , {"FileName", EbmlElementType::Utf8String}},
        {0x4660    , {"FileMimeType", EbmlElementType::AsciiString}},
        {0x465c    , {"FileData", EbmlElementType::Binary}},
        {0x46ae    , {"FileUID", EbmlElementType::UInt}},
        {0x4675    , {"FileReferral", EbmlElementType::Binary}},
        {0x4661    , {"FileUsedStartTime", EbmlElementType::UInt}},
        {0x4662    , {"FileUsedEndTime", EbmlElementType::UInt}},
        {0x1043a770, {"Chapters", EbmlElementType::Master}},
        {0x45b9    , {"EditionEntry", EbmlElementType::Master}},
        {0x45bc    , {"EditionUID", EbmlElementType::UInt}},
        {0x45bd    , {"EditionFlagHidden", EbmlElementType::UInt}},
        {0x45db    , {"EditionFlagDefault", EbmlElementType::UInt}},
        {0x45dd    , {"EditionFlagOrdered", EbmlElementType::UInt}},
        {0xb6      , {"ChapterAtom", EbmlElementType::Master}},
        {0x73c4    , {"ChapterUID", EbmlElementType::UInt}},
        {0x5654    , {"ChapterStringUID", EbmlElementType::Utf8String}},
        {0x91      , {"ChapterTimeStart", EbmlElementType::UInt}},
        {0x92      , {"ChapterTimeEnd", EbmlElementType::UInt}},
        {0x98      , {"ChapterFlagHidden", EbmlElementType::UInt}},
        {0x4598    , {"ChapterFlagEnabled", EbmlElementType::UInt}},
        {0x6e67    , {"ChapterSegmentUID", EbmlElementType::Binary}},
        {0x6ebc    , {"ChapterSegmentEditionUID", EbmlElementType::UInt}},
        {0x63c3    , {"ChapterPhysicalEquiv", EbmlElementType::UInt}},
        {0x8f      , {"ChapterTrack", EbmlElementType::Master}},
        {0x89      , {"ChapterTrackUID", EbmlElementType::UInt}},
        {0x80      , {"ChapterDisplay", EbmlElementType::Master}},
        {0x85      , {"ChapString", EbmlElementType::Utf8String}},
        {0x437c    , {"ChapLanguage", EbmlElementType::AsciiString}},
        {0x437d    , {"ChapLanguageIETF", EbmlElementType::AsciiString}},
        {0x437e    , {"ChapCountry", EbmlElementType::AsciiString}},
        {0x6944    , {"ChapProcess", EbmlElementType::Master}},
        {0x6955    , {"ChapProcessCodecID", EbmlElementType::UInt}},
        {0x450d    , {"ChapProcessPrivate", EbmlElementType::Binary}},
        {0x6911    , {"ChapProcessCommand", EbmlElementType::Master}},
        {0x6922    , {"ChapProcessTime", EbmlElementType::UInt}},
        {0x6933    , {"ChapProcessData", EbmlElementType::Binary}},
        {0x1254c367, {"Tags", EbmlElementType::Master}},
        {0x7373    , {"Tag", EbmlElementType::Master}},
        {0x63c0    , {"Targets", EbmlElementType::Master}},
        {0x68ca    , {"TargetTypeValue", EbmlElementType::UInt}},
        {0x63ca    , {"TargetType", EbmlElementType::AsciiString}},
        {0x63c5    , {"TagTrackUID", EbmlElementType::UInt}},
        {0x63c9    , {"TagEditionUID", EbmlElementType::UInt}},
        {0x63c4    , {"TagChapterUID", EbmlElementType::UInt}},
        {0x63c6    , {"TagAttachmentUID", EbmlElementType::UInt}},
        {0x67c8    , {"SimpleTag", EbmlElementType::Master}},
        {0x45a3    , {"TagName", EbmlElementType::Utf8String}},
        {0x447a    , {"TagLanguage", EbmlElementType::AsciiString}},
        {0x447b    , {"TagLanguageIETF", EbmlElementType::AsciiString}},
        {0x4484    , {"TagDefault", EbmlElementType::UInt}},
        {0x44b4    , {"TagDefaultBogus", EbmlElementType::UInt}},
        {0x4487    , {"TagString", EbmlElementType::Utf8String}},
        {0x4485    , {"TagBinary", EbmlElementType::Binary}}
    };

    enum class ChapterTranslateCodecValues {
        MatroskaScript = 0,
        DvdMenu = 1
    };
    enum class TrackTypeValues {
        Video = 1,
        Audio = 2,
        Complex = 3,
        Logo = 16,
        Subtitle = 17,
        Buttons = 18,
        Control = 32,
        Metadata = 33
    };
    enum class TrackTranslateCodecValues {
        MatroskaScript = 0,
        DvdMenu = 1
    };
    enum class FlagInterlacedValues {
        Undetermined = 0,
        Interlaced = 1,
        Progressive = 2
    };
    enum class FieldOrderValues {
        Progressive = 0,
        Tff = 1,
        Undetermined = 2,
        Bff = 6,
        BffSwapped = 9,
        TffSwapped = 14
    };
    enum class StereoModeValues {
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
    enum class OldStereoModeValues {
        Mono = 0,
        RightEye = 1,
        LeftEye = 2,
        BothEyes = 3
    };
    enum class DisplayUnitValues {
        Pixels = 0,
        Centimeters = 1,
        Inches = 2,
        DisplayAspectRatio = 3,
        Unknown = 4
    };
    enum class AspectRatioTypeValues {
        FreeResizing = 0,
        KeepAspectRatio = 1,
        Fixed = 2
    };
    enum class MatrixCoefficientsValues {
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
    enum class ChromaSitingHorzValues {
        Unspecified = 0,
        LeftCollocated = 1,
        Half = 2
    };
    enum class ChromaSitingVertValues {
        Unspecified = 0,
        TopCollocated = 1,
        Half = 2
    };
    enum class RangeValues {
        Unspecified = 0,
        BroadcastRange = 1,
        FullRangeNoClipping = 2,
        DefinedByMatrixcoefficientsOrTransfercharacteristics = 3
    };
    enum class TransferCharacteristicsValues {
        Reserved = 0,
        ItuRBt_709 = 1,
        Unspecified = 2,
        Reserved = 3,
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
    enum class PrimariesValues {
        Reserved = 0,
        ItuRBt_709 = 1,
        Unspecified = 2,
        Reserved = 3,
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
    enum class ProjectionTypeValues {
        Rectangular = 0,
        Equirectangular = 1,
        Cubemap = 2,
        Mesh = 3
    };
    enum class TrackPlaneTypeValues {
        LeftEye = 0,
        RightEye = 1,
        Background = 2
    };
    enum class ContentEncodingScopeValues {
        AllFrameContentsExcludingLacingData = 1,
        TheTracksPrivateData = 2,
        TheNextContentencodingNextContentencodingorder_EitherTheDataInsideContentcompressionAndOrOrContentencryption = 4
    };
    enum class ContentEncodingTypeValues {
        Compression = 0,
        Encryption = 1
    };
    enum class ContentCompAlgoValues {
        Zlib = 0,
        Bzlib = 1,
        Lzo1x = 2,
        HeaderStripping = 3
    };
    enum class ContentEncAlgoValues {
        NotEncrypted = 0,
        Des = 1,
        ThreeDes = 2,
        Twofish = 3,
        Blowfish = 4,
        Aes = 5
    };
    enum class AESSettingsCipherModeValues {
        AesCtrOrCounterNistSp80038a = 1,
        AesCbcOrCipherBlockChainingNistSp80038a = 2
    };
    enum class ContentSigAlgoValues {
        NotSigned = 0,
        Rsa = 1
    };
    enum class ContentSigHashAlgoValues {
        NotSigned = 0,
        Sha1160 = 1,
        Md5 = 2
    };
    enum class ChapProcessTimeValues {
        DuringTheWholeChapter = 0,
        BeforeStartingPlayback = 1,
        AfterPlaybackOfTheChapter = 2
    };
    enum class TargetTypeValueValues {
        Collection = 70,
        EditionOrIssueOrVolumeOrOpusOrSeasonOrSequel = 60,
        AlbumOrOperaOrConcertOrMovieOrEpisodeOrConcert = 50,
        PartOrSession = 40,
        TrackOrSongOrChapter = 30,
        SubtrackOrPartOrMovementOrScene = 20,
        Shot = 10
    };
    enum class TargetTypeValues {
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
    };
}