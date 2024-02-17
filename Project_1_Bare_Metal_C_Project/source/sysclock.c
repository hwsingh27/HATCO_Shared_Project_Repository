 /**
 * @file: sysclock.c
 * @brief: consists of the configuration routines for KL25Z system clock
 *
 * @author: Harshwardhan Singh
 * @date: 13th December 2022
 *
 * @tools: MCUXpresso IDE and FRDM-KL25Z Development Board
 * Inspired by https://learningmicro.wordpress.com/configuring-device-clock-and-using-systick-system-tick-timer-module-to-generate-software-timings/
 */

#include "common.h"

/**
 * @function: the function has a system clock configuration for KL25Z
 *
 * @parameter: void
 * @return: void
 */
void Sysclock_Init(void)
{
  // Select PLL/FLL as clock source
  MCG->C1 &= ~(MCG_C1_CLKS_MASK);
  MCG->C1 |= MCG_C1_CLKS(0);

  // Use internal reference clock as source for the FLL
  MCG->C1 |= MCG_C1_IREFS(1);

  // Select the FLL (by setting "PLL select" to 0)
  MCG->C6 &= ~(MCG_C6_PLLS_MASK);
  MCG->C6 |= MCG_C6_PLLS(0);

  // Select 24 MHz - see table for MCG_C4[DMX32]
  MCG->C4 &= ~(MCG_C4_DRST_DRS_MASK & MCG_C4_DMX32_MASK);
  MCG->C4 |= MCG_C4_DRST_DRS(0);
  MCG->C4 |= MCG_C4_DMX32(1);
}
