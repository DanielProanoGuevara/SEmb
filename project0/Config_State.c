/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* Project for the subject ESEMb, made by Diogo Rodrigues nº94240, Daniel Proanho nº101229, and Miguel Fernandes nº93790
 *
 *This file is the Config_State.c, this file was created to keep the main.c file clean and short.
 *
 *In this file we have DateTimeSet(), Get_Date(), Get_Time(), Set_PIN, Set_Distance, Set_Timeout.
 *
 *A more detailed description of the functions will be in the overhead of the functions.
 */
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "System.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*void DateTimeSet(void);
 *
 *STILL TESTING NOT FINAL
 *
 *this function is calling Get_Date() and Get_Time() to get current date and time inputed by the user and apply it to the already Tiva build
 *Calendar function.
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DateTimeSet(void)
{
    uint32_t ui32Year, ui32Month, ui32Day, ui32Hour, ui32Min, ui32Sec;

    Get_Date(&ui32Year, &ui32Month, &ui32Day);
    Get_Time(&ui32Hour, &ui32Min, &ui32Sec);

    HibernateCalendarGet(&sTime);

    sTime.tm_sec = ui32Sec;
    sTime.tm_min = ui32Min;
    sTime.tm_hour = ui32Hour;
    sTime.tm_mday = ui32Day;
    sTime.tm_mon = ui32Month;
    sTime.tm_year = 100 + ui32Year;

    HibernateCalendarSet(&sTime);

}

/*void DateTimeDefaultSet(void)
{
    g_ui32MonthIdx = 7;
    g_ui32DayIdx = 29;
    g_ui32YearIdx = 13;
    g_ui32HourIdx = 8;
    g_ui32MinIdx = 30;

}*/

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*void Get_Date(uint32_t *ui32Year, uint32_t *ui32Month, uint32_t *ui32Day);
 *
 * This function will get the current date by translating the char inputs of the keyboard to int values that will be set in the tm Time
 * struct with ui32Year, ui32Month, ui32Day.
 *
 * It asks the user to input data in the following format "DD-MM-YY", and then waits for the 'A' button to be pressed which is the
 * confirmation key, if the user has done a mistake it can press the 'B' button to repeat from the beginning.
 */
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Get_Date(uint32_t *ui32Year, uint32_t *ui32Month, uint32_t *ui32Day){
    int i=0;
    char key;
    char DateArray[7];
    char Temp[3];
    Lcd_Write_String("Enter date, B resets");
    SysCtlDelay(300000);
    Lcd_Write_String("DD-MM-YY ");
    while(1)
    {
        GPIOPinWrite(GPIO_PORTF_BASE, GREEN_LED|RED_LED|BLUE_LED, GREEN_LED|BLUE_LED);
        key = keypadScan();
        if (key != 'n' && i < 7)
        {
            GPIOPinWrite(GPIO_PORTF_BASE, GREEN_LED|RED_LED|BLUE_LED, RED_LED);

            if(key == 'A'){
                i++;
                break;
            }

            DateArray[i] = key;
            Lcd_Write_Char(key);

            if(i == 1|| i == 3) Lcd_Write_Char('-');

            i++;
        }
        if(key == 'A'){
            i++;
            break;
        }
        if(key == 'B')
        {
            for ( i = 0; i < 8; ++i)
                DateArray[i] = 0;
            i=0;
            Lcd_Write_String("DD-MM-YY");
        }
    }
    Temp[0] = DateArray[0];
    Temp[1] = DateArray[1];
    *ui32Day = atoi(Temp);

    Temp[0] = DateArray[2];
    Temp[1] = DateArray[3];
    *ui32Month = atoi(Temp);

    Temp[0] = DateArray[4];
    Temp[1] = DateArray[5];
    *ui32Year = atoi(Temp);
    return;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*void Get_Time(uint32_t *ui32Hour, uint32_t *ui32Min, uint32_t *ui32Sec);
 *
 * This function will get the current time by translating the char inputs of the keyboard to int values that will be set in the tm Time
 * struct with ui32Hour, ui32Min, ui32Sec.
 *
 * It asks the user to input data in the following format "hh:mm:ss", and then waits for the 'A' button to be pressed which is the
 * confirmation key, if the user has done a mistake it can press the 'B' button to repeat from the beginning.
 */
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Get_Time(uint32_t *ui32Hour, uint32_t *ui32Min, uint32_t *ui32Sec){
    GPIOPinWrite(GPIO_PORTF_BASE, GREEN_LED|RED_LED|BLUE_LED, GREEN_LED|BLUE_LED);
    int i=0;
    char key;
    char TimeArray[7];
    char Temp[3];
    Lcd_Write_String("Enter time, B resets");
    SysCtlDelay(300000);
    Lcd_Write_String("hh:mm:ss ");
    while(i < 7)
    {
        GPIOPinWrite(GPIO_PORTF_BASE, GREEN_LED|RED_LED|BLUE_LED, GREEN_LED|BLUE_LED);
        key = keypadScan();
        if (key != 'n' && i < 7)
        {
            GPIOPinWrite(GPIO_PORTF_BASE, GREEN_LED|RED_LED|BLUE_LED, RED_LED);

            if(key == 'A'){
               i++;
               break;
            }

            TimeArray[i] = key;
            Lcd_Write_Char(key);

            if(i == 1|| i == 3) Lcd_Write_Char(':');
            i++;
        }
        if(key == 'A'){
            i++;
            break;
        }
        if(key == 'B')
        {
            for ( i = 0; i <6; ++i)
                TimeArray[i] = 0;
            i=0;
            Lcd_Write_String("hh:mm:ss ");
        }
    }
    Temp[0] = TimeArray[0];
    Temp[1] = TimeArray[1];
    *ui32Hour = atoi(Temp);

    Temp[0] = TimeArray[2];
    Temp[1] = TimeArray[3];
    *ui32Min = atoi(Temp);

    Temp[0] = TimeArray[4];
    Temp[1] = TimeArray[5];
    *ui32Sec = atoi(Temp);
    return;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*int Set_PIN(void);
 *
 * This function will get the PIN by translating the char inputs of the keyboard to a int value that will be stored in main.c
 *
 * It asks the user to input data in the following format "****", and then waits for the 'A' button to be pressed which is the
 * confirmation key, if the user has done a mistake it can press the 'B' button to repeat from the beginning.
 */
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Set_PIN(void){
    GPIOPinWrite(GPIO_PORTF_BASE, GREEN_LED|RED_LED|BLUE_LED, GREEN_LED|BLUE_LED);
    int i=0;
    char key;
    char PIN[5];
    Lcd_Write_String("Enter PIN, B resets");
    SysCtlDelay(300000);
    Lcd_Write_String("****, ");
    while(i < 5)
    {
        GPIOPinWrite(GPIO_PORTF_BASE, GREEN_LED|RED_LED|BLUE_LED, GREEN_LED|BLUE_LED);
        key = keypadScan();
        if (key != 'n' && i < 5)
        {
            GPIOPinWrite(GPIO_PORTF_BASE, GREEN_LED|RED_LED|BLUE_LED, RED_LED);

            if(key == 'A'){
               i++;
               break;
            }

            PIN[i] = key;
            Lcd_Write_Char(key);

            i++;
        }
        if(key == 'A'){
             i++;
             break;
        }
        if(key == 'B')
        {
             for ( i = 0; i < 4; ++i)
                 PIN[i] = 0;
             i=0;
             Lcd_Write_String("**** ");
        }
    }
    int intPIN = atoi(PIN);
    return intPIN;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*int Set_Distance(void);
 *
 * This function will get the alarm triggering distance by translating the char inputs of the keyboard to a int value that will be stored
 * in main.c
 *
 * It asks the user to input data in the following format "***", and then waits for the 'A' button to be pressed which is the
 * confirmation key, if the user has done a mistake it can press the 'B' button to repeat from the beginning.
 */
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Set_Distance(void){
    GPIOPinWrite(GPIO_PORTF_BASE, GREEN_LED|RED_LED|BLUE_LED, GREEN_LED|BLUE_LED);
    int i=0;
    char key;
    char distance[3];
    Lcd_Write_String("Enter trigger distan");
    SysCtlDelay(300000);
    Lcd_Write_String("in *** cm, ");
    while(1)
    {
        GPIOPinWrite(GPIO_PORTF_BASE, GREEN_LED|RED_LED|BLUE_LED, GREEN_LED|BLUE_LED);
        key = keypadScan();
        if (key != 'n' && i < 3)
        {
            GPIOPinWrite(GPIO_PORTF_BASE, GREEN_LED|RED_LED|BLUE_LED, RED_LED);

            if(key == 'A'){
               i++;
               break;
            }

            distance[i] = key;
            Lcd_Write_Char(key);

            i++;
         }
         if(key == 'A'){
             i++;
             break;
         }
         if(key == 'B')
         {
             for ( i = 0; i < 3; ++i)
                 distance[i] = 0;
             i=0;
             Lcd_Write_String("in *** cm, ");
         }
      }
      int intDistance = atoi(distance);
      return intDistance;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*int Set_Timeout(void);
 *
 * This function will get the tasks timeout time by translating the char inputs of the keyboard to a int value that will be stored
 * in main.c
 *
 * It asks the user to input data in the following format "****", and then waits for the 'A' button to be pressed which is the
 * confirmation key, if the user has done a mistake it can press the 'B' button to repeat from the beginning.
 */
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Set_Timeout(void){
    GPIOPinWrite(GPIO_PORTF_BASE, GREEN_LED|RED_LED|BLUE_LED, GREEN_LED|BLUE_LED);
    int i=0;
    char key;
    char timeout[3];
    Lcd_Write_String("Enter timeout time");
    SysCtlDelay(300000);
    Lcd_Write_String("in ** s, ");
    while(1)
    {
        GPIOPinWrite(GPIO_PORTF_BASE, GREEN_LED|RED_LED|BLUE_LED, GREEN_LED|BLUE_LED);
        key = keypadScan();
        if (key != 'n' && i < 3)
        {
            GPIOPinWrite(GPIO_PORTF_BASE, GREEN_LED|RED_LED|BLUE_LED, RED_LED);

            if(key == 'A'){
               i++;
               break;
            }

            timeout[i] = key;
            Lcd_Write_Char(key);

            i++;
            if(key == 'B')
            {
                for ( i = 0; i < 2; ++i)
                    timeout[i] = 0;
                i=0;
                Lcd_Write_String("in s, B resets, ");
            }
         }
         if(key == 'A'){
             i++;
             break;
         }
         if(key == 'B')
         {
             for ( i = 0; i < 2; ++i)
                 timeout[i] = 0;
             i=0;
             Lcd_Write_String("in s, B resets, ");
         }
      }
      int intTimeout = atoi(timeout);
      return intTimeout;
}


