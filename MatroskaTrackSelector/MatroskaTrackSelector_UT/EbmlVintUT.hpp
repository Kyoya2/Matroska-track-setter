#include "UTCommon.hpp"

#define private public
#include "EbmlVint.h"

namespace EbmlVintUT
{

    void run_tests()
    {
        WriteLine("EbmlVint tests");

        // 20 test numbers of all possible encodable sizes (1-7 bytes) including highest and lowest
        constexpr array<array<uint64_t, 20>, 7> test_numers
        {{  // Lowest                Highest                       Random . . .
            {(uint64_t)1 << (7 * 0), ((uint64_t)1 << (7 * 1)) - 1, 0, 6, 12, 38, 39, 63, 66, 75, 79, 85, 94, 106, 109, 110, 113, 118, 119, 126},
            {(uint64_t)1 << (7 * 1), ((uint64_t)1 << (7 * 2)) - 1, 344, 1258, 1726, 1850, 2670, 3731, 4069, 4941, 8031, 8059, 8154, 9574, 11041, 11987, 12397, 13735, 14314, 14387},
            {(uint64_t)1 << (7 * 2), ((uint64_t)1 << (7 * 3)) - 1, 282383, 369707, 527002, 544295, 697924, 766381, 829295, 904494, 1084195, 1102163, 1284567, 1412491, 1458529, 1540381, 1554385, 1619442, 1692230, 2094911},
            {(uint64_t)1 << (7 * 3), ((uint64_t)1 << (7 * 4)) - 1, 30941096, 40242832, 53344747, 87263653, 103606745, 125765211, 127295766, 149243257, 159617931, 173255854, 190049517, 200751327, 202454090, 204947427, 244181730, 256084297, 258507919, 267626934},
            {(uint64_t)1 << (7 * 4), ((uint64_t)1 << (7 * 5)) - 1, 4396930618, 4932096994, 5517407689, 5751543178, 6656613332, 7177549870, 7285656667, 8265809759, 8372419204, 10500762302, 10654861128, 13020989791, 18467861653, 20062413224, 20593554326, 23278062372, 27518318202, 32188437251},
            {(uint64_t)1 << (7 * 5), ((uint64_t)1 << (7 * 6)) - 1, 36179364208, 547468931147, 832188127539, 1073607087742, 1153075541102, 1503870319197, 1515742034173, 2216009389489, 2250301607708, 2349425676110, 2528182596175, 2642358148140, 2999771855865, 3115379634907, 3368143188025, 3378068558223, 4136534312620, 4242814309487},
            {(uint64_t)1 << (7 * 6), ((uint64_t)1 << (7 * 7)) - 1, 22901212075985, 48378207147389, 59891251192781, 71996117941362, 97536513290462, 118682338373531, 130700646706090, 134989253970622, 167914607363539, 187759699830931, 199758124950051, 200985149069771, 268014717834237, 296906899531551, 329422502702055, 481030464057176, 490839924807192, 550620692848821}
        }};

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

                // Minimal size
                CHECK(i + 1 == without_marker.m_minimal_encoded_size);
                CHECK(i + 1 == with_marker.m_minimal_encoded_size);
            }
        }
    }

    void no_marker()
    {

    }

}