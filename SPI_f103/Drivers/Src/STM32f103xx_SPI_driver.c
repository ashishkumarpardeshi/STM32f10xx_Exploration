/*
 * STM32f103xx_SPI_driver.c
 *
 *  Created on: 09-Jun-2021
 *      Author: ashish
 */

#include "STM32f103xx_SPI_driver.h"
#include "STM32f103xx_gpio_driver.h"

#include <stdint.h>

/*******************************************************************************************
 *                     APIs Function Definition for LCD Display
 *******************************************************************************************/

/**
  ******************************************************************************
  * @brief	:	SPI Peripheral Clock Control API
  *
  * @param	:	SPIx Base Address
  * @param  :	Enable or Disable
  *
  * @retval	:	None
  *
  * @Note	:
  ******************************************************************************
  */
void SPI_PeriClkControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi)
{
	// For Enabling SPIx Peripheral Clock
	if(EnorDi == ENABLE)
	{
		if(pSPIx == SPI1)
		{
			SPI1_PCLK_EN();
		}

		if(pSPIx == SPI2)
		{
			SPI2_PCLK_EN();
		}
	}


	// For Disabling SPIx Peripheral Clock
	if(EnorDi == DISABLE)
	{
		if(pSPIx == SPI1)
		{
			SPI1_PCLK_DI();
		}

		if(pSPIx == SPI2)
		{
			SPI2_PCLK_DI();
		}
	}
}

/**
  ******************************************************************************
  * @brief	:	SPI Peripheral Enable
  *
  * @param	:	SPIx Base Address
  *
  * @param	:	Enable or Disable
  *
  * @retval	:	None
  *
  * @Note	:
  ******************************************************************************
  */
void SPI_PeriControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		pSPIx->CR1 |= 1<<SPI_CR1_SPE;
	}
	else
	{
		pSPIx->CR1 &= ~(1<<SPI_CR1_SPE);
	}
}

/**
  ******************************************************************************
  * @brief	:	SPI SSI Control (Internal Slave Select)
  *
  * @param	:	SPIx Base Address
  *
  * @param	:	Enable or Disable
  *
  * @retval	:	None
  *
  * @Note	:
  ******************************************************************************
  */

void SPI_SSIConfig(SPI_RegDef_t *pSPIx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		pSPIx->CR1 |= 1<<SPI_CR1_SSI;			// SSI = 1 Tied to +VCC Internally
	}
	else
	{
		pSPIx->CR1 &= ~(1<<SPI_CR1_SSI);		// SSI = 0 Tied to Gnd Internally
	}

}

/**
  ******************************************************************************
  * @brief	:	SPI SSOE Control (Slave Select Output Enabled)
  *
  * @param	:	SPIx Base Address
  *
  * @param	:	Enable or Disable
  *
  * @retval	:	None
  *
  * @Note	:
  ******************************************************************************
  */

void SPI_SSOEConfig(SPI_RegDef_t *pSPIx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		pSPIx->CR2 |= 1 << SPI_CR2_SSOE;		// Enable the Slave Select output Enable
	}
	else
	{
		pSPIx->CR2 &= ~(1 << SPI_CR2_SSOE);		// Disable the Slave Select output Enable
	}

}

/**
  ******************************************************************************
  * @brief	:	SPI Initialization
  *
  * @param	:	SPIx Base Address
  *
  * @retval	:	None
  *
  * @Note	:
  ******************************************************************************
  */
void SPI_Init(SPI_Handle_t *pSPIHandle)
{

	SPI_PeriClkControl(pSPIHandle->pSPIx, ENABLE);		// Enable the SPI2 Clock Peripheral

	// Configuring SPI CR1 Register
	uint32_t temp = 0x00000000;

	// 1. Configuring SPI MOde
	temp |= pSPIHandle->SPI_Config.SPI_Mode << SPI_CR1_MSTR;		//For Master Mode MSTR = 1 and for Slave Mode MSTR = 0

	// 2. Configuring SPI BUS

	if(pSPIHandle->SPI_Config.SPI_BusConfig == SPI_BUS_CONFIG_FD)
	{
		// BIDIMODE = 0
		temp &= ~(1<<SPI_CR1_BIDIMODE);	// BIDIMODE is 15 bit in SPI_CR1 Register
	}
	else if(pSPIHandle->SPI_Config.SPI_BusConfig == SPI_BUS_CONFIG_FD)
	{
		// BIDIMODE = 1
		temp |= (1<<SPI_CR1_BIDIMODE);	// // BIDIMODE is 15 bit in SPI_CR1 Register
	}
	else if(pSPIHandle->SPI_Config.SPI_BusConfig == SPI_BUS_CONFIG_SIM_RXONLY)
	{
		//BIDIMODE = 0 and RXONLY = 1
		temp &= ~(1<<SPI_CR1_BIDIMODE);	// BIDIMODE is 15 bit in SPI_CR1 Register
		temp |= (1<<SPI_CR1_RXONLY);	// RXONLY is 10th bit in SPI_CR1 Register
	}

	// 3. Configuring SPI Clock Speed

	temp |= pSPIHandle->SPI_Config.SPI_CLKSpeed << SPI_CR1_BR;	// BR [5:3] (3 bit for SPI CLK selection

	// 4. Configuring SPI Data Frame Format

	temp |= pSPIHandle->SPI_Config.SPI_DataFormat << SPI_CR1_DFF;	// DFF is 11th bit in SPI_CR1

	// 5. Configuring SPI CPOL

	temp |= pSPIHandle->SPI_Config.SPI_CPOL << SPI_CR1_CPOL;		// CPOL is 1st bit in SPI_CR1

	// 6. Configuring CPHASE

	temp |= pSPIHandle->SPI_Config.SPI_CPHASE << SPI_CR1_CPHA;		// CPHA is 0th bit in SPI_CR1

	// 7. Configuring SSM

	temp |= pSPIHandle->SPI_Config.SPI_SlaveMgmt << SPI_CR1_SSM;

	//**************** Updating SPI CR1 register ************************

	pSPIHandle->pSPIx->CR1 = temp;
}


/**
  ******************************************************************************
  * @brief	:	SPI Deinitialization
  *
  * @param	:	SPIx Base Address
  *
  * @retval	:	None
  *
  * @Note	:
  ******************************************************************************
  */
void SPI_Deinit(SPI_RegDef_t *pSPIx)
{
	if(pSPIx == SPI1)
	{
		SPI1_REG_RESET();				// Reset SPI1 Registers
	}

	if(pSPIx == SPI2)
	{
		SPI2_REG_RESET();				// Reset SPI2 Registers
	}
}


uint8_t SPI_GetFlagStatus(SPI_RegDef_t *pSPIx, uint32_t FlagName)
{
	if(pSPIx->SR & FlagName)	// True for FLAG Bit = 1
	{
		return FLAG_SET;		// return FLAG is SET
	}
	return FLAG_RESET;			// return FLAG is RESET
}

/**
  ******************************************************************************
  * @brief	:	SPI Send Data
  *
  * @param	:	SPIx Base Address
  *
  * @param	:	Data to transmit (Pointer to Data)
  *
  * @param	:	Length of TX Data Buffer (Number of Bytes to Transmit)
  *
  * @retval	:	None
  *
  * @Note	:	This is blocking Call API to transmit numbers of Bytes in Data
  ******************************************************************************
  */

void SPI_WriteData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t Len)
{
	uint8_t temp1 = 0x00;

	while(Len > 0)		// Loop while Complete data gets transmitted
	{
		// 1. Wait until TX_Buffer is not Empty (ie TXE bit in SPI_SR Reg is not set)
		// *** One Method
		//while(!(pSPIx->SR & (1<<1));		// ! of (0) is true, so continue
		// Other Method to call a Get Flag status function
		while(SPI_GetFlagStatus(pSPIx, SPI_TXE_FLAG) == FLAG_RESET);	// Wait until TXE is SET


		// 2. Check DFF bit for 8-Bit Data Frame Format or 16-Bit Data Frame Format
		if(pSPIx->CR1 & (1 << SPI_CR1_DFF))	 // true for 16-Bit Data Frame Format
		{
			//16-Bit Data Frame Format
			/*
			 * (uint16_t*)pTxBuffer		// typecasting the uint8_t* pTxBuffer to Uint16_t*
			 * *((uint16_t*)pTxBuffer)	// Dereferencing
			 */
			pSPIx->DR = *((uint16_t*)pTxBuffer);			// Load 16-Bit Data to SPI_DR

			// Decrement the length by 2 for loading 2 byte of data
			Len --;
			Len --;

			// Increment the pTXBuffer for next 16-Bit Data transmission
			(uint16_t*)pTxBuffer++;
		}
		else
		{
			pSPIx->DR = *pTxBuffer;	//Load 8-bit Data to SPI_DR
			Len --;						// Decrement the length by 1 as loading one byte of data
			pTxBuffer++;				// Increment pTxBuffer for next 8-Bit Data transmission
		}
		//delay_us(2);
	}

	while(SPI_GetFlagStatus(pSPIx, SPI_TXE_FLAG) == FLAG_RESET);	// Wait for TXE to SET
	while(SPI_GetFlagStatus(pSPIx, SPI_BSY_FLAG) == FLAG_SET);	// Wait for BSY to RESET

	//clear OVR Flag by reading the data, and status register
	temp1= SPI1->DR;
	temp1 = SPI1->SR;

}

/**
  ******************************************************************************
  * @brief	:	SPI Recieve Data
  *
  * @param	:	SPIx Base Address
  *
  * @param	:	Data to transmit (Pointer to Data)
  *
  * @param	:	Length of TX Data Buffer (Number of Bytes to Transmit)
  *
  * @retval	:	None
  *
  * @Note	:	This is blocking API to transmit numbers of Bytes in Data
  ******************************************************************************
  */


void SPI_ReadData(SPI_RegDef_t *pSPIx, uint8_t *pRxVuffer, uint32_t Len)
{

}

















