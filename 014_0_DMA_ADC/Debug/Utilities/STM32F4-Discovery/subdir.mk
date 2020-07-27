################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Utilities/STM32F4-Discovery/stm32f4_discovery.c \
../Utilities/STM32F4-Discovery/stm32f4_discovery_audio_codec.c \
../Utilities/STM32F4-Discovery/stm32f4_discovery_lis302dl.c 

OBJS += \
./Utilities/STM32F4-Discovery/stm32f4_discovery.o \
./Utilities/STM32F4-Discovery/stm32f4_discovery_audio_codec.o \
./Utilities/STM32F4-Discovery/stm32f4_discovery_lis302dl.o 

C_DEPS += \
./Utilities/STM32F4-Discovery/stm32f4_discovery.d \
./Utilities/STM32F4-Discovery/stm32f4_discovery_audio_codec.d \
./Utilities/STM32F4-Discovery/stm32f4_discovery_lis302dl.d 


# Each subdirectory must supply rules for building sources it contributes
Utilities/STM32F4-Discovery/stm32f4_discovery.o: ../Utilities/STM32F4-Discovery/stm32f4_discovery.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F4XX -DSTM32F40XX -DUSE_STDPERIPH_DRIVER -DUSE_STM32F4_DISCOVERY '-DHSE_VALUE=8000000' -c -I../src -I../Libraries/CMSIS/Include -I../Libraries/Device/STM32F4xx/Include -I../Libraries/STM32F4xx_StdPeriph_Driver/inc -I../Utilities/STM32F4-Discovery -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Utilities/STM32F4-Discovery/stm32f4_discovery.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Utilities/STM32F4-Discovery/stm32f4_discovery_audio_codec.o: ../Utilities/STM32F4-Discovery/stm32f4_discovery_audio_codec.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F4XX -DSTM32F40XX -DUSE_STDPERIPH_DRIVER -DUSE_STM32F4_DISCOVERY '-DHSE_VALUE=8000000' -c -I../src -I../Libraries/CMSIS/Include -I../Libraries/Device/STM32F4xx/Include -I../Libraries/STM32F4xx_StdPeriph_Driver/inc -I../Utilities/STM32F4-Discovery -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Utilities/STM32F4-Discovery/stm32f4_discovery_audio_codec.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Utilities/STM32F4-Discovery/stm32f4_discovery_lis302dl.o: ../Utilities/STM32F4-Discovery/stm32f4_discovery_lis302dl.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F4XX -DSTM32F40XX -DUSE_STDPERIPH_DRIVER -DUSE_STM32F4_DISCOVERY '-DHSE_VALUE=8000000' -c -I../src -I../Libraries/CMSIS/Include -I../Libraries/Device/STM32F4xx/Include -I../Libraries/STM32F4xx_StdPeriph_Driver/inc -I../Utilities/STM32F4-Discovery -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Utilities/STM32F4-Discovery/stm32f4_discovery_lis302dl.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

