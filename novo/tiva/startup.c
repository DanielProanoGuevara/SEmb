#include <stdint.h>
#include <stdbool.h>
#include "startup.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#define RCGCI2C 0x400FE620
#define PRI2C 0x400FEA08
#define RCGCGPIO 0x400FE620
#define PRGPIO 0x400FEA08
#define GPIOAFSEL 0x40004420
#define GPIODEN 0x4000451C
#define GPIOODR 0x4000450C
#define GPIOPCTL 0x4000452C
#define I2CMCR 0x40021020
#define I2CMTPR 0x4002100C
#define I2CMSA 0x40021000
#define I2CMDR 0x40021008
#define I2CMCS 0x40021004

/*
 * startup.c
 *
 *  Created on: 30 Dec 2021
 *      Author: Admin
 */

int measure_sonar(){
    volatile uint32_t control_I2C = (*(volatile uint32_t*)(I2CMCS));
    uint8_t sense_address = 0xE0;
    uint8_t data = 0x91;

    *(volatile uint32_t*)(I2CMSA) = sense_address << 1;
    *(volatile uint32_t*)(I2CMDR) = data;
    *(volatile uint32_t*)(I2CMCS) |= 0x07;

    while(!(control_I2C & 0x1));

    /*if(I2CMCS.ERROR == 1)
        return 1;*/

    return 0;
}

int get_value_sonar(){
    volatile uint32_t control_I2C = (*(volatile uint32_t*)(I2CMCS));
    uint8_t read_address_1 = 0xE1;
    uint8_t read_address_2 = (read_address_1 |= 0x000000003);
    //uint8_t dummies = 0x00;

    /**(volatile uint32_t*)(I2CMSA) = read_address_1 << 1; //Mete pra mandar
    *(volatile uint32_t*)(I2CMDR) = dummies; //dumies
    *(volatile uint32_t*)(I2CMCS) |= 0x07; //Manda*/
    *(volatile uint32_t*)(I2CMSA) |= read_address_2; //Mete pra receber
    *(volatile uint32_t*)(I2CMCS) |= 0x7; //recebe

    while(!(control_I2C & 0x1));

    /*if((control_I2C & 0x2)==1)
        return 0;
        //return 0x000000000;*/

    return 1;
    //return msg_rx;
}

void start_I2C(){
    volatile uint32_t wait_RCGCI2C = (*(volatile uint32_t*)(PRI2C));
    volatile uint32_t wait_RCGCGPIO = (*(volatile uint32_t*)(PRGPIO));

    /*perguntar aos outros caralhos o q eles vao inicializar*/

    *(volatile uint32_t*)(RCGCI2C) = 0x2;
    while(!(wait_RCGCI2C & 0x2));

    *(volatile uint32_t*)(RCGCGPIO) = 0x1;
    while(!(wait_RCGCGPIO & 0x1));

    *(volatile uint32_t*)(GPIOAFSEL) |= 0x000000C0;
    *(volatile uint32_t*)(GPIODEN) |= 0x000000C0;
    *(volatile uint32_t*)(GPIOODR) |= 0x000000C0;
    *(volatile uint32_t*)(GPIOPCTL) |= 0x33000000;
    *(volatile uint32_t*)(I2CMCR) |= 0x00000010;
    *(volatile uint32_t*)(I2CMTPR) = 0x00000009;
}
