################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../APP/central.c \
../APP/central_main.c \
../APP/ch32v20x_it.c \
../APP/system_ch32v20x.c 

OBJS += \
./APP/central.o \
./APP/central_main.o \
./APP/ch32v20x_it.o \
./APP/system_ch32v20x.o 

C_DEPS += \
./APP/central.d \
./APP/central_main.d \
./APP/ch32v20x_it.d \
./APP/system_ch32v20x.d 


# Each subdirectory must supply rules for building sources it contributes
APP/%.o: ../APP/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -DCH32V20x_D8W -DCLK_OSC32K=0 -I"C:\Users\OWNER\Desktop\课程教学\教学文件\课件\Lesson.4\源代码\CH32V208WBU6_Controller\APP\include" -I"C:\Users\OWNER\Desktop\课程教学\教学文件\课件\Lesson.4\源代码\CH32V208WBU6_Controller\HAL\include" -I"C:\Users\OWNER\Desktop\课程教学\教学文件\课件\Lesson.4\源代码\CH32V208WBU6_Controller\LIB" -I"C:\Users\OWNER\Desktop\课程教学\教学文件\课件\Lesson.4\源代码\CH32V208WBU6_Controller\Profile\include" -I"C:\Users\OWNER\Desktop\课程教学\教学文件\课件\Lesson.4\源代码\CH32V208WBU6_Controller\SRC\Core" -I"C:\Users\OWNER\Desktop\课程教学\教学文件\课件\Lesson.4\源代码\CH32V208WBU6_Controller\SRC\Debug" -I"C:\Users\OWNER\Desktop\课程教学\教学文件\课件\Lesson.4\源代码\CH32V208WBU6_Controller\SRC\Peripheral\inc" -I"C:\Users\OWNER\Desktop\课程教学\教学文件\课件\Lesson.4\源代码\CH32V208WBU6_Controller\SRC\Startup" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

