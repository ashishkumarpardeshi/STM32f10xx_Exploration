/*
 * STM32f103xx.h
 *
 *  Created on: Apr 3, 2021
 *      Author: ashish
 */


#ifndef STM32F103XX_H_
#define STM32F103XX_H_

#include <stdint.h>

 #define __vo  			volatile

 /*
  * base addresses of flash and SRAM memories
  */

 #define FLASH_BASEADDR		0x08000000U		// Base address of Flash, U = unsigned value

 #define SRAM1_BASEADDR		0x20000000U		// Base address of SRAM (20KB)
 #define SRAM 				SRAM1_BASEADDR  // STM32F103xx has single SRAM

 #define SRAM_BBA_BASEADDR	0x22000000U		// Base address of SRAM Bit Band Alias Region (32 Bit)


 #define ROM				0x1FFF0000U		// System memory (30KB)


 /*
  * base addresses of  APBx and AHBx bus peripheral addresses
  */

 #define PERIPH_BASEADDR		0x40000000U		// Base Address of Peripheral
 #define PERIPH_BBA_BASEADDR    0x42000000U		// Base address of Peripheral Bit BAnd Alias REgion

 #define APB1PERIPH_BASEADDR	PERIPH_BASEADDR		// Base Address of APB1 bus
 #define APB2PERIPH_BASEADDR    (PERIPH_BASEADDR + 0x00010000U)	// BAse Address of APB2 Bus
 #define AHBPERIPH_BASEADDR		(PERIPH_BASEADDR + 0x00020000U)	// Base Address of AHB Bus

 /*
   * Base addresses of peripherals hanging on APB1 Bus
   *
   * base addresses of the APB1 Bus + offset of peripherals on that bus
   */

 #define TIM2_BASEADDR		(APB1_BASEADDR + 0x00000000U)	// Base address of TIM2
 #define TIM3_BASEADDR		(APB1_BASEADDR + 0x00000400U)	// Base address of TIM3
 #define TIM4_BASEADDR		(APB1_BASEADDR + 0x00000800U)	// Base address of TIM4
 #define RTC_BASEADDR		(APB1_BASEADDR + 0x00002800U)	// Base address of RTC
 #define WWDG_BASEADDR		(APB1_BASEADDR + 0x00002C00U)	// Base address of WWDG
 #define IWDG_BASEADDR		(APB1_BASEADDR + 0x00003000U)	// Base address of IWDG
 #define SPI2_BASEADDR		(APB1_BASEADDR + 0x00003800U)	// Base address of SPI2
 #define USART2_BASEADDR		(APB1_BASEADDR + 0x00004400U)	// Base address of USART2
 #define USART3_BASEADDR		(APB1_BASEADDR + 0x00004800U)	// Base address of USART2
 #define I2C1_BASEADDR		(APB1_BASEADDR + 0x00005400U)	// Base address of I2C1
 #define I2C2_BASEADDR		(APB1_BASEADDR + 0x00005800U)	// Base address of I2C2
 #define USB_BASEADDR		(APB1_BASEADDR + 0x00005C00U)	// Base address of USB
 #define USB_CAN_SH_BASEADDR		(APB1_BASEADDR + 0x00006000U)	// Base address of USB_CAN
 #define BXCAN_BASEADDR		(APB1_BASEADDR + 0x00006400U)	// Base address of bxCAN
 #define BKP_BASEADDR		(APB1_BASEADDR + 0x00006C00U)	// Base address of BKP
 #define PWR_BASEADDR		(APB1_BASEADDR + 0x00007000U)	// Base address of PWR



 /*
  * Base addresses of peripherals hanging on APB2 Bus
  *
  * base addresses of the APB2 Bus + offset of peripherals on that bus
  */

 #define AFIO_BASEADDR		(APB2PERIPH_BASEADDR + 0x00000000U)		// Base Address of AFIO Register
 #define EXT1_BASEADDR		(APB2PERIPH_BASEADDR + 0x00000400U)		// Base Address of EXT1 Register
 #define GPIOA_BASEADDR		(APB2PERIPH_BASEADDR + 0X00000800U)		// Base Address of PORTA
 #define GPIOB_BASEADDR		(APB2PERIPH_BASEADDR + 0X00000C00U)		// Base Address of PORTB
 #define GPIOC_BASEADDR		(APB2PERIPH_BASEADDR + 0X00001000U)		// Base Address of PORTC
 #define GPIOD_BASEADDR		(APB2PERIPH_BASEADDR + 0X00001400U)		// Base Address of PORTD
 #define GPIOE_BASEADDR		(APB2PERIPH_BASEADDR + 0X00001800U)		// Base Address of PORTE
 #define ADC1_BASEADDR		(APB2PERIPH_BASEADDR + 0x00002400U)		// Base Address of ADC1
 #define ADC2_BASEADDR		(APB2PERIPH_BASEADDR + 0x00002800U)		// Base Address of ADC2
 #define TIM1_BASEADDR		(APB2PERIPH_BASEADDR + 0x00002C00U)		// Base Address of TIM1
 #define SPI1_BASEADDR		(APB2PERIPH_BASEADDR + 0x00003000U)		// Base Address of SPI1
 #define USART1_BASEADDR	(APB2PERIPH_BASEADDR + 0x00003400U)		// Base Address of USART1


 /*
  * Base addresses of peripherals hanging on AHB Bus
  *
  * base addresses of the AHB Bus + offset of peripherals on that bus
  */

 #define DMA_BASEADDR		(AHBPERPIH_BASEADDR + 0x00000000U)	// Base address of DMA
 #define RCC_BASEADDR		(AHBPERIPH_BASEADDR + 0x00001000U)  // Base Address of RCC (RESET and CLOCK CONTROL register
 #define FlashMI_BASEADDR	(AHBPERPIH_BASEADDR + 0x00002000U)	// Base address of Flash Interface
 #define CRC_BASEADDR		(AHBPERPIH_BASEADDR + 0x00003000U)	// Base address of CRC


 /*
  * Some Genric Macros
  */

 #define ENABLE 			1
 #define DISABLE 			0

 #define SET 			ENABLE
 #define RESET 			DISABLE

 #define GPIO_PIN_SET	SET
 #define GPIO_PIN_RESET  RESET



 /************************** Peripheral register definition structures *************/

 /*
  * Note: Registers of a peripheral are specific to MCU
  *
  */

typedef struct
{
	__vo uint32_t CR;			// OFFSET ADDR 0X00
	__vo uint32_t CFGR;			// OFFSET ADDR 0X04
	__vo uint32_t CIR;			// OFFSET ADDR 0X08
	__vo uint32_t APB2RSTR;		// OFFSET ADDR 0X0C
	__vo uint32_t APB1RSTR;		// OFFSET ADDR 0X10
	__vo uint32_t AHBENR;		// OFFSET ADDR 0X14
	__vo uint32_t APB2ENR;		// OFFSET ADDR 0X18
	__vo uint32_t APB1ENR;		// OFFSET ADDR 0X1C
	__vo uint32_t BDCR;			// OFFSET ADDR 0X20
	__vo uint32_t CSR;			// OFFSET ADDR 0X24
}RCC_RegDef_t;



typedef struct
{
	__vo uint32_t CRL;
	__vo uint32_t CRH;
	__vo uint32_t IDR;
	__vo uint32_t ODR;
	__vo uint32_t BSRR;
	__vo uint32_t BRR;
    __vo uint32_t LCKR;
}GPIO_RegDef_t;

typedef struct
{
	__vo uint32_t EVCR;
	__vo uint32_t MAPR;
	__vo uint32_t EXTICR1;
	__vo uint32_t EXTICR2;
	__vo uint32_t EXTICR3;
	__vo uint32_t EXTICR4;
    __vo uint32_t RESERVE;
    __vo uint32_t MAPR2;
}AFIO_RegDef_t;


/*
 * Peripheral definition (Peripheral base addresses type casted to xxx_RegDef_t)
 */

#define GPIOA					((GPIO_RegDef_t*) GPIOA_BASEADDR)
#define GPIOB					((GPIO_RegDef_t*) GPIOB_BASEADDR)
#define GPIOC					((GPIO_RegDef_t*) GPIOC_BASEADDR)
#define GPIOD					((GPIO_RegDef_t*) GPIOD_BASEADDR)
#define GPIOE					((GPIO_RegDef_t*) GPIOE_BASEADDR)

#define RCC						((RCC_RegDef_t*) RCC_BASEADDR)

#define AFIO					((AFIO_RegDef_t*) AFIO_BASEADDR)


/************************** Clock Enable Macros Starts from Here *****************************************/

/*
 * Clock Enable Macros for GPIOx peripherals
 */

#define AFIO_PCLK_EN()		(RCC->APB2ENR |= (1 << 0))

#define GPIOA_PCLK_EN()		(RCC->APB2ENR |= (1 << 2))	// Setting 2nd bit in AHB1ENR to enable clock for PORTA
#define GPIOB_PCLK_EN()		(RCC->APB2ENR |= (1 << 3))
#define GPIOC_PCLK_EN()		(RCC->APB2ENR |= (1 << 4))
#define GPIOD_PCLK_EN()		(RCC->APB2ENR |= (1 << 5))
#define GPIOE_PCLK_EN()		(RCC->APB2ENR |= (1 << 6))

/*
 * Clock Disable Macros for GPIOx peripherals
 */

#define AFIO_PCLK_DI		(RCC->APB2ENR &= ~(1 << 0))

#define GPIOA_PCLK_DI()		(RCC->APB2ENR &= ~(1 << 2))  //Clearing 2nd bit in AHB1ENR
#define GPIOB_PCLK_DI()		(RCC->APB2ENR &= ~(1 << 3))  //Clearing 3rd bit in AHB1ENR
#define GPIOC_PCLK_DI()		(RCC->APB2ENR &= ~(1 << 4))  //Clearing 4th bit in AHB1ENR
#define GPIOD_PCLK_DI()		(RCC->APB2ENR &= ~(1 << 5))  //Clearing 5th bit in AHB1ENR
#define GPIOE_PCLK_DI()		(RCC->APB2ENR &= ~(1 << 6))  //Clearing 6th bit in AHB1ENR


/*
 * Clock Enable Macros for I2Cx peripherals
 */

#define I2C1_PCLK_EN()		(RCC->APB1ENR |= (1<<21))
#define I2C2_PCLK_EN()		(RCC->APB1ENR |= (1<<22))

/*
 * Clock disable Macros for I2Cx peripherals
 */

#define I2C1_PCLK_DI()		(RCC->APB1ENR &= ~(1<<21))
#define I2C2_PCLK_DI()		(RCC->APB1ENR &= ~(1<<22))

/*
 * Clock Enable Macros for SPIx peripherals
 */

#define SPI1_PCLK_EN()		(RCC->APB2ENR |= (1<<12))
#define SPI2_PCLK_EN()		(RCC->APB1ENR |= (1<<14))
#define SPI3_PCLK_EN()		(RCC->APB1ENR |= (1<<15))

/*
 * Clock Disable Macros for SPIx peripherals
 */

#define SPI1_PCLK_DI()		(RCC->APB2ENR &= ~(1<<12))
#define SPI2_PCLK_DI()		(RCC->APB1ENR &= ~(1<<14))
#define SPI3_PCLK_DI()		(RCC->APB1ENR &= ~(1<<15))


/*
 * Clock Enable Macros for USARTx peripherals
 */

#define USART1_PCLK_EN()	(RCC->APB2ENR |= (1<<14))
#define USART2_PCLK_EN()	(RCC->APB1ENR |= (1<<17))
#define USART3_PCLK_EN()	(RCC->APB1ENR |= (1<<18))
#define USART4_PCLK_EN()	(RCC->APB1ENR |= (1<<19))

/*
 * Clock Disable Macros for USARTx peripherals
 */

#define USART1_PCLK_DI()	(RCC->APB2ENR &= ~(1<<14))
#define USART2_PCLK_DI()	(RCC->APB1ENR &= ~(1<<17))
#define USART3_PCLK_DI()	(RCC->APB1ENR &= ~(1<<18))
#define USART4_PCLK_DI()	(RCC->APB1ENR &= ~(1<<19))

/*
 * Macros to reset GPIOx peripherals
 */

#define GPIOA_REG_RESET()		do{ (RCC -> APB2RSTR |= (1<<2)); (RCC -> APB2RSTR &= ~(1<<2)); }while(0)
#define GPIOB_REG_RESET()		do{ (RCC -> APB2RSTR |= (1<<3)); (RCC -> APB2RSTR &= ~(1<<3)); }while(0)
#define GPIOC_REG_RESET()		do{ (RCC -> APB2RSTR |= (1<<4)); (RCC -> APB2RSTR &= ~(1<<4)); }while(0)
#define GPIOD_REG_RESET()		do{ (RCC -> APB2RSTR |= (1<<5)); (RCC -> APB2RSTR &= ~(1<<5)); }while(0)
#define GPIOE_REG_RESET()		do{ (RCC -> APB2RSTR |= (1<<6)); (RCC -> APB2RSTR &= ~(1<<6)); }while(0)


//#endif /* INC_STM32F103XX_H_ */



#endif /* DRIVERS_INC_STM32F103XX_H_ */
