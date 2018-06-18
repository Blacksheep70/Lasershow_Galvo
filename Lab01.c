#include <stdint.h>
#include <stdbool.h>
#include"inc/tm4c1294ncpdt.h"
#include "inc/hw_ssi.h"
#include "driverlib/ssi.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_memmap.h"
#include "driverlib/pin_map.h"
#include "galvo.h"


/**
 * main.c
 */


int main(void)
  {
    uint16_t x[100];
    uint16_t y[100];
    uint8_t onOff[100];
    uint32_t ui32SysClkFreq;
    ui32SysClkFreq = SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN | SYSCTL_USE_PLL | SYSCTL_CFG_VCO_480), 120000000);

    setUpGalvos(x, y, onOff, ui32SysClkFreq);


    while(1){

//        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2, 0);
//        SysCtlDelay(ui32SysClkFreq/3);
//        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2, GPIO_PIN_2);
//        SysCtlDelay(ui32SysClkFreq/3);

//        SSI0SendData_xy(0, 0);
//        SysCtlDelay(ui32SysClkFreq/3);
//        SSI0SendData_xy(500, 500);
//        SysCtlDelay(ui32SysClkFreq/3);
//        SSI0SendData_xy(4095, 4095);
//        SysCtlDelay(ui32SysClkFreq/3);

//        drawLineBresenham(0, 4095, 0, 0, ui32SysClkFreq);
//        drawLineBresenham(4095, 4095, 0, 4095, ui32SysClkFreq);
//        drawLineBresenham(4095, 0, 4095, 4095, ui32SysClkFreq);
//        drawLineBresenham(0, 0, 4095, 0, ui32SysClkFreq);

//        drawLine(0, 4095, 0, 4095, ui32SysClkFreq);
//        drawLine(4095, 4095, 4095, 0, ui32SysClkFreq);
//        drawLine(4095, 0, 0, 0, ui32SysClkFreq);
//        drawLine(0, 0, 0, 0, ui32SysClkFreq);



//        uint16_t x[] = {0,1,200,200,400,400,600,600,400,400,200,200,0,800,800,1200,1200,1400,1400,1800,1800,800,2000,2000,3000,3000,2800,2800,2600,2600,2400,2400,2200,2200,2000,3200,3200,4000,4000,3600,3600,3800,3800,3400,3400,4000,4000,3200, 0};
//        uint16_t y[] = {1000,1,0,400,400,0,0,1000,1000,600,600,1000,1000,1000,800,800,0,0,800,800,1000,1000,1000,0,0,1000,1000,200,200,400,400,200,200,1000,1000,1000,0,0,600,600,400,400,200,200,800,800,1000,1000, 1000};
//        uint8_t onOff[] = {0,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,0};
//        drawFrame(x, y, onOff, 49);

    }
}



