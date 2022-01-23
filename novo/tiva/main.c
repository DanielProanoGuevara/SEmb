#include <stdint.h>
#include <stdbool.h>
#include "startup.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"


/**
 * main.c
 */

void delayMs(uint32_t ui32Ms) {

    // 1 clock cycle = 1 / SysCtlClockGet() second
    // 1 SysCtlDelay = 3 clock cycle = 3 / SysCtlClockGet() second
    // 1 second = SysCtlClockGet() / 3
    // 0.001 second = 1 ms = SysCtlClockGet() / 3 / 1000

    SysCtlDelay(ui32Ms * (SysCtlClockGet() / 3 / 1000));
}

void delayUs(uint32_t ui32Us) {
    SysCtlDelay(ui32Us * (SysCtlClockGet() / 3 / 1000000));
}

int main(void)
{

    int teste_1 = 0, teste_2 = 0;

    start_I2C();

    while(1){
       teste_1 = measure_sonar();
       delayMs(1000);
       teste_2 = get_value_sonar();
    }

    return 0;
}
