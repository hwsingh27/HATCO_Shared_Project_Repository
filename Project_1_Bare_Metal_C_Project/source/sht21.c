/*
 * @file: sht21.c
 * @brief: the file contains temperature and humidity functions to get the values
 * of temperature in celcius and humidity in percentage respectively
 *
 * @author: Harshwardhan Singh
 * @date: 13th December 2022
 *
 * @tools: MCUXpresso IDE and FRDM-KL25Z Development Board
 */

#include "common.h"

#define SHT21_ADDR (0x40) // device address i.e. SHT21
#define TEMPERATURE (0xE3) // address of the register to get the temperature value
#define HUMIDITY (0xE5) // address of the register to get the humidity value

/**
 * @function: the function converts the temperature in degree Celsius using datasheet (formula)
 *
 * @parameter: void
 * @return: computed temperature in degree celsius in float
 */
float Get_Temperature(void)
{
	// getting the data from the SHT21, temperature register
	uint16_t raw_data = Read_Temp_Hum(SHT21_ADDR, TEMPERATURE);
	
	// clearing the last 2 bits (mentioned in the datasheet)
	raw_data &= ~0x003;
	
	// calculation to convert the raw data to degree Celcius according to the datasheet
	float celcius = (-46.85 + 175.72/65536 * (float)raw_data);
	
	return celcius;
}

/**
 * @function: the function converts the humidity in percentage using datasheet (formula)
 *
 * @parameter: void
 * @return: computed humidity in percentage
 */
float Get_Humidity(void)
{
	// getting the data from the SHT21, humidity register
	uint16_t raw_data = Read_Temp_Hum(SHT21_ADDR, HUMIDITY);
	
	// clearing the last 2 bits (mentioned in the datasheet)
	raw_data &= ~0x003;
	
	// calculation to convert the raw data to humidity (in percentage) according to the datasheet
	float humidity = (-6.0 + 125.0/65536 * (float)raw_data);
	
	return humidity;
}
