################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/ST/BlueNRG-2/hci/bluenrg1_devConfig.c \
../Middlewares/ST/BlueNRG-2/hci/bluenrg1_events.c \
../Middlewares/ST/BlueNRG-2/hci/bluenrg1_events_cb.c \
../Middlewares/ST/BlueNRG-2/hci/bluenrg1_hci_le.c 

OBJS += \
./Middlewares/ST/BlueNRG-2/hci/bluenrg1_devConfig.o \
./Middlewares/ST/BlueNRG-2/hci/bluenrg1_events.o \
./Middlewares/ST/BlueNRG-2/hci/bluenrg1_events_cb.o \
./Middlewares/ST/BlueNRG-2/hci/bluenrg1_hci_le.o 

C_DEPS += \
./Middlewares/ST/BlueNRG-2/hci/bluenrg1_devConfig.d \
./Middlewares/ST/BlueNRG-2/hci/bluenrg1_events.d \
./Middlewares/ST/BlueNRG-2/hci/bluenrg1_events_cb.d \
./Middlewares/ST/BlueNRG-2/hci/bluenrg1_hci_le.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/ST/BlueNRG-2/hci/%.o Middlewares/ST/BlueNRG-2/hci/%.su Middlewares/ST/BlueNRG-2/hci/%.cyclo: ../Middlewares/ST/BlueNRG-2/hci/%.c Middlewares/ST/BlueNRG-2/hci/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../BlueNRG_2/App -I../BlueNRG_2/Target -I../Drivers/BSP/STM32L4xx_Nucleo -I../Middlewares/ST/BlueNRG-2/hci/hci_tl_patterns/Basic -I../Middlewares/ST/BlueNRG-2/utils -I../Middlewares/ST/BlueNRG-2/includes -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-ST-2f-BlueNRG-2d-2-2f-hci

clean-Middlewares-2f-ST-2f-BlueNRG-2d-2-2f-hci:
	-$(RM) ./Middlewares/ST/BlueNRG-2/hci/bluenrg1_devConfig.cyclo ./Middlewares/ST/BlueNRG-2/hci/bluenrg1_devConfig.d ./Middlewares/ST/BlueNRG-2/hci/bluenrg1_devConfig.o ./Middlewares/ST/BlueNRG-2/hci/bluenrg1_devConfig.su ./Middlewares/ST/BlueNRG-2/hci/bluenrg1_events.cyclo ./Middlewares/ST/BlueNRG-2/hci/bluenrg1_events.d ./Middlewares/ST/BlueNRG-2/hci/bluenrg1_events.o ./Middlewares/ST/BlueNRG-2/hci/bluenrg1_events.su ./Middlewares/ST/BlueNRG-2/hci/bluenrg1_events_cb.cyclo ./Middlewares/ST/BlueNRG-2/hci/bluenrg1_events_cb.d ./Middlewares/ST/BlueNRG-2/hci/bluenrg1_events_cb.o ./Middlewares/ST/BlueNRG-2/hci/bluenrg1_events_cb.su ./Middlewares/ST/BlueNRG-2/hci/bluenrg1_hci_le.cyclo ./Middlewares/ST/BlueNRG-2/hci/bluenrg1_hci_le.d ./Middlewares/ST/BlueNRG-2/hci/bluenrg1_hci_le.o ./Middlewares/ST/BlueNRG-2/hci/bluenrg1_hci_le.su

.PHONY: clean-Middlewares-2f-ST-2f-BlueNRG-2d-2-2f-hci

