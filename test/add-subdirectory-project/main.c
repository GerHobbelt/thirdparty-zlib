#include <stdio.h>
#include "zlib-ng.h"

#include "monolithic_examples.h"


#if defined(BUILD_MONOLITHIC)
#define main      zlib_report_example_main
#endif

int main(void) {
    printf("zlib-ng: %s\n", ZLIBNG_VERSION);
    return 0;
}
