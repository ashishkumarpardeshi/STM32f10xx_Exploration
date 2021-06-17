# Serial Peripheral Interface (SPI)

SPI is a one of the serial protocol which is used to communicate between one Master device and one or more Slave devices in Embedded Systems. 

- *Four Wire Communication Protocol*
- *Full-Duplex, Serial Communication Protocol*
- *Synchronous Commuincation Protocol*
- *Single Master Multi Slave*

 <p align="center">
  <img src="./Assets/SPI_Basic1.jpg">
</p>

Master can be your host microcontroller and slaves can be devices such as SD Card, Ethernet, Sensors, EEPROM etc.

## SPI Bus
Four I/O pins are used for SPI communication.

- ***SCK (Serial Clock)*** : Serial Clock Output by master and input by Slave. 
It carries clock signal from master to slave. The data communication via MOSI and MISO between master and slave is synchronised with the clock. Therefore SPI is also called as Serial Synchronous Communication Protocol. 
**Always master will only generate the clock.**

- ***MOSI (Master Out Slave In)*** : Master Transmit Data and Slave recieve data.

- ***MISO (Master In Slave Out)*** : Slave transmit data and Master recieve data.

- ***SS (Slave Control)*** : It is used to select the individual Slave device for communicating to master.  When more than one Slave device is used then particular slave device SS line is drive to logic low by master .

**If there is only one slave device on SPI bus then the SS pin of the slave device can be pulled down to ground (GND) of the circuit as this will save the GPIO/SS pin on the master for other application.**

<p align="center">
  <img src="./Assets/SPI_Basic2.jpg">
</p>


> SPI is Short Distance and Low Speed Serial Synchronous Communication Protocol.
>
> - **SPI can achieve Maximum Distance upto 10 feet**
>
> - **SPI can achieve Maximum Speed upto Fpclk/2 bps**
>
> SPI communicate over TTL logic in the voltage range 0v to 5v, this is one of the reason for short distance communication.

## SPI Minimal BUS
As we have seen earlier that four wires required for SPI bus (ie SCK, MOSI, MISO and SS) for comunication between a master and one slave but these four wires can also be reduced to 2 wires.

Lets check out how.

<p align="center">
  <img src="./Assets/SPI_Basic3.jpg">
</p>

When a slave device on SPI bus  is capable of only recieving data from master and never send any data back to master thus there is no requirement of connecting MISO pins between that slave and master.

## SPI Slave Selection and Communication

Devices on SPI bus can either operates as Master or Slave. There must be atleast one master who can initiate communication with any of the slave devices.

Whenever there are more than one slave then it becomes realy important to first select the slave with whom master wants to talk. 

<p align="center">
  <img src="./Assets/SPI_Slave_selection.jpg">
</p>

The Master select the slave for communication by driving that particular slave SS pin to logic low via its GPIO pin and keeping all other slave SS line to logic high.

In this example say master wants to communicate to SLAVE 3 (ie Some Sensor) then at first master needs to select this sensor for communication by driving its GPIO_3 pin to Logic LOW which in turns drive the SS3 pin of SPI Sensor to Logic LOW. And very important the master will also drive GPIO_1 and GPIO_2 to Logic HIGH therefore Slave 1 (SD Card) and Slave 2 (Display) will not get involved while master is talking to SPI Sensor.

## SPI Hardware Architecture

SPI Communication is based on shift register. lets try to understand the internal of SPI Hardware Architecure.

<p align="center">
  <img src="./Assets/SPI_Internal1.jpg">
</p>

At every clock event the data communication will take place  and whenever master send the data to slave via MOSI pin, the master will also recieve data from slave via MISO pin because the shift register of master is connected to shift register of slave in a looping fashion.

That is the LSB of master shift register is connected serially to the MSB of slave shift register via MOSI.

Similarly the LSB of slave shift register is connected to MSB of master shift register via MISO.


## SPI Communication Configuration

The SPI communication allows the master to communicate using different configurations, depending on the device targeted and the application requirements.

- ***Full Duplex Communication*** : 
By default SPI is configured for full duplex communication.

- ***Half Duplex Communication*** :

- ***Simplex Communication***


### In SPI communiaction SPI is only produced when the Data is placed on MOSI Line.

