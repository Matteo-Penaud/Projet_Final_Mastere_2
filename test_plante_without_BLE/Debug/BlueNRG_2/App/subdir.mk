################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../BlueNRG_2/App/OTA.c \
../BlueNRG_2/App/app_bluenrg_2.c \
../BlueNRG_2/App/gatt_db.c \
../BlueNRG_2/App/sensor.c \
../BlueNRG_2/App/target_platform.c 

OBJS += \
./BlueNRG_2/App/OTA.o \
./BlueNRG_2/App/app_bluenrg_2.o \
./BlueNRG_2/App/gatt_db.o \
./BlueNRG_2/App/sensor.o \
./BlueNRG_2/App/target_platform.o 

C_DEPS += \
./BlueNRG_2/App/OTA.d \
./BlueNRG_2/App/app_bluenrg_2.d \
./BlueNRG_2/App/gatt_db.d \
./BlueNRG_2/App/sensor.d \
./BlueNRG_2/App/target_platform.d 


# Each subdirectory must supply rules for building sources it contributes
BlueNRG_2/App/%.o BlueNRG_2/App/%.su BlueNRG_2/App/%.cyclo: ../BlueNRG_2/App/%.c BlueNRG_2/App/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../BlueNRG_2/App -I../BlueNRG_2/Target -I../Drivers/BSP/STM32L4xx_Nucleo -I../Middlewares/ST/BlueNRG-2/hci/hci_tl_patterns/Basic -I../Middlewares/ST/BlueNRG-2/utils -I../Middlewares/ST/BlueNRG-2/includes -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-BlueNRG_2-2f-App

clean-BlueNRG_2-2f-App:
	-$(RM) ./BlueNRG_2/App/OTA.cyclo ./BlueNRG_2/App/OTA.d ./BlueNRG_2/App/OTA.o ./BlueNRG_2/App/OTA.su ./BlueNRG_2/App/app_bluenrg_2.cyclo ./BlueNRG_2/App/app_bluenrg_2.d ./BlueNRG_2/App/app_bluenrg_2.o ./BlueNRG_2/App/app_bluenrg_2.su ./BlueNRG_2/App/gatt_db.cyclo ./BlueNRG_2/App/gatt_db.d ./BlueNRG_2/App/gatt_db.o ./BlueNRG_2/App/gatt_db.su ./BlueNRG_2/App/sensor.cyclo ./BlueNRG_2/App/sensor.d ./BlueNRG_2/App/sensor.o ./BlueNRG_2/App/sensor.su ./BlueNRG_2/App/target_platform.cyclo ./BlueNRG_2/App/target_platform.d ./BlueNRG_2/App/target_platform.o ./BlueNRG_2/App/target_platform.su

.PHONY: clean-BlueNRG_2-2f-App

