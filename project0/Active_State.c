/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* Project for the subject SEmb, made by Diogo Rodrigues nº94240, Daniel Proanho nº101229, and Miguel Fernandes nº93790
 *
 * This file is the Active_State.c, this file was created to keep the main.c file clean and short.
 *
 * In this file we have alarm_Triggered(), check_PIN(), Active_State().
 *
 * This file has the possibility to become a task by itself.
 *
 * A more detailed description of the functions will be in the overhead of the functions.
 */
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "System.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* void alarm_Triggered(int * alarm_armed);
 *
 * This function was made to keep the Active_State() a little cleaner and maybe this function can be used in another setting.
 *
 * It was made to handle the count down in case the alarm was triggered to give time to the user to input the correct PIN to disarm
 * the alarm. In case this is not done in time the Buzzer will start ringing and it will stay locked in line 49 until the alarm is disarm
 * in Beacon State (state 2) also blocking the access to the other functionalities of Active State.
 *
 * For the count down we use the RTC, we give a fixed value to n2  and update n1 with the time that has passed since the
 * end of line 36, if we subtract 15 with n1 - n2 we will have a count down of 15 seconds, n3 is there so that the display only shows
 * when n1 changes value and for the n1-n2 subtraction.
 */
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void alarm_Triggered(int * alarm_armed){
    int n1, n2, n3, i;
    Lcd_Write_String("ALARM TRIGGERED!");
    SysCtlDelay(40000);
    Lcd_Write_String("ALARM TRIGGERED!");
    SysCtlDelay(40000);
    n2 = HibernateRTCGet();
    n3 = 0;
    i = 0;
    while(i < 15 && *alarm_armed == TRUE){
        n1 = HibernateRTCGet();
        if(n3 != n1){
            n3 = n1 - n2;
            Lcd_Clear();
            Lcd_Write_Integer((15-n3));
            n3 = n1;
            i++;
        }
    }
    if(*alarm_armed == TRUE){
        pwm0_start(1000, 60);
        update_Trigger_Date_Time();
        return;
        //while(*alarm_armed == TRUE){}
        Lcd_Write_String("ALARM DISARMED2!");
        SysCtlDelay(40000);
    }
    return;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* void update_Date_Time(void);
 *
 * This function was made to update the Date and Time when called. We use the seconds since the last update or when it was set up for the
 * calculate of change in the Date and Time values. We divide by the each one for the time of one year, month, etc... when the value is
 * bigger than the accept value (ex one month has a max of 31 days) we subtracted until we can calculate the  accepted value.
 * After this the RTC clock is reseted to count from 0, so since this change has occurred.
 */
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void update_Date_Time(void){
    uint32_t ui32Year, ui32Month, ui32Day, ui32Hour, ui32Min, ui32Sec;
    ui32Day = sTime.tm_mday;
    ui32Month = sTime.tm_mon;
    ui32Year = sTime.tm_year;
    ui32Year = ui32Year - 100;
    ui32Hour = sTime.tm_hour;
    ui32Min = sTime.tm_min;
    ui32Sec = sTime.tm_sec;


    int time = HibernateRTCGet();
    ui32Year = ui32Year + time/961848000;

    if((time/2635200) > 12){
        while((time/2635200) > 12) time = time - 961848000;
    }
    ui32Month = ui32Month + time/2635200;
    if(ui32Month > 12) ui32Month = ui32Month - 12;

    if((time/84600) > 31){
        while((time/84600) > 31) time = time - 2635200;
    }
    ui32Day = ui32Day + time/84600;
    if(ui32Day > 31) ui32Day = ui32Day - 31;

    if((time/3600) > 24){
        while((time/3600) > 24) time = time - 84600;
    }
    ui32Hour = ui32Hour + time/3600;
    if(ui32Hour > 24) ui32Hour = ui32Hour - 24;

    if((time/60) > 60){
    while((time/60) > 60) time = time - 3600;
    }
    ui32Min = ui32Min + time/60;
    if(ui32Min > 60) ui32Min = ui32Min - 60;

    if((time) > 60){
    while((time) > 60) time = time - 60;
    }
    ui32Sec = time;
    if(ui32Sec > 60) ui32Sec = ui32Sec - 60;

    Lcd_Clear();
    Lcd_Write_Integer2(ui32Year);
    Lcd_Write_Char('-');
    Lcd_Write_Integer2(ui32Month);
    Lcd_Write_Char('-');
    Lcd_Write_Integer2(ui32Day);
    Lcd_Write_Char(' ');
    Lcd_Write_Integer2(ui32Hour);
    Lcd_Write_Char(':');
    Lcd_Write_Integer2(ui32Min);
    Lcd_Write_Char(':');
    Lcd_Write_Integer2(ui32Sec);

    SysCtlDelay(1000000);

    return;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* void update_Trigger_Date_Time(void);
 *
 * This function was made to update the Date and Time and to registed as the last time the alarm was triggered when called. We use the
 * seconds since the last update or when it was set up for the calculate of change in the Date and Time values. We divide by the each one
 * seconds for the time of one year, month, etc... when the value is bigger than the accept value (ex one month has a max of 31 days) we
 * subtracted until we can calculate the  accepted value.
 * After this the RTC clock is reseted to count from 0, so since this change has occurred.
 */
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void update_Trigger_Date_Time(void){
    uint32_t ui32Year, ui32Month, ui32Day, ui32Hour, ui32Min, ui32Sec;
    ui32Day = sTime.tm_mday;
    ui32Month = sTime.tm_mon;
    ui32Year = sTime.tm_year;
    ui32Year = ui32Year - 100;
    ui32Hour = sTime.tm_hour;
    ui32Min = sTime.tm_min;
    ui32Sec = sTime.tm_sec;


    int time = HibernateRTCGet();
    ui32Year = ui32Year + time/961848000;

    if((time/2635200) > 12){
        while((time/2635200) > 12) time = time - 961848000;
    }
    ui32Month = ui32Month + time/2635200;
    if(ui32Month > 12) ui32Month = ui32Month - 12;

    if((time/84600) > 31){
        while((time/84600) > 31) time = time - 2635200;
    }
    ui32Day = ui32Day + time/84600;
    if(ui32Day > 31) ui32Day = ui32Day - 31;

    if((time/3600) > 24){
        while((time/3600) > 24) time = time - 84600;
    }
    ui32Hour = ui32Hour + time/3600;
    if(ui32Hour > 24) ui32Hour = ui32Hour - 24;

    if((time/60) > 60){
    while((time/60) > 60) time = time - 3600;
    }
    ui32Min = ui32Min + time/60;
    if(ui32Min > 60) ui32Min = ui32Min - 60;

    if((time) > 60){
    while((time) > 60) time = time - 60;
    }
    ui32Sec = time;
    if(ui32Sec > 60) ui32Sec = ui32Sec - 60;

    sTrigger.tm_sec = ui32Sec;
    sTrigger.tm_min = ui32Min;
    sTrigger.tm_hour = ui32Hour;
    sTrigger.tm_mday = ui32Day;
    sTrigger.tm_mon = ui32Month;
    sTrigger.tm_year = 100 + ui32Year;

    Lcd_Clear();
    Lcd_Write_Integer2(ui32Year);
    Lcd_Write_Char('-');
    Lcd_Write_Integer2(ui32Month);
    Lcd_Write_Char('-');
    Lcd_Write_Integer2(ui32Day);
    Lcd_Write_Char(' ');
    Lcd_Write_Integer2(ui32Hour);
    Lcd_Write_Char(':');
    Lcd_Write_Integer2(ui32Min);
    Lcd_Write_Char(':');
    Lcd_Write_Integer2(ui32Sec);

    SysCtlDelay(1000000);

    return;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* void show_Trigger_Date_Time(void)
 *
 * This function shows the last time the alarm was triggered by accessing the tm sTrigger struct.
 */
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void show_Trigger_Date_Time(void){
    uint32_t ui32Year, ui32Month, ui32Day, ui32Hour, ui32Min, ui32Sec;
    ui32Day = sTrigger.tm_mday;
    ui32Month = sTrigger.tm_mon;
    ui32Year = sTrigger.tm_year;
    ui32Year = ui32Year - 100;
    ui32Hour = sTrigger.tm_hour;
    ui32Min = sTrigger.tm_min;
    ui32Sec = sTrigger.tm_sec;

    Lcd_Clear();
    Lcd_Write_Integer2(ui32Year);
    Lcd_Write_Char('-');
    Lcd_Write_Integer2(ui32Month);
    Lcd_Write_Char('-');
    Lcd_Write_Integer2(ui32Day);
    Lcd_Write_Char(' ');
    Lcd_Write_Integer2(ui32Hour);
    Lcd_Write_Char(':');
    Lcd_Write_Integer2(ui32Min);
    Lcd_Write_Char(':');
    Lcd_Write_Integer2(ui32Sec);

    SysCtlDelay(1000000);

    return;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* int check_PIN (int PIN);
 *
 * This function was made since we check the PIN more that once program.
 *
 * We receive the correct PIN from the main.c and Active_State() and compare with PIN_Comparator, a int value that was obtain in the same
 * as the value PIN with Set_PIN().
 *
 * The rest is a cycle to only exit if the PIN is right or if the user chooses to exit with a flag that says that the user did not get PIN
 * right.
 *
 * If the PIN is correct the function will return 1 and if the user gives up it returns 0.
 *
 * The 'A' button is to repeat the input of the PIN and B is to give up.
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int check_PIN (int PIN){
    char key;
    int PIN_Comparator;
    while(1)
    {
       PIN_Comparator = Set_PIN();// for more details of this function go to Config_State.c

       if(PIN == PIN_Comparator){
           Lcd_Write_String("PIN is correct");
           SysCtlDelay(300000);
           return 1;
       }
       Lcd_Write_String("Wrong PIN");
       SysCtlDelay(300000);
       Lcd_Write_String("B to exit");
       SysCtlDelay(300000);
       Lcd_Write_String("A to repeat");
       SysCtlDelay(300000);
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* void Active_state(int PIN, int * alarm_armed, int trigger_distance, int * state);
 *
 * This function was made to keep main.c cleaner. It is the state 1 of the State Machine it uses the PIN, alarm_armed,
 * trigger_distance, state from main.c.
 *
 * There is 5 actions that the user can take:
 *      F-> return to Configuration State.
 *      E-> check date and time, we use the Tiva C Hibernation module which works with RTC to get the actual date and time
 *      after the time by seconds it was inputed.
 *      D-> check date and time of last trigger of the alarm, we use an array to store that data and update in case of a
 *      new trigger of the alarm.
 *      C-> to arm or disarm alarm. If the alarm is disarmed(which is by default) it will arm the alarm after the correct
 *      PIN is inputed, on the otherhand, if the alarm is armed it will disarm it after the correct PIN is inputed.
 *      After inputed the correct PIN it will ask to press 'A'to arm or disarm the alarm depending on the already
 *      talked case or to press 'B' to return without changing it s previous state of armed or disarmed.
 *      Idle-> shows the distance of an object to the sensor and if that distance is lower or equal than the trigger distance,
 *      the function alarm_Triggered() will be called and the state value will be changed to 2, so that in main.c the State
 *      Machine enters Beacon State, since the Program Counter is in the function alarm_Triggered() in line 49 the other
 *      functions of the Active State are Locked.
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
            key = keypadScan();
            if (key != 'n') break;
            // Keep updating distance in idle mode
            if(get_value_sonar(data, trigger_distance, alarm_armed, state) == 0){
                //Lcd_Write_String("TOO FAR AWAY ");
            }else if(get_value_sonar(data, trigger_distance, alarm_armed, state) == 2){
                return;
            }else{
                Lcd_Write_Integer(dist);
                Lcd_Write_Char('c');
                Lcd_Write_Char('m');
            }
        }

        switch(key)
        {
            case 'F':
                if (check_PIN(PIN)==1){
                    *state = 0;
                    return;
                }else{
                    Lcd_Write_String("Config LOCKED");
                    SysCtlDelay(30000);
                }

            case 'E':
                update_Date_Time();
                SysCtlDelay(300000);
                break;

            case 'D':
                show_Trigger_Date_Time();
                SysCtlDelay(300000);
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

                    Lcd_Write_String("B to return");
                    SysCtlDelay(300000);
                    Lcd_Write_String("A to disarm alarm");
                    SysCtlDelay(300000);
                    while(1)
                    {
                        key = keypadScan();
                        if (key != 'n')
                        {
                            if(key == 'B') break;

                            if(key == 'A'){
                                *alarm_armed = FALSE;
                                break;
                            }
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

                     Lcd_Write_String("B to return");
                     SysCtlDelay(300000);
                     Lcd_Write_String("A to arm the alarm");
                     SysCtlDelay(300000);
                     while(1)
                     {
                         key = keypadScan();
                         if (key != 'n')
                         {
                             if(key == 'B') break;

                             if(key == 'A') {
                                 *alarm_armed = TRUE;
                                 break;
                             }
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
