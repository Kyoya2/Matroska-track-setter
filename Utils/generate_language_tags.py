"""
    Matroska track setter  Copyright (C) 2023  Kyoya2

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
"""
import requests
import bs4
import re
from threading import Thread
from os.path import abspath

ISO639_2_CODE_LIST_URL = 'https://www.loc.gov/standards/iso639-2/php/code_list.php'
BCP47_LANGUAGE_SUBTAG_REGISTRY_URL = 'https://www.iana.org/assignments/language-subtag-registry/language-subtag-registry'

TEMPLATE_FILE_PATH = 'MatroskaLanguageTags.template.h'
OUTPUT_FILE_PATH = '../MatroskaTrackSelector/MatroskaTrackLib/MatroskaLanguageTags.auto.h'

def get_iso639_2_language_tags(result: list):
    raw_html_data = requests.get(ISO639_2_CODE_LIST_URL).content
    soup = bs4.BeautifulSoup(raw_html_data, features='lxml')

    # Select all rows in the table contaitning the values (except the first row which contains headers)
    rows = soup.select('body > table:nth-of-type(1) > tr:nth-of-type(1) > td:nth-of-type(1) > table:nth-of-type(1) > tr')[1:]
    for row in rows:
        # From each rows extract only the name of the language and the ISO639-2 tag
        language_names = set(row.select('td:nth-child(3)')[0].contents[0].split('; '))
        tags = {re.sub(r' \([TB]\)', '', e) for e in row.select('td:nth-child(1)')[0].contents if type(e)==bs4.element.NavigableString}

        # The same language may appear in multiple rows, in which case we join them together
        lang_already_exists = False
        for exesting_languages, matching_tags in result:
            if len(exesting_languages.intersection(language_names)):
                matching_tags.update(tags)
                exesting_languages.update(language_names)
                lang_already_exists = True
                break
        
        if not lang_already_exists:
            result.append((language_names, tags))

    return result


def get_bcp47_language_tags():
    result = []
    last_property = ''

    # Split into single entries
    subtag_entries = requests.get(BCP47_LANGUAGE_SUBTAG_REGISTRY_URL).content.decode().split('\n%%\n')

    # Each in an entry looks like "k: v", for example "Type: Language"
    # Turn each line into a property in a dictionary
    for subtag_entry in subtag_entries:
        properties = {}
        for p in subtag_entry.split('\n'):
            # Sometimes the line is too long and the next line will start with a double space
            # to represent that it's still the content from the previous line
            if p.startswith('  '):
                properties[last_property] += p[1:]
                continue

            # Add the current line to the properties
            k, _, v = p.partition(': ')
            properties.update({k: v})
            last_property = k

        # Generating result, ignore entries that we can't parse
        try:
            if properties['Type'] != 'language':
                continue
            result.append((properties['Description'], properties['Subtag']))
        except KeyError:
            continue

    return result


def set_to_cpp_array_entry(s: set):
    result = '{'
    for entry in sorted(s):
        r = repr(entry)  
        if r.startswith('"'):
            result += r
        else:
            result += r.replace('"', '\\"').replace("'", '"')
        result += ', '
    return result[:-2] + '}'


def main():
    # Get ISO639-2 tags in a separate thread
    all_tags = []
    t = Thread(target=get_iso639_2_language_tags, args=(all_tags,))
    t.start()
    bcp47_tags = get_bcp47_language_tags()
    t.join()

    # Add BCP47 tags with the same languages to all_tags
    for languages, current_iso639_2_tags in all_tags:
        for language, bcp47_tag in bcp47_tags:
            if language in languages:
                current_iso639_2_tags.add(bcp47_tag)
                bcp47_tags.remove((language, bcp47_tag))
                break

    # NOTE: Not adding BCP47 tags for languages that don't have an ISO639-2 tag
    # because they are not common and probably will never appear in MKV files.
    # This is done to save time when searching for a language string for each tag in a file.
    # If you still want to add BCP47 tags for languages that don't have an ISO639-2 tag,
    # uncomment the loop below.

    #for language, bcp47_tag in bcp47_tags:
    #    all_tags.append(({language}, {bcp47_tag}))

    result_string = ',\n'.join(sorted([(' ' * 8 + '{' + ', '.join(set_to_cpp_array_entry(e) for e in pair) + '}') for pair in all_tags]))

    with open(TEMPLATE_FILE_PATH, 'r') as template_file:
        template = template_file.read()

    with open(OUTPUT_FILE_PATH, 'w', encoding='UTF-8') as f:
        f.write(template.replace('{NUM_LANGUAGE_TAGS}', str(len(all_tags))).replace('{LANGUAGE_TAGS}', result_string))
    
    print('Generaetd file at', abspath(OUTPUT_FILE_PATH))


if __name__ == '__main__':
    main()