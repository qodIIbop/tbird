#define F_CPU 8000000UL
#include<avr/io.h>
#include<util/delay.h>
#include<inttypes.h>

#include "head.h"
#define DIAL_INIT -1
#define DELAY1 1000
#define DELAY_SHORT 500
//Author: Barna

int dial_num=0;
int move=0;
int dial_num_prev=DIAL_INIT;
int dial_btn_count=0;
char temp_string[10];

void main()
{
	init();
	init_phonedigit_array();
	lcd_config();
	while(1)
	{
		while((dial_num=read_out())==13)
		{
			_delay_ms(DELAY_SHORT);
		}
		if(dial_num<10)
		{
			if(dial_num==dial_num_prev)
			{
				dial_btn_count++;
			}
			if(dial_num_prev==DIAL_INIT)
			{
				dial_num_prev=dial_num;
			}
			if(dial_num>=0 && dial_num<10 && dial_num!=dial_num_prev)
			{
				led_out(255); //error message
				_delay_ms(DELAY1);
				led_out(0);	
			}
		}
				_delay_ms(DELAY1);
		if(dial_num_prev!=DIAL_INIT && dial_num==10 && dial_num_prev<10)
		{
			led_out(dial_btn_count);
				_delay_ms(DELAY1);
			sprintf(temp_string,"%c",phonedigits[dial_num_prev][dial_btn_count]);
			lcd_string(temp_string);
			dial_num_prev=DIAL_INIT;
			dial_btn_count=0;
		}
		if(dial_num==10 && dial_num_prev==DIAL_INIT)
		{
			lcd_string(" ");
			dial_num_prev=DIAL_INIT;
		}/*
		if(dial_num==12)
		{
			move++;
			lcd_move(0,move);
			dial_num_prev=DIAL_INIT;
		}*/
	}
}
