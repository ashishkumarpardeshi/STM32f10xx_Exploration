/*
 * STM32f103xx_rcc_driver.c
 *
 *  Created on: 04-May-2021
 *      Author: ashish
 */

#include "STM32f103xx.h"	// Target MCU header file
#include "STM32f103xx_rcc_driver.h"
#include <stdint.h>

uint16_t AHB_PreScaler[8] = {2,4,8,16,64,128,256,512};
uint8_t APB_PreScaler[4] = { 2, 4 , 8, 16};

/*********************************************************************
 * @fn      		  - RCC_GetPCLK1Value
 *
 * @brief             - This API will calculate APB1 Clock
 *
 * @param[in]         - none
 *
 * @return            - pclk1 (return APB1 Clock)
 *
 * @Note              -
 **********************************************************************/


uint32_t RCC_GetPCLK1Value(void)
{
	uint32_t pclk1,SystemClk;

	uint8_t clksrc,temp,ahbp,apb1p;

	// First check out the clock source used as system clock by reading SWS bits in RCC_CFGR
	clksrc = ((RCC->CFGR >> 2) & 0x3);

	if(clksrc == 0 )				//SWS = 00
	{
		SystemClk = 8000000;		// HSI is used as System Clock
	}
	else if(clksrc == 1)			//SWS = 01
	{
		SystemClk = 16000000;		// HSE is used as System Clock
	}
	else if (clksrc == 2)			//SWS = 2
	{
		SystemClk = RCC_GetPLLOutputClock();	// PLL is used as System Clock
	}

	// Check out the AHB Prescaler value in RCC_CFGR Register
	temp = ((RCC->CFGR >> 4 ) & 0xF);

	if(temp < 8)	// HPRE = 0xxx
	{
		ahbp = 1;	// AHB prescaler is selected as 1;
	}
	else
	{
		ahbp = AHB_PreScaler[temp-8];	//AHB prescalar selected as per AHB_Prescaler array given by this index
	}



	//Check out the APB1 prescaler value
	temp = ((RCC->CFGR >> 8 ) & 0x7);		// reading bits of PPRE1

	if(temp < 4)							// PPRE1 = 0xxx
	{
		apb1p = 1;							//APB1 prescaler is selected as 1
	}else
	{
		apb1p = APB_PreScaler[temp-4];	//APB1 prescalar selected as per APB_Prescaler array given by this index.
	}

	pclk1 =  (SystemClk / ahbp) /apb1p;

	return pclk1;
}



/*********************************************************************
 * @fn      		  - RCC_GetPCLK2Value
 *
 * @brief             - This API will calculate APB2 Clock
 *
 * @param[in]         - none
 *
 * @return            - pclk2 (return APB2 Clock)
 *
 * @Note              -
 **********************************************************************/
uint32_t RCC_GetPCLK2Value(void)
{
	uint32_t SystemClk = 0,temp,pclk2;

	uint8_t ahbp,apb2p;

	// First check out the clock source used as system clock by reading SWS bits in RCC_CFGR
	uint32_t clksrc = ((RCC->CFGR >> 2) & 0x3);

	if(clksrc == 0 )				//SWS = 00
	{
		SystemClk = 8000000;		// HSI is used as System Clock
	}
	else if(clksrc == 1)			//SWS = 01
	{
		SystemClk = 16000000;		// HSE is used as System Clock
	}
	else if (clksrc == 2)			//SWS = 2
	{
		SystemClk = RCC_GetPLLOutputClock();	// PLL is used as System Clock
	}

	// Check out the AHB Prescaler value in RCC_CFGR Register
	temp = ((RCC->CFGR >> 4 ) & 0xF);

	if(temp < 8)	// HPRE = 0XXX
	{
		ahbp = 1;	// AHB prescaler is selected as 1;
	}
	else
	{
		ahbp = AHB_PreScaler[temp-8];	//AHB prescalar selected as per AHB_Prescaler array given by this index.
	}

	// Check out the APB2 Prescaler value in RCC_CFGR Register
	temp = (RCC->CFGR >> 11 ) & 0x7;		// reading bits of PPRE1
	if(temp < 0x04)
	{
		apb2p = 1;						//APB2 prescaler is selected as 1
	}else
	{
		apb2p = APB_PreScaler[temp-4];	//APB2 prescalar selected as per APB_Prescaler array given by this index.
	}

	pclk2 = (SystemClk / ahbp )/ apb2p;

	return pclk2;
}

uint32_t RCC_GetPLLOutputClock()
{
	return 0;

}
