################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include uip/subdir.mk
-include src/subdir.mk
-include main/subdir.mk
-include main/lpc1700/subdir.mk
-include apps/webserver/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: RDB1768cmsis2_uIP.axf

# Tool invocations
RDB1768cmsis2_uIP.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"E:\FAKU\Sistemas_Embebidos\WORKSPACES\CAPEAR_2\CMSISv2p00_LPC17xx\Debug" -Xlinker --gc-sections -Xlinker -Map=RDB1768cmsis2_uIP.map -mcpu=cortex-m3 -mthumb -T "RDB1768cmsis2_uIP_Debug.ld" -o"RDB1768cmsis2_uIP.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES) RDB1768cmsis2_uIP.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size RDB1768cmsis2_uIP.axf; arm-none-eabi-objcopy -O binary RDB1768cmsis2_uIP.axf RDB1768cmsis2_uIP.bin ; checksum -p LPC1768 -d RDB1768cmsis2_uIP.bin;
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
