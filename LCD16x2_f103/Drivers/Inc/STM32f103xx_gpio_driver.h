
/*
 * STM32f103xx_gpio_driver.h
 *
 *  Created on: Mar 1, 2021
 *      Author: ashish
 */

#ifndef STM32F103XX_GPIO_DRIVER_H_
#define STM32F103XX_GPIO_DRIVER_H_

#include "STM32f103xx.h"

/*
 * Configurable structure for GPIO Pin
 */

typedef struct
{
	uint8_t GPIO_PinNumber;
	uint8_t GPIO_PinMode;
	uint8_t GPIO_PinOutInType;

}GPIO_PinConfig_t;

/*
 * Handle structure for GPIO Pin
 */

typedef struct
{
	// pointer to hold the base address of GPIO Peripheral
	GPIO_RegDef_t *pGPIOx;	// This hold the base address of GPIO port to which the pin belongs.
	GPIO_PinConfig_t GPIO_PinConfig;

}GPIO_Handle_t;



/*
 * GPIO Pin Numbers
 */

#define GPIO_PIN_NO_0		0
#define GPIO_PIN_NO_1		1
#define GPIO_PIN_NO_2		2
#define GPIO_PIN_NO_3		3
#define GPIO_PIN_NO_4		4
#define GPIO_PIN_NO_5		5
#define GPIO_PIN_NO_6		6
#define GPIO_PIN_NO_7		7
#define GPIO_PIN_NO_8		8
#define GPIO_PIN_NO_9		9
#define GPIO_PIN_NO_10		10
#define GPIO_PIN_NO_11		11
#define GPIO_PIN_NO_12		12
#define GPIO_PIN_NO_13		13
#define GPIO_PIN_NO_14		14
#define GPIO_PIN_NO_15		15



/************** CRL & CRH Register **************************************/
/*
 * GPIO pin possible Input type
 * GPIO_MODE = 0
 */

//#define GPIO_INPUT				0

#define GPIO_IP_ANALOG			0
#define GPIO_IP_FLOATING		1					// Reset State
#define GPIO_IP_PUPD			2


/*
 * GPIO Pin possible output type
 * GPIO_MODE > 0
 */


#define GPIO_OP_PP			0
#define GPIO_OP_OD			1

#define GPIO_ALTFN_OP_PP	2
#define GPIO_ALTFN_OP_OD	3


/*
 * GPIO pin possiible  mode
 */

#define GPIO_MODE_INPUT 			0
#define GPIO_MODE_OUTPUT_10MHZ		1
#define GPIO_MODE_OUTPUT_2MHZ		2
#define GPIO_MODE_OUTPUT_50MHZ		3





/******************************************************************************************************
 * 							APIs Supported by this driver
 * 			For more details about APIs check the function definitions in STM32f103xx.gpio.driver.c
 *
 *****************************************************************************************************/

/*
 * Init and Deint GPIOs
 */


void GPIO_Init(GPIO_Handle_t *pGPIOHandle);
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx);

/*
 * Data read and Write
 */

uint8_t GPIO_ReadPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);
uint16_t GPIO_ReadPort(GPIO_RegDef_t *pGPIOx);

void GPIO_WritePin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t value);
void GPIO_WritePort(GPIO_RegDef_t *pGPIOx, uint16_t value);

void GPIO_TogglePin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);

/*
 * BSRR and BRR Set Reset
 */

void GPIO_Atomic_SetResetPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t value);	//BSRR
void GPIO_Atomic_ResetPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);					//BRR


/*
 * Peripheral Clock Setup
 */

void GPIO_PeriClkControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi);


#endif /* INC_STM32F103XX_GPIO_DRIVER_H_ */





//#endif /* DRIVERS_INC_STM32F103XX_GPIO_DRIVER_H_ */
