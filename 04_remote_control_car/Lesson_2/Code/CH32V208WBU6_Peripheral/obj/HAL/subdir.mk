################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/KEY.c \
../HAL/LED.c \
../HAL/MCU.c \
../HAL/RTC.c \
../HAL/SLEEP.c 

OBJS += \
./HAL/KEY.o \
./HAL/LED.o \
./HAL/MCU.o \
./HAL/RTC.o \
./HAL/SLEEP.o 

C_DEPS += \
./HAL/KEY.d \
./HAL/LED.d \
./HAL/MCU.d \
./HAL/RTC.d \
./HAL/SLEEP.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/%.o: ../HAL/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -DCH32V20x_D8W -I"D:\GoingOn\桌面\课程教学\教学文件\课件\Lesson.2\源代码\CH32V208WBU6_Peripheral\APP\include" -I"D:\GoingOn\桌面\课程教学\教学文件\课件\Lesson.2\源代码\CH32V208WBU6_Peripheral\HAL\include" -I"D:\GoingOn\桌面\课程教学\教学文件\课件\Lesson.2\源代码\CH32V208WBU6_Peripheral\LIB" -I"D:\GoingOn\桌面\课程教学\教学文件\课件\Lesson.2\源代码\CH32V208WBU6_Peripheral\Profile\include" -I"D:\GoingOn\桌面\课程教学\教学文件\课件\Lesson.2\源代码\CH32V208WBU6_Peripheral\SRC\Core" -I"D:\GoingOn\桌面\课程教学\教学文件\课件\Lesson.2\源代码\CH32V208WBU6_Peripheral\SRC\Debug" -I"D:\GoingOn\桌面\课程教学\教学文件\课件\Lesson.2\源代码\CH32V208WBU6_Peripheral\SRC\Peripheral\inc" -I"D:\GoingOn\桌面\课程教学\教学文件\课件\Lesson.2\源代码\CH32V208WBU6_Peripheral\SRC\Startup" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

