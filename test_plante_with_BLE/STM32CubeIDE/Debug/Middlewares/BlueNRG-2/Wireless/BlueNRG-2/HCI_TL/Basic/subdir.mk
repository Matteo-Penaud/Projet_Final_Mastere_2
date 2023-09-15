################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/STM32CubeIDE_Workspace/SensorDemo_BLESensor-App/Middlewares/ST/BlueNRG-2/hci/bluenrg1_devConfig.c \
D:/STM32CubeIDE_Workspace/SensorDemo_BLESensor-App/Middlewares/ST/BlueNRG-2/hci/bluenrg1_events.c \
D:/STM32CubeIDE_Workspace/SensorDemo_BLESensor-App/Middlewares/ST/BlueNRG-2/hci/bluenrg1_events_cb.c \
D:/STM32CubeIDE_Workspace/SensorDemo_BLESensor-App/Middlewares/ST/BlueNRG-2/hci/bluenrg1_hci_le.c \
D:/STM32CubeIDE_Workspace/SensorDemo_BLESensor-App/Middlewares/ST/BlueNRG-2/hci/hci_tl_patterns/Basic/hci_tl.c 

OBJS += \
./Middlewares/BlueNRG-2/Wireless/BlueNRG-2/HCI_TL/Basic/bluenrg1_devConfig.o \
./Middlewares/BlueNRG-2/Wireless/BlueNRG-2/HCI_TL/Basic/bluenrg1_events.o \
./Middlewares/BlueNRG-2/Wireless/BlueNRG-2/HCI_TL/Basic/bluenrg1_events_cb.o \
./Middlewares/BlueNRG-2/Wireless/BlueNRG-2/HCI_TL/Basic/bluenrg1_hci_le.o \
./Middlewares/BlueNRG-2/Wireless/BlueNRG-2/HCI_TL/Basic/hci_tl.o 

C_DEPS += \
./Middlewares/BlueNRG-2/Wireless/BlueNRG-2/HCI_TL/Basic/bluenrg1_devConfig.d \
./Middlewares/BlueNRG-2/Wireless/BlueNRG-2/HCI_TL/Basic/bluenrg1_events.d \
./Middlewares/BlueNRG-2/Wireless/BlueNRG-2/HCI_TL/Basic/bluenrg1_events_cb.d \
./Middlewares/BlueNRG-2/Wireless/BlueNRG-2/HCI_TL/Basic/bluenrg1_hci_le.d \
./Middlewares/BlueNRG-2/Wireless/BlueNRG-2/HCI_TL/Basic/hci_tl.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/BlueNRG-2/Wireless/BlueNRG-2/HCI_TL/Basic/bluenrg1_devConfig.o: D:/STM32CubeIDE_Workspace/SensorDemo_BLESensor-App/Middlewares/ST/BlueNRG-2/hci/bluenrg1_devConfig.c Middlewares/BlueNRG-2/Wireless/BlueNRG-2/HCI_TL/Basic/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../../Inc -I../../Drivers/STM32L4xx_HAL_Driver/Inc -I../../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../../Drivers/CMSIS/Include -I../../Middlewares/ST/BlueNRG-2/hci/hci_tl_patterns/Basic -I../../Middlewares/ST/BlueNRG-2/utils -I../../Middlewares/ST/BlueNRG-2/includes -I../../Drivers/BSP/STM32L4xx_Nucleo -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/BlueNRG-2/Wireless/BlueNRG-2/HCI_TL/Basic/bluenrg1_events.o: D:/STM32CubeIDE_Workspace/SensorDemo_BLESensor-App/Middlewares/ST/BlueNRG-2/hci/bluenrg1_events.c Middlewares/BlueNRG-2/Wireless/BlueNRG-2/HCI_TL/Basic/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../../Inc -I../../Drivers/STM32L4xx_HAL_Driver/Inc -I../../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../../Drivers/CMSIS/Include -I../../Middlewares/ST/BlueNRG-2/hci/hci_tl_patterns/Basic -I../../Middlewares/ST/BlueNRG-2/utils -I../../Middlewares/ST/BlueNRG-2/includes -I../../Drivers/BSP/STM32L4xx_Nucleo -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/BlueNRG-2/Wireless/BlueNRG-2/HCI_TL/Basic/bluenrg1_events_cb.o: D:/STM32CubeIDE_Workspace/SensorDemo_BLESensor-App/Middlewares/ST/BlueNRG-2/hci/bluenrg1_events_cb.c Middlewares/BlueNRG-2/Wireless/BlueNRG-2/HCI_TL/Basic/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../../Inc -I../../Drivers/STM32L4xx_HAL_Driver/Inc -I../../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../../Drivers/CMSIS/Include -I../../Middlewares/ST/BlueNRG-2/hci/hci_tl_patterns/Basic -I../../Middlewares/ST/BlueNRG-2/utils -I../../Middlewares/ST/BlueNRG-2/includes -I../../Drivers/BSP/STM32L4xx_Nucleo -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/BlueNRG-2/Wireless/BlueNRG-2/HCI_TL/Basic/bluenrg1_hci_le.o: D:/STM32CubeIDE_Workspace/SensorDemo_BLESensor-App/Middlewares/ST/BlueNRG-2/hci/bluenrg1_hci_le.c Middlewares/BlueNRG-2/Wireless/BlueNRG-2/HCI_TL/Basic/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../../Inc -I../../Drivers/STM32L4xx_HAL_Driver/Inc -I../../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../../Drivers/CMSIS/Include -I../../Middlewares/ST/BlueNRG-2/hci/hci_tl_patterns/Basic -I../../Middlewares/ST/BlueNRG-2/utils -I../../Middlewares/ST/BlueNRG-2/includes -I../../Drivers/BSP/STM32L4xx_Nucleo -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/BlueNRG-2/Wireless/BlueNRG-2/HCI_TL/Basic/hci_tl.o: D:/STM32CubeIDE_Workspace/SensorDemo_BLESensor-App/Middlewares/ST/BlueNRG-2/hci/hci_tl_patterns/Basic/hci_tl.c Middlewares/BlueNRG-2/Wireless/BlueNRG-2/HCI_TL/Basic/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../../Inc -I../../Drivers/STM32L4xx_HAL_Driver/Inc -I../../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../../Drivers/CMSIS/Include -I../../Middlewares/ST/BlueNRG-2/hci/hci_tl_patterns/Basic -I../../Middlewares/ST/BlueNRG-2/utils -I../../Middlewares/ST/BlueNRG-2/includes -I../../Drivers/BSP/STM32L4xx_Nucleo -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-BlueNRG-2d-2-2f-Wireless-2f-BlueNRG-2d-2-2f-HCI_TL-2f-Basic

clean-Middlewares-2f-BlueNRG-2d-2-2f-Wireless-2f-BlueNRG-2d-2-2f-HCI_TL-2f-Basic:
	-$(RM) ./Middlewares/BlueNRG-2/Wireless/BlueNRG-2/HCI_TL/Basic/bluenrg1_devConfig.cyclo ./Middlewares/BlueNRG-2/Wireless/BlueNRG-2/HCI_TL/Basic/bluenrg1_devConfig.d ./Middlewares/BlueNRG-2/Wireless/BlueNRG-2/HCI_TL/Basic/bluenrg1_devConfig.o ./Middlewares/BlueNRG-2/Wireless/BlueNRG-2/HCI_TL/Basic/bluenrg1_devConfig.su ./Middlewares/BlueNRG-2/Wireless/BlueNRG-2/HCI_TL/Basic/bluenrg1_events.cyclo ./Middlewares/BlueNRG-2/Wireless/BlueNRG-2/HCI_TL/Basic/bluenrg1_events.d ./Middlewares/BlueNRG-2/Wireless/BlueNRG-2/HCI_TL/Basic/bluenrg1_events.o ./Middlewares/BlueNRG-2/Wireless/BlueNRG-2/HCI_TL/Basic/bluenrg1_events.su ./Middlewares/BlueNRG-2/Wireless/BlueNRG-2/HCI_TL/Basic/bluenrg1_events_cb.cyclo ./Middlewares/BlueNRG-2/Wireless/BlueNRG-2/HCI_TL/Basic/bluenrg1_events_cb.d ./Middlewares/BlueNRG-2/Wireless/BlueNRG-2/HCI_TL/Basic/bluenrg1_events_cb.o ./Middlewares/BlueNRG-2/Wireless/BlueNRG-2/HCI_TL/Basic/bluenrg1_events_cb.su ./Middlewares/BlueNRG-2/Wireless/BlueNRG-2/HCI_TL/Basic/bluenrg1_hci_le.cyclo ./Middlewares/BlueNRG-2/Wireless/BlueNRG-2/HCI_TL/Basic/bluenrg1_hci_le.d ./Middlewares/BlueNRG-2/Wireless/BlueNRG-2/HCI_TL/Basic/bluenrg1_hci_le.o ./Middlewares/BlueNRG-2/Wireless/BlueNRG-2/HCI_TL/Basic/bluenrg1_hci_le.su ./Middlewares/BlueNRG-2/Wireless/BlueNRG-2/HCI_TL/Basic/hci_tl.cyclo ./Middlewares/BlueNRG-2/Wireless/BlueNRG-2/HCI_TL/Basic/hci_tl.d ./Middlewares/BlueNRG-2/Wireless/BlueNRG-2/HCI_TL/Basic/hci_tl.o ./Middlewares/BlueNRG-2/Wireless/BlueNRG-2/HCI_TL/Basic/hci_tl.su

.PHONY: clean-Middlewares-2f-BlueNRG-2d-2-2f-Wireless-2f-BlueNRG-2d-2-2f-HCI_TL-2f-Basic

