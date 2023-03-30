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
import re
from typing import Dict

# A dict that maps between a number in the range [1,6] that represents a section depth to a RegEx that locates a header
# in that depth and captures the header's name
_SECTION_HEADER_REGEX = {section_depth: re.compile(r'(?:\A\n*|\n+)#{' + str(section_depth) + r'} +([\w ]+)\n*') for section_depth in range(1, 7)}
def get_markdown_sections(markdown: str, section_depth: int) -> Dict[str, str]:
    """
    Get a list of [[section name, section content], [..., ...], ...] from a markdown string
    :param markdown: The Markdown string that contains the desired section
    :param section_depth: The number of '#' symbols before the headers of the desired sections
    """
    parts = _SECTION_HEADER_REGEX[section_depth].split(markdown)

    # The first part is what comes before the first header, cut it out because it's irrelevant
    parts = parts[1:]

    # The RegEx doesn't strip newlines from the end of the last part, so I do it manually
    parts[-1] = parts[-1].rstrip('\n')

    # Return the pairs in the desired format
    return {parts[i]: parts[i+1] for i in range(0, len(parts), 2)}


def get_markdown_section_content(markdown: str, section_header_name: str) -> str:
    """
    Return the content of the topmost section with the header equal to the given name
    """
    topmost_section_depth = min(
        len(header_prefix) for
        header_prefix in
        re.findall(r'^(#+) ', markdown, re.MULTILINE)
    )

    return get_markdown_sections(markdown, topmost_section_depth)[section_header_name]
