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
#include "driverlib/pin_map.h"
#include "inc/tm4c123gh6pm.h"

#define TICKS_TO_WAIT 200


/**
 * main.c
 */

int dist = 0, alarm = 0;

int main(void){

    SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN |
                   SYSCTL_XTAL_16MHZ);

    int error_measure_dis = 1, error_demand_dis = 1, i, *data;

    data = &dist;

    start_I2C();

    while(1){
       //xSemaphoreTake(sensor_semaphore, TICKS_TO_WAIT);

       error_measure_dis =  measure_sonar();

       SysCtlDelay(39063);

       error_demand_dis = get_value_sonar(data);

       check_dis(dist);
       i = 0;
    }

    return 0;
}
