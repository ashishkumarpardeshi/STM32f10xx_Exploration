# STM32 UART and USART Peripheral

***UART*** is Universal Asynchronous Reciever and Transmitter.

***USART*** is Synchronous and Asynchronous Reciever and Transmitter.

- USART and UART are inbuit peripheral hardware which converts parallel data into serial data.

- UART only support Asynchronous mode.

- USART supports both Synchronous and Asynchronous mode.

    - In Synchronus mode, the clock is sent separately from data stream and no start/stop bits are used.


>All MCUs comes with USART module so we can use it in both synchronous mode as well as asynchronus mode.

***There is no specific port for USART communication. They are commonly used in conjugation with protocols like RS-232, RS-434, USB, etc.***


## USART Hardware Components

- Baud rate generator
- TX and Rx     


## Steps for Data Transmission

- Program the M-Bit in USART_CR1 to define the word length.

- Program the number of stop bits in USART_CR2 register.

- Select the desired Baud Rate using USART_BRR register.

- Set the TE bit in USART_CR1 to enable the transmit block.

- Enable the USART by writing the UE bit in USART_CR1.

- Now if TXE flag is set, then write the data byte to send, in the USART_DR register.

- After writing the last data into the USART_DR register, wait until TC=1 (Transmission complete Flag).


## Steps for Data Reception

- Program the M-Bit in USART_CR1 to define the word length.

- Program the number of stop bits in USART_CR2 register.

- Select the desired Baud Rate using USART_BRR register.

- Enable the USART by writing the UE bit in USART_CR1.

- Set the RE bit in USART_CR1 to enable the Reciever block.

- When a character is recieved, wait till the RXNE bit is set and read the data byte from the data register.

- The RXNE bit must be cleared by reading the data register, before the end of the reception of the next chapter to avoid an overrun error. 

Instead on polling on RXNE flag we can also get an interrupt by enabling this interrupt.


