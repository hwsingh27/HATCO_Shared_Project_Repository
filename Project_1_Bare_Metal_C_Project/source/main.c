/**
 * @file: main.c
 * @brief: function has an infinite loop for reading the values from the sensors and log messages to be displayed on 
 * a serial terminal. These messages can be disabled by setting the LOG macro to '0' in common.h file
 *
 * @author: Harshwardhan Singh
 * @date: 13th December 2022
 *
 * @tools: MCUXpresso IDE and FRDM-KL25Z Development Board
 */

#include "common.h"

#define BAUD_RATE (115200) // setting the baud rate as 115200
#define DELAY_MS (200) // delay of 2 sec -> 1 tick = 10 msec

// main function
int main(void)
{
    BOARD_InitBootPins();
    BOARD_InitBootPeripherals();

	// calling the system clock configuration function
    Sysclock_Init(); 
    
	// calling the systick timer initialization function
	Init_Systick();
    
	// calling the UART initialization function for message LOGGING
	Init_UART0(BAUD_RATE); 
    
	// calling initialization function of PWM for RGB LED
	Init_Pwm(); 
	
	// calling initialization functions of I2C0 and I2C1
	I2C1_Init(); 
	I2C0_Init(); 
	
	// calling the TSL2561 function for setting the appropriate registers
	Tsl_Init(); 
    
	// calling circular buffer test function
	Test_Cbuff(); 
    
	// initialized floating point variables for storing temperature, humidity and lux to 0
	float temperature = 0.0, lux = 0.0, humidity = 0.0;

#if (LOG_ENABLED)
    printf("Plant Health Monitoring Systems\n\r\n\r");
#endif

    /*
     * infinite while loop for getting the values in every 2 sec
     */
    while(1)
    {
    	// reading the value from the temperature (SHT21) sensor
    	temperature = Get_Temperature();

    	// reading the value from the humidity (SHT21) sensor
    	humidity = Get_Humidity(); 

    	// reading the value from the light (TSL2561) sensor
    	lux = Get_Lux();
		
		// calling the update_led function to glow the led with a particular color
    	Update_Led(temperature, humidity, lux);

#if (LOG_ENABLED)
    	printf("Temperature = %0.2f Celsius\n\r", temperature);
    	printf("Humidity = %0.2f percent \n\r", humidity);
    	printf("Illuminance = %0.2f lux\n\r", lux);
    	printf("\n\r");
#endif

    	Reset_Timer(); // resetting the systick timer
		
    	while(Get_Timer() != DELAY_MS); // checking if 2 seconds have passed to get the next reading (wait for 2 sec)
    }
    return 0 ;
}
