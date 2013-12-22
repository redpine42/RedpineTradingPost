################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../L1DataEval.cpp \
../TestTriggerMain.cpp \
../TimeSalesDataEval.cpp \
../Trigger.cpp 

OBJS += \
./L1DataEval.o \
./TestTriggerMain.o \
./TimeSalesDataEval.o \
./Trigger.o 

CPP_DEPS += \
./L1DataEval.d \
./TestTriggerMain.d \
./TimeSalesDataEval.d \
./Trigger.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include/activemq-cpp-3.8.1 -I"/home/dbrown/workspace/git/RedpineTradingPost/gcc/CornerTurn" -I"/home/dbrown/workspace/git/RedpineTradingPost/gcc/DataTypes" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


