/*----------------------------------------------------------------------------------------------
 * File Name:    adc.h                                                                         *
 * Author:       Mustafa Ibrahim                                                               *
 * Data Created: Apr 4, 2023                                                                   *
 * Description:  header file for the ATmega32 ADC driver.                                      *
 *---------------------------------------------------------------------------------------------*/

#ifndef ADC_H_
#define ADC_H_
#include "std_types.h"

/**********************************************************************************************
 *                                 Static configuration                                       *
 **********************************************************************************************/
#define POLLING
#define ADC_MAXIMUM_VALUE    1023  /* Equals for 10 bits */
#define ADC_REF_VOLT_VALUE   2.56  /* Depending on required reference volt */

/**********************************************************************************************
 *                                 User define types                                          *
 **********************************************************************************************/
typedef enum{
	NO_SCALER,PRESCALER_2,PRESCALER_4,PRESCALER_8,PRESCALER_16,PRESCALER_32,\
	PRESCALER_64,PRESCALER_128
}ADC_Prescaler;

typedef enum{
	AREF , AVCC , INTERNAL_AREF=3
}ADC_ReferenceVolatge;

typedef struct
{
	ADC_ReferenceVolatge ref_volt;
	ADC_Prescaler prescaler;
}ADC_ConfigType;

/**********************************************************************************************
 *                                 External Variables                                         *
 **********************************************************************************************/
#ifdef INTERRUPT
/* Extern Public global variables to be used by other modules */
extern volatile uint16 g_adcResults;
#endif
/**********************************************************************************************
 *                                 Functions Prototypes                                       *
 **********************************************************************************************/
/*
 * Description:
 * Function to initialize ADC driver
 * 1-Select required AREF
 * 2-Select required prescaler
 * 3-Select required trigger mode
 */
void ADC_init(const ADC_ConfigType*);
#ifdef POLLING
/*
 * Description:
 * Function to read ADC conversion
 * Argument: ADC channel
 * Return : value of digital signal
 */
uint16 ADC_readChannel(uint8);
#endif
#ifdef INTERRUPT
/*
 * Description:
 * Function to read ADC conversion
 * Argument: ADC channel
 */
void ADC_readChannel(uint8);
#endif
#endif /* ADC_H_ */
