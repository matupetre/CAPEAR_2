################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/capear_funciones.c \
../src/cr_startup_lpc176x.c \
../src/main.c 

OBJS += \
./src/capear_funciones.o \
./src/cr_startup_lpc176x.o \
./src/main.o 

C_DEPS += \
./src/capear_funciones.d \
./src/cr_startup_lpc176x.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_CMSIS=CMSISv2p00_LPC17xx -I"E:\FAKU\Sistemas_Embebidos\WORKSPACES\CAPEAR_2\RDB1768cmsis2_uIP\apps\webserver" -I"E:\FAKU\Sistemas_Embebidos\WORKSPACES\CAPEAR_2\RDB1768cmsis2_uIP\main" -I"E:\FAKU\Sistemas_Embebidos\WORKSPACES\CAPEAR_2\CAPEAR" -I"E:\FAKU\Sistemas_Embebidos\WORKSPACES\CAPEAR_2\CMSISv2p00_LPC17xx\inc" -I"E:\FAKU\Sistemas_Embebidos\WORKSPACES\CAPEAR_2\RDB1768cmsis2_uIP\uip" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/cr_startup_lpc176x.o: ../src/cr_startup_lpc176x.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_CMSIS=CMSISv2p00_LPC17xx -I"E:\FAKU\Sistemas_Embebidos\WORKSPACES\CAPEAR_2\RDB1768cmsis2_uIP\apps\webserver" -I"E:\FAKU\Sistemas_Embebidos\WORKSPACES\CAPEAR_2\RDB1768cmsis2_uIP\main" -I"E:\FAKU\Sistemas_Embebidos\WORKSPACES\CAPEAR_2\CAPEAR" -I"E:\FAKU\Sistemas_Embebidos\WORKSPACES\CAPEAR_2\CMSISv2p00_LPC17xx\inc" -I"E:\FAKU\Sistemas_Embebidos\WORKSPACES\CAPEAR_2\RDB1768cmsis2_uIP\uip" -Os -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"src/cr_startup_lpc176x.d" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


