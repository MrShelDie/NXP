################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../component/uart/fsl_adapter_uart.c 

OBJS += \
./component/uart/fsl_adapter_uart.o 

C_DEPS += \
./component/uart/fsl_adapter_uart.d 


# Each subdirectory must supply rules for building sources it contributes
component/uart/%.o: ../component/uart/%.c component/uart/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__NEWLIB__ -DCPU_MK64FN1M0VLL12 -DCPU_MK64FN1M0VLL12_cm4 -DSDK_OS_BAREMETAL -DSERIAL_PORT_TYPE_UART=1 -DSDK_DEBUGCONSOLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"/home/Nick/Documents/MCUXpresso_11.5.0_7232/workspace/NXP/board" -I"/home/Nick/Documents/MCUXpresso_11.5.0_7232/workspace/NXP/source" -I"/home/Nick/Documents/MCUXpresso_11.5.0_7232/workspace/NXP/drivers" -I"/home/Nick/Documents/MCUXpresso_11.5.0_7232/workspace/NXP/utilities" -I"/home/Nick/Documents/MCUXpresso_11.5.0_7232/workspace/NXP/component/serial_manager" -I"/home/Nick/Documents/MCUXpresso_11.5.0_7232/workspace/NXP/component/uart" -I"/home/Nick/Documents/MCUXpresso_11.5.0_7232/workspace/NXP/component/lists" -I"/home/Nick/Documents/MCUXpresso_11.5.0_7232/workspace/NXP/CMSIS" -I"/home/Nick/Documents/MCUXpresso_11.5.0_7232/workspace/NXP/device" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__NEWLIB__ -fstack-usage -specs=nano.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


