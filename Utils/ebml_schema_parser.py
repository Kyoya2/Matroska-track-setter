"""
This module is responsible for parsing an EBML Schema file and generating a c++ unordered_map of
'EbmlElementSpecification' objects whose keys are the IDs of the elements. The file EbmlElements.py
is generated from the template EbmlElements.template
for more information, see: https://www.rfc-editor.org/rfc/rfc8794.html#name-ebml-schema
"""
import xml.etree.ElementTree as ElementTree
from collections import namedtuple

EBML_SCHEMA_PATH_SEPARATOR = '\\'

EbmlElement = namedtuple('EbmlElement', ['Name', 'Type', 'Children', 'PossibleValues'],)

class EbmlElement:
    def __init__(self, element_type: str, default_value = None, children = None, possible_values = None):
        self.type = element_type
        self.default_value = default_value
        self.children = children
        self.possible_values = possible_values


class EbmlSchemaElementType:
    """
    All the possible types of an EBML element as specified in
    the 'type' attribute of an 'element' tag in the schema
    """
    Master = 'master'
    Int = 'integer'
    UInt = 'uinteger'
    Float = 'float'
    AsciiString = 'string'
    Utf8String = 'utf-8'
    Date = 'date'
    Binary = 'binary'

    # This is not a valid type for an ebml element but it makes more sense
    # to use this as a separate type because enums in the ebml schema are
    # represented in a 'restrictions' tag inside an 'element' tag
    Enum = 'ENUM'


class EbmlSchemaElement:
    def __init__(self, element_name: str, element_id: int, element_type: str, path: str, default_value = None, original_type = None):
        if element_type == EbmlSchemaElementType.Enum:
            self.possible_enum_values = dict()

        self.name = element_name
        self.id = element_id
        self.type = element_type
        self.path = path
        self.default_value = default_value
        self.numeric_path = None
        self.original_type = original_type

    def add_possible_enum(self, value: str, name: int):
        self.possible_enum_values.update({value: name})

    def is_first_degree_child(self, path: str) -> bool:
        """
        Returns true if the given path describes a first-degree
        parent of the current element
        """
        if not self.path.startswith(path):
            return False

        # If this is the root element than any first-degree child of
        # the root has a single path separator at the beginning
        if path == EBML_SCHEMA_PATH_SEPARATOR:
            return (self.path.count(EBML_SCHEMA_PATH_SEPARATOR) == 1)

        # at this point we know that the curent element is indeed a child of some degree
        # of the given parent. We cut out the part that the child shares with
        # the parent to get a relative path, for example:
        #   parent = '/Segment/a'
        #   child = '/Segment/a/b/c'
        #   relative_child_path = '/b/c'
        # now we can count the number of path separators inside the relative
        # path to determine the level of the child inside the parent, if the
        # level is 1 then he's the father, 2 for granfather and so on
        relative_child_path = self.path[len(path):]
        return (relative_child_path.count(EBML_SCHEMA_PATH_SEPARATOR) == 1)


def parse_value_by_type(value, value_type: str):
    """
    This function parses a value from the schema according to it's type
    """
    if value_type in [EbmlSchemaElementType.Int, EbmlSchemaElementType.UInt]:
        return int(value)
    elif value_type in [EbmlSchemaElementType.AsciiString, EbmlSchemaElementType.Utf8String]:
        return str(value)
    elif value_type == EbmlSchemaElementType.Float:
        if value == '0x1p+0':
            return 1.0
        elif value == '0x0p+0':
            return 0.0
        elif value == '0x1.f4p+12':
            return 8000.0
        else:
            print(value)
            raise NotImplementedError('Too lazy to figure out how this format works')
    else:
        raise NotImplementedError('Too lazy to implement parsing for this type')


def get_elements(schema_file: str):
    """
    This function generates a convinient dict that contains all specified elements
    """
    tree = ElementTree.parse(schema_file)
    root = tree.getroot()

    def remove_ebml_tag_prefix(tag_name: str) -> str:
        """
        ElementTree tag names are prefixed with the xml namespace, this
        function is responsible for removing that prefix.

        Example: remove_ebml_tag_prefix('{urn:ietf:rfc:8794}my_tag') = 'my_tag'
        """
        namespace_length = root.tag.index('}') + 1
        return tag_name[namespace_length:]


    # A list that contains all ebml elements
    # it's initialized with header elements that don't appear in the schema
    schema_elements = [
        EbmlSchemaElement('EBML', 0x1A45DFA3, EbmlSchemaElementType.Master, '\\EBML'),
        EbmlSchemaElement('EBMLVersion', 0x4286, EbmlSchemaElementType.UInt, '\\EBML\\EBMLVersion'),
        EbmlSchemaElement('EBMLReadVersion', 0x42F7, EbmlSchemaElementType.UInt, '\\EBML\\EBMLReadVersion'),
        EbmlSchemaElement('DocType', 0x4282, EbmlSchemaElementType.AsciiString, '\\EBML\\DocType'),
        EbmlSchemaElement('DocTypeVersion', 0x4287, EbmlSchemaElementType.UInt, '\\EBML\\DocTypeVersion'),
        EbmlSchemaElement('DocTypeReadVersion', 0x4285, EbmlSchemaElementType.UInt, '\\EBML\\DocTypeReadVersion'),
        EbmlSchemaElement('DocTypeExtension', 0x4281, EbmlSchemaElementType.Master, '\\EBML\\DocTypeExtension'),
        EbmlSchemaElement('DocTypeExtensionName', 0x4283, EbmlSchemaElementType.AsciiString, '\\EBML\\DocTypeExtension\\Name'),
        EbmlSchemaElement('DocTypeExtensionVersion', 0x4284, EbmlSchemaElementType.UInt, '\\EBML\\DocTypeExtension\\Version'),
        EbmlSchemaElement('CRC-32', 0xBF, EbmlSchemaElementType.Binary, '\\(1-\\)CRC-32'),
        EbmlSchemaElement('Void', 0xEC, EbmlSchemaElementType.Binary, '\\(-\\)Void')

        # these element appear in the header but they are usually included in the schema
        #EbmlSchemaElement('EBMLMaxIDLength', 0x42F2, EbmlSchemaElementType.UInt, '\\EBML\\EBMLMaxIDLength'),
        #EbmlSchemaElement('EBMLMaxSizeLength', 0x42F3, EbmlSchemaElementType.UInt, '\\EBML\\EBMLMaxSizeLength'),
    ]


    for element in root:
        restriction_element = None
        for child in element:
            if remove_ebml_tag_prefix(child.tag) == 'restriction':
                restriction_element = child
                break


        original_type = element.attrib['type']

        default_value = None
        try:
            if original_type != EbmlSchemaElementType().Master:
                default_value = parse_value_by_type(element.attrib['default'], original_type)
        except KeyError:
            ...

        # if the element has a 'restriction' tag it means that it's an enum
        current_element = EbmlSchemaElement(
                            element.attrib['name'],
                            int(element.attrib['id'][2:], base=16),
                            (EbmlSchemaElementType.Enum) if (restriction_element) else (original_type),
                            element.attrib['path'],
                            default_value,
                            original_type
                        )

        # adding possible enum values
        if current_element.type == EbmlSchemaElementType.Enum:
            for child in restriction_element:
                if remove_ebml_tag_prefix(child.tag) == 'enum':
                    current_element.add_possible_enum(
                                value = parse_value_by_type(child.attrib['value'], original_type),
                                name  = child.attrib['label']
                            )

        schema_elements.append(current_element)

    # Genrating numeric paths paths
    for element in schema_elements:
        numeric_path = []
        # loop over the parts of the path that don't include the name of the element
        # example: '/Segment/a/b/c' -> ['Segment', 'a', 'b']
        for element_name in element.path[:-len(element.name)].strip(EBML_SCHEMA_PATH_SEPARATOR).split(EBML_SCHEMA_PATH_SEPARATOR):
            for element2 in schema_elements:
                if element2.name == element_name:
                    numeric_path.append(element2.id)
                    break

        if len(numeric_path) > 0:
            element.numeric_path = tuple(numeric_path)

    return schema_elements


    # this is a dummy for the root element
    root_element = EbmlSchemaElement('root', 0, EbmlSchemaElementType.Master, EBML_SCHEMA_PATH_SEPARATOR)
    add_children_recursively(root_element, schema_elements)
    return root_element


def get_ebml_elements_string(element: EbmlSchemaElement):
    string = ''

    types_dict = {
        EbmlSchemaElementType.Master        : 'Master',
        EbmlSchemaElementType.Int           : 'Int',
        EbmlSchemaElementType.UInt          : 'UInt',
        EbmlSchemaElementType.Float         : 'Float',
        EbmlSchemaElementType.AsciiString   : 'AsciiString',
        EbmlSchemaElementType.Utf8String    : 'Utf8String',
        EbmlSchemaElementType.Date          : 'Date',
        EbmlSchemaElementType.Binary        : 'Binary',
        EbmlSchemaElementType.Enum          : 'Enum'
    }

    string += ' ' * 4
    string += hex(element.id).ljust(10) + ' : '
    string += f'EbmlElementSpecification(\'{element.name}\''
    string += ', EbmlElementType.' + types_dict[element.type]

    if element.default_value is not None:
        # default value
        string += ', default = ' + repr(element.default_value)

    if element.numeric_path is not None:
        string += ', numeric_path = (' + ''.join([(hex(path_part_id) + ', ') for path_part_id in element.numeric_path])[:-1] + ')'

    if element.type == EbmlSchemaElementType.Enum:
        # enum
        string += ', enum_type = EbmlElementType.' + types_dict[element.original_type]
        string += ', possible_values = {\n'
        for value, name in element.possible_enum_values.items():
            string += ' ' * 48
            string += f'{repr(value)} : {repr(name)},\n'

        # cut out last ',\n'
        string = string[:-2] + '}'
    string += ')'
    return string

def main():
    elements = get_elements('ebml_matroska.xml')

    # Generating 
    string = '{\n'
    for element in elements:
        string += get_ebml_elements_string(element)
        string += ',\n'

    string = string[:-2] + '\n}'

    with open('EbmlElements.template', 'r') as template_file:
        template = template_file.read()

    with open('../EbmlElements.py', 'w') as f:
        f.write(template.format(ebml_elements_placeholder = string))


if __name__ == '__main__':
    main()