################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../liblcd/lcdlib/._font.c \
../liblcd/lcdlib/._ili934x.c \
../liblcd/lcdlib/._lcd.c \
../liblcd/lcdlib/font.c \
../liblcd/lcdlib/ili934x.c \
../liblcd/lcdlib/lcd.c 

OBJS += \
./liblcd/lcdlib/._font.o \
./liblcd/lcdlib/._ili934x.o \
./liblcd/lcdlib/._lcd.o \
./liblcd/lcdlib/font.o \
./liblcd/lcdlib/ili934x.o \
./liblcd/lcdlib/lcd.o 

C_DEPS += \
./liblcd/lcdlib/._font.d \
./liblcd/lcdlib/._ili934x.d \
./liblcd/lcdlib/._lcd.d \
./liblcd/lcdlib/font.d \
./liblcd/lcdlib/ili934x.d \
./liblcd/lcdlib/lcd.d 


# Each subdirectory must supply rules for building sources it contributes
liblcd/lcdlib/%.o: ../liblcd/lcdlib/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


