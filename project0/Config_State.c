
#include "System.h"

void Config_init(void){
    GPIOPinWrite(GPIO_PORTF_BASE, GREEN_LED|RED_LED|BLUE_LED, GREEN_LED|BLUE_LED);

    Lcd_Write_String("Configuration State");
    SysCtlDelay(3000000);
}

void Get_Date(char *DateArray){
    GPIOPinWrite(GPIO_PORTF_BASE, GREEN_LED|RED_LED|BLUE_LED, GREEN_LED);
    int i=0;
    char key;

    Lcd_Write_String("Enter date, B resets");
    SysCtlDelay(3000000);

    Lcd_Write_String("DD-MM-YYYY");
    SysCtlDelay(3000000);

    while(i < 8)
    {
        GPIOPinWrite(GPIO_PORTF_BASE, GREEN_LED|RED_LED|BLUE_LED, GREEN_LED);
        key = keypadScan();
        if (key != 'n')
        {
            GPIOPinWrite(GPIO_PORTF_BASE, GREEN_LED|RED_LED|BLUE_LED, RED_LED);

            DateArray[i] = key;
            Lcd_Write_Char(key);

            if(i == 1|| i == 3) Lcd_Write_Char('-');
            i++;

            if(key == 'B'){
                for ( i = 0; i < 8; ++i) {
                    DateArray[i] = 0;
                }
                i=0;
            }
         }
    }
}

void Get_Time(char *TimeArray){
    GPIOPinWrite(GPIO_PORTF_BASE, GREEN_LED|RED_LED|BLUE_LED, BLUE_LED);
    int i=0;
    char key;

    Lcd_Write_String("Enter time, B resets");
    SysCtlDelay(1000000);

    Lcd_Write_String("hh:mm:ss ");
    SysCtlDelay(1000000);

    while(i < 6)
    {
        GPIOPinWrite(GPIO_PORTF_BASE, GREEN_LED|RED_LED|BLUE_LED, BLUE_LED);
        key = keypadScan();
        if (key != 'n')
        {
            GPIOPinWrite(GPIO_PORTF_BASE, GREEN_LED|RED_LED|BLUE_LED, RED_LED);

            TimeArray[i] = key;
            Lcd_Write_Char(key);

            if(i == 1|| i == 3) Lcd_Write_Char('-');
            i++;

            if(key == 'B'){
                for ( i = 0; i <6; ++i) {
                    TimeArray[i] = 0;
                }
                i=0;
            }
        }
    }
    HibernateRTCSet(0);
}

void Set_PIN(char *PIN){
    GPIOPinWrite(GPIO_PORTF_BASE, GREEN_LED|RED_LED|BLUE_LED, GREEN_LED);
    int i=0;
    char key;

    Lcd_Write_String("Enter PIN, B resets");
    SysCtlDelay(1000000);

    Lcd_Write_String("**** ");
    SysCtlDelay(1000000);

    while(i < 4)
    {
        GPIOPinWrite(GPIO_PORTF_BASE, GREEN_LED|RED_LED|BLUE_LED, GREEN_LED);
        key = keypadScan();
        if (key != 'n')
        {
            GPIOPinWrite(GPIO_PORTF_BASE, GREEN_LED|RED_LED|BLUE_LED, RED_LED);

            PIN[i] = key;
            Lcd_Write_Char(key);

            i++;

            if(key == 'B'){
                for ( i = 0; i < 4; ++i) {
                    PIN[i] = 0;
                }
                i=0;
            }
         }
    }
}
int Set_Distance(void){
    GPIOPinWrite(GPIO_PORTF_BASE, GREEN_LED|RED_LED|BLUE_LED, BLUE_LED);
    int i=0;
    char key;
    char distance[3];

    Lcd_Write_String("Set off alarm dist");
    SysCtlDelay(1000000);

    Lcd_Write_String("in *** cm, ");
    SysCtlDelay(1000000);

    while(i < 3)
    {
        GPIOPinWrite(GPIO_PORTF_BASE, GREEN_LED|RED_LED|BLUE_LED, BLUE_LED);
        key = keypadScan();
        if (key != 'n')
        {
            GPIOPinWrite(GPIO_PORTF_BASE, GREEN_LED|RED_LED|BLUE_LED, RED_LED);

            distance[i] = key;
            Lcd_Write_Char(key);

            i++;
            if(key == 'B'){
                for ( i = 0; i < 3; ++i) {
                    distance[i] = 0;
                }
                i=0;
            }

         }
      }
      int intDistance = atoi(distance);
      return intDistance;
}

int Set_Timeout(void){
    GPIOPinWrite(GPIO_PORTF_BASE, GREEN_LED|RED_LED|BLUE_LED, GREEN_LED);
    int i=0;
    char key;
    char timeout[2];

    Lcd_Write_String("Enter Timeout time");
    SysCtlDelay(1000000);

    Lcd_Write_String("in s, B resets, ");
    SysCtlDelay(1000000);

    while(i < 2)
    {
        GPIOPinWrite(GPIO_PORTF_BASE, GREEN_LED|RED_LED|BLUE_LED, GREEN_LED);
        key = keypadScan();
        if (key != 'n')
        {
            GPIOPinWrite(GPIO_PORTF_BASE, GREEN_LED|RED_LED|BLUE_LED, RED_LED);

            timeout[i] = key;
            Lcd_Write_Char(key);

            i++;
            if(key == 'B'){
                for ( i = 0; i < 2; ++i) {
                    timeout[i] = 0;
                }
                i=0;
            }

         }
      }
      int intTimeout = atoi(timeout);
      return intTimeout;
}


