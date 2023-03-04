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

#include "Common.h"
#include "OldEbmlElement.h"

class SeekEntry
{
public:
    SeekEntry(OldEbmlElementPtr& seek_element);

    SeekEntry(const SeekEntry&) = delete;
    SeekEntry& operator=(const SeekEntry&) = delete;

    SeekEntry(SeekEntry&& other) noexcept = default;
    SeekEntry& operator=(SeekEntry&& other) noexcept = default;

public:
    uint64_t get_seek_position();
    void update_seek_position(uint64_t new_seek_position);

PRIVATE:
    OldEbmlElementPtr m_seek_element;
    OldEbmlElementPtr m_seek_id_element;
    OldEbmlElementPtr m_seek_position_element;
    EbmlElementIDType m_seek_id;
    uint64_t m_seek_position;
};

