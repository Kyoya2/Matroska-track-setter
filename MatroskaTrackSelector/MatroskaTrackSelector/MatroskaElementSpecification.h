/*
 * Copyright 2021 Kyoya2
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#pragma once

// Element IDs
static constexpr EbmlElementIDType EBML_ID = 0x1a45dfa3;
static constexpr EbmlElementIDType EBMLVersion_ID = 0x4286;
static constexpr EbmlElementIDType EBMLReadVersion_ID = 0x42f7;
static constexpr EbmlElementIDType DocType_ID = 0x4282;
static constexpr EbmlElementIDType DocTypeVersion_ID = 0x4287;
static constexpr EbmlElementIDType DocTypeReadVersion_ID = 0x4285;
static constexpr EbmlElementIDType DocTypeExtension_ID = 0x4281;
static constexpr EbmlElementIDType DocTypeExtensionName_ID = 0x4283;
static constexpr EbmlElementIDType DocTypeExtensionVersion_ID = 0x4284;
static constexpr EbmlElementIDType CRC_32_ID = 0xbf;
static constexpr EbmlElementIDType Void_ID = 0xec;
static constexpr EbmlElementIDType EBMLMaxIDLength_ID = 0x42f2;
static constexpr EbmlElementIDType EBMLMaxSizeLength_ID = 0x42f3;
static constexpr EbmlElementIDType Segment_ID = 0x18538067;
static constexpr EbmlElementIDType SeekHead_ID = 0x114d9b74;
static constexpr EbmlElementIDType Seek_ID = 0x4dbb;
static constexpr EbmlElementIDType SeekID_ID = 0x53ab;
static constexpr EbmlElementIDType SeekPosition_ID = 0x53ac;
static constexpr EbmlElementIDType Info_ID = 0x1549a966;
static constexpr EbmlElementIDType SegmentUID_ID = 0x73a4;
static constexpr EbmlElementIDType SegmentFilename_ID = 0x7384;
static constexpr EbmlElementIDType PrevUID_ID = 0x3cb923;
static constexpr EbmlElementIDType PrevFilename_ID = 0x3c83ab;
static constexpr EbmlElementIDType NextUID_ID = 0x3eb923;
static constexpr EbmlElementIDType NextFilename_ID = 0x3e83bb;
static constexpr EbmlElementIDType SegmentFamily_ID = 0x4444;
static constexpr EbmlElementIDType ChapterTranslate_ID = 0x6924;
static constexpr EbmlElementIDType ChapterTranslateID_ID = 0x69a5;
static constexpr EbmlElementIDType ChapterTranslateCodec_ID = 0x69bf;
static constexpr EbmlElementIDType ChapterTranslateEditionUID_ID = 0x69fc;
static constexpr EbmlElementIDType TimestampScale_ID = 0x2ad7b1;
static constexpr EbmlElementIDType Duration_ID = 0x4489;
static constexpr EbmlElementIDType DateUTC_ID = 0x4461;
static constexpr EbmlElementIDType Title_ID = 0x7ba9;
static constexpr EbmlElementIDType MuxingApp_ID = 0x4d80;
static constexpr EbmlElementIDType WritingApp_ID = 0x5741;
static constexpr EbmlElementIDType Cluster_ID = 0x1f43b675;
static constexpr EbmlElementIDType Timestamp_ID = 0xe7;
static constexpr EbmlElementIDType SilentTracks_ID = 0x5854;
static constexpr EbmlElementIDType SilentTrackNumber_ID = 0x58d7;
static constexpr EbmlElementIDType Position_ID = 0xa7;
static constexpr EbmlElementIDType PrevSize_ID = 0xab;
static constexpr EbmlElementIDType SimpleBlock_ID = 0xa3;
static constexpr EbmlElementIDType BlockGroup_ID = 0xa0;
static constexpr EbmlElementIDType Block_ID = 0xa1;
static constexpr EbmlElementIDType BlockVirtual_ID = 0xa2;
static constexpr EbmlElementIDType BlockAdditions_ID = 0x75a1;
static constexpr EbmlElementIDType BlockMore_ID = 0xa6;
static constexpr EbmlElementIDType BlockAddID_ID = 0xee;
static constexpr EbmlElementIDType BlockAdditional_ID = 0xa5;
static constexpr EbmlElementIDType BlockDuration_ID = 0x9b;
static constexpr EbmlElementIDType ReferencePriority_ID = 0xfa;
static constexpr EbmlElementIDType ReferenceBlock_ID = 0xfb;
static constexpr EbmlElementIDType ReferenceVirtual_ID = 0xfd;
static constexpr EbmlElementIDType CodecState_ID = 0xa4;
static constexpr EbmlElementIDType DiscardPadding_ID = 0x75a2;
static constexpr EbmlElementIDType Slices_ID = 0x8e;
static constexpr EbmlElementIDType TimeSlice_ID = 0xe8;
static constexpr EbmlElementIDType LaceNumber_ID = 0xcc;
static constexpr EbmlElementIDType FrameNumber_ID = 0xcd;
static constexpr EbmlElementIDType BlockAdditionID_ID = 0xcb;
static constexpr EbmlElementIDType Delay_ID = 0xce;
static constexpr EbmlElementIDType SliceDuration_ID = 0xcf;
static constexpr EbmlElementIDType ReferenceFrame_ID = 0xc8;
static constexpr EbmlElementIDType ReferenceOffset_ID = 0xc9;
static constexpr EbmlElementIDType ReferenceTimestamp_ID = 0xca;
static constexpr EbmlElementIDType EncryptedBlock_ID = 0xaf;
static constexpr EbmlElementIDType Tracks_ID = 0x1654ae6b;
static constexpr EbmlElementIDType TrackEntry_ID = 0xae;
static constexpr EbmlElementIDType TrackNumber_ID = 0xd7;
static constexpr EbmlElementIDType TrackUID_ID = 0x73c5;
static constexpr EbmlElementIDType TrackType_ID = 0x83;
static constexpr EbmlElementIDType FlagEnabled_ID = 0xb9;
static constexpr EbmlElementIDType FlagDefault_ID = 0x88;
static constexpr EbmlElementIDType FlagForced_ID = 0x55aa;
static constexpr EbmlElementIDType FlagHearingImpaired_ID = 0x55ab;
static constexpr EbmlElementIDType FlagVisualImpaired_ID = 0x55ac;
static constexpr EbmlElementIDType FlagTextDescriptions_ID = 0x55ad;
static constexpr EbmlElementIDType FlagOriginal_ID = 0x55ae;
static constexpr EbmlElementIDType FlagCommentary_ID = 0x55af;
static constexpr EbmlElementIDType FlagLacing_ID = 0x9c;
static constexpr EbmlElementIDType MinCache_ID = 0x6de7;
static constexpr EbmlElementIDType MaxCache_ID = 0x6df8;
static constexpr EbmlElementIDType DefaultDuration_ID = 0x23e383;
static constexpr EbmlElementIDType DefaultDecodedFieldDuration_ID = 0x234e7a;
static constexpr EbmlElementIDType TrackTimestampScale_ID = 0x23314f;
static constexpr EbmlElementIDType TrackOffset_ID = 0x537f;
static constexpr EbmlElementIDType MaxBlockAdditionID_ID = 0x55ee;
static constexpr EbmlElementIDType BlockAdditionMapping_ID = 0x41e4;
static constexpr EbmlElementIDType BlockAddIDValue_ID = 0x41f0;
static constexpr EbmlElementIDType BlockAddIDName_ID = 0x41a4;
static constexpr EbmlElementIDType BlockAddIDType_ID = 0x41e7;
static constexpr EbmlElementIDType BlockAddIDExtraData_ID = 0x41ed;
static constexpr EbmlElementIDType Name_ID = 0x536e;
static constexpr EbmlElementIDType Language_ID = 0x22b59c;
static constexpr EbmlElementIDType LanguageIETF_ID = 0x22b59d;
static constexpr EbmlElementIDType CodecID_ID = 0x86;
static constexpr EbmlElementIDType CodecPrivate_ID = 0x63a2;
static constexpr EbmlElementIDType CodecName_ID = 0x258688;
static constexpr EbmlElementIDType AttachmentLink_ID = 0x7446;
static constexpr EbmlElementIDType CodecSettings_ID = 0x3a9697;
static constexpr EbmlElementIDType CodecInfoURL_ID = 0x3b4040;
static constexpr EbmlElementIDType CodecDownloadURL_ID = 0x26b240;
static constexpr EbmlElementIDType CodecDecodeAll_ID = 0xaa;
static constexpr EbmlElementIDType TrackOverlay_ID = 0x6fab;
static constexpr EbmlElementIDType CodecDelay_ID = 0x56aa;
static constexpr EbmlElementIDType SeekPreRoll_ID = 0x56bb;
static constexpr EbmlElementIDType TrackTranslate_ID = 0x6624;
static constexpr EbmlElementIDType TrackTranslateTrackID_ID = 0x66a5;
static constexpr EbmlElementIDType TrackTranslateCodec_ID = 0x66bf;
static constexpr EbmlElementIDType TrackTranslateEditionUID_ID = 0x66fc;
static constexpr EbmlElementIDType Video_ID = 0xe0;
static constexpr EbmlElementIDType FlagInterlaced_ID = 0x9a;
static constexpr EbmlElementIDType FieldOrder_ID = 0x9d;
static constexpr EbmlElementIDType StereoMode_ID = 0x53b8;
static constexpr EbmlElementIDType AlphaMode_ID = 0x53c0;
static constexpr EbmlElementIDType OldStereoMode_ID = 0x53b9;
static constexpr EbmlElementIDType PixelWidth_ID = 0xb0;
static constexpr EbmlElementIDType PixelHeight_ID = 0xba;
static constexpr EbmlElementIDType PixelCropBottom_ID = 0x54aa;
static constexpr EbmlElementIDType PixelCropTop_ID = 0x54bb;
static constexpr EbmlElementIDType PixelCropLeft_ID = 0x54cc;
static constexpr EbmlElementIDType PixelCropRight_ID = 0x54dd;
static constexpr EbmlElementIDType DisplayWidth_ID = 0x54b0;
static constexpr EbmlElementIDType DisplayHeight_ID = 0x54ba;
static constexpr EbmlElementIDType DisplayUnit_ID = 0x54b2;
static constexpr EbmlElementIDType AspectRatioType_ID = 0x54b3;
static constexpr EbmlElementIDType UncompressedFourCC_ID = 0x2eb524;
static constexpr EbmlElementIDType GammaValue_ID = 0x2fb523;
static constexpr EbmlElementIDType FrameRate_ID = 0x2383e3;
static constexpr EbmlElementIDType Colour_ID = 0x55b0;
static constexpr EbmlElementIDType MatrixCoefficients_ID = 0x55b1;
static constexpr EbmlElementIDType BitsPerChannel_ID = 0x55b2;
static constexpr EbmlElementIDType ChromaSubsamplingHorz_ID = 0x55b3;
static constexpr EbmlElementIDType ChromaSubsamplingVert_ID = 0x55b4;
static constexpr EbmlElementIDType CbSubsamplingHorz_ID = 0x55b5;
static constexpr EbmlElementIDType CbSubsamplingVert_ID = 0x55b6;
static constexpr EbmlElementIDType ChromaSitingHorz_ID = 0x55b7;
static constexpr EbmlElementIDType ChromaSitingVert_ID = 0x55b8;
static constexpr EbmlElementIDType Range_ID = 0x55b9;
static constexpr EbmlElementIDType TransferCharacteristics_ID = 0x55ba;
static constexpr EbmlElementIDType Primaries_ID = 0x55bb;
static constexpr EbmlElementIDType MaxCLL_ID = 0x55bc;
static constexpr EbmlElementIDType MaxFALL_ID = 0x55bd;
static constexpr EbmlElementIDType MasteringMetadata_ID = 0x55d0;
static constexpr EbmlElementIDType PrimaryRChromaticityX_ID = 0x55d1;
static constexpr EbmlElementIDType PrimaryRChromaticityY_ID = 0x55d2;
static constexpr EbmlElementIDType PrimaryGChromaticityX_ID = 0x55d3;
static constexpr EbmlElementIDType PrimaryGChromaticityY_ID = 0x55d4;
static constexpr EbmlElementIDType PrimaryBChromaticityX_ID = 0x55d5;
static constexpr EbmlElementIDType PrimaryBChromaticityY_ID = 0x55d6;
static constexpr EbmlElementIDType WhitePointChromaticityX_ID = 0x55d7;
static constexpr EbmlElementIDType WhitePointChromaticityY_ID = 0x55d8;
static constexpr EbmlElementIDType LuminanceMax_ID = 0x55d9;
static constexpr EbmlElementIDType LuminanceMin_ID = 0x55da;
static constexpr EbmlElementIDType Projection_ID = 0x7670;
static constexpr EbmlElementIDType ProjectionType_ID = 0x7671;
static constexpr EbmlElementIDType ProjectionPrivate_ID = 0x7672;
static constexpr EbmlElementIDType ProjectionPoseYaw_ID = 0x7673;
static constexpr EbmlElementIDType ProjectionPosePitch_ID = 0x7674;
static constexpr EbmlElementIDType ProjectionPoseRoll_ID = 0x7675;
static constexpr EbmlElementIDType Audio_ID = 0xe1;
static constexpr EbmlElementIDType SamplingFrequency_ID = 0xb5;
static constexpr EbmlElementIDType OutputSamplingFrequency_ID = 0x78b5;
static constexpr EbmlElementIDType Channels_ID = 0x9f;
static constexpr EbmlElementIDType ChannelPositions_ID = 0x7d7b;
static constexpr EbmlElementIDType BitDepth_ID = 0x6264;
static constexpr EbmlElementIDType TrackOperation_ID = 0xe2;
static constexpr EbmlElementIDType TrackCombinePlanes_ID = 0xe3;
static constexpr EbmlElementIDType TrackPlane_ID = 0xe4;
static constexpr EbmlElementIDType TrackPlaneUID_ID = 0xe5;
static constexpr EbmlElementIDType TrackPlaneType_ID = 0xe6;
static constexpr EbmlElementIDType TrackJoinBlocks_ID = 0xe9;
static constexpr EbmlElementIDType TrackJoinUID_ID = 0xed;
static constexpr EbmlElementIDType TrickTrackUID_ID = 0xc0;
static constexpr EbmlElementIDType TrickTrackSegmentUID_ID = 0xc1;
static constexpr EbmlElementIDType TrickTrackFlag_ID = 0xc6;
static constexpr EbmlElementIDType TrickMasterTrackUID_ID = 0xc7;
static constexpr EbmlElementIDType TrickMasterTrackSegmentUID_ID = 0xc4;
static constexpr EbmlElementIDType ContentEncodings_ID = 0x6d80;
static constexpr EbmlElementIDType ContentEncoding_ID = 0x6240;
static constexpr EbmlElementIDType ContentEncodingOrder_ID = 0x5031;
static constexpr EbmlElementIDType ContentEncodingScope_ID = 0x5032;
static constexpr EbmlElementIDType ContentEncodingType_ID = 0x5033;
static constexpr EbmlElementIDType ContentCompression_ID = 0x5034;
static constexpr EbmlElementIDType ContentCompAlgo_ID = 0x4254;
static constexpr EbmlElementIDType ContentCompSettings_ID = 0x4255;
static constexpr EbmlElementIDType ContentEncryption_ID = 0x5035;
static constexpr EbmlElementIDType ContentEncAlgo_ID = 0x47e1;
static constexpr EbmlElementIDType ContentEncKeyID_ID = 0x47e2;
static constexpr EbmlElementIDType ContentEncAESSettings_ID = 0x47e7;
static constexpr EbmlElementIDType AESSettingsCipherMode_ID = 0x47e8;
static constexpr EbmlElementIDType ContentSignature_ID = 0x47e3;
static constexpr EbmlElementIDType ContentSigKeyID_ID = 0x47e4;
static constexpr EbmlElementIDType ContentSigAlgo_ID = 0x47e5;
static constexpr EbmlElementIDType ContentSigHashAlgo_ID = 0x47e6;
static constexpr EbmlElementIDType Cues_ID = 0x1c53bb6b;
static constexpr EbmlElementIDType CuePoint_ID = 0xbb;
static constexpr EbmlElementIDType CueTime_ID = 0xb3;
static constexpr EbmlElementIDType CueTrackPositions_ID = 0xb7;
static constexpr EbmlElementIDType CueTrack_ID = 0xf7;
static constexpr EbmlElementIDType CueClusterPosition_ID = 0xf1;
static constexpr EbmlElementIDType CueRelativePosition_ID = 0xf0;
static constexpr EbmlElementIDType CueDuration_ID = 0xb2;
static constexpr EbmlElementIDType CueBlockNumber_ID = 0x5378;
static constexpr EbmlElementIDType CueCodecState_ID = 0xea;
static constexpr EbmlElementIDType CueReference_ID = 0xdb;
static constexpr EbmlElementIDType CueRefTime_ID = 0x96;
static constexpr EbmlElementIDType CueRefCluster_ID = 0x97;
static constexpr EbmlElementIDType CueRefNumber_ID = 0x535f;
static constexpr EbmlElementIDType CueRefCodecState_ID = 0xeb;
static constexpr EbmlElementIDType Attachments_ID = 0x1941a469;
static constexpr EbmlElementIDType AttachedFile_ID = 0x61a7;
static constexpr EbmlElementIDType FileDescription_ID = 0x467e;
static constexpr EbmlElementIDType FileName_ID = 0x466e;
static constexpr EbmlElementIDType FileMimeType_ID = 0x4660;
static constexpr EbmlElementIDType FileData_ID = 0x465c;
static constexpr EbmlElementIDType FileUID_ID = 0x46ae;
static constexpr EbmlElementIDType FileReferral_ID = 0x4675;
static constexpr EbmlElementIDType FileUsedStartTime_ID = 0x4661;
static constexpr EbmlElementIDType FileUsedEndTime_ID = 0x4662;
static constexpr EbmlElementIDType Chapters_ID = 0x1043a770;
static constexpr EbmlElementIDType EditionEntry_ID = 0x45b9;
static constexpr EbmlElementIDType EditionUID_ID = 0x45bc;
static constexpr EbmlElementIDType EditionFlagHidden_ID = 0x45bd;
static constexpr EbmlElementIDType EditionFlagDefault_ID = 0x45db;
static constexpr EbmlElementIDType EditionFlagOrdered_ID = 0x45dd;
static constexpr EbmlElementIDType ChapterAtom_ID = 0xb6;
static constexpr EbmlElementIDType ChapterUID_ID = 0x73c4;
static constexpr EbmlElementIDType ChapterStringUID_ID = 0x5654;
static constexpr EbmlElementIDType ChapterTimeStart_ID = 0x91;
static constexpr EbmlElementIDType ChapterTimeEnd_ID = 0x92;
static constexpr EbmlElementIDType ChapterFlagHidden_ID = 0x98;
static constexpr EbmlElementIDType ChapterFlagEnabled_ID = 0x4598;
static constexpr EbmlElementIDType ChapterSegmentUID_ID = 0x6e67;
static constexpr EbmlElementIDType ChapterSegmentEditionUID_ID = 0x6ebc;
static constexpr EbmlElementIDType ChapterPhysicalEquiv_ID = 0x63c3;
static constexpr EbmlElementIDType ChapterTrack_ID = 0x8f;
static constexpr EbmlElementIDType ChapterTrackUID_ID = 0x89;
static constexpr EbmlElementIDType ChapterDisplay_ID = 0x80;
static constexpr EbmlElementIDType ChapString_ID = 0x85;
static constexpr EbmlElementIDType ChapLanguage_ID = 0x437c;
static constexpr EbmlElementIDType ChapLanguageIETF_ID = 0x437d;
static constexpr EbmlElementIDType ChapCountry_ID = 0x437e;
static constexpr EbmlElementIDType ChapProcess_ID = 0x6944;
static constexpr EbmlElementIDType ChapProcessCodecID_ID = 0x6955;
static constexpr EbmlElementIDType ChapProcessPrivate_ID = 0x450d;
static constexpr EbmlElementIDType ChapProcessCommand_ID = 0x6911;
static constexpr EbmlElementIDType ChapProcessTime_ID = 0x6922;
static constexpr EbmlElementIDType ChapProcessData_ID = 0x6933;
static constexpr EbmlElementIDType Tags_ID = 0x1254c367;
static constexpr EbmlElementIDType Tag_ID = 0x7373;
static constexpr EbmlElementIDType Targets_ID = 0x63c0;
static constexpr EbmlElementIDType TargetTypeValue_ID = 0x68ca;
static constexpr EbmlElementIDType TargetType_ID = 0x63ca;
static constexpr EbmlElementIDType TagTrackUID_ID = 0x63c5;
static constexpr EbmlElementIDType TagEditionUID_ID = 0x63c9;
static constexpr EbmlElementIDType TagChapterUID_ID = 0x63c4;
static constexpr EbmlElementIDType TagAttachmentUID_ID = 0x63c6;
static constexpr EbmlElementIDType SimpleTag_ID = 0x67c8;
static constexpr EbmlElementIDType TagName_ID = 0x45a3;
static constexpr EbmlElementIDType TagLanguage_ID = 0x447a;
static constexpr EbmlElementIDType TagLanguageIETF_ID = 0x447b;
static constexpr EbmlElementIDType TagDefault_ID = 0x4484;
static constexpr EbmlElementIDType TagDefaultBogus_ID = 0x44b4;
static constexpr EbmlElementIDType TagString_ID = 0x4487;
static constexpr EbmlElementIDType TagBinary_ID = 0x4485;


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
    AllFrameContentsExcludingLacingData = 1,
    TheTracksPrivateData = 2,
    TheNextContentencodingNextContentencodingorder_EitherTheDataInsideContentcompressionAndOrOrContentencryption = 4
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
    ThreeDes = 2,
    Twofish = 3,
    Blowfish = 4,
    Aes = 5
};
enum class AESSettingsCipherMode {
    AesCtrOrCounterNistSp80038a = 1,
    AesCbcOrCipherBlockChainingNistSp80038a = 2
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
    AlbumOrOperaOrConcertOrMovieOrEpisodeOrConcert = 50,
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