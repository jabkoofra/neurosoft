################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../abscd/source/OWLQN.cpp \
../abscd/source/TerminationCriterion.cpp \
../abscd/source/leastSquares.cpp \
../abscd/source/logreg.cpp \
../abscd/source/main.cpp 

OBJS += \
./abscd/source/OWLQN.o \
./abscd/source/TerminationCriterion.o \
./abscd/source/leastSquares.o \
./abscd/source/logreg.o \
./abscd/source/main.o 

CPP_DEPS += \
./abscd/source/OWLQN.d \
./abscd/source/TerminationCriterion.d \
./abscd/source/leastSquares.d \
./abscd/source/logreg.d \
./abscd/source/main.d 


# Each subdirectory must supply rules for building sources it contributes
abscd/source/%.o: ../abscd/source/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


