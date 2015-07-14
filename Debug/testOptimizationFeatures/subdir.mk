################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../testOptimizationFeatures/TestNMOptimizer.cpp 

OBJS += \
./testOptimizationFeatures/TestNMOptimizer.o 

CPP_DEPS += \
./testOptimizationFeatures/TestNMOptimizer.d 


# Each subdirectory must supply rules for building sources it contributes
testOptimizationFeatures/%.o: ../testOptimizationFeatures/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


