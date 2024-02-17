/*
 * @file: update_led.h
 *
 * @author: Harshwardhan Singh
 * @date: 13th December 2022
 *
 */

#ifndef UPDATE_LED_H_
#define UPDATE_LED_H_

#include "common.h"

// macros

#define TEMP_WARN (24) // threshold temperature for warning situation
#define HUM_WARN (30) // threshold humidity for warning situation
#define LUX_WARN (50) // threshold lux for warning situation

#define TEMP_DANG (25) // threshold temperature for danger situation
#define HUM_DANG (50) // threshold humidity for danger situation
#define LUX_DANG (100) // threshold lux for danger situation

#define RED (255) // change the value to set the red color intensity
#define GREEN (255) // change the value to set the green color intensity
#define BLUE (255) // change the value to set the blue color intensity
#define OFF (0) // macro to turn off a particular color

// function declaration

void Update_Led(float temp, float hum, float light);

#endif /* UPDATE_LED_H_ */
