/*----------------------------------------------------------------------------------------------
 * File Name:    adc.c                                                                         *
 * Author:       Mustafa Ibrahim                                                               *
 * Data Created: Apr 4, 2023                                                                   *
 * Description:  source file for the ATmega32 ADC driverDriver.                                *
 *---------------------------------------------------------------------------------------------*/
#include "adc.h"
#include "common_macros.h"
#include <avr/io.h>
#include<avr/interrupt.h>

/***********************************************************************************************
 *                                  Global Variables                                           *
 ***********************************************************************************************/

#ifdef INTERRUPT
volatile uint16 g_adcResults = 0;
#endif

/***********************************************************************************************
 *                                   ISR's Definitions                                         *
 **********************************************************************************************/
#ifdef INTERRUPT
ISR(ADC_vect)
{
	g_adcResults = ADC ;
}
#endif
/***********************************************************************************************
 *                                 Functions Definitions                                       *
 ***********************************************************************************************/
/*
 * Description:
 * Function to initialize ADC driver
 * 1-Select required AREF
 * 2-Select required prescaler
 */
void ADC_init(const ADC_ConfigType *config_ptr)
{
	/*
	 * ADMUX Register Bits Description:
	 * REFS1:0 = 00 to choose to connect external reference voltage by input this voltage through AREF pin
	 * ADLAR   = 0 right adjusted
	 * MUX4:0  = 00000 to choose channel 0 as initialization
	 */
	ADMUX = ((config_ptr->ref_volt)<<6);
	/* ADCSRA Register Bits Description:
	 * ADEN    = 1 Enable ADC
	 * ADIE    = 0 Disable ADC Interrupt
	 * ADATE   = 0 Disable Auto Trigger
	 * ADPS2:0 = 011 to choose ADC_Clock = F_CPU/8 = 1Mhz/8 = 125Khz --> ADC must operate in range 50-200Khz
	 */
	ADCSRA = (1<<ADEN) | (config_ptr->prescaler);
#ifdef INTERRUPT
	ADCSRA |= (1<<ADIE);          /* Enable ADC Interrupt */
#endif
}

#ifdef POLLING
/*
 * Description:
 * Function to read ADC conversion
 * Argument: ADC channel
 * Return : value of digital signal
 */
uint16 ADC_readChannel(uint8 channel)
{
	/* First choose required channel to read from */
	ADMUX = (ADMUX & 0xE0) | (channel & 0x07) ;
	/* Start conversion by setting bit in ADSC */
	SET_BIT(ADCSRA,ADSC);
	/* Wait until finishing the conversion by polling on it */
	while(BIT_IS_CLEAR(ADCSRA,ADIF));
	/* Clear Interrupt flag */
	SET_BIT(ADCSRA,ADIF);
	/* Return digital signal in ADC register */
	return ADC;
}
#endif
#ifdef INTERRUPT
void ADC_readChannel(uint8 channel)
{
	/* First choose required channel to read from */
	ADMUX = (ADMUX & 0xE0) | (channel & 0x07) ;
	/* Start conversion by setting bit in ADSC */
	SET_BIT(ADCSRA,ADSC);
}
#endif


