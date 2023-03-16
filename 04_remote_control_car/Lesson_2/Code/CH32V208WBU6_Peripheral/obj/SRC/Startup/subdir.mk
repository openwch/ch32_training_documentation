################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_UPPER_SRCS += \
../SRC/Startup/startup_ch32v20x_D8W.S 

OBJS += \
./SRC/Startup/startup_ch32v20x_D8W.o 

S_UPPER_DEPS += \
./SRC/Startup/startup_ch32v20x_D8W.d 


# Each subdirectory must supply rules for building sources it contributes
SRC/Startup/%.o: ../SRC/Startup/%.S
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

