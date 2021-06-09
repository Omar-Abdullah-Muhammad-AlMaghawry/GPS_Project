#include "lcd_driver.h"

//Delay code by n microseconds
void delay_micro(int n){
 int i,j;
 for(i=0;i<n;i++)
 for(j=0;j<3;j++)
 {}
}

//Send Command to the LCD
void lcd_cmd(uint8_t command){
	GPIOE->DATA = 0x04;
	delay_micro(500);
	GPIOB->DATA = command;
	delay_micro(500);
	GPIOE->DATA = 0x00;
	delay_micro(500);
	if(command < 4) delay_micro(2000);
	else delay_micro(40);
}

//Write a single character in the current position
void lcd_write_char(char digit){
	GPIOE->DATA = 0x05;
	delay_micro(500);
	GPIOB->DATA = digit;
	delay_micro(500);
	//GPIOE->DATA = 0x4;
	//delay_micro(500);
	GPIOE->DATA = 0x00;
	delay_micro(500);
}

//used once to initialize the LCD display
void lcd_init(void){	
	SYSCTL->RCGCGPIO |= 0x12;
	
	GPIOE->AMSEL &= 0x00; //using E as control output
	GPIOE->AFSEL &= 0x00;
	GPIOE->DIR |= 0xFF;
	GPIOE->DEN |= 0x7; //E0 -> RS, E1 -> R/W, E2 -> E
	
	GPIOB->AMSEL &= 0x00; //using B as LCD data output
	GPIOB->AFSEL &= 0x00;
	GPIOB->DIR |= 0xFF;
	GPIOB->DEN |= 0xFF;
	
	//LCD initialisation sequence
	lcd_cmd(0x38); //Use LCD 8-bit mode
	lcd_cmd(0x02); //Start LCD and initialize cursor location
	lcd_cmd(0x06); //Enable automatic shifting to the right of the current cursor locaition
	lcd_cmd(0x0F); //Turn on LCD display
	lcd_cmd(0x01); //Clear display
	//lcd_cmd(0x80); //Set cursor for first line 
}

//used to display a single character in the next digit on the lcd
void lcd_write_line(char *str){
	char i;
	for(i = 0; (str[i] != 0) && (i < 16); i++){
		lcd_write_char(str[i]);
	}
}

//Set which line receives the next output (character or string)
void lcd_select_line(uint8_t line){
	if(line == 1) lcd_cmd(0x80);
	else if(line == 2) lcd_cmd(0xC0);
	else if(line == 3) lcd_cmd(0x90);
	else if (line == 4) lcd_cmd(0xD0);
}

/*
int main(){
	lcd_cmd(0x01);
	//while(1){
		lcd_select_line(1);
		//delay_micro(500);
		lcd_write_line("Hello world");
		//delay_micro(500);
		lcd_select_line(2);
		//lcd_write_char('b');
		//delay_micro(500);
	//}
}*/
/*
void SystemInit(){
	lcd_init();
	main();
}*/
