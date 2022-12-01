################################################################################
# 自动生成的文件。不要编辑！
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include User/subdir.mk
-include Startup/subdir.mk
-include Peripheral/src/subdir.mk
-include Hardware/CLK/subdir.mk
-include Debug/subdir.mk
-include Core/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
RCC-HSI_HSE.hex \

SECONDARY_LIST += \
RCC-HSI_HSE.lst \

SECONDARY_SIZE += \
RCC-HSI_HSE.siz \


# 所有目标
all: RCC-HSI_HSE.elf secondary-outputs

# 工具调用
RCC-HSI_HSE.elf: $(OBJS) $(USER_OBJS)
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -T "I:\CH32V系列RISC-VMCU开发实战（开发入门)\第四次课\RCC-HSI_HSE\Ld\Link.ld" -nostartfiles -Xlinker --gc-sections -Wl,-Map,"RCC-HSI_HSE.map" --specs=nano.specs --specs=nosys.specs -o "RCC-HSI_HSE.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@	@
RCC-HSI_HSE.hex: RCC-HSI_HSE.elf
	@	riscv-none-embed-objcopy -O ihex "RCC-HSI_HSE.elf"  "RCC-HSI_HSE.hex"
	@	@
RCC-HSI_HSE.lst: RCC-HSI_HSE.elf
	@	riscv-none-embed-objdump --all-headers --demangle --disassemble -M xw "RCC-HSI_HSE.elf" > "RCC-HSI_HSE.lst"
	@	@
RCC-HSI_HSE.siz: RCC-HSI_HSE.elf
	@	riscv-none-embed-size --format=berkeley "RCC-HSI_HSE.elf"
	@	@
# 其他目标
clean:
	-$(RM) $(ASM_UPPER_DEPS)$(OBJS)$(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_DEPS)$(S_UPPER_DEPS)$(C_DEPS) RCC-HSI_HSE.elf
	-@
secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
