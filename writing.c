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
 * writing.c
 *
 *  Created on: 24.05.2018
 *      Author: Alex
 */

void printString(char text[], uint8_t size, uint16_t bottomLine, uint16_t leftLine){

    uint16_t t;
    for(t=0; t<sizeof(text); t++){

        leftLine += t*4095*(8-size);
        switch (text[t]){
        case 'a'    :   //fall through
        case 'A'    :   printA(size, bottomLine, leftLine); break;

        case 'b'    :   //fallthrough
        case 'B'    :   printB(ui32SysClkFreq, size, bottomLine, leftLine); break;

        case 'c'    :   //fallthrough
        case 'C'    :   printC(ui32SysClkFreq, size, bottomLine, leftLine); break;

        case 'd'    :   //fallthrough
        case 'D'    :   printD(ui32SysClkFreq, size, bottomLine, leftLine); break;

        case 'e'    :   //fallthrough
        case 'E'    :   printE(ui32SysClkFreq, size, bottomLine, leftLine); break;

        case 'f'    :   //fallthrough
        case 'F'    :   printF(ui32SysClkFreq, size, bottomLine, leftLine); break;

        case 'g'    :   //fallthrough
        case 'G'    :   printG(ui32SysClkFreq, size, bottomLine, leftLine); break;

        case 'h'    :   //fallthrough
        case 'H'    :   printH(ui32SysClkFreq, size, bottomLine, leftLine); break;

        case 'i'    :   //fallthrough
        case 'I'    :   printI(ui32SysClkFreq, size, bottomLine, leftLine); break;

        case 'j'    :   //fallthrough
        case 'J'    :   printJ(ui32SysClkFreq, size, bottomLine, leftLine); break;

        case 'k'    :   //fallthrough
        case 'K'    :   printK(ui32SysClkFreq, size, bottomLine, leftLine); break;

        case 'l'    :   //fallthrough
        case 'L'    :   printL(ui32SysClkFreq, size, bottomLine, leftLine); break;

        case 'm'    :   //fallthrough
        case 'M'    :   printM(ui32SysClkFreq, size, bottomLine, leftLine); break;

        case 'n'    :   //fallthrough
        case 'N'    :   printN(ui32SysClkFreq, size, bottomLine, leftLine); break;

        case 'o'    :   //fallthrough
        case 'O'    :   printO(ui32SysClkFreq, size, bottomLine, leftLine); break;

        case 'p'    :   //fallthrough
        case 'P'    :   printP(ui32SysClkFreq, size, bottomLine, leftLine); break;

        case 'q'    :   //fallthrough
        case 'Q'    :   printQ(ui32SysClkFreq, size, bottomLine, leftLine); break;

        case 'r'    :   //fallthrough
        case 'R'    :   printR(ui32SysClkFreq, size, bottomLine, leftLine); break;

        case 's'    :   //fallthrough
        case 'S'    :   printS(ui32SysClkFreq, size, bottomLine, leftLine); break;

        case 't'    :   //fallthrough
        case 'T'    :   printT(ui32SysClkFreq, size, bottomLine, leftLine); break;

        case 'u'    :   //fallthrough
        case 'U'    :   printU(ui32SysClkFreq, size, bottomLine, leftLine); break;

        case 'v'    :   //fallthrough
        case 'V'    :   printV(ui32SysClkFreq, size, bottomLine, leftLine); break;

        case 'w'    :   //fallthrough
        case 'W'    :   printW(ui32SysClkFreq, size, bottomLine, leftLine); break;

        case 'x'    :   //fallthrough
        case 'X'    :   printX(ui32SysClkFreq, size, bottomLine, leftLine); break;

        case 'y'    :   //fallthrough
        case 'Y'    :   printY(ui32SysClkFreq, size, bottomLine, leftLine); break;

        case 'z'    :   //fallthrough
        case 'Z'    :   printZ(ui32SysClkFreq, size, bottomLine, leftLine); break;

        }
    }
}


void printA(uint8_t size, uint16_t bottomLine, uint16_t leftLine){
    uint16_t x[] = {0, 1365, 2730, 2275, 455};
    uint16_t y[] = {0, 4095, 0, 1365, 1365};
    uint8_t onOff[] = {0,1,1,0,1};

    scaleLetter(x, leftLine, size);
    scaleLetter(y, bottomLine, size);

    for(t=numberofpoints; t<sizeof(x), t++){
        x befülen
        y befüülen
        oO befüllen
        number++
    }
//    drawFrame(x, y, onOff);
}

void scaleLetter(uint16_t x[], uint16_t move, uint8_t size){
    uint8_t counter;
    for(counter = 0; counter < sizeof(x); counter++){
        x[counter] = x[counter] >> (8-size);
        x[counter] += move;
    }
}
