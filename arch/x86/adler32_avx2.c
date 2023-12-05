/* adler32_avx2.c -- compute the Adler-32 checksum of a data stream
 * Copyright (C) 1995-2022 Mark Adler
 * Authors:
 *   Brian Bockelman <bockelman@gmail.com>
 * For conditions of distribution and use, see copyright notice in zlib.h
 */

#include "../../zutil.h"
#ifdef X86_AVX2

#include <immintrin.h>

#include "adler32_avx2_tpl.h"

#define COPY
#include "adler32_avx2_tpl.h"

#endif
