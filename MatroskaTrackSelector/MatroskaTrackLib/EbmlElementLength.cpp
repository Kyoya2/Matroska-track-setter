/*   
 *   Matroska track setter  Copyright (C) 2023  Kyoya2
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
#include "EbmlElementLength.h"

EbmlElementLength::EbmlElementLength(EbmlElementLengthType value) :
    m_encoded_size(EbmlVintUtils::get_minimal_encoded_size(value, false)),
    m_value(value)
{}

EbmlElementLength::EbmlElementLength(std::istream& stream) :
    m_encoded_size(0),
    m_value(EbmlVintUtils::extract_from_stream(stream, false, &m_encoded_size))
{}

void EbmlElementLength::write(std::ostream& stream, size_t encoded_length) const
{
    if (0 == encoded_length)
    {
        encoded_length = m_encoded_size;
    }
    else if (encoded_length < get_minimal_encoded_size())
    {
        throw exception("Can't encode VINT to size smaller than minimum");
    }
    else if (encoded_length > sizeof(EbmlElementLengthType))
    {
        throw exception("Can't encode VINT to size bigger than maximum");
    }

    // Add marker to value
    EbmlElementLengthType encoded_value = m_value;
    encoded_value |= ((EbmlElementLengthType)1 << (7 * encoded_length));

    Utility::write_big_endian_to_stream(stream, encoded_value, encoded_length);

    // Update encoded size to match
    m_encoded_size = encoded_length;
}

std::ostream& operator<<(std::ostream& stream, const EbmlElementLength& element_length)
{
    element_length.write(stream);
    return stream;
}

std::istream& operator>>(std::istream& stream, EbmlElementLength& element_length)
{
    element_length = EbmlElementLength(stream);
    return stream;
}