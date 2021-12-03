#pragma once

#include <string_view>
#include <array>
#include <algorithm>

#include "Common.h"

using std::string_view;

struct LanguageDescriptor
{
    vector<string_view> language_names;
    vector<string_view> tags;
};

namespace MatroskaLanguageTags
{
    static const string_view UNKNOWN_LANGUGAGE = "UNKNOWN";
    static const std::array<LanguageDescriptor, 480> language_tags{{
        {{"Afar"}, {"aar", "aa"}},
        {{"Abkhazian"}, {"abk", "ab"}},
        {{"Achinese"}, {"ace"}},
        {{"Acoli"}, {"ach"}},
        {{"Adangme"}, {"ada"}},
        {{"Adyghe", "Adygei"}, {"ady"}},
        {{"Afro-Asiatic Languages"}, {"afa"}},
        {{"Afrihili"}, {"afh"}},
        {{"Afrikaans"}, {"afr", "af"}},
        {{"Ainu"}, {"ain"}},
        {{"Akan"}, {"ak", "aka"}},
        {{"Akkadian"}, {"akk"}},
        {{"Albanian"}, {"alb", "sqi", "sq"}},
        {{"Aleut"}, {"ale"}},
        {{"Algonquian Languages"}, {"alg"}},
        {{"Southern Altai"}, {"alt"}},
        {{"Amharic"}, {"amh", "am"}},
        {{"English Old (ca.450-1100)"}, {"ang"}},
        {{"Angika"}, {"anp"}},
        {{"Apache Languages"}, {"apa"}},
        {{"Arabic"}, {"ara", "ar"}},
        {{"Imperial Aramaic (700-300 BCE)", "Official Aramaic (700-300 BCE)"}, {"arc"}},
        {{"Aragonese"}, {"an", "arg"}},
        {{"Armenian"}, {"hye", "arm", "hy"}},
        {{"Mapudungun", "Mapuche"}, {"arn"}},
        {{"Arapaho"}, {"arp"}},
        {{"Artificial Languages"}, {"art"}},
        {{"Arawak"}, {"arw"}},
        {{"Assamese"}, {"asm", "as"}},
        {{"Asturleonese", "Leonese", "Asturian", "Bable"}, {"ast"}},
        {{"Athapascan Languages"}, {"ath"}},
        {{"Australian Languages"}, {"aus"}},
        {{"Avaric"}, {"av", "ava"}},
        {{"Avestan"}, {"ave", "ae"}},
        {{"Awadhi"}, {"awa"}},
        {{"Aymara"}, {"aym", "ay"}},
        {{"Azerbaijani"}, {"az", "aze"}},
        {{"Banda Languages"}, {"bad"}},
        {{"Bamileke Languages"}, {"bai"}},
        {{"Bashkir"}, {"bak", "ba"}},
        {{"Baluchi"}, {"bal"}},
        {{"Bambara"}, {"bm", "bam"}},
        {{"Balinese"}, {"ban"}},
        {{"Basque"}, {"baq", "eu", "eus"}},
        {{"Basa"}, {"bas"}},
        {{"Baltic Languages"}, {"bat"}},
        {{"Beja", "Bedawiyet"}, {"bej"}},
        {{"Belarusian"}, {"bel", "be"}},
        {{"Bemba"}, {"bem"}},
        {{"Bengali"}, {"bn", "ben"}},
        {{"Berber Languages"}, {"ber"}},
        {{"Bhojpuri"}, {"bho"}},
        {{"Bihari Languages"}, {"bh", "bih"}},
        {{"Bikol"}, {"bik"}},
        {{"Bini", "Edo"}, {"bin"}},
        {{"Bislama"}, {"bi", "bis"}},
        {{"Siksika"}, {"bla"}},
        {{"Bantu (Other)"}, {"bnt"}},
        {{"Bosnian"}, {"bos", "bs"}},
        {{"Braj"}, {"bra"}},
        {{"Breton"}, {"bre", "br"}},
        {{"Batak Languages"}, {"btk"}},
        {{"Buriat"}, {"bua"}},
        {{"Buginese"}, {"bug"}},
        {{"Bulgarian"}, {"bul", "bg"}},
        {{"Burmese"}, {"my", "bur", "mya"}},
        {{"Blin", "Bilin"}, {"byn"}},
        {{"Caddo"}, {"cad"}},
        {{"Central American Indian Languages"}, {"cai"}},
        {{"Galibi Carib"}, {"car"}},
        {{"Valencian", "Catalan"}, {"cat", "ca"}},
        {{"Caucasian Languages"}, {"cau"}},
        {{"Cebuano"}, {"ceb"}},
        {{"Celtic Languages"}, {"cel"}},
        {{"Chamorro"}, {"cha", "ch"}},
        {{"Chibcha"}, {"chb"}},
        {{"Chechen"}, {"ce", "che"}},
        {{"Chagatai"}, {"chg"}},
        {{"Chinese"}, {"chi", "zho", "zh"}},
        {{"Chuukese"}, {"chk"}},
        {{"Mari"}, {"chm"}},
        {{"Chinook Jargon"}, {"chn"}},
        {{"Choctaw"}, {"cho"}},
        {{"Dene Suline", "Chipewyan"}, {"chp"}},
        {{"Cherokee"}, {"chr"}},
        {{"Church Slavonic", "Church Slavic", "Old Church Slavonic", "Old Bulgarian", "Old Slavonic"}, {"cu", "chu"}},
        {{"Chuvash"}, {"chv", "cv"}},
        {{"Cheyenne"}, {"chy"}},
        {{"Chamic Languages"}, {"cmc"}},
        {{"Coptic"}, {"cop"}},
        {{"Cornish"}, {"kw", "cor"}},
        {{"Corsican"}, {"co", "cos"}},
        {{"Portuguese-based", "French-based", "Creoles And Pidgins", "English Based"}, {"cpe", "cpp", "cpf", "crp"}},
        {{"Cree"}, {"cre", "cr"}},
        {{"Crimean Tatar", "Crimean Turkish"}, {"crh"}},
        {{"Kashubian"}, {"csb"}},
        {{"Cushitic Languages"}, {"cus"}},
        {{"Czech"}, {"ces", "cze", "cs"}},
        {{"Dakota"}, {"dak"}},
        {{"Danish"}, {"da", "dan"}},
        {{"Dargwa"}, {"dar"}},
        {{"Land Dayak Languages"}, {"day"}},
        {{"Delaware"}, {"del"}},
        {{"Slave (Athapascan)"}, {"den"}},
        {{"Dogrib"}, {"dgr"}},
        {{"Dinka"}, {"din"}},
        {{"Dhivehi", "Maldivian", "Divehi"}, {"div", "dv"}},
        {{"Dogri"}, {"doi"}},
        {{"Dravidian Languages"}, {"dra"}},
        {{"Lower Sorbian"}, {"dsb"}},
        {{"Duala"}, {"dua"}},
        {{"Dutch Middle (ca.1050-1350)"}, {"dum"}},
        {{"Dutch", "Flemish"}, {"nl", "dut", "nld"}},
        {{"Dyula"}, {"dyu"}},
        {{"Dzongkha"}, {"dzo", "dz"}},
        {{"Efik"}, {"efi"}},
        {{"Egyptian (Ancient)"}, {"egy"}},
        {{"Ekajuk"}, {"eka"}},
        {{"Elamite"}, {"elx"}},
        {{"English"}, {"eng", "en"}},
        {{"English Middle (1100-1500)"}, {"enm"}},
        {{"Esperanto"}, {"epo", "eo"}},
        {{"Estonian"}, {"et", "est"}},
        {{"Ewe"}, {"ewe", "ee"}},
        {{"Ewondo"}, {"ewo"}},
        {{"Fang"}, {"fan"}},
        {{"Faroese"}, {"fao", "fo"}},
        {{"Fanti"}, {"fat"}},
        {{"Fijian"}, {"fij", "fj"}},
        {{"Pilipino", "Filipino"}, {"fil"}},
        {{"Finnish"}, {"fin", "fi"}},
        {{"Finno-Ugrian Languages"}, {"fiu"}},
        {{"Fon"}, {"fon"}},
        {{"French"}, {"fra", "fr", "fre"}},
        {{"French Middle (ca.1400-1600)"}, {"frm"}},
        {{"French Old (842-ca.1400)"}, {"fro"}},
        {{"Northern Frisian"}, {"frr"}},
        {{"Eastern Frisian"}, {"frs"}},
        {{"Western Frisian"}, {"fry", "fy"}},
        {{"Fulah"}, {"ful", "ff"}},
        {{"Friulian"}, {"fur"}},
        {{"Ga"}, {"gaa"}},
        {{"Gayo"}, {"gay"}},
        {{"Gbaya"}, {"gba"}},
        {{"Germanic Languages"}, {"gem"}},
        {{"Georgian"}, {"ka", "kat", "geo"}},
        {{"German"}, {"ger", "deu", "de"}},
        {{"Geez"}, {"gez"}},
        {{"Gilbertese"}, {"gil"}},
        {{"Gaelic", "Scottish Gaelic"}, {"gd", "gla"}},
        {{"Irish"}, {"gle", "ga"}},
        {{"Galician"}, {"glg", "gl"}},
        {{"Manx"}, {"glv", "gv"}},
        {{"German Middle High (ca.1050-1500)"}, {"gmh"}},
        {{"German Old High (ca.750-1050)"}, {"goh"}},
        {{"Gondi"}, {"gon"}},
        {{"Gorontalo"}, {"gor"}},
        {{"Gothic"}, {"got"}},
        {{"Grebo"}, {"grb"}},
        {{"Greek Ancient (to 1453)"}, {"grc"}},
        {{"Greek Modern (1453-)"}, {"el", "gre", "ell"}},
        {{"Guarani"}, {"gn", "grn"}},
        {{"Alemannic", "Swiss German", "Alsatian"}, {"gsw"}},
        {{"Gujarati"}, {"gu", "guj"}},
        {{"Gwich'in"}, {"gwi"}},
        {{"Haida"}, {"hai"}},
        {{"Haitian", "Haitian Creole"}, {"ht", "hat"}},
        {{"Hausa"}, {"ha", "hau"}},
        {{"Hawaiian"}, {"haw"}},
        {{"Hebrew"}, {"heb", "he"}},
        {{"Herero"}, {"her", "hz"}},
        {{"Hiligaynon"}, {"hil"}},
        {{"Himachali Languages", "Western Pahari Languages"}, {"him"}},
        {{"Hindi"}, {"hi", "hin"}},
        {{"Hittite"}, {"hit"}},
        {{"Hmong", "Mong"}, {"hmn"}},
        {{"Hiri Motu"}, {"hmo", "ho"}},
        {{"Croatian"}, {"hrv", "hr"}},
        {{"Upper Sorbian"}, {"hsb"}},
        {{"Hungarian"}, {"hun", "hu"}},
        {{"Hupa"}, {"hup"}},
        {{"Iban"}, {"iba"}},
        {{"Igbo"}, {"ibo", "ig"}},
        {{"Icelandic"}, {"is", "isl", "ice"}},
        {{"Ido"}, {"ido", "io"}},
        {{"Sichuan Yi", "Nuosu"}, {"iii", "ii"}},
        {{"Ijo Languages"}, {"ijo"}},
        {{"Inuktitut"}, {"iu", "iku"}},
        {{"Interlingue", "Occidental"}, {"ile", "ie"}},
        {{"Iloko"}, {"ilo"}},
        {{"Interlingua (International Auxiliary Language Association)"}, {"ia", "ina"}},
        {{"Indic Languages"}, {"inc"}},
        {{"Indonesian"}, {"ind", "id"}},
        {{"Indo-European Languages"}, {"ine"}},
        {{"Ingush"}, {"inh"}},
        {{"Inupiaq"}, {"ipk", "ik"}},
        {{"Iranian Languages"}, {"ira"}},
        {{"Iroquoian Languages"}, {"iro"}},
        {{"Italian"}, {"ita", "it"}},
        {{"Javanese"}, {"jav", "jv"}},
        {{"Lojban"}, {"jbo"}},
        {{"Japanese"}, {"ja", "jpn"}},
        {{"Judeo-Persian"}, {"jpr"}},
        {{"Judeo-Arabic"}, {"jrb"}},
        {{"Kara-Kalpak"}, {"kaa"}},
        {{"Kabyle"}, {"kab"}},
        {{"Jingpho", "Kachin"}, {"kac"}},
        {{"Greenlandic", "Kalaallisut"}, {"kl", "kal"}},
        {{"Kamba"}, {"kam"}},
        {{"Kannada"}, {"kn", "kan"}},
        {{"Karen Languages"}, {"kar"}},
        {{"Kashmiri"}, {"ks", "kas"}},
        {{"Kanuri"}, {"kr", "kau"}},
        {{"Kawi"}, {"kaw"}},
        {{"Kazakh"}, {"kk", "kaz"}},
        {{"Kabardian"}, {"kbd"}},
        {{"Khasi"}, {"kha"}},
        {{"Khoisan Languages"}, {"khi"}},
        {{"Central Khmer"}, {"khm", "km"}},
        {{"Sakan", "Khotanese"}, {"kho"}},
        {{"Kikuyu", "Gikuyu"}, {"ki", "kik"}},
        {{"Kinyarwanda"}, {"kin", "rw"}},
        {{"Kyrgyz", "Kirghiz"}, {"ky", "kir"}},
        {{"Kimbundu"}, {"kmb"}},
        {{"Konkani"}, {"kok"}},
        {{"Komi"}, {"kom", "kv"}},
        {{"Kongo"}, {"kg", "kon"}},
        {{"Korean"}, {"kor", "ko"}},
        {{"Kosraean"}, {"kos"}},
        {{"Kpelle"}, {"kpe"}},
        {{"Karachay-Balkar"}, {"krc"}},
        {{"Karelian"}, {"krl"}},
        {{"Kru Languages"}, {"kro"}},
        {{"Kurukh"}, {"kru"}},
        {{"Kuanyama", "Kwanyama"}, {"kj", "kua"}},
        {{"Kumyk"}, {"kum"}},
        {{"Kurdish"}, {"kur", "ku"}},
        {{"Kutenai"}, {"kut"}},
        {{"Ladino"}, {"lad"}},
        {{"Lahnda"}, {"lah"}},
        {{"Lamba"}, {"lam"}},
        {{"Lao"}, {"lo", "lao"}},
        {{"Latin"}, {"lat", "la"}},
        {{"Latvian"}, {"lv", "lav"}},
        {{"Lezghian"}, {"lez"}},
        {{"Limburgan", "Limburger", "Limburgish"}, {"li", "lim"}},
        {{"Lingala"}, {"ln", "lin"}},
        {{"Lithuanian"}, {"lit", "lt"}},
        {{"Mongo"}, {"lol"}},
        {{"Lozi"}, {"loz"}},
        {{"Letzeburgesch", "Luxembourgish"}, {"lb", "ltz"}},
        {{"Luba-Lulua"}, {"lua"}},
        {{"Luba-Katanga"}, {"lub", "lu"}},
        {{"Ganda"}, {"lug", "lg"}},
        {{"Luiseno"}, {"lui"}},
        {{"Lunda"}, {"lun"}},
        {{"Luo (Kenya And Tanzania)"}, {"luo"}},
        {{"Lushai"}, {"lus"}},
        {{"Macedonian"}, {"mk", "mkd", "mac"}},
        {{"Madurese"}, {"mad"}},
        {{"Magahi"}, {"mag"}},
        {{"Marshallese"}, {"mah", "mh"}},
        {{"Maithili"}, {"mai"}},
        {{"Makasar"}, {"mak"}},
        {{"Malayalam"}, {"ml", "mal"}},
        {{"Mandingo"}, {"man"}},
        {{"Maori"}, {"mi", "mao", "mri"}},
        {{"Austronesian Languages"}, {"map"}},
        {{"Marathi"}, {"mr", "mar"}},
        {{"Masai"}, {"mas"}},
        {{"Malay"}, {"may", "ms", "msa"}},
        {{"Moksha"}, {"mdf"}},
        {{"Mandar"}, {"mdr"}},
        {{"Mende"}, {"men"}},
        {{"Irish Middle (900-1200)"}, {"mga"}},
        {{"Mi'kmaq", "Micmac"}, {"mic"}},
        {{"Minangkabau"}, {"min"}},
        {{"Uncoded Languages"}, {"mis"}},
        {{"Mon-Khmer Languages"}, {"mkh"}},
        {{"Malagasy"}, {"mlg", "mg"}},
        {{"Maltese"}, {"mlt", "mt"}},
        {{"Manchu"}, {"mnc"}},
        {{"Manipuri"}, {"mni"}},
        {{"Manobo Languages"}, {"mno"}},
        {{"Mohawk"}, {"moh"}},
        {{"Mongolian"}, {"mon", "mn"}},
        {{"Mossi"}, {"mos"}},
        {{"Multiple Languages"}, {"mul"}},
        {{"Munda Languages"}, {"mun"}},
        {{"Creek"}, {"mus"}},
        {{"Mirandese"}, {"mwl"}},
        {{"Marwari"}, {"mwr"}},
        {{"Mayan Languages"}, {"myn"}},
        {{"Erzya"}, {"myv"}},
        {{"Nahuatl Languages"}, {"nah"}},
        {{"North American Indian Languages"}, {"nai"}},
        {{"Neapolitan"}, {"nap"}},
        {{"Nauru"}, {"nau", "na"}},
        {{"Navaho", "Navajo"}, {"nv", "nav"}},
        {{"South", "North", "Ndebele"}, {"nbl", "nr", "nd", "nde"}},
        {{"Ndonga"}, {"ng", "ndo"}},
        {{"Low", "Saxon"}, {"nds"}},
        {{"Nepali"}, {"ne", "nep"}},
        {{"Nepal Bhasa", "Newari"}, {"new"}},
        {{"Nias"}, {"nia"}},
        {{"Niger-Kordofanian Languages"}, {"nic"}},
        {{"Niuean"}, {"niu"}},
        {{"Nynorsk", "Norwegian", "Bokm�l"}, {"nno", "nb", "nor", "no", "nob", "nn"}},
        {{"Nogai"}, {"nog"}},
        {{"Norse", "Old"}, {"non"}},
        {{"N�Ko", "N'Ko"}, {"nqo"}},
        {{"Sepedi", "Northern Sotho", "Pedi"}, {"nso"}},
        {{"Nubian Languages"}, {"nub"}},
        {{"Classical Nepal Bhasa", "Old Newari", "Classical Newari"}, {"nwc"}},
        {{"Nyanja", "Chewa", "Chichewa"}, {"nya", "ny"}},
        {{"Nyamwezi"}, {"nym"}},
        {{"Nyankole"}, {"nyn"}},
        {{"Nyoro"}, {"nyo"}},
        {{"Nzima"}, {"nzi"}},
        {{"Proven�al", "Occitan (post 1500)"}, {"oc", "oci"}},
        {{"Ojibwa"}, {"oji", "oj"}},
        {{"Oriya"}, {"ori", "or"}},
        {{"Oromo"}, {"orm", "om"}},
        {{"Osage"}, {"osa"}},
        {{"Ossetic", "Ossetian"}, {"os", "oss"}},
        {{"Turkish Ottoman (1500-1928)"}, {"ota"}},
        {{"Otomian Languages"}, {"oto"}},
        {{"Papuan Languages"}, {"paa"}},
        {{"Pangasinan"}, {"pag"}},
        {{"Pahlavi"}, {"pal"}},
        {{"Kapampangan", "Pampanga"}, {"pam"}},
        {{"Punjabi", "Panjabi"}, {"pa", "pan"}},
        {{"Papiamento"}, {"pap"}},
        {{"Palauan"}, {"pau"}},
        {{"Persian Old (ca.600-400 B.C.)"}, {"peo"}},
        {{"Persian"}, {"fa", "per", "fas"}},
        {{"Philippine Languages"}, {"phi"}},
        {{"Phoenician"}, {"phn"}},
        {{"Pali"}, {"pli", "pi"}},
        {{"Polish"}, {"pl", "pol"}},
        {{"Pohnpeian"}, {"pon"}},
        {{"Portuguese"}, {"por", "pt"}},
        {{"Prakrit Languages"}, {"pra"}},
        {{"Proven�al Old (to 1500)"}, {"pro"}},
        {{"Pashto", "Pushto"}, {"ps", "pus"}},
        {{"Reserved For Local Use"}, {"qaa-qtz"}},
        {{"Quechua"}, {"qu", "que"}},
        {{"Rajasthani"}, {"raj"}},
        {{"Rapanui"}, {"rap"}},
        {{"Cook Islands Maori", "Rarotongan"}, {"rar"}},
        {{"Romance Languages"}, {"roa"}},
        {{"Romansh"}, {"roh", "rm"}},
        {{"Romany"}, {"rom"}},
        {{"Moldovan", "Romanian", "Moldavian"}, {"ro", "ron", "rum"}},
        {{"Rundi"}, {"run", "rn"}},
        {{"Aromanian", "Arumanian", "Macedo-Romanian"}, {"rup"}},
        {{"Russian"}, {"rus", "ru"}},
        {{"Sandawe"}, {"sad"}},
        {{"Sango"}, {"sg", "sag"}},
        {{"Yakut"}, {"sah"}},
        {{"South American Indian (Other)"}, {"sai"}},
        {{"Salishan Languages"}, {"sal"}},
        {{"Samaritan Aramaic"}, {"sam"}},
        {{"Sanskrit"}, {"san", "sa"}},
        {{"Sasak"}, {"sas"}},
        {{"Santali"}, {"sat"}},
        {{"Sicilian"}, {"scn"}},
        {{"Scots"}, {"sco"}},
        {{"Selkup"}, {"sel"}},
        {{"Semitic Languages"}, {"sem"}},
        {{"Irish Old (to 900)"}, {"sga"}},
        {{"Sign Languages"}, {"sgn"}},
        {{"Shan"}, {"shn"}},
        {{"Sidamo"}, {"sid"}},
        {{"Sinhala", "Sinhalese"}, {"si", "sin"}},
        {{"Siouan Languages"}, {"sio"}},
        {{"Sino-Tibetan Languages"}, {"sit"}},
        {{"Slavic Languages"}, {"sla"}},
        {{"Slovak"}, {"slk", "sk", "slo"}},
        {{"Slovenian"}, {"sl", "slv"}},
        {{"Southern Sami"}, {"sma"}},
        {{"Northern Sami"}, {"sme", "se"}},
        {{"Sami Languages"}, {"smi"}},
        {{"Lule Sami"}, {"smj"}},
        {{"Inari Sami"}, {"smn"}},
        {{"Samoan"}, {"sm", "smo"}},
        {{"Skolt Sami"}, {"sms"}},
        {{"Shona"}, {"sna", "sn"}},
        {{"Sindhi"}, {"sd", "snd"}},
        {{"Soninke"}, {"snk"}},
        {{"Sogdian"}, {"sog"}},
        {{"Somali"}, {"so", "som"}},
        {{"Songhai Languages"}, {"son"}},
        {{"Sotho", "Southern"}, {"sot", "st"}},
        {{"Castilian", "Spanish"}, {"spa", "es"}},
        {{"Sardinian"}, {"sc", "srd"}},
        {{"Sranan Tongo"}, {"srn"}},
        {{"Serbian"}, {"sr", "srp"}},
        {{"Serer"}, {"srr"}},
        {{"Nilo-Saharan Languages"}, {"ssa"}},
        {{"Swati"}, {"ss", "ssw"}},
        {{"Sukuma"}, {"suk"}},
        {{"Sundanese"}, {"su", "sun"}},
        {{"Susu"}, {"sus"}},
        {{"Sumerian"}, {"sux"}},
        {{"Swahili"}, {"swa", "sw"}},
        {{"Swedish"}, {"swe", "sv"}},
        {{"Classical Syriac"}, {"syc"}},
        {{"Syriac"}, {"syr"}},
        {{"Tahitian"}, {"tah", "ty"}},
        {{"Tai Languages"}, {"tai"}},
        {{"Tamil"}, {"ta", "tam"}},
        {{"Tatar"}, {"tt", "tat"}},
        {{"Telugu"}, {"tel", "te"}},
        {{"Timne"}, {"tem"}},
        {{"Tereno"}, {"ter"}},
        {{"Tetum"}, {"tet"}},
        {{"Tajik"}, {"tg", "tgk"}},
        {{"Tagalog"}, {"tl", "tgl"}},
        {{"Thai"}, {"tha", "th"}},
        {{"Tibetan"}, {"bod", "tib", "bo"}},
        {{"Tigre"}, {"tig"}},
        {{"Tigrinya"}, {"tir", "ti"}},
        {{"Tiv"}, {"tiv"}},
        {{"Tokelau"}, {"tkl"}},
        {{"tlhIngan-Hol", "TlhIngan-Hol", "Klingon"}, {"tlh"}},
        {{"Tlingit"}, {"tli"}},
        {{"Tamashek"}, {"tmh"}},
        {{"Tonga (Nyasa)"}, {"tog"}},
        {{"Tonga (Tonga Islands)"}, {"to", "ton"}},
        {{"Tok Pisin"}, {"tpi"}},
        {{"Tsimshian"}, {"tsi"}},
        {{"Tswana"}, {"tsn", "tn"}},
        {{"Tsonga"}, {"tso", "ts"}},
        {{"Turkmen"}, {"tk", "tuk"}},
        {{"Tumbuka"}, {"tum"}},
        {{"Tupi Languages"}, {"tup"}},
        {{"Turkish"}, {"tr", "tur"}},
        {{"Altaic Languages"}, {"tut"}},
        {{"Tuvalu"}, {"tvl"}},
        {{"Twi"}, {"tw", "twi"}},
        {{"Tuvinian"}, {"tyv"}},
        {{"Udmurt"}, {"udm"}},
        {{"Ugaritic"}, {"uga"}},
        {{"Uighur", "Uyghur"}, {"uig", "ug"}},
        {{"Ukrainian"}, {"uk", "ukr"}},
        {{"Umbundu"}, {"umb"}},
        {{"Undetermined"}, {"und"}},
        {{"Urdu"}, {"urd", "ur"}},
        {{"Uzbek"}, {"uzb", "uz"}},
        {{"Vai"}, {"vai"}},
        {{"Venda"}, {"ven", "ve"}},
        {{"Vietnamese"}, {"vie", "vi"}},
        {{"Volap�k"}, {"vo", "vol"}},
        {{"Votic"}, {"vot"}},
        {{"Wakashan Languages"}, {"wak"}},
        {{"Walamo"}, {"wal"}},
        {{"Waray"}, {"war"}},
        {{"Washo"}, {"was"}},
        {{"Welsh"}, {"cym", "wel", "cy"}},
        {{"Sorbian Languages"}, {"wen"}},
        {{"Walloon"}, {"wa", "wln"}},
        {{"Wolof"}, {"wol", "wo"}},
        {{"Kalmyk", "Oirat"}, {"xal"}},
        {{"Xhosa"}, {"xh", "xho"}},
        {{"Yao"}, {"yao"}},
        {{"Yapese"}, {"yap"}},
        {{"Yiddish"}, {"yid", "yi"}},
        {{"Yoruba"}, {"yo", "yor"}},
        {{"Yupik Languages"}, {"ypk"}},
        {{"Zapotec"}, {"zap"}},
        {{"Blissymbols", "Bliss", "Blissymbolics"}, {"zbl"}},
        {{"Zenaga"}, {"zen"}},
        {{"Standard Moroccan Tamazight"}, {"zgh"}},
        {{"Zhuang", "Chuang"}, {"zha", "za"}},
        {{"Zande Languages"}, {"znd"}},
        {{"Zulu"}, {"zu", "zul"}},
        {{"Zuni"}, {"zun"}},
        {{"No Linguistic Content", "Not Applicable"}, {"zxx"}},
        {{"Dimili", "Kirmanjki", "Dimli", "Kirdki", "Kirmanjki (macrolanguage)", "Zaza", "Zazaki", "Dimli (macrolanguage)"}, {"zza"}}
    }};
    
    bool does_tag_match_language(string language, string tag);
    const string_view& get_tag_language(string tag);
}