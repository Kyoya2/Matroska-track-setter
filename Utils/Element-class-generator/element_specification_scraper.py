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
"""
This module is responsible for parsing an EBML Schema file and generating a c++ unordered_map of
'EbmlElementSpecification' objects whose keys are the IDs of the elements. The file EbmlElements.py
is generated from the template EbmlElements.template
for more information, see: https://www.rfc-editor.org/rfc/rfc8794.html#name-ebml-schema
"""
import re
import requests
from schema_types import *
from os.path import abspath
from typing import Tuple
from xml.sax.saxutils import unescape
import xml.etree.ElementTree as ElementTree

EBML_RFC_ADDRESS = r'https://www.rfc-editor.org/rfc/rfc8794.xml'
MATROSKA_EBML_SCHEMA_ADDRESS = r'https://raw.githubusercontent.com/ietf-wg-cellar/matroska-specification/master/ebml_matroska.xml'
TEMPLATE_FILE_PATH = 'MatroskaElementSpecification.template.h'
OUTPUT_FILE_PATH = '../MatroskaTrackSelector/MatroskaTrackLib/MatroskaElementSpecification.auto.h'


def parse_value_by_type(value: str, value_type: EbmlElementType):
    """
    This function parses a value from the schema according to it's type
    """
    if value_type in [EbmlElementType.Int, EbmlElementType.UInt]:
        return int(value)
    elif value_type in [EbmlElementType.AsciiString, EbmlElementType.Utf8String]:
        return str(value)
    elif value_type == EbmlElementType.Float:
        return float.fromhex(value)
    elif value_type == EbmlElementType.Binary and value == '0':
        return 0
    else:
        raise NotImplementedError('Unimplemented enum type', value_type)


def extract_documentation_from_html_element(element: ElementTree.Element) -> EbmlDocumentation:
    """
    Returns all documentation entries inside an XML element
    """
    documentation = []
    for doc_element in element.findall('documentation'):
        # Skip non-english documentation
        if ('lang' in doc_element.attrib) and (doc_element.attrib['lang'] != 'en'):
            continue

        documentation.append(
            EbmlDocumentationEntry(
                EbmlDocumentationType(doc_element.attrib['purpose']),
                doc_element.text
            )
        )

    return documentation


def parse_boundary_string(bound_str: str, value_type: EbmlElementType) -> EbmlRangeDescriptor:
    """
    Parse a string that represents a single boundary, e.g. "<= 1337" or "> 0" and return an EbmlRangeDescriptor with
    either the lower or upper bound set to a valid EbmlBoundaryDescriptor according to the sign of the parsed string
    """
    sign, is_included, value_str = re.match(r'^([<>])(=)?\s*(\S+)$', bound_str).groups()
    bound = EbmlBoundaryDescriptor(
        parse_value_by_type(value_str, value_type),
        is_included == '='
    )

    if sign == '<':
        return EbmlRangeDescriptor(upper_bound=bound)
    else:
        assert sign == '>'
        return EbmlRangeDescriptor(lower_bound=bound)


def parse_length_attribute(length_attr: str) -> EbmlLengthType:
    """
    Parses a representation of an element's length.
    Possible representations include: "3", "< 5", ">= 1"
    """
    length_str = unescape(length_attr)
    if length_str[0] in ['<', '>']:
        # The length of an element is always an unsigned integer, regardless
        # of the type of the element
        return parse_boundary_string(length_str, EbmlElementType.UInt)
    else:
        return int(length_str)


def parse_range_attribute(range_attr: str, element_type: EbmlElementType) -> EbmlValueConstraintType:
    """
    Parses the representation of the range of an element's values
    Possible representations include: "1", "not 0", "<= 1", "< 5, >= 0", "3-90"
    """
    # Make sure that it's an element type that supports ranges
    assert element_type in [EbmlElementType.Int, EbmlElementType.UInt, EbmlElementType.Float, EbmlElementType.Date]

    range_string = unescape(range_attr)

    # "not xxx"
    if range_string.startswith('not '):
        return EbmlSingleValueConstraint(
            parse_value_by_type(range_string[len('not '):], element_type),
            False
        )

    # "<= foo, > bar" or "< bla" and etc...
    elif range_string[0] in ['<', '>']:
        range_parts = [part.strip() for part in range_string.split(',')]
        assert len(range_parts) in [1, 2]

        # Find and categorize the boundaries
        lower_bound, upper_bound = None, None
        for range_part in range_parts:
            crnt_bound = parse_boundary_string(range_part, element_type)
            if crnt_bound.upper_bound:
                assert upper_bound is None, 'Upper bound appears twice'
                upper_bound = crnt_bound.upper_bound
            elif crnt_bound.lower_bound:
                assert lower_bound is None, 'Lower bound appears twice'
                lower_bound = crnt_bound.lower_bound
            else:
                raise Exception('Got an empty constraint from string:', range_string)

        return EbmlRangeDescriptor(lower_bound, upper_bound)

    # "x-y"
    elif '-' in range_string:
        range_parts = range_string.split('-')
        assert len(range_parts) == 2
        return EbmlRangeDescriptor(*[
            EbmlBoundaryDescriptor(parse_value_by_type(range_part, element_type), True) for
            range_part in
            range_parts
        ])

    # "x"
    else:
        return EbmlSingleValueConstraint(
            parse_value_by_type(range_string, element_type),
            True
        )


def parse_element_from_ebml_rfc(element: ElementTree.Element) -> EbmlElement:
    """
    Parse an EBML element's description from an XML element in the EBML RFC.
    """
    # The properties of each element are pairs of (property_name, property_value) that follow each other
    # inside the "dl" element of the section
    property_names_and_values_elements = element.findall('dl/*')

    # make the list of [pname1, pval1, pname2, pval2, ...] into [[pname1, pval1], [pname2, pval2], ...]
    property_name_value_element_pairs = [property_names_and_values_elements[i:i + 2] for i in
                                         range(0, len(property_names_and_values_elements), 2)]

    # Set default values for properties that appear in SOME but NOT ALL element descriptors
    documentation = []
    default_value = None
    element_length = None
    min_occurs, max_occurs = 0, None
    value_constraints = None

    # Set bogus values for properties that are mandatory
    element_id, element_name, element_path, element_type = None, None, None, None

    # We need to know the type of the element to be able to parse the default value and the range. However, the
    # "type" property comes after the "default" property in the current format, so we iterate the list of
    # attributes in reversed order
    for property_name_element, property_value_element in reversed(property_name_value_element_pairs):
        property_name = property_name_element.text

        assert property_name.endswith(':'), 'Got an unexpected property'
        property_name = property_name[:-1]

        if property_name == 'path':
            property_value = property_value_element[0].text
        else:
            property_value = property_value_element.text

        if property_name == 'id':
            element_id = property_value

        elif property_name == 'name':
            element_name = property_value

        elif property_name == 'path':
            element_path = property_value

        elif property_name == 'type':
            # This is a translation dict for all the element types that appear in the RFC
            element_type = {
                'Master Element': EbmlElementType.Master,
                'Unsigned Integer': EbmlElementType.UInt,
                'String': EbmlElementType.AsciiString,
                'Binary': EbmlElementType.Binary
            }[property_value]

        elif property_name == 'description':
            # Treat the 'description' field as documentation of type 'definition'
            documentation.append(EbmlDocumentationEntry(EbmlDocumentationType.Definition, property_value))

        elif property_name == 'range':
            value_constraints = parse_range_attribute(property_value, element_type)

        elif property_name == 'length':
            element_length = parse_length_attribute(property_value)

        elif property_name == 'minOccurs':
            min_occurs = int(property_value)

        elif property_name == 'maxOccurs':
            max_occurs = int(property_value)

        elif property_name == 'default':
            default_value = parse_value_by_type(property_value, element_type)

        else:
            raise Exception('Got an unexpected attribute', property_name)

    return EbmlElement(
        name=element_name,
        id=element_id,
        type=element_type,
        path=element_path,
        max_occurs=max_occurs,
        min_occurs=min_occurs,
        default_value=default_value,
        value_constraints=value_constraints,
        length=element_length,
        documentation=documentation,
    )


def get_generic_ebml_elements() -> EbmlElements:
    """
    Get the EBML elements described in the EBML RFC
    """
    schema_root = ElementTree.fromstring(requests.get(EBML_RFC_ADDRESS).content.decode())
    element_semantics_element = schema_root.find('./middle/section[@anchor="elements-semantics"]')

    # The RFC document has two sections that describe EBML elements. Lucky for us, they are described in the same format
    ebml_header_elements = element_semantics_element.findall('./section[@anchor="ebml-header-elements"]/section')
    global_ebml_elements = element_semantics_element.findall('./section[@anchor="global-elements"]/section')

    elements = []
    for element_section_element in ebml_header_elements + global_ebml_elements:
        elements.append(parse_element_from_ebml_rfc(element_section_element))

    return EbmlElements(
        global_elements = [parse_element_from_ebml_rfc(element) for element in global_ebml_elements],
        local_elements = [parse_element_from_ebml_rfc(element) for element in ebml_header_elements]
    )


def get_elements_from_ebml_schema(schema_file_data: str) -> List[EbmlElement]:
    """
    Get the elements described by an EBML schema
    """
    # Remove XML namespace in order to not have to deal with the prefix on each tag name
    schema_root = ElementTree.fromstring(re.sub(' xmlns=".+?"', '', schema_file_data, count=1))

    # A list that contains all ebml elements
    # it's initialized with header elements that don't appear in the schema
    schema_elements = []

    for element in schema_root:
        # Load the element type to correctly parse default values and constraints
        element_type = EbmlElementType(element.attrib['type'])

        # Load some optional attributes
        element_length = None
        if 'length' in element.attrib:
            element_length = parse_length_attribute(element.attrib['length'])

        is_recurring = False
        if 'recurring' in element.attrib:
            is_recurring = bool(int(element.attrib['recurring']))

        is_recursive = False
        if 'recursive' in element.attrib:
            is_recursive = bool(int(element.attrib['recursive']))

        default_value = None
        if 'default' in element.attrib:
            default_value = parse_value_by_type(element.attrib['default'], element_type)

        min_occurs = 0
        if 'minOccurs' in element.attrib:
            min_occurs = int(element.attrib['minOccurs'])

        max_occurs = None
        if 'maxOccurs' in element.attrib:
            max_occurs = int(element.attrib['maxOccurs'])

        # Find value constraints
        value_constraints = None
        restriction_element = element.find('restriction')
        if restriction_element:
            value_constraints = []
            for enum_element in restriction_element.findall('enum'):
                value_constraints.append(
                    EbmlEnumConstraint(
                        enum_element.attrib['label'],
                        parse_value_by_type(enum_element.attrib['value'], element_type),
                        extract_documentation_from_html_element(enum_element)
                    )
                )
            element_type = EbmlElementType.Enum

        # Find range constraints
        elif 'range' in element.attrib:
            value_constraints = parse_range_attribute(element.attrib['range'].strip(), element_type)

        # If the current element qualifies for a flag element, change
        # the type and remove the value constraints
        if type(value_constraints) == EbmlRangeDescriptor and \
           element_type in [EbmlElementType.Int, EbmlElementType.UInt] and \
           value_constraints and \
           value_constraints.lower_bound and \
           value_constraints.upper_bound and \
           value_constraints.lower_bound.is_inclusive and \
           value_constraints.lower_bound.boundary_value == 0 and \
           value_constraints.upper_bound.is_inclusive and \
           value_constraints.upper_bound.boundary_value == 1:
            value_constraints = None
            element_type = EbmlElementType.Flag

        schema_elements.append(EbmlElement(
            name                = element.attrib['name'],
            id                  = element.attrib['id'],
            type                = element_type,
            path                = element.attrib['path'],
            max_occurs          = max_occurs,
            min_occurs          = min_occurs,
            default_value       = default_value,
            value_constraints   = value_constraints,
            length              = element_length,
            documentation       = extract_documentation_from_html_element(element),
            is_recursive        = is_recursive,
            is_recurring        = is_recurring
        ))

    return schema_elements


def build_element_tree(elements: List[EbmlElement]) -> Tuple[EbmlElement, Optional[List[object]]]:
    # Sort the elements by their path, this significantly simplifies the procedure
    # of building the tree because all children elements will appear after their parents
    elements.sort(key=lambda element: element.path)

    from pprintpp import pprint
    #pprint([a.path for a in elements])

    # Recursive function for obtaining a list of children of a certain element
    def _get_children(element: EbmlElement, potential_children: List[EbmlElement]) -> Optional[List[Tuple[EbmlElement, object]]]:
        children = []
        for i, potential_child in enumerate(potential_children):
            if potential_child.path.rsplit('\\', maxsplit=1)[0] == element.path or \
               (element.path == '\\' and potential_child.path.count('\\') == 1):
                children.append((potential_child, _get_children(potential_child, potential_children[i+1:])))

        return children if (len(children) > 0) else None

    return (elements[0], _get_children(elements[0], elements[1:]))


def get_matroska_ebml_elements() -> Tuple[EbmlElement, Optional[List[object]]]:
    """
    Returns a recursive structure that represents a tree of elements.
    Example of returned result:
    (RootElement, [
        (RootChild1, [(RootChildChild1, None)]),
        (RootChild2, None)
    ])
    """
    generic_ebml_elements = get_generic_ebml_elements()
    matroska_elements = [EbmlElement('Root', '', EbmlElementType.Master, '\\', 1, 1)] + \
                        get_elements_from_ebml_schema(requests.get(MATROSKA_EBML_SCHEMA_ADDRESS).content.decode())

    all_elements = matroska_elements.copy()

    # Only add generic EBML elements that are not overriden by the Matroska elements
    for generic_element in generic_ebml_elements.local_elements:
        if all(generic_element.id != matroska_element.id for matroska_element in matroska_elements):
            all_elements.append(generic_element)

    return build_element_tree(all_elements)


def string_to_cpp_var_name(string: str) -> str:
    """
    Converts a string to a C++ CamelCase variable name
    """
    string = string.lower()

    # Append an underscore if it starts with a digit
    if string[0].isdigit():
        string = '_' + string

    # Replace some special characters while making the name as readable as possible
    string = string.replace('/', ' or ').replace(' - ', ' to ').replace('.', '_')

    # Turn into UpperCamelCase
    string = re.sub(r'\b([A-Za-z])', lambda match: match[1].upper(), string)

    # Remove the rest of the special characters
    string = re.sub(r'\W', '', string)
    return string


def get_ebml_elements_string(element: 1):
    enum_string = ''
        
    element.name = element.name.replace('-', '_')
    element_string = f'DECL_ELEMENT_ID({element.name}, {hex(element.id)});'

    if element.possible_enum_values is not None:
        enum_string = 'enum class ' + element.name + ' {\n'
        for name, value in element.possible_enum_values.items():
            # Make enum name start with a valid character for C++ enum names=
            enum_string += ' ' * 4 + string_to_cpp_var_name(name)
            enum_string += f' = {repr(value)},\n'

        # cut out last ',\n'
        enum_string = enum_string[:-2] + '\n' + '};'

        # elegantly comment-out non-number elements to remind myself to handle it in the future
        if not all(type(value)==int for value in element.possible_enum_values.values()):
            enum_string = f'/*{enum_string}*/'
        enum_string += '\n'

    return element_string, enum_string


def main():
    # Download newest schema
    matroska_ebml_schema = requests.get(MATROSKA_EBML_SCHEMA_ADDRESS).content.decode()
    elements = get_elements_from_ebml_schema(matroska_ebml_schema)

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
    get_ebml_elements()
    exit()
    main()
