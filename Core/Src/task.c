#include "task.h"

uint8_t CAN_RxData[4];
uint32_t ms_cnt = 0;
uint16_t uTimerFlag = 0;
CanTxMsg TxMessage;
uint8_t init_led = 0;
void Event_30ms();
void Event_200ms();
void Event_500ms();	

void Timer_Event()
{
    if(uTimerFlag & TIM_30ms)	Event_30ms();		
    if(uTimerFlag & TIM_200ms)	Event_200ms();
    if(uTimerFlag & TIM_500ms)	Event_500ms();	
}


void Event_30ms()
{
    uTimerFlag &= ~TIM_30ms;
}


void Event_200ms()
{
    uTimerFlag &= ~TIM_200ms;
    
}


void Event_500ms()
{
    
    
    uTimerFlag &= ~TIM_500ms;
    
    
}