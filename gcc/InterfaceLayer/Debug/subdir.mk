################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CandleHistMaker.cpp \
../MBTInterfaceLayer.cpp \
../OrderMessageHandler.cpp 

OBJS += \
./CandleHistMaker.o \
./MBTInterfaceLayer.o \
./OrderMessageHandler.o 

CPP_DEPS += \
./CandleHistMaker.d \
./MBTInterfaceLayer.d \
./OrderMessageHandler.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/dbrown/workspace/git/RedpineTradingPost/gcc/InterfaceWrappers" -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


