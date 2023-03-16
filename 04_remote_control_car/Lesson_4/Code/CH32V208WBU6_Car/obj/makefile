################################################################################
# MRS Version: {"version":"1.8.4","date":"2023/02/15"}
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
-include Profile/subdir.mk
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
CH32V208WBU6_Car.hex \

SECONDARY_LIST += \
CH32V208WBU6_Car.lst \

SECONDARY_SIZE += \
CH32V208WBU6_Car.siz \


# All Target
all: CH32V208WBU6_Car.elf secondary-outputs

# Tool invocations
CH32V208WBU6_Car.elf: $(OBJS) $(USER_OBJS)
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -T "C:\Users\OWNER\Desktop\新建文件夹\Lesson.4\CH32V208WBU6_Car\HAL\Link.ld" -nostartfiles -Xlinker --gc-sections -L"C:\Users\OWNER\Desktop\新建文件夹\Lesson.4\CH32V208WBU6_Car\LIB" -Xlinker --print-memory-usage -Wl,-Map,"CH32V208WBU6_Car.map" --specs=nano.specs --specs=nosys.specs -o "CH32V208WBU6_Car.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@	@
CH32V208WBU6_Car.hex: CH32V208WBU6_Car.elf
	@	riscv-none-embed-objcopy -O ihex "CH32V208WBU6_Car.elf"  "CH32V208WBU6_Car.hex"
	@	@
CH32V208WBU6_Car.lst: CH32V208WBU6_Car.elf
	@	riscv-none-embed-objdump --all-headers --demangle --disassemble -M xw "CH32V208WBU6_Car.elf" > "CH32V208WBU6_Car.lst"
	@	@
CH32V208WBU6_Car.siz: CH32V208WBU6_Car.elf
	@	riscv-none-embed-size --format=berkeley "CH32V208WBU6_Car.elf"
	@	@
# Other Targets
clean:
	-$(RM) $(ASM_UPPER_DEPS)$(OBJS)$(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_DEPS)$(S_UPPER_DEPS)$(C_DEPS) CH32V208WBU6_Car.elf
	-@
secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
