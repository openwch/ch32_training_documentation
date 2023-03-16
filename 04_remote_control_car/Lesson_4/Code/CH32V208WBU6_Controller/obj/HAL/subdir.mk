################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/JOYSTICK.c \
../HAL/KEY.c \
../HAL/LED.c \
../HAL/MCU.c \
../HAL/MY_LED.c \
../HAL/RTC.c \
../HAL/SLEEP.c 

OBJS += \
./HAL/JOYSTICK.o \
./HAL/KEY.o \
./HAL/LED.o \
./HAL/MCU.o \
./HAL/MY_LED.o \
./HAL/RTC.o \
./HAL/SLEEP.o 

C_DEPS += \
./HAL/JOYSTICK.d \
./HAL/KEY.d \
./HAL/LED.d \
./HAL/MCU.d \
./HAL/MY_LED.d \
./HAL/RTC.d \
./HAL/SLEEP.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/%.o: ../HAL/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -DCH32V20x_D8W -DCLK_OSC32K=0 -I"C:\Users\OWNER\Desktop\课程教学\教学文件\课件\Lesson.4\源代码\CH32V208WBU6_Controller\APP\include" -I"C:\Users\OWNER\Desktop\课程教学\教学文件\课件\Lesson.4\源代码\CH32V208WBU6_Controller\HAL\include" -I"C:\Users\OWNER\Desktop\课程教学\教学文件\课件\Lesson.4\源代码\CH32V208WBU6_Controller\LIB" -I"C:\Users\OWNER\Desktop\课程教学\教学文件\课件\Lesson.4\源代码\CH32V208WBU6_Controller\Profile\include" -I"C:\Users\OWNER\Desktop\课程教学\教学文件\课件\Lesson.4\源代码\CH32V208WBU6_Controller\SRC\Core" -I"C:\Users\OWNER\Desktop\课程教学\教学文件\课件\Lesson.4\源代码\CH32V208WBU6_Controller\SRC\Debug" -I"C:\Users\OWNER\Desktop\课程教学\教学文件\课件\Lesson.4\源代码\CH32V208WBU6_Controller\SRC\Peripheral\inc" -I"C:\Users\OWNER\Desktop\课程教学\教学文件\课件\Lesson.4\源代码\CH32V208WBU6_Controller\SRC\Startup" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

