
#ifndef __HW_CONFIG_H
#define __HW_CONFIG_H

/* includes */
#include "main.h"
#include "stdio.h"
#include "math.h"
#include "define.h"		/* Define */


/* global variables */
extern bool f_commCAN;			/* Init. UART */



extern uint32_t u2SysStatusF;
extern uint32_t uKeyStatusFlag;
extern uint32_t Received_canID;

extern uint16_t uTimerFlag;
extern uint16_t	uCommStatusFlag; 
extern uint16_t u16_DebugFlag;

extern uint16_t DMotorWaitime;
extern uint16_t SMotorWaitime;
extern uint16_t RK_PermitTime;		/* 100ms */

extern uint8_t t_200msCnt;
extern uint8_t t_1sCnt;


extern uint8_t DMotorSeq; 
extern uint8_t SMotorSeq;
extern uint8_t DRV_PWMDuty;
extern uint8_t STR_PWMDuty;
extern uint8_t DRV_Speed;			/* 1.2.3.4.5 */ 
extern uint8_t	 Received_canIDType;
extern uint8_t	 Received_canDLC;



typedef struct
{
	uint16_t 	lK_Data;
	uint16_t 	lK_Last;
	uint16_t	lK_Back;
	uint16_t 	lK_ChatCnt;
	uint8_t		lkey_Ident;
}LocalKeyType;



typedef struct
{
	uint16_t 	rK_Data;
	uint16_t 	rK_Last;
	uint16_t	rK_Back;
	uint16_t 	rK_ChatCnt;
	uint8_t		rkey_Ident;
}RFRKeyType;



extern LocalKeyType Local_Key;		//  Local_Key.Seq = 0;
extern RFRKeyType RFR_Key;

#endif  /*__HW_CONFIG_H */

