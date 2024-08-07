#include "debug.h"
#include "hw_config.h"
#include "debug.h"
#include "task.h"

#if 0 

void Comm_Check()
{
  if(uCommStatusFlag & f_canDRV160In)		DRV160_In();
	
  if(uCommStatusFlag & f_canSTR707In)		STR707_In();
	uCommStatusFlag &=  ~f_canSTR707In; 
  
  
  //
  if(uCommStatusFlag & f_canRTKDRV323In)	RTKDRV_Con();
  //
  if(uCommStatusFlag & f_canDBG747In)		can_DBGCommand();
  if(uCommStatusFlag & f_canMUF757In)		can_MUFCommand();
  //
#if 0
  * [dbg-0001]{ENT} --> uDebugFlag
  *   1 : Local Key, 2 : Remocon, 3 : Option, 4 : Sensor
  *  10(0A) : �������, 11 : ������� 
  *  20(0x14) : ��������
  *  30(0x1E) : SPI  31(0x1F) : RPM Time  32(0x20) : sysRun Time
  *  40(0x28) : BLE RCV
  *  50(0x32) : ADC_ROTATE KEY, 51(0x33) : ADC BAT VOLTAGE, 52(0x34) : ADC FUAL, 53(0x35) : ADC OIL, 54(0x36) : ADC CHG
#endif
}

#endif 
