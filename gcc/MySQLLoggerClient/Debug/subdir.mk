################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../DataStore.cpp \
../MySQLLoggerClient.cpp 

OBJS += \
./DataStore.o \
./MySQLLoggerClient.o 

CPP_DEPS += \
./DataStore.d \
./MySQLLoggerClient.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/dbrown/workspace/git/RedpineTradingPost/gcc/DataTypes" -I"/home/dbrown/workspace/git/RedpineTradingPost/gcc/MySQLLayer" -I"/home/dbrown/workspace/git/RedpineTradingPost/gcc/CornerTurn" -I/usr/local/include/activemq-cpp-3.8.1 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


