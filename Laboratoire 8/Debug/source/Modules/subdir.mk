################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/Modules/mCpu.c \
../source/Modules/mDelay.c \
../source/Modules/mLcd.c \
../source/Modules/mLeds.c \
../source/Modules/mSwitch.c 

OBJS += \
./source/Modules/mCpu.o \
./source/Modules/mDelay.o \
./source/Modules/mLcd.o \
./source/Modules/mLeds.o \
./source/Modules/mSwitch.o 

C_DEPS += \
./source/Modules/mCpu.d \
./source/Modules/mDelay.d \
./source/Modules/mLcd.d \
./source/Modules/mLeds.d \
./source/Modules/mSwitch.d 


# Each subdirectory must supply rules for building sources it contributes
source/Modules/%.o: ../source/Modules/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MKL46Z256VLL4 -DCPU_MKL46Z256VLL4_cm0plus -DSDK_OS_BAREMETAL -DFSL_RTOS_BM -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__NEWLIB__ -I../board -I../source -I../ -I../drivers -I../CMSIS -I../utilities -I../startup -I../source/Gestionnaires -I../source/Interfaces -I../source/Modules -I../source/Utils -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -mcpu=cortex-m0plus -mthumb -D__NEWLIB__ -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


