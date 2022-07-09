/*
 *   Matroska track setter  Copyright (C) 2021  Kyoya2
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
#include "SeekEntry.h"

SeekEntry::SeekEntry(BasicSharedPtr<EbmlElement>& seek_element) :
    seek_element(seek_element),
    m_seek_position(0)
{
    assert(seek_element->get_id().get_value() == Seek_ID);

    unordered_map<EbmlElementIDType, BasicSharedPtr<EbmlElement>> children{
        {SeekID_ID, nullptr},
        {SeekPosition_ID, nullptr},
    };

    seek_element->get_unique_children(children);

    // Save element pointers
    seek_id_element = children[SeekID_ID];
    seek_position_element = children[SeekPosition_ID];

    // Load only the value of the seek ID
    seek_id = static_cast<EbmlElementIDType>(children[SeekID_ID]->get_uint_value());
}

uint64_t SeekEntry::get_seek_position()
{
    if (0 == m_seek_position)
        m_seek_position = seek_position_element->get_uint_value();

    return m_seek_position;
}
