################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SRC/Debug/debug.c 

OBJS += \
./SRC/Debug/debug.o 

C_DEPS += \
./SRC/Debug/debug.d 


# Each subdirectory must supply rules for building sources it contributes
SRC/Debug/%.o: ../SRC/Debug/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -DCH32V20x_D8W -I"D:\GoingOn\桌面\课程教学\教学文件\课件\Lesson.2\源代码\CH32V208WBU6_Peripheral\APP\include" -I"D:\GoingOn\桌面\课程教学\教学文件\课件\Lesson.2\源代码\CH32V208WBU6_Peripheral\HAL\include" -I"D:\GoingOn\桌面\课程教学\教学文件\课件\Lesson.2\源代码\CH32V208WBU6_Peripheral\LIB" -I"D:\GoingOn\桌面\课程教学\教学文件\课件\Lesson.2\源代码\CH32V208WBU6_Peripheral\Profile\include" -I"D:\GoingOn\桌面\课程教学\教学文件\课件\Lesson.2\源代码\CH32V208WBU6_Peripheral\SRC\Core" -I"D:\GoingOn\桌面\课程教学\教学文件\课件\Lesson.2\源代码\CH32V208WBU6_Peripheral\SRC\Debug" -I"D:\GoingOn\桌面\课程教学\教学文件\课件\Lesson.2\源代码\CH32V208WBU6_Peripheral\SRC\Peripheral\inc" -I"D:\GoingOn\桌面\课程教学\教学文件\课件\Lesson.2\源代码\CH32V208WBU6_Peripheral\SRC\Startup" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

