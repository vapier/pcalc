#ifndef debug_defined
#define debug_defined

#include <stdio.h>

#define TEST 0
#define debug(args...) do { if (TEST) printf(args); } while (0)

#endif
