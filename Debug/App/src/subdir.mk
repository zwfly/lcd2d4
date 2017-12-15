################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App/src/app_2d4.c \
../App/src/app_key.c \
../App/src/app_lcd.c \
../App/src/app_repeat_exe.c \
../App/src/app_work.c \
../App/src/main.c 

OBJS += \
./App/src/app_2d4.o \
./App/src/app_key.o \
./App/src/app_lcd.o \
./App/src/app_repeat_exe.o \
./App/src/app_work.o \
./App/src/main.o 

C_DEPS += \
./App/src/app_2d4.d \
./App/src/app_key.d \
./App/src/app_lcd.d \
./App/src/app_repeat_exe.d \
./App/src/app_work.d \
./App/src/main.d 


# Each subdirectory must supply rules for building sources it contributes
App/src/%.o: ../App/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -DFOSC_110592 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


