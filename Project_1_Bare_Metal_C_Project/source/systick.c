/*
 * @file: systick.c
 * @brief: the file constains functions for handling the systick_timer of KL25Z
 *
 * @author: Harshwardhan Singh
 * @date: 13th December 2022
 *
 * @tools: MCUXpresso IDE and FRDM-KL25Z Development Board
 */
#include "common.h"

#define SYSTEM_CLOCK (48000000) // system clock of KL25Z i.e. 48MHz
#define PRESCALAR (16) // prescalar divisor
#define DESIRED_FREQ (100) // desired frequency in Hz - 100 Hz = 10 msec

static volatile ticktime_t reset = 0;
static volatile ticktime_t timer = 0;

/**
 * @brief: this Init function is used to configure the clock
 * by loading the counter value as per the requirement.
 * Here 10 msec has been taken as 1 count value, hence load
 * value becomes (0.01 x SYSTEM_CLOCK)/PRESCALAR
 *
 * @param: void
 * @return: void
 */
void Init_Systick(void)
{
	SysTick->LOAD = (SYSTEM_CLOCK / PRESCALAR) / DESIRED_FREQ; 	// 10msec x 48 Mhz / PRESCALAR
	NVIC_SetPriority(SysTick_IRQn, 1);  	// interrupt priority is set to 1
	SysTick->VAL = 0;					// force load of reload value
	SysTick->CTRL = SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;	// enable interrupt and systick timer with alternative clock source
}

/**
 * @brief: function is executed as soon as the Systick is enabled
 * and keeps incrementing the value of timer.
 *
 * @param: void
 * @return: void
 */
void SysTick_Handler()
{
	timer++;
}

/**
 * @brief: function is used to get the time, timer value should be multipled
 * by 10 to get the time in msec since one count equals 10 msec.
 *
 * @param: void
 * @return: returns the current time count value
 */
ticktime_t Now(void)
{
	return timer;
}

/**
 * @brief: function stores the current time in reset variable.
 *
 * @param: void
 * @return: void
 */
void Reset_Timer(void)
{
	reset = Now();
}

/**
 * @brief: function returns the time passed since the last
 * call to reset
 *
 * @param: void
 * @return: returns ticks since the last call to Reset_Timer()
 */
ticktime_t Get_Timer(void)
{
	return (timer - reset);
}
