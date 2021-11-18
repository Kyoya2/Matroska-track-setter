#include "EbmlVintUT.h"
#include "BasicSharedPtrUT.h"
#include "EbmlParserUT.h"

int wmain(int argc, wchar_t* argv[])
{
    argc;
    argv;
    //EbmlVintUT::run_tests();
    //BasicSharedPtrUT::run_tests();
    EbmlParserUT::run_tests();

    if (MatroskaTrackSelectorUT::tests_passed)
        WriteLine(endl << "All test passed!");
    else
        WriteLine(endl << "Some tests FAILED :(");
}