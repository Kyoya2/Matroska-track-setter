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

    friend std::ostream& operator<<(std::ostream& stream, const EbmlElementID& element_id);
    friend std::istream& operator>>(std::istream& stream, EbmlElementID& element_id);

PRIVATE:
    size_t m_encoded_size;
    EbmlElementIDType m_value;
};