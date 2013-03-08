################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../uip/psock.c \
../uip/timer.c \
../uip/uip-fw.c \
../uip/uip-neighbor.c \
../uip/uip-split.c \
../uip/uip.c \
../uip/uip_arp.c \
../uip/uiplib.c 

OBJS += \
./uip/psock.o \
./uip/timer.o \
./uip/uip-fw.o \
./uip/uip-neighbor.o \
./uip/uip-split.o \
./uip/uip.o \
./uip/uip_arp.o \
./uip/uiplib.o 

C_DEPS += \
./uip/psock.d \
./uip/timer.d \
./uip/uip-fw.d \
./uip/uip-neighbor.d \
./uip/uip-split.d \
./uip/uip.d \
./uip/uip_arp.d \
./uip/uiplib.d 


# Each subdirectory must supply rules for building sources it contributes
uip/%.o: ../uip/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__USE_CMSIS=CMSISv2p00_LPC17xx -DDEBUG -D__CODE_RED -D_RDB1768_ -D__REDLIB__ -I"E:\FAKU\Sistemas_Embebidos\WORKSPACES\CAPEAR_2\CAPEAR\src" -I"E:\FAKU\Sistemas_Embebidos\WORKSPACES\CAPEAR_2\CMSISv2p00_LPC17xx\inc" -I"E:/FAKU/Sistemas_Embebidos/WORKSPACES/CAPEAR_2/RDB1768cmsis2_uIP/main" -I"E:/FAKU/Sistemas_Embebidos/WORKSPACES/CAPEAR_2/RDB1768cmsis2_uIP/main/lpc1700" -I"E:/FAKU/Sistemas_Embebidos/WORKSPACES/CAPEAR_2/RDB1768cmsis2_uIP/uip" -I"E:/FAKU/Sistemas_Embebidos/WORKSPACES/CAPEAR_2/RDB1768cmsis2_uIP/apps/webserver" -O0 -g3 -c -fmessage-length=0 -fno-builtin -ffunction-sections -mcpu=cortex-m3 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


