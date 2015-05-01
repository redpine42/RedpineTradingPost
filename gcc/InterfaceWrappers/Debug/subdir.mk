################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../AccountManager.cpp \
../CandleManager.cpp \
../HistImpl.cpp \
../MBQuotes_i.cpp \
../OrderManager.cpp \
../QuotesManager.cpp \
../TradeManager.cpp 

OBJS += \
./AccountManager.o \
./CandleManager.o \
./HistImpl.o \
./MBQuotes_i.o \
./OrderManager.o \
./QuotesManager.o \
./TradeManager.o 

CPP_DEPS += \
./AccountManager.d \
./CandleManager.d \
./HistImpl.d \
./MBQuotes_i.d \
./OrderManager.d \
./QuotesManager.d \
./TradeManager.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/dbrown/workspace/git/RedpineTradingPost/gcc/InterfaceStubs" -I"/home/dbrown/workspace/git/RedpineTradingPost/gcc/DataTypes" -I"/home/dbrown/workspace/git/RedpineTradingPost/gcc/CornerTurn" -I/usr/include/activemq-cpp-3.8.2 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


