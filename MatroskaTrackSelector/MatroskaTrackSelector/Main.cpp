#include "EbmlVintUT.h"

int wmain(int argc, wchar_t* argv[])
{
    EbmlVintUT::run_tests();

    if (MatroskaTrackSelectorUT::tests_passed)
        WriteLine(endl << "All test passed!");
    else
        WriteLine(endl << "Some tests FAILED :(");
}