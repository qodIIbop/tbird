#ifndef head_H_
#define head_H_
#define F_CPU 12000000UL
#include<avr/io.h>
#include<util/delay.h>
#include <avr/interrupt.h>
#include <inttypes.h>

char phonedigits[10][6];
int init_phonedigit_array();

//LCD
#define DATA_DDR DDRE //data direction
#define DATA_PORT PORTE //data port 
#define COMM_DDR DDRF //command direction
#define COMM_PORT PORTF //command port
#define CMD_RS PF1 //instruction register, if command ->0, if data -> 1
#define CMD_RW PF2 //read/write, if write ->0, if read ->1
#define CMD_EN PF3 //enable
void lcd_init();
void lcd_senddata(int c);
void lcd_sendcommand(int c);
void clock();
void lcd_config();
void lcd_string(char *pointer);
void lcd_move(int column, int row);
void lcd_num(unsigned long number);

//Buzzer
void buzzer_on();
void buzzer_off();

//inits
void init();
void button_push();
void led_inner_d();
int number;
void segment_place(int place, int number);
void segment_write( int number);
int G_port_button();
void led_out(int led);

// CGRAM
void selectmyobject(int digit);
void Createmyobject00();

//UART
void UART_init();
void USART_Transmit(unsigned char data);
unsigned char USART_Receive(void);
void UART_string_Transmit(char *pointer);

//ADC
void ADC_init();
int ADC_read(int ch);

//RGB
void RGB_init();

//Timer
void Timer1_init();

//SPI
#define SPI_DDR DDRB //SPI Dirction
#define SPI_PORT PORTB //SPI port

#define SPI_SS PB0
#define SPI_SCK PB1
#define SPI_MOSI PB2
#define SPI_MISO PB3
#define SPI_CS PB4
#define CS_EN (SPI_PORT &=~(1<<SPI_CS))
#define CS_DIS (SPI_PORT |=(1<<SPI_CS))
#define MASTER 0
#define SLAVE 1
void SPI_init(int select);
void SPI_write(int input);
unsigned char SPI_read();

#endif
