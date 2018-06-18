#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
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
#include <driverlib/i2c.h>
#include "galvo.h"
#include "writing.h"
#include "snake.h"

uint32_t checkForCollision(uint16_t ui16GameField[8][16], uint32_t GameStatus){

    uint8_t ui8ColumnPlayer = GameStatus>>8 & 0x000000FF;
    uint8_t ui8RowPlayer = GameStatus >>16 & 0x000000FF;
    GameStatus &= 0x11111100;
    switch(ui16GameField[ui8ColumnPlayer][ui8RowPlayer+1] & 0x0003){
       case 0   :                               break;
       case 2   :   GameStatus |= 10<<4 | 1<<1; break;
       case 3   :   GameStatus |= 11<<4 | 1<<1; break;
    }

    if(ui8ColumnPlayer < (sizeof(ui16GameField)/sizeof(ui16GameField[0]))-2){
        switch(ui16GameField[ui8ColumnPlayer+1][ui8RowPlayer] & 0x0003){
            case 0   :                                  break;
            case 2   :   GameStatus |= 10<<4 | 1<<2;    break;
            case 3   :   GameStatus |= 11<<4 | 1<<2;    break;
        }
    }
    if(ui8ColumnPlayer > 0){
        switch(ui16GameField[ui8ColumnPlayer-1][ui8RowPlayer] & 0x0003){
            case 0   :                                  break;
            case 2   :   GameStatus |= 10<<4 | 1<<3;    break;
            case 3   :   GameStatus |= 11<<4 | 1<<3;    break;
        }
    }

    //The following code will check if there is a block two rows above the player (which would be relevant if the player wanted
    //to move up in the same cycle the field moves down) and below the player. Since for now the player will only be able
    //to move left or right, this is not relevant.
//    switch(ui8GameField[ui8ColumnPlayer][ui8RowPlayer+2] & 0x0003){
//       case 0   :   GameStatus &= 0<<6;         break;
//       case 2   :
//       case 3   :   GameStatus |= 1<<6;         break;
//    }
//    switch(ui8GameField[ui8ColumnPlayer][ui8RowPlayer-1] & 0x0003){
//        case 0  :                               break;
//        case 2  :   GameStatus |= 10<<4 | 1;    break;
//        case 3  :   GameStatus |= 11<<4 | 1;    break;
//    }

    return GameStatus;
}

void calculateNextStep(uint16_t ui16GameField[][], uint32_t GameStatus){
    if(!(GameStatus>>5 & 0x0000001))                //no collision detected
    //Since the player should have the chance to move more often than the whole field moves the field moves down every
    //fourth cycle and the player can move every cycle
    {
        if(GameStatus>>20 & 0x0000003 != 3)         //Less than 4 cycles since the field moved the last time
        {
            if(GameStatus >> 16 & 0x00000F)         //Player wants to move
                movePlayer(ui16GameField, GameStatus);   //Player can move
            GameStatus = calculateCycle(GameStatus);
        }
        else                                        //Four cycles since the field moved the last time -> field moves again
        {
            moveFieldDown(ui16GameField, GameStatus);
//            if((GameStatus >> 16 & 0x00000F)    &&  (!(GameStatus>>6 & 0x00000001) || !(GameStatus>>17 &0x0000001)))  //If there's a block two rows above the player and the player moves up they would end at the same position. In this case the player is not allowed to move up. Furthermore it is important to check whether the player wants to move at all.
            if(GameStatus >> 16 & 0x00000F)         //Check if the player wants to move at all
                movePlayer(ui16GameField, GameStatus);
            GameStatus = calculateCycle(GameStatus);
        }
    }
    else                                            //a collision has been detected
    {
//        if(GameStatus & 0x00000001)                 //there's a collision with a block below the player
//        {
//            if(GameStatus>>20 & 0x0000003 != 4)     //less than 4 cycles since the last time the field moved
//            {
//                GameStatus = calculateCycle(GameStatus);
//                if(GameStatus >>17 & 0x0000007)     //Player wants to move up, left or right
//                    movePlayer(ui8GameField, GameStatus);
//            }
//            else                                    //4 cycles have passed and the field can be moved down
//            {
//                moveFieldDown(ui8GameField, GameStatus);
//                GameStatus = calculateCycle(GameStatus);
//                if(GameStatus >> 16 & 0x00000F)         //Player wants to move
//                    movePlayer(ui8GameField, GameStatus);   //Player can move
//            }
//        }

        if(GameStatus & 0x00000002)            //Collision with a block above
            if(GameStatus)                          //stop the whole process and let the collision take place
                executeCollision(ui16GameField, GameStatus);
                if(GameStatus >> 16 & 0x00000F)         //Check if the player wants to move at all
                        movePlayer(ui16GameField, GameStatus);

        else if(GameStatus & 0x00000004)            //Collision on the right side
        {
            if(GameStatus>>20 & 0x0000003 == 3)     //4 cycles have passed since the field moved the last time -> move field
                moveFieldDown(ui16GameField, GameStatus);
            GameStatus = calculateCycle(GameStatus);
            if(GameStatus>>16 & 0x000000B)      //Player wants to move upwards, downwards or to the left
                    movePlayer(ui16GameField, GameStatus);

        }

        else if(GameStatus & 0x00000008)            //Collision on the left side
        {
            if(GameStatus>>20 & 0x0000003 == 3)     //4 cycles have passed since the field moved the last time -> move field
                moveFieldDown(ui16GameField, GameStatus);
            GameStatus = calculateCycle(GameStatus);
            if(GameStatus>>16 & 0x0000007)          //Player wants to move upwards, downwards or to the right
                    movePlayer(ui16GameField, GameStatus);

        }
    }
}

//The field should only move every 4th cycle. The number of cycles since the last movement are saved in GameStatus bits 20 and 21.
//This function notices the amount of cycles and updates it (0->1->2->3->0) every time it is called. Therefore it must only be called
//once every cycle.
uint32_t calculateCycle(uint32_t GameStatus){
    uint8_t ui8Cycle = GameStatus>>20 & 0x0000003;
    if(ui8Cycle < 3)
        ui8Cycle++;
    else
        ui8Cycle = 0;
    GameStatus = (GameStatus & 0xFFCFFFFF) | ui8Cycle<<20;
    return GameStatus;
}

uint32_t executeCollision(uint16_t ui16GameField[8][16], uint32_t GameStatus){
    uint8_t ui8ColumnPlayer = GameStatus>>8 & 0x000000FF;
    uint8_t ui8RowPlayer = GameStatus >>16 & 0x000000FF;
    uint8_t ui8TypeBlock = ui16GameField[ui8ColumnPlayer][ui8RowPlayer+1] & 0x0003;
    uint16_t ui16ValueBlock = ui16GameField[ui8ColumnPlayer][ui8RowPlayer+1]>>2;
    uint16_t ui16ValuePlayer = ui16GameField[ui8ColumnPlayer][ui8RowPlayer]>>2;

    ui16ValueBlock--;                                                               //Make value of the block go down
    if(ui8TypeBlock == 2)                                                           //Block is a stone
        ui16ValuePlayer--;                                                          //Make the players lifes go down
    else if(ui8TypeBlock == 3)                                                      //Block is a star
        ui16ValuePlayer++;                                                          //Make the players lifes go up

    if(ui16ValuePlayer == 0)                                                        //Player has no more lifes
        GameStatus &= 0x7FFFFFFF;                                                   //Make game stop
    if(ui16ValueBlock)                                                              //Block has no more value
    {
        GameStatus &= 0xFFFFFFDD;                                                   //Change GameStatus to no collision and no collision above
        ui8TypeBlock = 0;                                                           //Change block in the array
    }
    ui16GameField[ui8ColumnPlayer][ui8RowPlayer+1] = ui16ValueBlock<<2 | ui8TypeBlock;
    ui16GameField[ui8ColumnPlayer][ui8RowPlayer] = (ui16GameField[ui8ColumnPlayer][ui8RowPlayer] & 0x0003) | ui16ValuePlayer<<2;
    return GameStatus;
}

void moveFieldDown(uint16_t ui16GameField[8][16], uint32_t GameStatus){
    static uint16_t ui16NumberOfFieldMovements = 1;
    uint8_t ui8CounterY;
    uint8_t ui8CounterX;
    uint8_t ui8NextBlock;
    uint8_t ui8ChanceStone;
    uint8_t ui8ChanceStar;

    for(ui8CounterY = 1; ui8CounterY < 15; ui8CounterY++)
        for(ui8CounterX = 0; ui8CounterX < 16; ui8CounterX++)
            ui16GameField[ui8CounterX][ui8CounterY-1] = ui16GameField[ui8CounterX][ui8CounterY];
    ui8ChanceStone = CHANCE_STONE>>(ui16NumberOfFieldMovements % 2);
    ui8ChanceStar = CHANCE_STAR>>(ui16NumberOfFieldMovements % 2);

    srand(time(NULL));
    for(ui8CounterX = 0; ui8CounterX < 16; ui8CounterX++){
        ui8NextBlock = rand() % 100;
        if(ui8NextBlock > 100-ui8ChanceStone)
            ui16GameField[ui8CounterX][15] = ui16NumberOfFieldMovements<<2 | 0b10;
        else if(ui8NextBlock > 100-ui8ChanceStone-ui8ChanceStar)
            ui16GameField[ui8CounterX][15] = ui16NumberOfFieldMovements<<2 | 0b11;
        else
            ui16GameField[ui8CounterX][15] = 0x0000;
    }
    ui16NumberOfFieldMovements++;
}

void setUpNunchuk(uint32_t ui32SysClkFreq){

    // Enable GPION and I2C
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
    SysCtlPeripheralReset(SYSCTL_PERIPH_I2C2);                        // reset I2C if it has already been activated
    SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C2);
    SysCtlDelay(3); // wait a bit before accessing

    //Configure Pins
    GPIOPinConfigure(GPIO_PN5_I2C2SCL);
    GPIOPinConfigure(GPIO_PN4_I2C2SDA);
    GPIOPinTypeI2CSCL(GPIO_PORTN_BASE, GPIO_PIN_5);
    GPIOPinTypeI2C(GPIO_PORTN_BASE, GPIO_PIN_4);

    // Initialize I2C master peripheral, false = 100 kBits/s, true = 400 kBit/s
    I2CMasterInitExpClk(I2C2_BASE, ui32SysClkFreq, false);

    SysCtlDelay(3);         // wait a bit

    // Configure Nunchuk -> SEND 0xF0, 0x55 STOP SEND 0xFB 0x00
    I2CMasterSlaveAddrSet(I2C2_BASE, NC_Address, false);
    I2CMasterDataPut(I2C2_BASE, 0xF0);
    I2CMasterControl(I2C2_BASE,I2C_MASTER_CMD_BURST_SEND_START);
    SysCtlDelay(500);                           // wait 500
    while (I2CMasterBusy(I2C2_BASE)) { }        // check if I2C still busy

    I2CMasterDataPut(I2C2_BASE, 0x55);
    I2CMasterControl(I2C2_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);
    SysCtlDelay(500);      // wait 500
    while (I2CMasterBusy(I2C2_BASE)) { }        // check if I2C still busy

    I2CMasterSlaveAddrSet(I2C2_BASE, NC_Address, false);
    I2CMasterDataPut(I2C2_BASE, 0xFB);
    I2CMasterControl(I2C2_BASE,I2C_MASTER_CMD_BURST_SEND_START);
    SysCtlDelay(500);                           // wait 500
    while (I2CMasterBusy(I2C2_BASE)) { }        // check if I2C still busy

    I2CMasterDataPut(I2C2_BASE, 0x00);
    I2CMasterControl(I2C2_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);
    SysCtlDelay(500);                           // wait 500
    while (I2CMasterBusy(I2C2_BASE)) { }
}

uint32_t readValuesNunchuk(uint32_t GameStatus){

    char buffer[3];
    uint8_t ui8counter;

    //for-loop because values are only stable if you check them 3 times in a row
    //Big SysCtlDelays instead of a for-loop do not solve the problem
    for(ui8counter = 0; ui8counter<3; ui8counter++){
        SysCtlDelay(50000);

        //Send 0x00 -> Register where values lay
        I2CMasterSlaveAddrSet(I2C2_BASE, NC_Address, false);
        I2CMasterDataPut(I2C2_BASE, 0x00);
        I2CMasterControl(I2C2_BASE, I2C_MASTER_CMD_SINGLE_SEND);
        SysCtlDelay(300);                           // wait 500
        while (I2CMasterBusy(I2C2_BASE)) { }        // check if I2C still busy

        //read x-axis
        I2CMasterSlaveAddrSet(I2C2_BASE, NC_Address, true);
        I2CMasterControl(I2C2_BASE, I2C_MASTER_CMD_BURST_RECEIVE_START);
        SysCtlDelay(300);                           // wait 500
        while (I2CMasterBusy(I2C2_BASE)) { }        // check if I2C still busy
        buffer[0] = I2CMasterDataGet(I2C2_BASE);

        //read y-axis
        I2CMasterControl(I2C2_BASE, I2C_MASTER_CMD_BURST_RECEIVE_CONT);
        SysCtlDelay(300);                           // wait 500
        while (I2CMasterBusy(I2C2_BASE)) { }        // check if I2C still busy
        buffer[1] = I2CMasterDataGet(I2C2_BASE);

        //no relevant data
        I2CMasterControl(I2C2_BASE, I2C_MASTER_CMD_BURST_RECEIVE_CONT);
        SysCtlDelay(300);                           // wait 500
        while (I2CMasterBusy(I2C2_BASE)) { }        // check if I2C still busy
        I2CMasterDataGet(I2C2_BASE);

        //no relevant data
        I2CMasterControl(I2C2_BASE, I2C_MASTER_CMD_BURST_RECEIVE_CONT);
        SysCtlDelay(300);                           // wait 500
        while (I2CMasterBusy(I2C2_BASE)) { }        // check if I2C still busy
        I2CMasterDataGet(I2C2_BASE);

        //no relevant data
        I2CMasterControl(I2C2_BASE, I2C_MASTER_CMD_BURST_RECEIVE_CONT);
        SysCtlDelay(300);                           // wait 500
        while (I2CMasterBusy(I2C2_BASE)) { }        // check if I2C still busy
        I2CMasterDataGet(I2C2_BASE);

        //read last bit for c and z buttons -> z button lsb (0. bit), c button 1. bit
        I2CMasterControl(I2C2_BASE, I2C_MASTER_CMD_BURST_RECEIVE_FINISH);
        SysCtlDelay(300);                           // wait 500
        while (I2CMasterBusy(I2C2_BASE)) { }        // check if I2C still busy
        buffer[2] = I2CMasterDataGet(I2C2_BASE);
    }

    GameStatus = (GameStatus & 0x9FF0FFFF) | ~buffer[2]<<29;
    if(buffer[0] < 120)
        GameStatus |= 1<<19;
    else if(buffer[0] > 145)
        GameStatus |= 1<<18;
    return GameStatus;
}

void calculateArray(uint16_t GameField[8][16], uint16_t x[], uint16_t y[], uint8_t onOff[]){
    uint8_t ui8CounterX;
    uint8_t ui8CounterY;
    uint8_t ui8CounterPoints = 0;
    uint8_t ui8NumberOfRows = sizeof(GameField)/sizeof(GameField[0]);

    for(ui8CounterX = 0; ui8CounterX < sizeof(x); ui8CounterX++){
        x[ui8CounterX] = 0;
        y[ui8CounterX] = 0;
        onOff[ui8CounterX] = 0;
    }

    for(ui8CounterY=0; ui8CounterY<sizeof(GameField[0]); ui8CounterY++)
        for(ui8CounterX=0; ui8CounterX<ui8NumberOfRows; ui8CounterX++)
            switch(GameField[ui8CounterX][ui8CounterY] & 0x0003){
            case 0  :   break;
            case 1  :   ui8CounterPoints = drawPlayer(ui8CounterPoints, x, y, onOff, ui8CounterX, ui8CounterY);
            case 2  :   ui8CounterPoints = drawStone(ui8CounterPoints, x, y, onOff, ui8CounterX, ui8CounterY);
            case 3  :   ui8CounterPoints = drawStar(ui8CounterPoints, x, y, onOff, ui8CounterX, ui8CounterY);
            }
}

uint8_t drawPlayer(uint8_t ui8CounterPoints, uint16_t x[], uint16_t y[], uint8_t onOff[], uint16_t ui16PositionX, uint16_t ui16PositionY){
    ui16PositionX = ui16PositionX*256+128;
    ui16PositionY = ui16PositionY*256+128;
    ui8CounterPoints = fillArray(ui8CounterPoints, x, y, onOff, ui16PositionX-128, ui16PositionY-128, 0);
    ui8CounterPoints = fillArray(ui8CounterPoints, x, y, onOff, ui16PositionX, ui16PositionY+128, 1);
    ui8CounterPoints = fillArray(ui8CounterPoints, x, y, onOff, ui16PositionX+128, ui16PositionY-128, 1);
    ui8CounterPoints = fillArray(ui8CounterPoints, x, y, onOff, ui16Cui8PositionXenterX-128, ui16PositionY-128, 1);
    return ui8CounterPoints;
}
uint8_t drawStone(uint8_t ui8CounterPoints, uint16_t x[], uint16_t y[], uint8_t onOff[], uint16_t ui16PositionX, uint16_t ui16PositionY){
    ui16PositionX = ui16PositionX*256+128;
    ui16PositionY = ui16PositionY*256+128;
    ui8CounterPoints = fillArray(ui8CounterPoints, x, y, onOff, ui16CenterX-128, ui16CenterY-128, 0);
    ui8CounterPoints = fillArray(ui8CounterPoints, x, y, onOff, ui16CenterX-128, ui16CenterY+128, 1);
    ui8CounterPoints = fillArray(ui8CounterPoints, x, y, onOff, ui16CenterX+128, ui16CenterY+128, 1);
    ui8CounterPoints = fillArray(ui8CounterPoints, x, y, onOff, ui16CenterX+128, ui16CenterY-128, 1);
    ui8CounterPoints = fillArray(ui8CounterPoints, x, y, onOff, ui16CenterX-128, ui16CenterY-128, 1);
    return ui8CounterPoints;
}
uint8_t drawStar(uint8_t ui8CounterPoints, uint16_t x[], uint16_t y[], uint8_t onOff[], uint16_t ui16PositionX, uint16_t ui16PositionY){
    ui16PositionX = ui16PositionX*256+128;
    ui16PositionY = ui16PositionY*256+128;
    ui8CounterPoints = fillArray(ui8CounterPoints, x, y, onOff, ui16PositionX-128, ui16PositionY+128, 0);
    ui8CounterPoints = fillArray(ui8CounterPoints, x, y, onOff, ui16PositionX+128, ui16PositionY+128, 1);
    ui8CounterPoints = fillArray(ui8CounterPoints, x, y, onOff, ui16PositionX, ui16PositionY-128, 1);
    ui8CounterPoints = fillArray(ui8CounterPoints, x, y, onOff, ui16PositionX-128, ui16PositionY+128, 1);
    return ui8CounterPoints;
}

uint8_t fillArray(uint8_t ui8CounterPoints, uint16_t x[], uint16_t y[], uint8_t onOff[], uin16_t ui16XValue, uin16_t ui16YValue, uin16_t ui16OnOffValue){
    x[ui8CounterPoints] = ui16XValue;
    y[ui8CounterPoints] = ui16YValue;
    onOff[ui8CounterPoints] = ui16OnOffValue;
    return ++ui8CounterPoints;
}

