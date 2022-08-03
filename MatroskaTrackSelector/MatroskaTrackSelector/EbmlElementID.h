/*   
 *   Matroska track setter  Copyright (C) 2022  Kyoya2
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
#include <algorithm>

#include "Common.h"
#include "EbmlVintUtils.h"

using EbmlElementIDType = uint32_t;

class EbmlElementID
{
public:
    EbmlElementID(EbmlElementIDType value);
    explicit EbmlElementID(std::istream& stream);

    EbmlElementID(const EbmlElementID& other) = default;
    EbmlElementID& operator=(const EbmlElementID& other) = default;

public:
    inline EbmlElementIDType get_value() const { return m_value; }
    inline size_t get_encoded_size() const { return m_encoded_size; }
    void write(std::ostream& stream) const;

    inline operator EbmlElementIDType() const;

    friend std::ostream& operator<<(std::ostream& stream, const EbmlElementID& element_id);
    friend std::istream& operator>>(std::istream& stream, EbmlElementID& element_id);

PRIVATE:
    size_t m_encoded_size;
    EbmlElementIDType m_value;
};


inline EbmlElementID::operator EbmlElementIDType() const
{
    return m_value;
}