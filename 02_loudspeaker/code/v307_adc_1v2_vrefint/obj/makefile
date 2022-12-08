################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include User/subdir.mk
-include Startup/subdir.mk
-include Peripheral/src/subdir.mk
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
v307_adc_1v2_vrefint.hex \

SECONDARY_LIST += \
v307_adc_1v2_vrefint.lst \

SECONDARY_SIZE += \
v307_adc_1v2_vrefint.siz \


# All Target
all: v307_adc_1v2_vrefint.elf secondary-outputs

# Tool invocations
v307_adc_1v2_vrefint.elf: $(OBJS) $(USER_OBJS)
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -T "D:\Desktop\Â¼Òôº°»°Æ÷\code\v307_adc_1v2_vrefint\Ld\Link.ld" -nostartfiles -Xlinker --gc-sections -Wl,-Map,"v307_adc_1v2_vrefint.map" --specs=nano.specs --specs=nosys.specs  -o "v307_adc_1v2_vrefint.elf" $(OBJS) $(USER_OBJS) $(LIBS) -lprintfloat
	@	@
v307_adc_1v2_vrefint.hex: v307_adc_1v2_vrefint.elf
	@	riscv-none-embed-objcopy -O ihex "v307_adc_1v2_vrefint.elf"  "v307_adc_1v2_vrefint.hex"
	@	@
v307_adc_1v2_vrefint.lst: v307_adc_1v2_vrefint.elf
	@	riscv-none-embed-objdump --all-headers --demangle --disassemble -M xw "v307_adc_1v2_vrefint.elf" > "v307_adc_1v2_vrefint.lst"
	@	@
v307_adc_1v2_vrefint.siz: v307_adc_1v2_vrefint.elf
	@	riscv-none-embed-size --format=berkeley "v307_adc_1v2_vrefint.elf"
	@	@
# Other Targets
clean:
	-$(RM) $(ASM_UPPER_DEPS)$(OBJS)$(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_DEPS)$(S_UPPER_DEPS)$(C_DEPS) v307_adc_1v2_vrefint.elf
	-@
secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
