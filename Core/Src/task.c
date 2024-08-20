#include "task.h"
#include "bsp_can.h"
#include "bsp_adc.h"
uint8_t CAN_RxData[8];
uint32_t ms_cnt = 0;
uint8_t tm10mS_Cnt = 0;
uint8_t init_led = 0;
void Event_30ms();
void Event_200ms();
void Event_500ms();	
void Event_10ms();

void G_LED_R_Toggle(void)
{
	HAL_GPIO_TogglePin(GPIOE, DBG_LED_R);
}
void D_LED_G_Toggle(void)
{
    HAL_GPIO_TogglePin(GPIOE, DBG_LED_G);
}

void Timer_Event()
{
    if(uTimerFlag & TIM_10ms)	Event_10ms();		
    if(uTimerFlag & TIM_30ms)	Event_30ms();		
    if(uTimerFlag & TIM_200ms)	Event_200ms();
    if(uTimerFlag & TIM_500ms)	Event_500ms();	
}

void Event_10ms()
{
  uTimerFlag &= ~TIM_10ms;
 
  ++tm10mS_Cnt;
  if(tm10mS_Cnt >= 3)
  	tm10mS_Cnt = 0;
  
  switch(tm10mS_Cnt)
  {
	case 1:
		if(RK_PermitTime)	--RK_PermitTime;
		 can1_Trans8b(CAN_DRV);		/* Driver */
		break;
	case 2:
		can1_Trans8b(CAN_MCU);		/* STR */		
		break;
	default:
        can1_Trans8b(CAN_STR);
		break;
  }
  
}

void Event_30ms()
{
    
    if(RK_PermitTime)	--RK_PermitTime;


    uTimerFlag &= ~TIM_30ms;
}


void Event_200ms()
{
    
    uTimerFlag &= ~TIM_200ms;
}


void Event_500ms()
{
    D_LED_G_Toggle();
    G_LED_R_Toggle();
    uTimerFlag &= ~TIM_500ms;
}