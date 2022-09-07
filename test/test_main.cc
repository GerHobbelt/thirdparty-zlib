/* test_test.cc - Main entry point for test framework */

#include <stdio.h>

#include "gtest/gtest.h"

extern "C" {
#  include "zbuild.h"
#  include "cpu_features.h"
}

#include "monolithic_examples.h"


#if defined(BUILD_MONOLITHIC)
#define main      zlib_unittests_main
#endif

GTEST_API_ int main(int argc, const char **argv) {
  printf("Running main() from %s\n", __FILE__);
  cpu_check_features();
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
