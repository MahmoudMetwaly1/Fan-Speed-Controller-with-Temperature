/*============================================================================================
 * FILE NAME:            ADC.h
 * AUTHER :              MAHMOUD METWALY
 * DATE CREATED :        30/9/2022
 * DESCRIPTION :         Header File For ADC Driver

 ===========================================================================================*/

#ifndef ADC_H_
#define ADC_H_

/*----------------------------------------- INCLUDES --------------------------------------*/
#include "std_types.h"



/*----------------------------------------- Definitions ---------------------------------*/

//#define ADC_INTERRUPT_MODE
#define ADC_MAXIMUM_VALUE    1023
#define ADC_REF_VOLT_VALUE   2.56

/*----------------------------- Extern Moudle Shaered global variables ------------------*/
#ifdef ADC_INTERRUPT_MODE

extern volatile uint16 g_adcResult; // extern global variable to use in anther file0

#endif
/*-------------------------------------------- ENUM ------------------------------------*/
typedef enum
{
    ADC_AREF = 0x00,ADC_AVCC = 0x40,ADC_RESEVER = 0x80,ADC_INTERNAL = 0xC0
}ADC_refConfig;

typedef enum
{
  ADC_F_CPU_2, ADC_F_CPU_21 , ADC_F_CPU_4, ADC_F_CPU_8, ADC_F_CPU_16, ADC_F_CPU_32, ADC_F_CPU_64, ADC_F_CPU_128
}ADC_clockPrescaler;

typedef enum
{
    ADC_INTERRUPT_D, ADC_INTERRUPT_E
}ADC_interruptConfig;

/*-------------------------------------------- STRUCT ----------------------------------------*/

typedef struct
{
    ADC_refConfig REF;                // THE voltage REfrance To ADC.
    ADC_clockPrescaler clock;         // the clock prescaler For ADC.
    ADC_interruptConfig interrupt;    // state of interrupt disable or enable.
}ADC_configType;


/*------------------------------------  Functions DeCLARATION ---------------------------------*/


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
void ADC_init(const ADC_configType *config_ptr);


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
void ADC_readChannel(uint8 channel_num);
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
uint16 ADC_readChannel(uint8 channel_num);
#endif


#endif /* ADC_H_ */
