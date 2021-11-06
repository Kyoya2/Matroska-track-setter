#include "Common.h"

#define CHECK(condition) do{ if (!(condition)) {WriteLine("Error in file " << __FILE__ << ":" << __LINE__); MatroskaTrackSelectorUT::tests_passed = false;} } while(0, 0)

#define WriteLine1 WriteLine;
#define WriteLine2(something) WriteLine(".   " << something);
#define WriteLine3(something) WriteLine(".   .   " << something);
#define WriteLine4(something) WriteLine(".   .   .   " << something);

namespace MatroskaTrackSelectorUT
{
    bool tests_passed = true;
}