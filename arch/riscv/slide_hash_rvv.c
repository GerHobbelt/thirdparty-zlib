/* slide_hash_rvv.c - RVV version of slide_hash
 * Copyright (C) 2023 SiFive, Inc. All rights reserved.
 * Contributed by Alex Chiang <alex.chiang@sifive.com>
 * For conditions of distribution and use, see copyright notice in zlib.h
 */

#include "../../zbuild.h"
#include "../../deflate.h"

#ifdef RISCV_RVV

#include <riscv_vector.h>

static inline void slide_hash_chain(Pos *table, uint32_t entries, uint16_t wsize) {
    size_t vl;
    while (entries > 0) {
        vl = __riscv_vsetvl_e16m4(entries);
        vuint16m4_t v_tab = __riscv_vle16_v_u16m4(table, vl);
        vuint16m4_t v_diff = __riscv_vsub_vx_u16m4(v_tab, wsize, vl);
        vbool4_t mask = __riscv_vmsltu_vx_u16m4_b4(v_tab, wsize, vl);
        v_tab = __riscv_vmerge_vxm_u16m4(v_diff, 0, mask, vl);
        __riscv_vse16_v_u16m4(table, v_tab, vl);
        table += vl, entries -= vl;
    }
}

Z_INTERNAL void slide_hash_rvv(deflate_state *s) {
    uint16_t wsize = (uint16_t)s->w_size;

    slide_hash_chain(s->head, HASH_SIZE, wsize);
    slide_hash_chain(s->prev, wsize, wsize);
}

#endif // RISCV_RVV
