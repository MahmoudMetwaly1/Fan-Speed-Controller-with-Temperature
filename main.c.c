/*============================================================================================
 * FILE NAME    :        Mini_Project3.c
 * AUTHER       :        MAHMOUD METWALY
 * DATE CREATED :        5/10/2022
 * DESCRIPTION  :        Fan Controller system

 ===========================================================================================*/

/*------------------------------------------- INCLUDES -------------------------------------*/

#include "lcd.h"
#include "adc.h"
#include "dcmotor.h"
#include "lm35_sensor.h"
#include "pwm.h"
#include "lcd.h"
#include <util/delay.h>

int main(void)
{
	uint8 tempValue = 0;      /*to receive the temperature value from the sensor */
	ADC_configType ADC_config = {ADC_INTERNAL, ADC_F_CPU_8, ADC_INTERRUPT_D}; /*ADC configuration */
	LCD_init();  //initiate the lcd
	ADC_init(&ADC_config);  //initiate ADC
	DcMotor_Init(); //initiate DC Motor
	LCD_displayStringRowColumn(1, 2, "TEMP =      c");   /* Display the string in row 1 and column 3 */
	while(1)
	{
		/* receive the temperature value from the sensor */
		tempValue = LM35_getTemperature();
		LCD_moveCursor(1, 10);   // move LCD cursor to row 1 and column 10.
		/*display the temperature value in LCD */

		if(tempValue >= 100)
		{
			LCD_intgerToString(tempValue);
		}
		else if(tempValue >= 10 && tempValue > 100)
		{
			LCD_intgerToString(tempValue);
			LCD_displayCharacter(" ");
		}
		else
		{
			LCD_intgerToString(tempValue);
			LCD_displayString("  ");
		}

		/* check the temperature and configure the motor  */
		if(tempValue < 30)
		{
			/* if the temperature < 30c the Motor Stop*/
			DcMotor_Rotate(DC_STOP, 0);
			LCD_displayStringRowColumn(0, 2, "FAN IS OFF");

		}
		else if(tempValue >= 30 && tempValue < 60)
		{
			/* if the temperature >= 30c the Motor will rotate by 25% from speed */

			DcMotor_Rotate(DC_CW, 25);
			LCD_displayStringRowColumn(0, 2,"FAN IS ON ");

		}
		else if(tempValue >= 60 && tempValue < 90)
		{
			/* if the temperature >= 600c the Motor will rotate by 50% from speed */

			DcMotor_Rotate(DC_CW, 50);
			LCD_displayStringRowColumn(0, 2,"FAN IS ON ");

		}
		else if(tempValue >= 90 && tempValue < 120)
		{
			/* if the temperature >= 90c the Motor will rotate by 75% from speed */

			DcMotor_Rotate(DC_CW, 75);
			LCD_displayStringRowColumn(0, 2,"FAN IS ON ");

		}
		else if(tempValue >= 120)
		{
			/* if the temperature >= 120c the Motor will rotate by 100% from speed */
			DcMotor_Rotate(DC_CW, 100);
			LCD_displayStringRowColumn(0, 2,"FAN IS ON ");

		}
		/* control the motor speed by PWM and DUTY CYCLE */
		PWM_Timer0_Init(g_DutyCycle);


	}

}

