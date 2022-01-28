################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/Interfaces/iAd.c \
../source/Interfaces/iCpu.c \
../source/Interfaces/iDac.c \
../source/Interfaces/iDio.c \
../source/Interfaces/iFlextimer.c \
../source/Interfaces/iI2C.c \
../source/Interfaces/iPit.c \
../source/Interfaces/iSpi.c \
../source/Interfaces/iUart.c 

OBJS += \
./source/Interfaces/iAd.o \
./source/Interfaces/iCpu.o \
./source/Interfaces/iDac.o \
./source/Interfaces/iDio.o \
./source/Interfaces/iFlextimer.o \
./source/Interfaces/iI2C.o \
./source/Interfaces/iPit.o \
./source/Interfaces/iSpi.o \
./source/Interfaces/iUart.o 

C_DEPS += \
./source/Interfaces/iAd.d \
./source/Interfaces/iCpu.d \
./source/Interfaces/iDac.d \
./source/Interfaces/iDio.d \
./source/Interfaces/iFlextimer.d \
./source/Interfaces/iI2C.d \
./source/Interfaces/iPit.d \
./source/Interfaces/iSpi.d \
./source/Interfaces/iUart.d 


# Each subdirectory must supply rules for building sources it contributes
source/Interfaces/%.o: ../source/Interfaces/%.c source/Interfaces/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__NEWLIB__ -DCPU_MK64FN1M0VLL12 -DCPU_MK64FN1M0VLL12_cm4 -DSDK_OS_BAREMETAL -DSERIAL_PORT_TYPE_UART=1 -DSDK_DEBUGCONSOLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"/home/Nick/NXP/NXP/board" -I"/home/Nick/NXP/NXP/source" -I"/home/Nick/NXP/NXP/drivers" -I"/home/Nick/NXP/NXP/utilities" -I"/home/Nick/NXP/NXP/component/serial_manager" -I"/home/Nick/NXP/NXP/component/uart" -I"/home/Nick/NXP/NXP/component/lists" -I"/home/Nick/NXP/NXP/CMSIS" -I"/home/Nick/NXP/NXP/device" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__NEWLIB__ -fstack-usage -specs=nano.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


