#include "System.h"
#include "driverlib/pwm.c"
#include "driverlib/pwm.h"

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
void pwm0_stop()
{
    PWMOutputState(PWM0_BASE, PWM_OUT_6_BIT, false);
}



