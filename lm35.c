/*----------------------------------------------------------------------------------------------
 * File Name:    lm35.c                                                                        *
 * Author:       Mustafa Ibrahim                                                               *
 * Data Created: Apr 4, 2023                                                                   *
 * Description:  source file for the ATmega32 sensor driver.                                   *
 *---------------------------------------------------------------------------------------------*/
#include <util/delay.h> /* For the delay functions */
#include "lm35.h"
#include "adc.h"

/***********************************************************************************************
 *                                 Functions Definitions                                       *
 ***********************************************************************************************/
/*
 * Description:
 * Function responsible for calculate the temperature from the ADC digital value.
 */
uint8 LM35_getTemperature()
{
	uint16 adc_value = 0 ;

	uint8 sensor_temp = 0 ;
#ifdef POLLING
	adc_value = ADC_readChannel(SENSOR_CHANNEL_ID);
#endif
#ifdef  INTERRUPT
	/* Read ADC channel where the temperature sensor is connected */
	ADC_readChannel(SENSOR_CHANNEL_ID);
	_delay_ms(5);
	adc_value = g_adcResults;
#endif
	sensor_temp = (uint8)( ((float32) ADC_REF_VOLT_VALUE*adc_value * LM35_TEMP_MAX_VALUE ) / ((float32)(LM35_VOLT_MAX_VALUE * ADC_MAXIMUM_VALUE)) );

	return sensor_temp;
}

