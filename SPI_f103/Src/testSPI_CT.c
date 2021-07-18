/*
 * testSPI_CT.c
 *
 *  Created on: 12-Jun-2021
 *      Author: ashish
 */


#include "STM32f103xx.h"                  // Device header

void GPIOConfig (void)
{
	RCC->APB2ENR |=  (1<<2);  // Enable GPIOA clock

	GPIOA->CRL = 0;
	GPIOA->CRL |= (11U<<20);   // PA5 (SCK) AF output Push Pull
	GPIOA->CRL |= (11U<<28);   // PA7 (MOSI) AF output Push Pull
	GPIOA->CRL |= (1<<26);    // PA6 (MISO) Input mode (floating)
	GPIOA->CRL |= (3<<16);    // PA4 used for CS, GPIO Output

}


void SPIConfig (void)
{

		RCC->APB2ENR |= (1<<12);  // Enable SPI1 Clock

		SPI1->CR1 |= 3<<3;   // BR[2:0] = 011 = fPCLK/16, PCLK2 = 72MHz, SPI clk = 4.5MHz

		SPI1->CR1 |= (1<<0)|(1<<1);  // CPOL=1, CPHA=1

		SPI1->CR1 &= ~(1<<10);  // RXONLY = 0, full-duplex

		SPI1->CR1 &= ~(1<<7);   // LSBFIRST = 0, MSB first

		SPI1->CR1 |= (1<<2);  // MSTR=1, Master mode

		SPI1->CR1 &= ~(1<<11);  // DFF=0, 8 bit data

		// software slave management must be selecetd, and then we can control the slave using any output pin

		SPI1->CR1 |= (1<<9)| (1<<8);  // SSM = 1, SSI = 1

		SPI1->CR2 = 0;
}

void SPI_Enable (void)
{
	SPI1->CR1 |= (1<<6);   // SPE=1, Peripheral enabled
}

void SPI_Disable (void)
{
	SPI1->CR1 &= ~(1<<6);   // SPE=0, Peripheral Disabled
}

void SPI_Transmit (uint8_t *data, int size)
{
	/************** STEPS TO FOLLOW *****************
	1. Wait for the TXE bit to set in the Status Register
	2. Write the data to the Data Register
	3. After the data has been transmitted, wait for the BSY bit to reset in Status Register
	4. Clear the Overrun flag by reading DR and SR
	************************************************/

	uint8_t temp1;

	if (!(SPI1->CR1&(1<<6)))
	{
		SPI_Enable();
	}
	int i=0;
	while (i<size)
	{
	   while (!((SPI1->SR)&(1<<1))) {};  // wait for TXE bit to set -> This will indicate that the buffer is empty
	   SPI1->DR = data[i];  // load the data into the Data Register
	   i++;
	}

/*During discontinuous communications, there is a 2 APB clock period delay between the
write operation to the SPI_DR register and BSY bit setting. As a consequence it is
mandatory to wait first until TXE is set and then until BSY is cleared after writing the last
data.
*/
	while (!((SPI1->SR)&(1<<1))) {};  // wait for TXE bit to set -> This will indicate that the buffer is empty
	while (((SPI1->SR)&(1<<7))) {};  // wait for BSY bit to Reset -> This will indicate that SPI is not busy in communication

		//clear OVR Flag by reading the data, and status register
	temp1= SPI1->DR;
	temp1 = SPI1->SR;
}

void SPI_Receive (uint8_t *data, int size)
{

	/************** STEPS TO FOLLOW *****************
	1. Wait for the BSY bit to reset in Status Register
	2. Send some Dummy data before reading the DATA
	3. Wait for the RXNE bit to Set in the status Register
	4. Read data from Data Register
	************************************************/
	while (size)
	{
		SPI1->DR = 0;  // send dummy data
		while (!((SPI1->SR) &(1<<0))){};  // Wait for RXNE to set -> This will indicate that the Rx buffer is not empty
	  *data++ = (SPI1->DR);
		size--;
	}
}

void CS_Enable (void)
{
	GPIOA->BSRR |= (1<<4)<<16U;
}

void CS_Disable (void)
{
	GPIOA->BSRR |= (1<<4);
}

float xg, yg, zg;
int16_t x,y,z;
uint8_t Rxdata[20];

void adxl_write (uint8_t address, uint8_t value)
{
	uint8_t data[2];
	data[0] = address|0x40;  // multibyte write enabled
	data[1] = value;
	CS_Enable();   // pull the cs pin low to enable the slave
	SPI_Transmit (data, 2);  // transmit the address and data
	CS_Disable(); // pull the cs pin high to disable the slave
}

void adxl_read (uint8_t address)
{
	address |= 0x80;  // read operation
	address |= 0x40;  // multibyte read
	CS_Enable();   // pull the cs pin low to enable the slave
	SPI_Transmit (&address, 1);  // send the address from where you want to read data
	SPI_Receive (Rxdata, 6);  // read 6 BYTES of data
	CS_Disable();  // pull the cs pin high to disable the slave
}

void adxl_init (void)
{
	adxl_write (0x31, 0x01);  // data_format range= +- 4g
	adxl_write (0x2d, 0x00);  // reset all bits
	adxl_write (0x2d, 0x08);  // power_cntl measure and wake up 8hz
}

uint8_t data[] = {0x35, 0x96};
int main ()
{
	//SystemInit ();
	GPIOConfig ();
	SPIConfig ();

	adxl_init ();

		adxl_read (0x32);
		x = ((Rxdata[1]<<8)|Rxdata[0]);
		y = ((Rxdata[3]<<8)|Rxdata[2]);
		z = ((Rxdata[5]<<8)|Rxdata[4]);

	  xg = x*.0078;
    yg = y*.0078;
   	zg = z*.0078;
	while (1)
	{

	}
}
