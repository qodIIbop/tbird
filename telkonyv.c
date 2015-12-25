#define F_CPU 8000000UL
#include<avr/io.h>
#include<util/delay.h>
#include<inttypes.h>

#include "head.h"

void init()
{
	DDRB = 0xFF;	//LED (upper)
 	DDRD = 0xFF;	//LED (lower)
 	DDRG = 0x00;	//Push buttons
 	DDRA = 0xff;	//7 segment display
 	DDRC = 0xF8;	//Numerical buttons
 	DDRE = 0xFF;	//RGB LED, RX-TX (PB0,PB1)
}

int G_port_button()
{
 return PING;
}

void led_out(int led)
{
	 PORTB = (led<<4);
	 PORTD = led;
}

int read_out()
{
	int row=0;
	int column=0;

	for(row=0;row<4;row++)
	{
		PORTC= (1<<(row+3));
		_delay_ms(1);
		column=PINC&0x07;
		switch(column)
		{
			case 6:
				return((row*3)+1);
				break;
			case 5:
				if(row ==3)
				{
					return 0;
				}
				else
				{
					return((row*3)+2);
				}
				break;
			case 3:
				return((row*3)+3);
				break;
		}
	}

	return 13;
}

void lcd_init()
{
	DATA_DDR |= 0xF0; //determine data DDR
	COMM_DDR |= (1<<CMD_RS)|(1<<CMD_RW)|(1<<CMD_EN);
}

void lcd_send_data(int c)
{
	COMM_PORT |= (1<<CMD_RS); //instrumction register sent to send data
	DATA_PORT = c & 0xF0;
	clock();
	DATA_PORT = c<<4;
	clock();
}

void lcd_send_comm(int c)
{
	COMM_PORT &=~ (0<<CMD_RS); //instrumction register sent to send command
	DATA_PORT = c & 0xF0;
	clock();
	DATA_PORT = c<<4;
	clock();
}

void clock()
{
	_delay_ms(3);
	COMM_PORT |=(1<<CMD_EN);
	_delay_ms(3);
	COMM_PORT &=~(1<<CMD_EN);
}

void lcd_config()
{
	lcd_init();
	COMM_PORT &=~(1<<CMD_RW); //RW is 0. write on the screen
	COMM_PORT &=~(1<<CMD_RS); //RS is 0. send command
	DATA_PORT |=0x20; //use the LCD in 4bit mode
	lcd_send_comm(0x28); //4bit mode w/ 2 line
	lcd_send_comm(0x28);
	lcd_send_comm(0x28);
	lcd_send_comm(0x02); //reset mode
	lcd_send_comm(0x01); //clear lcd
	lcd_send_comm(0x0F); //lcd cursor blinking
}

void lcd_string(char *pointer)
{
	while(*pointer)
	{
		lcd_send_data(*pointer);
		pointer++;
	}
}
void lcd_move(int column, int row)
{
//0 = 0x00
//1 = 0x40
//2 = 0x10
//3 = 0x50

	int tmp=0;
	int line0=0x00;
	int line1=0x40;
	int line2=0x10;
	int line3=0x50;

	switch(row)
	{
		case 0: tmp=(line0+0x80+column); break;
		case 1: tmp=(line1+0x80+column); break;
		case 2: tmp=(line2+0x80+column); break;
		case 3: tmp=(line3+0x80+column); break;
		default: tmp=(line0+0x80+column);
	}
lcd_send_comm(tmp);
}

void lcd_num(unsigned long number)
{
	lcd_send_data('0'+(number/10000000%10));
	lcd_send_data('0'+(number/1000000%10));
	lcd_send_data('0'+(number/100000%10));
	lcd_send_data('0'+(number/10000%10));
	lcd_send_data('0'+(number/1000%10));
	lcd_send_data('0'+(number/100%10));
	lcd_send_data('0'+(number%10));
}

void buzzer_on()
{
	DDRE |=(1<<PE3);
	TCCR3A=(1<<COM3A1) | (1<<WGM30);
	TCCR3B=(1<<WGM32)  | (1<<CS32);
	OCR3A=128;
}

void buzzer_off()
{
	TCCR3A&=~(1<<COM3A1);
}

//2d array init
int init_phonedigit_array()
{
    phonedigits[0][0]='0';
    phonedigits[0][1]='+';
    phonedigits[0][2]='\0';
    phonedigits[1][0]='1';
    phonedigits[1][1]='\0';
    phonedigits[2][0]='a';
    phonedigits[2][1]='b';
    phonedigits[2][2]='c';
    phonedigits[2][3]='2';
    phonedigits[2][4]='\0';
    phonedigits[3][0]='d';
    phonedigits[3][1]='e';
    phonedigits[3][2]='f';
    phonedigits[3][3]='3';
    phonedigits[3][4]='\0';
    phonedigits[4][0]='g';
    phonedigits[4][1]='h';
    phonedigits[4][2]='i';
    phonedigits[4][3]='4';
    phonedigits[4][4]='\0';
    phonedigits[5][0]='j';
    phonedigits[5][1]='k';
    phonedigits[5][2]='l';
    phonedigits[5][3]='5';
    phonedigits[5][4]='\0';
    phonedigits[6][0]='m';
    phonedigits[6][1]='n';
    phonedigits[6][2]='o';
    phonedigits[6][3]='6';
    phonedigits[6][4]='\0';
    phonedigits[7][0]='p';
    phonedigits[7][1]='q';
    phonedigits[7][2]='r';
    phonedigits[7][3]='s';
    phonedigits[7][4]='7';
    phonedigits[7][5]='\0';
    phonedigits[8][0]='t';
    phonedigits[8][1]='u';
    phonedigits[8][2]='v';
    phonedigits[8][3]='8';
    phonedigits[8][4]='\0';
    phonedigits[9][0]='w';
    phonedigits[9][1]='x';
    phonedigits[9][2]='y';
    phonedigits[9][3]='z';
    phonedigits[9][4]='9';
    phonedigits[9][5]='\0';
    return 0;
}
