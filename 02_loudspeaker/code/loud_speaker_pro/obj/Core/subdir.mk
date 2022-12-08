################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/core_riscv.c 

OBJS += \
./Core/core_riscv.o 

C_DEPS += \
./Core/core_riscv.d 


# Each subdirectory must supply rules for building sources it contributes
Core/%.o: ../Core/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O3 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"E:\work\branding\RISC-V推广\视频课程\CH32V系列RISC-V MCU开发实战\录音喊话器\code\loud_speaker_pro\Debug" -I"E:\work\branding\RISC-V推广\视频课程\CH32V系列RISC-V MCU开发实战\录音喊话器\code\loud_speaker_pro\User\app" -I"E:\work\branding\RISC-V推广\视频课程\CH32V系列RISC-V MCU开发实战\录音喊话器\code\loud_speaker_pro\Core" -I"E:\work\branding\RISC-V推广\视频课程\CH32V系列RISC-V MCU开发实战\录音喊话器\code\loud_speaker_pro\User" -I"E:\work\branding\RISC-V推广\视频课程\CH32V系列RISC-V MCU开发实战\录音喊话器\code\loud_speaker_pro\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

