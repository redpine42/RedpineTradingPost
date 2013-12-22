################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../AccountManager.cpp \
../CHistSink.cpp \
../COrderSink.cpp \
../CandleManager.cpp \
../ComSink.cpp \
../HistImpl.cpp \
../MBQuotes_i.cpp \
../OrderManager.cpp \
../QuotesManager.cpp \
../TradeManager.cpp 

OBJS += \
./AccountManager.o \
./CHistSink.o \
./COrderSink.o \
./CandleManager.o \
./ComSink.o \
./HistImpl.o \
./MBQuotes_i.o \
./OrderManager.o \
./QuotesManager.o \
./TradeManager.o 

CPP_DEPS += \
./AccountManager.d \
./CHistSink.d \
./COrderSink.d \
./CandleManager.d \
./ComSink.d \
./HistImpl.d \
./MBQuotes_i.d \
./OrderManager.d \
./QuotesManager.d \
./TradeManager.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/dbrown/workspace/git/RedpineTradingPost/gcc/DataTypes" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


