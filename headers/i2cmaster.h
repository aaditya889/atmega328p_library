/*
 * i2cmaster.h
 *
 *  Created on: 27-Apr-2019
 *      Author: aaditya
 */

#include <avr/io.h>
#include <stdint.h>
#include <math.h>
#include "print_uart.h"
// MPU DEFINES

#define ACC_X 59
#define ACC_Y 61
#define ACC_Z 63
#define ACC_CONFIG 28
#define ACC_FS_SEL_0 0
#define ACC_FS_SEL_1 8
#define ACC_FS_SEL_2 16
#define ACC_FS_SEL_3 24
#define ACC_SENS_0 16384.0
#define ACC_SENS_1 8192.0
#define ACC_SENS_2 4096.0
#define ACC_SENS_3 2048.0

#define GYR_X 67
#define GYR_Y 69
#define GYR_Z 71
#define GYR_CONFIG 27
#define GYR_FS_SEL_0 0
#define GYR_FS_SEL_1 8
#define GYR_FS_SEL_2 16
#define GYR_FS_SEL_3 24
#define GYR_SENS_0 131.0
#define GYR_SENS_1 65.5
#define GYR_SENS_2 32.8
#define GYR_SENS_3 16.4

#define PI 3.1415926535

uint8_t tim=0;

void iicInit(void)
{
	//set SCL to 400kHz
	TWSR = 0x00;
	TWBR = 0x0C;
	//enable TWI
	TWCR = (1<<TWEN);
}

void iicStart()
{
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while ((TWCR & (1<<TWINT)) == 0);
}

void iicStop()
{
	TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
}

void iicSend(uint8_t data)
{
	TWDR = data;
	TWCR = (1<<TWINT)|(1<<TWEN);
	while ((TWCR & (1<<TWINT)) == 0);
}

uint8_t iicReadWithAck()
{
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
	while ((TWCR & (1<<TWINT)) == 0);
	return TWDR;
}

uint8_t iicReadWithNack()
{
	TWCR = (1<<TWINT)|(1<<TWEN);
	while ((TWCR & (1<<TWINT)) == 0);
	return TWDR;
}

uint8_t iicGetStatus()
{
	uint8_t status;
	//mask status
	status = TWSR & 0xF8;
	return status;
}

unsigned char mpuRead(uint8_t reg_addr)
{
	uint8_t data;
	iicStart();
	iicSend(208);	// addr + write = 208, addr + read = 209
	iicSend(reg_addr);
	iicStart();
	iicSend(209);

	data = iicReadWithNack();
	iicStop();

	if (iicGetStatus() != 0x58)
	{
		lcd_clear_and_print_string("ERROR_READ!");
	//	while(1){;}
	}
	iicStop();

	return data;
}

void mpuWrite(uint8_t reg_addr, uint8_t data)
{
	iicStart();
	iicSend(208);	// addr + write = 208, addr + read = 209
	iicSend(reg_addr);
	iicSend(data);
	if (iicGetStatus() != 0x28)
	{
		lcd_clear_and_print_string("ERROR_WRITE!");
		while(1){;}
	}
	iicStop();
}

uint16_t mpuBurstRead(uint8_t reg_addr)
{
	uint8_t temp;
	uint16_t data;

	iicStart();
	iicSend(208);
	iicSend(reg_addr);
	iicStart();
	iicSend(209);
	data = iicReadWithAck();
	temp = iicReadWithNack();
	iicStop();
	data = data << 8;
	data |= temp;

	return data;

}

void mpuInit()
{
	//lcd_clear_and_print_string("inside mpu init!");
	//_delay_ms(1000);
	mpuWrite(107, 0);
	_delay_ms(10);
	mpuWrite(26, 3);
	_delay_ms(10);
	mpuWrite(27, 16);
	_delay_ms(10);
	mpuWrite(28, 16);
	_delay_ms(10);
}

double getAccData(char axis)
{
	double tem_angle, fin_angle;
	uint16_t data = 0;

	if(axis == 'x')
		data = (int16_t) mpuBurstRead(ACC_X);
	else if(axis == 'y')
		data = (int16_t) mpuBurstRead(ACC_Y);
	else if(axis == 'z')
		data = (int16_t) mpuBurstRead(ACC_Z);

//	uprintln("value before return - %d", data);

	tem_angle = (double)((int16_t) data/(double)ACC_SENS_2);
//	uprintln("value before return - %f", tem_angle);
	fin_angle = asin(tem_angle)*(180/(double)PI);
//	uprintln("value after return - %f", fin_angle);

	return fin_angle;
}

double getGyrData(char axis)
{
	double fin_angle;
	uint16_t data = 0;

	if(axis == 'x')
		data = (int16_t) mpuBurstRead(GYR_X);
	else if(axis == 'y')
		data = (int16_t) mpuBurstRead(GYR_Y);
	else if(axis == 'z')
		data = (int16_t) mpuBurstRead(GYR_Z);

	fin_angle = (double)data/(double)GYR_SENS_2;
//	fin_angle = asin(tem_angle);

	return fin_angle;
}


double getMpuReadTime()
{
	double curr_time = 0.0;
	uint16_t reg_value;
	TCCR1A = 0;
	TCCR1B = (1 << CS01);
	getAccData('x');
	TCCR1B = 0;
	reg_value = TCNT1;
	curr_time = reg_value/(double)16000000.0;
	return curr_time*1000;

}




































