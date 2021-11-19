################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Lib/perfCont.c" \

C_SRCS += \
../Lib/perfCont.c \

OBJS += \
./Lib/perfCont.o \

C_DEPS += \
./Lib/perfCont.d \

OBJS_QUOTED += \
"./Lib/perfCont.o" \

C_DEPS_QUOTED += \
"./Lib/perfCont.d" \

OBJS_OS_FORMAT += \
./Lib/perfCont.o \


# Each subdirectory must supply rules for building sources it contributes
Lib/perfCont.o: ../Lib/perfCont.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Lib/perfCont.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Lib/perfCont.o"
	@echo 'Finished building: $<'
	@echo ' '


