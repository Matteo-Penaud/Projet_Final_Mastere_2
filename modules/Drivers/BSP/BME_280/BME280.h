#ifndef BME280_H_
#define BME280_H_

/*********************************INCLUDES******************************************/
#include "stm32l4xx_hal.h"


/**********************************DEFINES******************************************/

/*BME280 Sensor I2C Slave Address*/
#define BME280_ADDR						0x76

/* BME280 Sensor Register Address */
// Output Registers
#define BME280_HUM_LSB        		    0xFE
#define BME280_HUM_MSB           		0xFD
#define BME280_TEMP_XLSB         		0xFC
#define BME280_TEMP_LSB          		0xFB
#define BME280_TEMP_MSB           		0xFA
#define BME280_PRESS_XLSB       		0xF9
#define BME280_PRESS_LSB          		0xF8
#define BME280_PRESS_MSB          		0xF7
// Configuration & Operation Registers
#define BME280_CONFIG             		0xF5
#define BME280_CTRL_MEAS          		0xF4
#define BME280_STATUS             		0xF3
#define BME280_CTRL_HUM           		0xF2
#define BME280_RESET              		0xE0
#define BME280_ID_ADDRESS         		0xD0
// Calibration Registers
#define BME280_CALIB00            		0x88
#define BME280_CALIB01            		0x89
#define BME280_CALIB02            		0x8A
#define BME280_CALIB03            		0x8B
#define BME280_CALIB04            		0x8C
#define BME280_CALIB05            		0x8D
#define BME280_CALIB06            		0x8E
#define BME280_CALIB07            		0x8F
#define BME280_CALIB08            		0x90
#define BME280_CALIB09            		0x91
#define BME280_CALIB10            		0x92
#define BME280_CALIB11            		0x93
#define BME280_CALIB12            		0x94
#define BME280_CALIB13            		0x95
#define BME280_CALIB14            		0x96
#define BME280_CALIB15           		0x97
#define BME280_CALIB16            		0x98
#define BME280_CALIB17            		0x99
#define BME280_CALIB18            		0x9A
#define BME280_CALIB19            		0x9B
#define BME280_CALIB20           		0x9C
#define BME280_CALIB21            		0x9D
#define BME280_CALIB22            		0x9E
#define BME280_CALIB23            		0x9F
#define BME280_CALIB24            		0xA0
#define BME280_CALIB25            		0xA1
#define BME280_CALIB26            		0xE1
#define BME280_CALIB27            		0xE2
#define BME280_CALIB28            		0xE3
#define BME280_CALIB29            		0xE4
#define BME280_CALIB30            		0xE5
#define BME280_CALIB31            		0xE6
#define BME280_CALIB32            		0xE7
#define BME280_CALIB33           		0xE8
#define BME280_CALIB34            		0xE9
#define BME280_CALIB35            		0xEA
#define BME280_CALIB36            		0xEB
#define BME280_CALIB37            		0xEC
#define BME280_CALIB38            		0xED
#define BME280_CALIB39            		0xEE
#define BME280_CALIB40            		0xEF
#define BME280_CALIB41            		0xF0

/* Mode Definitions */
#define BME280_SLEEP_MODE        	 	0x00
#define BME280_FORCED_MODE        		0x01
#define BME280_NORMAL_MODE        		0x03

/* Oversampling Definitions */
#define BME280_OVERSAMP_NO        		0x00
#define BME280_OVERSAMP_X1        		0x01
#define BME280_OVERSAMP_X2        		0x02
#define BME280_OVERSAMP_X4        		0x03
#define BME280_OVERSAMP_X8        		0x04
#define BME280_OVERSAMP_X16       		0x05

/* Standby Time Definitions */
#define BME280_STDBY_500_US       		0x00
#define BME280_STDBY_62_5_MS      		0x01
#define BME280_STDBY_125_MS       		0x02
#define BME280_STDBY_250_MS       		0x03
#define BME280_STDBY_500_MS       		0x04
#define BME280_STDBY_1000_MS      		0x05
#define BME280_STDBY_10_MS        		0x06
#define BME280_STDBY_20_MS        		0x07

/* Filter Coeficient Definitions */
#define BME280_FILTER_OFF         		0x00
#define BME280_FILTER_2           		0x01
#define BME280_FILTER_4           		0x02
#define BME280_FILTER_8           		0x03
#define BME280_FILTER_16          		0x04

/* BME280 ID */
#define BME280_ID          				0x60

/*********************************STRUCTURES****************************************/
typedef struct
{
	I2C_HandleTypeDef *i2cHandle;
	float temp_val;
	float pressure_val;
	float humidity_val;
} BME280;


typedef struct
{
	uint16_t dig_T1;
	int16_t dig_T2;
	int16_t dig_T3;
	uint16_t dig_P1;
	int16_t dig_P2;
	int16_t dig_P3;
	int16_t dig_P4;
	int16_t dig_P5;
	int16_t dig_P6;
	int16_t dig_P7;
	int16_t dig_P8;
	int16_t dig_P9;
	uint8_t dig_H1;
	int16_t dig_H2;
	uint8_t dig_H3;
	int16_t dig_H4;
	int16_t dig_H5;
	int8_t dig_H6;
}BME280_Calib;

/******************************EXTERN VARIABLES*************************************/


/****************************FUNCTION PROTOTYPES************************************/
void BME280_Init(BME280 *device, I2C_HandleTypeDef *i2c);
void BME280_GetTemperature(BME280 *device);
void BME280_GetPressure(BME280 *device);
void BME280_GetHumidity(BME280 *device);
void UART_Plot_Data(BME280 *device, UART_HandleTypeDef *port);

#endif /* BME280_H_ */
