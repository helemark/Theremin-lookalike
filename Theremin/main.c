/*
 * Theremin.c
 *
 * Created: 14.07.2021 09.14.33
 * Author : Helene
 */ 

#include <avr/io.h>

#define F_CPU 20000000


#include <avr/io.h>
#include <util/delay.h>
#include <avr/cpufunc.h>


#define USART1_BAUD_RATE(BAUD_RATE) ((float)(F_CPU * 64 / (16 * (float)BAUD_RATE)) + 0.5)
#define START_FRAME 0x3
#define END_FRAME (~START_FRAME)


//disse må nok endres Helene <333
#define A0 0xB2
#define C 0x95
#define D 0x85
#define E 0x77
#define G 0x64
#define A 0x59


uint8_t distance;


void USART3_init(void)
{
	USART3.BAUD = (uint16_t)USART1_BAUD_RATE(9600); ///Setter baudraten til 9600 (regnes ut fra klokkefrekvensen gitt i formelen i makro)
	PORTB.DIR |= PIN0_bm;							//Setter PB0 som utgangspin
	USART3.CTRLB |= USART_TXEN_bm;					//Enabler tranciever
}

void USART3_sendChar(char c)
{
	while (!(USART3.STATUS & USART_DREIF_bm))
	{
		;
	}
	USART3.TXDATAL = c;
}

void USART3_send_16_bit(uint16_t Val)
{
	USART3_sendChar(START_FRAME);
	USART3_sendChar(Val & 0xFF);
	USART3_sendChar((Val >> 8) & 0xFF);
	USART3_sendChar(END_FRAME);
}

void USART3_send_32_bit(uint32_t Val)
{
	USART3_sendChar(START_FRAME);
	USART3_sendChar(Val & 0xFF);
	USART3_sendChar((Val >> 8) & 0xFF);
	USART3_sendChar((Val >> 16) & 0xFF);
	USART3_sendChar((Val >> 24) & 0xFF);
	USART3_sendChar(END_FRAME);
}


void distanceSensor_init(void)
{
	
	//Pin 7 as output to Trig
	PORTD.DIRSET = PIN7_bm;
	
	//Pin0 as input - default
	
}

void take_distanceSample(void)
{
	PORTD.OUTSET = PIN7_bm;
	_delay_us(10);
	PORTD.OUTCLR = PIN7_bm;
	
	
}






int main(void)
{
	ccp_write_io((uint8_t*)&CLKCTRL.OSCHFCTRLA, CLKCTRL_FREQSEL_20M_gc);
	USART3_init();
	distanceSensor_init();
	
	
	
    while (1) 
    {
    }
}

