################################################################################
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Hardware/USART/usart.c 

OBJS += \
./Hardware/USART/usart.o 

C_DEPS += \
./Hardware/USART/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Hardware/USART/%.o: ../Hardware/USART/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"C:\Users\OWNER\Desktop\USART\Debug" -I"C:\Users\OWNER\Desktop\USART\Hardware\USART" -I"C:\Users\OWNER\Desktop\USART\Core" -I"C:\Users\OWNER\Desktop\USART\User" -I"C:\Users\OWNER\Desktop\USART\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

