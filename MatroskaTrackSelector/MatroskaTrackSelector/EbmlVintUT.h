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
#include "UTCommon.h"
#include "EbmlElementLength.h"
#include "EbmlElementID.h"

#include <ios>
#include <fstream>

namespace EbmlVintUT
{
    void run_tests()
    {
        WriteLine("EbmlVint tests");

        // 10 test numbers of all possible encodable sizes (1-8 bytes) including highest and lowest
        constexpr std::array<std::array<uint64_t, 10>, 8> test_numers
        {{  // Lowest                Highest                       Random . . .
            {(uint64_t)1 << (7 * 0), ((uint64_t)1 << (7 * 1)) - 1, 0, 21, 23, 33, 40, 48, 63, 104},
            {(uint64_t)1 << (7 * 1), ((uint64_t)1 << (7 * 2)) - 1, 2145, 2611, 5116, 5713, 6920, 7183, 8527, 13726},
            {(uint64_t)1 << (7 * 2), ((uint64_t)1 << (7 * 3)) - 1, 20192, 30931, 194895, 325646, 360101, 411640, 584949, 1020706},
            {(uint64_t)1 << (7 * 3), ((uint64_t)1 << (7 * 4)) - 1, 60760031, 74896690, 85532447, 162698622, 209156049, 230218164, 237236699, 247558183},
            {(uint64_t)1 << (7 * 4), ((uint64_t)1 << (7 * 5)) - 1, 7248751067, 7796102206, 16253194168, 16838031476, 19637100865, 21856134694, 31802121689, 32163113226},
            {(uint64_t)1 << (7 * 5), ((uint64_t)1 << (7 * 6)) - 1, 948972099695, 1147755987023, 1280105707974, 2971872828217, 3358800559283, 3781701395214, 4117206037367, 4339859932640},
            {(uint64_t)1 << (7 * 6), ((uint64_t)1 << (7 * 7)) - 1, 25096682569717, 65988423884461, 104265902063787, 312867211253539, 320614950036023, 349722492589874, 358762174973963, 368474031442049},
            {(uint64_t)1 << (7 * 7), ((uint64_t)1 << (7 * 8)) - 1, 12730655342155177, 13501103592526957, 16116897341298376, 24267091028906911, 29389454369744868, 44330399345006307, 55889445115127876, 59423846566273419}
        }};

        // Init test file
        std::fstream test_file("test_file.bin", std::ios_base::binary | std::ios_base::out | std::ios_base::in | std::ios_base::trunc);
        std::array<uint32_t, 9> stream_position_indices;

        for (uint64_t i = 0; i < test_numers.size(); ++i)
        {
            WriteLine2("Number group " << i);
            for (uint64_t test_number : test_numers[i])
            {
                WriteLine3(test_number);

                uint64_t value_with_marker = test_number | ((uint64_t)1 << (7 * (i + 1)));

                EbmlElementLength element_length = test_number;
                CHECK(element_length == test_number); // Sanity
                CHECK(i + 1 == element_length.get_minimal_encoded_size());// Check minimal size

                test_file.seekp(0);

                // Test the ID only if the current number group supports its' size
                if (i + 1 <= sizeof(EbmlElementIDType))
                {
                    EbmlElementID element_id = static_cast<EbmlElementIDType>(value_with_marker);
                    CHECK(element_id == value_with_marker);
                    CHECK(EbmlVintUtils::remove_vint_marker(element_id) == test_number); // Remove marker
                    CHECK(i + 1 == element_id.get_encoded_size());

                /************************************ TESTING USING FILE ************************************/

                    // Encoding the VINT with the marker using original length
                    test_file << element_id;
                    stream_position_indices[0] = (uint32_t)test_file.tellp();

                    test_file.seekg(0);
                    // Decoding and checking the VINT with the marker
                    test_file >> element_id;
                    CHECK(i + 1 == element_id.get_encoded_size());
                    CHECK(element_id == value_with_marker);

                    test_file.seekp(0);
                }

                for (uint32_t j = (uint32_t)i + 1; j <= sizeof(EbmlElementLengthType); ++j)
                {
                    WriteLine4("Encoding at length " << j);

                    // Encode to file and remember stream position
                    element_length.write(test_file, j);
                    stream_position_indices[j] = (uint32_t)test_file.tellp();
                }
                
                test_file.seekg(0);
                for (uint32_t j = (uint32_t)i + 1; j <= sizeof(EbmlElementLengthType); ++j)
                {
                    WriteLine4("Decoding at length " << j);

                    // Read from file and verify stream positions
                    test_file >> element_length;

                    CHECK(stream_position_indices[j] == test_file.tellg());

                    // Check value
                    CHECK(element_length.get_value() == test_number);

                    // Check sizes
                    CHECK(j == element_length.get_encoded_size());
                    CHECK(i + 1 == element_length.get_minimal_encoded_size());
                }
            }
        }
    }
}