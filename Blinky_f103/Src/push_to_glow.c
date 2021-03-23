/*
 * File push_to_glow.c
 *
 * Created on: 20-Mar-2021
 *
 * Author: Ashish Pardeshi
 *
 * IDE: STMCubeIDE 1.6.0 (Empty Project)
 *
 * Compiler: ARM GCC
 *
 * Platform: Ubuntu 20.04
 *
 * Code Description: This code will continuously scan for switch press and when found will toggle the LED.
 *
 *
 *_____________________ Interfacing _________________________
 *
 * S.no		Device			MCU_Pin			Interface
 * ------------------------------------------------------
 *  1		Onboard_LED 	GPIOC_13		Digtal_Output
 *  2		Push_Button		GPIOB_8			Digital_input
 *
 * ___________________________________________________________
 */


// Include all the required header files
#include "STM32f103xx.h"				// Header file containing addresses of memories, Buses, peripherals etc
#include "STM32f103xx_gpio_driver.h"	// GPIO Driver header file contains Driver functions, Structures, macros etc

//Function declaration of delay_ms
void delay_ms(uint32_t);



// Main Function starts here
int main (void)
{
	// Turn on Peripheral Clock for GPIOB and GPIOC
	GPIO_PeriClkControl(GPIOB, ENABLE);						// Enable Clock for GPIOB
	GPIO_PeriClkControl(GPIOC, ENABLE);						// Enable Clock for GPIOC

	GPIO_Handle_t led, sw_1;							 // creating two variables for structure GPIO_Handle_t

	led.pGPIOx = GPIOC;										 // Onboard LED (sink mode) is connected to GPIOC
	led.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;		 // Pin no 13
	led.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUTPUT_2MHZ; // Configured as output pin with speed of 2Mhz for LED
	led.GPIO_PinConfig.GPIO_PinOutInType = GPIO_OP_PP;		 // and output type as Push Pull

	GPIO_Init(&led);		// Initialize the PC13 as OUTPUT (as per above config)



	sw_1.pGPIOx = GPIOB;									// Switch_1 is connected to GPIOB
	sw_1.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_8;	    // Pin no 8
	sw_1.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_INPUT;		// configured as input for Switch
	sw_1.GPIO_PinConfig.GPIO_PinOutInType = GPIO_IP_PUPD;	// and Input type as Pull up and Pull Down

	GPIO_Init(&sw_1);		// Initialize the PB8 as INPUT (as per above config)

	GPIO_WritePin(GPIOB, GPIO_PIN_NO_8, SET);	// Activate the Internal Pull-up by setting the PxODR corresponding bit


	// Infinite loop starts here
	while(1)
	{
		uint8_t sw_State;									// Create a variable for switch status of size 1 byte
		sw_State = ((uint8_t)GPIO_ReadPin(GPIOB, GPIO_PIN_NO_8));		// Read GPIOB_8 and store result in sw_State

		if(!sw_State)										// if sw_state is non zero (switch pressed)
		{
			delay_ms(30);									// wait for debounce time

			do
			{
				sw_State = ((uint8_t)GPIO_ReadPin(GPIOB, GPIO_PIN_NO_8));	// Read the switch pin again if switch is still pressed
			}while(!sw_State);												// if yes then

			GPIO_TogglePin(GPIOC, GPIO_PIN_NO_13); 			// toggle led connected on PC13
		}
	}
	return 0;

}



// Function Definition for delay_ms
void delay_ms(uint32_t ms)
{
	uint32_t delay = ms * 625;
	for (int i = 0; i < delay; i++)  // 325000 = 500 msec rough estimation
		__asm__("nop");
}
