/*
 * STM32f103xx_lcd16x2_driver.h
 *
 *  Created on: Mar 27, 2021
 *      Author: ashish
 */

#ifndef STM32F103XX_LCD_DRIVER_H_
#define STM32F103XX_LCD_DRIVER_H_

#include "STM32f103xx.h"					// including target header file
#include "STM32F103xx_gpio_driver.h"		// including GPIO Driver

 /********************************************************************************
 * User can edit these macros for defining display type, LCD Control bits, LCD Data bits etc
 */


// Define Display Type here

//Number of Rows of the display (upto 4 only)
#define LCD_ROWS			2

//Number of Cols of the display (16 or 20)
#define LCD_COLS			16

// Define Data Mode (4-Bit or 8-Bit) for Display operation

#define LCD_DATA_MODE		4	// or 8


//----------------------------------------------------------------

// Define LCD Control Port/lines (All Control lines should be on same Port)

#define LCD_CONTROL_PORT	GPIOA

#define LCD_RS_PIN			GPIO_PIN_0
#define LCD_EN_PIN			GPIO_PIN_1

//----------------------------------------------------------------

// Define LCD Data Port/lines (All Data lines should be on same Port)

#define LCD_DATA_PORT		GPIOA


#define LCD_D4_PIN			GPIO_PIN_2
#define LCD_D5_PIN			GPIO_PIN_3
#define LCD_D6_PIN			GPIO_PIN_4
#define LCD_D7_PIN			GPIO_PIN_5

//-----------------------------------------------------------------

/***************************************************************************************/


/***************************************************************************************
 * LCD Datasheet instructions and values
 */


// LCD DDRAM Address

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

typedef struct
{
	GPIO_Handle_t LCD_Port;
	uint8_t RS_Pin;
	uint8_t	EN_Pin;
	uint8_t D4_Pin;
	uint8_t D5_Pin;
	uint8_t D6_Pin;
	uint8_t D7_Pin;

}LCD_PinConfig_t;

/*
 * LCD Flags
 */
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00


void LCD_Init();






#endif /* STM32F103XX_LCD_DRIVER_H_ */
