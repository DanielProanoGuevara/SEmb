//*****************************************************************************
//
// project0.c - Example to demonstrate minimal TivaWare setup
//
// Copyright (c) 2012-2017 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
// 
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
// 
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
// 
// This is part of revision 2.1.4.178 of the EK-TM4C123GXL Firmware Package.
//
//*****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_ints.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/fpu.h"
#include "driverlib/interrupt.h"
#include "driverlib/timer.h"
#include "driverlib/pwm.c"
#include "driverlib/pwm.h"
#include "LCD.h"
#include "KEYBOARD.h"

//*****************************************************************************
//
// Define pin to LED color mapping.
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup example_list
//! <h1>Project Zero (project0)</h1>
//!
//! This example demonstrates the use of TivaWare to setup the clocks and
//! toggle GPIO pins to make the LED's blink. This is a good place to start
//! understanding your launchpad and the tools that can be used to program it.
//
//*****************************************************************************

#define RED_LED   GPIO_PIN_1
#define BLUE_LED  GPIO_PIN_2
#define GREEN_LED GPIO_PIN_3
//*****************************************************************************
//
// The error routine that is called if the driver library encounters an error.
//
//*****************************************************************************
#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
}
#endif

//*****************************************************************************
//
// Main 'C' Language entry point.  Toggle an LED using TivaWare.
//
//*****************************************************************************
void pwm0_init()
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    GPIOPinConfigure(GPIO_PC4_M0PWM6);
    GPIOPinTypePWM(GPIO_PORTC_BASE, GPIO_PIN_4);
    PWMGenConfigure(PWM0_BASE, PWM_GEN_3, PWM_GEN_MODE_UP_DOWN | PWM_GEN_MODE_NO_SYNC);
}

void pwm0_start(unsigned long frequence, unsigned long duty_cycle)
{
    PWMGenPeriodSet(PWM0_BASE, PWM_GEN_3, SysCtlClockGet() / frequence);
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_6, (PWMGenPeriodGet(PWM0_BASE, PWM_GEN_3) * duty_cycle) / 100);
    PWMOutputState(PWM0_BASE, PWM_OUT_6_BIT, true);
    PWMGenEnable(PWM0_BASE, PWM_GEN_3);
}

int main(void){
    //
    // Setup the system clock to run at 50 Mhz from PLL with crystal reference
    //
    //FPUEnable();
    //FPULazyStackingEnable();
    SysCtlClockSet(SYSCTL_SYSDIV_1|SYSCTL_USE_OSC|SYSCTL_XTAL_16MHZ|
                    SYSCTL_OSC_MAIN);

    TimerConfigure(TIMER_CFG_*, TIMER_CFG_RTC);
    //
    // Enable and wait for the port to be ready for access
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))
    {
    }
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOE))
    {
    }
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOB))
    {
    }
    
    //
    // Configure the GPIO port for the LED operation.
    //
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, RED_LED|BLUE_LED|GREEN_LED);

    GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, D7|D6|D5|D4|EN|RS);

    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, R1|R2|R3|R4);

    GPIOPinTypeGPIOInput(GPIO_PORTB_BASE, C1|C2|C3|C4);

    // Ativate LEDS for debug

    GPIOPinWrite(GPIO_PORTF_BASE, GREEN_LED|RED_LED|BLUE_LED, GREEN_LED|RED_LED|BLUE_LED);

    SysCtlDelay(10000000);

    pwm0_init();

    Lcd_Init();

    Lcd_Clear();

    Lcd_Write_String("Hello World");

    GPIOPinWrite(GPIO_PORTF_BASE, GREEN_LED|RED_LED|BLUE_LED, BLUE_LED);

    SysCtlDelay(10000000);

    Lcd_Clear();

    char key;

    pwm0_start(1000, 40);

    while(1)
    {
        GPIOPinWrite(GPIO_PORTF_BASE, GREEN_LED|RED_LED|BLUE_LED, GREEN_LED);
        key = keypadScan();
        if (key != 'n')
        {
            Lcd_Clear();
            Lcd_Write_Char(key);
            GPIOPinWrite(GPIO_PORTF_BASE, GREEN_LED|RED_LED|BLUE_LED, RED_LED);
        }

        SysCtlDelay(20000);

    }
}
