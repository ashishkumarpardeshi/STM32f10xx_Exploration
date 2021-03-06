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

#include "STM32f103xx.h"
#include "STM32f103xx_usart_driver.h"
#include "STM32f103xx_gpio_driver.h"
#include "STM32f103xx_rcc_driver.h"

#include <stdint.h>
#include <string.h>

//Function declarations
void delay_ms(uint32_t);
void USART2_GPIOInit();
void USART2_Init();

// Global Variables
USART_Handle_t usart2;

char msg[1024] = "Counter Value...\n\r";



int main(void)
{
	uint32_t i = 0;

	USART2_GPIOInit();

	USART2_Init();

	USART_PeripheralControl(USART2, ENABLE);

	USART_SendData(&usart2, (uint8_t*) msg, strlen(msg));

    /* Loop forever */
	while(1)
	{

		USART_SendData(&usart2, (uint8_t*) i+48, strlen((uint8_t*)i+48));
		delay_ms(1000);

		i++;

	}
}


void USART2_GPIOInit()
{
	GPIO_Handle_t usart2_gpios;			// Create a GPIO_Handle_t variable usart_gpios

	usart2_gpios.pGPIOx = GPIOA;  // Configuring for USART2
	usart2_gpios.GPIO_PinConfig.GPIO_PinMode = GPIO_ALTFN_OP_PP;			// Alternate function Push Pull Mode
	usart2_gpios.GPIO_PinConfig.GPIO_PinOutInType = GPIO_MODE_OUTPUT_50MHZ ; // GPIO Speed 50 Mhz

	GPIO_PeriClkControl(GPIOA, ENABLE);		// Enable the Clock of GPIOA


	usart2_gpios.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_2;				// USART2 TX pin
	GPIO_Init(&usart2_gpios);				// Initialize the USART2 Tx GPIO

	usart2_gpios.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_3;				// USART2 RX pin
	GPIO_Init(&usart2_gpios);				// Initialize the USART2 Rx GPIO
}

void USART2_Init()
{

	usart2.pUSARTx = USART2;
	usart2.USART_Config.USART_BaudRate = USART_BAUD_9600;
	usart2.USART_Config.USART_NoOfStopBits = USART_STOP_BIT_1;
	usart2.USART_Config.USART_ParityControl = USART_PARITY_DISABLE;
	usart2.USART_Config.USART_WordLength = USART_WORDLEN_8BIT;
	usart2.USART_Config.USART_HWFlowControl = USART_HW_FLOW_CTRL_NONE;
	usart2.USART_Config.USART_Mode = USART_MODE_TXRX;

	USART_Init(&usart2);
}

void delay_ms(uint32_t ms)
{
	uint32_t delay = ms * 668;
	for (int i = 0; i < delay; i++)  // 325000 = 500 msec rough estimation
		__asm__("nop");
}
