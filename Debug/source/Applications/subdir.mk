################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../source/Applications/gCompute.cpp \
../source/Applications/gInput.cpp \
../source/Applications/gMBox.cpp \
../source/Applications/gOutput.cpp 

OBJS += \
./source/Applications/gCompute.o \
./source/Applications/gInput.o \
./source/Applications/gMBox.o \
./source/Applications/gOutput.o 

CPP_DEPS += \
./source/Applications/gCompute.d \
./source/Applications/gInput.d \
./source/Applications/gMBox.d \
./source/Applications/gOutput.d 


# Each subdirectory must supply rules for building sources it contributes
source/Applications/%.o: ../source/Applications/%.cpp source/Applications/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -DCPU_MK64FN1M0VLL12 -DCPU_MK64FN1M0VLL12_cm4 -DSDK_OS_BAREMETAL -DSERIAL_PORT_TYPE_UART=1 -DSDK_DEBUGCONSOLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__NEWLIB__ -I"/home/Nick/Documents/MCUXpresso_11.5.0_7232/workspace/NXP/board" -I"/home/Nick/Documents/MCUXpresso_11.5.0_7232/workspace/NXP/source" -I"/home/Nick/Documents/MCUXpresso_11.5.0_7232/workspace/NXP/drivers" -I"/home/Nick/Documents/MCUXpresso_11.5.0_7232/workspace/NXP/utilities" -I"/home/Nick/Documents/MCUXpresso_11.5.0_7232/workspace/NXP/component/serial_manager" -I"/home/Nick/Documents/MCUXpresso_11.5.0_7232/workspace/NXP/component/uart" -I"/home/Nick/Documents/MCUXpresso_11.5.0_7232/workspace/NXP/component/lists" -I"/home/Nick/Documents/MCUXpresso_11.5.0_7232/workspace/NXP/CMSIS" -I"/home/Nick/Documents/MCUXpresso_11.5.0_7232/workspace/NXP/device" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fno-rtti -fno-exceptions -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__NEWLIB__ -fstack-usage -specs=nano.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


