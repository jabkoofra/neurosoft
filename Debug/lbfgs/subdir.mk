################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lbfgs/lbfgs.c \
../lbfgs/sample.c 

OBJS += \
./lbfgs/lbfgs.o \
./lbfgs/sample.o 

C_DEPS += \
./lbfgs/lbfgs.d \
./lbfgs/sample.d 


# Each subdirectory must supply rules for building sources it contributes
lbfgs/%.o: ../lbfgs/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


