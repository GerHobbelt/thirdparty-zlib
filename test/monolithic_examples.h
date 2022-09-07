
#pragma once

#if defined(BUILD_MONOLITHIC)

#ifdef __cplusplus
extern "C" {
#endif

int zlib_report_example_main(void);
int zlib_test_example_main(int cnt, const char **arr);
int zlib_gh1235_test_main(void);
int zlib_infcover_test_main(void);
int zlib_mini_deflate_main(int cnt, const char **arr);
int zlib_mini_gzip_main(int cnt, const char **arr);
int zlib_switchlevels_main(int cnt, const char **arr);
int zlib_unittests_main(int cnt, const char **arr);
int zlib_mk_crc32_tables_main(void);
int zlib_mk_fixed_table_main(void);
int zlib_mk_trees_header_main(void);

#ifdef __cplusplus
}
#endif

#endif
