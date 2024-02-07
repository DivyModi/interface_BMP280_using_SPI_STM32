################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../driver/Scr/bmp280.c 

OBJS += \
./driver/Scr/bmp280.o 

C_DEPS += \
./driver/Scr/bmp280.d 


# Each subdirectory must supply rules for building sources it contributes
driver/Scr/%.o driver/Scr/%.su: ../driver/Scr/%.c driver/Scr/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../Core/Inc -I"D:/M.Tech College/PA&D/Workspace/pad_SPI/driver/Inc" -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-driver-2f-Scr

clean-driver-2f-Scr:
	-$(RM) ./driver/Scr/bmp280.d ./driver/Scr/bmp280.o ./driver/Scr/bmp280.su

.PHONY: clean-driver-2f-Scr

