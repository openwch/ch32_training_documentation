################################################################################
# MRS Version: {"version":"1.8.4","date":"2023/02/15"}
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SRC/Peripheral/src/ch32v20x_adc.c \
../SRC/Peripheral/src/ch32v20x_bkp.c \
../SRC/Peripheral/src/ch32v20x_can.c \
../SRC/Peripheral/src/ch32v20x_crc.c \
../SRC/Peripheral/src/ch32v20x_dbgmcu.c \
../SRC/Peripheral/src/ch32v20x_dma.c \
../SRC/Peripheral/src/ch32v20x_exti.c \
../SRC/Peripheral/src/ch32v20x_flash.c \
../SRC/Peripheral/src/ch32v20x_gpio.c \
../SRC/Peripheral/src/ch32v20x_i2c.c \
../SRC/Peripheral/src/ch32v20x_iwdg.c \
../SRC/Peripheral/src/ch32v20x_misc.c \
../SRC/Peripheral/src/ch32v20x_opa.c \
../SRC/Peripheral/src/ch32v20x_pwr.c \
../SRC/Peripheral/src/ch32v20x_rcc.c \
../SRC/Peripheral/src/ch32v20x_rtc.c \
../SRC/Peripheral/src/ch32v20x_spi.c \
../SRC/Peripheral/src/ch32v20x_tim.c \
../SRC/Peripheral/src/ch32v20x_usart.c \
../SRC/Peripheral/src/ch32v20x_wwdg.c 

OBJS += \
./SRC/Peripheral/src/ch32v20x_adc.o \
./SRC/Peripheral/src/ch32v20x_bkp.o \
./SRC/Peripheral/src/ch32v20x_can.o \
./SRC/Peripheral/src/ch32v20x_crc.o \
./SRC/Peripheral/src/ch32v20x_dbgmcu.o \
./SRC/Peripheral/src/ch32v20x_dma.o \
./SRC/Peripheral/src/ch32v20x_exti.o \
./SRC/Peripheral/src/ch32v20x_flash.o \
./SRC/Peripheral/src/ch32v20x_gpio.o \
./SRC/Peripheral/src/ch32v20x_i2c.o \
./SRC/Peripheral/src/ch32v20x_iwdg.o \
./SRC/Peripheral/src/ch32v20x_misc.o \
./SRC/Peripheral/src/ch32v20x_opa.o \
./SRC/Peripheral/src/ch32v20x_pwr.o \
./SRC/Peripheral/src/ch32v20x_rcc.o \
./SRC/Peripheral/src/ch32v20x_rtc.o \
./SRC/Peripheral/src/ch32v20x_spi.o \
./SRC/Peripheral/src/ch32v20x_tim.o \
./SRC/Peripheral/src/ch32v20x_usart.o \
./SRC/Peripheral/src/ch32v20x_wwdg.o 

C_DEPS += \
./SRC/Peripheral/src/ch32v20x_adc.d \
./SRC/Peripheral/src/ch32v20x_bkp.d \
./SRC/Peripheral/src/ch32v20x_can.d \
./SRC/Peripheral/src/ch32v20x_crc.d \
./SRC/Peripheral/src/ch32v20x_dbgmcu.d \
./SRC/Peripheral/src/ch32v20x_dma.d \
./SRC/Peripheral/src/ch32v20x_exti.d \
./SRC/Peripheral/src/ch32v20x_flash.d \
./SRC/Peripheral/src/ch32v20x_gpio.d \
./SRC/Peripheral/src/ch32v20x_i2c.d \
./SRC/Peripheral/src/ch32v20x_iwdg.d \
./SRC/Peripheral/src/ch32v20x_misc.d \
./SRC/Peripheral/src/ch32v20x_opa.d \
./SRC/Peripheral/src/ch32v20x_pwr.d \
./SRC/Peripheral/src/ch32v20x_rcc.d \
./SRC/Peripheral/src/ch32v20x_rtc.d \
./SRC/Peripheral/src/ch32v20x_spi.d \
./SRC/Peripheral/src/ch32v20x_tim.d \
./SRC/Peripheral/src/ch32v20x_usart.d \
./SRC/Peripheral/src/ch32v20x_wwdg.d 


# Each subdirectory must supply rules for building sources it contributes
SRC/Peripheral/src/%.o: ../SRC/Peripheral/src/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -DCH32V20x_D8W -I"C:\Users\OWNER\Desktop\新建文件夹\Lesson.4\CH32V208WBU6_Car\APP\include" -I"C:\Users\OWNER\Desktop\新建文件夹\Lesson.4\CH32V208WBU6_Car\HAL\include" -I"C:\Users\OWNER\Desktop\新建文件夹\Lesson.4\CH32V208WBU6_Car\LIB" -I"C:\Users\OWNER\Desktop\新建文件夹\Lesson.4\CH32V208WBU6_Car\Profile\include" -I"C:\Users\OWNER\Desktop\新建文件夹\Lesson.4\CH32V208WBU6_Car\SRC\Core" -I"C:\Users\OWNER\Desktop\新建文件夹\Lesson.4\CH32V208WBU6_Car\SRC\Debug" -I"C:\Users\OWNER\Desktop\新建文件夹\Lesson.4\CH32V208WBU6_Car\SRC\Peripheral\inc" -I"C:\Users\OWNER\Desktop\新建文件夹\Lesson.4\CH32V208WBU6_Car\SRC\Startup" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

