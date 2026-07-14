################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Middlewares/SerLink/Writer/Writer.cpp 

OBJS += \
./Middlewares/SerLink/Writer/Writer.o 

CPP_DEPS += \
./Middlewares/SerLink/Writer/Writer.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/SerLink/Writer/%.o Middlewares/SerLink/Writer/%.su Middlewares/SerLink/Writer/%.cyclo: ../Middlewares/SerLink/Writer/%.cpp Middlewares/SerLink/Writer/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Core/Inc/hal -I../Middlewares/SerLink/StateMachine -I../Middlewares/SerLink/Frame -I../Middlewares/SerLink/Writer -I../Middlewares/SerLink/Reader -I../USB_HOST/App -I../USB_HOST/Target -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-SerLink-2f-Writer

clean-Middlewares-2f-SerLink-2f-Writer:
	-$(RM) ./Middlewares/SerLink/Writer/Writer.cyclo ./Middlewares/SerLink/Writer/Writer.d ./Middlewares/SerLink/Writer/Writer.o ./Middlewares/SerLink/Writer/Writer.su

.PHONY: clean-Middlewares-2f-SerLink-2f-Writer

