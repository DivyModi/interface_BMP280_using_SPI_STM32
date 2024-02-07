/*
 * bmp280.c
 *
 *  Created on: Aug 31, 2022
 *      Author: divy
 */

#include <math.h>
#include "stm32l4xx_hal.h"
#include "bmp280.h"


signed long temperature_raw, pressure_raw;
unsigned short dig_T1, dig_P1;
signed short dig_T2, dig_T3, dig_P2, dig_P3, dig_P4, dig_P5, dig_P6, dig_P7, dig_P8, dig_P9;
float temperature;
uint8_t rx_buff_1[6];


uint8_t SPI_Read_Register(uint8_t internal_adr)
{
	uint8_t tx_buff[1];
	uint8_t rx_buff[1];

	tx_buff[0] = internal_adr;

	HAL_SPI_Transmit(&hspi1, tx_buff, 1, 100);
	HAL_SPI_Receive(&hspi1, rx_buff, 1, 100);

	return rx_buff[0];
}

void SPI_Write_Register(uint8_t internal_adr, uint8_t data)
{
	uint8_t tx_buff[2];

	tx_buff[0] = internal_adr;
	tx_buff[1] = data;

	HAL_SPI_Transmit(&hspi1, (uint8_t *)tx_buff, 2, 100);
}


void BMP280_init(uint8_t register_F4, uint8_t register_F5)
{
	SPI_Write_Register(BMP280_F4_write, register_F4);// osrs_t 010 x2, osrs_p 16 101, mode normal 11
	SPI_Write_Register(BMP280_F5_write, register_F5);// standby time 500ms 100, filter 16 100, SPI DIS 0
}


void BMP280_get_calib_values(void)
{
	uint8_t rx_buff[24], starting_address=0x88;

	HAL_SPI_Transmit(&hspi1, &starting_address, 1, 100);
	HAL_SPI_Receive(&hspi1, rx_buff, 24, 100);

	dig_T1=(rx_buff[0])+(rx_buff[1]<<8);
	dig_T2=(rx_buff[2])+(rx_buff[3]<<8);
	dig_T3=(rx_buff[4])+(rx_buff[5]<<8);
	dig_P1=(rx_buff[6])+(rx_buff[7]<<8);
	dig_P2=(rx_buff[8])+(rx_buff[9]<<8);
	dig_P3=(rx_buff[10])+(rx_buff[11]<<8);
	dig_P4=(rx_buff[12])+(rx_buff[13]<<8);
	dig_P5=(rx_buff[14])+(rx_buff[15]<<8);
	dig_P6=(rx_buff[16])+(rx_buff[17]<<8);
	dig_P7=(rx_buff[18])+(rx_buff[19]<<8);
	dig_P8=(rx_buff[20])+(rx_buff[21]<<8);
	dig_P9=(rx_buff[22])+(rx_buff[23]<<8);
}


void BMP280_get_status(void)
{
	uint8_t status;

	do
	{
		status=SPI_Read_Register(0xF3);
	} while(((status&0b00001000)==8)||((status&0b00000001)==1));
}



void BMP280_calc_values(void)
{
	uint8_t starting_address=0xF7;

	HAL_SPI_Transmit(&hspi1, &starting_address, 1, 100);
	HAL_SPI_Receive(&hspi1, rx_buff_1, 6, 100);

	volatile uint32_t temp[3];
	temp[2]=rx_buff_1[3];
	temp[1]=rx_buff_1[4];
	temp[0]=rx_buff_1[5];
	temperature_raw=(temp[2]<<12)+(temp[1]<<4)+(temp[0]>>4);

//	temp[2]=rx_buff[0];
//	temp[1]=rx_buff[1];
//	temp[0]=rx_buff[2];
//	pressure_raw=(temp[2]<<12)+(temp[1]<<4)+(temp[0]>>4);

	double var1, var2;
	var1=(((double)temperature_raw)/16384.0-((double)dig_T1)/1024.0)*((double)dig_T2);
	var2=((((double)temperature_raw)/131072.0-((double)dig_T1)/8192.0)*(((double)temperature_raw)/131072.0-((double)dig_T1)/8192.0))*((double)dig_T3);
	volatile	float T = (var1+var2)/5120.0;
	temperature=T;
}
