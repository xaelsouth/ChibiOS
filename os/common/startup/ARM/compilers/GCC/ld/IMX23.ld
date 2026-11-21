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

/*
 * i.MX23 memory setup.
 *
 * NOTE: this file is NOT passed to the linker directly. It is preprocessed
 *       by the C preprocessor so that the board.h #defines (IMX23_RAM_SIZE
 *       etc.) configure the memory layout. The project Makefile must do:
 *
 *         $(BUILDDIR)/IMX23.ld: $(STARTUPLD)/IMX23.ld board/board.h
 *             $(TRGT)gcc -E -P -x c -D__IMX23_LDSCRIPT__ \
 *                 -I<board dir> -I$(STARTUP device dir) $< -o $@
 *         LDSCRIPT = $(BUILDDIR)/IMX23.ld
 *
 *       board.h must wrap its non-#define content in
 *       "#if !defined(__IMX23_LDSCRIPT__)" so the preprocessed output is a
 *       valid linker script.
 *
 * The ChibiOS image runs entirely from SDRAM (loaded at IMX23_RAM_ORIGIN by
 * the bootstream / U-Boot and entered by a jump, no relocation needed).
 * "flash" below is the load region (text + load image of .data), ram0 is
 * the runtime region (stacks, .data, .bss, heap) and ram1 is the on-chip
 * SRAM (usable via __attribute__((section(".ram1")))).
 */

#include "board.h"
#include "imx23_mem.h"

MEMORY
{
    flash : org = IMX23_RAM_ORIGIN, len = IMX23_RAM_SIZE
    ram0  : org = IMX23_RAM_ORIGIN, len = IMX23_RAM_SIZE - IMX23_TOP_RESERVE
    ram1  : org = IMX23_SRAM_ORIGIN, len = IMX23_SRAM_SIZE
    ram2  : org = 0x00000000, len = 0
    ram3  : org = 0x00000000, len = 0
    ram4  : org = 0x00000000, len = 0
    ram5  : org = 0x00000000, len = 0
    ram6  : org = 0x00000000, len = 0
    ram7  : org = 0x00000000, len = 0
}

/* RAM region to be used for stacks. This stack accommodates the processing
   of all exceptions and interrupts*/
REGION_ALIAS("STACKS_RAM", ram0);

/* RAM region to be used for data segment.*/
REGION_ALIAS("DATA_RAM", ram0);

/* RAM region to be used for BSS segment.*/
REGION_ALIAS("BSS_RAM", ram0);

INCLUDE rules.ld
