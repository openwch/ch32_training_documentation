################################################################################
# MRS Version: {"version":"1.8.4","date":"2023/02/15"}
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../APP/ch32v20x_it.c \
../APP/peripheral.c \
../APP/peripheral_main.c \
../APP/system_ch32v20x.c 

OBJS += \
./APP/ch32v20x_it.o \
./APP/peripheral.o \
./APP/peripheral_main.o \
./APP/system_ch32v20x.o 

C_DEPS += \
./APP/ch32v20x_it.d \
./APP/peripheral.d \
./APP/peripheral_main.d \
./APP/system_ch32v20x.d 


# Each subdirectory must supply rules for building sources it contributes
APP/%.o: ../APP/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -DCH32V20x_D8W -I"C:\Users\OWNER\Desktop\新建文件夹\CH32V208WBU6_Template\APP\include" -I"C:\Users\OWNER\Desktop\新建文件夹\CH32V208WBU6_Template\HAL\include" -I"C:\Users\OWNER\Desktop\新建文件夹\CH32V208WBU6_Template\LIB" -I"C:\Users\OWNER\Desktop\新建文件夹\CH32V208WBU6_Template\Profile\include" -I"C:\Users\OWNER\Desktop\新建文件夹\CH32V208WBU6_Template\SRC\Core" -I"C:\Users\OWNER\Desktop\新建文件夹\CH32V208WBU6_Template\SRC\Debug" -I"C:\Users\OWNER\Desktop\新建文件夹\CH32V208WBU6_Template\SRC\Peripheral\inc" -I"C:\Users\OWNER\Desktop\新建文件夹\CH32V208WBU6_Template\SRC\Startup" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

