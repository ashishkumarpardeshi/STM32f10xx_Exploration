/*
 * atomic_blinky.c
 *
 *  Created on: 22-Mar-2021
 *      Author: ashish
 */

#include "../Drivers/Inc/STM32f103xx.h"
#include "../Drivers/Inc/STM32f103xx_gpio_driver.h"



//Function declaration of delay_ms

void delay_ms(uint32_t);



// Main starts here.

int main(void)
{

	GPIO_PeriClkControl(GPIOB, ENABLE);
	GPIO_PeriClkControl(GPIOC, ENABLE);
	GPIO_PeriClkControl(GPIOA, ENABLE);

	GPIO_Handle_t redled, greenLed, blueled;

	blueled.pGPIOx = GPIOA;
	blueled.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_8;
	blueled.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUTPUT_2MHZ;
	blueled.GPIO_PinConfig.GPIO_PinOutInType = GPIO_OP_PP;

	GPIO_Init(&blueled);


	redled.pGPIOx = GPIOB; //GPIOB
	redled.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_11; //GPIO_PIN_NO_15;
	redled.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUTPUT_2MHZ;
	redled.GPIO_PinConfig.GPIO_PinOutInType = GPIO_OP_PP;

	GPIO_Init(&redled);


	greenLed.pGPIOx = GPIOC; //GPIOB
	greenLed.GPIO_PinConfig.GPIO_PinNumber = 13; //GPIO_PIN_NO_15;
	greenLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUTPUT_2MHZ;
	greenLed.GPIO_PinConfig.GPIO_PinOutInType = GPIO_OP_PP;


	GPIO_Init(&greenLed);



	while(1)
	{
		GPIO_Atomic_SetResetPin(GPIOA, GPIO_PIN_NO_8, GPIO_PIN_SET);
		delay_ms(200);
		GPIO_Atomic_SetResetPin(GPIOB, GPIO_PIN_NO_11, GPIO_PIN_SET);
		delay_ms(200);
		GPIO_Atomic_SetResetPin(GPIOC, GPIO_PIN_NO_13, GPIO_PIN_RESET);
		delay_ms(1000);

		GPIO_Atomic_SetResetPin(GPIOC, GPIO_PIN_NO_13, GPIO_PIN_SET);
		delay_ms(200);
		GPIO_Atomic_ResetPin(GPIOB, GPIO_PIN_NO_11);//, GPIO_PIN_RESET);
		delay_ms(200);
		GPIO_Atomic_ResetPin(GPIOA, GPIO_PIN_NO_8);//, GPIO_PIN_RESET);
		delay_ms(1000);
	}
	return 0;

}


// Function Definition for delay_ms

void delay_ms(uint32_t ms)
{
	uint32_t delay = ms * 668;
	for (int i = 0; i < delay; i++)  // 325000 = 500 msec rough estimation
		__asm__("nop");
}

