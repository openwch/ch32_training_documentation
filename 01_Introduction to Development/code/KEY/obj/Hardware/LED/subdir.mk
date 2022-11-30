################################################################################
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Hardware/LED/led.c 

OBJS += \
./Hardware/LED/led.o 

C_DEPS += \
./Hardware/LED/led.d 


# Each subdirectory must supply rules for building sources it contributes
Hardware/LED/%.o: ../Hardware/LED/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"C:\Users\OWNER\Desktop\KEY\Debug" -I"C:\Users\OWNER\Desktop\KEY\Hardware\KEY" -I"C:\Users\OWNER\Desktop\KEY\Hardware\LED" -I"C:\Users\OWNER\Desktop\KEY\Core" -I"C:\Users\OWNER\Desktop\KEY\User" -I"C:\Users\OWNER\Desktop\KEY\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

