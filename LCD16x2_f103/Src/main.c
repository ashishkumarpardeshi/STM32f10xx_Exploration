/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

#include "STM32f103xx.h"					// including target header file

#include "STM32f103xx_gpio_driver.h"		// including GPIO Driver

#include "STM32f103xx_lcd_driver.h"			// including LCD Driver

#include <stdint.h>

int main(void)
{

	uint16_t i = 0;

	//GPIO_DeInit(GPIOB);

	GPIO_PeriClkControl(GPIOC, ENABLE);

	GPIO_Handle_t redled;

	redled.pGPIOx = GPIOC; //GPIOB
	redled.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13; //GPIO_PIN_NO_15;
	redled.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUTPUT_2MHZ;
	redled.GPIO_PinConfig.GPIO_PinOutInType = GPIO_OP_PP;

	GPIO_Init(&redled);

	GPIO_WritePin(GPIOC, GPIO_PIN_NO_13, GPIO_PIN_SET);


	LCD_Init();

	//LCD_Clear();

	LCD_SetCursor(0,0);

	LCD_WriteString(" Ashish ");

	LCD_SetCursor(1,0);		// Set Cursor to line 1, position 0 (or row 1 and col 0)

	LCD_WriteString("Workbench");

	delay_ms(2000);

	//******************* Scroll Display Right than Left ***************

	for(i=0;i<7;i++)
	{
		LCD_Display_Scroll(RIGHT);
		delay_ms(400);

	}
	for(i=0;i<7;i++)
	{
		LCD_Display_Scroll(LEFT);
		delay_ms(400);

	}
	//*********************************************************************

	delay_ms(4000);

	LCD_Clear();
	LCD_SetCursor(0,0);
	LCD_WriteString("Counting..");


    /* Loop forever */
	while(1)
	{
		for(i=0; i<10000; i++)
		{
			LCD_SetCursor(1,0);
			GPIO_TogglePin(GPIOC, GPIO_PIN_NO_13);
			LCD_WriteInteger(i);
			delay_ms(300);
		}
		LCD_Clear();	// clear the LCD

	}
}

