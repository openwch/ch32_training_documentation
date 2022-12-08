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
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"D:\Desktop\Â¼Òôº°»°Æ÷\code\v307_dac_triangle\Debug" -I"D:\Desktop\Â¼Òôº°»°Æ÷\code\v307_dac_triangle\Core" -I"D:\Desktop\Â¼Òôº°»°Æ÷\code\v307_dac_triangle\User" -I"D:\Desktop\Â¼Òôº°»°Æ÷\code\v307_dac_triangle\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

