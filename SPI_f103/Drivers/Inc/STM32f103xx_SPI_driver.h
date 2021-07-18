/*
 * STM32f103xx_SPI_driver.h
 *
 *  Created on: 09-Jun-2021
 *      Author: ashish
 */

#ifndef STM32F103XX_SPI_DRIVER_H_
#define STM32F103XX_SPI_DRIVER_H_

#include "STM32f103xx.h"					// including target header file



/*
 * Configurable structure for SPI
 */

typedef struct
{
	uint8_t SPI_Mode;
	uint8_t SPI_BusConfig;
	uint8_t SPI_CLKSpeed;
	uint8_t SPI_DataFormat;
	uint8_t SPI_CPHASE;
	uint8_t SPI_CPOL;
	uint8_t SPI_SlaveMgmt;
}SPI_Config_t;

/*
 * Handle structure for SPI
 */

typedef struct
{
	// pointer to hold the base address of SPI Peripheral
	SPI_RegDef_t *pSPIx;	// This hold the base address of SPIx
	SPI_Config_t SPI_Config;

}SPI_Handle_t;



/******************************************************************************************************
 * 		Macros for SPI (User Configuration Setting Macros, SPI Flag Masking Macros)
 *****************************************************************************************************/

// SPI Mode Select macros
#define SPI_MODE_MASTER				1
#define SPI_MODE_SLAVE				0

// Bus Config Macros
#define SPI_BUS_CONFIG_FD			1
#define SPI_BUS_CONFIG_HD			2
#define SPI_BUS_CONFIG_SIM_RXONLY 	3

// SPI CLock Baudrate Selction Macros
#define SPI_CLKSPEED_FPCLK_2			0
#define SPI_CLKSPEED_FPCLK_4			1
#define SPI_CLKSPEED_FPCLK_8			2
#define SPI_CLKSPEED_FPCLK_16			3
#define SPI_CLKSPEED_FPCLK_32			4
#define SPI_CLKSPEED_FPCLK_64			5
#define SPI_CLKSPEED_FPCLK_128			6
#define SPI_CLkSPEED_FPCLK_256			7

// Data Frame Format Macros
#define SPI_DFF_8BIT				0
#define SPI_DFF_16BIT				1

// CPOL and CPHASE Macros
#define SPI_CPOL_0_IDLE				0
#define SPI_CPOL_1_IDLE				1

#define SPI_CPHASE_DATA_LEAD_EDGE	0
#define SPI_CPHASE_DATA_TRAIL_EDGE	1

// Slave Management Macros
#define SPI_SSM_DI					0
#define SPI_SSM_EN 					1

// SPI Enable Macros
#define SPI_EN						1
#define SPI_DI						0


// Other Macros


// SPI FLAG MASKING MACROS
#define SPI_TXE_FLAG	(1 << SPI_SR_TXE)			// TX Buffer Empty Flag
#define SPI_RXNE_FLAG	(1 << SPI_SR_RXNE)			// RX Buffer Empty Flag
#define SPI_BSY_FLAG	(1 << SPI_SR_BSY)			// SPI Communication Busy Flag





/******************************************************************************************************
 * 							APIs Supported by this driver
 * 			For more details about APIs check the function definitions in STM32f103xx_SPI_driver.c
 *
 *****************************************************************************************************/

/*
 * Init and Deint SPIx
 */

void SPI_Init(SPI_Handle_t *pSPIHandle);
void SPI_DeInit(SPI_RegDef_t *pSPIx);

/*
 * SPI Get Status Flag
 */
uint8_t SPI_GetFlagStatus(SPI_RegDef_t *pSPIx, uint32_t FlagName);

/*
 * SPI Peripheral Clock Setup
 */

void SPI_PeriClkControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi);

/*
 * SPI Peripheral Enable or Disable
 */
void SPI_PeriControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi);

/*
 * SPI SSI Configuration
 */
void SPI_SSIConfig(SPI_RegDef_t *pSPIx, uint8_t EnorDi);

/*
 *  Slave Select Output Enable/Disable
 */

void SPI_SSOEConfig(SPI_RegDef_t *pSPIx, uint8_t EnorDi);

/*
 *  SPI Data Read and Write
 */
void SPI_WriteData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t Len);
void SPI_ReadData(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer, uint32_t Len);

/*
 *  SPI IRQ Configuration and ISR Handling
 */
void SPI_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);
void SPI_PriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);
void SPI_IRQHandling(SPI_Handle_t);

/*
 *  SPI Other API
 */




#endif /* STM32F103XX_SPI_DRIVER_H_ */
