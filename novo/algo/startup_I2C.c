#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_i2c.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "driverlib/i2c.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "inc/tm4c123gh6pm.h"


/*#define RCGCI2C 0x400FE620
#define PRI2C 0x400FEA20
#define RCGCGPIO 0x400FE608
#define PRGPIO 0x400FEA08
#define GPIOAFSEL 0x40004420
#define GPIODEN 0x4000451C
#define GPIOODR 0x4000450C
#define GPIOPCTL 0x4000452C
#define I2CMCR 0x40021020
#define I2CMTPR 0x4002100C
#define I2CMSA 0x40021000
#define I2CMDR 0x40021008
#define I2CMCS 0x40021004*/

/*
 * startup.c
 *
 *  Created on: 30 Dec 2021
 *      Author: Admin
 */

int measure_sonar(){
    uint8_t sense_address = 0x70, data = 0x51;

    I2CMasterSlaveAddrSet(I2C1_BASE, sense_address, false);

    I2CMasterDataPut(I2C1_BASE, data);

    I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_SINGLE_SEND);
    while(I2CMasterBusy(I2C1_BASE));
    if(I2CMasterErr())
        return -1;

    return 1;
}

int get_value_sonar(int *int_data){
    int aux;
    uint8_t sense_address = 0x70;

    I2CMasterSlaveAddrSet(I2C1_BASE, sense_address, true);

    I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_RECEIVE_START );
    while(I2CMasterBusy(I2C1_BASE));
    if(I2CMasterErr())
        return -1;

    aux = (int)I2CMasterDataGet(I2C1_BASE) * 1000;

    I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_RECEIVE_FINISH);
    while(I2CMasterBusy(I2C1_BASE));
    if(I2CMasterErr())
        return -1;

    *int_data = (int)I2CMasterDataGet(I2C1_BASE) + aux;

    return 1;
}

void start_I2C(){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C1);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_I2C1));

    SysCtlPeripheralReset(SYSCTL_PERIPH_I2C1);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_I2C1));

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA));

    GPIOPinConfigure(GPIO_PA6_I2C1SCL);
    GPIOPinConfigure(GPIO_PA7_I2C1SDA);
    GPIOPinTypeGPIOOutputOD(GPIO_PORTA_BASE, GPIO_PIN_6|GPIO_PIN_7);

    GPIOPinTypeI2CSCL(GPIO_PORTA_BASE, GPIO_PIN_6);
    GPIOPinTypeI2C(GPIO_PORTA_BASE, GPIO_PIN_7);

    I2CMasterInitExpClk(I2C1_BASE, SysCtlClockGet(), false);
}

void check_dis(){
    if(dist < limit){
        flag_dist = 0;
        xSemaphoreGive(semaphore_alarm);
        xSemaphoreTake(semaphore_wait_alarm, portMAX_DELAY);
    }
}
