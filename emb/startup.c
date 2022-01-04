/*
 * startup.c
 *
 *  Created on: 30 Dec 2021
 *      Author: Admin
 */

void measure_sonar{
    I2CMSA = 0x0000001C0;
    I2CMDR = 0x000000091;
    I2MCS = 0x000000007;

    while(!I2CMCS.BUSBSY);

    if(I2CMCS.ERROR == 1)
        return 1;

    return 0;
}

void get_value_sonar{
    I2CMSA = 0x0000001C2;
    I2MCS = 0x000000007;

    while(!I2CMCS.BUSBSY);

    if(I2CMCS.ERROR == 1)
        return 1;

    return 0;
}

void start_I2C(){

    /*perguntar aos outros caralhos o q eles vao inicializar*/

    RCGCI2C = 0x00000002;
    RCGCGPIO = 0x00000017;
    GPIOAFSEL = 0x40004023;
    GPIOAFSEL = 0x40004024;
    GPIOODR = 0x40004023;
    GPIOODR = 0x40004024;
    GPIOPCTL = 0X40004000;
    I2CMCR = 0x40020010
    I2CMTPR = 0x00000009;
}
