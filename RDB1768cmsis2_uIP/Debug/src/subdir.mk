################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/cr_startup_lpc176x.c 

OBJS += \
./src/cr_startup_lpc176x.o 

C_DEPS += \
./src/cr_startup_lpc176x.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__USE_CMSIS=CMSISv2p00_LPC17xx -DDEBUG -D__CODE_RED -D_RDB1768_ -D__REDLIB__ -I"E:\FAKU\Sistemas_Embebidos\WORKSPACES\CAPEAR_2\CAPEAR\src" -I"E:\FAKU\Sistemas_Embebidos\WORKSPACES\CAPEAR_2\CMSISv2p00_LPC17xx\inc" -I"E:/FAKU/Sistemas_Embebidos/WORKSPACES/CAPEAR_2/RDB1768cmsis2_uIP/main" -I"E:/FAKU/Sistemas_Embebidos/WORKSPACES/CAPEAR_2/RDB1768cmsis2_uIP/main/lpc1700" -I"E:/FAKU/Sistemas_Embebidos/WORKSPACES/CAPEAR_2/RDB1768cmsis2_uIP/uip" -I"E:/FAKU/Sistemas_Embebidos/WORKSPACES/CAPEAR_2/RDB1768cmsis2_uIP/apps/webserver" -O0 -g3 -c -fmessage-length=0 -fno-builtin -ffunction-sections -mcpu=cortex-m3 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


