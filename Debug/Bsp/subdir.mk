################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Bsp/bsp.c 

OBJS += \
./Bsp/bsp.o 

C_DEPS += \
./Bsp/bsp.d 


# Each subdirectory must supply rules for building sources it contributes
Bsp/%.o: ../Bsp/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -DFOSC_110592 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


