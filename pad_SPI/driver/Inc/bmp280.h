/*
 * bmp280.h
 *
 *  Created on: Aug 31, 2022
 *      Author: divy
 */

#ifndef BMP280_H_
#define BMP280_H_

#include <math.h>
#include "stm32l4xx_hal.h"

#define BMP280_F4_write 0x74
#define BMP280_F4_read 0xF4
#define BMP280_F5_write 0x75
#define BMP280_F5_read 0xF5

//REGISTER 0xF4
#define F4_osrs_t_skipped			0b00000000
#define F4_osrs_t_oversampling1		0b00100000
#define F4_osrs_t_oversampling2		0b01000000
#define F4_osrs_t_oversampling4		0b01100000
#define F4_osrs_t_oversampling8		0b10000000
#define F4_osrs_t_oversampling16	0b10100000

#define F4_osrs_p_skipped			0b00000000
#define F4_osrs_p_oversampling1		0b00000100
#define F4_osrs_p_oversampling2		0b00001000
#define F4_osrs_p_oversampling4		0b00001100
#define F4_osrs_p_oversampling8		0b00010000
#define F4_osrs_p_oversampling16	0b00010100

#define F4_mode_sleep				0b00000000
#define F4_mode_forced				0b00000001
#define F4_mode_normal				0b00000011

//REGISTER 0xF5
#define F5_t_sb_500us				0b00000000
#define F5_t_sb_62500us				0b00100000
#define F5_t_sb_125ms				0b01000000
#define F5_t_sb_250ms				0b01100000
#define F5_t_sb_500ms				0b10000000
#define F5_t_sb_1sec				0b10100000
#define F5_t_sb_2sec				0b11000000
#define F5_t_sb_4sec				0b11100000

#define F5_filter_1					0b00000000
#define F5_filter_2					0b00000010
#define F5_filter_5					0b00000100
#define F5_filter_11				0b00000110
#define F5_filter_22				0b00001010

#define F5_spi4w_en					0b00000000
#define F5_spi3w_en					0b00000001

extern SPI_HandleTypeDef hspi1;

extern signed long temperature_raw, pressure_raw;
extern unsigned short dig_T1, dig_P1;
extern signed short dig_T2, dig_T3, dig_P2, dig_P3, dig_P4, dig_P5, dig_P6, dig_P7, dig_P8, dig_P9;
extern float temperature, pressure, altitude, init_height;

extern uint8_t SPI_Read_Register(uint8_t internal_adr);

extern void SPI_Write_Register(uint8_t internal_adr, uint8_t data);

extern void BMP280_init(uint8_t register_F4, uint8_t register_F5);

extern void BMP280_calc_values(void);

extern void BMP280_get_values(void);

void BMP280_get_status(void);

void BMP280_get_calib_values(void);

#endif /* BMP280_H_ */
