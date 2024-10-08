#include "keyscan.h"
uint16_t  R_KeyBuff = 0;
void Lkey_Action();
uint8_t Key_IdentChk(uint16_t In_LocalKey);
uint8_t isAutoCondition();
uint8_t is_NotUrgency();
void DRV_Start();
void STR_Start();
void Drive_REQ(uint8_t Control);
void Rkey_Action();	/* 무선리모컨  */
uint16_t L_KeyBuff;
void LKEY_Check()		/* STIICK 4 Key */
{
    
    L_KeyBuff = ~(GPIOE->IDR >> 3) & 0x000F;
    if(L_KeyBuff != 0 && Key_IdentChk(L_KeyBuff)) 	/* 동시 Key 처리 --> 막는다. */
    {
    Local_Key.lK_Data = L_KeyBuff;
    if(Local_Key.lK_Data == Local_Key.lK_Back)
    {
        if(Local_Key.lK_ChatCnt == 0)
        {
            uKeyStatusFlag |= fLK_Ok;
            uKeyStatusFlag &= ~fLK_Repeat;
            if(Local_Key.lK_Data == Local_Key.lK_Last)
                uKeyStatusFlag |= fLK_Repeat;
            Local_Key.lK_Last = Local_Key.lK_Data;
            Local_Key.lK_ChatCnt = 30;		/* 매 30ms 마다 */
            RK_PermitTime = 3000/30;		/* 3초 뒤 R Key Check */
            Lkey_Action();					
        }
    } 
    else 
    {
        Local_Key.lK_Back = Local_Key.lK_Data;
        Local_Key.lK_ChatCnt = 60;
        uKeyStatusFlag &= ~fLK_Ok;
        uKeyStatusFlag &= ~fLK_Repeat;
    }
    }
    else
    {
    uKeyStatusFlag &= ~fLK_Ok;
    uKeyStatusFlag &= ~fLK_Repeat;
    Local_Key.lK_Data = 0;
    Local_Key.lK_Back = 0;
    Local_Key.lK_Last = 0;
    Local_Key.lK_ChatCnt = 60;
    }
}
void Lkey_Action()
{

    if((Local_Key.lK_Last & KEY_FORWARD)  == KEY_FORWARD)
    {
        if(isAutoCondition() == 0)	
        {
            uKeyStatusFlag |= flk_Forward;
            uKeyStatusFlag &= ~flk_Backward;
            Drive_REQ(KEY_FORWARD);
        }
    }
    else if((Local_Key.lK_Last & KEY_BACKWORD)  == KEY_BACKWORD)
    {
        if(isAutoCondition() == 0)
        {
            uKeyStatusFlag &= ~flk_Forward;
            uKeyStatusFlag |= flk_Backward;
            Drive_REQ(KEY_BACKWORD);
        }	
    }
    else
    {
        uKeyStatusFlag &= ~flk_Forward;
        uKeyStatusFlag &= ~flk_Backward;
    }
    if((Local_Key.lK_Last & KEY_LEFT) == KEY_LEFT)
    {
        if(isAutoCondition() == 0)
        {
            uKeyStatusFlag |= flk_Left;
            uKeyStatusFlag &= ~flk_Right;
            Drive_REQ(KEY_LEFT);
        }	
        
    }
    else if((Local_Key.lK_Last & KEY_RIGHT) == KEY_RIGHT)
    {
        if(isAutoCondition() == 0)	
        {
            uKeyStatusFlag &= ~flk_Left;
            uKeyStatusFlag |= flk_Right;
            Drive_REQ(KEY_RIGHT);
        }
    }
    else
    {
        uKeyStatusFlag &= ~flk_Left;
        uKeyStatusFlag &= ~flk_Right;
    }
}


void RKEY_Check()
{
    #if 1 
    #if 0 
    PC_rKey = (GPIOC->IDR & 0xF000) >> 12;
    PD_rKey = (GPIOD->IDR & 0x001F) << 4;
    R_KeyBuff = PC_rKey | PD_rKey;
    R_KeyBuff &= 0x01FF;
    #endif 
    //R_KeyBuff = CAN_RxData[0];
    
    if(R_KeyBuff & 0xFFFF)		/* RFR_MAIN 제외  */
    {
        RFR_Key.rK_Data = R_KeyBuff;
            
        if(RFR_Key.rK_Data == RFR_Key.rK_Back)
        {
            if(RFR_Key.rK_ChatCnt == 0)
            {
                /* uKeyStatusFlag fLK_Ok */
                uKeyStatusFlag |= fRK_Ok;
                uKeyStatusFlag &= ~fRK_Repeat;
                if(RFR_Key.rK_Data == RFR_Key.rK_Last)
                    uKeyStatusFlag |= fRK_Repeat;
                //		
                RFR_Key.rK_Last = RFR_Key.rK_Data;
                RFR_Key.rK_Back = RFR_Key.rK_Data;
                RFR_Key.rK_ChatCnt = 100;			/* 연속키 처리 타임  매 10ms 마다 */
                Rkey_Action();
                #if 0 
                if(((RFR_Key.rK_Last & RFR_PUMP) == RFR_PUMP) || ((RFR_Key.rK_Last & RFR_FANONUP) == RFR_FANONUP) || ((RFR_Key.rK_Last & RFR_ATDRV) == RFR_ATDRV) || ((RFR_Key.rK_Last & RFR_FANOFF) == RFR_FANOFF)) 
                {
                    if((uKeyStatusFlag & fRK_Repeat) == 0)
                        Rkey_Action();
                    
                }
                else
                {
                    Rkey_Action();
                }
                #endif 
            }
        } 
        else 
        {
            RFR_Key.rK_Back = RFR_Key.rK_Data;
            RFR_Key.rK_ChatCnt = 100;
            uKeyStatusFlag &= ~fRK_Ok;
            uKeyStatusFlag &= ~fRK_Repeat;
        }
    }
    else
    {
        uKeyStatusFlag &= ~fRK_Ok;
        uKeyStatusFlag &= ~fRK_Repeat;
        RFR_Key.rK_Data = 0;
        RFR_Key.rK_Back = 0;
        RFR_Key.rK_Last = 0;
        RFR_Key.rK_ChatCnt = 100;
    }
    #endif
}


void Rkey_Action()	/* 무선리모컨  */
{
  
  if((RFR_Key.rK_Last & RFR_FORWARD)  == RFR_FORWARD)			/* 0x20 */
  {
	if(isAutoCondition() == 0)
	{
		uKeyStatusFlag |= frk_Forward;
		uKeyStatusFlag &= ~frk_Backward;
		Drive_REQ(KEY_FORWARD);
	}
  }
  else if((RFR_Key.rK_Last & RFR_BACKWORD)  == RFR_BACKWORD)	/* 0x01 */
  {
	if(isAutoCondition() == 0)
	{
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
  if((RFR_Key.rK_Last & RFR_LEFT)  == RFR_LEFT)				/* 0x02 */
  {
	if(isAutoCondition() == 0)
	{
		uKeyStatusFlag |= frk_Left;
		uKeyStatusFlag &= ~frk_Right;
		Drive_REQ(KEY_LEFT); 
	}
  }
  else if((RFR_Key.rK_Last & RFR_RIGHT)  == RFR_RIGHT)		/* 0x04 */
  {
	if(isAutoCondition() == 0)
	{
		uKeyStatusFlag |= frk_Right;
		uKeyStatusFlag &= ~frk_Left;
		Drive_REQ(KEY_RIGHT); 
	}
  }
  else
  {
	uKeyStatusFlag &= ~frk_Left;
	uKeyStatusFlag &= ~frk_Right;
  }
  

}

uint8_t Key_IdentChk(uint16_t In_LocalKey) /*동시 Key 블럭*/
{
  if(((In_LocalKey & KEY_FORWARD) == KEY_FORWARD) && ((In_LocalKey & KEY_BACKWORD) == KEY_BACKWORD))
	return 0;
  
  if(((In_LocalKey & KEY_LEFT) == KEY_LEFT) && ((In_LocalKey & KEY_RIGHT) == KEY_RIGHT))
    return 0;
   
  return 1;
}

uint8_t isAutoCondition() /* 자율주행중인지 조건 판단*/
{
  if(u2SysStatusF & f_AutoRun)
	return 1;
  else		
	return 0;
}


void User_Interface()
{
 //Port_ReadACT();
  LKEY_Check();		/* Low BAT. 상태에서도 Local Key 는 동작 한다. */
  RKEY_Check();
    #if 0 
    if((uSysStatusFlag & f_LowBat) == 0)
    {
        if((uKeyStatusFlag & fLK_Ok) == 0)	/* Local Key 가 릴리지 되고 */
        {
            if(RK_PermitTime == 0)			/* 3초 이후부터 RFR을 입력 받는다.*/ 
            {
                RFR_MainCheck();
                if((uSysStatusFlag & f_RFR_Emergency) == 0)
                {
                    RKEY_Check();
                    SMART_check();
                }
                else
                {
                    LKAUTO_CHKSeq();
                    SMART_check();
                }
            }
        }
    }
    #endif
}

void Drive_REQ(uint8_t Control)
{
  switch(Control)
  {
	case KEY_FORWARD:
    {
        u2SysStatusF |= f_DMForward;
		DRV_Start();
    }
    break;

	case KEY_BACKWORD:
    {
        u2SysStatusF &= ~f_DMForward;			
		DRV_Start();
    }
    break;
		
	case KEY_LEFT:
    {
        if((u2SysStatusF & f_LimitLeft) == 0)
		{
			u2SysStatusF |= f_SMLeft;
			STR_Start();
		}
    }
    break;

	case KEY_RIGHT:
    {
        if((u2SysStatusF & f_LimitRight) == 0)
		{
			u2SysStatusF &= ~f_SMLeft;
			STR_Start();
		}
    }
	break;	
		
		
	case KEY_PUMP:
    {
        
    }		
    break;

	case KEY_FANONUP:
    {
        
    }   
	break;
		
	case KEY_FANOFF:
    {
        
    }
	break;

	case KEY_AUTORUN:
    {
        
    }
	break;

	default:
		break;
  }

}

uint8_t is_NotUrgency()
{
  return 0;
}

void DRV_Start()
{
    if((u2SysStatusF & f_DMotorACT) == 0)
    {
        DMotorWaitime = 10;
    }
    DMotorSeq = DMOTOR_START; 		  /* Local & RFR Forward */
    u2SysStatusF |= f_DMotorACT;
}

void STR_Start()
{
    u2SysStatusF |= f_SMotorACT;
	SMotorSeq = SMOTOR_START;
}