/*
 * timer.h
 *
 *  Created on: Jun 18, 2023
 *      Author: SOFT ZONE
 */

#ifndef TIMER_H_
#define TIMER_H_
#include "std_types.h"

/*                                   Static Configuration                                      */
#define TIMER0

#ifdef TIMER0
#define T0_ENABLE_PORT_ID      PORTB_ID
#define T0_ENABLE_PIN_ID       PIN3_ID
/*                                   USER Define Type                                         */

typedef enum{
	TIMER0_NORMAL_MODE,TIMER0_CTC_MODE=2,TIMER0_PWM_FAST_MODE
}TIMER0_WAVE_GENERATION;
typedef enum{
	TIMER0_NORMAL_PORT_NON_PWM,TIMER0_TOGGLE_OC0_NON_PWM,TIMER0_CLEAR_OC0_NON_PWM,TIMER0_SET_OC0_NON_PWM
}TIMER0_OC0_NON_PWM;
typedef enum{
	TIMER0_NORMAL_PORT_FAST_PWM,TIMER0_CLEAR_OC0_FAST_PWM = 2,TIMER0_SET_OC0_FAST_PWM
}TIMER0_OC0_FAST_PWM;
typedef enum{
	TIMER0_NO_CLK,TIMER0_NO_PRESCALE,TIMER0_8_PRESCALE,TIMER0_64_PRESCALE,TIMER0_256_PRESCALE,\
	TIMER0_1024_PRESCALE,TIMER0_EXTERNAL_CLK_FALLING,TIMER0_EXTERNAL_CLK_RISING
}TIMER0_PRESCALER;
typedef struct{
	uint8                              initial_value;
	uint8                              compare_value;
	TIMER0_WAVE_GENERATION             timer0_mode;
	TIMER0_PRESCALER                   timer0_prescaler;
	TIMER0_OC0_NON_PWM                 timer0_mode_non_pwm;
	TIMER0_OC0_FAST_PWM                timer0_mode_fast_pwm;
}Timer0_ConfigType;

/*                                   Function Prototype                                      */
/*
 * Description: Function to initialize the Timer driver
 * Input: pointer to the configuration structure with type Timer_ConfigType.
 * Output: None
 */
void Timer0_init(const Timer0_ConfigType * Config_Ptr);
/*
 * Description:Function to disable the Timer.
 * Input: None
 * Output: None
 */
void Timer0_deInit(void);
/*
 * Description: Function to set the Call Back function address.
 * Input: None
 * Output: None
 */
void Timer0_setCallBack(void(*a_ptr)(void));
void Timer0_pwmAdjust(uint8 duty_cycle);
#endif

/*********************************************************************************************/
#ifdef TIMER1

#define T1_ENABLE_PORT_ID               PORTB_ID
#define T1_ENABLE_PIN_ID                PIN1_ID

#define OCR1A_OCR1B_ENABLE_PORT_ID      PORTD_ID

#define OCR1A_ENABLE_PIN_ID             PIN4_ID
#define OCR1B_ENABLE_PIN_ID             PIN5_ID

/*                                   USER Define Type                                         */

typedef enum{
	TIMER1_NORMAL_MODE,TIMER1_CTC_MODE_TOP_OCR1A=4,\
	TIMER1_CTC_MODE_TOP_ICR1 = 12,\
	TIMER1_PWM_FAST_MODE_TOP_ICR1=14,TIMER1_PWM_FAST_MODE_TOP_OCR1A
}TIMER1_WAVE_GENERATION;
typedef enum{
	TIMER1_NORMAL,TIMER1_TOGGLE,TIMER1_CLEAR,TIMER1_SET
}TIMER1_COMPARE_OUTPUT_MODE;
typedef enum{
	TIMER1_NO_CLK,TIMER1_NO_PRESCALE,TIMER1_8_PRESCALE,TIMER1_64_PRESCALE,TIMER1_256_PRESCALE,\
	TIMER1_1024_PRESCALE,TIMER1_EXTERNAL_CLK_FALLING,TIMER1_EXTERNAL_CLK_RISING
}TIMER1_PRESCALER;
typedef enum {
	NONE,TIMER1A,TIMER1B
}Timer1_Index;
typedef struct{
	uint16                                   initial_value;
	uint16                                   compare_value;
	TIMER1_WAVE_GENERATION                   timer1_mode;
	TIMER1_PRESCALER                         timer1_prescaler;
	TIMER1_COMPARE_OUTPUT_MODE               timer1_compare_mode;
	Timer1_Index                             index;
}Timer1_ConfigType;
/*                                   Function Prototype                                      */
/*
 * Description: Function to initialize the Timer driver
 * Input: pointer to the configuration structure with type Timer_ConfigType.
 * Output: None
 */
void Timer1_init(const Timer1_ConfigType * Config_Ptr);
/*
 * Description: Function to change OCR value for Changing duty cycle
 * Input: Pointer to structure
 * Return: None
 */
void Timer1_changeOcr_value(const Timer1_ConfigType * Config_Ptr);
/*
 * Description:Function to disable the Timer.
 * Input: None
 * Output: None
 */
void Timer1_deInit(void);
void Timer1_Pause(void);
void Timer1_Resume(TIMER1_PRESCALER prescaler);
void Timer1_Reset(void);
/*
 * Description: Function to set the Call Back function address.
 * Input: None
 * Output: None
 */
void Timer1_setCallBack(void(*a_ptr)(void));
void Timer1_pwmAdjust(Timer1_ConfigType *ptr_sturct ,uint16 duty_cycle);
#endif
#endif /* TIMER_H_ */
