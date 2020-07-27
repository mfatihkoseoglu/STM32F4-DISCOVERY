################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include Drivers/STM32F4xx_HAL_Driver/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
EXAMPLE_10_I2C_2x16_DISPLAY.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
EXAMPLE_10_I2C_2x16_DISPLAY.list \


# All Target
all: EXAMPLE_10_I2C_2x16_DISPLAY.elf secondary-outputs

# Tool invocations
EXAMPLE_10_I2C_2x16_DISPLAY.elf: $(OBJS) $(USER_OBJS) C:\Users\ATSON\STM32CubeIDE\workspace_1.0.2\EXAMPLE_10_I2C_2x16_DISPLAY\STM32F407VGTX_FLASH.ld
	arm-none-eabi-gcc -o "EXAMPLE_10_I2C_2x16_DISPLAY.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"C:\Users\ATSON\STM32CubeIDE\workspace_1.0.2\EXAMPLE_10_I2C_2x16_DISPLAY\STM32F407VGTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="EXAMPLE_10_I2C_2x16_DISPLAY.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

EXAMPLE_10_I2C_2x16_DISPLAY.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "EXAMPLE_10_I2C_2x16_DISPLAY.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
