# Conceptualizing and Designing STM32F103C8 Dev Board

This note is to conceptualize and design a STM32F103C8 (BluePill) based Development board consisting of peripheral devices, Peripheral Expansion connectors, Power Management etc.

The main goal for designing this board is to boost the exploration and learning curve of STM32 Cortex M3 Core and developing the firmware and drivers from the scratch without getting into hassles of interfacing peripheral devices using bread board.


<br>


## My plan is encorporate most of the followings to this Dev Board with possible compact form factor.

<br>

### ***MCU***
- STM32F103C8 Bluepill Board at center of this board. 

<br>

### ***Peripheral Devices***
- LEDs x 8
- Buzzer x 1
- Two Digit Seven Segment Display
- LCD 16 x 2
- WS2812 Addressable LED x2
- Push Buttons x 2
- Potentiometer (Multiturn) x 1
- ESP01 (WiFi MOdule)
- HC-05 (Bluetooth Module)
- SD Card Interface Slot
- nRF24L01 Radio Module
- OLED (128 x 64)
- MPU6050 (IMU)

<br>

### ***Peripheral Expansion Connectors***
- GPIOs Ports
- I2C Port (Vcc, Gnd, SDA, SCL) x 2
- SPI Port (VCC, Gnd, MISO, MOSI, SCK, CS)
- CAN Port

<br>

### ***Programming Interface***
- USB Connector via CH340 to UART
- SWD Connector (available on Bluepill Board)


