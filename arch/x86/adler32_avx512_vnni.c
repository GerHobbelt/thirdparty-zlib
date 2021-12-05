/* adler32_avx512_vnni.c -- compute the Adler-32 checksum of a data stream
 * Based on Brian Bockelman's AVX2 version
 * Copyright (C) 1995-2011 Mark Adler
 * Authors:
 *   Adam Stylinski <kungfujesus06@gmail.com>
 *   Brian Bockelman <bockelman@gmail.com>
 * For conditions of distribution and use, see copyright notice in zlib.h
 */

#include "../../zbuild.h"
#include "../../zutil.h"

#include "../../adler32_p.h"

#include <immintrin.h>

#ifdef X86_AVX512VNNI_ADLER32

Z_INTERNAL uint32_t adler32_avx512_vnni(uint32_t adler, const unsigned char *buf, size_t len) {
    uint32_t sum2;

     /* split Adler-32 into component sums */
    sum2 = (adler >> 16) & 0xffff;
    adler &= 0xffff;

    /* in case user likes doing a byte at a time, keep it fast */
    if (UNLIKELY(len == 1))
        return adler32_len_1(adler, buf, sum2);

    /* initial Adler-32 value (deferred check for len == 1 speed) */
    if (UNLIKELY(buf == NULL))
        return 1L;

    /* in case short lengths are provided, keep it somewhat fast */
    if (UNLIKELY(len < 16))
        return adler32_len_16(adler, buf, len, sum2);

    const __mmask16 vs_mask = 1U << 15;
    __m512i vs1 = _mm512_maskz_set1_epi32(vs_mask, adler);
    __m512i vs2 = _mm512_maskz_set1_epi32(vs_mask, sum2);

    const __m512i dot2v = _mm512_set_epi8(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
                                          20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37,
                                          38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55,
                                          56, 57, 58, 59, 60, 61, 62, 63, 64);

    const __m512i zero = _mm512_setzero_si512();

    while (len >= 64) {
        int k = (len < NMAX ? (int)len : NMAX);
        k -= k % 64;
        len -= k;
        __m512i vs1_0 = vs1;
        __m512i vs3 = _mm512_setzero_si512();

        /* Manually unrolled this loop by 2 for an decent amount of ILP */
        while (k >= 128) {
            /*
               vs1 = adler + sum(c[i])
               vs2 = sum2 + 64 vs1 + sum( (64-i+1) c[i] )
            */
            __m512i vbuf0 = _mm512_loadu_si512(buf);
            __m512i vbuf1 = _mm512_loadu_si512(buf+64);
            buf += 128;
            k -= 128;

            __m512i vs1_sad = _mm512_sad_epu8(vbuf0, zero);
            vs1 = _mm512_add_epi32(vs1, vs1_sad);
            vs3 = _mm512_add_epi32(vs3, vs1_0);
            /* multiply-add, resulting in 16 ints. Fuse with sum stage from prior versions, as we now have the dp
             * instructions to eliminate them */
            vs2 = _mm512_dpbusd_epi32(vs2, vbuf0, dot2v);
            vs1_0 = vs1;

            vs1_sad = _mm512_sad_epu8(vbuf1, zero);
            vs1 = _mm512_add_epi32(vs1, vs1_sad);
            vs3 = _mm512_add_epi32(vs3, vs1_0);
            vs2 = _mm512_dpbusd_epi32(vs2, vbuf1, dot2v);
            vs1_0 = vs1;
        }

        /* Remainder peeling */
        while (k >= 64) {
            __m512i vbuf = _mm512_loadu_si512(buf);
            buf += 64;
            k -= 64;

            __m512i vs1_sad = _mm512_sad_epu8(vbuf, zero);
            vs1 = _mm512_add_epi32(vs1, vs1_sad);
            vs3 = _mm512_add_epi32(vs3, vs1_0);
            vs2 = _mm512_dpbusd_epi32(vs2, vbuf, dot2v);
            vs1_0 = vs1;
        }

        vs3 = _mm512_slli_epi32(vs3, 6);
        vs2 = _mm512_add_epi32(vs2, vs3);

        adler = _mm512_reduce_add_epi32(vs1) % BASE;
        vs1 = _mm512_maskz_set1_epi32(vs_mask, adler);
        sum2 = _mm512_reduce_add_epi32(vs2) % BASE;
        vs2 = _mm512_maskz_set1_epi32(vs_mask, sum2);
    }

    /* Process tail (len < 16).  */
    return adler32_len_16(adler, buf, len, sum2);
}

#endif
