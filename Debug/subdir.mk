################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ADC.c \
../DcMotor.c \
../GPIO.c \
../LCD.c \
../Mini_Project3.c \
../PWM.c \
../lm35_sensor.c 

OBJS += \
./ADC.o \
./DcMotor.o \
./GPIO.o \
./LCD.o \
./Mini_Project3.o \
./PWM.o \
./lm35_sensor.o 

C_DEPS += \
./ADC.d \
./DcMotor.d \
./GPIO.d \
./LCD.d \
./Mini_Project3.d \
./PWM.d \
./lm35_sensor.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


