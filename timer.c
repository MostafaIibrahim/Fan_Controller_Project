/*
 * timer.c
 *
 *  Created on: Jun 18, 2023
 *      Author: SOFT ZONE
 */
#include "timer.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "gpio.h"
#include "common_macros.h"
/*                                    Global Variables                                        */

#ifdef TIMER0
static volatile void (*g_ptr_t0)(void) = NULL_PTR;
/*
 *                                        ISR                                               */

ISR(TIMER0_COMP_vect){
	if(g_ptr_t0 != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_ptr_t0)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}
ISR(TIMER0_OVF_vect){
	if(g_ptr_t0 != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_ptr_t0)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

/*                                   Function Definition                                      */

/*
 * Description: Function to initialize the Timer driver
 * Input: pointer to the configuration structure with type Timer_ConfigType.
 * Output: None
 */
void Timer0_init(const Timer0_ConfigType * Config_Ptr){
	/* Initial value of Timer register */
	TCNT0 = Config_Ptr->compare_value ;
	/* Configure WGM00 WGM01 of mode */
	TCCR0 = (TCCR0 & 0xBF) | ((Config_Ptr->timer0_mode& 0x01)<<6) ;
	TCCR0 = (TCCR0 & 0xF7)	| ((Config_Ptr->timer0_mode& 0x02)<<2) ;
	/* Configure CS00 ~ CS02 for prescaler */
	TCCR0= (TCCR0 & 0xF8) | (Config_Ptr->timer0_prescaler & 0x07);

	if(Config_Ptr->timer0_mode != TIMER0_PWM_FAST_MODE){
		TCCR0 |= (1<<FOC0);
	}

	/* Initial value of CTC register */
	if(Config_Ptr->timer0_mode != TIMER0_NORMAL_MODE){
		OCR0 = Config_Ptr->compare_value;
		TIMSK |= (1<<OCIE0);
	}
	else{
		TIMSK |= (1<<TOIE0);
	}

	/* set pwm pin as output */
	if((Config_Ptr->timer0_mode == TIMER0_PWM_FAST_MODE)\
			|| (Config_Ptr->timer0_mode_non_pwm != TIMER0_NORMAL_PORT_NON_PWM)){
		GPIO_setupPinDirection(T0_ENABLE_PORT_ID ,T0_ENABLE_PIN_ID,PIN_OUTPUT);
	}

	/* Configure COM01 COM00 */
	if(Config_Ptr->timer0_mode != TIMER0_PWM_FAST_MODE){
		TCCR0 |= ((Config_Ptr->timer0_mode_non_pwm)<<4);
	}
	else if(Config_Ptr->timer0_mode == TIMER0_PWM_FAST_MODE){
		TCCR0 |= ((Config_Ptr->timer0_mode_fast_pwm)<<4);
	}


}
/*
 * Description:Function to disable the Timer.
 * Input: None
 * Output: None
 */
void Timer0_deInit(void){
	TCCR0=0;
	TCNT0=0;
	OCR0=0;
	CLEAR_BIT(TIMSK,OCIE0);
	CLEAR_BIT(TIMSK,TOIE0);
}

/*
 * Description: Function to set the Call Back function address.
 * Input: None
 * Output: None
 */
void Timer0_setCallBack(void(*a_ptr)(void)){
	g_ptr_t0 = a_ptr;
}
void Timer0_pwmAdjust(uint8 duty_cycle)
{
	Timer0_ConfigType ocr_value;
	duty_cycle  = (uint8)(((uint16)255*duty_cycle)/100); //define compare value
	ocr_value.compare_value =  duty_cycle;

}
#endif

#ifdef TIMER1
static volatile void (*g_ptr_t1)(void) = NULL_PTR;
/*                                          ISR                                           */
ISR(TIMER1_COMPA_vect){
	if(g_ptr_t1 != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_ptr_t1)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}
ISR(TIMER1_COMPB_vect){
	if(g_ptr_t1 != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_ptr_t1)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}
ISR(TIMER1_OVF_vect){
	if(g_ptr_t1 != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_ptr_t1)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

/*                                   Function Prototype                                      */
/*
 * Description: Function to initialize the Timer driver
 * Input: pointer to the configuration structure with type Timer_ConfigType.
 * Output: None
 */
void Timer1_init(const Timer1_ConfigType * Config_Ptr){
#ifdef COUNTER_MODE
	GPIO_setupPinDirection(T1_ENABLE_PORT_ID, T1_ENABLE_PIN_ID, PIN_INPUT);
#endif
	/* Timer1 register initial value */
	TCNT1 = Config_Ptr->initial_value;

	/* Configure Wave generation Form in TCCR1 A & B registers  */
	TCCR1A = (TCCR1A & 0xFC) | (Config_Ptr->timer1_mode & 0x03);
	TCCR1B = (TCCR1B & 0xE7) | ((Config_Ptr->timer1_mode & 0x0C)<<1);

	/* Configure Prescaler  in TCCR1B registers */
	TCCR1B = (TCCR1B & 0xF8) | (Config_Ptr->timer1_prescaler & 0x07);

	if((Config_Ptr->timer1_mode != TIMER1_PWM_FAST_MODE_TOP_OCR1A) && (Config_Ptr->timer1_mode != TIMER1_PWM_FAST_MODE_TOP_ICR1)){
		TCCR1A |= (1<<FOC1A) | (1<<FOC1B);
	}

	if((Config_Ptr->timer1_mode == TIMER1_PWM_FAST_MODE_TOP_ICR1) &&(Config_Ptr->timer1_mode == TIMER1_PWM_FAST_MODE_TOP_OCR1A) ){
		if(Config_Ptr->index==TIMER1A)
		{
			GPIO_setupPinDirection(OCR1A_OCR1B_ENABLE_PORT_ID, OCR1A_ENABLE_PIN_ID,PIN_OUTPUT);
		}
		else if(Config_Ptr->index==TIMER1B)
		{
			GPIO_setupPinDirection(OCR1A_OCR1B_ENABLE_PORT_ID, OCR1B_ENABLE_PIN_ID,PIN_OUTPUT);
		}
	}
	if(Config_Ptr->timer1_mode != TIMER1_NORMAL_MODE){
		if(Config_Ptr->index == TIMER1A){
			TCCR1A = (TCCR1A & 0x3F) | ((Config_Ptr->timer1_compare_mode & 0x03)<<6);
			OCR1A = Config_Ptr->compare_value;
			SET_BIT(TIMSK,OCIE1A);
		}
		else if(Config_Ptr->index == TIMER1B){
			TCCR1A=(TCCR1A & 0xCF)|((Config_Ptr->timer1_compare_mode & 0x03)<<4); //set compare match event
			OCR1B=Config_Ptr->compare_value; //define compare value
			SET_BIT(TIMSK,OCIE1B); //enable compare interrupt
		}
	}
	else
	{
		SET_BIT(TIMSK,TOIE1); //enable overflow interrupt
	}
}
/*
 * Description:Function to disable the Timer.
 * Input: None
 * Output: None
 */
void Timer1_deInit(void){
	TCCR1A = 0 ;
	TCCR1B = 0 ;
	TCNT1 = 0 ;
	OCR1A = 0 ;
	OCR1B = 0 ;
	CLEAR_BIT(TIMSK,OCIE1A);
	CLEAR_BIT(TIMSK,OCIE1B);
	CLEAR_BIT(TIMSK,TOIE1);
}
/*
 * Description: Function to set the Call Back function address.
 * Input: None
 * Output: None
 */
void Timer1_setCallBack(void(*a_ptr)(void)){
	g_ptr_t1 = a_ptr ;
}

void Timer1_pwmAdjust(Timer1_ConfigType *ptr_sturct ,uint16 duty_cycle)
{
	duty_cycle  = (uint16)(((uint16)255*duty_cycle)/100); //define compare value
	ptr_sturct->compare_value = duty_cycle;
}
/*
 * Description: Function to change OCR value for Changing duty cycle
 * Input: Pointer to structure
 * Return: None
 */
void Timer1_changeOcr_value(const Timer1_ConfigType * Config_Ptr){
	if(Config_Ptr->index == TIMER1A){
		OCR1A = Config_Ptr->compare_value;
	}
	else if(Config_Ptr->index == TIMER1B){
		OCR1B = Config_Ptr->compare_value;
	}
}
void Timer1_Pause(void){
	TCCR1B &= 0xF8 ;
}
void Timer1_Resume(TIMER1_PRESCALER prescaler){
	/* Configure Prescaler  in TCCR1B registers */
	TCCR1B = (TCCR1B & 0xF8) | (prescaler & 0x07);
}
void Timer1_Reset(void){
	TCNT1 = 0 ;
}
#endif
