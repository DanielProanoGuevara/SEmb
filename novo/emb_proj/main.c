#include <stdint.h>
#include <stdbool.h>
#include "start_I2C.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "inc/tm4c123gh6pm.h"


/**
 * main.c
 */

int main(void){
    SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

    int teste_1 = 0, teste_2 = 0, i = 0;

    start_I2C();

    while(1){
       teste_1 = measure_sonar();

       while(i<4000){
           i++;
       }

       //teste_2 = get_value_sonar();
    }

    return 0;
}
