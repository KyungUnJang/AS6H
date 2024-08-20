#ifndef __BSP_CAN_H
#define __BSP_CAN_H



#include "define.h"
#include "hw_config.h"
#include "task.h"
extern void can1_Trans8b(uint8_t Command);
extern void bsp_can_init();

#endif 