/*
 * Copyright 2021 Kyoya2
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#pragma once
#include <algorithm>

#include "Common.h"
#include "EbmlVintUtils.h"

DECL_EXCEPTION(VINTEncodingError);

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

    friend std::ostream& operator<<(std::ostream& stream, const EbmlElementLength& element_length);
    friend std::istream& operator>>(std::istream& stream, EbmlElementLength& element_length);

PRIVATE:
    mutable size_t m_encoded_size; // Changes based on last write/read
    EbmlElementLengthType m_value;
    size_t m_minimal_encoded_size;
};