################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User/ch32v30x_it.c \
../User/main.c \
../User/system_ch32v30x.c 

OBJS += \
./User/ch32v30x_it.o \
./User/main.o \
./User/system_ch32v30x.o 

C_DEPS += \
./User/ch32v30x_it.d \
./User/main.d \
./User/system_ch32v30x.d 


# Each subdirectory must supply rules for building sources it contributes
User/%.o: ../User/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O3 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"E:\work\branding\RISC-V推广\视频课程\CH32V系列RISC-V MCU开发实战\录音喊话器\code\loud_speaker_pro\Debug" -I"E:\work\branding\RISC-V推广\视频课程\CH32V系列RISC-V MCU开发实战\录音喊话器\code\loud_speaker_pro\User\app" -I"E:\work\branding\RISC-V推广\视频课程\CH32V系列RISC-V MCU开发实战\录音喊话器\code\loud_speaker_pro\Core" -I"E:\work\branding\RISC-V推广\视频课程\CH32V系列RISC-V MCU开发实战\录音喊话器\code\loud_speaker_pro\User" -I"E:\work\branding\RISC-V推广\视频课程\CH32V系列RISC-V MCU开发实战\录音喊话器\code\loud_speaker_pro\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

