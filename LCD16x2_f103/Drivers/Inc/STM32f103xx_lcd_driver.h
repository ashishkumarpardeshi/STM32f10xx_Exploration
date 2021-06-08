
/*
 * STM32f103xx_lcd16x2_driver.h
 *
 *  Created on: Mar 27, 2021
 *      Author: ashish
 */

#ifndef STM32F103XX_LCD_DRIVER_H_
#define STM32F103XX_LCD_DRIVER_H_


#include "STM32f103xx.h"					// including target header file

#include "STM32f103xx_gpio_driver.h"		// including GPIO Driver header file

/******************************************************************************************************
 * 	User can edit these macros for defining display type, LCD Control bits, LCD Data bits etc
 *****************************************************************************************************/

/****** Define Display Type here *********************************/

//Number of Rows of the display (upto 4 only)
#define LCD_ROWS			2

//Number of Cols of the display (16 or 20)
#define LCD_COLS			16

// Define Data Mode (4-Bit or 8-Bit) for Display operation

#define LCD_DATA_MODE		4	// or 8

//----------------------------------------------------------------

// Define LCD Control Port/lines (All Control lines should be on same Port)

#define LCD_CONTROL_PORT	GPIOB

#define LCD_RS_PIN			GPIO_PIN_NO_9
#define LCD_EN_PIN			GPIO_PIN_NO_8

//----------------------------------------------------------------

// Define LCD Data Port/lines (All Data lines should be on same Port)

#define LCD_DATA_PORT		GPIOB


#define LCD_D4_PIN			GPIO_PIN_NO_7
#define LCD_D5_PIN			GPIO_PIN_NO_6
#define LCD_D6_PIN			GPIO_PIN_NO_5
#define LCD_D7_PIN			GPIO_PIN_NO_4

//-----------------------------------------------------------------

/******************************************************************************************************
 * 		Structure Variables for LCD Control GPIO and Data GPIO Configuration
 *****************************************************************************************************/

//GPIO_Handle_t lcd_Control, lcd_Data;

/*****************************************************************************************************/


/******************************************************************************************************
 * 		Macros for LCD instructions
 *****************************************************************************************************/

/* Display Clearing Instruction  */
#define LCD_CLEAR_DISPLAY			0x01

/* DReturn Home Instruction  */
#define LCD_RETURN_HOME				0x02

/* Character entry mode instructions */
#define LCD_INC_SHIFT_OFF			0x06	// Initialization setting
#define LCD_DEC_SHIFT_OFF			0x04
#define LCD_INC_SHIFT_ON			0x07
#define LCD_DEC_SHIFT_ON			0x05	// Initialization setting

/*Display ON/OFF Control instructions */
#define LCD_DISPLAY_ON							0x0C
#define LCD_DISPLAY_ON_CURSOR_ON				0x0E
#define LCD_DISPLAY_ON_BLINK_ON					0x0D
#define LCD_DISPLAY_ON_CURSOR_ON_BLINK_ON		0x0F
#define LCD_DISPLAY_OFF_CURSOR_OFF_BLINK_OFF	0x08


// Cursor and Display shift instructions
#define LCD_DISPLAY_SHIFT_RIGHT		0x1C
#define LCD_DISPLAY_SHIFT_LEFT		0x18
#define LCD_CURSOR_SHIFT_RIGHT		0x14
#define LCD_CURSOR_SHIFT_LEFT		0x10


// Function Set Instructions

/***** 8-Bit Data Lenght **********************/
#define LCD_8BIT_5X8_2LINE			0x38
#define LCD_8BIT_5x8_1LINE			0x30
#define LCD_8BIT_5X10_2LINE			0x3C
#define LCD_8BIT_5x10_1LINE			0x34

/***** 4-Bit Data Lenght **********************/
#define LCD_4BIT_5X8_2LINE			0x28
#define LCD_4BIT_5x8_1LINE			0x20
#define LCD_4BIT_5X10_2LINE			0x2C
#define LCD_4BIT_5x10_1LINE			0x24

// Row and Col initial Address
#define LCD_ROW0COL0_ADDR			0x80
#define LCD_ROW1COL0_ADDR			0xC0
#define LCD_ROW2COL0_ADDR			0x94
#define LCD_ROW3COL0_ADDR			0xD4

// LCD Macros Flags


#define DATA 	1
#define CMD		0
#define RIGHT	1
#define LEFT	0


// -----------------------------------------------------------------------------------------------------

// Temprory Initialization Commands
/*#define LCD_8BITMODEDL		0x38
#define LCD_4BITMODEDL		0x28
#define LCD_DisCurBlink		0x0F
#define LCD_INCCurNoShift	0x06
#define LCD_CurPosition		0x80*/


/******************************************************************************************************
 * 							           APIs Supported by this driver
 * 		For more details about APIs check the function definitions in STM32f103xx_lcd_driver.c
 *
 *****************************************************************************************************/

/*
 * Init LCD
 */
void LCD_Init();

/*
 * Clear LCD Display
 */

void LCD_Clear(void);

/*
 * Set Cursor with respective to  Rows(0 or 1), Cols (0 to 15)
 */
void LCD_SetCursor(uint8_t row, uint8_t col);

/*
 * Scroll the Display right/left
 */
void LCD_Display_Scroll(uint8_t direction);

/*
 * Shift the cursor right/left
 */
void LCD__Cursor_Shift(uint8_t direction);

/*
 * Write Character to LCD
 */
void LCD_WriteChar(uint8_t character);

/*
 * Write String to LCD
 */
void LCD_WriteString(const char* string);

/*
 * Write Integer value to LCD
 */
void LCD_WriteInteger(uint16_t intvalue);
/*
 * Delay in Milliseconds
 */
void delay_ms(uint32_t ms);

/*
 * Delay in Microseconds
 */
void delay_us(uint32_t us);

/********************************* API Declaration Ends Here ******************************************/

#endif /* STM32F103XX_LCD_DRIVER_H_ */

