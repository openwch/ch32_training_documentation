################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Debug/debug.c 

OBJS += \
./Debug/debug.o 

C_DEPS += \
./Debug/debug.d 


# Each subdirectory must supply rules for building sources it contributes
Debug/%.o: ../Debug/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"D:\Desktop\Â¼Òôº°»°Æ÷\code\v307_adc_multi_channel\Debug" -I"D:\Desktop\Â¼Òôº°»°Æ÷\code\v307_adc_multi_channel\Core" -I"D:\Desktop\Â¼Òôº°»°Æ÷\code\v307_adc_multi_channel\User" -I"D:\Desktop\Â¼Òôº°»°Æ÷\code\v307_adc_multi_channel\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

