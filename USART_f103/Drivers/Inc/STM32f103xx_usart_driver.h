/*
 * STM32f103xx_usart_driver.h
 *
 *  Created on: Apr 8, 2021
 *      Author: ashish
 */

#ifndef INC_STM32F103XX_USART_DRIVER_H_
#define INC_STM32F103XX_USART_DRIVER_H_

#include "STM32f103xx.h"		// target MCU header file

 /*
 * Configuration Structure for USARTx peripheral
 */
typedef struct
{
	uint8_t USART_Mode;
	uint32_t USART_BaudRate;
	uint8_t USART_NoOfStopBits;
	uint8_t USART_WordLength;
	uint8_t USART_ParityControl;
	uint8_t USART_HWFlowControl;

} USART_Config_t;

/*
* Handling Structure for USARTx peripheral
*/
typedef struct
{
	USART_RegDef_t *pUSARTx;    	// will pass the USARTx (x = 1 or 2 or 3) address here
	USART_Config_t USART_Config;

	uint8_t *pTxBuffer;
	uint8_t *pRxBuffer;
	uint32_t TxLen;
	uint32_t RxLen;
	uint8_t TxBusyState;
	uint8_t RxBusyState;

} USART_Handle_t;

/*
 * @USART_Mode (config in USART_CR1 register)
 * Possible options for USART_Mode
 */
#define USART_MODE_TX	0
#define USART_MODE_RX	1
#define USART_MODE_TXRX	2


/*
 * @USART_BaudRate (config in USART_BRR register)
 * Possible options for USART_BaudRate
 */
#define USART_BAUD_1200		1200
#define	USART_BAUD_2400		2400
#define	USART_BAUD_9600		9600
#define	USART_BAUD_19200	19200
#define	USART_BAUD_38400	38400
#define	USART_BAUD_57600	57600
#define	USART_BAUD_115200	115200
#define	USART_BAUD_230400	230400
#define	USART_BAUD_460800	460800
#define	USART_BAUD_921600	921600
#define	USART_BAUD_2M		2000000
#define	USART_BAUD_3M		3000000

/*
 * @USART_NoOfStopBits (config in USART_CR2 register)
 * Possible options for USART_NoOfStopBits
 */
#define USART_STOP_BIT_1	0	// Generally stop bit is 1 for Baud Rate < 1 mbps.
#define USART_STOP_BIT_0_5	1	// Baud Rate <= 9600 we can use 0.5 stop bit.
#define USART_STOP_BIT_2	2	// Baud Rate >= 1 mbps use either 2 stop bits
#define USART_STOP_BIT_1_5	3	// or use 1.5 stop bit.

/*
 * @USART_WordLength
 * Possible options for USART_WordLength
 */
#define USART_WORDLEN_8BIT	0
#define USART_WORDLEN_9BIT	1

/*
 * @USART_ParityControl
 * Possible options for USART_ParityControl
 */
#define USART_PARITY_DISABLE	0
#define USART_PARITY_EN_EVEN	1
#define USART_PARITY_EN_ODD		2

/*
 * @USART_HWFlowControl
 * Possible options for USART_HWFlowControl
 */
#define USART_HW_FLOW_CTRL_NONE		0
#define USART_HW_FLOW_CTRL_CTS		1
#define USART_HW_FLOW_CTRL_RTS		2
#define USART_HW_FLOW_CTRL_CTS_RTS	3

/*
 * @USART_Flags
 * Possible options for USART_Flag
 */

#define USART_FLAG_TXE 			( 1 << USART_SR_TXE)		// TDR data transferred to shift register
#define USART_FLAG_RXNE 		( 1 << USART_SR_RXNE)		// RDR shift reg data transferred to USART DR
#define USART_FLAG_TC 			( 1 << USART_SR_TC)			// Transmission Complete Flag


/*
 * @USART Application states
 */
#define USART_BUSY_IN_RX 1
#define USART_BUSY_IN_TX 2
#define USART_READY 0

#define 	USART_EVENT_TX_CMPLT   0
#define		USART_EVENT_RX_CMPLT   1
#define		USART_EVENT_IDLE      2
#define		USART_EVENT_CTS       3
#define		USART_EVENT_PE        4
#define		USART_ERR_FE     	5
#define		USART_ERR_NE    	 6
#define		USART_ERR_ORE    	7



/******************************************************************************************************
 * 							APIs Supported by this driver
 * 			For more details about APIs check the function definitions in STM32f103xx.gpio.driver.c
 *
 *****************************************************************************************************/

/*
 * USART Init and Deint
 */
void USART_Init(USART_Handle_t *pUSARTx);
void USART_DeInit(USART_RegDef_t *pUSARTx);


/*
 * USART Peripheral Clock Setup
 */
void USART_PeriClockControl(USART_RegDef_t *pUSARTx, uint8_t EnOrDi);

/*
 * USART Baudrate setup
 */
void USART_SetBaudRate(USART_RegDef_t *pUSARTx, uint32_t BaudRate);

/*
 * USART Enable or Disable
 */
void USART_PeripheralControl(USART_RegDef_t *pUSARTx, uint8_t Cmd);

/*
 * USART Flag Status
 */
uint8_t USART_GetFlagStatus(USART_RegDef_t *pUSARTx, uint8_t StatusFlagName);

/*
 * Data Send and Receive
 */
void USART_SendData(USART_Handle_t *pUSARTx,uint8_t *pTxBuffer, uint32_t Len);
void USART_ReceiveData(USART_Handle_t *pUSARTx, uint8_t *pRxBuffer, uint32_t Len);
//uint8_t USART_SendDataIT(USART_Handle_t *pUSARTHandle,uint8_t *pTxBuffer, uint32_t Len);
//uint8_t USART_ReceiveDataIT(USART_Handle_t *pUSARTHandle, uint8_t *pRxBuffer, uint32_t Len);



#endif /* INC_STM32F103XX_USART_DRIVER_H_ */
