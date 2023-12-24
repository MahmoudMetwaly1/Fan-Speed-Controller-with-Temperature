/*============================================================================================
 * FILE NAME:            ADC.C
 * AUTHER :              MAHMOUD METWALY
 * DATE CREATED :        30/9/2022
 * DESCRIPTION :         ADC DRIVER

 ===========================================================================================*/
/*------------------------------ INCLUDES --------------------------------------------*/
#include "adc.h"
#include "avr/io.h" /* To use the ADC Registers */
#include "common_macros.h" /* To use the macros like SET_BIT */

#ifdef ADC_INTERRUPT_MODE

#include <avr/interrupt.h> /* For ADC ISR */

#endif

/*----------------------------- Global Variable -------------------------------*/

#ifdef ADC_INTERRUPT_MODE

volatile uint16 g_adcResult = 0; // to store the ADC REG in ISR

#endif

/*--------------------------------- ISR DEFINATION -------------------------------*/

#ifdef ADC_INTERRUPT_MODE

ISR(ADC_vect)
{
	/* Read ADC Data after conversion complete */
	g_adcResult = ADC;
}
#endif // ADC_INTERRUPT_MODE


/*--------------------  Functions Definitions -------------------------------------*/

/*
 * [Function Name] : ADC_init()
 * [Description]   : Function responsible for initialize the ADC driver
 *[ARG]            :
 *
 *[in]        const ADC_configType *config_ptr:
 *                            This Arg Receive the Address Of the structure that configure the ADC Driver Initialization.
 *
 * [Return]        : Void
 */
void ADC_init(const ADC_configType *config_ptr)
{
	/* ADMUX Register Bits Description:
	 * REFS1:0 = 01 to choose AVCC = 5v as reference voltage
	 * ADLAR   = 0 right adjusted
	 * MUX4:0  = 00000 to choose channel 0 as initialization
	 */
	ADMUX = (config_ptr->REF);

	/* ADCSRA Register Bits Description:
	 * ADEN    = 1 Enable ADC
	 * ADIE    = 0 Disable ADC Interrupt
	 * ADATE   = 0 Disable Auto Trigger
	 * ADPS2:0 = 111 to choose ADC_Clock = F_CPU/128 = 16Mhz/128 = 125Khz --> ADC must operate in range 50-200Khz
	 */
	SET_BIT(ADCSRA,ADEN);
	CLEAR_BIT(ADCSRA,ADATE);
	ADCSRA = (ADCSRA & 0xF8) | (config_ptr->clock);
	ADCSRA = (ADCSRA & 0xF7) | ((config_ptr->interrupt)<<3);

}


#ifdef ADC_INTERRUPT_MODE
/*
 * [Function Name] : ADC_readChannel()
 * [Description]   : Asynchronous Function responsible for Analog data from a certain ADC channel
 *                      and convert it to digital using the ADC driver by ISR.
 *[ARG]            :
 *
 *[in]        uint8 channel_num:
 *                            This Arg Indicate to the ADC Channel Number.
 *
 * [Return]        : Void
 */
void ADC_readChannel(uint8 channel_num)
{
	ADMUX = (ADMUX & 0xE0) | (channel_num);   // insert the channel number in ADMUX Register.
	SET_BIT(ADCSRA,ADSC); /* Start conversion write '1' to ADSC */
}

#else
/*
 * [Function Name] : ADC_readChannel()
 * [Description]   : synchronous Function responsible for Analog data from a certain ADC channel
 *                      and convert it to digital using the ADC driver.
 *[ARG]            :
 *
 *[in]        uint8 channel_num:
 *                            This Arg Indicate to the ADC Channel Number.
 *
 * [Return]        : ADC Register.
 */
uint16 ADC_readChannel(uint8 channel_num)
{
	ADMUX = (ADMUX & 0xE0) | (channel_num); // insert the channel number in ADMUX Register.
	SET_BIT(ADCSRA,ADSC); /* Start conversion write '1' to ADSC */
	while(BIT_IS_CLEAR(ADCSRA,ADIF)); /* Wait for conversion to complete, ADIF becomes '1' */
	SET_BIT(ADCSRA,ADIF); /* Clear ADIF by write '1' to it :) */
	return ADC; /* Read the digital value from the data register */
}
#endif // ADC_INTERRUPT_MODE

