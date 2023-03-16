################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SRC/Core/core_riscv.c 

OBJS += \
./SRC/Core/core_riscv.o 

C_DEPS += \
./SRC/Core/core_riscv.d 


# Each subdirectory must supply rules for building sources it contributes
SRC/Core/%.o: ../SRC/Core/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -DCH32V20x_D8W -DCLK_OSC32K=0 -I"D:\GoingOn\桌面\课程教学\教学文件\课件\Lesson.3\源代码\CH32V208WBU6_Central\APP\include" -I"D:\GoingOn\桌面\课程教学\教学文件\课件\Lesson.3\源代码\CH32V208WBU6_Central\HAL\include" -I"D:\GoingOn\桌面\课程教学\教学文件\课件\Lesson.3\源代码\CH32V208WBU6_Central\LIB" -I"D:\GoingOn\桌面\课程教学\教学文件\课件\Lesson.3\源代码\CH32V208WBU6_Central\Profile\include" -I"D:\GoingOn\桌面\课程教学\教学文件\课件\Lesson.3\源代码\CH32V208WBU6_Central\SRC\Core" -I"D:\GoingOn\桌面\课程教学\教学文件\课件\Lesson.3\源代码\CH32V208WBU6_Central\SRC\Debug" -I"D:\GoingOn\桌面\课程教学\教学文件\课件\Lesson.3\源代码\CH32V208WBU6_Central\SRC\Peripheral\inc" -I"D:\GoingOn\桌面\课程教学\教学文件\课件\Lesson.3\源代码\CH32V208WBU6_Central\SRC\Startup" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

