################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/interface/iCpu.c \
../source/interface/iDio.c \
../source/interface/iPit.c 

OBJS += \
./source/interface/iCpu.o \
./source/interface/iDio.o \
./source/interface/iPit.o 

C_DEPS += \
./source/interface/iCpu.d \
./source/interface/iDio.d \
./source/interface/iPit.d 


# Each subdirectory must supply rules for building sources it contributes
source/interface/%.o: ../source/interface/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MKL46Z256VLL4 -DCPU_MKL46Z256VLL4_cm0plus -DSDK_OS_BAREMETAL -DFSL_RTOS_BM -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__NEWLIB__ -I../board -I../source -I../ -I../drivers -I../CMSIS -I../utilities -I../startup -I../source/gestionnaire -I../source/module -I../source/interface -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -mcpu=cortex-m0plus -mthumb -D__NEWLIB__ -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


