/*
 * LCD.h
 *
 *  Created on: Jan 1, 2022
 *      Author: Diogo Rosinha
 */
#include <stdlib.h>
#include <math.h>

#ifndef LCD_H_
#define LCD_H_

#define D7 GPIO_PIN_0
#define D6 GPIO_PIN_1
#define D5 GPIO_PIN_2
#define D4 GPIO_PIN_3
#define EN GPIO_PIN_4
#define RS GPIO_PIN_5

void Lcd_Port(char a);
void Lcd_Cmd(char a);
void Lcd_Clear(void);
void Lcd_Set_Cursor(char a, char b);
void Lcd_Init(void);
void Lcd_Write_Char(char a);
void Lcd_Write_String(const char *a);
void Lcd_Shift_Right(void);
void Lcd_Shift_Left(void);
void Lcd_Write_Integer(int v);
void Lcd_Write_Float(float f);

#endif /* LCD_H_ */
