#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/tm4c123gh6pm.h"
#define GPTMCTL 0x400300C0
#define GPTMTAMR 0x40030004
#define GPTMCFG 0x400300004
#define RCGCTIMER 0x400FE604
#define GPTMTAMATCHR 0x40030030


void enable_RTC(){
    /*GPTMCTL = 0x00;
    GPTMTAMR = 0x000;
    GPTMCFG = 0x1;*/


}
