 /*============================================================================================
 * FILE NAME:            lm35_sensor.C
 * AUTHER :              MAHMOUD METWALY
 * DATE CREATED :        6/10/2022
 * DESCRIPTION :         lm35_sensor DRIVER

 ===========================================================================================*/

/*--------------------------------INCLUDES---------------------------------------*/

#include "lm35_sensor.h"
#include "adc.h"   // to use ADC driver

/*------------------------------Function Definition-------------------------------*/

/*
 * [Function Name] : LM35_getTemperature()
 * [Description]   : Function responsible for calculate the temperature from the ADC digital value.
 * [ARG]            :  No ARG
 *
 * [Return]        : temperature value
 */
uint8 LM35_getTemperature(void)
{
	uint8 temp_value = 0;   // to store the temperature value.

	uint16 adc_value = 0;   // to receive the value From ADC.

	/* Read ADC channel where the temperature sensor is connected */
	adc_value = ADC_readChannel(SENSOR_CHANNEL_ID);

	/* Calculate the temperature from the ADC value*/
	temp_value = (uint8)(((uint32)adc_value*SENSOR_MAX_TEMPERATURE*ADC_REF_VOLT_VALUE)/(ADC_MAXIMUM_VALUE*SENSOR_MAX_VOLT_VALUE));

	return temp_value;
}

