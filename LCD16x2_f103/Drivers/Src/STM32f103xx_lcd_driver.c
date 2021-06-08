/*
 * STM32f103xx_lcd_driver.c
 *
 *  Created on: Apr 3, 2021
 *      Author: ashish
 */

#include "STM32f103xx.h"					// including target header file

#include "STM32f103xx_lcd_driver.h"			// including LCD Driver

//#include "STM32f103xx_gpio_driver.h"


/*
 * Write either Command or Data to LCD
 */
static void LCD_Write(uint8_t data, uint8_t rs);

/*
 * Enable Pulse (High to Low Transition)
 */
static void LCD_En_Pulse();




/*******************************************************************************************
 *                     APIs Function Definition for LCD Display
 *******************************************************************************************/


void LCD_Init() // Initialize the LCD
{

	GPIO_Handle_t lcd_Control, lcd_Data;

/*************** GPIO Clock Enable *********************************************************/

	GPIO_PeriClkControl(LCD_CONTROL_PORT, ENABLE);		// Enable Clock for LCD Control Port
	GPIO_PeriClkControl(LCD_DATA_PORT, ENABLE);			// Enable Clock for LCD Data Port

/*******************************************************************************************/

/*************** AFIO Re-mapping PB3, PB4 & PA15 as an GPIO pins ******************************************************************************************************************************/

	// By default after reset these pins act as JTDO, NJTRST & JTDI respectively (ie JTAG-DP)
	// If we want them to use as GPIO we need to remap them using AFIO_MAPR register's SWJ_CFG [2:0] bits
	// SWJ_CFG [2:0] = 010; // JTAG-DP Disabled and SW-DP Enabled

	if((LCD_DATA_PORT == GPIOB )&& (LCD_CONTROL_PORT == GPIOB) && ((LCD_D7_PIN == 4) | (LCD_D6_PIN == 4) | (LCD_D5_PIN == 4) | (LCD_D4_PIN == 4) | (LCD_RS_PIN == 4) | (LCD_EN_PIN == 4)))
	{
		AFIO_PCLK_EN();

		AFIO -> MAPR |= 0x02000000;			// GPIO PB4, PB3 and PA15 will be free

	}

/**********************************************************************************************************************************************************************************************/

/*************** GPIO configuration for LCD ************************************************/

	lcd_Control.pGPIOx = LCD_CONTROL_PORT;
	lcd_Control.GPIO_PinConfig.GPIO_PinNumber = LCD_RS_PIN;
	lcd_Control.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUTPUT_2MHZ;
	lcd_Control.GPIO_PinConfig.GPIO_PinOutInType = GPIO_OP_PP;
	GPIO_Init(&lcd_Control);


	lcd_Control.GPIO_PinConfig.GPIO_PinNumber = LCD_EN_PIN;
	GPIO_Init(&lcd_Control);

	lcd_Data.pGPIOx = LCD_DATA_PORT;
	lcd_Data.GPIO_PinConfig.GPIO_PinNumber = LCD_D4_PIN;
	lcd_Data.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUTPUT_2MHZ;
	lcd_Data.GPIO_PinConfig.GPIO_PinOutInType = GPIO_OP_PP;

	GPIO_Init(&lcd_Data);


	lcd_Data.GPIO_PinConfig.GPIO_PinNumber = LCD_D5_PIN;
	GPIO_Init(&lcd_Data);


	lcd_Data.GPIO_PinConfig.GPIO_PinNumber = LCD_D6_PIN;
	GPIO_Init(&lcd_Data);


	lcd_Data.GPIO_PinConfig.GPIO_PinNumber = LCD_D7_PIN;
	GPIO_Init(&lcd_Data);

	GPIO_WritePin(LCD_CONTROL_PORT, LCD_RS_PIN, GPIO_PIN_RESET);
	GPIO_WritePin(LCD_CONTROL_PORT, LCD_EN_PIN, GPIO_PIN_RESET);

	GPIO_WritePin(LCD_DATA_PORT, LCD_D4_PIN, GPIO_PIN_RESET);
	GPIO_WritePin(LCD_DATA_PORT, LCD_D5_PIN, GPIO_PIN_RESET);
	GPIO_WritePin(LCD_DATA_PORT, LCD_D6_PIN, GPIO_PIN_RESET);
	GPIO_WritePin(LCD_DATA_PORT, LCD_D7_PIN, GPIO_PIN_RESET);
/*******************************************************************************************/

	/*lcd_Control.pGPIOx -> BRR = 1 << LCD_RS_PIN;
	lcd_Data.pGPIOx -> BSRR = 1 << LCD_D4_PIN;
	lcd_Data.pGPIOx -> BSRR = 1 << LCD_D5_PIN;
	LCD_En_Pulse();*/

/*************** LCD Initialization Sequence ************************************************/

	delay_ms(40);						// Wait for 40 ms LCD initialization after LCD power ON

	LCD_Write(0x03, CMD);				// Send 0x03;

	delay_ms(5);						// Wait for 5 ms

	LCD_Write(0x03, CMD);				// again Send 0x03

	delay_us(150);						// wait for 100 us

	LCD_Write(0x03, CMD);				// again Send 0x03;

	LCD_Write(0x02, CMD);				// Send 0x02;

	//LCD_Write(LCD_4BITMODEDL, CMD);		// Configure LCD in 4-Bit Mode (0x28)
	LCD_Write(LCD_4BIT_5X8_2LINE, CMD);

	//LCD_Write(LCD_DisCurBlink, CMD);	//	Display ON, Cursor ON, Blink ON
	LCD_Write(LCD_DISPLAY_ON_CURSOR_ON, CMD);

	LCD_Write(LCD_CLEAR_DISPLAY, CMD);	// Clear the display

	delay_ms(2);						// After clear cmd wait for 2 ms

	//LCD_Write(LCD_INCCurNoShift, CMD);	//  Increment the Cursor
	LCD_Write(LCD_INC_SHIFT_OFF, CMD);

	//LCD_Write(LCD_CurPosition, CMD);	//  Initial Cursor Position 0th position @ Line 1
	LCD_Write(LCD_ROW0COL0_ADDR, CMD);


/*********************************************************************************************/

}

/**
  ******************************************************************************
  * @brief	Scrol Display Right/Left
  * @param	RIGHT or LEFT
  * @retval	None
  ******************************************************************************
  */
void LCD_Display_Scroll(uint8_t direction)
{
	if(direction == 1)
	{
		LCD_Write(LCD_DISPLAY_SHIFT_RIGHT, CMD);
	}
	else
	{
		LCD_Write(LCD_DISPLAY_SHIFT_LEFT, CMD);
	}

}

/**
  ******************************************************************************
  * @brief	Shift Cursor Right/Left
  * @param	RIGHT or LEFT
  * @retval	None
  ******************************************************************************
  */
void LCD__Cursor_Shift(uint8_t direction)
{
	if(direction == 1)
	{
		LCD_Write(LCD_CURSOR_SHIFT_RIGHT, CMD);
	}
	else
	{
		LCD_Write(LCD_CURSOR_SHIFT_LEFT, CMD);
	}

}


/**
  ******************************************************************************
  * @brief	Clear the LCD.
  * @param	None
  * @retval	None
  ******************************************************************************
  */
void LCD_Clear(void)
{

	LCD_Write(LCD_CLEAR_DISPLAY, CMD);

	delay_ms(2);						// After clear cmd wait for 2 ms

}



/**
  ******************************************************************************
  * @brief	Set LCD cursor to specific position via Row and Col.
  * @param	LCD row (row)
  * @param	LCD column (col)
  * @retval	None
  ******************************************************************************
  */

void LCD_SetCursor(uint8_t row, uint8_t col)
{
	#if LCD_ROWS == 1

		LCD_Write(LCD_ROW0COL0_ADDR + col,CMD);

	#elif LCD_ROWS == 2

		if(row == 0)
		{
			col = col + LCD_ROW0COL0_ADDR;
		}
		else
		{
			col = col + LCD_ROW1COL0_ADDR;
		}

		LCD_Write(col,CMD);

	#elif LCD_ROWS == 4

		if(row == 0)
		{
			col = col + LCD_ROW0COL0_ADDR;
		}
		else if(row == 1)
		{
			col = col + LCD_ROW1COL0_ADDR;
		}
		else if(row == 2)
		{
			col = col + LCD_ROW2COL0_ADDR;
		}
		else
		{
			col = col + LCD_ROW3COL0_ADDR;
		}

		LCD_Write(col,CMD);

	#endif

}

//
/**
  ******************************************************************************
  * @brief	Send Command/Data to LCD RAM.
  * @param	LCD Data or Command (data)
  * @param	LCD Register Select (rs)
  * @retval	None
  ******************************************************************************
  */

static void LCD_Write(uint8_t data, uint8_t rs)
{

	/* RS = 0 (CMD) for commands
	 * RS = 1 (DATA) for Data
	 */

	//lcd_Control.pGPIOx -> BRR = (1 << LCD_D4_PIN) | (1 << LCD_D5_PIN) | (1 << LCD_D6_PIN) | (1 << LCD_D7_PIN); // Clear all Data lines of LCD
	GPIO_WritePin(LCD_DATA_PORT, LCD_D4_PIN, GPIO_PIN_RESET);
	GPIO_WritePin(LCD_DATA_PORT, LCD_D5_PIN, GPIO_PIN_RESET);
	GPIO_WritePin(LCD_DATA_PORT, LCD_D6_PIN, GPIO_PIN_RESET);
	GPIO_WritePin(LCD_DATA_PORT, LCD_D7_PIN, GPIO_PIN_RESET);

	// Send Higher Nibble of Data First
	if(data & 0x80)
		//lcd_Data.pGPIOx -> BSRR = 1 << LCD_D7_PIN;
		GPIO_WritePin(LCD_DATA_PORT, LCD_D7_PIN, GPIO_PIN_SET);
	if(data & 0x40)
		//lcd_Data.pGPIOx -> BSRR = 1 << LCD_D6_PIN;
		GPIO_WritePin(LCD_DATA_PORT, LCD_D6_PIN, GPIO_PIN_SET);
	if(data & 0x20)
		//lcd_Data.pGPIOx -> BSRR = 1 << LCD_D5_PIN;
		GPIO_WritePin(LCD_DATA_PORT, LCD_D5_PIN, GPIO_PIN_SET);
	if(data & 0x10)
		//lcd_Data.pGPIOx -> BSRR = 1 << LCD_D4_PIN;
		GPIO_WritePin(LCD_DATA_PORT, LCD_D4_PIN, GPIO_PIN_SET);

    // Write to LCD RS Pin for Data/Command
	if(rs == DATA)
	{
		//lcd_Control.pGPIOx -> BSRR = 1 << LCD_RS_PIN;
		GPIO_WritePin(LCD_CONTROL_PORT, LCD_RS_PIN, GPIO_PIN_SET);
	}
	else
	{
		//lcd_Control.pGPIOx -> BRR = 1 << LCD_RS_PIN;
		GPIO_WritePin(LCD_CONTROL_PORT, LCD_RS_PIN, GPIO_PIN_RESET);
	}

	LCD_En_Pulse();

	//lcd_Control.pGPIOx -> BRR = (1 << LCD_D4_PIN) | (1 << LCD_D5_PIN) | (1 << LCD_D6_PIN) | (1 << LCD_D7_PIN); // Clear all Data lines of LCD

	GPIO_WritePin(LCD_DATA_PORT, LCD_D4_PIN, GPIO_PIN_RESET);
	GPIO_WritePin(LCD_DATA_PORT, LCD_D5_PIN, GPIO_PIN_RESET);
	GPIO_WritePin(LCD_DATA_PORT, LCD_D6_PIN, GPIO_PIN_RESET);
	GPIO_WritePin(LCD_DATA_PORT, LCD_D7_PIN, GPIO_PIN_RESET);

	// Send Lower Nibble of Data First
	if(data & 0x08)
		//lcd_Data.pGPIOx -> BSRR = 1 << LCD_D7_PIN;
		GPIO_WritePin(LCD_DATA_PORT, LCD_D7_PIN, GPIO_PIN_SET);
	if(data & 0x04)
		//lcd_Data.pGPIOx -> BSRR = 1 << LCD_D6_PIN;
		GPIO_WritePin(LCD_DATA_PORT, LCD_D6_PIN, GPIO_PIN_SET);
	if(data & 0x02)
		//lcd_Data.pGPIOx -> BSRR = 1 << LCD_D5_PIN;
		GPIO_WritePin(LCD_DATA_PORT, LCD_D5_PIN, GPIO_PIN_SET);
	if(data & 0x01)
		//lcd_Data.pGPIOx -> BSRR = 1 << LCD_D4_PIN;
		GPIO_WritePin(LCD_DATA_PORT, LCD_D4_PIN, GPIO_PIN_SET);

	LCD_En_Pulse();
}

static void LCD_En_Pulse()
{
	//lcd_Control.pGPIOx -> BSRR = 1 << LCD_EN_PIN;
	GPIO_WritePin(LCD_CONTROL_PORT, LCD_EN_PIN, GPIO_PIN_SET);
	delay_ms(1);

	//lcd_Control.pGPIOx -> BRR = 1 << LCD_EN_PIN;
	GPIO_WritePin(LCD_CONTROL_PORT, LCD_EN_PIN, GPIO_PIN_RESET);
	delay_ms(2);

}

/**
  ******************************************************************************
  * @brief	Write a Character on LCD
  * @param	Character to display
  * @retval	None
  ******************************************************************************
*/
void LCD_WriteChar(uint8_t character)
{
	LCD_Write(character, DATA);
}

/**
  ******************************************************************************
  * @brief	Write a String on LCD
  * @param	String to display
  * @retval	None
  ******************************************************************************
*/
void LCD_WriteString(const char* string)
{
	while(*string)
	{
		LCD_WriteChar(*string++);
		delay_ms(1);
	}
}

/**
  ******************************************************************************
  * @brief	Write an Integer on LCD
  * @param	Integer to display
  * @retval	None
  ******************************************************************************
*/
void LCD_WriteInteger(uint16_t intvalue)
{
	uint8_t i = 0;

	if(intvalue > 999 && intvalue <= 9999)
	{
		i = intvalue / 1000;		// divide 4-digit value by 1000 gives thousand's place integer
		LCD_WriteChar(i + 48);

		i = (intvalue / 100) % 10;	// Hundred's place Integer
		LCD_WriteChar(i + 48);

		i = (intvalue % 100) / 10;	// Ten's place Integer
		LCD_WriteChar(i + 48);

		i = (intvalue % 100) % 10;	// One's place Integer
		LCD_WriteChar(i + 48);
	}
	else if(intvalue > 99 && intvalue <= 999)
	{

		i = intvalue / 100;	// Hundred's place Integer
		LCD_WriteChar(i + 48);

		i = (intvalue % 100) / 10;	// Ten's place Integer
		LCD_WriteChar(i + 48);

		i = (intvalue % 100) % 10;	// One's place Integer
		LCD_WriteChar(i + 48);
	}
	else if(intvalue > 9 && intvalue <= 99)
	{

		i = intvalue / 10;			// Ten's place Integer
		LCD_WriteChar(i + 48);

		i = intvalue % 10;			// One's place Integer
		LCD_WriteChar(i + 48);
	}
	else
	{
		LCD_WriteChar(intvalue + 48);
	}

}


/**
  ******************************************************************************
  * @brief	Delay in milliseconds
  * @param	time in ms
  * @retval	None
  ******************************************************************************
*/
void delay_ms(uint32_t ms)
{
	uint32_t delay = ms * 668;
	for (int i = 0; i < delay; i++)  // 325000 = 500 msec rough estimation
		__asm__("nop");
}


/**
  ******************************************************************************
  * @brief	Delay in milliseconds
  * @param	time in ms
  * @retval	None
  ******************************************************************************
*/
void delay_us(uint32_t us)
{
	uint32_t delay = (us * 0.668) + 1;
	for (int i = 0; i < delay; i++)  // 325000 = 500 msec rough estimation
		__asm__("nop");
}

