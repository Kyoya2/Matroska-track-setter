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
#include "EbmlElementID.h"

EbmlElementID::EbmlElementID(EbmlElementIDType value) :
    m_encoded_size(EbmlVintUtils::get_minimal_encoded_size(value, true)),
    m_value(value)
{}

EbmlElementID::EbmlElementID(std::istream& stream) :
    m_encoded_size(0),
    m_value(EbmlVintUtils::extract_from_stream(stream, true, &m_encoded_size))
{}

void EbmlElementID::write(std::ostream& stream) const
{
    Utility::write_big_endian_to_stream(stream, m_value, m_encoded_size);
}

std::ostream& operator<<(std::ostream& stream, const EbmlElementID& element_id)
{
    element_id.write(stream);
    return stream;
}

std::istream& operator>>(std::istream& stream, EbmlElementID& element_id)
{
    element_id = EbmlElementID(stream);
    return stream;
}