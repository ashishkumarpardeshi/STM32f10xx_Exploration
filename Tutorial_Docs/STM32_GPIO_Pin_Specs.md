# STM32 GPIO Pin Specs

Lets explore the GPIO pin specification of STM32 MCU. So here we will be looking into the STM32F103C8 datasheet and finding cititcal parameters such as Power supply, source and sink current of GPIO, voltage levels etc.

## Table of Content

- [STM32 GPIO Pin Specs](#stm32-gpio-pin-specs)

- [Table of Content](#table-of-content)

- [Absolute Maximum Rating](#absolute-maximum-rating)


## Absolute Maximum Rating (AMR)

### General Operating Conditions

- It guaranteed values within which the device operates in proper conditions.
- It also talk about handling of various parameters of peripherals like frequency of operation, bus etc.

### What is the maximum input voltage which can be applied to any pin of STM32 MCU?

## Ivdd
- Total curent into VDD power lines (source) of MCU.

- It is the total current the MCu will draw from VDD power lines to the external interfacings.

- In STM32 Max Ivdd = 240 mA. (At maximum, MCU can source this current). 

## Ivss
- Total curent out from VSS ground lines (sink) of MCU.

- It is the total current the MCU will sink to VSS ground lines from the external interfacings.

- In STM32 Max Ivss = 240 mA. (At maximum, MCU can sink this current).

## I/O Source Current

- Maximum current which flows out of the device through GPIO output pin when HIGH.

- In STM32 Max Source Current = 25 mA

[//]:<> (Add current sourcing example ckt)

## I/O Source Current

- Maximum current which can be sunk in to Vss by a GPIO pin when LOW.

- In STM32 Max Sink Current = 25 mA

[//]:<> (Add current sinking example ckt)

## Injected Current (Iinj)

- It is the current that is being forced into the pin by an input voltage (Vin) higher than the positive supply (Vdd) or lower the ground supply (Vss).

- Injection current above the given specification causes a current flow inside the device and affects its reliability. Even a tiny current exceeding the specification is not allowed.

**Negative-Injection Current**

- It is the current induced when Vin < Vss.

- The Max negative injected current is -5 mA.

- Min Voltage Level accepted on the GPIO is -0.3 V for TT (Three-Volt Tolerant) and FT (Five-Volt Tolerant) GPIO.

**Positive-Injection Current**

- It is the current induced when Vin > Vdd.

- The Max negative injected current is -5 mA.

- Min Voltage Level accepted on FT GPIO is defined as N/A or 0 mA.

- 0 mA means that the current injection can damage the GPIO and induce the STM32 malfuntion.

- **Positive injection current is probhited for both TT and FT if not defined.**

- As long as Vin on FT is less than AMR (vdd + 4V) the positive injection won't happen.

- The upper limit 0-mA indicates that the positive injection current should never flow into the  GPIO Pin, otherwise, the device may be damaged. 

- If vin goes beyond Vdd + 4V, then positive injection happens, and the device may be damaged if the injection current is above the threshold, which is not mentioned in the datasheet.


## Logic Levels

It defines Threshold voltage for logic '0' and threshold voltage for logic '1'.

- All I/Os are CMOS and TTL compliant.

When Ever we are interfacing two devices, we should look for Logic Level compatibility, otherwise those two devices will not talk to each other or their could be data curruption.

In the case of communication exchange,

>- STM32 O/P signals must be compatible with the V(IL)/V(IH) (Input Threshold Volatges) of the receptor device.
>
>- STM32 I/P must be compliant with V(OL)/V(OH) (Output Threshold Voltages) of the transmitter device.

**V(IL)** : It is the maximum voltage level that is interpreted as a logical 0 by a digital input.

**V(IH)** : It is the minimum voltage level that is interpreted as a logical 1 by a digital input.

**V(OL)** : It is the maximum Output Low level voltage which can be interpreted as logic 0.

**V(OH)** : It is the minimum Output HIGH level voltage which can be interpreted as logic 1.

> Please Note :
>
>- For CMOS Technology, the input threshold voltages are relative to Vdd as follows:
>
>   ***V(IH)min : ~ 2/3 Vdd & V(IL)max : ~ 1/3 Vdd***
>
>- For TTL technology, the levels are fixed as follows:
>
>   ***V(IH)min = 2V & V(IL)max = 0.8v***

<br>

> **STM32 MCUs are based on CMOS Technology thus the Threshold Voltages for Input and Output will be relative to Vdd.**















