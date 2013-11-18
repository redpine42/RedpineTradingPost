################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../DataTypes/CandleData.cpp \
../DataTypes/L1Data.cpp \
../DataTypes/L2Data.cpp \
../DataTypes/OrderBook.cpp \
../DataTypes/PurchaseData.cpp \
../DataTypes/TimeSalesData.cpp 

OBJS += \
./DataTypes/CandleData.o \
./DataTypes/L1Data.o \
./DataTypes/L2Data.o \
./DataTypes/OrderBook.o \
./DataTypes/PurchaseData.o \
./DataTypes/TimeSalesData.o 

CPP_DEPS += \
./DataTypes/CandleData.d \
./DataTypes/L1Data.d \
./DataTypes/L2Data.d \
./DataTypes/OrderBook.d \
./DataTypes/PurchaseData.d \
./DataTypes/TimeSalesData.d 


# Each subdirectory must supply rules for building sources it contributes
DataTypes/%.o: ../DataTypes/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


