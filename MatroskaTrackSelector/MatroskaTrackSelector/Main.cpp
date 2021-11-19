#include "EbmlVintUT.h"
#include "BasicSharedPtrUT.h"
#include "EbmlParserUT.h"

#ifdef _DEBUG
namespace BasicSharedPtrStats
{
    uint32_t total_creations = 0;
    uint32_t total_deletions = 0;
}
#endif

int wmain(int argc, wchar_t* argv[])
{
    // Unreferenced
    argc;
    argv;

    //EbmlVintUT::run_tests();
    //BasicSharedPtrUT::run_tests();
    EbmlParserUT::run_tests();

    WriteLine(endl << "Creations: " << BasicSharedPtrStats::total_creations);
    WriteLine("Deletions: " << BasicSharedPtrStats::total_deletions);

    if (MatroskaTrackSelectorUT::tests_passed)
        WriteLine(endl << "All test passed!");
    else
        WriteLine(endl << "Some tests FAILED :(");
}