################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include MCAL/subdir.mk
-include HAL/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
Copy_of_Sergutic_Pump.lss \

FLASH_IMAGE += \
Copy_of_Sergutic_Pump.hex \

EEPROM_IMAGE += \
Copy_of_Sergutic_Pump.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: Copy_of_Sergutic_Pump.elf secondary-outputs

# Tool invocations
Copy_of_Sergutic_Pump.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Copy_of_Sergutic_Pump.map -mmcu=atmega328p -o "Copy_of_Sergutic_Pump.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Copy_of_Sergutic_Pump.lss: Copy_of_Sergutic_Pump.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Copy_of_Sergutic_Pump.elf  >"Copy_of_Sergutic_Pump.lss"
	@echo 'Finished building: $@'
	@echo ' '

Copy_of_Sergutic_Pump.hex: Copy_of_Sergutic_Pump.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex Copy_of_Sergutic_Pump.elf  "Copy_of_Sergutic_Pump.hex"
	@echo 'Finished building: $@'
	@echo ' '

Copy_of_Sergutic_Pump.eep: Copy_of_Sergutic_Pump.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex Copy_of_Sergutic_Pump.elf  "Copy_of_Sergutic_Pump.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Copy_of_Sergutic_Pump.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega328p Copy_of_Sergutic_Pump.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) Copy_of_Sergutic_Pump.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
