################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/STM32CubeIDE_Workspace/SensorDemo_BLESensor-App/Middlewares/ST/BlueNRG-2/hci/controller/bluenrg1_gap_aci.c \
D:/STM32CubeIDE_Workspace/SensorDemo_BLESensor-App/Middlewares/ST/BlueNRG-2/hci/controller/bluenrg1_gatt_aci.c \
D:/STM32CubeIDE_Workspace/SensorDemo_BLESensor-App/Middlewares/ST/BlueNRG-2/hci/controller/bluenrg1_hal_aci.c \
D:/STM32CubeIDE_Workspace/SensorDemo_BLESensor-App/Middlewares/ST/BlueNRG-2/hci/controller/bluenrg1_l2cap_aci.c 

OBJS += \
./Middlewares/BlueNRG-2/Wireless/BlueNRG-2/Controller/bluenrg1_gap_aci.o \
./Middlewares/BlueNRG-2/Wireless/BlueNRG-2/Controller/bluenrg1_gatt_aci.o \
./Middlewares/BlueNRG-2/Wireless/BlueNRG-2/Controller/bluenrg1_hal_aci.o \
./Middlewares/BlueNRG-2/Wireless/BlueNRG-2/Controller/bluenrg1_l2cap_aci.o 

C_DEPS += \
./Middlewares/BlueNRG-2/Wireless/BlueNRG-2/Controller/bluenrg1_gap_aci.d \
./Middlewares/BlueNRG-2/Wireless/BlueNRG-2/Controller/bluenrg1_gatt_aci.d \
./Middlewares/BlueNRG-2/Wireless/BlueNRG-2/Controller/bluenrg1_hal_aci.d \
./Middlewares/BlueNRG-2/Wireless/BlueNRG-2/Controller/bluenrg1_l2cap_aci.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/BlueNRG-2/Wireless/BlueNRG-2/Controller/bluenrg1_gap_aci.o: D:/STM32CubeIDE_Workspace/SensorDemo_BLESensor-App/Middlewares/ST/BlueNRG-2/hci/controller/bluenrg1_gap_aci.c Middlewares/BlueNRG-2/Wireless/BlueNRG-2/Controller/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../../Inc -I../../Drivers/STM32L4xx_HAL_Driver/Inc -I../../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../../Drivers/CMSIS/Include -I../../Middlewares/ST/BlueNRG-2/hci/hci_tl_patterns/Basic -I../../Middlewares/ST/BlueNRG-2/utils -I../../Middlewares/ST/BlueNRG-2/includes -I../../Drivers/BSP/STM32L4xx_Nucleo -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/BlueNRG-2/Wireless/BlueNRG-2/Controller/bluenrg1_gatt_aci.o: D:/STM32CubeIDE_Workspace/SensorDemo_BLESensor-App/Middlewares/ST/BlueNRG-2/hci/controller/bluenrg1_gatt_aci.c Middlewares/BlueNRG-2/Wireless/BlueNRG-2/Controller/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../../Inc -I../../Drivers/STM32L4xx_HAL_Driver/Inc -I../../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../../Drivers/CMSIS/Include -I../../Middlewares/ST/BlueNRG-2/hci/hci_tl_patterns/Basic -I../../Middlewares/ST/BlueNRG-2/utils -I../../Middlewares/ST/BlueNRG-2/includes -I../../Drivers/BSP/STM32L4xx_Nucleo -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/BlueNRG-2/Wireless/BlueNRG-2/Controller/bluenrg1_hal_aci.o: D:/STM32CubeIDE_Workspace/SensorDemo_BLESensor-App/Middlewares/ST/BlueNRG-2/hci/controller/bluenrg1_hal_aci.c Middlewares/BlueNRG-2/Wireless/BlueNRG-2/Controller/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../../Inc -I../../Drivers/STM32L4xx_HAL_Driver/Inc -I../../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../../Drivers/CMSIS/Include -I../../Middlewares/ST/BlueNRG-2/hci/hci_tl_patterns/Basic -I../../Middlewares/ST/BlueNRG-2/utils -I../../Middlewares/ST/BlueNRG-2/includes -I../../Drivers/BSP/STM32L4xx_Nucleo -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/BlueNRG-2/Wireless/BlueNRG-2/Controller/bluenrg1_l2cap_aci.o: D:/STM32CubeIDE_Workspace/SensorDemo_BLESensor-App/Middlewares/ST/BlueNRG-2/hci/controller/bluenrg1_l2cap_aci.c Middlewares/BlueNRG-2/Wireless/BlueNRG-2/Controller/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../../Inc -I../../Drivers/STM32L4xx_HAL_Driver/Inc -I../../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../../Drivers/CMSIS/Include -I../../Middlewares/ST/BlueNRG-2/hci/hci_tl_patterns/Basic -I../../Middlewares/ST/BlueNRG-2/utils -I../../Middlewares/ST/BlueNRG-2/includes -I../../Drivers/BSP/STM32L4xx_Nucleo -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-BlueNRG-2d-2-2f-Wireless-2f-BlueNRG-2d-2-2f-Controller

clean-Middlewares-2f-BlueNRG-2d-2-2f-Wireless-2f-BlueNRG-2d-2-2f-Controller:
	-$(RM) ./Middlewares/BlueNRG-2/Wireless/BlueNRG-2/Controller/bluenrg1_gap_aci.cyclo ./Middlewares/BlueNRG-2/Wireless/BlueNRG-2/Controller/bluenrg1_gap_aci.d ./Middlewares/BlueNRG-2/Wireless/BlueNRG-2/Controller/bluenrg1_gap_aci.o ./Middlewares/BlueNRG-2/Wireless/BlueNRG-2/Controller/bluenrg1_gap_aci.su ./Middlewares/BlueNRG-2/Wireless/BlueNRG-2/Controller/bluenrg1_gatt_aci.cyclo ./Middlewares/BlueNRG-2/Wireless/BlueNRG-2/Controller/bluenrg1_gatt_aci.d ./Middlewares/BlueNRG-2/Wireless/BlueNRG-2/Controller/bluenrg1_gatt_aci.o ./Middlewares/BlueNRG-2/Wireless/BlueNRG-2/Controller/bluenrg1_gatt_aci.su ./Middlewares/BlueNRG-2/Wireless/BlueNRG-2/Controller/bluenrg1_hal_aci.cyclo ./Middlewares/BlueNRG-2/Wireless/BlueNRG-2/Controller/bluenrg1_hal_aci.d ./Middlewares/BlueNRG-2/Wireless/BlueNRG-2/Controller/bluenrg1_hal_aci.o ./Middlewares/BlueNRG-2/Wireless/BlueNRG-2/Controller/bluenrg1_hal_aci.su ./Middlewares/BlueNRG-2/Wireless/BlueNRG-2/Controller/bluenrg1_l2cap_aci.cyclo ./Middlewares/BlueNRG-2/Wireless/BlueNRG-2/Controller/bluenrg1_l2cap_aci.d ./Middlewares/BlueNRG-2/Wireless/BlueNRG-2/Controller/bluenrg1_l2cap_aci.o ./Middlewares/BlueNRG-2/Wireless/BlueNRG-2/Controller/bluenrg1_l2cap_aci.su

.PHONY: clean-Middlewares-2f-BlueNRG-2d-2-2f-Wireless-2f-BlueNRG-2d-2-2f-Controller

