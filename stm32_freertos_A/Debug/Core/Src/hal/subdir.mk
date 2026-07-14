################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/hal/timer2.c \
../Core/Src/hal/timer3.c \
../Core/Src/hal/uart2.c 

C_DEPS += \
./Core/Src/hal/timer2.d \
./Core/Src/hal/timer3.d \
./Core/Src/hal/uart2.d 

OBJS += \
./Core/Src/hal/timer2.o \
./Core/Src/hal/timer3.o \
./Core/Src/hal/uart2.o 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/hal/%.o Core/Src/hal/%.su Core/Src/hal/%.cyclo: ../Core/Src/hal/%.c Core/Src/hal/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Core/Inc/hal -I../Middlewares/SerLink/StateMachine -I../Middlewares/SerLink/Frame -I../Middlewares/SerLink/Writer -I../Middlewares/SerLink/Reader -I../USB_HOST/App -I../USB_HOST/Target -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-hal

clean-Core-2f-Src-2f-hal:
	-$(RM) ./Core/Src/hal/timer2.cyclo ./Core/Src/hal/timer2.d ./Core/Src/hal/timer2.o ./Core/Src/hal/timer2.su ./Core/Src/hal/timer3.cyclo ./Core/Src/hal/timer3.d ./Core/Src/hal/timer3.o ./Core/Src/hal/timer3.su ./Core/Src/hal/uart2.cyclo ./Core/Src/hal/uart2.d ./Core/Src/hal/uart2.o ./Core/Src/hal/uart2.su

.PHONY: clean-Core-2f-Src-2f-hal

