
/******************************************************************************
 * @file    hsi_measurement.c
 * @author  Ashish Kumar Pardeshi
 * @brief   This code will Output the HSI clock at MCO pin (PA8).
 ******************************************************************************
*/


#include<stdint.h>

// Making RCC_CHGR Register Address

#define  RCC_BASE_ADDR     0x40021000U    // Base address of RCC Registers

#define  RCC_CFGR_OFFSET   0x00000004U    // Offset address of RCC_CFGR

#define   RCC_CFGR_ADDR   0x40021004U  //RCC_BASE_ADDR + RCC_CFGR_OFFSET

// Making RCC_APB2ENR Register Address

#define RCC_APB2ENR_OFFSET  0x00000018U // Offset address of RCC_APB2ENR Register

#define RCC_APB2ENR_ADDR  (RCC_BASE_ADDR + RCC_APB2ENR_OFFSET)

// Making GPIOA_CRH Register Address

#define GPIOA_BASE_ADDR 0x40010800U // Base address of GPIOA

#define GPIOA_CRH_OFFSET  0X00000004U //Offset address of GPIO_CRH

#define GPIOA_CRH_ADDR   (GPIOA_BASE_ADDR + GPIOA_CRH_OFFSET) //Address of GPIOA_CRH

int main(void)

{

    // 1) Selecting HSI Clock Signal to be Output at MCO pin

    uint32_t *pRccCfgrReg =  (uint32_t*) RCC_CFGR_ADDR; //Dereferencing RCC_CFGR Address

    *pRccCfgrReg &= ~(0x7 << 24);     // Clear Bits 26 to 24

    *pRccCfgrReg |= (0x5 << 24);       // 0101 << 24

    // 2) Enable the peripheral clock for GPIOA peripheral

    uint32_t *pRccApb2enrReg = (uint32_t*)RCC_APB2ENR_ADDR;

    *pRccApb2enrReg |= ( 1 << 2); //Enable GPIOA peripheral clock

    // 3) Configure the mode of GPIOA pin 8 as alternate function mode

    uint32_t *pGpioACrhReg = (uint32_t*)GPIOA_CRH_ADDR; // Dereference the GPIOA_CRH address

    *pGpioACrhReg &= ~(0xF << 0); // clear bit 0 to 3

    *pGpioACrhReg |= 0xE; // write 1101 to Bits[3:0] of GPIOA_CRH

    while(1)    // Infinite Loop
    {

    }

}


