#include <avr/io.h>
#include <stdint.h>
#include <math.h>
#include <avr/interrupt.h>
#define CLOCK 16000000
unsigned long int ov = 0;
#define INPUT 0
#define OUTPUT 1
#define LOW 0
#define HIGH 1

void pinMode(short x, short y)
{
	switch(x)
	{
		case 1:   // pin1 is PC6
				if(y == OUTPUT) DDRC |= (1<<DDC6);
		else DDRC &= ~(1<<DDC6);
				break;
		case 2:
				if(y == OUTPUT) DDRD |= (1<<DDD0);
        else DDRD &= ~(1<<DDD0);
				break;
		case 3:
				if(y == OUTPUT) DDRD |= (1<<DDD1);
        else DDRD &= ~(1<<DDD1);
				break;
		case 4:
				if(y == OUTPUT) DDRD |= (1<<DDD2);
        else DDRD &= ~(1<<DDD2);
				break;
		case 5:
				if(y == OUTPUT) DDRD |= (1<<DDD3);
        else DDRD &= ~(1<<DDD3);
				break;
		case 6:
				if(y == OUTPUT) DDRD |= (1<<DDD4);
        else DDRD &= ~(1<<DDD4);
				break;
		case 11:
				if(y == OUTPUT) DDRD |= (1<<DDD5);
        else DDRD &= ~(1<<DDD5);
				break;
		case 12:
				if(y == OUTPUT) DDRD |= (1<<DDD6);
        else DDRD &= ~(1<<DDD6);
				break;
		case 13:
				if(y == OUTPUT) DDRD |= (1<<DDD7);
        else DDRD &= ~(1<<DDD7);
				break;
		case 14:
				if(y == OUTPUT) DDRB |= (1<<DDB0);
				else DDRB &= ~(1<<DDB0);
				break;
		case 15:
				if(y == OUTPUT) DDRB |= (1<<DDB1);
				else DDRB &= ~(1<<DDB1);
				break;
		case 16:
				if(y == OUTPUT) DDRB |= (1<<DDB2);
				else DDRB &= ~(1<<DDB2);
				break;
		case 17:
				if(y == OUTPUT) DDRB |= (1<<DDB3);
				else DDRB &= ~(1<<DDB3);
				break;
		case 18:
				if(y == OUTPUT) DDRB |= (1<<DDB4);
				else DDRB &= ~(1<<DDB4);
				break;
		case 19:
				if(y == OUTPUT) DDRB |= (1<<DDB5);
				else DDRB &= ~(1<<DDB5);
				break;
		case 23:
				if(y == OUTPUT) DDRC |= (1<<DDC0);
				else DDRC &= ~(1<<DDC0);
				break;
		case 24:
				if(y == OUTPUT) DDRC |= (1<<DDC1);
				else DDRC &= ~(1<<DDC1);
				break;
		case 25:
				if(y == OUTPUT) DDRC |= (1<<DDC2);
				else DDRC &= ~(1<<DDC2);
				break;
		case 26:
				if(y == OUTPUT) DDRC |= (1<<DDC3);
				else DDRC &= ~(1<<DDC3);
				break;
		case 27:
				if(y == OUTPUT) DDRC |= (1<<DDC4);
				else DDRC &= ~(1<<DDC4);
				break;
		case 28:
				if(y == OUTPUT) DDRC |= (1<<DDC5);
				else DDRC &= ~(1<<DDC5);
				break;
	}
}

short readPin(short int x)
{
	switch(x)
	{
		case 1:
				if(PINC & (1<<PINC6)) return 1;
				else return 0;
		case 2:
				if(PIND & (1<<PIND0)) return 1;
				else return 0;
		case 3:
				if(PIND & (1<<PIND1)) return 1;
				else return 0;
		case 4:
				if(PIND & (1<<PIND2)) return 1;
				else return 0;
		case 5:
				if(PIND & (1<<PIND3)) return 1;
				else return 0;
		case 6:
				if(PIND & (1<<PIND4)) return 1;
				else return 0;
		case 11:
				if(PIND & (1<<PIND5)) return 1;
				else return 0;
		case 12:
				if(PIND & (1<<PIND6)) return 1;
				else return 0;
		case 13:
				if(PIND & (1<<PIND7)) return 1;
				else return 0;
		case 14:
				if(PINB & (1<<PINB0)) return 1;
				else return 0;
		case 15:
				if(PINB & (1<<PINB1)) return 1;
				else return 0;
		case 16:
				if(PINB & (1<<PINB2)) return 1;
				else return 0;
		case 17:
				if(PINB & (1<<PINB3)) return 1;
				else return 0;
		case 18:
				if(PINB & (1<<PINB4)) return 1;
				else return 0;
		case 19:
				if(PINB & (1<<PINB5)) return 1;
				else return 0;
		case 23:
				if(PINC & (1<<PINC0)) return 1;
				else return 0;
		case 24:
				if(PINC & (1<<PINC1)) return 1;
				else return 0;
		case 25:
				if(PINC & (1<<PINC2)) return 1;
				else return 0;
		case 26:
				if(PINC & (1<<PINC3)) return 1;
				else return 0;
		case 27:
				if(PINC & (1<<PINC4)) return 1;
				else return 0;
		case 28:
				if(PINC & (1<<PINC5)) return 1;
				else return 0;
	}
	return -1;

}

void digitalWrite(short int x, short int y)
{
	switch(x)
	{
		case 1:     // pin1 is PC6
			if(y==1) PORTC |= (1<<PORTC6);
			else PORTC &= ~(1<<PORTC6);
			break;
		case 2:
			if(y==1) PORTD |= (1<<PORTD0);
			else PORTD &= ~(1<<PORTD0);
			break;
		case 3:
			if(y==1) PORTD |= (1<<PORTD1);
			else PORTD &= ~(1<<PORTD1);
			break;
		case 4:
			if(y==1) PORTD |= (1<<PORTD2);
			else PORTD &= ~(1<<PORTD2);
			break;
		case 5:
			if(y==1) PORTD |= (1<<PORTD3);
			else PORTD &= ~(1<<PORTD3);
			break;
		case 6:
			if(y==1) PORTD |= (1<<PORTD4);
			else PORTD &= ~(1<<PORTD4);
			break;
		case 11:
			if(y==1) PORTD |= (1<<PORTD5);
			else PORTD &= ~(1<<PORTD5);
			break;
		case 12:
			if(y==1) PORTD |= (1<<PORTD6);
			else PORTD &= ~(1<<PORTD6);
			break;
		case 13:
			if(y==1) PORTD |= (1<<PORTD7);
			else PORTD &= ~(1<<PORTD7);
			break;
		case 14:
			if(y==1) PORTB |= (1<<PORTB0);
			else PORTB &= ~(1<<PORTB0);
			break;
		case 15:
			if(y==1) PORTB |= (1<<PORTB1);
			else PORTB &= ~(1<<PORTB1);
			break;
		case 16:
			if(y==1) PORTB |= (1<<PORTB2);
			else PORTB &= ~(1<<PORTB2);
			break;
		case 17:
			if(y==1) PORTB |= (1<<PORTB3);
			else PORTB &= ~(1<<PORTB3);
			break;
		case 18:
			if(y==1) PORTB |= (1<<PORTB4);
			else PORTB &= ~(1<<PORTB4);
			break;
		case 19:
			if(y==1) PORTB |= (1<<PORTB5);
			else PORTB &= ~(1<<PORTB5);
			break;
		case 23:
			if(y==1) PORTC |= (1<<PORTC0);
			else PORTC &= ~(1<<PORTC0);
			break;
		case 24:
			if(y==1) PORTC |= (1<<PORTC1);
			else PORTC &= ~(1<<PORTC1);
			break;
		case 25:
			if(y==1) PORTC |= (1<<PORTC2);
			else PORTC &= ~(1<<PORTC2);
			break;
		case 26:
			if(y==1) PORTC |= (1<<PORTC3);
			else PORTC &= ~(1<<PORTC3);
			break;
		case 27:
			if(y==1) PORTC |= (1<<PORTC4);
			else PORTC &= ~(1<<PORTC4);
			break;
		case 28:
			if(y==1) PORTC |= (1<<PORTC5);
			else PORTC &= ~(1<<PORTC5);
			break;
	}
}




void startTime()
{
	ov = 0;
	TCNT1 = 0;
	sei();
	TIMSK1 |= (1<<TOIE1);
	TCCR1A = 0;
	TCCR1B = (1 << CS10);	//start the timer in normal mode
}

double stopAndGetTime()
{
	double curr_time = 0.0;
	uint16_t reg_value;
	TCCR1B = 0;	//stop the timer
	cli();
	reg_value = TCNT1;
	curr_time = reg_value/(double)CLOCK;
	curr_time += (65535*ov/(double)CLOCK);
	return curr_time;
}

unsigned long stopAndGetRawTime()
{
	unsigned long reg_value;
	TCCR1B = 0;	//stop the timer
	cli();
	reg_value = TCNT1;
	reg_value += 65535*ov;
	return reg_value;
}

double getTime()
{
	double curr_time = 0.0;
	uint16_t reg_value;
	reg_value = TCNT1;
	curr_time = reg_value/(double)CLOCK;
	curr_time += (65535*ov/(double)CLOCK);
	return curr_time;
}

unsigned long getRawTime()
{
	unsigned long reg_value;
	reg_value = TCNT1;
	reg_value += 65535*ov;
	return reg_value;
}

ISR (TIMER1_OVF_vect)
{
    ov++;
}
