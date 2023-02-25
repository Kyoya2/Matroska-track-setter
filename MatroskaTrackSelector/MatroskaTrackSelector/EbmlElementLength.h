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
#pragma once
#include <algorithm>

#include "Common.h"
#include "EbmlVintUtils.h"

using EbmlElementLengthType = uint64_t;

class EbmlElementLength
{
public:
    EbmlElementLength(EbmlElementLengthType value);
    explicit EbmlElementLength(std::istream& stream);

    EbmlElementLength(const EbmlElementLength& other) = default;
    EbmlElementLength& operator=(const EbmlElementLength& other) = default;

public:
    inline EbmlElementLengthType get_value() const { return m_value; }
    inline size_t get_minimal_encoded_size() const { return m_minimal_encoded_size; }
    inline size_t get_encoded_size() const { return m_encoded_size; }

    void write(std::ostream& stream, size_t encoded_length = 0) const;

    inline operator EbmlElementLengthType() const;

    friend std::ostream& operator<<(std::ostream& stream, const EbmlElementLength& element_length);
    friend std::istream& operator>>(std::istream& stream, EbmlElementLength& element_length);

PRIVATE:
    mutable size_t m_encoded_size; // Changes based on last write/read
    EbmlElementLengthType m_value;
    size_t m_minimal_encoded_size;
};


inline EbmlElementLength::operator EbmlElementLengthType() const
{
    return m_value;
}