/*
 * startup.c
 *
 *  Created on: 30 Dec 2021
 *      Author: Admin
 */


/*void start_I2C(){


}*/

void start_mcu(){

    /*perguntar aos outros caralhos o q eles vao inicializar*/

    RCGCI2C = 0x00000002;
    RCGCGPIO = 0x00000017;
    GPIOAFSEL = 0x40004023;
    GPIOAFSEL = 0x40004024;
    GPIOODR = 0x40004023;
    GPIOODR = 0x40004024;
    GPIOPCTL = 0X40004000;
    I2CMCR = 0x40020010
}
