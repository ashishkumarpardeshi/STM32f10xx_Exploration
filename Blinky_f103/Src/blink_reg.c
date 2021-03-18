/*
 * blink_reg.c
 *
 *  Created on: 07-Mar-2021
 *      Author: ashish
 */


#include "STM32f103xx_gpio_driver.h"
#include "STM32f103xx.h"

/*#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif*/


void delay_ms(uint32_t);

int main(void)
{

	/*GPIO_PeriClkControl(GPIOB, ENABLE);			// This piece of code is not working, For GPIOB it is not updating the value in CRH
	 	 	 	 	 	 	 	 	 	 	 	 	// for GPIOA WD interrupt is occurred which forced the execution in infinite loop.

	GPIOB->CRH &= ~(0XF << 12);
	GPIOB->CRH |= (0X2 << 12);



	while(1)		// infinite loop
	{
		GPIOB->ODR |= (1 << 11);			// setting bit PB11
		delay_ms(100);						// waste approx 100 ms
		GPIOB->ODR &= ~(1 << 11);			// clear bit PB11
		delay_ms(100);
	}*/

	GPIO_PeriClkControl(GPIOB, ENABLE);
	GPIOB->CRH = 0x44442444;



	GPIO_PeriClkControl(GPIOC, ENABLE);			// for GPIOC this is working great. So now the question is why it is not working for GPIOA and GPIOB

	GPIOC->CRH &= ~(0XF << 20);
	GPIOC->CRH |= (0X02 << 20);



	while(1)		// infinite loop
	{
		GPIOC->ODR |= (1 << 13);			// setting bit PB13
		GPIOB->ODR |= (1 << 11);
		delay_ms(1000);						// waste approx 100 ms
		GPIOC->ODR &= ~(1 << 13);			// clear bit PB13
		GPIOB->ODR &= ~(1 << 11);
		delay_ms(100);
	}



	return 0;

}


void delay_ms(uint32_t ms)
{
	uint32_t delay = ms * 625;
	for (int i = 0; i < delay; i++)  // 325000 = 500 msec rough estimation
		__asm__("nop");
}
