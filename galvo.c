#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include"inc/tm4c1294ncpdt.h"
#include "inc/hw_ssi.h"
#include "driverlib/ssi.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_memmap.h"
#include "driverlib/pin_map.h"
#include "driverlib/timer.h"
#include "galvo.h"
#include <driverlib/interrupt.h>

/*
 * galvo.c
 *
 *  Created on: 04.05.2018
 *      Author: Alex
 */

uint16_t* x;
uint16_t* y;
uint8_t* onOff;
uint8_t firstByte_A;
uint8_t secondByte_A;
uint8_t firstByte_B;
uint8_t secondByte_B;
uint8_t ui8SSICounter;


void setUpGalvos(uint16_t x1[], uint16_t y1[], uint8_t onOff1[], uint32_t ui32SysClkFreq){
    x = x1;
    y = y1;
    onOff = onOff1;
    setUpSSIO(ui32SysClkFreq);
    setUpLaser();
    setUpTimer();
}
void setUpLaser()
{
    //Enable GPIOD
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);

    //Wait for GPIOD to be ready
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOD))
        ;

    //Configure Port D2 as GPIO
    GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_2);
}

void setUpSSIO(uint32_t ui32SysClkFreq)
{
    //Enable the SSI2 peripheral

        SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI2);

        //Wait for the SSI2 module to be ready
        while (!SysCtlPeripheralReady(SYSCTL_PERIPH_SSI2))
            ;

        //Enable GPIOD
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);

        //Wait for GPIOD to be ready
        while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOD))
            ;

        //Enable GPION
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);

        //Wait for GPION to be ready
        while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPION))
            ;

        GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_2);
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_2, GPIO_PIN_2);

        GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_3);
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_3, GPIO_PIN_3);

        //Configure Pin D3 as Clock
        GPIOPinConfigure(GPIO_PD3_SSI2CLK);

        //Configure Pin D1 as Data Pin
        GPIOPinConfigure(GPIO_PD1_SSI2XDAT0);

        //Declare Pins D1 and D3 as SSI Pins
        GPIOPinTypeSSI(GPIO_PORTD_BASE, GPIO_PIN_3 | GPIO_PIN_1);

        //Configure the SSI
        SSIConfigSetExpClk(SSI2_BASE, ui32SysClkFreq, SSI_FRF_MOTO_MODE_0,
                           SSI_MODE_MASTER, 5000000, 8);

        //Enable the SSI module
        SSIEnable(SSI2_BASE);

        SSIIntRegister(SSI2_BASE, SSIIntHandler);
        SSIIntEnable(SSI2_BASE, SSI_TXEOT);
}

void setUpTimer(){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER0));
}


void SSI0SendData_xy(uint16_t valueX, uint16_t valueY)
{
    uint8_t configBits_A = 0 << 3 | 1 << 2 | 1 << 1 | 1;
firstByte_A = configBits_A << 4 | (valueX & 0xF00) >> 8;
secondByte_A = valueX & 0xFF;

    uint8_t configBits_B = 1 << 3 | 0 << 2 | 1 << 1 | 1;
firstByte_B = configBits_B << 4 | (valueY & 0xF00) >> 8;
secondByte_B = valueY & 0xFF;

    GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_3, 0);

    SSIDataPut(SSI2_BASE, firstByte_A);
//    while (SSIBusy(SSI2_BASE))
//        ;
//
//    SSIDataPut(SSI2_BASE, secondByte_A);
//    while (SSIBusy(SSI2_BASE))
//        ;
//    GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_3, GPIO_PIN_3);
//    GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_3, 0);
//
//    SSIDataPut(SSI2_BASE, firstByte_B);
//    while (SSIBusy(SSI2_BASE))
//        ;
//
//    SSIDataPut(SSI2_BASE, secondByte_B);
//    while (SSIBusy(SSI2_BASE))
//        ;
//
//    GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_3, GPIO_PIN_3);
//
//    GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_2, 0);
//    GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_2, GPIO_PIN_2);
}

//Linienberechnung nach dem Bresenham Algorithmus
//Ohne Float Operation --> schneller
void drawLineBresenham (uint16_t x_start, uint16_t x_end, uint16_t y_start, uint16_t y_end){
    uint16_t x, y, deltaslowdirection, deltafastdirection, t;
    int32_t dx, dy, err;
    int8_t incx, incy, pdx, pdy, ddx, ddy;

    //Entfernung in beide Richtungen berechnen
    dx = x_end - x_start;
    dy = y_end - y_start;

    //Vorzeichen bestimmen
    incx = sgn(dx);
    incy = sgn(dy);
    dx = fabs(dx);
    dy = fabs(dy);

    ddx = incx;
    ddy = incy;

    if(dx > dy){
        //x ist die schnelle Richtung
        pdx = incx;
        pdy = 0; //Dies ist der Parallelschritt
        deltaslowdirection = dy;
        deltafastdirection = dx;
    }
    else{
        pdx = 0;
        pdy = incy;
        deltaslowdirection = dx;
        deltafastdirection = dy;
    }

    x = x_start;
    y = y_start;
    err = deltafastdirection >> 1;
    SSI0SendData_xy(x, y);
    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2, GPIO_PIN_2);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOD))
    SysCtlDelay(10);
    for(t = 0; t<deltafastdirection; t++){
        err -= deltaslowdirection;
        if(err<0){
            err += deltafastdirection;
            x += ddx;
            y += ddy;
        }
        else{
            x += pdx;
            y += pdy;
        }
    if(t % 200 == 0 || t == 0 || t == deltafastdirection-1){
        SSI0SendData_xy(x, y);
    SysCtlDelay(10000);}
    }
    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2, 0);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOD));
    //SysCtlDelay(10);
}

void drawCircleBresenham(uint16_t x0, uint16_t y0, uint16_t radius, uint8_t corner)
 {
   int16_t f = 1 - radius;
   uint16_t ddF_x = 0;
   int16_t ddF_y = -2 * radius;
   uint16_t x = 0;
   uint16_t y = radius;

   GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2, GPIO_PIN_2);
   while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOD));

   if(corner & 0x01 || corner & 0x02)
       SSI0SendData_xy(x0, y0 + radius);
   if(corner & 0x03 || corner & 0x04)
       SSI0SendData_xy(x0, y0 - radius);
   if(corner & 0x01 || corner & 0x03)
       SSI0SendData_xy(x0 + radius, y0);
   if(corner & 0x02 || corner & 0x04)
       SSI0SendData_xy(x0 - radius, y0);

   while(x < y)
   {
     if(f >= 0)
     {
       y--;
       ddF_y += 2;
       f += ddF_y;
     }
     x++;
     ddF_x += 2;
     f += ddF_x + 1;

     if(corner & 0x01){
         SSI0SendData_xy(x0 + x, y0 + y);
         SSI0SendData_xy(x0 + y, y0 + x);
     }
     if(corner & 0x02){
         SSI0SendData_xy(x0 - x, y0 + y);
         SSI0SendData_xy(x0 - y, y0 + x);
     }
     if(corner & 0x03){
         SSI0SendData_xy(x0 + x, y0 - y);
         SSI0SendData_xy(x0 + y, y0 - x);
     }
     if(corner & 0x04){
         SSI0SendData_xy(x0 - x, y0 - y);
         SSI0SendData_xy(x0 - y, y0 - x);
     }
   }
     GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2, 0);
     while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOD));
 }

int8_t sgn(int32_t number){
    if(number > 0)
        return 1;
    else if(number < 0)
        return -1;
    else
        return 0;
}


void startDrawing(uint32_t ui32SysClkFreq){
    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
    TimerLoadSet(TIMER0_BASE, TIMER_A, ui32SysClkFreq/10-1);
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    IntEnable(INT_TIMER0A);
    IntMasterEnable();
    TimerIntRegister(TIMER0_BASE, TIMER_A, Timer0IntHandler);
    TimerEnable(TIMER0_BASE, TIMER_A);
}

void Timer0IntHandler(){

    TimerIntClear(TIMER0_BASE, TIMER_A);
    drawFrame(x, y, onOff);

}

void drawFrame(uint16_t x[], uint16_t y[], uint8_t onOff[]){

    uint16_t t;

    for(t = 0; t < sizeof(x); t++)
    {

        if(onOff[t] == 0)
            SSI0SendData_xy(x[t], y[t]);
        else if(onOff[t] == 1)
            drawLineBresenham(x[t-1], x[t], y[t-1], y[t]);
        else if(onOff[t] == 2){
            drawCircleBresenham(x[t], y[t], x[t+1], y[t+1]);
            t++;
        }
    }
}

void plotLine(uint16_t x_start, uint16_t x_end, uint16_t y_start, uint16_t y_end, uint32_t ui32SysClkFreq){
        uint16_t x, y, deltaslowdirection, deltafastdirection, t;
        int32_t dx, dy, err;
        int8_t incx, incy, pdx, pdy, ddx, ddy;

        //Entfernung in beide Richtungen berechnen
        dx = x_end - x_start;
        dy = y_end - y_start;

        //Vorzeichen bestimmen
        incx = sgn(dx);
        incy = sgn(dy);
        dx = fabs(dx);
        dy = fabs(dy);

        ddx = incx;
        ddy = incy;

        if(dx > dy){
            //x ist die schnelle Richtung
            pdx = incx;
            pdy = 0; //Dies ist der Parallelschritt
            deltaslowdirection = dy;
            deltafastdirection = dx;
        }
        else{
            pdx = 0;
            pdy = incy;
            deltaslowdirection = dx;
            deltafastdirection = dy;
        }

        x = x_start;
        y = y_start;
        err = deltafastdirection >> 1;
        SSI0SendData_xy(x, y);
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2, GPIO_PIN_2);
        while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOD))
        SysCtlDelay(10);
        for(t = 0; t<deltafastdirection; t++){
            err -= deltaslowdirection;
            if(err<0){
                err += deltafastdirection;
                x += ddx;
                y += ddy;
            }
            else{
                x += pdx;
                y += pdy;
            }
        drawLineBresenham(0, x, 0, y);
        if(t % 200 == 0 || t == 0 || t == deltafastdirection-1){
            GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2, GPIO_PIN_2);
            SSI0SendData_xy(x, y);
        SysCtlDelay(ui32SysClkFreq/20000-1);}
        }
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2, 0);
        while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOD));
        //SysCtlDelay(10);
}

void SSIIntHandler(void){
    SSIIntClear(SSI2_BASE, SSI_TXEOT);
    switch (ui8SSICounter){
    case 0  :   SSIDataPut(SSI2_BASE, secondByte_A);
                ui8SSICounter++;
                GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_3, GPIO_PIN_3);
                GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_3, 0);
                break;
    case 1  :   SSIDataPut(SSI2_BASE, firstByte_B);
                ui8SSICounter++;
                break;
    case 2  :   SSIDataPut(SSI2_BASE, secondByte_B);
                ui8SSICounter = 0;
                GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_3, GPIO_PIN_3);
                GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_2, 0);
                GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_2, GPIO_PIN_2);
                break;
    }
}

//uint8_t drawLine (uint16_t x_start, uint16_t x_end, uint16_t y_start, uint16_t y_end, uint32_t ui32SysClkFreq)
//{
//    float_t x;
//    float_t y;
//    uint16_t counter_max;
//    uint16_t counter;
//    uint16_t stepwidth = 200;
//
//
//    //Check if x and y values are usable
//    if(x_start > 4095   ||  x_end > 4095    ||  y_start > 4095  ||  y_end > 4095)
//        return 0;
//
//    //Shut Down Laser
//    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2, 0);
//
//    //Move to start position
//    SSI0SendData_xy(x_start, y_start);
//
//    //Calculate x and y steps, so that every step has the length 1
//    if(x_start != x_end){
//    x = (sqrt( 1.0 / ( pow(((float)y_end-(float)y_start)/((float)x_end-(float)x_start), 2.0) + 1.0) )) * (((float)x_end-(float)x_start)/fabs((float)x_end-(float)x_start));
//    y = fabs(( ( ( (float)y_end-(float)y_start ) / ( (float)x_end-(float)x_start ) ) * (float)x) ) * (((float)y_end-(float)y_start)/fabs((float)y_end-(float)y_start));
//    counter_max = fabs(((float)x_end - (float)x_start) / x);
//    }
//
//    else if (y_start != y_end){
//        y = ((float)y_end-(float)y_start)/fabs((float)y_end-(float)y_start);
//        x = 0;
//        counter_max = fabs((float)y_end - (float)y_start);
//    }
//
//    else {
//        x = 0;
//        y = 0;
//        counter_max = 0;
//    }
////    SysCtlDelay(ui32SysClkFreq/1000);
//
//    //Turn on Laser
//    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2, GPIO_PIN_2);
//
//    //Move stepwise until final position is reached
//    for(counter = 0; counter < counter_max; counter += stepwidth){
//        SSI0SendData_xy(x_start + ((float)counter * x), y_start + ((float)counter * y));
//        if(counter+200 > counter_max)
//            counter = counter_max - stepwidth;
//    }
//
//
////    SysCtlDelay(ui32SysClkFreq/1000);
//
//    //Turn Down Laser
//    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2, 0);
//    return 1;
//}
