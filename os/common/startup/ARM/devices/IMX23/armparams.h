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
 * @file    ARM/devices/IMX23/armparams.h
 * @brief   i.MX23 (ARM926EJ-S, ARMv5TE) specific parameters.
 *
 * @addtogroup ARM_SPECIFIC
 * @{
 */

#ifndef ARMPARAMS_H
#define ARMPARAMS_H

/**
 * @brief   ARM core model.
 * @details ARM926EJ-S is an ARMv5TE core, modelled as ARM9 here.
 */
#define ARM_CORE                ARM_CORE_ARM9

/**
 * @brief   Thumb-capable (Thumb-1 only on ARM926EJ-S).
 */
#define ARM_SUPPORTS_THUMB      1

/**
 * @brief   Thumb2-capable.
 */
#define ARM_SUPPORTS_THUMB2     0

/**
 * @brief   Implementation of the wait-for-interrupt state enter.
 * @details ARM926EJ-S has no WFI instruction; the CP15 "wait for interrupt"
 *          operation (MCR p15, 0, Rd, c7, c0, 4) is used instead.
 */
#define ARM_WFI_IMPL            __asm__ volatile ("mov r0, #0\n\t" \
                                                  "mcr p15, 0, r0, c7, c0, 4" \
                                                  : : : "r0", "memory")

/**
 * @brief   Address of the IRQ vector register in the interrupt controller.
 * @details On the i.MX23 this is HW_ICOLL_VECTOR (ICOLL base 0x80000000,
 *          offset 0x000). Reading it presents the vector address of the
 *          highest priority pending interrupt, computed as
 *          HW_ICOLL_VBASE + vector_number * 4 * HW_ICOLL_CTRL[VECTOR_PITCH].
 *          The port programs VBASE with a table in SDRAM whose entries point
 *          to the per-IRQ trampoline (see os/hal/ports/IMX23/IMX23xx/icoll.S).
 */
#if !defined(_FROM_ASM_) || defined(__DOXYGEN__)
#define ARM_IRQ_VECTOR_REG      0x80000000U
#else
#define ARM_IRQ_VECTOR_REG      0x80000000
#endif

#endif /* ARMPARAMS_H */

/** @} */
