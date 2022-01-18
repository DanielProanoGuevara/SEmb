/*
 * KEYBOARD.h
 *
 *  Created on: Jan 13, 2022
 *      Author: diogo
 */

#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#define R4 GPIO_PIN_0
#define R3 GPIO_PIN_1
#define R2 GPIO_PIN_2
#define R1 GPIO_PIN_3
#define C4 GPIO_PIN_4
#define C3 GPIO_PIN_5
#define C2 GPIO_PIN_6
#define C1 GPIO_PIN_7

char keypadScan(void);

#endif /* KEYBOARD_H_ */
