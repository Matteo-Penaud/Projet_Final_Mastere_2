

/*********************************INCLUDES******************************************/
#include "BME280.h"
#include <string.h>

/**********************GLOBAL VARIABLES AND CONSTANTS*******************************/


/****************************FORWARD DECLARATIONS***********************************/
uint32_t adc_t, adc_p, adc_h;
int32_t t_fine;
BME280_Calib Calib_Data;

/*********************************FUNCTIONS*****************************************/


/*
 * @brief  Function reads BME280 chip ID
 * @retval BME280 chip ID
 *
 * */
static uint8_t BME280_GetID(BME280 *device)
{
   uint8_t id;
   HAL_I2C_Mem_Read(device->i2cHandle, BME280_ADDR << 1, BME280_ID_ADDRESS, 1, &id, 1, 20);

   return id;
}

/*
 * @brief  Function sets temperature oversampling
 *
 * */
static void BME280_SetTemperatureOversamp(BME280 *device, uint8_t value)
{
   uint8_t ctrl;
   HAL_I2C_Mem_Read(device->i2cHandle, BME280_ADDR << 1, BME280_CTRL_MEAS, 1, &ctrl, 1, 20);
   ctrl &= 0x1F;
   ctrl |= value << 5;
   HAL_I2C_Mem_Write(device->i2cHandle, BME280_ADDR << 1, BME280_CTRL_MEAS, 1, &ctrl, 1, 20);
}

/*
 * @brief  Function sets pressure oversampling
 *
 * */
static void BME280_SetPressureOversamp(BME280 *device, uint8_t value)
{
   uint8_t ctrl;
   HAL_I2C_Mem_Read(device->i2cHandle, BME280_ADDR << 1, BME280_CTRL_MEAS, 1, &ctrl, 1, 20);
   ctrl &= 0xE3;
   ctrl |= value << 2;
   HAL_I2C_Mem_Write(device->i2cHandle, BME280_ADDR << 1, BME280_CTRL_MEAS, 1, &ctrl, 1, 20);
}

/*
 * @brief  Function sets humidity oversampling
 *
 * */
static void BME280_SetHumidityOversamp(BME280 *device, uint8_t value)
{
   uint8_t ctrl;
   HAL_I2C_Mem_Read(device->i2cHandle, BME280_ADDR << 1, BME280_CTRL_HUM, 1, &ctrl, 1, 20);
   ctrl &= 0x00;
   ctrl |= value;
   HAL_I2C_Mem_Write(device->i2cHandle, BME280_ADDR << 1, BME280_CTRL_HUM, 1, &ctrl, 1, 20);
}

/*
 * @brief  Function sets working mode
 *
 * */
static void BME280_SetWorkingMode(BME280 *device, uint8_t value)
{
   uint8_t ctrl;
   HAL_I2C_Mem_Read(device->i2cHandle, BME280_ADDR << 1, BME280_CTRL_MEAS, 1, &ctrl, 1, 20);
   ctrl &= 0xFC;
   ctrl |= value;
   HAL_I2C_Mem_Write(device->i2cHandle, BME280_ADDR << 1, BME280_CTRL_MEAS, 1, &ctrl, 1, 20);
}

/*
 * @brief  Function sets filter coefficients
 *
 * */
static void BME280_SetFilterCoeff(BME280 *device, uint8_t value)
{
   uint8_t ctrl;
   HAL_I2C_Mem_Read(device->i2cHandle, BME280_ADDR << 1, BME280_CONFIG, 1, &ctrl, 1, 20);
   ctrl &= 0xE3;
   ctrl |= value << 2;
   HAL_I2C_Mem_Write(device->i2cHandle, BME280_ADDR << 1, BME280_CONFIG, 1, &ctrl, 1, 20);
}

/*
 * @brief  Function sets stdby time
 *
 * */
static void BME280_SetStdbyTime(BME280 *device, uint8_t value)
{
   uint8_t ctrl;
   HAL_I2C_Mem_Read(device->i2cHandle, BME280_ADDR << 1, BME280_CONFIG, 1, &ctrl, 1, 20);
   ctrl &= 0x1F;
   ctrl |= value << 5;
   HAL_I2C_Mem_Write(device->i2cHandle, BME280_ADDR << 1, BME280_CONFIG, 1, &ctrl, 1, 20);
}

/*
 * @brief  Device Software reset
 *
 * */
void BME280_SoftReset(BME280 *device)
{
	uint8_t reset_val = 0xB6;
	HAL_I2C_Mem_Write(device->i2cHandle, BME280_ADDR  << 1, BME280_RESET,1, &reset_val, 1, 20);
}


/*
 * @brief  Read calibration data from BME280 and format it
 * @param  Pointer to an instance of BME280 structure
 *
 * */
static void BME280_GetCalibData(BME280 *device)
{

	uint8_t temp_buffer[6] = {0}, press_buffer[18] = {0}, hum_buffer[9] = {0};

	/* Read & Format Temperature Calibration Data */

	HAL_I2C_Mem_Read(device->i2cHandle, BME280_ADDR << 1, BME280_CALIB00, 1, temp_buffer, 6, 20);
	Calib_Data.dig_T1 = ((uint16_t)temp_buffer[1] << 8) + temp_buffer[0];
	Calib_Data.dig_T2 = ((int16_t)temp_buffer[3] << 8) + temp_buffer[2];
	Calib_Data.dig_T3 = ((int16_t)temp_buffer[5]<< 8) + temp_buffer[4];

	/* Read & Format Pressure Calibration Data */

	HAL_I2C_Mem_Read(device->i2cHandle, BME280_ADDR << 1, BME280_CALIB06, 1, press_buffer, 18, 20);
	Calib_Data.dig_P1 = ((uint16_t)press_buffer[1] << 8) + press_buffer[0];
	Calib_Data.dig_P2 = ((int16_t)press_buffer[3] << 8) + press_buffer[2];
	Calib_Data.dig_P3 = ((int16_t)press_buffer[5] << 8) + press_buffer[4];
	Calib_Data.dig_P4 = ((int16_t)press_buffer[7] << 8) + press_buffer[6];
	Calib_Data.dig_P5 = ((int16_t)press_buffer[9] << 8) + press_buffer[8];
	Calib_Data.dig_P6 = ((int16_t)press_buffer[11] << 8) + press_buffer[10];
	Calib_Data.dig_P7 = ((int16_t)press_buffer[13] << 8) + press_buffer[12];
	Calib_Data.dig_P8 = ((int16_t)press_buffer[15] << 8) + press_buffer[14];
	Calib_Data.dig_P9 = ((int16_t)press_buffer[17] << 8) + press_buffer[16];

	/* Read & Format Humidity Calibration Data */

	HAL_I2C_Mem_Read(device->i2cHandle, BME280_ADDR << 1, BME280_CALIB25, 1, hum_buffer, 1, 20);
	Calib_Data.dig_H1 = (uint8_t)hum_buffer[0];

	HAL_I2C_Mem_Read(device->i2cHandle, BME280_ADDR << 1, BME280_CALIB26, 1, &hum_buffer[1], 7, 20);
	Calib_Data.dig_H2 = ((int16_t)hum_buffer[2] << 8) + hum_buffer[1];
	Calib_Data.dig_H3 = (uint8_t)hum_buffer[3];
	Calib_Data.dig_H4 = ((int16_t)hum_buffer[4] << 4) | (hum_buffer[5] & 0x0F);
	Calib_Data.dig_H5 = ((int16_t)hum_buffer[6] << 4) | (hum_buffer[5] >> 4);
	Calib_Data.dig_H6 = (int8_t)hum_buffer[7];
}

/*
 * @brief  Initialization function
 *
 * */
void BME280_Init(BME280 *device, I2C_HandleTypeDef *i2c)
{
	// Fill the structure fields with initial values
	device->i2cHandle = i2c;
	device->temp_val = 0.0f;
	device->pressure_val = 0.0f;
	device->humidity_val = 0.0f;

	BME280_SoftReset(device);
	HAL_Delay(100);

	uint8_t bme280_id = 0;
	bme280_id = BME280_GetID(device);

	if(bme280_id == BME280_ID)
	{
		BME280_GetCalibData(device);
		HAL_Delay(50);

		BME280_SetTemperatureOversamp(device, BME280_OVERSAMP_X1);
		BME280_SetPressureOversamp(device, BME280_OVERSAMP_X2);
		BME280_SetHumidityOversamp(device, BME280_OVERSAMP_X1);
		BME280_SetFilterCoeff(device, BME280_FILTER_OFF);
		BME280_SetStdbyTime(device, BME280_STDBY_20_MS);
	    BME280_SetWorkingMode(device, BME280_NORMAL_MODE);
	}

}



/*
 * @brief  Read raw temperature, pressure & humidity data from BME280
 * @param  Pointer to an instance of BME280 structure
 *
 * */
void BME280_ReadSensorData(BME280 *device)
{
	uint8_t output_data[10] = {0};

	HAL_I2C_Mem_Read(device->i2cHandle, BME280_ADDR << 1, BME280_PRESS_MSB, 1, output_data, 8, 20);

	adc_p  = (uint32_t)output_data[0] << 12;      //PRESS_MSB
	adc_p |= (uint32_t)output_data[1] << 4;       //PRESS_LSB
	adc_p |= (uint32_t)output_data[2] >> 4;       //PRESS_XLSB

    adc_t  = (uint32_t)output_data[3] << 12;      //TEMP_MSB
    adc_t |= (uint32_t)output_data[4] << 4;       //TEMP_LSB
    adc_t |= (uint32_t)output_data[5] >> 4;       //TEMP_XLSB

    adc_h  = (uint32_t)output_data[6] << 8;       //HUM_MSB
    adc_h |= (uint32_t)output_data[7];            //HUM_LSB

}


/*
 * @brief  Function executes Temperature Compensation Algorithm
 *
 * */
static int32_t BME280_TemperatureComp()
{

   int32_t temp1, temp2, T;

   temp1 = ((((adc_t>>3) - ((int32_t)Calib_Data.dig_T1<<1))) * ((int32_t)Calib_Data.dig_T2)) >> 11;
   temp2 = (((((adc_t>>4) - ((int32_t)Calib_Data.dig_T1)) * ((adc_t>>4) - ((int32_t)Calib_Data.dig_T1))) >> 12) * ((int32_t)Calib_Data.dig_T3)) >> 14;
   t_fine = temp1 + temp2;
   T = (t_fine * 5 + 128) >> 8;

   return T;
}

/*
 * @brief  Function executes Pressure Compensation Algorithm
 *
 * */
static uint32_t BME280_PressureComp()
{
   int32_t press1, press2;
   uint32_t P;

   press1 = (((int32_t)t_fine)>>1) - (int32_t)64000;
   press2 = (((press1>>2) * (press1>>2)) >> 11 ) * ((int32_t)Calib_Data.dig_P6);
   press2 = press2 + ((press1 * ((int32_t)Calib_Data.dig_P5))<<1);
   press2 = (press2>>2) + (((int32_t)Calib_Data.dig_P4)<<16);
   press1 = (((Calib_Data.dig_P3 * (((press1>>2) * (press1>>2)) >> 13 )) >> 3) + ((((int32_t)Calib_Data.dig_P2) * press1)>>1))>>18;
   press1 =((((32768 + press1))*((int32_t)Calib_Data.dig_P1))>>15);
   if (press1 == 0)
   {
      return 0; // division by zero exception
   }
    P = (((uint32_t)(((int32_t)1048576) - adc_p) - (press2>>12))) * 3125;
    if (P < 0x80000000)
    {
    	P = (P << 1) / ((uint32_t)press1);
    }
    else
    {
    	P = (P / (uint32_t)press1) * 2;
    }
   press1 = (((int32_t)Calib_Data.dig_P9) * ((int32_t)(((P>>3) * (P>>3))>>13)))>>12;
   press2 = (((int32_t)(P>>2)) * ((int32_t)Calib_Data.dig_P8))>>13;
   P = (uint32_t)((int32_t)P + ((press1 + press2 + Calib_Data.dig_P7) >> 4));

   return P;
}

/*
 * @brief  Function executes Humidity Compensation Algorithm
 *
 * */
static uint32_t BME280_HumidityComp()
{
   uint32_t H;
   int32_t h1;

   h1 = (t_fine - ((int32_t)76800));
   h1 = (((((adc_h << 14) - (((int32_t)Calib_Data.dig_H4) << 20) - (((int32_t)Calib_Data.dig_H5) * h1)) +
        ((int32_t)16384)) >> 15) * (((((((h1 * ((int32_t)Calib_Data.dig_H6)) >> 10) * (((h1 *
        ((int32_t)Calib_Data.dig_H3)) >> 11) + ((int32_t)32768))) >> 10) + ((int32_t)2097152)) *
        ((int32_t)Calib_Data.dig_H2) + 8192) >> 14));
   h1 = (h1 - (((((h1 >> 15) * (h1 >> 15)) >> 7) * ((int32_t)Calib_Data.dig_H1)) >> 4));
   h1 = (h1 < 0 ? 0 : h1);
   h1 = (h1 > 419430400 ? 419430400 : h1);
   H = (uint32_t)(h1>>12);

   return H;
}

/*
 * @brief  Function calculates the temperature in C
 *
 * */
void BME280_GetTemperature(BME280 *device)
{
   float Temp;
   int32_t T;
   BME280_ReadSensorData(device);
   T = BME280_TemperatureComp();
   Temp = (float)T/100;
   device->temp_val = Temp;
}

/*
 * @brief  Function calculates the Pressure in hPa
 *
 * */
void BME280_GetPressure(BME280 *device)
{
   float Press;
   int32_t P;
   BME280_ReadSensorData(device);
   P = BME280_PressureComp();
   Press = (float)P/100;
   device->pressure_val = Press;
}

/*
 * @brief  Function calculates the Humidity
 *
 * */
void BME280_GetHumidity(BME280 *device)
{
   float Hum = 0.0f;
   uint32_t H;
   BME280_ReadSensorData(device);
   H = BME280_HumidityComp();
   Hum = (float)H/1024;
   device->humidity_val = Hum;
}


/**
  *  @brief  Send all the data via UART to plot. Data is formated for ploting in Serial Debug Assistant
  *
  */
void UART_Plot_Data(BME280 *device, UART_HandleTypeDef *port)
{
	char data_send[20] = {0};

	sprintf(data_send, "T=%2.2f,", device->temp_val);
	HAL_UART_Transmit(port, (uint8_t*)data_send, strlen(data_send), 20);

	sprintf(data_send, "P=%4.2f,", device->pressure_val);
	HAL_UART_Transmit(port, (uint8_t*)data_send, strlen(data_send), 20);

	sprintf(data_send, "H=%2.2f\r\n,", device->humidity_val);
	HAL_UART_Transmit(port, (uint8_t*)data_send, strlen(data_send), 20);
}




