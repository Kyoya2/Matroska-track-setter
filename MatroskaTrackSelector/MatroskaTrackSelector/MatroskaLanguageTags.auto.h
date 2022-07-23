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

#include <array>
#include <algorithm>

#include "Common.h"

struct LanguageDescriptor
{
    vector<string_view> language_names;
    vector<string_view> tags;
};

namespace MatroskaLanguageTags
{
    static string UNKNOWN_LANGUGAGE = "UNKNOWN";
    static const std::array<LanguageDescriptor, 487> language_tags{{
        {{"Abkhazian"}, {"abk", "ab"}},
        {{"Achinese"}, {"ace"}},
        {{"Acoli"}, {"ach"}},
        {{"Adangme"}, {"ada"}},
        {{"Adygei", "Adyghe"}, {"ady"}},
        {{"Afar"}, {"aar", "aa"}},
        {{"Afrihili"}, {"afh"}},
        {{"Afrikaans"}, {"afr", "af"}},
        {{"Afro-Asiatic languages"}, {"afa"}},
        {{"Ainu"}, {"ain"}},
        {{"Akan"}, {"aka", "ak"}},
        {{"Akkadian"}, {"akk"}},
        {{"Albanian"}, {"sqi", "sq", "alb"}},
        {{"Aleut"}, {"ale"}},
        {{"Algonquian languages"}, {"alg"}},
        {{"Altaic languages"}, {"tut"}},
        {{"Amharic"}, {"amh", "am"}},
        {{"Angika"}, {"anp"}},
        {{"Apache languages"}, {"apa"}},
        {{"Arabic"}, {"ar", "ara"}},
        {{"Aragonese"}, {"an", "arg"}},
        {{"Arapaho"}, {"arp"}},
        {{"Arawak"}, {"arw"}},
        {{"Armenian"}, {"hye", "hy", "arm"}},
        {{"Artificial languages"}, {"art"}},
        {{"Assamese"}, {"asm", "as"}},
        {{"Asturleonese", "Asturian", "Bable", "Leonese"}, {"ast"}},
        {{"Athapascan languages"}, {"ath"}},
        {{"Australian languages"}, {"aus"}},
        {{"Austronesian languages"}, {"map"}},
        {{"Avaric"}, {"ava", "av"}},
        {{"Avestan"}, {"ave", "ae"}},
        {{"Awadhi"}, {"awa"}},
        {{"Aymara"}, {"ay", "aym"}},
        {{"Azerbaijani"}, {"az", "aze"}},
        {{"Balinese"}, {"ban"}},
        {{"Baltic languages"}, {"bat"}},
        {{"Baluchi"}, {"bal"}},
        {{"Bambara"}, {"bam", "bm"}},
        {{"Bamileke languages"}, {"bai"}},
        {{"Banda languages"}, {"bad"}},
        {{"Bantu languages"}, {"bnt"}},
        {{"Basa"}, {"bas"}},
        {{"Bashkir"}, {"ba", "bak"}},
        {{"Basque"}, {"eu", "baq", "eus"}},
        {{"Batak languages"}, {"btk"}},
        {{"Beja", "Bedawiyet"}, {"bej"}},
        {{"Belarusian"}, {"bel", "be"}},
        {{"Bemba"}, {"bem"}},
        {{"Bengali"}, {"ben"}},
        {{"Berber languages"}, {"ber"}},
        {{"Bhojpuri"}, {"bho"}},
        {{"Bihari languages"}, {"bh", "bih"}},
        {{"Bikol"}, {"bik"}},
        {{"Bislama"}, {"bi", "bis"}},
        {{"Blin", "Bilin"}, {"byn"}},
        {{"Blissymbolics", "Bliss", "Blissymbols"}, {"zbl"}},
        {{"Bosnian"}, {"bos", "bs"}},
        {{"Braj"}, {"bra"}},
        {{"Breton"}, {"br", "bre"}},
        {{"Buginese"}, {"bug"}},
        {{"Bulgarian"}, {"bg", "bul"}},
        {{"Buriat"}, {"bua"}},
        {{"Burmese"}, {"my", "bur", "mya"}},
        {{"Caddo"}, {"cad"}},
        {{"Caucasian languages"}, {"cau"}},
        {{"Cebuano"}, {"ceb"}},
        {{"Celtic languages"}, {"cel"}},
        {{"Central American Indian languages"}, {"cai"}},
        {{"Central Khmer"}, {"khm", "km"}},
        {{"Chagatai"}, {"chg"}},
        {{"Chamic languages"}, {"cmc"}},
        {{"Chamorro"}, {"ch", "cha"}},
        {{"Chechen"}, {"che", "ce"}},
        {{"Cherokee"}, {"chr"}},
        {{"Cheyenne"}, {"chy"}},
        {{"Chibcha"}, {"chb"}},
        {{"Chichewa", "Chewa", "Nyanja"}, {"ny", "nya"}},
        {{"Chinese"}, {"zho", "chi", "zh"}},
        {{"Chinook jargon"}, {"chn"}},
        {{"Chipewyan", "Dene Suline"}, {"chp"}},
        {{"Choctaw"}, {"cho"}},
        {{"Chuang", "Zhuang"}, {"zha", "za"}},
        {{"Chuukese"}, {"chk"}},
        {{"Chuvash"}, {"chv", "cv"}},
        {{"Classical Newari", "Old Newari", "Classical Nepal Bhasa"}, {"nwc"}},
        {{"Classical Syriac"}, {"syc"}},
        {{"Coptic"}, {"cop"}},
        {{"Cornish"}, {"kw", "cor"}},
        {{"Corsican"}, {"cos", "co"}},
        {{"Cree"}, {"cre", "cr"}},
        {{"Creek"}, {"mus"}},
        {{"Creoles and pidgins"}, {"crp"}},
        {{"Creoles and pidgins, English based"}, {"cpe"}},
        {{"Creoles and pidgins, French-based"}, {"cpf"}},
        {{"Creoles and pidgins, Portuguese-based"}, {"cpp"}},
        {{"Crimean Tatar", "Crimean Turkish"}, {"crh"}},
        {{"Croatian"}, {"hr", "hrv"}},
        {{"Cushitic languages"}, {"cus"}},
        {{"Czech"}, {"cze", "cs", "ces"}},
        {{"Dakota"}, {"dak"}},
        {{"Danish"}, {"da", "dan"}},
        {{"Dargwa"}, {"dar"}},
        {{"Delaware"}, {"del"}},
        {{"Dinka"}, {"din"}},
        {{"Divehi", "Maldivian", "Dhivehi"}, {"div", "dv"}},
        {{"Dogri"}, {"doi"}},
        {{"Dogrib"}, {"dgr"}},
        {{"Dravidian languages"}, {"dra"}},
        {{"Duala"}, {"dua"}},
        {{"Dutch", "Flemish"}, {"nld", "nl", "dut"}},
        {{"Dutch, Middle (ca.1050-1350)"}, {"dum"}},
        {{"Dyula"}, {"dyu"}},
        {{"Dzongkha"}, {"dzo", "dz"}},
        {{"Eastern Frisian"}, {"frs"}},
        {{"Edo", "Bini"}, {"bin"}},
        {{"Efik"}, {"efi"}},
        {{"Egyptian (Ancient)"}, {"egy"}},
        {{"Ekajuk"}, {"eka"}},
        {{"Elamite"}, {"elx"}},
        {{"English"}, {"eng", "en"}},
        {{"English, Middle (1100-1500)"}, {"enm"}},
        {{"English, Old (ca.450-1100)"}, {"ang"}},
        {{"Erzya"}, {"myv"}},
        {{"Esperanto"}, {"eo", "epo"}},
        {{"Estonian"}, {"et", "est"}},
        {{"Ewe"}, {"ee", "ewe"}},
        {{"Ewondo"}, {"ewo"}},
        {{"Fang"}, {"fan"}},
        {{"Fanti"}, {"fat"}},
        {{"Faroese"}, {"fao", "fo"}},
        {{"Fijian"}, {"fij", "fj"}},
        {{"Finnish"}, {"fin", "fi"}},
        {{"Finno-Ugrian languages"}, {"fiu"}},
        {{"Fon"}, {"fon"}},
        {{"French"}, {"fre", "fra", "fr"}},
        {{"French, Middle (ca.1400-1600)"}, {"frm"}},
        {{"French, Old (842-ca.1400)"}, {"fro"}},
        {{"Friulian"}, {"fur"}},
        {{"Fulah"}, {"ful", "ff"}},
        {{"Ga"}, {"gaa"}},
        {{"Gaelic", "Scottish Gaelic"}, {"gd", "gla"}},
        {{"Galibi Carib"}, {"car"}},
        {{"Galician"}, {"gl", "glg"}},
        {{"Ganda"}, {"lug"}},
        {{"Gayo"}, {"gay"}},
        {{"Gbaya"}, {"gba"}},
        {{"Geez"}, {"gez"}},
        {{"Georgian"}, {"ka", "kat", "geo"}},
        {{"German"}, {"de", "deu", "ger"}},
        {{"German, Middle High (ca.1050-1500)"}, {"gmh"}},
        {{"German, Old High (ca.750-1050)"}, {"goh"}},
        {{"Germanic languages"}, {"gem"}},
        {{"Gikuyu", "Kikuyu"}, {"ki", "kik"}},
        {{"Gilbertese"}, {"gil"}},
        {{"Gondi"}, {"gon"}},
        {{"Gorontalo"}, {"gor"}},
        {{"Gothic"}, {"got"}},
        {{"Grebo"}, {"grb"}},
        {{"Greek, Ancient (to 1453)"}, {"grc"}},
        {{"Greek, Modern (1453-)"}, {"gre", "ell"}},
        {{"Greenlandic", "Kalaallisut"}, {"kal", "kl"}},
        {{"Guarani"}, {"grn", "gn"}},
        {{"Gujarati"}, {"guj", "gu"}},
        {{"Gwich'in"}, {"gwi"}},
        {{"Haida"}, {"hai"}},
        {{"Haitian Creole", "Haitian"}, {"ht", "hat"}},
        {{"Hausa"}, {"hau", "ha"}},
        {{"Hawaiian"}, {"haw"}},
        {{"Hebrew"}, {"he", "heb"}},
        {{"Herero"}, {"hz", "her"}},
        {{"Hiligaynon"}, {"hil"}},
        {{"Hindi"}, {"hi", "hin"}},
        {{"Hiri Motu"}, {"hmo", "ho"}},
        {{"Hittite"}, {"hit"}},
        {{"Hungarian"}, {"hun", "hu"}},
        {{"Hupa"}, {"hup"}},
        {{"Iban"}, {"iba"}},
        {{"Icelandic"}, {"is", "isl", "ice"}},
        {{"Ido"}, {"io", "ido"}},
        {{"Igbo"}, {"ig", "ibo"}},
        {{"Ijo languages"}, {"ijo"}},
        {{"Iloko"}, {"ilo"}},
        {{"Inari Sami"}, {"smn"}},
        {{"Indic languages"}, {"inc"}},
        {{"Indo-European languages"}, {"ine"}},
        {{"Indonesian"}, {"ind", "id"}},
        {{"Ingush"}, {"inh"}},
        {{"Interlingua (International Auxiliary Language Association)"}, {"ina", "ia"}},
        {{"Interlingue", "Occidental"}, {"ile", "ie"}},
        {{"Inuktitut"}, {"iu", "iku"}},
        {{"Inupiaq"}, {"ik", "ipk"}},
        {{"Iranian languages"}, {"ira"}},
        {{"Irish"}, {"gle", "ga"}},
        {{"Irish, Middle (900-1200)"}, {"mga"}},
        {{"Irish, Old (to 900)"}, {"sga"}},
        {{"Iroquoian languages"}, {"iro"}},
        {{"Italian"}, {"ita", "it"}},
        {{"Japanese"}, {"ja", "jpn"}},
        {{"Javanese"}, {"jav", "jv"}},
        {{"Judeo-Arabic"}, {"jrb"}},
        {{"Judeo-Persian"}, {"jpr"}},
        {{"Kabardian"}, {"kbd"}},
        {{"Kabyle"}, {"kab"}},
        {{"Kachin", "Jingpho"}, {"kac"}},
        {{"Kamba"}, {"kam"}},
        {{"Kannada"}, {"kn", "kan"}},
        {{"Kanuri"}, {"kau", "kr"}},
        {{"Kapampangan", "Pampanga"}, {"pam"}},
        {{"Kara-Kalpak"}, {"kaa"}},
        {{"Karachay-Balkar"}, {"krc"}},
        {{"Karelian"}, {"krl"}},
        {{"Karen languages"}, {"kar"}},
        {{"Kashmiri"}, {"ks", "kas"}},
        {{"Kashubian"}, {"csb"}},
        {{"Kawi"}, {"kaw"}},
        {{"Kazakh"}, {"kk", "kaz"}},
        {{"Khasi"}, {"kha"}},
        {{"Khoisan languages"}, {"khi"}},
        {{"Khotanese", "Sakan"}, {"kho"}},
        {{"Kimbundu"}, {"kmb"}},
        {{"Kinyarwanda"}, {"kin", "rw"}},
        {{"Komi"}, {"kv", "kom"}},
        {{"Kongo"}, {"kg", "kon"}},
        {{"Konkani"}, {"kok"}},
        {{"Korean"}, {"kor", "ko"}},
        {{"Kosraean"}, {"kos"}},
        {{"Kpelle"}, {"kpe"}},
        {{"Kru languages"}, {"kro"}},
        {{"Kuanyama", "Kwanyama"}, {"kj", "kua"}},
        {{"Kumyk"}, {"kum"}},
        {{"Kurdish"}, {"kur", "ku"}},
        {{"Kurukh"}, {"kru"}},
        {{"Kutenai"}, {"kut"}},
        {{"Kyrgyz", "Kirghiz"}, {"ky", "kir"}},
        {{"Ladino"}, {"lad"}},
        {{"Lahnda"}, {"lah"}},
        {{"Lamba"}, {"lam"}},
        {{"Land Dayak languages"}, {"day"}},
        {{"Lao"}, {"lao", "lo"}},
        {{"Latin"}, {"la", "lat"}},
        {{"Latvian"}, {"lav", "lv"}},
        {{"Letzeburgesch", "Luxembourgish"}, {"lb", "ltz"}},
        {{"Lezghian"}, {"lez"}},
        {{"Limburgan", "Limburger", "Limburgish"}, {"lim", "li"}},
        {{"Lingala"}, {"ln", "lin"}},
        {{"Lithuanian"}, {"lt", "lit"}},
        {{"Lojban"}, {"jbo"}},
        {{"Low German", "German, Low", "Saxon, Low", "Low Saxon"}, {"nds"}},
        {{"Lower Sorbian"}, {"dsb"}},
        {{"Lozi"}, {"loz"}},
        {{"Luba-Katanga"}, {"lu", "lub"}},
        {{"Luba-Lulua"}, {"lua"}},
        {{"Luiseno"}, {"lui"}},
        {{"Lule Sami"}, {"smj"}},
        {{"Lunda"}, {"lun"}},
        {{"Luo (Kenya and Tanzania)"}, {"luo"}},
        {{"Lushai"}, {"lus"}},
        {{"Macedo-Romanian", "Arumanian", "Aromanian"}, {"rup"}},
        {{"Macedonian"}, {"mac", "mk", "mkd"}},
        {{"Madurese"}, {"mad"}},
        {{"Magahi"}, {"mag"}},
        {{"Maithili"}, {"mai"}},
        {{"Makasar"}, {"mak"}},
        {{"Malagasy"}, {"mlg", "mg"}},
        {{"Malay"}, {"msa", "may"}},
        {{"Malayalam"}, {"mal", "ml"}},
        {{"Maltese"}, {"mt", "mlt"}},
        {{"Manchu"}, {"mnc"}},
        {{"Mandar"}, {"mdr"}},
        {{"Mandingo"}, {"man"}},
        {{"Manipuri"}, {"mni"}},
        {{"Manobo languages"}, {"mno"}},
        {{"Manx"}, {"glv", "gv"}},
        {{"Maori"}, {"mao", "mri", "mi"}},
        {{"Mapuche", "Mapudungun"}, {"arn"}},
        {{"Marathi"}, {"mr", "mar"}},
        {{"Mari"}, {"chm"}},
        {{"Marshallese"}, {"mah", "mh"}},
        {{"Marwari"}, {"mwr"}},
        {{"Masai"}, {"mas"}},
        {{"Mayan languages"}, {"myn"}},
        {{"Mende"}, {"men"}},
        {{"Micmac", "Mi'kmaq"}, {"mic"}},
        {{"Minangkabau"}, {"min"}},
        {{"Mirandese"}, {"mwl"}},
        {{"Mohawk"}, {"moh"}},
        {{"Moksha"}, {"mdf"}},
        {{"Moldovan", "Moldavian", "Romanian"}, {"mo", "ron", "rum"}},
        {{"Mon-Khmer languages"}, {"mkh"}},
        {{"Mong", "Hmong"}, {"hmn"}},
        {{"Mongo"}, {"lol"}},
        {{"Mongolian"}, {"mon", "mn"}},
        {{"Montenegrin"}, {"cnr"}},
        {{"Mossi"}, {"mos"}},
        {{"Multiple languages"}, {"mul"}},
        {{"Munda languages"}, {"mun"}},
        {{"N'Ko"}, {"nqo"}},
        {{"Nahuatl languages"}, {"nah"}},
        {{"Nauru"}, {"nau", "na"}},
        {{"Navajo", "Navaho"}, {"nav", "nv"}},
        {{"Ndebele, North", "North Ndebele"}, {"nde", "nd"}},
        {{"Ndebele, South", "South Ndebele"}, {"nr", "nbl"}},
        {{"Ndonga"}, {"ng", "ndo"}},
        {{"Neapolitan"}, {"nap"}},
        {{"Nepal Bhasa", "Newari"}, {"new"}},
        {{"Nepali"}, {"nep"}},
        {{"Nias"}, {"nia"}},
        {{"Niger-Kordofanian languages"}, {"nic"}},
        {{"Nilo-Saharan languages"}, {"ssa"}},
        {{"Niuean"}, {"niu"}},
        {{"No linguistic content", "Not applicable"}, {"zxx"}},
        {{"Nogai"}, {"nog"}},
        {{"Norse, Old"}, {"non"}},
        {{"North American Indian languages"}, {"nai"}},
        {{"Northern Frisian"}, {"frr"}},
        {{"Northern Sami"}, {"se", "sme"}},
        {{"Norwegian"}, {"nor", "no"}},
        {{"Norwegian Bokmål", "Bokmål, Norwegian"}, {"nob", "nb"}},
        {{"Norwegian Nynorsk", "Nynorsk, Norwegian"}, {"nno", "nn"}},
        {{"Nubian languages"}, {"nub"}},
        {{"Nuosu", "Sichuan Yi"}, {"ii", "iii"}},
        {{"Nyamwezi"}, {"nym"}},
        {{"Nyankole"}, {"nyn"}},
        {{"Nyoro"}, {"nyo"}},
        {{"Nzima"}, {"nzi"}},
        {{"Occitan (post 1500)"}, {"oc", "oci"}},
        {{"Official Aramaic (700-300 BCE)", "Imperial Aramaic (700-300 BCE)"}, {"arc"}},
        {{"Oirat", "Kalmyk"}, {"xal"}},
        {{"Ojibwa"}, {"oji", "oj"}},
        {{"Old Church Slavonic", "Old Slavonic", "Church Slavic", "Church Slavonic", "Old Bulgarian"}, {"chu", "cu"}},
        {{"Oriya"}, {"ori"}},
        {{"Oromo"}, {"om", "orm"}},
        {{"Osage"}, {"osa"}},
        {{"Ossetic", "Ossetian"}, {"oss", "os"}},
        {{"Otomian languages"}, {"oto"}},
        {{"Pahlavi"}, {"pal"}},
        {{"Palauan"}, {"pau"}},
        {{"Pali"}, {"pi", "pli"}},
        {{"Pangasinan"}, {"pag"}},
        {{"Papiamento"}, {"pap"}},
        {{"Papuan languages"}, {"paa"}},
        {{"Pedi", "Northern Sotho", "Sepedi"}, {"nso"}},
        {{"Persian"}, {"fa", "per", "fas"}},
        {{"Persian, Old (ca.600-400 B.C.)"}, {"peo"}},
        {{"Philippine languages"}, {"phi"}},
        {{"Phoenician"}, {"phn"}},
        {{"Pilipino", "Filipino"}, {"fil"}},
        {{"Pohnpeian"}, {"pon"}},
        {{"Polish"}, {"pl", "pol"}},
        {{"Portuguese"}, {"por", "pt"}},
        {{"Prakrit languages"}, {"pra"}},
        {{"Provençal, Old (to 1500);Occitan, Old (to 1500)"}, {"pro"}},
        {{"Punjabi", "Panjabi"}, {"pa", "pan"}},
        {{"Pushto", "Pashto"}, {"ps", "pus"}},
        {{"Quechua"}, {"que", "qu"}},
        {{"Rajasthani"}, {"raj"}},
        {{"Rapanui"}, {"rap"}},
        {{"Rarotongan", "Cook Islands Maori"}, {"rar"}},
        {{"Reserved for local use"}, {"qaa-qtz"}},
        {{"Romance languages"}, {"roa"}},
        {{"Romansh"}, {"rm", "roh"}},
        {{"Romany"}, {"rom"}},
        {{"Rundi"}, {"rn", "run"}},
        {{"Russian"}, {"rus", "ru"}},
        {{"Salishan languages"}, {"sal"}},
        {{"Samaritan Aramaic"}, {"sam"}},
        {{"Sami languages"}, {"smi"}},
        {{"Samoan"}, {"smo", "sm"}},
        {{"Sandawe"}, {"sad"}},
        {{"Sango"}, {"sag", "sg"}},
        {{"Sanskrit"}, {"sa", "san"}},
        {{"Santali"}, {"sat"}},
        {{"Sardinian"}, {"sc", "srd"}},
        {{"Sasak"}, {"sas"}},
        {{"Scots"}, {"sco"}},
        {{"Selkup"}, {"sel"}},
        {{"Semitic languages"}, {"sem"}},
        {{"Serbian"}, {"sr", "srp"}},
        {{"Serer"}, {"srr"}},
        {{"Shan"}, {"shn"}},
        {{"Shona"}, {"sna", "sn"}},
        {{"Sicilian"}, {"scn"}},
        {{"Sidamo"}, {"sid"}},
        {{"Sign Languages"}, {"sgn"}},
        {{"Siksika"}, {"bla"}},
        {{"Sindhi"}, {"snd", "sd"}},
        {{"Sinhala", "Sinhalese"}, {"si", "sin"}},
        {{"Sino-Tibetan languages"}, {"sit"}},
        {{"Siouan languages"}, {"sio"}},
        {{"Skolt Sami"}, {"sms"}},
        {{"Slave (Athapascan)"}, {"den"}},
        {{"Slavic languages"}, {"sla"}},
        {{"Slovak"}, {"sk", "slk", "slo"}},
        {{"Slovenian"}, {"slv", "sl"}},
        {{"Sogdian"}, {"sog"}},
        {{"Somali"}, {"so", "som"}},
        {{"Songhai languages"}, {"son"}},
        {{"Soninke"}, {"snk"}},
        {{"Sorbian languages"}, {"wen"}},
        {{"Sotho, Southern"}, {"sot"}},
        {{"South American Indian languages"}, {"sai"}},
        {{"Southern Altai"}, {"alt"}},
        {{"Southern Sami"}, {"sma"}},
        {{"Spanish", "Castilian"}, {"es", "spa"}},
        {{"Sranan Tongo"}, {"srn"}},
        {{"Standard Moroccan Tamazight"}, {"zgh"}},
        {{"Sukuma"}, {"suk"}},
        {{"Sumerian"}, {"sux"}},
        {{"Sundanese"}, {"sun", "su"}},
        {{"Susu"}, {"sus"}},
        {{"Swahili"}, {"swa"}},
        {{"Swati"}, {"ss", "ssw"}},
        {{"Swedish"}, {"swe", "sv"}},
        {{"Swiss German", "Alemannic", "Alsatian"}, {"gsw"}},
        {{"Syriac"}, {"syr"}},
        {{"Tagalog"}, {"tgl", "tl"}},
        {{"Tahitian"}, {"ty", "tah"}},
        {{"Tai languages"}, {"tai"}},
        {{"Tajik"}, {"tgk", "tg"}},
        {{"Tamashek"}, {"tmh"}},
        {{"Tamil"}, {"tam", "ta"}},
        {{"Tatar"}, {"tt", "tat"}},
        {{"Telugu"}, {"te", "tel"}},
        {{"Tereno"}, {"ter"}},
        {{"Tetum"}, {"tet"}},
        {{"Thai"}, {"th", "tha"}},
        {{"Tibetan"}, {"tib", "bo", "bod"}},
        {{"Tigre"}, {"tig"}},
        {{"Tigrinya"}, {"ti", "tir"}},
        {{"Timne"}, {"tem"}},
        {{"Tiv"}, {"tiv"}},
        {{"Tlingit"}, {"tli"}},
        {{"Tok Pisin"}, {"tpi"}},
        {{"Tokelau"}, {"tkl"}},
        {{"Tonga (Nyasa)"}, {"tog"}},
        {{"Tonga (Tonga Islands)"}, {"to", "ton"}},
        {{"Tsimshian"}, {"tsi"}},
        {{"Tsonga"}, {"tso", "ts"}},
        {{"Tswana"}, {"tsn", "tn"}},
        {{"Tumbuka"}, {"tum"}},
        {{"Tupi languages"}, {"tup"}},
        {{"Turkish"}, {"tr", "tur"}},
        {{"Turkish, Ottoman (1500-1928)"}, {"ota"}},
        {{"Turkmen"}, {"tk", "tuk"}},
        {{"Tuvalu"}, {"tvl"}},
        {{"Tuvinian"}, {"tyv"}},
        {{"Twi"}, {"twi", "tw"}},
        {{"Udmurt"}, {"udm"}},
        {{"Ugaritic"}, {"uga"}},
        {{"Uighur", "Uyghur"}, {"ug", "uig"}},
        {{"Ukrainian"}, {"uk", "ukr"}},
        {{"Umbundu"}, {"umb"}},
        {{"Uncoded languages"}, {"mis"}},
        {{"Undetermined"}, {"und"}},
        {{"Upper Sorbian"}, {"hsb"}},
        {{"Urdu"}, {"urd", "ur"}},
        {{"Uzbek"}, {"uzb", "uz"}},
        {{"Vai"}, {"vai"}},
        {{"Valencian", "Catalan"}, {"ca", "cat"}},
        {{"Venda"}, {"ven", "ve"}},
        {{"Vietnamese"}, {"vie", "vi"}},
        {{"Volapük"}, {"vo", "vol"}},
        {{"Votic"}, {"vot"}},
        {{"Wakashan languages"}, {"wak"}},
        {{"Walloon"}, {"wln", "wa"}},
        {{"Waray"}, {"war"}},
        {{"Washo"}, {"was"}},
        {{"Welsh"}, {"wel", "cy", "cym"}},
        {{"Western Frisian"}, {"fry", "fy"}},
        {{"Western Pahari languages", "Himachali languages"}, {"him"}},
        {{"Wolaytta", "Wolaitta"}, {"wal"}},
        {{"Wolof"}, {"wol", "wo"}},
        {{"Xhosa"}, {"xh", "xho"}},
        {{"Yakut"}, {"sah"}},
        {{"Yao"}, {"yao"}},
        {{"Yapese"}, {"yap"}},
        {{"Yiddish"}, {"yid", "ji"}},
        {{"Yoruba"}, {"yor", "yo"}},
        {{"Yupik languages"}, {"ypk"}},
        {{"Zande languages"}, {"znd"}},
        {{"Zapotec"}, {"zap"}},
        {{"Zazaki", "Dimli", "Kirdki", "Zaza", "Dimili", "Kirmanjki"}, {"zza"}},
        {{"Zenaga"}, {"zen"}},
        {{"Zulu"}, {"zul", "zu"}},
        {{"Zuni"}, {"zun"}},
        {{"tlhIngan-Hol", "Klingon"}, {"tlh"}}
    }};
    
    bool does_tag_match_language(const string& language, const string& tag);
    string get_tag_language(const string& tag);
    const vector<string_view>& get_language_tags(const string& language);
}