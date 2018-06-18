/*
 * snake.h
 *
 *  Created on: 25.05.2018
 *      Author: Alex
 */

#ifndef SNAKE_H_
#define SNAKE_H_
#define CHANCE_STONE    0x23    //The chance of the appearance of a stone in percent
#define CHANCE_STAR     0x0C    //The chance of the appearance of a star in percent
#define NC_Address      0x52    //I2C Address of the nunchuk

uint32_t checkForCollision(uint16_t ui16GameField[][], uint32_t GameStatus);
void calculateNextStep(uint16_t ui16GameField[][], uint32_t GameStatus);
void moveFieldDown(uint16_t ui16GameField[][], uint32_t GameStatus);
void movePlayer(uint16_t ui16GameField[][], uint32_t GameStatus);
uint32_t calculateCycle(uint32_t GameStatus);
uint32_t executeCollision(uint16_t ui16GameField[][], uint32_t GameStatus);
void setupNunchuk(uint32_t ui32SysClkFreq);
uint32_t checkNunchuk(uint32_t GameStatus);
void calculateArray(uint16_t GameField[8][16], uint16_t x[], uint16_t y[], uint8_t onOff[]);
uint8_t drawPlayer(uint8_t ui8CounterPoints, uint16_t x[], uint16_t y[], uint8_t onOff[], uint8_t ui8PositionX, uint8_t ui8PositionY);
uint8_t drawStone(uint8_t ui8CounterPoints, uint16_t x[], uint16_t y[], uint8_t onOff[], uint8_t ui8PositionX, uint8_t ui8PositionY);
uint8_t drawStar(uint8_t ui8CounterPoints, uint16_t x[], uint16_t y[], uint8_t onOff[], uint8_t ui8PositionX, uint8_t ui8PositionY);
uint8_t fillArray(uint8_t ui8CounterPoints, uint16_t x[], uint16_t y[], uint8_t onOff[], uin16_t ui16XValue, uin16_t ui16YValue, uin16_t ui16OnOffValue);


#endif /* SNAKE_H_ */
