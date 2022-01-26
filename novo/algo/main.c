#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "inc/hw_i2c.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "driverlib/i2c.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "inc/hw_ints.h"
#include "driverlib/pin_map.h"
#include "driverlib/interrupt.h"
#include "inc/tm4c123gh6pm.h"
#include "driverlib/hibernate.h"

#define TICKS_SENSOR_STBALIZE
#define TICKS_TO_WAIT 200


/**
 * main.c
 */

xSemaphoreHandle xSens_semaph;

int dist = 0, alarm = 0;

void Int_Keypad(){


}

int main(void){

    SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN |
                   SYSCTL_XTAL_16MHZ);

    int error_measure_dis = 1, error_demand_dis = 1, i, *data;

    IntEnable(INT_GPIOB_TM4C123);
    //IntPrioritySet(INT_GPION_TM4C123, escolher a prioridade);

    data = &dist;

    start_I2C();
    // vSemaphoreCreateBinary(xsens_semaph);

   // if( xsens_)

    while(1){
       //xSemaphoreTake(sensor_semaphore, TICKS_TO_WAIT);

       error_measure_dis =  measure_sonar();

       //SysCtlDelay(1600000);
       vTaskDelay(TICKS_SENSOR_STBALIZE);

       error_demand_dis = get_value_sonar(data);

       check_dis();
       i = 0;
    }

    return 0;
}

HibernateCalendarSet();
