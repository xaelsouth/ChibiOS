/*
    ChibiOS - Copyright (C) 2006-2026 Giovanni Di Sirio.

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

/**
 * @file    ARM/devices/IMX23/imx23_early.c
 * @brief   i.MX23 very early initialization (exception vectors placement).
 *
 * @details The i.MX23 boot ROM executes from 0xFFFF0000 with the CPU in
 *          high-vector mode (CP15 c1 V=1). The ChibiOS image is linked at
 *          IMX23_RAM_ORIGIN (SDRAM, default 0x40000000) but the ARM
 *          exception table must live at 0x00000000 (V=0) or 0xFFFF0000
 *          (V=1, occupied by the ROM). The on-chip SRAM (OCRAM, 32KB) is
 *          mapped at 0x00000000, so the 8 exception vectors (32 bytes) are
 *          copied from the image base into OCRAM and the CPU is switched
 *          to low vectors. No MMU is required for this.
 *
 * @note    This runs as __early_init() from crt0.S, i.e. before .data/.bss
 *          are initialized: no initialized globals may be used here.
 *
 * @addtogroup ARM_SPECIFIC
 * @{
 */

#include <stdint.h>

#include "board.h"

#if !defined(IMX23_RAM_ORIGIN) || defined(__DOXYGEN__)
#define IMX23_RAM_ORIGIN        0x40000000
#endif

/**
 * @brief   Very early board/CPU initialization.
 * @note    Overrides the weak symbol in crt1.c.
 */
void __early_init(void) {

  /* Copy the 8 ARM exception vectors (32 bytes) from the image base
     (where the .vectors section is linked) to OCRAM at 0x00000000. */
  volatile uint32_t *src = (volatile uint32_t *)IMX23_RAM_ORIGIN;
  volatile uint32_t *dst = (volatile uint32_t *)0x00000000U;
  unsigned i;

  for (i = 0U; i < 8U; i++) {
    dst[i] = src[i];
  }

  /* Invalidate and disable the caches and the MMU: the bootstream may
     have left the D-cache on, which would break DMA/LCDIF coherency
     (no MMU is used, all SDRAM is identity-mapped). */
  {
    uint32_t c1;

    __asm__ volatile ("mcr p15, 0, %0, c7, c7, 0" : : "r" (0) : "memory");
    __asm__ volatile ("mrc p15, 0, %0, c1, c0, 0" : "=r" (c1));
    c1 &= ~((1UL << 13) | (1UL << 12) | (1UL << 2) | (1UL << 0));
    __asm__ volatile ("mcr p15, 0, %0, c1, c0, 0" : : "r" (c1) : "memory");
  }

  /* Switch the CPU to low exception vectors (clear V bit, c1 bit 13). */
  {
    uint32_t c1;

    __asm__ volatile ("mrc p15, 0, %0, c1, c0, 0" : "=r" (c1));
    c1 &= ~(1UL << 13);
    __asm__ volatile ("mcr p15, 0, %0, c1, c0, 0" : : "r" (c1) : "memory");
  }
}

/** @} */
