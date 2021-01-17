################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/Gestionnaires/gCompute.c \
../source/Gestionnaires/gInput.c \
../source/Gestionnaires/gMBox.c \
../source/Gestionnaires/gOutput.c \
../source/Gestionnaires/gTerminal.c \
../source/Gestionnaires/main.c 

OBJS += \
./source/Gestionnaires/gCompute.o \
./source/Gestionnaires/gInput.o \
./source/Gestionnaires/gMBox.o \
./source/Gestionnaires/gOutput.o \
./source/Gestionnaires/gTerminal.o \
./source/Gestionnaires/main.o 

C_DEPS += \
./source/Gestionnaires/gCompute.d \
./source/Gestionnaires/gInput.d \
./source/Gestionnaires/gMBox.d \
./source/Gestionnaires/gOutput.d \
./source/Gestionnaires/gTerminal.d \
./source/Gestionnaires/main.d 


# Each subdirectory must supply rules for building sources it contributes
source/Gestionnaires/%.o: ../source/Gestionnaires/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MKL46Z256VLL4 -DCPU_MKL46Z256VLL4_cm0plus -DSDK_OS_BAREMETAL -DFSL_RTOS_BM -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__NEWLIB__ -I../board -I../source -I../ -I../drivers -I../CMSIS -I../utilities -I../startup -I../source/Gestionnaires -I../source/Interfaces -I../source/Modules -I../source/Utils -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -mcpu=cortex-m0plus -mthumb -D__NEWLIB__ -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


