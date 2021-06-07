/*
 * STM32f103xx_rcc_driver.h
 *
 *  Created on: 04-May-2021
 *      Author: ashish
 */

#ifndef INC_STM32F103XX_RCC_DRIVER_H_
#define INC_STM32F103XX_RCC_DRIVER_H_

#include "STM32f103xx.h"	// Target MCU header file

/******************************************************************************************************
 * 							APIs Supported by this driver
 * 			For more details about APIs check the function definitions in STM32f103xx.gpio.driver.c
 *
 *****************************************************************************************************/

/*
 * PClK 1 and PCLK 2 Clock
 */
uint32_t RCC_GetPCLK1Value(void);
uint32_t RCC_GetPCLK2Value(void);
uint32_t  RCC_GetPLLOutputClock();

#endif /* INC_STM32F103XX_RCC_DRIVER_H_ */
