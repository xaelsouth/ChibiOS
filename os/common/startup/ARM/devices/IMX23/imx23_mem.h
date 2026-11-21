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
 * @file    ARM/devices/IMX23/imx23_mem.h
 * @brief   i.MX23 memory layout defaults.
 *
 * @details These macros are consumed both by C code and by the IMX23.ld
 *          linker script (which is run through the C preprocessor, see the
 *          demo Makefile). Boards override them in board.h, e.g.:
 *          - OLIMEX i.MX233 : #define IMX23_RAM_SIZE 0x4000000  (64MB)
 *          - i.MX23 EVK     : #define IMX23_RAM_SIZE 0x8000000  (128MB)
 *
 * @addtogroup ARM_SPECIFIC
 * @{
 */

#ifndef IMX23_MEM_H
#define IMX23_MEM_H

/**
 * @brief   SDRAM (EMI CS0) base address on the i.MX23.
 */
#ifndef IMX23_RAM_ORIGIN
#define IMX23_RAM_ORIGIN        0x40000000
#endif

/**
 * @brief   SDRAM size in bytes, board specific (64MB or 128MB).
 * @note    Must be a plain numeric literal (no U/L suffixes) so that it can
 *          be used inside the linker script as well.
 */
#ifndef IMX23_RAM_SIZE
#define IMX23_RAM_SIZE          0x4000000
#endif

/**
 * @brief   Bytes reserved at the very top of SDRAM (not handed out to the
 *          ChibiOS heap). Boards use this e.g. for a fixed LCD framebuffer
 *          or an MMU page table.
 */
#ifndef IMX23_TOP_RESERVE
#define IMX23_TOP_RESERVE       0x0
#endif

/**
 * @brief   On-chip SRAM (OCRAM) usable base.
 * @details The i.MX23 has 32KB of OCRAM at 0x00000000 (aliased every 32KB up
 *          to 0x3FFFFFFF). The first 4KB are left to the exception vectors
 *          (copied to 0x00000000 by __early_init) and to the boot ROM.
 */
#ifndef IMX23_SRAM_ORIGIN
#define IMX23_SRAM_ORIGIN       0x00001000
#endif

/**
 * @brief   On-chip SRAM usable size.
 */
#ifndef IMX23_SRAM_SIZE
#define IMX23_SRAM_SIZE         0x00007000
#endif

#endif /* IMX23_MEM_H */

/** @} */
