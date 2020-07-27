################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../src/startup_stm32f40xx.s 

C_SRCS += \
../src/main.c \
../src/stm32f4xx_it.c \
../src/system_stm32f4xx.c \
../src/tiny_printf.c 

OBJS += \
./src/main.o \
./src/startup_stm32f40xx.o \
./src/stm32f4xx_it.o \
./src/system_stm32f4xx.o \
./src/tiny_printf.o 

C_DEPS += \
./src/main.d \
./src/stm32f4xx_it.d \
./src/system_stm32f4xx.d \
./src/tiny_printf.d 


# Each subdirectory must supply rules for building sources it contributes
src/main.o: ../src/main.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F4XX -DSTM32F40XX -DUSE_STDPERIPH_DRIVER -DUSE_STM32F4_DISCOVERY '-DHSE_VALUE=8000000' -c -I../src -I../Libraries/CMSIS/Include -I../Libraries/Device/STM32F4xx/Include -I../Libraries/STM32F4xx_StdPeriph_Driver/inc -I../Utilities/STM32F4-Discovery -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"src/main.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
src/%.o: ../src/%.s
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -DSTM32F4XX -DSTM32F40XX -DUSE_STDPERIPH_DRIVER -DUSE_STM32F4_DISCOVERY '-DHSE_VALUE=8000000' -c -I../src -I../Libraries/CMSIS/Include -I../Libraries/Device/STM32F4xx/Include -I../Libraries/STM32F4xx_StdPeriph_Driver/inc -I../Utilities/STM32F4-Discovery -x assembler-with-cpp --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"
src/stm32f4xx_it.o: ../src/stm32f4xx_it.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F4XX -DSTM32F40XX -DUSE_STDPERIPH_DRIVER -DUSE_STM32F4_DISCOVERY '-DHSE_VALUE=8000000' -c -I../src -I../Libraries/CMSIS/Include -I../Libraries/Device/STM32F4xx/Include -I../Libraries/STM32F4xx_StdPeriph_Driver/inc -I../Utilities/STM32F4-Discovery -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"src/stm32f4xx_it.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
src/system_stm32f4xx.o: ../src/system_stm32f4xx.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F4XX -DSTM32F40XX -DUSE_STDPERIPH_DRIVER -DUSE_STM32F4_DISCOVERY '-DHSE_VALUE=8000000' -c -I../src -I../Libraries/CMSIS/Include -I../Libraries/Device/STM32F4xx/Include -I../Libraries/STM32F4xx_StdPeriph_Driver/inc -I../Utilities/STM32F4-Discovery -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"src/system_stm32f4xx.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
src/tiny_printf.o: ../src/tiny_printf.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F4XX -DSTM32F40XX -DUSE_STDPERIPH_DRIVER -DUSE_STM32F4_DISCOVERY '-DHSE_VALUE=8000000' -c -I../src -I../Libraries/CMSIS/Include -I../Libraries/Device/STM32F4xx/Include -I../Libraries/STM32F4xx_StdPeriph_Driver/inc -I../Utilities/STM32F4-Discovery -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"src/tiny_printf.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

