
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


/*
 * LCD Datasheet instructions and values
 */

// DDRAM address of first char of row 1
#define LCD_START_ROW_1			0x00
// DDRAM address of first char of row 2
#define LCD_START_ROW_2			0x40

// Cursor and Display ON/OFF Instruction
#define LCD_CUSOR_ON			0X02
#define	LCD_CURSOR_OFF			0x00

#define LCD_CURSOR_BLINK_ON		0x01
#define LCD_CURSOR_BLINK_OFF	0x00

#define LCD_DISPLAY_ON			0x04
#define LCD_DISPLAY_OFF			0x00;


// Display cursor shift instructions
#define LCD_DISPLAY_SHIFT		0x08
#define LCD_CURSOR_MOVE			0x00
#define LCD_RIGHT_SHIFT			0x04
#define LCD_LEFT_SHIFT			0x00


// Instructions bit location
#define LCD_CLEAR_DISPLAY			0x01

#define LCD_CURSOR_HOME				0x02
#define LCD_CHARACTER_ENTRY_MODE	0x04
#define LCD_DISPLAY_CURSOR_ON_OFF	0x08
#define LCD_DISPLAY_CURSOR_SHIFT 	0x10
#define LCD_FUNCTION_SET			0x20
#define LCD_SET_CGRAM_ADDRESS	 	0x40
#define LCD_SET_DDRAM_ADDRESS	 	0x80

/* Character entry mode instructions */
#define LCD_INCREMENT				0x02	// Initialization setting
#define LCD_DECREMENT				0x00
#define LCD_DISPLAY_SHIFT_ON		0x01
#define LCD_DISPLAY_SHIFT_OFF		0x00	// Initialization setting


// Temprory Initialization Commands
#define LCD_8BITMODEDL		0x38
#define LCD_4BITMODEDL		0x28
#define LCD_DisCurBlink		0x0F
#define LCD_INCCurNoShift	0x06
#define LCD_CurPosition		0x80


#define DATA 	1
#define CMD		0


/*
 * LCD Flags
 */
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00

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





//#endif /* DRIVERS_INC_STM32F103XX_LCD_DRIVER_H_ */
