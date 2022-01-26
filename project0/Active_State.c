///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* Project for the subject ESEMb, made by Diogo Rodrigues nº94240, Daniel Proanho nº101229, and Miguel Fernandes nº93790
 *
 *This file is the Active_State.c, this file was created to keep the main.c file clean and short.
 *
 *In this file we have alarm_Triggered(), check_PIN(), Active_State().
 *
 *This file has the possibility to become a task by itself.
 *
 *A more detailed description of the functions will be in the overhead of the functions.
 */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "System.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* void alarm_Triggered(int * alarm_armed);
 *
 * This function was made to keep the Active_State() a little cleaner and maybe this function can be used in another setting.
 *
 * It was made to handle the count down in case the alarm was triggered to give time to the user to input the correct PIN to disarm
 * the alarm. In case this is not done in time the Buzzer will start ringing and it will stay locked in line 40 until the alarm is disarm
 * in Beacon State (state 2) also blocking the access to the other functionalities of Active State.
 *
 * For the count down we use the RTC, we //give a fixed value to n2 (0 seconds) and// update n1 with the time that has passed since the
 * end of line 34, if we subtract 15 with that value we will have a count down of 15 seconds, n3 is there so that the display only shows when n1 changes
 * value.
 */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void alarm_Triggered(int * alarm_armed){
    int n1, n3; //n2
    Lcd_Write_String("ALARM TRIGGERED!");
    SysCtlDelay(40000);
    Lcd_Write_String("ALARM TRIGGERED!");
    SysCtlDelay(40000);
    HibernateRTCSet(0);
    //n2 = HibernateRTCGet(); // if the HibernateRTCSet(0); only works once in the Init_System.c uncomment this line and erase line 35
    n3 = 0;
    while(n3 < 15 && *alarm_armed == TRUE){
        n1 = HibernateRTCGet();
        if(n3 != n1){
            //n3 = n1 - n2;
            Lcd_Clear();
            Lcd_Write_Integer((15-n1));
            n3 = n1;
        }
    }
    if(*alarm_armed == TRUE){
        pwm0_start(1000, 60);
        while(*alarm_armed == TRUE){}
        Lcd_Write_String("ALARM DISARMED2!");
        SysCtlDelay(40000);
    }
    return;
}

int check_PIN (int PIN){
    char key;
    int PIN_Comparator;
    while(1)
    {
       PIN_Comparator = Set_PIN();

       if(PIN == PIN_Comparator){
           Lcd_Write_String("PIN is correct");
           SysCtlDelay(300000);
           return 6;
       }
       Lcd_Write_String("Wrong PIN");
       SysCtlDelay(300000);
       Lcd_Write_String("A to repeat");
       SysCtlDelay(300000);
       Lcd_Write_String("B to exit");
       SysCtlDelay(300000);
       Lcd_Clear();
       while(1)
       {
           key = keypadScan();
           if (key != 'n')
           {
               if(key == 'A') break;

               if(key == 'B') return 0;
           }
       }

    }
}

void Active_state(int PIN, int * alarm_armed, int trigger_distance, int * state){
    Lcd_Write_String("Active State");
    SysCtlDelay(100000);

    while(1){
        GPIOPinWrite(GPIO_PORTF_BASE, GREEN_LED|RED_LED|BLUE_LED, RED_LED|GREEN_LED);
        char key;
        int *data, dist;
        data = &dist;
        Lcd_Write_String("F to config again");
        SysCtlDelay(700000);
        Lcd_Write_String("E to display time");
        SysCtlDelay(700000);
        Lcd_Write_String("D to display alarm");
        SysCtlDelay(700000);
        Lcd_Write_String("C to arm/disarm");
        SysCtlDelay(700000);
        Lcd_Write_String("B to read again");
        SysCtlDelay(700000);

        while(1)
        {
            // Keep updating distance in idle mode
            measure_sonar();
            if(get_value_sonar(data) == 0){
                //Lcd_Write_String("TOO FAR AWAY ");
            }else{
                Lcd_Write_Integer(dist);
                Lcd_Write_Char('c');
                Lcd_Write_Char('m');
            }
            if(dist <= trigger_distance && *alarm_armed == TRUE){
                *state = 2;
                alarm_Triggered(alarm_armed);
            }
            key = keypadScan();
            if (key != 'n') break;
        }

        switch(key)
        {
            case 'F':
                *state = 0;
                return;

            case 'E':

                break;

            case 'D':
                Lcd_Write_String("Work in progress");
                SysCtlDelay(1000000);
                break;

            case 'C':
                if(*alarm_armed == TRUE){

                    Lcd_Write_String("The alarm is armed");
                    SysCtlDelay(300000);
                    Lcd_Write_String("The PIN is needed");
                    SysCtlDelay(300000);
                    Lcd_Write_String("to disarm the alarm");
                    SysCtlDelay(300000);

                    if (check_PIN(PIN) == 0){
                        Lcd_Write_String("since PIN was wrong");
                        SysCtlDelay(300000);
                        Lcd_Write_String("exiting function");
                        SysCtlDelay(300000);
                        return;
                    }

                    Lcd_Write_String("A to disarm alarm");
                    SysCtlDelay(300000);
                    Lcd_Write_String("B to return");
                    SysCtlDelay(300000);
                    while(1)
                    {
                        key = keypadScan();
                        if (key != 'n')
                        {
                            if(key == 'B') break;

                            if(key == 'A') *alarm_armed = FALSE;
                        }
                    }
                }else{

                    Lcd_Write_String("Alarm is disarmed");
                    SysCtlDelay(300000);
                    Lcd_Write_String("The PIN is needed");
                    SysCtlDelay(300000);
                    Lcd_Write_String("to arm the alarm");
                    SysCtlDelay(300000);

                    if (check_PIN(PIN) == 0){
                        Lcd_Write_String("since PIN was wrong");
                        SysCtlDelay(300000);
                        Lcd_Write_String("exiting function");
                        SysCtlDelay(300000);
                        return;
                    }

                     Lcd_Write_String("A to arm the alarm");
                     SysCtlDelay(300000);
                     Lcd_Write_String("B to return");
                     SysCtlDelay(300000);
                     while(1)
                     {
                         key = keypadScan();
                         if (key != 'n')
                         {
                             if(key == 'B') break;

                             if(key == 'A') *alarm_armed = TRUE;
                         }
                     }
                }
                break;

            default:
                Lcd_Write_String("ERROR DEFAULT");
                return;
        }
    }
}
