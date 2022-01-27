#include "System.h"

void measure_sonar(){
    uint8_t sense_address = 0x70;
    uint8_t data = 0x51;

    I2CMasterSlaveAddrSet(I2C1_BASE, sense_address, false);

    I2CMasterDataPut(I2C1_BASE, data);

    I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_SINGLE_SEND);
    while(I2CMasterBusy(I2C1_BASE));
    //if(I2CMasterErr()) Lcd_Write_String("ERROR MEASURE SONAR");

    return;
}

int get_value_sonar(int *int_data){

    SysCtlDelay(160000);

    int verifica;
    uint8_t sense_address = 0x70;

    I2CMasterSlaveAddrSet(I2C1_BASE, sense_address, true);

    I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_RECEIVE_START );
    while(I2CMasterBusy(I2C1_BASE));
    if((verifica = (int)I2CMasterDataGet(I2C1_BASE))!=0 || verifica == 2)
        return 0;

    I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_RECEIVE_FINISH);
    while(I2CMasterBusy(I2C1_BASE));
    //if(I2CMasterErr()) Lcd_Write_String("ERROR VALUE SONAR");
    *int_data = (int)I2CMasterDataGet(I2C1_BASE);

    return 1;
}

void start_I2C(){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C1);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_I2C1));

    SysCtlPeripheralReset(SYSCTL_PERIPH_I2C1);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_I2C1));

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA));

    GPIOPinConfigure(GPIO_PA6_I2C1SCL);
    GPIOPinConfigure(GPIO_PA7_I2C1SDA);

    GPIOPinTypeI2CSCL(GPIO_PORTA_BASE, GPIO_PIN_6);
    GPIOPinTypeI2C(GPIO_PORTA_BASE, GPIO_PIN_7);

    I2CMasterInitExpClk(I2C1_BASE, SysCtlClockGet(), false);
}




