/*
 * STM32f103xx_lcd_driver.c
 *
 *  Created on: Apr 3, 2021
 *      Author: ashish
 */

#include "STM32f103xx.h"					// including target header file

#include "STM32f103xx_lcd_driver.h"			// including LCD Driver



/*******************************************************************************************
 *                     APIs Function Definition for LCD Display
 *******************************************************************************************/


void LCD_Init() // Initialize the LCD
{

/*************** GPIO Clock Enable *********************************************************/

	GPIO_PeriClkControl(LCD_CONTROL_PORT, ENABLE);		// Enable Clock for LCD Control Port
	GPIO_PeriClkControl(LCD_DATA_PORT, ENABLE);			// Enable Clock for LCD Data Port

/*******************************************************************************************/


/*************** GPIO configuration for LCD ************************************************/

	lcd_Control.pGPIOx = LCD_CONTROL_PORT;
	lcd_Control.GPIO_PinConfig.GPIO_PinNumber = LCD_RS_PIN;
	lcd_Control.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUTPUT_2MHZ;
	lcd_Control.GPIO_PinConfig.GPIO_PinOutInType = GPIO_OP_PP;

	GPIO_Init(&lcd_Control);

	lcd_Control.pGPIOx = LCD_CONTROL_PORT;
	lcd_Control.GPIO_PinConfig.GPIO_PinNumber = LCD_EN_PIN;
	lcd_Control.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUTPUT_2MHZ;
	lcd_Control.GPIO_PinConfig.GPIO_PinOutInType = GPIO_OP_PP;


	GPIO_Init(&lcd_Control);

	lcd_Data.pGPIOx = LCD_DATA_PORT;
	lcd_Data.GPIO_PinConfig.GPIO_PinNumber = LCD_D4_PIN;
	lcd_Data.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUTPUT_2MHZ;
	lcd_Data.GPIO_PinConfig.GPIO_PinOutInType = GPIO_OP_PP;

	GPIO_Init(&lcd_Data);

	lcd_Data.pGPIOx = LCD_DATA_PORT;
	lcd_Data.GPIO_PinConfig.GPIO_PinNumber = LCD_D5_PIN;
	lcd_Data.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUTPUT_2MHZ;
	lcd_Data.GPIO_PinConfig.GPIO_PinOutInType = GPIO_OP_PP;

	GPIO_Init(&lcd_Data);

	lcd_Data.pGPIOx = LCD_DATA_PORT;
	lcd_Data.GPIO_PinConfig.GPIO_PinNumber = LCD_D6_PIN;
	lcd_Data.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUTPUT_2MHZ;
	lcd_Data.GPIO_PinConfig.GPIO_PinOutInType = GPIO_OP_PP;

	GPIO_Init(&lcd_Data);

	lcd_Data.pGPIOx = LCD_DATA_PORT;
	lcd_Data.GPIO_PinConfig.GPIO_PinNumber = LCD_D7_PIN;
	lcd_Data.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUTPUT_2MHZ;
	lcd_Data.GPIO_PinConfig.GPIO_PinOutInType = GPIO_OP_PP;

	GPIO_Init(&lcd_Data);

/*******************************************************************************************/

	/*lcd_Control.pGPIOx -> BRR = 1 << LCD_RS_PIN;
	lcd_Data.pGPIOx -> BSRR = 1 << LCD_D4_PIN;
	lcd_Data.pGPIOx -> BSRR = 1 << LCD_D5_PIN;
	LCD_En_Pulse();*/

/*************** LCD Initialization Sequence ************************************************/

	delay_ms(20);						// Wait for LCD initialization after LCD power ON

	LCD_Write(0x02, CMD);				// 4-Bit Mode

	LCD_Write(LCD_4BITMODEDL, CMD);		// Configure LCD in 4-Bit Mode

	LCD_Write(LCD_DisCurBlink, CMD);	//	Display ON, Cursor ON, Blink ON

	LCD_Write(LCD_INCCurNoShift, CMD);	//  Increment the Cursor

	LCD_Write(LCD_CLEAR_DISPLAY, CMD);	// Clear the display

	LCD_Write(LCD_CurPosition, CMD);	//  Initial Cursor Position 0th position @ Line 1


/*********************************************************************************************/

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

		LCD_Write(col + 0x80,CMD);

	#elif LCD_ROWS == 2

		if(row == 0)
		{
			col = col + 0x80;
		}
		else
		{
			col = col + 0xC0;
		}

		LCD_Write(col,CMD);

	#elif LCD_ROWS == 4

		if(row == 0)
		{
			col = col + 0x80;
		}
		else if(row == 1)
		{
			col = col + 0xC0;
		}
		else if(row == 2)
		{
			col = col + 0x94;
		}
		else
		{
			col = col + 0xD4;
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

void LCD_Write(uint8_t data, uint8_t rs)
{


	lcd_Control.pGPIOx -> BRR = (1 << LCD_D4_PIN) | (1 << LCD_D5_PIN) | (1 << LCD_D6_PIN) | (1 << LCD_D7_PIN); // Clear all Data lines of LCD

	// Send Higher Nibble of Data First
	if(data & 0x80)
		lcd_Data.pGPIOx -> BSRR = 1 << LCD_D7_PIN;
	if(data & 0x40)
		lcd_Data.pGPIOx -> BSRR = 1 << LCD_D6_PIN;
	if(data & 0x20)
		lcd_Data.pGPIOx -> BSRR = 1 << LCD_D5_PIN;
	if(data & 0x10)
		lcd_Data.pGPIOx -> BSRR = 1 << LCD_D4_PIN;

    // Write to LCD RS Pin for Data/Command
	if(rs == DATA)
	{
		lcd_Control.pGPIOx -> BSRR = 1 << LCD_RS_PIN;
	}
	else
	{
		lcd_Control.pGPIOx -> BRR = 1 << LCD_RS_PIN;
	}


	LCD_En_Pulse();

	lcd_Control.pGPIOx -> BRR = (1 << LCD_D4_PIN) | (1 << LCD_D5_PIN) | (1 << LCD_D6_PIN) | (1 << LCD_D7_PIN); // Clear all Data lines of LCD

	// Send Lower Nibble of Data First
	if(data & 0x08)
		lcd_Data.pGPIOx -> BSRR = 1 << LCD_D7_PIN;
	if(data & 0x04)
		lcd_Data.pGPIOx -> BSRR = 1 << LCD_D6_PIN;
	if(data & 0x02)
		lcd_Data.pGPIOx -> BSRR = 1 << LCD_D5_PIN;
	if(data & 0x01)
		lcd_Data.pGPIOx -> BSRR = 1 << LCD_D4_PIN;

	LCD_En_Pulse();
}

void LCD_En_Pulse()
{
	lcd_Control.pGPIOx -> BSRR = 1 << LCD_EN_PIN;
	delay_ms(1);
	lcd_Control.pGPIOx -> BRR = 1 << LCD_EN_PIN;
	delay_ms(2);

}

void LCD_WriteChar(uint8_t character)
{
	LCD_Write(character, DATA);
}

void LCD_WriteString(const char* string)
{
	while(*string)
	{
		LCD_WriteChar(*string++);
		delay_ms(1);
	}
}

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

void delay_ms(uint32_t ms)
{
	uint32_t delay = ms * 668;
	for (int i = 0; i < delay; i++)  // 325000 = 500 msec rough estimation
		__asm__("nop");
}

void delay_us(uint32_t us)
{
	uint32_t delay = (us * 0.668) + 1;
	for (int i = 0; i < delay; i++)  // 325000 = 500 msec rough estimation
		__asm__("nop");
}

