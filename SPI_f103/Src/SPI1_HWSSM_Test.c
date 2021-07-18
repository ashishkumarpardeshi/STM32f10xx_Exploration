/*
 * SPI1_test_HWSSM.c
 *
 *  Created on: 12-Jun-2021
 *      Author: ashish
 *
 *
 *  This code will simply send data over MOSI line whenever a pushbutton is pressed and released.
 *
 *  SPI1 is used with Master Mode and Hardware Slave Selection management.
 */



#include<string.h>

#include "STM32f103xx.h"					// including target header file
#include "STM32f103xx_gpio_driver.h"
#include "STM32f103xx_SPI_driver.h"


#include <stdint.h>

/************************************************************************************
 * 								Function API Declaration
 ************************************************************************************/
void SPI1_GPIOPin_Def();		// SPI2 GPIO Pin Definition Function Declaration

void SPI1_UsrConfig();		//  SPI2 User Configuration	Function Declaration

//void SPI_WriteChar(SPI_RegDef_t *pSPIx, char pTxBuffer, uint32_t Len);


// USer Defined Macros

#define SPI1_GPIOPort 	GPIOA

#define NSS_Pin 		GPIO_PIN_NO_4
#define SCK_Pin			GPIO_PIN_NO_5
#define MISO_Pin		GPIO_PIN_NO_6
#define MOSI_Pin		GPIO_PIN_NO_7


/************************************************************************************
 * 									Main Function
 ************************************************************************************/
int main(void)
{
	char user_data1[] = {"ASHISH Workbench Rocks"};

	GPIO_Handle_t pushbutton, redled;

	GPIO_PeriClkControl(GPIOB, ENABLE);

	pushbutton.pGPIOx = GPIOB;
	pushbutton.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_INPUT;
	pushbutton.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
	pushbutton.GPIO_PinConfig.GPIO_PinOutInType = GPIO_IP_PUPD;
	GPIO_WritePin(GPIOB, GPIO_PIN_NO_12, GPIO_PIN_SET);		// Activate Pull-up on PB13
	GPIO_Init(&pushbutton);


	redled.pGPIOx = GPIOB;
	redled.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUTPUT_2MHZ;
	redled.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_15;
	redled.GPIO_PinConfig.GPIO_PinOutInType = GPIO_OP_PP;

	GPIO_Init(&redled);

	/*for(int i = 0;i<10;i++)
	{
		GPIO_TogglePin(GPIOB, GPIO_PIN_NO_15);
		delay_ms(100);
	}*/


	// Initialize the GPIO pins for SPI1
	SPI1_GPIOPin_Def();					// SPI1 GPIO Pin Definition Setting Call

	// Initialize the SPI1 with user configuration settings
	SPI1_UsrConfig();					// SPI1 User Configuration Call

	// If H/W Slave Management is Selected (ie SSM = 0), so for Master Mode SSOE should be SET
	// When SSOE = SET then NSS pin will be pulled Low automatically whenever SPE =  SET (SPI is Enabled)
	// and NSS will be pulled high automatically when SPE = RESET (SPI is disabled)

	SPI_SSOEConfig(SPI1, ENABLE);			// SSOE = 1 for Master Mode, H/W Slave Select Management (ie SSM = 0)

	SPI_PeriControl(SPI1,ENABLE);
	SPI_WriteData(SPI1,(uint8_t*)user_data1,strlen(user_data1));
	SPI_PeriControl(SPI1,DISABLE);



	while(1)
	{
		/*if(GPIO_ReadPin(GPIOB, GPIO_PIN_NO_12) == RESET)
		{
			delay_ms(40);		// delay for debouncing
			while(GPIO_ReadPin(GPIOB, GPIO_PIN_NO_12) == RESET);
			//{
				GPIO_TogglePin(GPIOB, GPIO_PIN_NO_15);

				// Enable the SPI1 Peripheral
				SPI_PeriControl(SPI1,ENABLE);		// This will automatically pull NSS to LOW

				//GPIO_WritePin(SPI1_GPIOPort, NSS_Pin, RESET);	// Pull the NSS Low
				SPI_WriteData(SPI1,(uint8_t*)user_data1,strlen(user_data1));
				//GPIO_WritePin(SPI1_GPIOPort, NSS_Pin, SET);	// Pull the NSS High

				// Disable the SPI2 Peripheral
				SPI_PeriControl(SPI1,DISABLE);		// This will automatically pull NSS to HIGH
			//}
		}*/

	}
	return 0;
}

void SPI1_GPIOPin_Def()
{
	GPIO_Handle_t SPI1Pins;

	AFIO_PeriClkControl(ENABLE);

	SPI1Pins.pGPIOx = GPIOA;
	SPI1Pins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUTPUT_50MHZ;
	SPI1Pins.GPIO_PinConfig.GPIO_PinOutInType = GPIO_ALTFN_OP_PP;

	SPI1Pins.GPIO_PinConfig.GPIO_PinNumber = SCK_Pin;		// SPI1 SCK Pin
	GPIO_Init(&SPI1Pins);

	SPI1Pins.GPIO_PinConfig.GPIO_PinNumber = MOSI_Pin;		// SPI1 MOSI pin
	GPIO_Init(&SPI1Pins);

	SPI1Pins.GPIO_PinConfig.GPIO_PinNumber = MISO_Pin;		// SPI1 MISO  Pin
	SPI1Pins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_INPUT;
	SPI1Pins.GPIO_PinConfig.GPIO_PinOutInType = GPIO_IP_FLOATING;
	GPIO_Init(&SPI1Pins);


	SPI1Pins.GPIO_PinConfig.GPIO_PinNumber = NSS_Pin;		// SPI1 NSS Pin
	SPI1Pins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUTPUT_50MHZ;
	SPI1Pins.GPIO_PinConfig.GPIO_PinOutInType = GPIO_ALTFN_OP_PP;		// Configuration for SSM = 0, SSOE = 1
	GPIO_Init(&SPI1Pins);
}

void SPI1_UsrConfig()
{
	SPI_Handle_t SPI1_UsrConfig;

	SPI1_UsrConfig.pSPIx = SPI1;
	SPI1_UsrConfig.SPI_Config.SPI_Mode = SPI_MODE_MASTER;
	SPI1_UsrConfig.SPI_Config.SPI_BusConfig = SPI_BUS_CONFIG_FD;
	SPI1_UsrConfig.SPI_Config.SPI_CLKSpeed = SPI_CLKSPEED_FPCLK_128;		// SCL Clock Speed of 125 KHz
	SPI1_UsrConfig.SPI_Config.SPI_CPHASE = SPI_CPHASE_DATA_LEAD_EDGE;
	SPI1_UsrConfig.SPI_Config.SPI_CPOL = SPI_CPOL_0_IDLE;
	SPI1_UsrConfig.SPI_Config.SPI_DataFormat = SPI_DFF_8BIT;			// Data Frame Format of 8-Bit
	SPI1_UsrConfig.SPI_Config.SPI_SlaveMgmt = SPI_SSM_DI;				// H/W Slave Management Enabled for NSS Pin

	SPI_Init(&SPI1_UsrConfig);
}

/*void SPI_WriteChar(SPI_RegDef_t *pSPIx, char pTxBuffer, uint32_t Len)
{
	//GPIO_WritePin(SPI1_GPIOPort, NSS_Pin, RESET);
	//SPI_SSIConfig(SPI1,RESET);		// Reset the SSI




	while(SPI_GetFlagStatus(pSPIx, SPI_TXE_FLAG) == RESET);		// Wait until TXE is RESET

	while(SPI_GetFlagStatus(pSPIx, SPI_BSY_FLAG) == SET);		// Wait until BSY is SET

	//SPI_SSIConfig(SPI1,RESET);		// Reset the SSI

	GPIO_WritePin(SPI1_GPIOPort, NSS_Pin, RESET);
	pSPIx->DR = pTxBuffer;	//Load 8-bit Data to SPI_DR

	GPIO_WritePin(SPI1_GPIOPort, NSS_Pin, SET);
	//SPI_SSIConfig(SPI1,SET);			// Set the SSI
}*/




