/*
 * galvo.h
 *
 *  Created on: 04.05.2018
 *      Author: Alex
 */

#ifndef GALVO_H_
#define GALVO_H_

#define TOP_RIGHT       0x01
#define TOP_LEFT        0x02
#define BOTTOM_RIGHT    0x03
#define BOTTOM_LEFT     0x04

void setUpGalvos(uint16_t x1[], uint16_t y1[], uint8_t onOff1[], uint32_t ui32SysClkFreq);
void setUpLaser();
void setUpSSIO(uint32_t ui32SysClkFreq);
void setUpTimer();
void SSI0SendData_xy(uint16_t valueX, uint16_t valueY);
void drawLineBresenham (uint16_t x_start, uint16_t x_end, uint16_t y_start, uint16_t y_end);
void drawCircleBresenham(uint16_t x0, uint16_t y0, uint16_t radius, uint8_t corner);
int8_t sgn(int32_t number);
void startDrawing(uint32_t ui32SysClkFreq);
void Timer0IntHandler();
void drawFrame(uint16_t x[], uint16_t y[], uint8_t onOff[]);
void plotLine(uint16_t x_start, uint16_t x_end, uint16_t y_start, uint16_t y_end, uint32_t ui32SysClkFreq);
void SSIIntHandler(void);
uint16_t** switchArrays(uint16_t x1[], uint16_t y1[], uint8_t onOff1[]);
//uint8_t drawLine (uint16_t x_start, uint16_t x_end, uint16_t y_start, uint16_t y_end,uint32_t ui32SysClkFreq);




#endif /* GALVO_H_ */
