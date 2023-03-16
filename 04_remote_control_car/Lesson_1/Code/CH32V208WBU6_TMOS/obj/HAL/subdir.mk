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
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -DCH32V20x_D8W -I"C:\Users\OWNER\Desktop\课程教学\教学文件\课件\Lesson.1\源代码\CH32V208WBU6_TMOS\APP\include" -I"C:\Users\OWNER\Desktop\课程教学\教学文件\课件\Lesson.1\源代码\CH32V208WBU6_TMOS\HAL\include" -I"C:\Users\OWNER\Desktop\课程教学\教学文件\课件\Lesson.1\源代码\CH32V208WBU6_TMOS\LIB" -I"C:\Users\OWNER\Desktop\课程教学\教学文件\课件\Lesson.1\源代码\CH32V208WBU6_TMOS\Profile\include" -I"C:\Users\OWNER\Desktop\课程教学\教学文件\课件\Lesson.1\源代码\CH32V208WBU6_TMOS\SRC\Core" -I"C:\Users\OWNER\Desktop\课程教学\教学文件\课件\Lesson.1\源代码\CH32V208WBU6_TMOS\SRC\Debug" -I"C:\Users\OWNER\Desktop\课程教学\教学文件\课件\Lesson.1\源代码\CH32V208WBU6_TMOS\SRC\Peripheral\inc" -I"C:\Users\OWNER\Desktop\课程教学\教学文件\课件\Lesson.1\源代码\CH32V208WBU6_TMOS\SRC\Startup" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

