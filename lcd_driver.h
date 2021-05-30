#ifndef lcd_driver
#define lcd_driver
#include "tm4c123gh6pm.h"
#include <stdint.h>
void delay_micro(int n);
void lcd_cmd(uint8_t command);
void lcd_write_char(char digit);
void lcd_init(void);
void lcd_write_line(char *str);
void lcd_select_line(uint8_t line);
#endif
