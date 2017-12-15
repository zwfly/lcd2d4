################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Common/src/Common.c \
../Common/src/Delay.c \
../Common/src/Display.c \
../Common/src/Version.c 

OBJS += \
./Common/src/Common.o \
./Common/src/Delay.o \
./Common/src/Display.o \
./Common/src/Version.o 

C_DEPS += \
./Common/src/Common.d \
./Common/src/Delay.d \
./Common/src/Display.d \
./Common/src/Version.d 


# Each subdirectory must supply rules for building sources it contributes
Common/src/%.o: ../Common/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -DFOSC_110592 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


