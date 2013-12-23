################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CancelOrderConsumer.cpp \
../CandleDataConsumer.cpp \
../CornerTurnConfig.cpp \
../CreateOrderConsumer.cpp \
../L1DataConsumer.cpp \
../L2DataConsumer.cpp \
../MsgConsumer.cpp \
../MsgProducer.cpp \
../TimeSalesDataConsumer.cpp 

OBJS += \
./CancelOrderConsumer.o \
./CandleDataConsumer.o \
./CornerTurnConfig.o \
./CreateOrderConsumer.o \
./L1DataConsumer.o \
./L2DataConsumer.o \
./MsgConsumer.o \
./MsgProducer.o \
./TimeSalesDataConsumer.o 

CPP_DEPS += \
./CancelOrderConsumer.d \
./CandleDataConsumer.d \
./CornerTurnConfig.d \
./CreateOrderConsumer.d \
./L1DataConsumer.d \
./L2DataConsumer.d \
./MsgConsumer.d \
./MsgProducer.d \
./TimeSalesDataConsumer.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/dbrown/workspace/git/RedpineTradingPost/gcc/DataTypes" -I/usr/local/include/activemq-cpp-3.8.1 -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


