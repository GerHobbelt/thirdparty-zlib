/* slide_hash_neon.c -- Optimized hash table shifting for ARM with support for NEON instructions
 * Copyright (C) 2017-2020 Mika T. Lindqvist
 *
 * Authors:
 * Mika T. Lindqvist <postmaster@raasu.org>
 * Jun He <jun.he@arm.com>
 *
 * For conditions of distribution and use, see copyright notice in zlib.h
 */

#if defined(ARM_NEON_SLIDEHASH)
#ifdef _M_ARM64
#  include <arm64_neon.h>
#else
#  include <arm_neon.h>
#endif
#include "../../zbuild.h"
#include "../../deflate.h"

/* SIMD version of hash_chain rebase */
static inline void slide_hash_chain(Pos *table, uint32_t entries, uint16_t wsize) {
    Z_REGISTER uint16x8_t v;
    uint16x8x4_t p0, p1;
    Z_REGISTER size_t n;

    size_t size = entries*sizeof(table[0]);
    Assert((size % sizeof(uint16x8_t) * 8 == 0), "hash table size err");

    Assert(sizeof(Pos) == 2, "Wrong Pos size");
    v = vdupq_n_u16(wsize);

    n = size / (sizeof(uint16x8_t) * 8);
    do {
        p0 = vld1q_u16_x4(table); 
        p1 = vld1q_u16_x4(table+32); 
        p0.val[0] = vqsubq_u16(p0.val[0], v);
        p0.val[1] = vqsubq_u16(p0.val[1], v);
        p0.val[2] = vqsubq_u16(p0.val[2], v);
        p0.val[3] = vqsubq_u16(p0.val[3], v);
        p1.val[0] = vqsubq_u16(p1.val[0], v);
        p1.val[1] = vqsubq_u16(p1.val[1], v);
        p1.val[2] = vqsubq_u16(p1.val[2], v);
        p1.val[3] = vqsubq_u16(p1.val[3], v);
        vst1q_u16_x4(table, p0);
        vst1q_u16_x4(table+32, p1);
        table += 64;
    } while (--n);
}

Z_INTERNAL void slide_hash_neon(deflate_state *s) {
    unsigned int wsize = s->w_size;

    slide_hash_chain(s->head, HASH_SIZE, wsize);
    slide_hash_chain(s->prev, wsize, wsize);
}
#endif
