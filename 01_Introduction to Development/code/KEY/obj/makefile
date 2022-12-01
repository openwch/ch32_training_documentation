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
-include Hardware/LED/subdir.mk
-include Hardware/KEY/subdir.mk
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
KEY.hex \

SECONDARY_LIST += \
KEY.lst \

SECONDARY_SIZE += \
KEY.siz \


# 所有目标
all: KEY.elf secondary-outputs

# 工具调用
KEY.elf: $(OBJS) $(USER_OBJS)
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -T "C:\Users\OWNER\Desktop\KEY\Ld\Link.ld" -nostartfiles -Xlinker --gc-sections -Wl,-Map,"KEY.map" --specs=nano.specs --specs=nosys.specs -o "KEY.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@	@
KEY.hex: KEY.elf
	@	riscv-none-embed-objcopy -O ihex "KEY.elf"  "KEY.hex"
	@	@
KEY.lst: KEY.elf
	@	riscv-none-embed-objdump --all-headers --demangle --disassemble -M xw "KEY.elf" > "KEY.lst"
	@	@
KEY.siz: KEY.elf
	@	riscv-none-embed-size --format=berkeley "KEY.elf"
	@	@
# 其他目标
clean:
	-$(RM) $(ASM_UPPER_DEPS)$(OBJS)$(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_DEPS)$(S_UPPER_DEPS)$(C_DEPS) KEY.elf
	-@
secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
