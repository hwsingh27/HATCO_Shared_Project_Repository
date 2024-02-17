/**
 * @file: update_led.c
 * @brief: this file contains a function that is used to to glow the RGB LED with a different colors
 * to indicate various situations around the plants and LOG the messages accordingly if LOG is enabled
 * in common.h file
 *
 * @author: Harshwardhan Singh
 * @date: 13th December 2022
 *
 * @tools: MCUXpresso IDE and FRDM-KL25Z Development Board
 */

#include "common.h"

/**
 * @function: the function is used to glow the RGB LED with a different colors
 * to indicate various situations around plants and LOG the messages accordingly 
 * if LOG feature is enabled in common.h
 *
 * @parameter: values of temperature, humidity and lux from the sensor modules
 * @return: void
 */
void Update_Led(float temp, float hum, float light)
{
		/*
    	 * glowing the RED LED and printing the danger message when the threshold is crossed
    	 * glowing the YELLOW LED and printing the warning message when the threshold is crossed
    	 * glowing the GREEN LED when the values are in the safer range
    	 */
    	if(temp > TEMP_DANG && hum > HUM_DANG && light > LUX_DANG)
    	{
    		Set_Color(RED,OFF,OFF); //RED LED
#if (LOG_ENABLED)
    		printf("Danger....Danger....Danger....\n\r");
#endif
    	}
    	else if(temp > TEMP_WARN && hum > HUM_WARN && light > LUX_WARN)
    	{
    		Set_Color(RED,GREEN,OFF); //YELLOW LED -> RED + GREEN = YELLOW
#if (LOG_ENABLED)
    		printf("Warning....Warning....Warning....\n\r");
#endif
    	}
    	else
    	{
    		Set_Color(OFF,GREEN,OFF); //GREEN LED
#if (LOG_ENABLED)
    		printf("Safe....Safe....Safe....\n\r");
#endif
    	}
}