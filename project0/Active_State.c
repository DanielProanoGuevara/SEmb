#include "System.h"

int Active_state(char * DateArray, char * TimeArray, char * PIN, int alarm_armed){
    Lcd_Write_String("Active State");
    SysCtlDelay(10000000);
    while(1){
        GPIOPinWrite(GPIO_PORTF_BASE, GREEN_LED|RED_LED|BLUE_LED, RED_LED|BLUE_LED);
        int key;

        Lcd_Write_String("F to Config again");
        SysCtlDelay(1500000);
        Lcd_Write_String("E to display time");
        SysCtlDelay(1500000);
        Lcd_Write_String("D to display alarm");
        SysCtlDelay(1500000);
        Lcd_Write_String("C to arm/disarm");
        SysCtlDelay(1500000);
        Lcd_Write_String("B to read again");
        while(1){
            // check distance work in progress
            key = keypadScan();
            if (key != 'n') break;
        }
        switch(key)
        {
            case 'F':
                return 0;
            case 'E':
                GPIOPinWrite(GPIO_PORTF_BASE, GREEN_LED|RED_LED|BLUE_LED, RED_LED);

                Lcd_Write_String(DateArray);
                SysCtlDelay(10000000);

                Lcd_Write_String(TimeArray);
                SysCtlDelay(10000000);
            case 'D':
                GPIOPinWrite(GPIO_PORTF_BASE, GREEN_LED|RED_LED|BLUE_LED, RED_LED|BLUE_LED|GREEN_LED);

                Lcd_Write_String("Work in progress");
                SysCtlDelay(10000000);
            case 'C':
                GPIOPinWrite(GPIO_PORTF_BASE, GREEN_LED|RED_LED|BLUE_LED, BLUE_LED);
                if(alarm_armed == TRUE){

                    Lcd_Write_String("The alarm is armed");
                    SysCtlDelay(3000000);

                    Lcd_Write_String("The PIN is needed");
                    SysCtlDelay(3000000);

                    Lcd_Write_String("to disarm the alarm");
                    SysCtlDelay(3000000);
                    char PIN_Comparator[4];
                    while(1)
                    {
                       Set_PIN(PIN_Comparator);

                       if(strcmp (PIN, PIN_Comparator) == 0){

                           Lcd_Write_String("PIN is correct");
                           SysCtlDelay(3000000);
                           break;
                       }
                       Lcd_Write_String("Wrong PIN");
                       SysCtlDelay(3000000);
                       while(1)
                       {

                           Lcd_Write_String("A to repeat");
                           SysCtlDelay(3000000);

                           Lcd_Write_String("B to return");
                           SysCtlDelay(3000000);
                           key = keypadScan();
                           if (key != 'n')
                           {
                               if(key == 'A') break;

                               if(key == 'B') return 3;
                           }
                       }

                    }

                    Lcd_Write_String("A to disarm alarm");
                    SysCtlDelay(3000000);

                    Lcd_Write_String("B to return");
                    SysCtlDelay(3000000);
                    while(1)
                    {
                        key = keypadScan();
                        if (key != 'n')
                        {
                            if(key == 'B') break;

                            if(key == 'A') return 1;
                        }
                    }
                }else{

                    Lcd_Write_String("Alarm is disarmed");
                    SysCtlDelay(3000000);

                    Lcd_Write_String("The PIN is needed");
                    SysCtlDelay(3000000);

                    Lcd_Write_String("to arm the alarm");
                    SysCtlDelay(3000000);
                    char PIN_Comparator[4];
                    while(1)
                    {
                        Set_PIN(PIN_Comparator);

                        if(strcmp (PIN, PIN_Comparator) == 0)
                        {

                            Lcd_Write_String("PIN is correct");
                            SysCtlDelay(3000000);
                            break;
                        }
                        Lcd_Write_String("Wrong PIN");
                        SysCtlDelay(3000000);
                        while(1)
                        {

                            Lcd_Write_String("A to repeat");
                            SysCtlDelay(3000000);

                            Lcd_Write_String("B to return");
                            SysCtlDelay(3000000);
                            key = keypadScan();
                            if (key != 'n')
                            {
                                if(key == 'A') break;

                                if(key == 'B') return 3;
                            }
                         }

                     }

                     Lcd_Write_String("A to arm the alarm");
                     SysCtlDelay(3000000);

                     Lcd_Write_String("B to return");
                     SysCtlDelay(3000000);
                     while(1)
                     {
                         key = keypadScan();
                         if (key != 'n')
                         {
                             if(key == 'B') break;

                             if(key == 'A') return 2;
                         }
                     }
                }
            default:
                key = 'n';
        }
    }
}
