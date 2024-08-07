#include "hw_config.h"
#include "bsp_can.h"
#include "motor.h"
CanTxMsg TxMessage;
uint32_t TxMailbox;
extern CAN_HandleTypeDef hcan;
CAN_TxHeaderTypeDef txHeader; //CAN Bus Receive Header
CAN_FilterTypeDef sFilterConfig; //declare CAN filter structure

void can1_Trans8b(uint8_t Command) 
{
  switch(Command)
  {
	case CAN_STR:	  /* STR Driver Control */ 
		if((u2SysStatusF & f_AutoRun) == 0)
		{
			TxMessage.Data[0] = uSTR_PWM & 0x00FF;
			TxMessage.Data[1] = uSTR_PWM >> 8;
			TxMessage.Data[2] = 0;
											  
			TxMessage.StdId = 0x187;
			TxMessage.DLC = 3;
			TxMessage.RTR = CAN_RTR_DATA;
			TxMessage.IDE = CAN_ID_STD;
			HAL_CAN_AddTxMessage(&hcan, &txHeader, TxMessage.Data, &TxMailbox);
		}
		break;
		//
	case CAN_DRV:		/* DRV Driver Control */ 
		if((u2SysStatusF & f_AutoRun) == 0)
		{
			TxMessage.Data[0] = uDRV_RPM & 0x00FF;
			TxMessage.Data[1] = uDRV_RPM >> 8;
			TxMessage.Data[2] = 0x01;		/* Interlock signal (0x01: Drive&Steer ON) */

			TxMessage.Data[3] = 0;
			TxMessage.Data[4] = 0;
			if(rDRV_DIR == 1)			/* FOR */
				TxMessage.Data[3] = 1;
			else if(rDRV_DIR == 2)		/* BACK */	
				TxMessage.Data[4] = 1;
			//
			TxMessage.StdId = 0x323;
			TxMessage.DLC = 5;
			TxMessage.RTR = CAN_RTR_DATA;
			TxMessage.IDE = CAN_ID_STD;
			HAL_CAN_AddTxMessage(&hcan, &txHeader, TxMessage.Data, &TxMailbox);
		}
		break;
		//
	default:		/* MCU Status Broadcast */
		if((u2SysStatusF & f_Heartbeat) == 0)
			u2SysStatusF |= f_Heartbeat;
		else
			u2SysStatusF &= ~f_Heartbeat;
		// 						
		TxMessage.Data[0] = u2SysStatusF & 0x000000FF;			/* BP07 - BP00 */ 
		TxMessage.Data[1] = (u2SysStatusF >> 8) & 0x000000FF;	/* BP15 - BP08 */
#if 1
		if(u2SysStatusF & f_RFR_Emergency)
		{
			if(LKAUTOSeq >= 6)
				TxMessage.Data[1] &= 0xBF;			/* 1011 1111 RFR_Emergency �� �����ؼ� ����. */ 			
		}
#endif
		TxMessage.Data[2] = rAutoMax_Speed;
		TxMessage.StdId = 0x737;
		TxMessage.DLC = 3;
		TxMessage.RTR = CAN_RTR_DATA;
		TxMessage.IDE = CAN_ID_STD;
		HAL_CAN_AddTxMessage(&hcan, &txHeader, TxMessage.Data, &TxMailbox);
		break;
  }
}