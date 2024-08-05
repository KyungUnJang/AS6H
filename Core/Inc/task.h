#ifndef __BSP_TASK_H
#define __BSP_TASK_H

#include "define.h"

extern uint32_t ms_cnt;
extern uint16_t uTimerFlag;
extern uint8_t INIT_FLAG;
extern uint8_t CAN_RxData[4];
extern void Timer_Event();

typedef struct 
{
    uint32_t StdId; 
    uint32_t ExtId; 
    uint8_t IDE;    
    uint8_t RTR;    
    uint8_t DLC;    
    uint8_t Data[8];
}CanTxMsg;


typedef struct 
{
    uint32_t StdId; 
    uint32_t ExtId; 
    uint8_t IDE;    
    uint8_t RTR;    
    uint8_t DLC;    
    uint8_t Data[8];
    uint8_t FMI;
}CanRxMsg;

#endif 