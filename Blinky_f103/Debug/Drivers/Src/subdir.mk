################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Src/STM32f103xx_gpio_driver.c 

OBJS += \
./Drivers/Src/STM32f103xx_gpio_driver.o 

C_DEPS += \
./Drivers/Src/STM32f103xx_gpio_driver.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Src/STM32f103xx_gpio_driver.o: ../Drivers/Src/STM32f103xx_gpio_driver.c Drivers/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -c -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/Src/STM32f103xx_gpio_driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

