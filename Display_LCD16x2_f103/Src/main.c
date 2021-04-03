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

#include <stdint.h>

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

int main(void)
{
	LCD_PinConfig_t		lcd;		// define LCD Pin Configuration structure  Variable

	lcd.LCD_Port.pGPIOx = GPIOA;
	lcd.RS_Pin = GPIO_PIN_NO_13;
	lcd.En_Pin = GPIO_PIN_NO_12;
	lcd.D4_Pin = GPIO_PIN_NO_11;
	lcd.D5_Pin = GPIO_PIN_NO_10;
	lcd.D6_Pin = GPIO_PIN_NO_9;
	lcd.D7_Pin = GPIO_PIN_NO_8;




    /* Loop forever */
	while(1)
	{

	}
}