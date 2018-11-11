################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../EngineLib/tinystr.cpp \
../EngineLib/tinyxml.cpp \
../EngineLib/tinyxmlerror.cpp \
../EngineLib/tinyxmlparser.cpp 

OBJS += \
./EngineLib/tinystr.o \
./EngineLib/tinyxml.o \
./EngineLib/tinyxmlerror.o \
./EngineLib/tinyxmlparser.o 

CPP_DEPS += \
./EngineLib/tinystr.d \
./EngineLib/tinyxml.d \
./EngineLib/tinyxmlerror.d \
./EngineLib/tinyxmlparser.d 


# Each subdirectory must supply rules for building sources it contributes
EngineLib/%.o: ../EngineLib/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I/usr/local/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


