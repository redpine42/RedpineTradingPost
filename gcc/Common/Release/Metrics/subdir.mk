################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Metrics/ADXMetric.cpp \
../Metrics/ATRMetric.cpp \
../Metrics/BBandsHA.cpp \
../Metrics/CCIMetric.cpp \
../Metrics/CandlePatternMetric.cpp \
../Metrics/ConsistentMove.cpp \
../Metrics/CorrSlopeMetric.cpp \
../Metrics/CorrelationMetric.cpp \
../Metrics/DivMetric.cpp \
../Metrics/EMAMetric.cpp \
../Metrics/Hilbert.cpp \
../Metrics/LaguerreMetric.cpp \
../Metrics/MACDMetric.cpp \
../Metrics/MVAMetric.cpp \
../Metrics/MaxMin.cpp \
../Metrics/MaxMinHA.cpp \
../Metrics/MeanMetric.cpp \
../Metrics/MetricsCache.cpp \
../Metrics/MinusDIMetric.cpp \
../Metrics/MomentumMetric.cpp \
../Metrics/PSARMetric.cpp \
../Metrics/PlusDIMetric.cpp \
../Metrics/ROCMetric.cpp \
../Metrics/RSIMetric.cpp \
../Metrics/RandNum.cpp \
../Metrics/STDMetric.cpp \
../Metrics/STOCHMetric.cpp \
../Metrics/STOCHRSIMetric.cpp \
../Metrics/SlopeMetric.cpp \
../Metrics/SubMetric.cpp \
../Metrics/TrendDesc.cpp \
../Metrics/Ultosc.cpp \
../Metrics/VarMetric.cpp \
../Metrics/WilliamsRMetric.cpp 

OBJS += \
./Metrics/ADXMetric.o \
./Metrics/ATRMetric.o \
./Metrics/BBandsHA.o \
./Metrics/CCIMetric.o \
./Metrics/CandlePatternMetric.o \
./Metrics/ConsistentMove.o \
./Metrics/CorrSlopeMetric.o \
./Metrics/CorrelationMetric.o \
./Metrics/DivMetric.o \
./Metrics/EMAMetric.o \
./Metrics/Hilbert.o \
./Metrics/LaguerreMetric.o \
./Metrics/MACDMetric.o \
./Metrics/MVAMetric.o \
./Metrics/MaxMin.o \
./Metrics/MaxMinHA.o \
./Metrics/MeanMetric.o \
./Metrics/MetricsCache.o \
./Metrics/MinusDIMetric.o \
./Metrics/MomentumMetric.o \
./Metrics/PSARMetric.o \
./Metrics/PlusDIMetric.o \
./Metrics/ROCMetric.o \
./Metrics/RSIMetric.o \
./Metrics/RandNum.o \
./Metrics/STDMetric.o \
./Metrics/STOCHMetric.o \
./Metrics/STOCHRSIMetric.o \
./Metrics/SlopeMetric.o \
./Metrics/SubMetric.o \
./Metrics/TrendDesc.o \
./Metrics/Ultosc.o \
./Metrics/VarMetric.o \
./Metrics/WilliamsRMetric.o 

CPP_DEPS += \
./Metrics/ADXMetric.d \
./Metrics/ATRMetric.d \
./Metrics/BBandsHA.d \
./Metrics/CCIMetric.d \
./Metrics/CandlePatternMetric.d \
./Metrics/ConsistentMove.d \
./Metrics/CorrSlopeMetric.d \
./Metrics/CorrelationMetric.d \
./Metrics/DivMetric.d \
./Metrics/EMAMetric.d \
./Metrics/Hilbert.d \
./Metrics/LaguerreMetric.d \
./Metrics/MACDMetric.d \
./Metrics/MVAMetric.d \
./Metrics/MaxMin.d \
./Metrics/MaxMinHA.d \
./Metrics/MeanMetric.d \
./Metrics/MetricsCache.d \
./Metrics/MinusDIMetric.d \
./Metrics/MomentumMetric.d \
./Metrics/PSARMetric.d \
./Metrics/PlusDIMetric.d \
./Metrics/ROCMetric.d \
./Metrics/RSIMetric.d \
./Metrics/RandNum.d \
./Metrics/STDMetric.d \
./Metrics/STOCHMetric.d \
./Metrics/STOCHRSIMetric.d \
./Metrics/SlopeMetric.d \
./Metrics/SubMetric.d \
./Metrics/TrendDesc.d \
./Metrics/Ultosc.d \
./Metrics/VarMetric.d \
./Metrics/WilliamsRMetric.d 


# Each subdirectory must supply rules for building sources it contributes
Metrics/%.o: ../Metrics/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


