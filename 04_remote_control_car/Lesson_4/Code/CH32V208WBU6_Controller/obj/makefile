################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include SRC/Startup/subdir.mk
-include SRC/Peripheral/src/subdir.mk
-include SRC/Debug/subdir.mk
-include SRC/Core/subdir.mk
-include HAL/subdir.mk
-include APP/subdir.mk
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
CH32V208WBU6_Controller.hex \

SECONDARY_LIST += \
CH32V208WBU6_Controller.lst \

SECONDARY_SIZE += \
CH32V208WBU6_Controller.siz \


# All Target
all: CH32V208WBU6_Controller.elf secondary-outputs

# Tool invocations
CH32V208WBU6_Controller.elf: $(OBJS) $(USER_OBJS)
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -T "C:\Users\OWNER\Desktop\课程教学\教学文件\课件\Lesson.4\源代码\CH32V208WBU6_Controller\HAL\Link.ld" -nostartfiles -Xlinker --gc-sections -L"C:\Users\OWNER\Desktop\课程教学\教学文件\课件\Lesson.4\源代码\CH32V208WBU6_Controller\LIB" -Xlinker --print-memory-usage -Wl,-Map,"CH32V208WBU6_Controller.map" --specs=nano.specs --specs=nosys.specs -o "CH32V208WBU6_Controller.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@	@
CH32V208WBU6_Controller.hex: CH32V208WBU6_Controller.elf
	@	riscv-none-embed-objcopy -O ihex "CH32V208WBU6_Controller.elf"  "CH32V208WBU6_Controller.hex"
	@	@
CH32V208WBU6_Controller.lst: CH32V208WBU6_Controller.elf
	@	riscv-none-embed-objdump --all-headers --demangle --disassemble -M xw "CH32V208WBU6_Controller.elf" > "CH32V208WBU6_Controller.lst"
	@	@
CH32V208WBU6_Controller.siz: CH32V208WBU6_Controller.elf
	@	riscv-none-embed-size --format=berkeley "CH32V208WBU6_Controller.elf"
	@	@
# Other Targets
clean:
	-$(RM) $(ASM_UPPER_DEPS)$(OBJS)$(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_DEPS)$(S_UPPER_DEPS)$(C_DEPS) CH32V208WBU6_Controller.elf
	-@
secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
