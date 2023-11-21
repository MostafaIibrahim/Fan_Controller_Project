/*----------------------------------------------------------------------------------------------
 * File Name:    lm35.h                                                                        *
 * Author:       Mustafa Ibrahim                                                               *
 * Data Created: Apr 4, 2023                                                                   *
 * Description:  header file for the ATmega32 sensor driver.                                   *
 *---------------------------------------------------------------------------------------------*/
#ifndef LM35_H_
#define LM35_H_
#include "std_types.h"

/**********************************************************************************************
 *                                 Static configuration                                       *
 **********************************************************************************************/
#define SENSOR_CHANNEL_ID       2
#define LM35_VOLT_MAX_VALUE     1.5
#define LM35_TEMP_MAX_VALUE     150
/**********************************************************************************************
 *                                 Functions Prototypes                                       *
 **********************************************************************************************/
/*
 * Description:
 * Function responsible for calculate the temperature from the ADC digital value.
 */
uint8 LM35_getTemperature();


#endif /* LM35_H_ */
