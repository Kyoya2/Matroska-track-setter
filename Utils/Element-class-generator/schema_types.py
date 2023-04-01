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
from enum import Enum
from datetime import datetime
from typing import NamedTuple, Optional, Union, List

# Basic EBML types
EbmlPrimitiveTypes = Union[int, float, str, datetime, bytes]

#####################################################
################### Documentation ###################
#####################################################
class EbmlDocumentationType(Enum):
    Definition = 'definition'
    Rationale  = 'rationale'
    UsageNotes = 'usage notes'
    references = 'references'


class EbmlDocumentationEntry(NamedTuple):
    documentation_type: EbmlDocumentationType
    documentation: str

EbmlDocumentation = List[EbmlDocumentationEntry]


#####################################################
################# Value constraints #################
#####################################################
# Types of elements  that can have the 'range' attribute
EbmlRangeSupportingTypes = Union[int, float, datetime]


# Represents a constraint that allows all possible values except a single value
class EbmlSingleValueConstraint(NamedTuple):
    value: EbmlRangeSupportingTypes

    # True if the constraint only allows the given value.
    # False if the constraint allows any value except the given value.
    is_inclusive: bool


class EbmlBoundaryDescriptor(NamedTuple):
    # The value of the boundary
    boundary_value: EbmlRangeSupportingTypes

    # Is the value of the boundary included within the range
    is_inclusive: bool


class EbmlRangeDescriptor(NamedTuple):
    lower_bound: Optional[EbmlBoundaryDescriptor] = None
    upper_bound: Optional[EbmlBoundaryDescriptor] = None


class EbmlEnumConstraint(NamedTuple):
    label: str
    value: EbmlPrimitiveTypes
    documentation: EbmlDocumentation


EbmlValueConstraintType = Union[
        EbmlRangeDescriptor,        # The value has to be in a certain range of values, the range may have one or two boundaries
        EbmlSingleValueConstraint,  # The value is either constant or can have any value except some given value
        List[EbmlEnumConstraint]    # The element has a defined set of values
    ]

# The length of an element is either a constant value or an integer in some range of values
EbmlLengthType = Union[EbmlRangeDescriptor, int]


class EbmlElementType(Enum):
    """
    Types of available enum element values
    """
    Int = 'integer'
    UInt = 'uinteger'
    Float = 'float'
    AsciiString = 'string'
    Utf8String = 'utf-8'
    Date = 'date'
    Binary = 'binary'
    Master = 'master'

    # Special types that are not defined in EBML but are convenient to use
    Flag = '#BOOL'  # Uint or Int with a value range of 0-1
    Enum = '#ENUM'  # Any type that has a restriction for specific values


class EbmlElement(NamedTuple):
    """
    https://www.rfc-editor.org/rfc/rfc8794.html#section-11.1.6
    """
    name: str
    id: str  # The hex representation of the ID
    type: EbmlElementType

    # The path to the element within an EBML file
    path: str

    # The maximum permitted number of occurrences of this element within its parent
    max_occurs: Optional[int] = None

    # The minimum permitted number of occurrences of this element within its parent
    min_occurs: int = 0

    # The default value of the element when it's not present
    default_value: Optional[EbmlPrimitiveTypes] = None

    # Range of possible values
    value_constraints: Optional[EbmlValueConstraintType] = None

    # The length in bytes of the element's data (currently appears only in binary elements)
    length: Optional[EbmlLengthType] = None

    # A list of documentation entries that give information about the element
    documentation: EbmlDocumentation = None

    # Can this element store more instances of itself (relevant only to master elements)
    is_recursive: bool = False

    # Can multiple IDENTICAL copies of the element appear
    is_recurring: bool = False

    # Can the element have an unknown size
    is_unknown_size_allowed: bool = False


class EbmlElements(NamedTuple):
    # Elements that can appear anywhere in an EBML document
    global_elements: List[EbmlElement]

    # Elements that can only appear as children of other specific elements
    local_elements: List[EbmlElement]
