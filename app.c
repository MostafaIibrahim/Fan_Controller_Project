/*
 * app.c
 *
 *  Created on: Jul 3, 2023
 *      Author: SOFT ZONE
 */
#include  "timer.h"
#include "lm35.h"
#include "dc_motor.h"
#include "adc.h"
#include "lcd.h"

int main(){
	uint8 temp ;
	Timer0_ConfigType config = {0,0,TIMER0_PWM_FAST_MODE,TIMER0_8_PRESCALE,0,TIMER0_CLEAR_OC0_FAST_PWM};
	ADC_ConfigType adc_config = {INTERNAL_AREF,PRESCALER_8};
	DcMotor_Init();
	LCD_init();
	ADC_init(&adc_config);
	Timer0_init(&config);

	/* Display on LCD */
	LCD_displayStringRowColumn(0,0,"FAN is  ");
	LCD_displayStringRowColumn(1,0,"Temp =    C");

	while(1){
		/* get LM35 sensor read */
		temp = LM35_getTemperature() ;
		if(temp < 30)
		{
			DcMotor_Rotate(STOP,0);
			LCD_displayStringRowColumn(0,7,"OFF");
			/* move cursor in required position */
			LCD_moveCursor(1,7);
			LCD_intgerToString(temp);
			LCD_displayCharacter(' ');
		}
		else if ((temp >= 30) && (temp < 60))
		{
			DcMotor_Rotate(CW,25);
			LCD_moveCursor(0,7);
			LCD_displayString("ON");
			LCD_displayCharacter(' ');
			/* move cursor in required position */
			LCD_moveCursor(1,7);
			LCD_intgerToString(temp);
			LCD_displayCharacter(' ');
		}
		else if ((temp >= 60) && (temp < 90))
		{
			DcMotor_Rotate(CW,50);
			LCD_moveCursor(0,7);
			LCD_displayString("ON");
			/* move cursor in required position */
			LCD_moveCursor(1,7);
			LCD_intgerToString(temp);
			LCD_displayCharacter(' ');
		}
		else if ((temp >= 90) && (temp < 120))
		{
			DcMotor_Rotate(CW,75);
			LCD_moveCursor(0,7);
			LCD_displayString("ON");
			/* move cursor in required position */
			LCD_moveCursor(1,7);
			if (temp < 100)
			{
				LCD_intgerToString(temp);
				LCD_displayCharacter(' ');
			}
			else
			{
				LCD_intgerToString(temp);
			}
		}
		else
		{
			DcMotor_Rotate(CW,100);
			LCD_displayStringRowColumn(0,0,"FAN is ON");
			/* move cursor in required position */
			LCD_moveCursor(1,7);
			LCD_intgerToString(temp);
		}
	}
}

