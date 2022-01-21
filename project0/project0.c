////////////////////////////////////////////////////////////////////////////////
/* Main file
 *
 */
///////////////////////////////////////////////////////////////////////////////

#include "System.h"

int main(void){
    
    init_system();

    // Ativate LEDS for debug

    GPIOPinWrite(GPIO_PORTF_BASE, GREEN_LED|RED_LED|BLUE_LED, GREEN_LED|RED_LED|BLUE_LED);

    SysCtlDelay(3000000);

    pwm0_init();

    Lcd_Init();

    Lcd_Write_String("Hello World");

    SysCtlDelay(3000000);


    int state = 0;
    char DateArray[8];
    char TimeArray[6];
    char PIN[4];
    long timeout, trigger_distance;
    int alarm_armed = FALSE, alarm_trigger = FALSE;
    int temp = 0, i;
    while(1)
    {

        switch(state)
        {

            case 0: //config state
                Config_init();
                Get_Date(DateArray);
                Lcd_Write_String(DateArray);
                SysCtlDelay(2000000);
                Get_Time(TimeArray);
                Lcd_Write_String(TimeArray);
                SysCtlDelay(2000000);
                Set_PIN(PIN);
                Lcd_Write_String(PIN);
                SysCtlDelay(2000000);
                trigger_distance = Set_Distance();
                Lcd_Write_Integer(trigger_distance);
                SysCtlDelay(2000000);
                timeout = Set_Timeout();
                Lcd_Write_Integer(timeout);
                SysCtlDelay(2000000);
                state = 1;
            case 1:
                temp = Active_state(DateArray, TimeArray, PIN, alarm_armed);

                if(temp == 0){
                    state = 0;
                }else if(temp == 1){
                    alarm_armed = FALSE;
                    if(alarm_trigger == 1){
                        pwm0_stop();
                        alarm_trigger = 0;
                        Lcd_Write_String("ALARM DISARMED!");
                        SysCtlDelay(500000);
                    }
                }else if(temp == 2){
                    alarm_armed = TRUE;
                }else if(temp == 3){
                    Lcd_Write_String("PIN was INCORRECT");
                    SysCtlDelay(5000000);
                }else{
                    Lcd_Write_String("ERROR IN ACTIVE");
                    SysCtlDelay(5000000);
                }
            case 2:// vai estar no sensor;
                pwm0_start(1000, 60);
                i = 0;
                while(i<5){
                    Lcd_Write_String("ALARM TRIGGERED!");
                    SysCtlDelay(80000);
                    i++;
                }
                alarm_trigger = 1;
            default:
                Lcd_Write_String("ERROR IN DEFAULT");
                SysCtlDelay(5000000);
                state = 1;
        }
    }
}
