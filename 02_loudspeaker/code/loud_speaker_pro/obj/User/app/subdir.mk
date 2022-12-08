################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User/app/adc.c \
../User/app/dac.c \
../User/app/multi_button.c \
../User/app/my_button.c \
../User/app/opa.c 

OBJS += \
./User/app/adc.o \
./User/app/dac.o \
./User/app/multi_button.o \
./User/app/my_button.o \
./User/app/opa.o 

C_DEPS += \
./User/app/adc.d \
./User/app/dac.d \
./User/app/multi_button.d \
./User/app/my_button.d \
./User/app/opa.d 


# Each subdirectory must supply rules for building sources it contributes
User/app/%.o: ../User/app/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O3 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"E:\work\branding\RISC-V推广\视频课程\CH32V系列RISC-V MCU开发实战\录音喊话器\code\loud_speaker_pro\Debug" -I"E:\work\branding\RISC-V推广\视频课程\CH32V系列RISC-V MCU开发实战\录音喊话器\code\loud_speaker_pro\User\app" -I"E:\work\branding\RISC-V推广\视频课程\CH32V系列RISC-V MCU开发实战\录音喊话器\code\loud_speaker_pro\Core" -I"E:\work\branding\RISC-V推广\视频课程\CH32V系列RISC-V MCU开发实战\录音喊话器\code\loud_speaker_pro\User" -I"E:\work\branding\RISC-V推广\视频课程\CH32V系列RISC-V MCU开发实战\录音喊话器\code\loud_speaker_pro\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

