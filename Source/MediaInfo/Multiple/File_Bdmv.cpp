// File_Mpls - Info for Blu-ray Movie files
// Copyright (C) 2009-2009 Jerome Martinez, Zen@MediaArea.net
//
// This library is free software: you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this library. If not, see <http://www.gnu.org/licenses/>.
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//---------------------------------------------------------------------------
// Compilation conditions
#include "MediaInfo/Setup.h"
#ifdef __BORLANDC__
    #pragma hdrstop
#endif
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#if defined(MEDIAINFO_BDMV_YES)
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#include "MediaInfo/Multiple/File_Bdmv.h"
//---------------------------------------------------------------------------

namespace MediaInfoLib
{

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//     index        (INDX) with title
// --> MovieObject  (MOBJ) with mobj
// --> PlayList     (MPLS)
// --> PlayItem     (MPLS) with Mark
// --> ClipInfo     (CLPI)
// --> Clip (?)     (CLPI)
// --> Stream       (M2TS)
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//***************************************************************************
// Constants
//***************************************************************************

//---------------------------------------------------------------------------
namespace Elements
{
    const int32u CLPI=0x48444D56; //HDMV
    const int32u INDX=0x494E4458;
    const int32u MOBJ=0x4D4F424A;
    const int32u MPLS=0x4D504C53;
}

//***************************************************************************
// Infos
//***************************************************************************

//---------------------------------------------------------------------------
const char* Clpi_Offsets[]=
{
    "Unknown",
    "Unknown",
    "Streams",
    "Unknown",
    "Unknown",
    "Unknown",
    "Reserved",
    "Reserved",
    "Reserved",
};

//---------------------------------------------------------------------------
const char* Indx_Offsets[]=
{
    "AppInfoBDMV",
    "Indexes",
    "ExtensionData",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
};

//---------------------------------------------------------------------------
const char* Mobj_Offsets[]=
{
    "MovieObjects",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
};

//---------------------------------------------------------------------------
const char* Mpls_Offsets[]=
{
    "AppInfoPlayList",
    "PlayList",
    "PlayListMarks",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
};

//---------------------------------------------------------------------------
const char* Bdmv_Type(int32u Type_Indicator, size_t Start_Adress_Pos)
{
    switch (Type_Indicator)
    {
        case Elements::CLPI : return Clpi_Offsets[Start_Adress_Pos];
        case Elements::INDX : return Indx_Offsets[Start_Adress_Pos];
        case Elements::MOBJ : return Mobj_Offsets[Start_Adress_Pos];
        case Elements::MPLS : return Mpls_Offsets[Start_Adress_Pos];
        default             : return "";
    }
}

//---------------------------------------------------------------------------
const char* Clpi_Format(int8u StreamType)
{
    switch (StreamType)
    {
        case 0x01 : return "MPEG-1 Video";
        case 0x02 : return "MPEG-2 Video";
        case 0x03 : return "MPEG-1 Audio";
        case 0x04 : return "MPEG-2 Audio";
        case 0x80 : return "PCM";
        case 0x81 : return "AC-3";
        case 0x82 : return "DTS";
        case 0x83 : return "TrueHD";
        case 0x84 : return "E-AC-3";
        case 0x85 : return "DTS";
        case 0x86 : return "DTS";
        case 0x90 : return "PGS";
        case 0x91 : return "Interactive";
        case 0x92 : return "Subtitle";
        case 0x1B : return "AVC";
        case 0xA1 : return "E-AC-3"; //Secondary
        case 0xA2 : return "DTS"; //Secondary
        case 0xEA : return "VC-1";
        default   : return "";
    }
}

//---------------------------------------------------------------------------
const char* Clpi_Format_Profile(int8u StreamType)
{
    switch (StreamType)
    {
        case 0x85 : return "HD";
        case 0x86 : return "MA";
        case 0xA2 : return "HD"; //Secondary
        default   : return "";
    }
}

//---------------------------------------------------------------------------
stream_t Clpi_Type(int8u StreamType)
{
    switch (StreamType)
    {
        case 0x01 : return Stream_Video;
        case 0x02 : return Stream_Video;
        case 0x03 : return Stream_Audio;
        case 0x04 : return Stream_Audio;
        case 0x80 : return Stream_Audio;
        case 0x81 : return Stream_Audio;
        case 0x82 : return Stream_Audio;
        case 0x83 : return Stream_Audio;
        case 0x84 : return Stream_Audio;
        case 0x85 : return Stream_Audio;
        case 0x86 : return Stream_Audio;
        case 0x90 : return Stream_Text;
        case 0x91 : return Stream_Max;
        case 0x92 : return Stream_Text;
        case 0x1B : return Stream_Video;
        case 0xA1 : return Stream_Audio;
        case 0xA2 : return Stream_Audio;
        case 0xEA : return Stream_Video;
        default   : return Stream_Max;
    }
}

//---------------------------------------------------------------------------
const char* Clpi_Video_Format[]=
{
    "",
    "480i",
    "576i",
    "480p",
    "1080i",
    "720p",
    "1080p",
    "576p",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
};

//---------------------------------------------------------------------------
const char* Clpi_Video_Interlacement[]=
{
    "",
    "Interlaced",
    "Interlaced",
    "PPF",
    "Interlaced",
    "PPF",
    "PPF",
    "PPF",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
};

//---------------------------------------------------------------------------
const char* Clpi_Video_Standard[]=
{
    "",
    "NTSC",
    "PAL",
    "NTSC",
    "",
    "",
    "",
    "PAL",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
};

//---------------------------------------------------------------------------
int16u Clpi_Video_Width[]=
{
    0,
    720,
    720,
    720,
    1920,
    1280,
    1920,
    720,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
};

//---------------------------------------------------------------------------
int16u Clpi_Video_Height[]=
{
    0,
    480,
    576,
    480,
    1080,
    720,
    1080,
    576,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
};

//---------------------------------------------------------------------------
float32 Clpi_Video_FrameRate[]=
{
     0.000,
    23.976,
    24.000,
    25.000,
    29.970,
     0.000,
    50.000,
    59.940,
     0.000,
     0.000,
     0.000,
     0.000,
     0.000,
     0.000,
     0.000,
     0.000,
};

//---------------------------------------------------------------------------
float32 Clpi_Video_AspectRatio[]=
{
    0.000,
    0.000,
    1.333,
    1.778,
    2.210,
    0.000,
    0.000,
    0.000,
    0.000,
    0.000,
    0.000,
    0.000,
    0.000,
    0.000,
    0.000,
    0.000,
};

//---------------------------------------------------------------------------
int8u Clpi_Audio_Channels[]=
{
    0,
    1,
    0,
    2,
    0,
    0,
    0, //Multi 6-8
    0,
    0,
    0,
    0,
    0,
    0, //Combo
    0,
    0,
    0,
};

//---------------------------------------------------------------------------
int32u Clpi_Audio_SamplingRate[]=
{
        0,
    48000,
        0,
        0,
    96000,
   192000,
        0,
        0,
        0,
        0,
        0,
        0,
    48000, //192000?
    48000, // 96000?
        0,
        0,
};

//---------------------------------------------------------------------------
const char* Indx_object_type[]=
{
    "",
    "HDMV",
    "BD-J",
    "",
};

//---------------------------------------------------------------------------
const char* Indx_playback_type[4][4]=
{
    {"",            "",             "",             "",             },
    {"Movie",       "Interactive",  "",             "",             },
    {"",            "",             "Movie",        "Interactive",  },
    {"",            "",             "",             "",             },
};

//---------------------------------------------------------------------------
const char* Indx_title_search[]=
{
    "Permitted",
    "Prohibited1",
    "Prohibited2",
    "",
};

//---------------------------------------------------------------------------
const char* Mpls_playback_type[]=
{
    "Sequencial",
    "Random",
    "Shuffle",
    "",
};

//---------------------------------------------------------------------------
const char* Mpls_PlayListMarks_Mark_type(int8u type)
{
    switch (type)
    {
        case 1 : return "entry-mark";
        case 2 : return "link point";
        default: return "";
    }
}

//***************************************************************************
// Helpers
//***************************************************************************

//---------------------------------------------------------------------------
Ztring Bdmv_Decimal_Hexa(int64u Number)
{
    Ztring Temp;
    Temp.From_Number(Number);
    Temp+=_T(" (0x");
    Temp+=Ztring::ToZtring(Number, 16);
    Temp+=_T(")");
    return Temp;
}

//***************************************************************************
// Buffer - File header
//***************************************************************************

//---------------------------------------------------------------------------
bool File_Bdmv::FileHeader_Begin()
{
    //Element_Size
    if (Buffer_Size<4)
        return false; //Must wait for more data

    switch (CC4(Buffer))
    {
        case Elements::CLPI :
        case Elements::INDX :
        case Elements::MOBJ :
        case Elements::MPLS :
                              break;
        default             : Reject("Blu-ray");
                              return false;
    }

    //All should be OK...
    return true;
}

//***************************************************************************
// Buffer - Global
//***************************************************************************

//---------------------------------------------------------------------------
void File_Bdmv::Read_Buffer_Continue()
{
    if (Buffer_Size<File_Size)
    {
        Element_WaitForMoreData();
        return; //Wait for more data
    }

    //Parsing
    int32u type_indicator;
    int16u version_numberH;
    Element_Begin("Header");
    Get_C4 (type_indicator,                                     "type_indicator");
    Data_Accept("Blu-ray");
    Get_C2 (version_numberH,                                    "version_number (High)");
    Skip_C2(                                                    "version_number (Low)");
    Element_End();

    FILLING_BEGIN();
        Stream_Prepare(Stream_General);
        switch (type_indicator)
        {
            case Elements::CLPI : Fill(Stream_General, 0, General_Format, "Blu-ray Clip info"); break;
            case Elements::INDX : Fill(Stream_General, 0, General_Format, "Blu-ray Index"); break;
            case Elements::MOBJ : Fill(Stream_General, 0, General_Format, "Blu-ray Movie object"); break;
            case Elements::MPLS : Fill(Stream_General, 0, General_Format, "Blu-ray Playlist"); break;
            default             : ;
        }
    FILLING_END();

    if (version_numberH==0x3031 || version_numberH==0x3032) //Version 1 or 2
    {
        Element_Begin("Offsets");
        Types[0x28]=0; //First object
        for (size_t Start_Adress_Pos=1; Start_Adress_Pos<9; Start_Adress_Pos++)
        {
            int32u Start_Adress;
            Get_B4 (Start_Adress,                               Bdmv_Type(type_indicator, Start_Adress_Pos));
            Types[Start_Adress]=Start_Adress_Pos;
        }
        Element_End();

        for (std::map<int32u, size_t>::iterator Type=Types.begin(); Type!=Types.end(); Type++)
        {
            if (Type->first>=Element_Offset) //If valid
            {
                if (Type->first>Element_Offset)
                    Skip_XX(Type->first-Element_Offset,         "unknown");

                Element_Begin(Bdmv_Type(type_indicator, Type->second));
                int32u length;
                Get_B4 (length,                                 "length");
                int64u End=Element_Offset+length;
                switch (type_indicator)
                {
                    case Elements::CLPI :
                                            switch(Type->second)
                                            {
                                                case 2 : Clpi_Streams  (); break;
                                                default: ;
                                            }
                                            break;
                    case Elements::INDX :
                                            switch(Type->second)
                                            {
                                                case 0 : Indx_AppInfoBDMV(); break;
                                                case 1 : Indx_Indexes(); break;
                                                case 2 : Indx_ExtensionData(); break;
                                                default: ;
                                            }
                                            break;
                    case Elements::MOBJ :
                                            switch(Type->second)
                                            {
                                                case 0 : Mobj_MovieObjects(); break;
                                                case 1 : Mobj_ExtensionData(); break;
                                                default: ;
                                            }
                                            break;
                    case Elements::MPLS :
                                            switch(Type->second)
                                            {
                                                case 0 : Mpls_AppInfoPlayList(); break;
                                                case 1 : Mpls_PlayList(); break;
                                                case 2 : Mpls_PlayListMarks (); break;
                                                default: ;
                                            }
                                            break;
                    default             :   ;
                }
                if (End>Element_Offset)
                    Skip_XX(End-Element_Offset,                 "Unknown");
                Element_End();
            }
        }

        if (Element_Size>Element_Offset)
            Skip_XX(Element_Size-Element_Offset,                "Unknown");
    }
    else
        Skip_XX(Element_Size-Element_Offset,                    "Unknown");
}

//***************************************************************************
// Elements
//***************************************************************************

//---------------------------------------------------------------------------
void File_Bdmv::Clpi_Streams()
{
    //Parsing
    int8u Count;
    Skip_B4(                                                    "Unknown");
    Skip_B4(                                                    "Unknown");
    Get_B1 (Count,                                              "Streams count");
    Skip_B1(                                                    "Unknown");
    for (int16u Pos=0; Pos<Count; Pos++)
    {
        Element_Begin("Stream");
        int16u PID;
        int8u Length;
        Get_B2 (PID,                                            "PID");
        Get_B1 (Length,                                         "Length");
        int64u End=Element_Offset+Length;
        Get_B1 (stream_type,                                    "Stream type"); Param_Info(Clpi_Format(stream_type)); Element_Info(Clpi_Format(stream_type));
        switch (Clpi_Type(stream_type))
        {
            case Stream_Video : Clpi_Streams_Video(); break;
            case Stream_Audio : Clpi_Streams_Audio(); break;
            case Stream_Text  : Clpi_Streams_Text() ; break;
            default           : ;
        }

        if (End-Element_Offset)
            Skip_XX(End-Element_Offset,                         "Unknown");
        Element_End();

        FILLING_BEGIN();
            if (StreamKind_Last!=Stream_Max)
            {
                Fill(StreamKind_Last, StreamPos_Last, "ID", PID, 10, true);
                Fill(StreamKind_Last, StreamPos_Last, "ID/String", Bdmv_Decimal_Hexa(PID), true);
            }
        FILLING_END();
    }
}

//---------------------------------------------------------------------------
void File_Bdmv::Clpi_Streams_Video()
{
    //Parsing
    int8u Format, FrameRate, AspectRatio;
    BS_Begin();
    Get_S1 (4, Format,                                          "Format"); Param_Info(Clpi_Video_Format[Format]);
    Get_S1 (4, FrameRate,                                       "Frame rate"); Param_Info(Clpi_Video_FrameRate[FrameRate]);
    Get_S1 (4, AspectRatio,                                     "Aspect ratio"); Param_Info(Clpi_Video_AspectRatio[AspectRatio]);
    Skip_BS(4,                                                  "Reserved");
    BS_End();

    FILLING_BEGIN();
        Stream_Prepare(Stream_Video);
        Fill(Stream_Video, StreamPos_Last, Video_Format, Clpi_Format(stream_type));
        if (Clpi_Video_Width[Format])
            Fill(Stream_Video, StreamPos_Last, Video_Width, Clpi_Video_Width[Format]);
        if (Clpi_Video_Height[Format])
            Fill(Stream_Video, StreamPos_Last, Video_Height, Clpi_Video_Height[Format]);
        Fill(Stream_Video, StreamPos_Last, Video_Interlacement, Clpi_Video_Interlacement[stream_type]);
        Fill(Stream_Video, StreamPos_Last, Video_Standard, Clpi_Video_Standard[Format]);
        if (Clpi_Video_FrameRate[FrameRate])
            Fill(Stream_Video, StreamPos_Last, Video_FrameRate, Clpi_Video_FrameRate[FrameRate]);
        if (Clpi_Video_Height[AspectRatio])
            Fill(Stream_Video, StreamPos_Last, Video_DisplayAspectRatio, Clpi_Video_AspectRatio[AspectRatio]);
    FILLING_END();
}

//---------------------------------------------------------------------------
void File_Bdmv::Clpi_Streams_Audio()
{
    //Parsing
    int8u Channels, SamplingRate;
    BS_Begin();
    Get_S1 (4, Channels,                                        "Channel layout"); Param_Info(Clpi_Audio_Channels[Channels]);
    Get_S1 (4, SamplingRate,                                    "Sampling Rate"); Param_Info(Clpi_Audio_SamplingRate[SamplingRate]);
    BS_End();
    Info_Local(3, Language,                                     "Language"); Element_Info(Language);

    FILLING_BEGIN();
        Stream_Prepare(Stream_Audio);
        Fill(Stream_Audio, StreamPos_Last, Audio_Format, Clpi_Format(stream_type));
        Fill(Stream_Audio, StreamPos_Last, Audio_Format_Profile, Clpi_Format_Profile(stream_type));
        if (Clpi_Audio_Channels[Channels])
            Fill(Stream_Audio, StreamPos_Last, Audio_Channel_s_, Clpi_Audio_Channels[Channels]);
        if (Clpi_Audio_SamplingRate[SamplingRate])
            Fill(Stream_Audio, StreamPos_Last, Audio_SamplingRate, Clpi_Audio_SamplingRate[SamplingRate]);
        Fill(Stream_Audio, StreamPos_Last, Audio_Language, Language);
    FILLING_END();
}

//---------------------------------------------------------------------------
void File_Bdmv::Clpi_Streams_Text()
{
    //Parsing
    if (stream_type==0x92) //Subtitle
        Skip_B1(                                                "Unknown");
    Info_Local(3, Language,                                     "Language"); Element_Info(Language);

    FILLING_BEGIN();
        Stream_Prepare(Stream_Text);
        Fill(Stream_Text, StreamPos_Last, Text_Format, Clpi_Format(stream_type));
        Fill(Stream_Text, StreamPos_Last, Text_Language, Language);
    FILLING_END();
}

//---------------------------------------------------------------------------
void File_Bdmv::Indx_AppInfoBDMV()
{
    //Parsing
    Skip_B2(                                                    "reserved");
    Skip_Local(32,                                              "user_data");
}

//---------------------------------------------------------------------------
void File_Bdmv::Indx_Indexes()
{
    //Parsing
    int16u number_of_Titles;
    Element_Begin("FirstPlayback", 12);
        BS_Begin();
        Info_S1( 2, object_type,                                "object_type"); Param_Info(Indx_object_type[object_type]);
        Skip_S4(30,                                             "reserved");
        BS_End();
        Indx_Indexes_Index(object_type);
    Element_End();
    Element_Begin("TopMenu", 12); {
        BS_Begin();
        Info_S1( 2, object_type,                                "object_type"); Param_Info(Indx_object_type[object_type]);
        Skip_S4(30,                                             "reserved");
        BS_End();
        Indx_Indexes_Index(object_type);
    Element_End(); }
    Get_B2 (number_of_Titles,                                   "number_of_Titles");
    for (int16u Pos=0; Pos<number_of_Titles; Pos++)
    {
        Element_Begin("Title", 12);
        BS_Begin();
        Info_S1( 2, object_type,                                "object_type"); Param_Info(Indx_object_type[object_type]);
        Info_S1( 2, title_search,                               "title_search"); Param_Info(Indx_title_search[title_search]);
        Skip_S4(28,                                             "reserved");
        BS_End();
        Indx_Indexes_Index(object_type);
        Element_End();
    }
}

//---------------------------------------------------------------------------
void File_Bdmv::Indx_Indexes_Index(int8u object_type)
{
    BS_Begin();
    Info_S1( 2, playback_type,                                  "playback_type"); Param_Info(Indx_playback_type[object_type][playback_type]);
    Skip_S2(14,                                                 "reserved");
    BS_End();
    switch (object_type)
    {
        case 1 : //HDMV
                {
                Info_B2(id_ref,                                 "id_ref"); Element_Info(id_ref);
                Skip_B4(                                        "reserved");
                }
                break;
        case 2 : //BD-J
                {
                Info_Local(5, id_ref,                           "id_ref"); Element_Info(id_ref);
                Skip_B1(                                        "reserved");
                }
                break;
        default:
                Skip_XX(6,                                      "unknown");
    }
}

//---------------------------------------------------------------------------
void File_Bdmv::Indx_ExtensionData()
{
    //Parsing
    std::map<int32u, int32u> exts; //Key is the start adress, value is length
    int64u Base_Offset=Element_Offset-4; //Size is included
    int8u number_of_ext_data_entries;
    Skip_B4(                                                    "data_block_start_adress");
    Skip_B3(                                                    "reserved");
    Get_B1 (number_of_ext_data_entries,                         "number_of_ext_data_entries");
    for (int16u Pos=0; Pos<number_of_ext_data_entries; Pos++)
    {
        Element_Begin("ext_data_entry");
        int32u ext_data_start_adress, ext_data_length;
        Skip_B2(                                                "ID1 (AVCHD)");
        Skip_B2(                                                "ID2 (Version)");
        Get_B4 (ext_data_start_adress,                          "ext_data_start_adress");
        Get_B4 (ext_data_length,                                "ext_data_length");
        Element_End();
        exts[ext_data_start_adress]=ext_data_length;
    }

    for (std::map<int32u, int32u>::iterator ext=exts.begin(); ext!=exts.end(); ext++)
    {
        if (Base_Offset+ext->first>=Element_Offset)
        {
            if (Base_Offset+ext->first>Element_Offset)
                Skip_XX(ext->first-Element_Offset,              "Unknown");

            Element_Begin();
            int64u End=Element_Offset+ext->second;

            int32u type_indicator;
            Get_C4(type_indicator,                              "type_indicator"); Element_Info(Ztring().From_CC4(type_indicator));
            switch (type_indicator)
            {
                case 0x49444558 : Indx_ExtensionData_IDEX(); break;
                default         : Element_Name("Unknown");
                                  Skip_XX(ext->second-4,        "Unknown");
            }
            if (End>Element_Offset)
                Skip_XX(End-Element_Offset,                     "Unknown");
            Element_End();
        }
    }
}

//---------------------------------------------------------------------------
void File_Bdmv::Indx_ExtensionData_IDEX()
{
    Element_Name("IndexExtension");

    //Parsing
    int64u Base_Offset=Element_Offset-4; //Size is included
    int32u TableOfPlayLists_start_adress, MakersPrivateData_start_adress;
    Skip_B4(                                                    "reserved");
    Get_B4 (TableOfPlayLists_start_adress,                      "TableOfPlayLists_start_adress");
    Get_B4 (MakersPrivateData_start_adress,                     "MakersPrivateData_start_adress");
    Skip_XX(24,                                                 "reserved");

    Indx_ExtensionData_IDEX_UIAppInfoAVCHD();
    if (TableOfPlayLists_start_adress)
    {
        if (Base_Offset+TableOfPlayLists_start_adress>Element_Offset)
            Skip_XX(Base_Offset+TableOfPlayLists_start_adress-Element_Offset, "Unknown");
        Indx_ExtensionData_IDEX_TableOfPlayLists();
    }
    if (MakersPrivateData_start_adress)
    {
        if (Base_Offset+MakersPrivateData_start_adress>Element_Offset)
            Skip_XX(Base_Offset+MakersPrivateData_start_adress-Element_Offset, "Unknown");
        Indx_ExtensionData_IDEX_MakersPrivateData();
    }
}

//---------------------------------------------------------------------------
void File_Bdmv::Indx_ExtensionData_IDEX_UIAppInfoAVCHD()
{
    Element_Begin("UIAppInfoAVCHD");

    //Parsing
    int32u length, length2;
    int8u AVCHD_name_length;
    Get_B4 (length,                                             "length");
    Skip_B2(                                                    "maker_ID");
    Skip_B2(                                                    "maker_model_code");
    Skip_XX(32,                                                 "maker_private_area");
    BS_Begin();
    Skip_BS(15,                                                 "reserved");
    Skip_SB(                                                    "AVCHD_write_protect_flag");
    BS_End();
    Skip_B2(                                                    "ref_to_menu_thumbail_index");
    Skip_B1(                                                    "time_zone");
    Skip_XX(7,                                                  "record_time_and_date");
    Skip_B1(                                                    "reserved");
    Skip_B1(                                                    "AVCHD_character_set");
    Get_B1 (AVCHD_name_length,                                  "AVCHD_name_length");
    Skip_Local(AVCHD_name_length,                               "AVCHD_name");
    Skip_XX(255-AVCHD_name_length,                              "AVCHD_name (junk)");
    Element_Begin("additional data");
    Get_B4 (length2,                                            "length2");
    Skip_XX(length2,                                            "reserved");
    Element_End(4+length2);

    Element_End(4+length);
}

//---------------------------------------------------------------------------
void File_Bdmv::Indx_ExtensionData_IDEX_TableOfPlayLists()
{
    Element_Begin("TableOfPlayLists");

    //Parsing
    int32u length;
    Get_B4 (length,                                             "length");
    Skip_XX(length,                                             "unknown");

    Element_End();
}

//---------------------------------------------------------------------------
void File_Bdmv::Indx_ExtensionData_IDEX_MakersPrivateData()
{
    Element_Begin("MakersPrivateData");

    //Parsing
    int64u Base_Offset=Element_Offset-4; //Size is included
    int32u length, datablock_start_adress;
    int8u number_of_maker_entries;
    Get_B4 (length,                                             "length");
    Get_B4 (datablock_start_adress,                             "datablock_start_adress");
    Skip_XX(24,                                                 "reserved");
    Get_B1 (number_of_maker_entries,                            "number_of_maker_entries");
    for (int8u Pos=0; Pos<number_of_maker_entries; Pos++)
    {
        Element_Begin("maker_entry");
        Skip_B2(                                                "maker_ID");
        Skip_B2(                                                "maker_model_code");
        Skip_B4(                                                "mpd_start_adress");
        Skip_B4(                                                "mpd_length");
        Element_End();
    }

    if (datablock_start_adress)
    {
        if (Base_Offset+datablock_start_adress>Element_Offset)
            Skip_XX(Base_Offset+datablock_start_adress-Element_Offset, "Unknown");
        Skip_XX(length-datablock_start_adress,                  "Unknown");
    }

    Element_End();
}

//---------------------------------------------------------------------------
void File_Bdmv::Mobj_MovieObjects()
{
    //Parsing
    int16u number_of_mobjs;
    Skip_B4(                                                    "reserved");
    Get_B2 (number_of_mobjs,                                    "number_of_mobj");
    for (int16u Pos=0; Pos<number_of_mobjs; Pos++)
    {
        Element_Begin("mobj");
        int16u number_of_navigation_commands;
        BS_Begin();
        Info_SB(resume,                                         "resume"); Param_Info(resume?"suspend":"discard");
        Info_SB(menu_call,                                      "menu_call"); Param_Info(menu_call?"enable":"disable");
        Info_SB(title_search,                                   "title_search"); Param_Info(title_search?"enable":"disable");
        Skip_BS(13,                                             "reserved");
        BS_End();
        Get_B2 (number_of_navigation_commands,                  "number_of_navigation_commands");
        for (int16u Pos=0; Pos<number_of_navigation_commands; Pos++)
        {
            Element_Begin("navigation_command");
            Skip_B4(                                            "opcode");
            Skip_B4(                                            "destination");
            Skip_B4(                                            "source");
            Element_End();
        }
        Element_End();
    }
}

//---------------------------------------------------------------------------
void File_Bdmv::Mobj_ExtensionData()
{
}

//---------------------------------------------------------------------------
void File_Bdmv::Mpls_AppInfoPlayList()
{
    //Parsing
    Skip_B1(                                                    "unknown");
    BS_Begin();
    Skip_S1(6,                                                  "unknown");
    Info_S2(2, playback_type,                                   "playback_type"); Param_Info(Mpls_playback_type[playback_type]);
    BS_End();
    Skip_B2(                                                    "playback_count");
    Skip_B4(                                                    "user_operation_mask_code 1");
    Skip_B4(                                                    "user_operation_mask_code 2");
    BS_Begin();
    Skip_SB(                                                    "random access");
    Skip_SB(                                                    "audio mix");
    Skip_SB(                                                    "bypass mixer");
    Skip_S2(13,                                                 "reserved");
    BS_End();
}

//---------------------------------------------------------------------------
void File_Bdmv::Mpls_PlayList()
{
    //Parsing
    int64u PlayItems_Duration=0;
    int16u number_of_PlayItems, number_of_SubPaths;
    Skip_B2(                                                    "reserved");
    Get_B2 (number_of_PlayItems,                                "number_of_PlayItems");
    Get_B2 (number_of_SubPaths,                                 "number_of_SubPaths");
    for (int16u Pos=0; Pos<number_of_PlayItems; Pos++)
    {
        Element_Begin("PlayItem");
        Ztring file;
        int16u length;
        Get_B2 (length,                                         "length");
        int64u End=Element_Offset+length;
        Get_Local (5, file,                                     "file"); Element_Info(file);
        Skip_Local(4,                                           "type");
        Skip_B1(                                                "unknown");
        BS_Begin();
            Skip_S1(3,                                          "unknown");
            Skip_SB(                                            "Angle?");
            Skip_S1(4,                                          "Condition");
        BS_End();
        Skip_B1(                                                "Unknown");
        Info_B4(Time_In,                                        "Time (In)"); Param_Info((float32)Time_In/45000);
        Info_B4(Time_Out,                                       "Time (Out)"); Param_Info((float32)Time_Out/45000);
        Skip_B4(                                                "UO1");
        Skip_B4(                                                "UO2");
        Skip_B4(                                                "An?");

        Element_Begin("STN"); {
        int16u length;
        Get_B2 (length,                                         "length");
        int64u End=Element_Offset+length;
        Skip_B2(                                                "unknown");
        Skip_B1(                                                "Vi");
        Skip_B1(                                                "Au");
        Skip_B1(                                                "PG");
        Skip_B1(                                                "IG");
        Skip_B1(                                                "sV");
        Skip_B1(                                                "sA");
        Skip_B1(                                                "PIP");
        Skip_B1(                                                "unknown");
        Skip_B1(                                                "unknown");
        Skip_B1(                                                "unknown");
        Skip_B1(                                                "unknown");
        Skip_B1(                                                "unknown");

        while (Element_Offset+16<=End)
        {
            Element_Begin();
            Ztring language;
            int16u mPID;
            int8u length;
            Skip_B1(                                            "type");
            Skip_B1(                                            "unknown");
            Get_B2 (mPID,                                       "mPID"); Element_Name(Ztring::ToZtring(mPID, 16));
            Skip_B2(                                            "SPid");
            Skip_B2(                                            "sCid");
            Skip_B2(                                            "sPID");
            Get_B1 (length,                                     "length");
            int64u End=Element_Offset+length;
            Get_B1 (stream_type,                                "stream_type"); Param_Info(Clpi_Format(stream_type)); Element_Info(Clpi_Format(stream_type));
            switch (Clpi_Type(stream_type))
            {
                case Stream_Video : Mpls_PlayList_PlayItem_STN_Video(); break;
                case Stream_Audio : Mpls_PlayList_PlayItem_STN_Audio(); break;
                case Stream_Text  : Mpls_PlayList_PlayItem_STN_Text() ; break;
                default           : StreamKind_Last=Stream_Max;
            }
            Get_Local(3, language,                              "language"); Element_Info(language);

            if (End-Element_Offset)
                Skip_XX(End-Element_Offset,                     "unknown");
            Element_End();

            FILLING_BEGIN();
                if (StreamKind_Last!=Stream_Max)
                {
                    if (mPID)
                    {
                        Fill(StreamKind_Last, StreamPos_Last, "ID", mPID, 10, true);
                        Fill(StreamKind_Last, StreamPos_Last, "ID/String", Bdmv_Decimal_Hexa(mPID), true);
                    }
                    Fill(StreamKind_Last, StreamPos_Last, "Language", language);
                }
            FILLING_END();
        }
            
        if (End>Element_Offset)
            Skip_XX(End-Element_Offset,                         "unknown");
        Element_End(2+length); }

        if (End>Element_Offset)
            Skip_XX(End-Element_Offset,                         "unknown");
        Element_End(2+length);

        if (Time_Out>Time_In)
            PlayItems_Duration+=Time_Out-Time_In;
    }

    if (PlayItems_Duration)
        Fill(Stream_General, 0, General_Duration, PlayItems_Duration/45);

    for (int16u Pos=0; Pos<number_of_SubPaths; Pos++)
    {
        Element_Begin("SubPath");
        Ztring file;
        int32u length;
        int16u number_of_items;
        Get_B4 (length,                                         "length");
        int64u End=Element_Offset+length;
        Skip_B2(                                                "type?");
        Skip_B2(                                                "repeat");
        Get_B2 (number_of_items,                                "number_of_items");
        for (int16u Pos=0; Pos<number_of_SubPaths; Pos++)
        {
            Element_Begin("Item");
            Ztring file;
            int16u length;
            Get_B2 (length,                                     "length");
            int64u End=Element_Offset+length;
            Get_Local (5, file,                                 "file"); Element_Info(file);
            Skip_Local(4,                                       "type");
            Skip_B1(                                            "unknown");
            Skip_B2(                                            "unknown");
            Skip_B2(                                            "unknown");
            Info_B4(Time_In,                                    "time (in)"); Param_Info((float32)Time_In/45000);
            Info_B4(Time_Out,                                   "time (out)"); Param_Info((float32)Time_Out/45000);
            Skip_B1(                                            "sync PI");
            Skip_B4(                                            "sync PTS");
            Skip_B1(                                            "An?");

            if (End>Element_Offset)
                Skip_XX(End-Element_Offset,                     "unknown");
            Element_End(2+length);
        }

        if (End>Element_Offset)
            Skip_XX(End-Element_Offset,                         "unknown");
        Element_End(2+length);
    }
}

//---------------------------------------------------------------------------
void File_Bdmv::Mpls_PlayList_PlayItem_STN_Video()
{
    //Parsing
    int8u Format, FrameRate;
    BS_Begin();
    Get_S1 (4, Format,                                          "format"); Param_Info(Clpi_Video_Format[Format]);
    Get_S1 (4, FrameRate,                                       "frame_rate"); Param_Info(Clpi_Video_FrameRate[FrameRate]);
    BS_End();

    FILLING_BEGIN();
        Stream_Prepare(Stream_Video);
        Fill(Stream_Video, StreamPos_Last, Video_Format, Clpi_Format(stream_type));
        if (Clpi_Video_Width[Format])
            Fill(Stream_Video, StreamPos_Last, Video_Width, Clpi_Video_Width[Format]);
        if (Clpi_Video_Height[Format])
            Fill(Stream_Video, StreamPos_Last, Video_Height, Clpi_Video_Height[Format]);
        Fill(Stream_Video, StreamPos_Last, Video_Interlacement, Clpi_Video_Interlacement[stream_type]);
        Fill(Stream_Video, StreamPos_Last, Video_Standard, Clpi_Video_Standard[Format]);
        if (Clpi_Video_FrameRate[FrameRate])
            Fill(Stream_Video, StreamPos_Last, Video_FrameRate, Clpi_Video_FrameRate[FrameRate]);
    FILLING_END();
}

//---------------------------------------------------------------------------
void File_Bdmv::Mpls_PlayList_PlayItem_STN_Audio()
{
    //Parsing
    int8u Channels, SamplingRate;
    BS_Begin();
    Get_S1 (4, Channels,                                        "channel_layout"); Param_Info(Clpi_Audio_Channels[Channels]);
    Get_S1 (4, SamplingRate,                                    "sampling_rate"); Param_Info(Clpi_Audio_SamplingRate[SamplingRate]);
    BS_End();

    FILLING_BEGIN();
        Stream_Prepare(Stream_Audio);
        Fill(Stream_Audio, StreamPos_Last, Audio_Format, Clpi_Format(stream_type));
        Fill(Stream_Audio, StreamPos_Last, Audio_Format_Profile, Clpi_Format_Profile(stream_type));
        if (Clpi_Audio_Channels[Channels])
            Fill(Stream_Audio, StreamPos_Last, Audio_Channel_s_, Clpi_Audio_Channels[Channels]);
        if (Clpi_Audio_SamplingRate[SamplingRate])
            Fill(Stream_Audio, StreamPos_Last, Audio_SamplingRate, Clpi_Audio_SamplingRate[SamplingRate]);
    FILLING_END();
}

//---------------------------------------------------------------------------
void File_Bdmv::Mpls_PlayList_PlayItem_STN_Text()
{
    //Parsing
    if (stream_type==0x92) //Subtitle
        Skip_B1(                                                "Unknown");

    FILLING_BEGIN();
        Stream_Prepare(Stream_Text);
        Fill(Stream_Text, StreamPos_Last, Text_Format, Clpi_Format(stream_type));
    FILLING_END();
}

//---------------------------------------------------------------------------
void File_Bdmv::Mpls_PlayListMarks()
{
    Stream_Prepare(Stream_Menu);
    Fill(Stream_Menu, StreamPos_Last, Menu_Chapters_Pos_Begin, Count_Get(Stream_Menu, StreamPos_Last), 10, true);

    //Parsing
    int32u time_Pos0;
    int16u count;
    Get_B2 (count,                                              "count");
    for (int16u Pos=0; Pos<count; Pos++)
    {
        Element_Begin("Mark");
        int8u type;
        Skip_B1(                                                "unknown");
        Get_B1 (type,                                           "type"); Param_Info(Mpls_PlayListMarks_Mark_type(type));
        switch (type)
        {
            case 1 : //entry-mark
            case 2 : //link point
                    {
                    int32u time;
                    int16u stream_file_index;
                    Get_B2 (stream_file_index,                  "stream_file_index");
                    Get_B4 (time,                               "time"); Param_Info(time/45, " milliseconds");
                    Skip_B2(                                    "unknown");
                    Skip_B4(                                    "unknown");

                    FILLING_BEGIN();
                        if (Pos==0)
                            time_Pos0=time;
                        if (stream_file_index==0 && type==1) //We currently handle only the first file
                            Fill(Stream_Menu, 0, Ztring().Duration_From_Milliseconds((time-time_Pos0)/45).To_UTF8().c_str(), _T("Chapter ")+Ztring::ToZtring(Pos+1));
                    FILLING_END();
                    }
                    break;
            default:
                    Skip_XX(12,                                 "unknwon");
        }
        Element_End();
    }

    Fill(Stream_Menu, StreamPos_Last, Menu_Chapters_Pos_End, Count_Get(Stream_Menu, StreamPos_Last), 10, true);
}

} //NameSpace

#endif //MEDIAINFO_BDMV_YES