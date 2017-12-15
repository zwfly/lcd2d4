################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Bsp/src/bsp_2d4.c \
../Bsp/src/bsp_adc.c \
../Bsp/src/bsp_display.c \
../Bsp/src/bsp_key.c \
../Bsp/src/bsp_keyBright.c \
../Bsp/src/bsp_lcdBright.c \
../Bsp/src/bsp_timer0.c 

OBJS += \
./Bsp/src/bsp_2d4.o \
./Bsp/src/bsp_adc.o \
./Bsp/src/bsp_display.o \
./Bsp/src/bsp_key.o \
./Bsp/src/bsp_keyBright.o \
./Bsp/src/bsp_lcdBright.o \
./Bsp/src/bsp_timer0.o 

C_DEPS += \
./Bsp/src/bsp_2d4.d \
./Bsp/src/bsp_adc.d \
./Bsp/src/bsp_display.d \
./Bsp/src/bsp_key.d \
./Bsp/src/bsp_keyBright.d \
./Bsp/src/bsp_lcdBright.d \
./Bsp/src/bsp_timer0.d 


# Each subdirectory must supply rules for building sources it contributes
Bsp/src/%.o: ../Bsp/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -DFOSC_110592 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


