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
	#if 1 
  switch(Command)
  {
	case CAN_STR:	  /* STR Driver Control */ 
		if((u2SysStatusF & f_AutoRun) == 0)
		{
			TxMessage.Data[0] = uSTR_PWM & 0x00FF;
			TxMessage.Data[1] = uSTR_PWM >> 8;
			TxMessage.Data[2] = 0;
											  
			txHeader.StdId = 0x187;
			txHeader.DLC = 3;
			txHeader.RTR = CAN_RTR_DATA;
			txHeader.IDE = CAN_ID_STD;
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
			
			txHeader.StdId = 0x323;
			txHeader.DLC = 5;
			txHeader.RTR = CAN_RTR_DATA;
			txHeader.IDE = CAN_ID_STD;

			HAL_CAN_AddTxMessage(&hcan, &txHeader, TxMessage.Data, &TxMailbox);
		}
		break;
		case CAN_CRABLE:
		{
			if((u2SysStatusF & f_AutoRun) == 0)
			{
				TxMessage.Data[0] = 0xFF;
				txHeader.StdId = 0x123;
				txHeader.DLC = 1;
				txHeader.RTR = CAN_RTR_DATA;
				txHeader.IDE = CAN_ID_STD;
				HAL_CAN_AddTxMessage(&hcan, &txHeader, TxMessage.Data, &TxMailbox);
			}
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
		TxMessage.Data[2] = 0X03;
		TxMessage.Data[0] |=0X40;

		txHeader.StdId = 0x737;
		txHeader.DLC = 3;
		txHeader.RTR = CAN_RTR_DATA;
		txHeader.IDE = CAN_ID_STD;
		HAL_CAN_AddTxMessage(&hcan, &txHeader, TxMessage.Data, &TxMailbox);
		break;
  }
  #endif 
}

void bsp_can_init()
{
    TxMessage.Data[0] = 0x11; 
    TxMessage.Data[1] = 0;
    TxMessage.Data[2] = 0;
    TxMessage.Data[3] = 0x44;
    txHeader.DLC = 8;
    txHeader.IDE = CAN_ID_STD;
    txHeader.RTR = CAN_RTR_DATA;
    txHeader.StdId = 0x737;
    //txHeader.ExtId = 0x02;
    txHeader.TransmitGlobalTime = DISABLE;

    
	#if 1 
  	sFilterConfig.FilterFIFOAssignment=CAN_FILTER_FIFO0; //set fifo assignment
	sFilterConfig.FilterIdHigh=0x737; //the ID that the filter looks for (switch this for the other microcontroller)
	sFilterConfig.FilterIdLow=0;
	sFilterConfig.FilterMaskIdHigh=0;
	sFilterConfig.FilterMaskIdLow=0;
	sFilterConfig.FilterScale=CAN_FILTERSCALE_32BIT; //set filter scale
	sFilterConfig.FilterActivation=ENABLE;

    
	
	HAL_CAN_ConfigFilter(&hcan, &sFilterConfig); //configure CAN filter
	HAL_CAN_Start(&hcan); //start CAN
	HAL_CAN_ActivateNotification(&hcan, CAN_IT_RX_FIFO0_MSG_PENDING); //enable interrupts
  #endif 

}


#if 0 

void CAN_DT_Remote()
{
	

	if((CAN_Rx_Remote[6] & CAN_R_FORWARD)  == CAN_R_FORWARD)			//0x01
	{
		if(isAutoCondition() == 0 )
		{
			if ( (CAN_Rx_Remote[6] & CAN_R_BACKWORD)  != CAN_R_BACKWORD)
			uKeyStatusFlag |= frk_Forward;
			uKeyStatusFlag &= ~frk_Backward;
			Drive_REQ(KEY_FORWARD);
		}
	}
	else if((CAN_Rx_Remote[6] & CAN_R_BACKWORD)  == CAN_R_BACKWORD)	 // 0x02 
	{
		if(isAutoCondition() == 0)
		{
			if ( (CAN_Rx_Remote[6] & CAN_R_FORWARD)  != CAN_R_FORWARD)
			uKeyStatusFlag |= frk_Backward;
			uKeyStatusFlag &= ~frk_Forward;
			Drive_REQ(KEY_BACKWORD); 
		}
	}
	else
	{
		uKeyStatusFlag &= ~frk_Forward;
		uKeyStatusFlag &= ~frk_Backward;
	}
	//
	if((CAN_Rx_Remote[4] & CAN_R_RIGHT)  == CAN_R_RIGHT)		// 0x40
	{
		if(isAutoCondition() == 0)
		{
			if ( (CAN_Rx_Remote[6] & CAN_R_LEFT)  != CAN_R_LEFT)
			uKeyStatusFlag |= frk_Right;
			uKeyStatusFlag &= ~frk_Left;
			Drive_REQ(KEY_RIGHT); 
		}
	}
	else if((CAN_Rx_Remote[4] & CAN_R_LEFT)  == CAN_R_LEFT)				// 0x20
	{
		if(isAutoCondition() == 0)
		{
			if ( (CAN_Rx_Remote[6] & CAN_R_RIGHT)  != CAN_R_RIGHT)
			uKeyStatusFlag |= frk_Left;
			uKeyStatusFlag &= ~frk_Right;
			Drive_REQ(KEY_LEFT); 
		}
	}
	
	else
	{
		uKeyStatusFlag &= ~frk_Left;
		uKeyStatusFlag &= ~frk_Right;
	}
	//  
	if((CAN_Rx_Remote[4] & CAN_R_FANOFF) == CAN_R_FANOFF)		//0x08
	{
		if(u16_DebugFlag == 1)
		{
			cliPrintf("\n FAN_OFF");
		}
		uKeyStatusFlag |= frk_FanOff;
		Drive_REQ(KEY_FANOFF);  
	}
	else if((CAN_Rx_Remote[4] & CAN_R_FANONUP) == CAN_R_FANONUP) // 0x04
	{
		if ( fan_check_dly == 0 )
		{
			fan_check_dly = 200;
			uKeyStatusFlag |= frk_FanOnUp;
			Drive_REQ(KEY_FANONUP);  
		}
		
	}
	else
	{
		if ( fan_check_dly == 0 )
		{
			fan_check_dly = 200;
			uKeyStatusFlag &= ~frk_FanOnUp;
			uKeyStatusFlag &= ~frk_FanOff;
		}
		
	}

	if((CAN_Rx_Remote[4] & CAN_R_PUMP) == CAN_R_PUMP)   //0x08
	{
		if ( pump_check_dly < 1)
		{
			if(u16_DebugFlag == 1)
			{
				cliPrintf("\n RFR_PUMP");
			}
			uKeyStatusFlag |= frk_Pump;
			Drive_REQ(KEY_PUMP);
			pump_check_dly = 200;
		}
		  			
	}
	else
	{
		if ( pump_check_dly < 1)
		{
			uKeyStatusFlag &= ~frk_Pump;
			pump_check_dly = 200;
		}
		 	
	}
	
	//
	if((CAN_Rx_Remote[4] & CAN_R_ATDRV) == CAN_R_ATDRV)      //0x04
	{
		if ( atdrv_check_dly == 0)
		{
			atdrv_check_dly = 200;
			uKeyStatusFlag |= frk_AutoDrv;
			Drive_REQ(KEY_AUTORUN);  				
		}
		
	}

	#if ADD_KEY 
	#if 0
/* 추가되는 기능 FN , MODE 기능 추가키 */
	if((CAN_Rx_Remote[4] & CAN_R_FN) == CAN_R_FN)   //0x40
	{
		auto_run_check_time = 10000;
		if(u16_DebugFlag == 1)
		{
			cliPrintf("\n CAN_R_FN");
		}
		//uKeyStatusFlag |= frk_Pump;
		//Drive_REQ(KEY_PUMP);  			
	}
	else
	{
		//uKeyStatusFlag &= ~frk_Pump; 	
	}
	
	if((CAN_Rx_Remote[4] & CAN_R_MODE) == CAN_R_MODE)   //0x80
	{
		if(u16_DebugFlag == 1)
		{
			cliPrintf("\n CAN_R_MODE");
		}
		//uKeyStatusFlag |= frk_Pump;
		//Drive_REQ(KEY_PUMP);  			
	}
	else
	{
		//uKeyStatusFlag &= ~frk_Pump; 	
	}
	#endif 
	#endif 

}

#endif 