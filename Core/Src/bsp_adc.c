
#include "bsp_adc.h"


#define NUMBER_ADC_CHANNEL 1
#define NUMBER_ADC_CHANNEL_AVERAGE_PER_CHANNEL 8

uint16_t ADC_DMA_BUFF[NUMBER_ADC_CHANNEL * NUMBER_ADC_CHANNEL_AVERAGE_PER_CHANNEL]={0};

extern ADC_HandleTypeDef hadc1;
extern DMA_HandleTypeDef hdma_adc1;

#define Speed_MAX_SIZE		5
#define Angle_MAX_SIZE      5

float   outValue; 
float   out_val_angle;
uint8_t remote_value;

void get_remote_val();

uint16_t ADC_DMA_AVERAGE(int channel)
{
	uint32_t adc_sum;
	int i;
	
	adc_sum = 0;
	if(channel < NUMBER_ADC_CHANNEL )
	{
		for(i=0; i<NUMBER_ADC_CHANNEL_AVERAGE_PER_CHANNEL; i++)
			adc_sum += ADC_DMA_BUFF[channel+i*NUMBER_ADC_CHANNEL];
	}
	else
		return 1;
	
	return adc_sum/NUMBER_ADC_CHANNEL_AVERAGE_PER_CHANNEL;
}



void bsp_adc_init()
{
    HAL_ADC_Start_DMA(&hadc1, (uint32_t *)ADC_DMA_BUFF, NUMBER_ADC_CHANNEL * NUMBER_ADC_CHANNEL_AVERAGE_PER_CHANNEL);
}


#if 1 
uint16_t angle_sensor()
{
    return ADC_DMA_AVERAGE(0);
}
#endif 

#if 0 
typedef struct
{
	float angleMPa;
} Angle_MPa_t;

typedef struct
{
	float angleAdc;
} Angle_Adc_t;


Angle_MPa_t angleMpa[Angle_MAX_SIZE] = {
		40,
		63,
		90,
		115,
		140
};

Angle_Adc_t angleAdc[Angle_MAX_SIZE] = {
		300,
		1015,
		1735,
		2610,
		3500
};


typedef struct
{
	float remoteMPa;
} Speed_MPa_t;

typedef struct
{
	float remoteAdc;
} Speed_Adc_t;


Speed_MPa_t remoteMpa[Speed_MAX_SIZE] = {
		100,
		125,
		150,
		175,
		200
};

Speed_Adc_t remoteAdc[Speed_MAX_SIZE] = {
		0,
		1300,
		2000,
		2600,
		3450
};




float map_function(float x, float in_min, float in_max, float out_min, float out_max) 
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


float multiMap(float val, float* _in, float* _out, uint16_t size){
    // take care the value is within range
    // val = constrain(val, _in[0], _in[size-1]);
    if (val <= _in[0]) return _out[0];
    if (val >= _in[size-1]) return _out[size-1];

    // search right interval
    uint8_t pos = 1; // _in[0] allready tested
    while(val > _in[pos]) pos++;

    // this will handle all exact “points” in the _in array
    if (val == _in[pos]) return _out[pos];

    // interpolate in the right segment for the rest
    return map_function(val, _in[pos-1], _in[pos], _out[pos-1], _out[pos]);
}


uint16_t test1[7];


void get_angle_val()
{
	#if 0 
	out_val_angle = multiMap(ADC_DMA_AVERAGE(2), &angleAdc, &angleMpa, Angle_MAX_SIZE);
	angle_value = (uint8_t)out_val_angle;
	#if 0 
	cliPrintf("adc value = %d \r\n",ADC_DMA_AVERAGE(2));
	cliPrintf("anlge_value = %d \r\n",angle_value);
	#endif
	#endif
	//V_Battery = (60.5 * ADC_DMA_AVERAGE(0))/4095; 

}
void get_remote_val()
{
    
    #if 0
	V_Battery = ((60.5 * ADC_DMA_AVERAGE(0))/4095)-1; 
    outValue = multiMap(ADC_DMA_AVERAGE(1), &remoteAdc, &remoteMpa, Speed_MAX_SIZE);
	remote_value = (uint8_t)outValue ;
	//DRV_DAC_SET = remote_value;

	#if 0
	cliPrintf("adc value = %d \r\n",ADC_DMA_AVERAGE(1));
	cliPrintf("motor speed = %d \r\n",remote_value);
	#endif 

	if(remote_value <= 120)
		DRV_Speed = 1;
	else if(remote_value <= 140)
		DRV_Speed = 2;
	else if(remote_value <= 160)
		DRV_Speed = 3;
	else if(remote_value <= 180)
		DRV_Speed = 4;
	else
		DRV_Speed = 5;

    #endif 

}

#endif 