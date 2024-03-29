/**
 * @file: tsl2561.c
 * @brief: file contains the functions to configure TSL2561 sensor and get the value of light intensity in lux from the sensor
 *
 * @author: Harshwardhan Singh
 * @date: 13th December 2022
 *
 * @tools: MCUXpresso IDE and FRDM-KL25Z Development Board
 */

#include "common.h"

#define GAIN_TIME (0x02) // setting the gain as 0 and time as 2 for 402ms
#define POWER_UP (0x03) // powering up the device i.e. TSL2561

#define TSL2561_ADDR	(0x39) // address of the TSL2561
#define TSL2561_CMD     (0x80) // for setting the MSB
#define	TSL2561_CONTROL   (0x00) // for controlling the basic functions
#define	TSL2561_TIMING    (0x01) // integration time/gain control
#define	TSL2561_THRESH_LOW  (0x02) // low byte of low interrupt threshold
#define	TSL2561_THRESH_HIGH  (0x04) // low byte of high interrupt threshold
#define	TSL2561_DATA_0_LOW    (0x0C) // low byte of ADC channel 0
#define	TSL2561_DATA_0_HIGH   (0x0D) // high byte of ADC channel 0
#define	TSL2561_DATA_1_LOW    (0x0E) // low byte of ADC channel 1
#define	TSL2561_DATA_1_HIGH   (0x0F) // high byte of ADC channel 1

/**
 * @function: the function is used to write into various registers to configure the I2C0 for TSL2561 sensor
 *
 * @parameter: void
 * @return: void
 */
void Tsl_Init(void)
{
	// setting gain to 0 and time to 2 for 402ms
	Write_Luminosity(TSL2561_ADDR, TSL2561_TIMING | TSL2561_CMD, GAIN_TIME);
	
	// powering up the device
	Write_Luminosity(TSL2561_ADDR, TSL2561_CONTROL | TSL2561_CMD, POWER_UP);
}

/**
 * @function: the function computes the lux value from the TSL2561 sensor using the datasheet (formula)
 *
 * @parameter: void
 * @return: the value from light sensor in lux
 */
float Get_Lux(void)
{
	uint8_t data0_low = 0, data0_high = 0, data1_low = 0, data1_high = 0;
	float lux = 0.0, ratio = 0.0;
	double data1 = 0.0, data0 = 0.0;

	// reading the data from the data0 low register
	data0_low = Read_Luminosity(TSL2561_ADDR,TSL2561_DATA_0_LOW | TSL2561_CMD);
	
	// reading the data from the data0 high register
	data0_high = Read_Luminosity(TSL2561_ADDR,TSL2561_DATA_0_HIGH | TSL2561_CMD);
	
	// reading the data from the data1 low register
	data1_low = Read_Luminosity(TSL2561_ADDR,TSL2561_DATA_1_LOW | TSL2561_CMD);
	
	// reading the data from the data1 high register
	data1_high = Read_Luminosity(TSL2561_ADDR,TSL2561_DATA_1_HIGH | TSL2561_CMD);

	// getting the overall value from data0 high and data0 low register and storing in data0
	data0 = (data0_high << 8) | (data0_low);
	
	// getting the overall value from data1 high and data1 low register and storing in data1
	data1 = (data1_high << 8) | (data1_low);

	// computing the ratio of data0 and data1 to measure the lux using appropriate formula from the datasheet
	ratio = data1 / data0;

	if(ratio < 0.5)
	{
		lux = 3.5*(3.04 * data0 - 6.2 * data0); // formula used from the datasheet
	}

	if(ratio < 0.61)
	{
		lux = 3.5*(2.24 * data0 - 3.1 * data1); // formula used from the datasheet
	}

	if(ratio < 0.80)
	{
		lux = 3.5*(1.28 * data0 - 1.53 * data1); // formula used from the datasheet
	}

	if(ratio < 1.30)
	{
		lux = 3.5*(0.146 * data0 - 0.112 * data1); // formula used from the datasheet
	}
	if(ratio > 1.30)
	{
		lux = 0;
	}
	
	return lux;
}
