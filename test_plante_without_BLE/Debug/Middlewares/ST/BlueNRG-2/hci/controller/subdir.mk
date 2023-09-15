################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/ST/BlueNRG-2/hci/controller/bluenrg1_gap_aci.c \
../Middlewares/ST/BlueNRG-2/hci/controller/bluenrg1_gatt_aci.c \
../Middlewares/ST/BlueNRG-2/hci/controller/bluenrg1_hal_aci.c \
../Middlewares/ST/BlueNRG-2/hci/controller/bluenrg1_l2cap_aci.c 

OBJS += \
./Middlewares/ST/BlueNRG-2/hci/controller/bluenrg1_gap_aci.o \
./Middlewares/ST/BlueNRG-2/hci/controller/bluenrg1_gatt_aci.o \
./Middlewares/ST/BlueNRG-2/hci/controller/bluenrg1_hal_aci.o \
./Middlewares/ST/BlueNRG-2/hci/controller/bluenrg1_l2cap_aci.o 

C_DEPS += \
./Middlewares/ST/BlueNRG-2/hci/controller/bluenrg1_gap_aci.d \
./Middlewares/ST/BlueNRG-2/hci/controller/bluenrg1_gatt_aci.d \
./Middlewares/ST/BlueNRG-2/hci/controller/bluenrg1_hal_aci.d \
./Middlewares/ST/BlueNRG-2/hci/controller/bluenrg1_l2cap_aci.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/ST/BlueNRG-2/hci/controller/%.o Middlewares/ST/BlueNRG-2/hci/controller/%.su Middlewares/ST/BlueNRG-2/hci/controller/%.cyclo: ../Middlewares/ST/BlueNRG-2/hci/controller/%.c Middlewares/ST/BlueNRG-2/hci/controller/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../BlueNRG_2/App -I../BlueNRG_2/Target -I../Drivers/BSP/STM32L4xx_Nucleo -I../Middlewares/ST/BlueNRG-2/hci/hci_tl_patterns/Basic -I../Middlewares/ST/BlueNRG-2/utils -I../Middlewares/ST/BlueNRG-2/includes -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-ST-2f-BlueNRG-2d-2-2f-hci-2f-controller

clean-Middlewares-2f-ST-2f-BlueNRG-2d-2-2f-hci-2f-controller:
	-$(RM) ./Middlewares/ST/BlueNRG-2/hci/controller/bluenrg1_gap_aci.cyclo ./Middlewares/ST/BlueNRG-2/hci/controller/bluenrg1_gap_aci.d ./Middlewares/ST/BlueNRG-2/hci/controller/bluenrg1_gap_aci.o ./Middlewares/ST/BlueNRG-2/hci/controller/bluenrg1_gap_aci.su ./Middlewares/ST/BlueNRG-2/hci/controller/bluenrg1_gatt_aci.cyclo ./Middlewares/ST/BlueNRG-2/hci/controller/bluenrg1_gatt_aci.d ./Middlewares/ST/BlueNRG-2/hci/controller/bluenrg1_gatt_aci.o ./Middlewares/ST/BlueNRG-2/hci/controller/bluenrg1_gatt_aci.su ./Middlewares/ST/BlueNRG-2/hci/controller/bluenrg1_hal_aci.cyclo ./Middlewares/ST/BlueNRG-2/hci/controller/bluenrg1_hal_aci.d ./Middlewares/ST/BlueNRG-2/hci/controller/bluenrg1_hal_aci.o ./Middlewares/ST/BlueNRG-2/hci/controller/bluenrg1_hal_aci.su ./Middlewares/ST/BlueNRG-2/hci/controller/bluenrg1_l2cap_aci.cyclo ./Middlewares/ST/BlueNRG-2/hci/controller/bluenrg1_l2cap_aci.d ./Middlewares/ST/BlueNRG-2/hci/controller/bluenrg1_l2cap_aci.o ./Middlewares/ST/BlueNRG-2/hci/controller/bluenrg1_l2cap_aci.su

.PHONY: clean-Middlewares-2f-ST-2f-BlueNRG-2d-2-2f-hci-2f-controller

