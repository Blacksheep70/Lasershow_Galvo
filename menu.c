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
#include "writing.h"

/*
 * menu.c
 *
 *  Created on: 25.05.2018
 *      Author: Alex
 */

void makeMainMenu(uint32_t ui32SysClkFreq){

    uint8_t selector;

//    while(1){
//        printString("Spiel 1 starten", ui32SysClkFreq, size, bottomLine, leftLine);
//        printString("Testbild anzeigen.", ui32SysClkFreq, size, bottomLine, leftLine);
//        printString("Reboot", ui32SysClkFreq, size, bottomLine, leftLine);
//
//        switch(selector){
//        case 0  :   drawLineBresenham(x_start, x_end, y_start, y_end, ui32SysClkFreq) : break;//um ersten Auswahlpunkt herum malen
//        case 1  :   drawLineBresenham(x_start, x_end, y_start, y_end, ui32SysClkFreq) : break;//um zweiten Auswahlpunkt herum malen
//        case 2  :   drawLineBresenham(x_start, x_end, y_start, y_end, ui32SysClkFreq) : break;//um dritten Auswahlpunkt herum malen
//        }
//    }
}



