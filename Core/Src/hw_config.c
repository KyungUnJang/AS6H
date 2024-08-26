
#include "task.h"
#include "hw_config.h"

LocalKeyType Local_Key;
RFRKeyType RFR_Key;


bool f_commCAN = FALSE;			/* Init. UART */


uint16_t uTimerFlag = 0;
uint32_t u2SysStatusF = 0;
uint32_t uKeyStatusFlag = 0;
uint16_t u16_DebugFlag = 0;
uint8_t t_200msCnt = 0;
uint8_t t_1sCnt = 0;
uint8_t DMotorSeq = 0;
uint8_t SMotorSeq = 0;
uint16_t DMotorWaitime = 0;
uint16_t SMotorWaitime = 0;
uint16_t RK_PermitTime = 0;
uint8_t DRV_Speed = 1;
uint32_t Received_canID = 0;
uint8_t	 Received_canIDType = 0;
uint8_t	 Received_canDLC = 0;
