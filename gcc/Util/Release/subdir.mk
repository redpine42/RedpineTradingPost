################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Conversions.cpp \
../DataPrepUtil.cpp \
../TimeWrapper.cpp 

OBJS += \
./Conversions.o \
./DataPrepUtil.o \
./TimeWrapper.o 

CPP_DEPS += \
./Conversions.d \
./DataPrepUtil.d \
./TimeWrapper.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


