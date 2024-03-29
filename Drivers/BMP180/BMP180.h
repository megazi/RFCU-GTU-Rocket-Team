/**
 * @file		BMP180.h																								
 * @author   Mete Can Gazi																										
 * @brief      BMP180 Libray for Rocket Application							
 * @revision 20.06.2019
 **/

#ifndef  _BMP180_H
#define _BMP180_H

#ifdef __cplusplus
 extern "C" {
#endif

#if defined(STMF1_Device)
	#include "stm32f1xx_hal.h"
#elif defined(STMF4_Device)
	#include "stm32f4xx_hal.h"
#endif

/*Device I2C Adresses*/
#define BMP180_Write_Adress 0xEF
#define BMP180_Read_Adress 0xEE
#define BMP180_OUT_XLSB 0xF8
#define BMP180_OUT_LSB 0xF7
#define BMP180_OUT_MSB 0xF6
#define BMP180_CTRL_MEAS 0xF4
#define BMP180_SOFT 0xE0
#define BMP180_ID 0xD0
#define BMP180_AC1 0xAA
#define BMP180_AC2 0xAC
#define BMP180_AC3 0xAE
#define BMP180_AC4 0xB0
#define BMP180_AC5 0XB2
#define BMP180_AC6 0xB4
#define BMP180_B1 0xB6
#define BMP180_B2 0xB8
#define BMP180_MB 0xBA
#define BMP180_MC 0xBC
#define BMP180_MD 0xBE

#include "stdlib.h"
#include "math.h"
#include "i2c.h"

typedef enum{
	BMP180_OverSamplingMode_UltraLowPower = 0,
	BMP180_OverSamplingMode_Standart = 1,
	BMP180_OverSamplingMode_HighResolution = 2,
	BMP180_OverSamplingMode_UltraHighResolution = 3
}BMP180_OverSamplingMode;

typedef enum{
	BMP180_ControlMeasurement_Pressure = 0x14,
	BMP180_ControlMeasurement_Temperature = 0x0E
}BMP180_ControlMeasurement;

typedef enum{
	BMP180_StartOfConversion_Start = 0x01,
	BMP180_StartOfConversion_Reset = 0x00
}BMP180_StartOfConversion;

typedef enum{
	BMP180_OK,
	BMP180_ERROR,
	BMP180_READY
}BMP180_StatusTypeDef;

typedef struct BMP180{
	I2C_HandleTypeDef  myI2C;
	uint8_t statusBMP180;
	
	/*Calibration Parameters*/
	int16_t ac1, ac2, ac3, b1, b2, mb, mc, md;
  uint16_t ac4, ac5, ac6;
	/*Calculation Parameters*/
	int32_t ut,up;
	/*Output Parameters*/
	int32_t temperature,pressure,refPressure;
	float pressurehPa,temperatureDeg,absAltitude;

}BMP180_HandleTypeDef;

/*Public Functions*/
BMP180_StatusTypeDef initBMP180(struct BMP180 *BMP180, I2C_HandleTypeDef myI2C);
BMP180_StatusTypeDef isBMP180Ready(struct BMP180 *BMP180);
BMP180_StatusTypeDef calcPressure(struct BMP180 *BMP180);
BMP180_StatusTypeDef calcAbsAltitude(struct BMP180 *BMP180);
BMP180_StatusTypeDef calibrateBMP180(struct BMP180 *BMP180);

/*Private Functions*/
void setOverSamplingMode(struct BMP180 *BMP180, BMP180_OverSamplingMode BMP180_OverSamplingMode);
void setControlMeasument(struct BMP180 *BMP180, BMP180_ControlMeasurement BMP180_ControlMeasurement);
void setStartOfConversion(struct BMP180 *BMP180, BMP180_StartOfConversion BMP180_StartOfConversion);
void writeByteBMP180(struct BMP180 *BMP180,uint8_t adress, uint8_t command);
void readByteBMP180(struct BMP180 *BMP180,uint8_t adress, uint8_t *toWrite);
void readCalibrationValues(struct BMP180 *BMP180);

uint16_t read2BytesBMP180(struct BMP180 *BMP180, uint8_t adress);
void bubblesort(int32_t *list, uint32_t n);

#ifdef __cplusplus
}
#endif

#endif
