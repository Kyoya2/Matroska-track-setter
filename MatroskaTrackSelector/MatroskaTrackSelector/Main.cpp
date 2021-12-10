#include <windows.h>

#ifdef _DEBUG
#include "EbmlVintUT.h"
#include "BasicSharedPtrUT.h"
#include "EbmlParserUT.h"
#include "MatroskaLanguageTagsUT.h"
#include "TrackParserUT.h"

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

    // This is required for ConsoleUtils::print_table
    SetConsoleOutputCP(CP_UTF8);

#ifdef _DEBUG
    EbmlVintUT::run_tests();
    BasicSharedPtrUT::run_tests();
    EbmlParserUT::run_tests();
    MatroskaLanguageTagsUT::run_tests();
    TrackParserUT::run_tests();


    WriteLine(endl << "Creations: " << BasicSharedPtrStats::total_creations);
    WriteLine("Deletions: " << BasicSharedPtrStats::total_deletions);

    if (MatroskaTrackSelectorUT::tests_passed)
        WriteLine(endl << "All test passed!");
    else
        WriteLine(endl << "Some tests FAILED :(");
#endif
}