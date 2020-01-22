/*
 * lcd.h
 *
 *  Created on: 27-Apr-2019
 *      Author: aaditya
 */
#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <stdarg.h>

#define RS PORTD4
#define EN PORTD2

#define DAT4 PORTB0
#define DAT5 PORTB4
#define DAT6 PORTB5
#define DAT7 PORTC0

#define RS_PORT PORTD
#define EN_PORT PORTD

#define RS_OUTPUT_REG DDRD
#define EN_OUTPUT_REG DDRD

#define RS_OUTPUT_BIT DDD4
#define EN_OUTPUT_BIT DDD2

#define D4_PORT PORTB
#define D5_PORT PORTB
#define D6_PORT PORTB
#define D7_PORT PORTC

#define D4_OUTPUT_REG DDRB
#define D5_OUTPUT_REG DDRB
#define D6_OUTPUT_REG DDRB
#define D7_OUTPUT_REG DDRC

#define D4_OUTPUT_BIT DDB0
#define D5_OUTPUT_BIT DDB4
#define D6_OUTPUT_BIT DDB5
#define D7_OUTPUT_BIT DDC0

int curr_pos = 0;

void lcd_init_ports()
{
	// Set all the pins as output
	RS_OUTPUT_REG |= (1 << RS_OUTPUT_BIT);
	EN_OUTPUT_REG |= (1 << EN_OUTPUT_BIT);
	D4_OUTPUT_REG |= (1 << D4_OUTPUT_BIT);
	D5_OUTPUT_REG |= (1 << D5_OUTPUT_BIT);
	D6_OUTPUT_REG |= (1 << D6_OUTPUT_BIT);
	D7_OUTPUT_REG |= (1 << D7_OUTPUT_BIT);
}

void lcd_set_data_upper(unsigned char data)
{
	if (data & (1<<7))
	{
		D7_PORT |= (1 << DAT7);
	}
	else
	{
		D7_PORT &= ~(1 << DAT7);
	}
	if (data & (1<<6))
	{
		D6_PORT |= (1 << DAT6);
	}
	else
	{
		D6_PORT &= ~(1 << DAT6);
	}
	if (data & (1<<5))
	{
		D5_PORT |= (1 << DAT5);
	}
	else
	{
		D5_PORT &= ~(1 << DAT5);
	}
	if (data & (1<<4))
	{
		D4_PORT |= (1 << DAT4);
	}
	else
	{
		D4_PORT &= ~(1 << DAT4);
	}
}

void lcd_set_data_lower(unsigned char data)
{
	if (data & (1<<3))
	{
		D7_PORT |= (1 << DAT7);
	}
	else
	{
		D7_PORT &= ~(1 << DAT7);
	}
	if (data & (1<<2))
	{
		D6_PORT |= (1 << DAT6);
	}
	else
	{
		D6_PORT &= ~(1 << DAT6);
	}
	if (data & (1<<1))
	{
		D5_PORT |= (1 << DAT5);
	}
	else
	{
		D5_PORT &= ~(1 << DAT5);
	}
	if (data & (1<<0))
	{
		D4_PORT |= (1 << DAT4);
	}
	else
	{
		D4_PORT &= ~(1 << DAT4);
	}
}

void lcd_send_command(unsigned char data)
{
	EN_PORT &= ~(1 << EN);
	RS_PORT &= ~(1 << RS); // RS=0 Command

	// send upper nibble

	lcd_set_data_upper(data);

	EN_PORT |= (1 << EN); // EN=1
	_delay_us(1);
	EN_PORT &= ~(1 << EN); // EN=0

	_delay_us(200);

	// send lower nibble

	lcd_set_data_lower(data);

	EN_PORT |= (1 << EN); // EN=1
	_delay_us(1);
	EN_PORT &= ~(1 << EN); // EN=0

	_delay_ms(2);
}

void lcd_setcursor(char a, char b)
{
	if(a == 1)
	lcd_send_command(0x80 + b);
	else if(a == 2)
	lcd_send_command(0xC0 + b);
}

void lcd_send_char(unsigned char data)
{
	if (curr_pos == 16)
	{
		lcd_setcursor(2, 0);
	}
	RS_PORT |= (1 << RS); // RS=1 Data
	EN_PORT &= ~(1 << EN); // EN=0

	// send upper nibble

	lcd_set_data_upper(data);

	EN_PORT |= (1 << EN); // EN=1
	_delay_us(1);
	EN_PORT &= ~(1 << EN); // EN=0

	_delay_us(200);

	// send lower nibble

	lcd_set_data_lower(data);

	EN_PORT |= (1 << EN); // EN=1
	_delay_us(1);
	EN_PORT &= ~(1 << EN); // EN=0

	curr_pos++;
	_delay_ms(2);
}

void lcd_clear()
{
	lcd_send_command(0x01);
	lcd_send_command(0x80);
	curr_pos = 0;
}

void lcd_init()
{
	// initialise lcd in 4 bit mode

	_delay_ms(20); /* LCD Power ON delay always >15ms */
	lcd_init_ports();


	lcd_send_command(0x02);
	lcd_send_command(0x28);
	lcd_send_command(0x0c);
	lcd_send_command(0x06);
	lcd_send_command(0x01);
	lcd_clear();

	_delay_ms(2);
}

void lcd_print_string(char *str)
{
	int i;
	for (i=0;str[i]!=0;i++)
	{
		lcd_send_char(str[i]);
	}
}

void lcd_clear_and_print_string(char *str)
{
	lcd_clear();
	lcd_print_string(str);
}

void lcd_print_num(int16_t x)
{
	int i[5],n=0,j;
	unsigned char t[]="0123456789";
	if(x<0){
		x*=-1;
		lcd_send_char('-');
	}
	do{
		i[n++]=x%10;
		x/=10;
	}while(x>0);
	for(j=n-1;j>=0;j--)
	lcd_send_char(t[i[j]]);
}

void lcd_print_double(double x)
{
	unsigned int y;
	unsigned char t[2],z[]="0123456789";
	if(x<0){
		x*=-1;
		lcd_send_char('-');
	}
	lcd_print_num((int) x);
	lcd_send_char('.');
	y=(x*100);
	t[1]=y%10;
	y/=10;
	t[0]=y%10;
	lcd_send_char(z[t[0]]);
	lcd_send_char(z[t[1]]);
}

void lcd_clear_print(char *str, ...)
{
	char *x = str;
	va_list args;

	lcd_clear();

	va_start(args, str);
	while(*x){
		if(*x=='%'){
			x++;
			if(*x=='d'){
				lcd_print_num(va_arg(args, int));
			}
			else if(*x=='f'){
				lcd_print_double(va_arg(args, double));
			}
		}
		else lcd_send_char(*x);
		x++;
	}
}

void lcd_print(char *str, ...)
{
	char *x = str;
	va_list args;

	va_start(args, str);
	while(*x){
		if(*x=='%'){
			x++;
			if(*x=='d'){
				lcd_print_num(va_arg(args, int));
			}
			else if(*x=='f'){
				lcd_print_double(va_arg(args, double));
			}
		}
		else lcd_send_char(*x);
		x++;
	}
}
