"""
    Matroska track setter  Copyright (C) 2022  Kyoya2

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
"""
This module is responsible for parsing an EBML Schema file and generating a c++ unordered_map of
'EbmlElementSpecification' objects whose keys are the IDs of the elements. The file EbmlElements.py
is generated from the template EbmlElements.template
for more information, see: https://www.rfc-editor.org/rfc/rfc8794.html#name-ebml-schema
"""
from os.path import abspath
import re
import xml.etree.ElementTree as ElementTree
import requests

MATROSKA_EBML_SCHEMA_ADDRESS = r'https://raw.githubusercontent.com/ietf-wg-cellar/matroska-specification/master/ebml_matroska.xml'
TEMPLATE_FILE_PATH = 'MatroskaElementSpecification.template.h'
OUTPUT_FILE_PATH = '../MatroskaTrackSelector/MatroskaTrackSelector/MatroskaElementSpecification.auto.h'

class EbmlSchemaElementType:
    """
    Types of available enum element values
    """
    Int = 'integer'
    UInt = 'uinteger'
    AsciiString = 'string'


class EbmlSchemaElement:
    def __init__(self, element_name: str, element_id: int):
        self.name = element_name
        self.id = element_id
        self.possible_enum_values = None

    def add_possible_enum(self, value: str, name: int):
        self.possible_enum_values.update({name: value})


def parse_value_by_type(value, value_type: str):
    """
    This function parses a value from the schema according to it's type
    """
    if value_type in [EbmlSchemaElementType.Int, EbmlSchemaElementType.UInt]:
        return int(value)
    elif value_type in EbmlSchemaElementType.AsciiString:
        return str(value)
    else:
        raise NotImplementedError('Unimplemented enum type')


def get_elements(schema_file_data: str):
    """
    This function generates a convinient dict that contains all specified elements
    """
    # Remove XML namespace in order to not have to deal with the prefix on each tag name
    root = ElementTree.fromstring(re.sub(' xmlns=".+?"', '', schema_file_data, count=1))

    # A list that contains all ebml elements
    # it's initialized with header elements that don't appear in the schema
    schema_elements = [
        EbmlSchemaElement('EBML', 0x1A45DFA3),
        EbmlSchemaElement('EBMLVersion', 0x4286),
        EbmlSchemaElement('EBMLReadVersion', 0x42F7),
        EbmlSchemaElement('DocType', 0x4282),
        EbmlSchemaElement('DocTypeVersion', 0x4287),
        EbmlSchemaElement('DocTypeReadVersion', 0x4285),
        EbmlSchemaElement('DocTypeExtension', 0x4281),
        EbmlSchemaElement('DocTypeExtensionName', 0x4283),
        EbmlSchemaElement('DocTypeExtensionVersion', 0x4284),
        EbmlSchemaElement('CRC-32', 0xBF),
        EbmlSchemaElement('Void', 0xEC)

        # these element appear in the header but they are usually included in the schema
        #EbmlSchemaElement('EBMLMaxIDLength', 0x42F2),
        #EbmlSchemaElement('EBMLMaxSizeLength', 0x42F3),
    ]

    for element in root:
        element_type = element.attrib['type']
        current_element = EbmlSchemaElement(element.attrib['name'], int(element.attrib['id'][2:], base=16))

        # adding possible enum values
        restriction_element = element.find('restriction')
        if restriction_element:
            current_element.possible_enum_values = {}
            for child in restriction_element.findall('enum'):
                current_element.possible_enum_values.update({child.attrib['label']: parse_value_by_type(child.attrib['value'], element_type)})

        schema_elements.append(current_element)
    
    return schema_elements


def get_ebml_elements_string(element: EbmlSchemaElement):
    enum_string = ''
        
    element.name = element.name.replace('-', '_')
    element_string = f'DECL_ELEMENT_ID({element.name}, {hex(element.id)});'

    if element.possible_enum_values is not None:
        enum_string = 'enum class ' + element.name + ' {\n'
        for name, value in element.possible_enum_values.items():
            # Make enum name start with a valid character for C++ enum names
            displayed_name = name.lower()
            if displayed_name[0].isdigit():
                displayed_name = '_'+displayed_name
            
            # Replace some special characters while making the enum name as readable as possible
            displayed_name = displayed_name.replace('/', ' or ').replace(' - ', ' to ').replace('.', '_')

            # Turn into UpperCamelCase
            displayed_name = re.sub(r'\b(\w)', lambda match:match[1].upper(), displayed_name)

            # Remove the rest of the special characters
            displayed_name = re.sub(r'[^\w\d]', '', displayed_name)

            enum_string += ' ' * 4 + displayed_name
            enum_string += f' = {repr(value)},\n'

        # cut out last ',\n'
        enum_string = enum_string[:-2] + '\n' + '};'

        # elegantly comment-out non-number elements to remind myself to handle it in the future
        if not all(type(value)==int for value in element.possible_enum_values.values()):
            enum_string = f'/*{enum_string}*/'
        enum_string += '\n'

    return (element_string, enum_string)


def main():
    # Download newest schema
    matroska_ebml_schema = requests.get(MATROSKA_EBML_SCHEMA_ADDRESS).content.decode()
    elements = get_elements(matroska_ebml_schema)

    elements_string = ''
    enums_string = ''
    for element in elements:
        element_string, enum_string = get_ebml_elements_string(element)
        elements_string += element_string + '\n'
        enums_string += enum_string

    elements_string = elements_string[:-1]
    enums_string = enums_string[:-1]

    with open(TEMPLATE_FILE_PATH, 'r') as template_file:
        template = template_file.read()

    with open(OUTPUT_FILE_PATH, 'w') as f:
        f.write(template.format(ELEMENTS_INFO=elements_string, ENUM_ELEMENTS=enums_string))
    
    print('Generaetd file at', abspath(OUTPUT_FILE_PATH))


if __name__ == '__main__':
    main()