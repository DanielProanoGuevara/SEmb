
#include"System.h"

char keypadScan(){
  //Scan 1st row
  //r1 = 1; r2 = 0; r3 = 0; r4 = 0;
  GPIOPinWrite(GPIO_PORTB_BASE, R1|R2|R3|R4, R1);
  // Read columns
  if (GPIOPinRead(GPIO_PORTB_BASE, C1) == C1){SysCtlDelay(200000); while(GPIOPinRead(GPIO_PORTB_BASE, C1) == C1); SysCtlDelay(200000); return '1';}
  if (GPIOPinRead(GPIO_PORTB_BASE, C2) == C2){SysCtlDelay(200000); while(GPIOPinRead(GPIO_PORTB_BASE, C2) == C2); SysCtlDelay(200000); return '2';}
  if (GPIOPinRead(GPIO_PORTB_BASE, C3) == C3){SysCtlDelay(200000); while(GPIOPinRead(GPIO_PORTB_BASE, C3) == C3); SysCtlDelay(200000); return '3';}
  if (GPIOPinRead(GPIO_PORTB_BASE, C4) == C4){SysCtlDelay(200000); while(GPIOPinRead(GPIO_PORTB_BASE, C4) == C4); SysCtlDelay(200000); return 'F';}
  //Scan 2nd row
  //r1 = 0; r2 = 1; r3 = 0; r4 = 0;
  GPIOPinWrite(GPIO_PORTB_BASE, R1|R2|R3|R4, R2);
  // Read columns
  if (GPIOPinRead(GPIO_PORTB_BASE, C1) == C1){SysCtlDelay(200000); while(GPIOPinRead(GPIO_PORTB_BASE, C1) == C1); SysCtlDelay(200000); return '4';}
  if (GPIOPinRead(GPIO_PORTB_BASE, C2) == C2){SysCtlDelay(200000); while(GPIOPinRead(GPIO_PORTB_BASE, C2) == C2); SysCtlDelay(200000); return '5';}
  if (GPIOPinRead(GPIO_PORTB_BASE, C3) == C3){SysCtlDelay(200000); while(GPIOPinRead(GPIO_PORTB_BASE, C3) == C3); SysCtlDelay(200000); return '6';}
  if (GPIOPinRead(GPIO_PORTB_BASE, C4) == C4){SysCtlDelay(200000); while(GPIOPinRead(GPIO_PORTB_BASE, C4) == C4); SysCtlDelay(200000); return 'E';}
  //Scan 3rd row
  //r1 = 0; r2 = 0; r3 = 1; r4 = 0;
  GPIOPinWrite(GPIO_PORTB_BASE, R1|R2|R3|R4, R3);
  // Read columns
  if (GPIOPinRead(GPIO_PORTB_BASE, C1) == C1){SysCtlDelay(200000); while(GPIOPinRead(GPIO_PORTB_BASE, C1) == C1); SysCtlDelay(200000); return '7';}
  if (GPIOPinRead(GPIO_PORTB_BASE, C2) == C2){SysCtlDelay(200000); while(GPIOPinRead(GPIO_PORTB_BASE, C2) == C2); SysCtlDelay(200000); return '8';}
  if (GPIOPinRead(GPIO_PORTB_BASE, C3) == C3){SysCtlDelay(200000); while(GPIOPinRead(GPIO_PORTB_BASE, C3) == C3); SysCtlDelay(200000); return '9';}
  if (GPIOPinRead(GPIO_PORTB_BASE, C4) == C4){SysCtlDelay(200000); while(GPIOPinRead(GPIO_PORTB_BASE, C4) == C4); SysCtlDelay(200000); return 'D';}
  //Scan 4th row
  //r1 = 0; r2 = 0; r3 = 0; r4 = 1;
  GPIOPinWrite(GPIO_PORTB_BASE, R1|R2|R3|R4, R4);
  // Read columns
  if (GPIOPinRead(GPIO_PORTB_BASE, C1) == C1){SysCtlDelay(200000); while(GPIOPinRead(GPIO_PORTB_BASE, C1) == C1); SysCtlDelay(200000); return 'A';}
  if (GPIOPinRead(GPIO_PORTB_BASE, C2) == C2){SysCtlDelay(200000); while(GPIOPinRead(GPIO_PORTB_BASE, C2) == C2); SysCtlDelay(200000); return '0';}
  if (GPIOPinRead(GPIO_PORTB_BASE, C3) == C3){SysCtlDelay(200000); while(GPIOPinRead(GPIO_PORTB_BASE, C3) == C3); SysCtlDelay(200000); return 'B';}
  if (GPIOPinRead(GPIO_PORTB_BASE, C4) == C4){SysCtlDelay(200000); while(GPIOPinRead(GPIO_PORTB_BASE, C4) == C4); SysCtlDelay(200000); return 'C';}
  return 'n'; //n for "not pressed"
  }


