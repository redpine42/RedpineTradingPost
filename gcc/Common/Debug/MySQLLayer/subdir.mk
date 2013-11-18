################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../MySQLLayer/CandleDataHelper.cpp \
../MySQLLayer/CandleDataManipulation.cpp \
../MySQLLayer/CursorData.cpp \
../MySQLLayer/L1DataManipulation.cpp \
../MySQLLayer/L2DataManipulation.cpp \
../MySQLLayer/MySQLLayer.cpp \
../MySQLLayer/TimeSalesDataManipulation.cpp 

OBJS += \
./MySQLLayer/CandleDataHelper.o \
./MySQLLayer/CandleDataManipulation.o \
./MySQLLayer/CursorData.o \
./MySQLLayer/L1DataManipulation.o \
./MySQLLayer/L2DataManipulation.o \
./MySQLLayer/MySQLLayer.o \
./MySQLLayer/TimeSalesDataManipulation.o 

CPP_DEPS += \
./MySQLLayer/CandleDataHelper.d \
./MySQLLayer/CandleDataManipulation.d \
./MySQLLayer/CursorData.d \
./MySQLLayer/L1DataManipulation.d \
./MySQLLayer/L2DataManipulation.d \
./MySQLLayer/MySQLLayer.d \
./MySQLLayer/TimeSalesDataManipulation.d 


# Each subdirectory must supply rules for building sources it contributes
MySQLLayer/%.o: ../MySQLLayer/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


