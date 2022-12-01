################################################################################
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Hardware/CLK/clk.c 

OBJS += \
./Hardware/CLK/clk.o 

C_DEPS += \
./Hardware/CLK/clk.d 


# Each subdirectory must supply rules for building sources it contributes
Hardware/CLK/%.o: ../Hardware/CLK/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"I:\CH32V系列RISC-VMCU开发实战（开发入门)\第四次课\RCC-HSI_HSE\Debug" -I"I:\CH32V系列RISC-VMCU开发实战（开发入门)\第四次课\RCC-HSI_HSE\Hardware\CLK" -I"I:\CH32V系列RISC-VMCU开发实战（开发入门)\第四次课\RCC-HSI_HSE\Core" -I"I:\CH32V系列RISC-VMCU开发实战（开发入门)\第四次课\RCC-HSI_HSE\User" -I"I:\CH32V系列RISC-VMCU开发实战（开发入门)\第四次课\RCC-HSI_HSE\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

