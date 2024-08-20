#ifndef __BSP_ADC_H
#define __BSP_ADC_H
#include "define.h"
#include "hw_config.h"
#include "task.h"

extern void get_adc_value();
extern void bsp_adc_init();
extern uint16_t angle_sensor();
#endif 
