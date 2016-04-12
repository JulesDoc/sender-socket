################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/udpsender.cpp 

OBJS += \
./src/udpsender.o 

CPP_DEPS += \
./src/udpsender.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X_ -I/home/jcalvopi/work/tbb44_20160316oss/include -I/home/jcalvopi/work/tbb44_20160128oss/include -O0 -g3 -Wall -c -fpermissive -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


