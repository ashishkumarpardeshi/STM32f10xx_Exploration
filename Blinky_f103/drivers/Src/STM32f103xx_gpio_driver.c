/*
 * STM32f103xx_gpio_driver.c
 *
 *  Created on: Mar 1, 2021
 *      Author: ashish
 */


#include "STM32f103xx.h"
#include "STM32f103xx_gpio_driver.h"

/**************************************************************************************
 *                             APIs Function Definition
 *************************************************************************************/
/*
 * Init and Deinit GPIO
 */

void GPIO_Init(GPIO_Handle_t *pGPIOHandle)
{
	uint32_t temp = 0x0;
	uint32_t crl = 0x0, crh = 0x0;
	uint16_t offset;
	uint8_t pinNo;

	pinNo = pGPIOHandle -> GPIO_PinConfig.GPIO_PinNumber;

	crl = pGPIOHandle -> pGPIOx -> CRL;
	crh = pGPIOHandle -> pGPIOx -> CRH;

	if(pinNo < 8)
	{
		offset = pinNo * 4;
		temp = crl;
	}
	else
	{
		offset = (pinNo - 8) * 4;
		temp = crh;
	}

	temp &= ~(0xf << offset);
	temp |= (pGPIOHandle -> GPIO_PinConfig.GPIO_PinMode << offset)| (pGPIOHandle -> GPIO_PinConfig.GPIO_PinOutInType << (offset + 2));

	if(pinNo < 8)
	{
		crl = temp;
		//pGPIOHandle -> pGPIOx -> CRL =  temp;
	}
	else
	{
		crh = temp;
		//pGPIOHandle -> pGPIOx -> CRH = temp;

	}

	pGPIOHandle -> pGPIOx -> CRL =  crl;
	pGPIOHandle -> pGPIOx -> CRH = crh;

}

void GPIO_DeInit(GPIO_RegDef_t *pGPIOx)				// Reset the GPIO setting as default
{
	if(pGPIOx == GPIOA)
	{
		GPIOA_REG_RESET();
	}
	else if(pGPIOx == GPIOB)
	{
			GPIOB_REG_RESET();
	}
	else if(pGPIOx == GPIOC)
	{
			GPIOC_REG_RESET();
	}

	else if(pGPIOx == GPIOD)
	{
			GPIOD_REG_RESET();
	}
	else if(pGPIOx == GPIOE)
	{
			GPIOE_REG_RESET();
	}
}

/*
 * Peripheral Clock Setup
 */

void GPIO_PeriClkControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		if(pGPIOx == GPIOA)
		{
			GPIOA_PCLK_EN();
		}
		else if(pGPIOx == GPIOB)
		{
			GPIOB_PCLK_EN();
		}
		else if(pGPIOx == GPIOC)
		{
			GPIOC_PCLK_EN();
		}
		else if(pGPIOx == GPIOD)
		{
			GPIOD_PCLK_EN();
		}
		else if(pGPIOx == GPIOE)
		{
			GPIOE_PCLK_EN();
		}
	}
	else
	{
		if(pGPIOx == GPIOA)
		{
			GPIOA_PCLK_DI();
		}
		else if(pGPIOx == GPIOB)
		{
			GPIOB_PCLK_DI();
		}
		else if(pGPIOx == GPIOC)
		{
			GPIOC_PCLK_DI();
		}
		else if(pGPIOx == GPIOD)
		{
			GPIOD_PCLK_DI();
		}
		else if(pGPIOx == GPIOE)
		{
			GPIOE_PCLK_DI();
		}
	}

}


/*
 * Data read and Write
 */


// Read single bit of PORTx
uint8_t GPIO_ReadPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
	uint16_t value;
	value  = ((uint16_t)pGPIOx -> IDR >> PinNumber) & 0x00000001;
	return value;
}

//Read complete PORTx
uint16_t GPIO_ReadPort(GPIO_RegDef_t *pGPIOx)
{
	uint16_t value;
	value = ((uint16_t)pGPIOx -> IDR);
	return value;
}

//Write to single bit of PORTx
void GPIO_WritePin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t value)
{
	if(value == GPIO_PIN_SET)
	{
		pGPIOx -> ODR |= 1 << PinNumber;
	}
	else
	{
		pGPIOx -> ODR &= ~ (1 << PinNumber);
	}
}

//Write to complete PORTx
void GPIO_WritePort(GPIO_RegDef_t *pGPIOx, uint16_t value)
{
	pGPIOx -> ODR = value;
}

void GPIO_TogglePin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
	pGPIOx -> ODR ^= (1 << PinNumber);
}

//Atomic Set Reset the Pin
void GPIO_Atomic_SetResetPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t value) //Atomic Set/Clear the Pin 0:16 as per Value
{
	if(value == GPIO_PIN_SET)
	{
		pGPIOx -> BSRR = 1 << PinNumber;
	}
	else
	{
		pGPIOx -> BSRR = 1 << (PinNumber + 16);
	}
}


void GPIO_Atomic_ResetPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber) // Atomic Clear the Pin 0:16
{
	pGPIOx -> BRR = 1 << PinNumber;
}
