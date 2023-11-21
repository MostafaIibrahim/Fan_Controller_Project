/*----------------------------------------------------------------------------------------------
 * File Name:    adc.c                                                                         *
 * Author:       Mustafa Ibrahim                                                               *
 * Data Created: Apr 4, 2023                                                                   *
 * Description:  source file for the ATmega32 ADC driverDriver.                                *
 *---------------------------------------------------------------------------------------------*/
#include "lcd.h"
#include "gpio.h"
#include <util/delay.h>
#include "common_macros.h"

/***********************************************************************************************
 *                                 Functions Definitions                                       *
 ***********************************************************************************************/
/*
 * Description :
 * Initialize the LCD:
 * 1. Setup the LCD pins directions by use the GPIO driver.
 * 2. Setup the LCD Data Mode 4-bits or 8-bits.
 */
void LCD_init(void)
{
	/* Setup LCD (RS-E) pins direction */
	GPIO_setupPinDirection(LCD_RS_PORT_ID,LCD_RS_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_ENABLE_PORT_ID,LCD_ENABLE_PIN_ID,PIN_OUTPUT);
	_delay_ms(20);  /* To display LCD */

	/* Setup LCD port direction for 8 and 4 bits */
#if LCD_DATA_BITS_MODE == 8
	GPIO_setupPortDirection(LCD_DATA_PORT_ID, PORT_OUTPUT);
	LCD_sendCommand(LCD_TWO_LINES_EIGHT_BITS_MODE); /* 8 Bits mode command */

#elif LCD_DATA_BITS_MODE == 4
	GPIO_setupPinDirection(LCD_DATA_PORT_ID,LCD_DB4_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID,LCD_DB5_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID,LCD_DB6_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID,LCD_DB7_PIN_ID,PIN_OUTPUT);
	/* LCD 2 lines 4 bit mode */
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT1);
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT2);
	/* 4 bits + 2 Lines + 5x7 mode command */
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE);
#endif

	LCD_sendCommand(LCD_CURSOR_OFF);
	LCD_sendCommand(LCD_CLEAR_DSPLAY_SCREEN);
}
/*
 * Description:
 * Function to send command
 */
void LCD_sendCommand(uint8 command)
{
	GPIO_writePin(LCD_RS_PORT_ID,LCD_RS_PIN_ID, LOGIC_LOW); /* Configure pin low as Command */
	_delay_ms(1);
	GPIO_writePin(LCD_ENABLE_PORT_ID,LCD_ENABLE_PIN_ID, LOGIC_HIGH);
	_delay_ms(1);

#if (LCD_DATA_BITS_MODE == 4)
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB4_PIN_ID,GET_BIT(command,4));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB5_PIN_ID,GET_BIT(command,5));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB6_PIN_ID,GET_BIT(command,6));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB7_PIN_ID,GET_BIT(command,7));
	_delay_ms(1);

	GPIO_writePin(LCD_ENABLE_PORT_ID,LCD_ENABLE_PIN_ID, LOGIC_LOW);
	_delay_ms(1);
	GPIO_writePin(LCD_ENABLE_PORT_ID,LCD_ENABLE_PIN_ID, LOGIC_HIGH);
	_delay_ms(1);

	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB4_PIN_ID,GET_BIT(command,0));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB5_PIN_ID,GET_BIT(command,1));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB6_PIN_ID,GET_BIT(command,2));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB7_PIN_ID,GET_BIT(command,3));

#elif(LCD_DATA_BITS_MODE == 8)
	GPIO_writePort(LCD_DATA_PORT_ID,command);
#endif

	_delay_ms(1);
	GPIO_writePin(LCD_ENABLE_PORT_ID,LCD_ENABLE_PIN_ID, LOGIC_LOW);
	_delay_ms(1);
}
/*
 * Description:
 * Function to send required data(character) to LCD
 */
void LCD_displayCharacter(uint8 data)
{
	GPIO_writePin(LCD_RS_PORT_ID,LCD_RS_PIN_ID, LOGIC_HIGH); /* Configure pin high as Data */
	_delay_ms(1);
	GPIO_writePin(LCD_ENABLE_PORT_ID,LCD_ENABLE_PIN_ID, LOGIC_HIGH);
	_delay_ms(1);

#if (LCD_DATA_BITS_MODE == 4)
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB4_PIN_ID,GET_BIT(data,4));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB5_PIN_ID,GET_BIT(data,5));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB6_PIN_ID,GET_BIT(data,6));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB7_PIN_ID,GET_BIT(data,7));
	_delay_ms(1);

	GPIO_writePin(LCD_ENABLE_PORT_ID,LCD_ENABLE_PIN_ID, LOGIC_LOW);
	_delay_ms(1);
	GPIO_writePin(LCD_ENABLE_PORT_ID,LCD_ENABLE_PIN_ID, LOGIC_HIGH);
	_delay_ms(1);

	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB4_PIN_ID,GET_BIT(data,0));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB5_PIN_ID,GET_BIT(data,1));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB6_PIN_ID,GET_BIT(data,2));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB7_PIN_ID,GET_BIT(data,3));

#elif(LCD_DATA_BITS_MODE == 8)
	GPIO_writePort(LCD_DATA_PORT_ID,data);
#endif

	_delay_ms(1);
	GPIO_writePin(LCD_ENABLE_PORT_ID,LCD_ENABLE_PIN_ID, LOGIC_LOW);
	_delay_ms(1);
}

/*
 * Description:
 * Function to display string
 */
void LCD_displayString(const char *string)
{
	while((*string) != '\0')
	{
		LCD_displayCharacter(*string);
		string++;
	}
}
/*
 * Description:
 * Function to move Cursor to required address
 * Arguments : Row and Column
 */
void LCD_moveCursor(uint8 row , uint8 column)
{
	uint8 adress_result;
	switch(row)
	{
	case 0: adress_result = column;
	break;
	case 1: adress_result = column + 0x40;
	break;
	case 2: adress_result = column + 0x10;
	break;
	case 3: adress_result = column + 0x50;
	}
	LCD_sendCommand(adress_result | LCD_CURSOR_TO_BEGIN); /* Enter 1 at MSB to send command */
}
/*
 * Description:
 * Function to display string in required place
 * Arguments : row and column and string
 */
void LCD_displayStringRowColumn(uint8 row,uint8 column,const char *string)
{
	LCD_moveCursor(row,column);
	LCD_displayString(string);
}
/*
 * Description:
 * Function to clear screen
 */
void LCD_clearScrean()
{
	LCD_sendCommand(LCD_CLEAR_DSPLAY_SCREEN);
}
/*
 * Description:
 * Function to convert any number to string
 * Arguments: string
 */
void LCD_intgerToString(int number)
{
	char buff[16];
	itoa(number,buff,10);
	LCD_displayString(buff);
}
