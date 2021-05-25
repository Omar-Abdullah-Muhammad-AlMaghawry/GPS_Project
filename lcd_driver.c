#include "tm4c123gh6pm.h"
#include <stdint.h>
//TODO implement lcd_write, complete the startup sequence
void delay_micro(int n)
{
 int i,j;
 for(i=0;i<n;i++)
 for(j=0;j<3;j++)
 {}
 
}

void lcd_cmd(uint8_t command){
	GPIOE->DATA = 0;
	GPIOD->DATA = command;
	GPIOE->DATA = 0x8;
	delay_micro(0);
	if(command < 4) delay_micro(2000);
	else delay_micro(37);
}

void lcd_write_char(char digit){
	GPIOE->DATA = 0x1;
	GPIOD->DATA = digit;
	GPIOE->DATA |= 0x8;
	GPIOE->DATA = 0x0;
	delay_micro(0);
}

//used once to initialize the LCD display
void lcd_init(){	
	SYSCTL->RCGCGPIO |= 0x18;
	
	GPIOE->AMSEL &= 0x00; //using E as control output
	GPIOE->AFSEL &= 0x00;
	GPIOE->DIR |= 0xFF;
	GPIOE->DEN |= 0x7; //F0 -> RS, F1 -> R/W, F3 -> E
	
	GPIOD->AMSEL &= 0x00; //using D as LCD data output
	GPIOD->AFSEL &= 0x00;
	GPIOD->DIR |= 0xFF;
	GPIOD->DEN |= 0xFF;
	
	//LCD initialisation sequence
	lcd_cmd(0x38); //Use LCD 8-bit mode
	lcd_cmd(0x03); //Start LCD and initialize cursor location
	lcd_cmd(0x06); //Enable Automatic shifting right of the cursor when typing
	lcd_cmd(0x0F); //Turn on LCD display
}

//used to display a single character in the next digit on the lcd
void lcd_write(char *str){
	char i;
	for(i = 0; str[i] != 0; i++){
		lcd_write_char(str[i]);
	}
}

void lcd_select_line(uint8_t line){
	if(line == 1) lcd_cmd(0x80);
	else if(line == 2) lcd_cmd(0xC0);
}

int main(){
	
}
void SystemInit(){
	lcd_init();
	main();
}
