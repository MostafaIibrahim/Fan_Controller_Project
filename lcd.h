/*----------------------------------------------------------------------------------------------
 * File Name:    lcd.h                                                                         *
 * Author:       Mustafa Ibrahim                                                               *
 * Data Created: Apr 4, 2023                                                                   *
 * Description:  header file for the ATmega32 LCD driver.                                      *
 *---------------------------------------------------------------------------------------------*/

#ifndef LCD_H_
#define LCD_H_
#include "std_types.h"

/**********************************************************************************************
 *                                 Static configuration                                       *
 **********************************************************************************************/
#define LCD_DATA_BITS_MODE      8

#if ((LCD_DATA_BITS_MODE != 8) && (LCD_DATA_BITS_MODE != 4))
#error "Number of Data bits should be equal 4 or 8"
#endif

/* Configure RS port and pin */
#define LCD_RS_PORT_ID                        PORTD_ID
#define LCD_RS_PIN_ID                         PIN0_ID
/* Configure ENABLE port and pin */
#define LCD_ENABLE_PORT_ID                    PORTD_ID
#define LCD_ENABLE_PIN_ID                     PIN2_ID
/* Configure LCD PORT */
#define LCD_DATA_PORT_ID                      PORTC_ID

#if (LCD_DATA_BITS_MODE == 4)
/* Pins of data bus */
#define LCD_DB4_PIN_ID                        PIN3_ID
#define LCD_DB5_PIN_ID                        PIN4_ID
#define LCD_DB6_PIN_ID                        PIN5_ID
#define LCD_DB7_PIN_ID                        PIN6_ID
#endif
/* Configure LCD commands HEX code */
#define LCD_CLEAR_DSPLAY_SCREEN               0x01
#define LCD_CURSOR_OFF                        0x0C
#define LCD_CURSOR_ON                         0x0E
#define LCD_TWO_LINES_EIGHT_BITS_MODE         0x38
#define LCD_TWO_LINES_FOUR_BITS_MODE          0x28
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT1    0X33
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT2    0X32
#define LCD_CURSOR_TO_BEGIN                   0x80

/**********************************************************************************************
 *                                 Functions Prototypes                                       *
 **********************************************************************************************/
/*
 * Description:
 *  Initialization of LCD
 */
void LCD_init(void);
/*
 * Description:
 * Function to send required commands to LCD
 */
void LCD_sendCommand(uint8 command);
/*
 * Description:
 * Function to send required data to LCD
 */
void LCD_displayCharacter(uint8 data);
/*
 * Description:
 * Function to display string
 */
void LCD_displayString(const char *string);
/*
 * Description:
 * Function to move Cursor to required address
 * Arguments : Row and Column
 */
void LCD_moveCursor(uint8 row , uint8 column);
/*
 * Description:
 * Function to display string in required place
 * Arguments : row and column and string
 */
void LCD_displayStringRowColumn(uint8 row,uint8 column,const char *string);
/*
 * Description:
 * Function to convert any number to string
 * Arguments: string
 */
void LCD_intgerToString(int number);
/*
 * Description:
 * Function to clear screen
 */
void LCD_clearScrean();

#endif /* LCD_H_ */
