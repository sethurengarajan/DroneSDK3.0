################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Source/CBebopInterface.cpp \
../Source/CCommandPacket.cpp \
../Source/CNetworkInterface.cpp \
../Source/CNetworkSettings.cpp \
../Source/CVehicleInterface.cpp \
../Source/main.cpp 

OBJS += \
./Source/CBebopInterface.o \
./Source/CCommandPacket.o \
./Source/CNetworkInterface.o \
./Source/CNetworkSettings.o \
./Source/CVehicleInterface.o \
./Source/main.o 

CPP_DEPS += \
./Source/CBebopInterface.d \
./Source/CCommandPacket.d \
./Source/CNetworkInterface.d \
./Source/CNetworkSettings.d \
./Source/CVehicleInterface.d \
./Source/main.d 


# Each subdirectory must supply rules for building sources it contributes
Source/%.o: ../Source/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I../ThirdPartyLibs/ArDroneSDK3/include -I../ThirdPartyLibs/rapidjson/include -I../ThirdPartyLibs/easyloggingpp/include -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


