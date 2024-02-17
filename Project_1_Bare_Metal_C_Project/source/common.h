/*
 * @file: common.h
 * @brief: the common header file contains all the common headers and macros that are used by the other source files
 *
 * @author: Harshwardhan Singh
 * @date: 13th December 2022
 *
 */

#ifndef COMMON_H_
#define COMMON_H_

#include "MKL25Z4.h"
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "core_cm0plus.h"

#include <stdio.h>
#include <stdint.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "assert.h"

#include "test.h"
#include "i2c.h"
#include "pwm.h"
#include "tsl2561.h"
#include "sht21.h"
#include "sysclock.h"
#include "circular_buffer.h"
#include "uart.h"
#include "update_led.h"
#include "systick.h"

// common macros
#define LOG_ENABLED (1) // enable/disable logging
#define SUCCESS (1)
#define FAILURE (0)

#endif /* COMMON_H_ */
