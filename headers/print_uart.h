/*
 * print_uart.h
 *
 *  Created on: 27-Apr-2019
 *      Author: aaditya
 */
#include<math.h>
#include <stdio.h>

#define BAUDRATE 9600        //The baudrate that we want to use
#define BAUD_PRESCALLER (((F_CPU / (BAUDRATE * 16UL))) - 1)    //The formula that does all the required maths

#define FOSC 16000000
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

static void usend(char data, FILE *stream);

//static FILE mystdout = FDEV_SETUP_STREAM(usend, NULL, _FDEV_SETUP_WRITE);

void uinit(void){
//	PD1 as output and PD0 as input:

	DDRD |= (1 << DDD1);
	DDRD &= ~(1 << DDD0);

	UBRR0H = (uint8_t)(BAUD_PRESCALLER>>8);
	UBRR0L = (uint8_t)(BAUD_PRESCALLER);
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	UCSR0C = ((1<<UCSZ00)|(3<<UCSZ01));

//	NEW DATA
    //1 = output, 0 = input
//    DDRB = 0b11101111; //PB4 = MISO
//    DDRC = 0b11111111; //
//    DDRD = 0b11111110; //PORTD (RX on PD0)

    //USART Baud rate: 9600
//    UBRR0H = (MYUBRR >> 8);
//    UBRR0L = MYUBRR;
//    UCSR0B = (1<<RXEN0)|(1<<TXEN0);

//    NEW DATA END

//    stdout = &mystdout; //Required for printf init
}

static void usend(char data, FILE *stream)
{
    if (data == '\n') usend('\r', stream);
	while(!(UCSR0A & (1<<UDRE0)));
	UDR0 = data;
}

unsigned char ureceive(void){

	while(!(UCSR0A & (1<<RXC0)));
	return UDR0;

}

void uputstring(char* StringPtr){

	FILE *stream = 0;

	while(*StringPtr != 0x00)
	{    //Here we check if there is still more chars to send, this is done checking the actual char and see if it is different from the null char
		usend(*StringPtr, stream);    //Using the simple send function we send one char at a time
		StringPtr++;
	}        //We increment the pointer so we can read the next char
	usend('\r', stream);
	usend('\n', stream);
}

void uprint_long(unsigned long x)
{
	FILE *stream = 0;
	int i[5],n=0,j;
	unsigned char t[]="0123456789";
	if(x<0){
		x*=-1;
		usend('-', stream);
	}
	do{
		i[n++]=x%10;
		x/=10;
	}while(x>0);
	for(j=n-1;j>=0;j--)
	usend(t[i[j]], stream);
}

void uprint_num(int16_t x)
{
	FILE *stream = 0;
	int i[5],n=0,j;
	unsigned char t[]="0123456789";
	if(x<0){
		x*=-1;
		usend('-', stream);
	}
	do{
		i[n++]=x%10;
		x/=10;
	}while(x>0);
	for(j=n-1;j>=0;j--)
	usend(t[i[j]], stream);
}

void uprint_double(double x)
{
	FILE *stream = 0;
	uint16_t y;
	int i;
	unsigned char max_dec = 3;
	unsigned char t[7], z[]="0123456789";
	if(x<0){
		x*=-1;
		usend('-', stream);
	}
	uprint_num((int) x);
	usend('.', stream);

	for(i=0; i <= max_dec; i++)
		x *= 10;

	y = (uint16_t) x;

	for(i = max_dec; i >= 0; i--)
	{
		t[i] = y%10;
		y /= 10;
	}

	for (i = 0; i <= max_dec; i++)
	{
		usend(z[t[i]], stream);
	}

}

void uprint(char *str, ...)
{
	FILE *stream = 0;
	char *x = str;
	va_list args;

	va_start(args, str);
	while(*x != 0)
	{
		if(*x=='%')
		{
			x++;
			if(*x=='d')
			{
				uprint_num(va_arg(args, int));
			}
			else if(*x=='f')
			{
				uprint_double(va_arg(args, double));
			}
			else if(*x=='l' && *(x+1)=='d')
			{
				uprint_num(va_arg(args, int16_t));
				x++;
			}
		}
		else usend(*x, stream);

		x++;
	}
}

// Main print function

void uprintln(char *str, ...)
{
	char *x = str;
	va_list args;
	FILE *stream = 0;

	va_start(args, str);
	while(*x != 0)
	{
		if(*x=='%')
		{
			x++;
			if(*x=='d')
			{
				uprint_num(va_arg(args, int));
			}
			else if(*x=='f')
			{
				uprint_double(va_arg(args, double));
			}
			else if(*x=='l' && *(x+1)=='d')
			{
				uprint_long(va_arg(args, unsigned long));
				x++;
			}
		}
		else usend(*x, stream);

		x++;
	}
	usend('\r', stream);
	usend('\n', stream);
}

//TEST FUNCTION
void uart_test()
{
	/*
	while(1)
	{        //Infinite loop
		USART_putstring("Aaditya");		//Pass the string to the USART_putstring function and sends it over the serial
		_delay_ms(1000);				//Delay for 5 seconds so it will re-send the string every 5 seconds
	}
	*/
	while(1)
	{
		printf("Test it!! x = %d\n", 24);
		_delay_ms(500);
	}
}






