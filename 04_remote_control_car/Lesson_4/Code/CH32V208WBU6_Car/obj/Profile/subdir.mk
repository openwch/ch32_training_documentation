################################################################################
# MRS Version: {"version":"1.8.4","date":"2023/02/15"}
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Profile/devinfoservice.c \
../Profile/gattprofile.c 

OBJS += \
./Profile/devinfoservice.o \
./Profile/gattprofile.o 

C_DEPS += \
./Profile/devinfoservice.d \
./Profile/gattprofile.d 


# Each subdirectory must supply rules for building sources it contributes
Profile/%.o: ../Profile/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -DCH32V20x_D8W -I"C:\Users\OWNER\Desktop\新建文件夹\Lesson.4\CH32V208WBU6_Car\APP\include" -I"C:\Users\OWNER\Desktop\新建文件夹\Lesson.4\CH32V208WBU6_Car\HAL\include" -I"C:\Users\OWNER\Desktop\新建文件夹\Lesson.4\CH32V208WBU6_Car\LIB" -I"C:\Users\OWNER\Desktop\新建文件夹\Lesson.4\CH32V208WBU6_Car\Profile\include" -I"C:\Users\OWNER\Desktop\新建文件夹\Lesson.4\CH32V208WBU6_Car\SRC\Core" -I"C:\Users\OWNER\Desktop\新建文件夹\Lesson.4\CH32V208WBU6_Car\SRC\Debug" -I"C:\Users\OWNER\Desktop\新建文件夹\Lesson.4\CH32V208WBU6_Car\SRC\Peripheral\inc" -I"C:\Users\OWNER\Desktop\新建文件夹\Lesson.4\CH32V208WBU6_Car\SRC\Startup" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

