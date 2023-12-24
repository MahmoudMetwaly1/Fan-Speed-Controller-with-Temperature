/*============================================================================================
 * FILE NAME:            lm35_sensor.h
 * AUTHER :              MAHMOUD METWALY
 * DATE CREATED :        6/10/2022
 * DESCRIPTION :         THe Header File for lm35_sensor DRIVER

 ===========================================================================================*/


#ifndef LM35_SENSOR_H_
#define LM35_SENSOR_H_

/*--------------------------------- INCLUDES ---------------------------------------------*/
#include "std_types.h"


/*--------------------------------- Definitions ------------------------------------------*/
#define SENSOR_CHANNEL_ID         2
#define SENSOR_MAX_VOLT_VALUE     1.5
#define SENSOR_MAX_TEMPERATURE    150

/*-------------------------------FUNCTION DECLARATION ------------------------------------*/

/*
 * [Function Name] : LM35_getTemperature()
 * [Description]   : Function responsible for calculate the temperature from the ADC digital value.
 * [ARG]            :  No ARG
 *
 * [Return]        : temperature value
 */
uint8 LM35_getTemperature(void);

#endif /* LM35_SENSOR_H_ */
