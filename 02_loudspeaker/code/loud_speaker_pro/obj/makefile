################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include User/app/subdir.mk
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
loud_speaker_pro.bin \

SECONDARY_LIST += \
loud_speaker_pro.lst \

SECONDARY_SIZE += \
loud_speaker_pro.siz \


# All Target
all: loud_speaker_pro.elf secondary-outputs

# Tool invocations
loud_speaker_pro.elf: $(OBJS) $(USER_OBJS)
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O3 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -T "E:\work\branding\RISC-V推广\视频课程\CH32V系列RISC-V MCU开发实战\录音喊话器\code\loud_speaker_pro\Ld\Link.ld" -nostartfiles -Xlinker --gc-sections -Wl,-Map,"loud_speaker_pro.map" --specs=nano.specs -u _printf_float --specs=nosys.specs -o "loud_speaker_pro.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@	@
loud_speaker_pro.bin: loud_speaker_pro.elf
	@	riscv-none-embed-objcopy -O binary "loud_speaker_pro.elf"  "loud_speaker_pro.bin"
	@	@
loud_speaker_pro.lst: loud_speaker_pro.elf
	@	riscv-none-embed-objdump --source --all-headers --demangle --disassemble -M xw "loud_speaker_pro.elf" > "loud_speaker_pro.lst"
	@	@
loud_speaker_pro.siz: loud_speaker_pro.elf
	@	riscv-none-embed-size --format=berkeley "loud_speaker_pro.elf"
	@	@
# Other Targets
clean:
	-$(RM) $(ASM_UPPER_DEPS)$(OBJS)$(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_DEPS)$(S_UPPER_DEPS)$(C_DEPS) loud_speaker_pro.elf
	-@
secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
