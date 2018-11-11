################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Engine/AccessoriesManager.cpp \
../Engine/AudioManager.cpp \
../Engine/Camera.cpp \
../Engine/Character.cpp \
../Engine/DynamicEntity.cpp \
../Engine/Engine.cpp \
../Engine/EngineMediator.cpp \
../Engine/Entity.cpp \
../Engine/Level.cpp \
../Engine/LevelManager.cpp \
../Engine/ObjectManager.cpp \
../Engine/StaticEntity.cpp 

OBJS += \
./Engine/AccessoriesManager.o \
./Engine/AudioManager.o \
./Engine/Camera.o \
./Engine/Character.o \
./Engine/DynamicEntity.o \
./Engine/Engine.o \
./Engine/EngineMediator.o \
./Engine/Entity.o \
./Engine/Level.o \
./Engine/LevelManager.o \
./Engine/ObjectManager.o \
./Engine/StaticEntity.o 

CPP_DEPS += \
./Engine/AccessoriesManager.d \
./Engine/AudioManager.d \
./Engine/Camera.d \
./Engine/Character.d \
./Engine/DynamicEntity.d \
./Engine/Engine.d \
./Engine/EngineMediator.d \
./Engine/Entity.d \
./Engine/Level.d \
./Engine/LevelManager.d \
./Engine/ObjectManager.d \
./Engine/StaticEntity.d 


# Each subdirectory must supply rules for building sources it contributes
Engine/%.o: ../Engine/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I/usr/local/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


