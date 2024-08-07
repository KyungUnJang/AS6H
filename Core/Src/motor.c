
#include "motor.h"
#include "bsp_can.h"
uint8_t rAutoMax_Speed = 0;
uint8_t rAutoMax_SpeedBk = 0;


uint16_t uSTR_PWM;		
uint16_t uDRV_RPM;
uint8_t rDRV_DIR;


const unsigned int DRV_SPD[6] = {
	0,800,1200,2000,2500,3000,
};




uint8_t is_DriveKey()
{
  if(((Local_Key.lK_Last & KEY_FORWARD) == KEY_FORWARD) || ((Local_Key.lK_Last & KEY_BACKWORD) == KEY_BACKWORD))
	return 1;
  else
  {
	if(((RFR_Key.rK_Last & RFR_FORWARD) == RFR_FORWARD) || ((RFR_Key.rK_Last & RFR_BACKWORD) == RFR_BACKWORD))
 		return 1;
	else
		return 0;
  }
}

void DM_Stop()
{
  rDRV_DIR = 0;	  /* 0x00: Nutral, 0x01: Forward, 0x02: Reverse */
  uDRV_RPM = 0;
  can1_Trans8b(CAN_DRV);
  if(DMotorSeq != DMOTOR_STOP)		DMotorSeq = DMOTOR_STOP;
  if(u2SysStatusF & f_DMotorACT)	u2SysStatusF &= ~f_DMotorACT;
}

void DRV_Control()
{
  
  if((u2SysStatusF & f_DMotorACT) && (is_DriveKey() == 0))
  {
  	DM_Stop();
  }
  
  switch(DMotorSeq)
  {
	case DMOTOR_START:
		if(DMotorWaitime == 0)
		{
			uDRV_RPM = DRV_SPD[DRV_Speed];
#if _DRV_REVERSE			
			if(u2SysStatusF & f_DMForward)
				rDRV_DIR = 0x02;	/* 0x00: Nutral, 0x01: Forward, 0x02: Reverse */				
			else
				rDRV_DIR = 0x01;	/* 0x00: Nutral, 0x01: Forward, 0x02: Reverse */				
#else
			if(u2SysStatusF & f_DMForward)
				rDRV_DIR = 0x01;	/* 0x00: Nutral, 0x01: Forward, 0x02: Reverse */				
			else
				rDRV_DIR = 0x02;	/* 0x00: Nutral, 0x01: Forward, 0x02: Reverse */				
#endif
			DMotorWaitime = 0;
			DMotorSeq = DMOTOR_END;
		}
		break;
		//
	case DMOTOR_END:		
	default:		
		
		break;
  }
}

uint8_t is_StrringKey()
{
  if(((Local_Key.lK_Last & KEY_LEFT) == KEY_LEFT) || ((Local_Key.lK_Last & KEY_RIGHT) == KEY_RIGHT))
	return 1;
  else
  {
	if(((RFR_Key.rK_Last & RFR_LEFT) == RFR_LEFT) || ((RFR_Key.rK_Last & RFR_RIGHT) == RFR_RIGHT))
		return 1;
	else
	{
		if(((RFR_Key.rK_Last & RFR_FORWARD) == RFR_FORWARD))
			return 1;
		else
			return 0;
	}
  }
}

void SM_Stop()
{
  uSTR_PWM = 0;			
  can1_Trans8b(CAN_STR);
  if(SMotorSeq != SMOTOR_STOP)		SMotorSeq = SMOTOR_STOP;
  if(u2SysStatusF & f_SMotorACT)	u2SysStatusF &= ~f_SMotorACT;
  
}


void STR_Control()
{
  if((u2SysStatusF & f_SMotorACT) && (is_StrringKey() == 0))
  {
	SM_Stop();  
  }
  //
  switch(SMotorSeq)
  {
	case SMOTOR_START:
		//Port_ReadACT();
		if(SMotorWaitime == 0)
		{
			//uSTR_PWM = 1000;	/* 0x3E8 : <L> <--> <R>  158 x 30ms  4,740 */ 
			//uSTR_PWM = 1500;	/* 0x5DC : <L> <--> <R>  100 x 30ms  3,000 */ 
			//uSTR_PWM = 2000;	/* 0x7D0 : <L> <--> <R>   73 x 30ms  2,190 */ 
			//uSTR_PWM = 2200;	/* 0x7D0 : <L> <--> <R>   66 x 30ms  1,980 */ 
			//uSTR_PWM = 2400;	/* 0x7D0 : <L> <--> <R>   61 x 30ms  1,830 */ 
			//uSTR_PWM = 2600;	/* 0x7D0 : <L> <--> <R>   56 x 30ms  1,680 */ 
			//uSTR_PWM = 2800;	/* 0x7D0 : <L> <--> <R>   52 x 30ms  1,560 */ 
			//uSTR_PWM = 3000;	/* 0x7D0 : <L> <--> <R>   49 x 30ms  1,470 */ 
			uSTR_PWM = 2000;
			if((u2SysStatusF & f_SMLeft) == 0)
				uSTR_PWM = (0xFFFF - uSTR_PWM) + 1;	/* Right */	
			
			SMotorWaitime = 0;
			SMotorSeq = SMOTOR_END;
		}
		break;
		//
	case SMOTOR_END:		
	default:		
		break;
  }
}


void all_MotorStop()
{

    DM_Stop();		/* DRV Motor Stop */
    SM_Stop();		/* STR Motor Stop */

    LKAUTOSeq = 0;
    
}

//
void Motor_Control()
{
    if(u2SysStatusF & f_DMotorACT)	DRV_Control();
    if(u2SysStatusF & f_SMotorACT)	STR_Control();
}

