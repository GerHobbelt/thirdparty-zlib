
#include "monolithic_examples.h"

#define USAGE_NAME   "sqlite3pp_tests"

#include "monolithic_main_internal_defs.h"

// declare your own monolith dispatch table:
MONOLITHIC_CMD_TABLE_START()
{ "report", { .f = zlib_report_example_main } },
{ "test_example", { .fa = zlib_test_example_main } },
{ "gh1235", { .f = zlib_gh1235_test_main } },
{ "infcover", { .f = zlib_infcover_test_main } },
{ "mini_deflate", { .fa = zlib_mini_deflate_main } },
{ "mini_gzip", { .fa = zlib_mini_gzip_main } },
{ "switchlevels", { .fa = zlib_switchlevels_main } },
{ "unittests", { .fa = zlib_unittests_main } },
{ "mk_crc32_tables", { .f = zlib_mk_crc32_tables_main } },
{ "mk_fixed_table", { .f = zlib_mk_fixed_table_main } },
{ "mk_trees_header", { .f = zlib_mk_trees_header_main } },
MONOLITHIC_CMD_TABLE_END();

#include "monolithic_main_tpl.h"
