/*
 * Init_System.h
 *
 *  Created on: Jan 20, 2022
 *      Author: diogo
 */

#ifndef SYSTEM_H_
#define SYSTEM_H_

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include "inc/hw_i2c.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_ints.h"
#include "driverlib/i2c.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/hibernate.h"


/////////////////////////////////////////////////////////////////////////////

// INICIATE THE SYSTEM

/////////////////////////////////////////////////////////////////////////////

#define RED_LED   GPIO_PIN_1
#define BLUE_LED  GPIO_PIN_2
#define GREEN_LED GPIO_PIN_3
#define TRUE 1
#define FALSE 0

void init_system(void);

/////////////////////////////////////////////////////////////////////////////

// LCD

////////////////////////////////////////////////////////////////////////////

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
void Lcd_Write_Integer(long v);

///////////////////////////////////////////////////////////////////////////////

// KEYBOARD

//////////////////////////////////////////////////////////////////////////////

#define R4 GPIO_PIN_0
#define R3 GPIO_PIN_1
#define R2 GPIO_PIN_2
#define R1 GPIO_PIN_3
#define C4 GPIO_PIN_4
#define C3 GPIO_PIN_5
#define C2 GPIO_PIN_6
#define C1 GPIO_PIN_7

char keypadScan(void);

/////////////////////////////////////////////////////////////////////////////

// PWM

/////////////////////////////////////////////////////////////////////////////

void pwm0_init(void);

void pwm0_start(unsigned long frequence, unsigned long duty_cycle);

void pwm0_stop();

////////////////////////////////////////////////////////////////////////////

// CONFIG STATE

///////////////////////////////////////////////////////////////////////////

void Config_init(void);

void DateTimeSet(void);

void Get_Date(uint32_t *ui32Year, uint32_t *ui32Month, uint32_t *ui32Day);

void Get_Time(uint32_t *ui32Hour, uint32_t *ui32Min, uint32_t *ui32Sec);

int Set_PIN(void);

int Set_Distance(void);

int Set_Timeout(void);

////////////////////////////////////////////////////////////////////////////

// ATIVE STATE

////////////////////////////////////////////////////////////////////////////

void alarm_Triggered(int * alarm_armed);

int check_PIN (int PIN);

void Active_state(int PIN, int * alarm_armed, int trigger_distance, int * state);

////////////////////////////////////////////////////////////////////////////

// I2C & ULTRASONIC SENSOR

///////////////////////////////////////////////////////////////////////////

void measure_sonar();

int get_value_sonar();

void start_I2C();

///////////////////////////////////////////////////////////////////////////

#endif /* SYSTEM_H_ */
