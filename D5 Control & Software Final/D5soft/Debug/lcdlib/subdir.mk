################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lcdlib/._font.c \
../lcdlib/._ili934x.c \
../lcdlib/._lcd.c \
../lcdlib/font.c \
../lcdlib/ili934x.c \
../lcdlib/lcd.c 

OBJS += \
./lcdlib/._font.o \
./lcdlib/._ili934x.o \
./lcdlib/._lcd.o \
./lcdlib/font.o \
./lcdlib/ili934x.o \
./lcdlib/lcd.o 

C_DEPS += \
./lcdlib/._font.d \
./lcdlib/._ili934x.d \
./lcdlib/._lcd.d \
./lcdlib/font.d \
./lcdlib/ili934x.d \
./lcdlib/lcd.d 


# Each subdirectory must supply rules for building sources it contributes
lcdlib/%.o: ../lcdlib/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


