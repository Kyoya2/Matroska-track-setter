#include "UTCommon.hpp"

#include <ios>
#include <fstream>

#define private public
#include "EbmlVint.h"

namespace EbmlVintUT
{
    void run_tests()
    {
        WriteLine("EbmlVint tests");

        // 10 test numbers of all possible encodable sizes (1-8 bytes) including highest and lowest
        constexpr array<array<uint64_t, 10>, 8> test_numers
        {{  // Lowest                Highest                       Random . . .
            {(uint64_t)1 << (7 * 0), ((uint64_t)1 << (7 * 1)) - 1, 3, 21, 23, 33, 40, 48, 63, 104},
            {(uint64_t)1 << (7 * 1), ((uint64_t)1 << (7 * 2)) - 1, 2145, 2611, 5116, 5713, 6920, 7183, 8527, 13726},
            {(uint64_t)1 << (7 * 2), ((uint64_t)1 << (7 * 3)) - 1, 20192, 30931, 194895, 325646, 360101, 411640, 584949, 1020706},
            {(uint64_t)1 << (7 * 3), ((uint64_t)1 << (7 * 4)) - 1, 60760031, 74896690, 85532447, 162698622, 209156049, 230218164, 237236699, 247558183},
            {(uint64_t)1 << (7 * 4), ((uint64_t)1 << (7 * 5)) - 1, 7248751067, 7796102206, 16253194168, 16838031476, 19637100865, 21856134694, 31802121689, 32163113226},
            {(uint64_t)1 << (7 * 5), ((uint64_t)1 << (7 * 6)) - 1, 948972099695, 1147755987023, 1280105707974, 2971872828217, 3358800559283, 3781701395214, 4117206037367, 4339859932640},
            {(uint64_t)1 << (7 * 6), ((uint64_t)1 << (7 * 7)) - 1, 25096682569717, 65988423884461, 104265902063787, 312867211253539, 320614950036023, 349722492589874, 358762174973963, 368474031442049},
            {(uint64_t)1 << (7 * 7), ((uint64_t)1 << (7 * 8)) - 1, 12730655342155177, 13501103592526957, 16116897341298376, 24267091028906911, 29389454369744868, 44330399345006307, 55889445115127876, 59423846566273419}
        }};

        // Init test file
        std::fstream test_file;
        test_file.open("test_file.txt", std::ios_base::binary | std::ios_base::out | std::ios_base::in | std::ios_base::trunc);

        for (uint64_t i = 0; i < test_numers.size(); ++i)
        {
            WriteLine2("Number group " << i);
            for (uint64_t test_number : test_numers[i])
            {
                WriteLine3(test_number);

                uint64_t value_with_marker = test_number | ((uint64_t)1 << (7 * (i + 1)));

                EbmlVint<false> without_marker = test_number;
                EbmlVint<true> with_marker = value_with_marker;

                // Sanity
                CHECK(without_marker.m_value == test_number);
                CHECK(with_marker.m_value == value_with_marker);

                // Remove marker
                CHECK(with_marker._s_remove_vint_marker(with_marker.m_value) == test_number);

                // Check minimal size
                CHECK(i + 1 == without_marker.m_minimal_encoded_size);
                CHECK(i + 1 == with_marker.m_minimal_encoded_size);

                // Write to file
                size_t mid_pos = 0;
                size_t end_pos = 0;
                test_file.seekp(0);

                without_marker.write(test_file);
                mid_pos = test_file.tellp();
                with_marker.write(test_file);
                end_pos = test_file.tellp();

                // Read from file in reversed order and verify stream positions
                test_file.seekg(0);
                with_marker = EbmlVint<true>(test_file);
                CHECK(mid_pos == test_file.tellg());
                without_marker = EbmlVint<false>(test_file);
                CHECK(end_pos == test_file.tellg());

                // Check values
                CHECK(without_marker.m_value == test_number);
                CHECK(with_marker.m_value == value_with_marker);

                // Check minimal size
                CHECK(i + 1 == without_marker.m_minimal_encoded_size);
                CHECK(i + 1 == with_marker.m_minimal_encoded_size);
            }
        }

        EbmlVint<false> qwe = 0;
        cout << qwe;

    }

    void no_marker()
    {

    }

}