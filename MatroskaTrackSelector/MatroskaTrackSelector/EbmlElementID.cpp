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
#include "EbmlElementID.h"

EbmlElementID::EbmlElementID(EbmlElementIDType value) :
    m_encoded_size(EbmlVintUtils::get_minimal_encoded_size(value, true)),
    m_value(value)
{}

EbmlElementID::EbmlElementID(std::istream& stream) :
    m_encoded_size(0),
    m_value(EbmlVintUtils::extract_from_stream<EbmlElementIDType>(stream, true, &m_encoded_size))
{}

void EbmlElementID::write(std::ostream& stream) const
{
    EbmlVintUtils::encode_and_write(m_value, m_encoded_size, stream);
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