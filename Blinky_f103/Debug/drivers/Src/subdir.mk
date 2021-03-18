################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/Src/STM32f103xx_gpio_driver.c 

OBJS += \
./drivers/Src/STM32f103xx_gpio_driver.o 

C_DEPS += \
./drivers/Src/STM32f103xx_gpio_driver.d 


# Each subdirectory must supply rules for building sources it contributes
drivers/Src/STM32f103xx_gpio_driver.o: ../drivers/Src/STM32f103xx_gpio_driver.c drivers/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -c -I"/home/ashish/Documents/Embedded_World/STM32_World/STM32f10xx_Exploration/Blinky_f103/drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"drivers/Src/STM32f103xx_gpio_driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

