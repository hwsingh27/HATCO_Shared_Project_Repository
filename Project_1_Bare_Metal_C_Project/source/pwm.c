/*
 * @file: pwm.c
 * @brief: the file contains PWM configuration function and
 * function that is used to set the color of RGB LED
 *
 * @author: Harshwardhan Singh
 * @date: 13th December 2022
 *
 * @tools: MCUXpresso IDE and FRDM-KL25Z Development Board
 */

#include "common.h"

#define RED_LED_PIN 	(18) // GPIO Pin for red LED
#define GREEN_LED_PIN 	(19) // GPIO Pin for green LED
#define BLUE_LED_PIN 	(1) // GPIO pin for blue LED
#define PWM_MOD_VAL 	(48000) // (48MHz/500Hz) / prescalar = 96000/2 = 48000
#define PWM_HLIMIT 		(255) // maximum value for light intensity

/**
 * @function: the function is used to configure PWM module
 *
 * @parameter: void
 * @return: void
 */
void Init_Pwm(void)
{
	//enable clock to PORTD, PORTB, TPM0 and TPM2
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
	SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK;
	SIM->SCGC6 |= SIM_SCGC6_TPM2_MASK;

	//setting pins to FTM
	PORTB->PCR[RED_LED_PIN] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[RED_LED_PIN] |= PORT_PCR_MUX(3);

	PORTB->PCR[GREEN_LED_PIN] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[GREEN_LED_PIN] |= PORT_PCR_MUX(3);

	PORTD->PCR[BLUE_LED_PIN] &= ~PORT_PCR_MUX_MASK;
	PORTD->PCR[BLUE_LED_PIN] |= PORT_PCR_MUX(4);

	//set clock source for TPM i.e. 48MHz
	SIM->SOPT2 |= (SIM_SOPT2_TPMSRC(1));

	//loading the counter and MOD
	TPM2->MOD = PWM_MOD_VAL - 1; // ((48MHz/500Hz) / prescalar) - 1 = 96000/2 - 1 = 48000 - 1
	
	//set the TPM counter direction to up with the prescaler of 2
	TPM2->SC = TPM_SC_PS(1);
	
	//continue operation in DEBUG mode
	TPM2->CONF |= TPM_CONF_DBGMODE(3);
	
	//set channel 0 to edge aligned low-true PWM
	TPM2->CONTROLS[0].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK;
	
	//set initial duty cycle as 0
	TPM2->CONTROLS[0].CnV = 0;
	
	//start TPM
	TPM2->SC |= TPM_SC_CMOD(1);

	//set channel 1 to edge aligned low-true PWM
	TPM2->CONTROLS[1].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK;
	
	//set initial duty cycle as 0
	TPM2->CONTROLS[1].CnV = 0;
	
	//start TPM
	TPM2->SC |= TPM_SC_CMOD(1);

	//loading the counter and MOD
	TPM0->MOD = PWM_MOD_VAL - 1; // (system clock freq / desired freq) - 1 i.e. (48Mhz / 100Hz) - 1
	
	//set the TPM counter direction to up with the prescaler of 2
	TPM0->SC = TPM_SC_PS(1);
	
	//continue operation in DEBUG mode
	TPM0->CONF |= TPM_CONF_DBGMODE(3);
	
	//set channel 1 to edge aligned low-true PWM
	TPM0->CONTROLS[1].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK;
	
	//set initial duty cycle as 0
	TPM0->CONTROLS[1].CnV = 0;
	
	//start TPM
	TPM0->SC |= TPM_SC_CMOD(1);
}

/**
 * @function: the function is used to set the PWM control registers with the values ranging 0-255 to glow RGB LED according
 * to the color intensity values
 *
 * @parameter: the intensities of Red, Blue and Green color by passing any value in the range 0-255
 * @return: void
 */
void Set_Color(int r, int g, int b)
{
	int red = (r * PWM_MOD_VAL) / PWM_HLIMIT;
	int green = (g * PWM_MOD_VAL) / PWM_HLIMIT;
	int blue = (b * PWM_MOD_VAL) / PWM_HLIMIT;

	TPM2->CONTROLS[0].CnV = red;
	TPM2->CONTROLS[1].CnV = green;
	TPM0->CONTROLS[1].CnV = blue;
}