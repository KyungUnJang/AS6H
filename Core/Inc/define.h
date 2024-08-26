
#ifndef __BSP_DEFINE_H
#define __BSP_DEFINE_H


#include "main.h"
#include "def.h"
#include "stm32f103xe.h"



#define TRUE 1
#define FALSE 0

#define C_NRML "\033[0m"
#define C_BLCK "\033[30m"
#define C_RED  "\033[31m"
#define C_GREN "\033[32m"
#define C_YLLW "\033[33m"
#define C_BLUE "\033[34m"
#define C_PRPL "\033[35m"
#define C_AQUA "\033[36m"
#define C_END  "\033[0m"


#define CAN_MCU		0
#define CAN_STR 	1
#define CAN_DRV 	2
#define CAN_CRABLE  3




/* PART A Define */
#if 0	
	23	PA0 	IN_ADC		Battery 48V +			CON-01,  	
	24	PA1 	IN_ADC		RFR Volume				CON-03, 					
	25	PA2 	IN_ADC		Current_Ready			CN19	
	26	PA3 	IN_ADC		????_Ready				CN21
	
	29	PA4 	OUT_DAC 	DRV_ACC 				CON-01,  	
	30	PA5 	OUT_DAC 	STR_ACC 				CON-01, 	
	31	PA6 	OUT_PORT	BL_BZ					CON-02,  
	32	PA7 			
	67	PA8 	IN_Ready	
	68	PA9 	UART 1		TX	Debug				CON-04,   
	69	PA10				RX						CON-04,  
	70	PA11	CAN 		RX						CON-04,  	
	71	PA12				TX						CON-04,  
	72	PA13	SYS_JTMS_SWDIO						J7(TMS) 
	76	PA14	SYS_JTCK_SWCLK(TCK) 				J7(TCK) 	
	77	PA15	SYS_JTDI
#endif	
#define A_in_ADC1_0				GPIO_PIN_0
#define A_in_ADC1_1				GPIO_PIN_1
#define A_in_ADC1_2				GPIO_PIN_2
#define A_in_ADC1_3				GPIO_PIN_3
#define GPIO_DAC1				GPIO_PIN_4
#define GPIO_DAC2				GPIO_PIN_5
#define A_BUZZER				GPIO_PIN_6

#define GPIO_UART1_Tx    		GPIO_PIN_9
#define GPIO_UART1_Rx    		GPIO_PIN_10
#define GPIO_CAN1_Rx    		GPIO_PIN_11
#define GPIO_CAN1_Tx    		GPIO_PIN_12


/* PART B Define */
#if 0
	35	PB0 	OUT_PORT	BL_G					CON-02,  
	36	PB1 	OUT_PORT	BL_B					CON-02,  
	37	PB2 	
	89	PB3 	SYS_JTDO_TRACESWO		
	90	PB4 	SYS_NJTRST		
	91	PB5 	OUT_PORT	EEP WP
	92	PB6 	OUT_PORT	I2C_SCL
	93	PB7 	OUT_PORT	I2C_SDA
	95	PB8 	OUT_PORT	LED_Y	
	96	PB9 	OUT_PORT	LED_W
	47	PB10	UART3		TX (RDY)				J6			
	48	PB11				RX						J6
	51	PB12	OUT_PORT	PUMP_ON 				CON-01,    
	52	PB13	OUT_PORT	PUMP_UP 				CON-01,   
	53	PB14	OUT_PORT	PUMP_OFF				CON-01,   
	54	PB15	OUT_PORT	PUMP_DN 				CON-01,  
#endif
#define B_BEACON_G				GPIO_PIN_0
#define B_BEACON_B				GPIO_PIN_1

#define GPIO_I2C_WP				GPIO_PIN_5	
#define GPIO_I2C_SCL			GPIO_PIN_6	
#define GPIO_I2C_SDA			GPIO_PIN_7
#define B_LED_Y					GPIO_PIN_8					
#define B_LED_W					GPIO_PIN_9					
#define GPIO_UART3_Tx    		GPIO_PIN_10
#define GPIO_UART3_Rx    		GPIO_PIN_11

#define B_PMPON					GPIO_PIN_12					
#define B_PMPUP					GPIO_PIN_13					
#define B_PMPOFF				GPIO_PIN_14					
#define B_PMPDN					GPIO_PIN_15		 			


/* PART C Define */
#if 0
	15	PC0 	IN_PORT 	STR_S_R (INT.)			
	16	PC1 	IN_PORT 	STR_S_L (INT.)		
	17	PC2 	IN_PORT 	CS_IN1	(INT.)			
	18	PC3 	IN_PORT 	CS_IN2	(INT.)			
	33	PC4 	IN_PORT 	STR_S_C 							
	34	PC5 	OUT_PORT	BL_R						
	63	PC6 	IN_PORT 	WLS_IN1(����)				
	64	PC7 	IN_PORT 	WLS_IN2(��ü)			
	65	PC8 	IN_Ready
	66	PC9 	IN_Ready		
	78	PC10	UART4		TX (RDY)						
	79	PC11				RX					
	80	PC12	IN_PORT 	RFR_F(forward)			
	7	PC13	IN_PORT 	RFR_AD(autodrive)		
	8	PC14	IN_PORT 	RFR_FANONUP 			
	9	PC15	IN_PORT 	RFR_FANOFF				
#endif
#define	C_STRright_LMT			GPIO_PIN_0			
#define	C_STRleft_LMT			GPIO_PIN_1
#define	C_CRASH_1				GPIO_PIN_2		
//#define	C_CRASH_2				GPIO_PIN_3
#define	C_STRcenter				GPIO_PIN_4
#define C_BEACON_R				GPIO_PIN_5
#define	C_WLS_IN1				GPIO_PIN_6		
#define	C_WLS_IN2				GPIO_PIN_7		


#define C_OPT_RDY    			GPIO_PIN_10
#define C_OPT_COMM    			GPIO_PIN_11
#define C_OPT_VISION   			GPIO_PIN_11
#define	IR_FORWARD				GPIO_PIN_12	
#define	IR_AUTODRIVE			GPIO_PIN_13
#define	IR_FANONUP				GPIO_PIN_14
#define	IR_FANOFF				GPIO_PIN_15

/* PORT D Define */
#if 0	
	81	PD0 	IN_PORT 	RFR_B(backword) 	CON-03,   4
	82	PD1 	IN_PORT 	RFR_L(left) 		CON-03,   5 
	83	PD2 	IN_PORT 	RFR_R(right)		CON-03,   6 
	84	PD3 	IN_PORT 	RFR_PUMP(on/off)	CON-03,   8
	85	PD4 	IN_PORT 	RFR_MAIN			CON-03,  12
	86	PD5 	UART2		TX(SMART)			CON-03,  21
	87	PD6 				RX					CON-03,  23
	88	PD7
	55	PD8 	IN_Ready(3.3v, 10k PU)
	56	PD9 	IN_Ready(3.3v, 10k PU)
	57	PD10	IN_Ready(3.3v, 10k PU)
	58	PD11	IN_Ready(3.3v, 10k PU)			
	59	PD12	IN_Ready(3.3v, 10k PU)
	60	PD13	IN_Ready(3.3v, 10k PU)	 
	61	PD14	OUT_PWM_Ready(TIM4_CH3) 		TP102
	62	PD15	OUT_PWM_FAN(TIM4_CH4)			CON-01,  19			
#endif	
#define	IR_BACKWARD		GPIO_PIN_0
#define	IR_LEFT			GPIO_PIN_1	
#define	IR_RIGHT		GPIO_PIN_2
#define	IR_PUMP			GPIO_PIN_3
#define IR_Main			GPIO_PIN_4
#define GIO_UART2_Tx    GPIO_PIN_5 
#define GIO_UART2_Rx    GPIO_PIN_6

#define	PWM_RDY			GPIO_PIN_14 
#define	PWM_FAN			GPIO_PIN_15 

/* PORT E Define */
#if 0
	97	PE0 	OUT_PORT	LED R
	98	PE1 	OUT_PORT	LED G
	1	PE2 	IN_PORT 	LK_E(emergency) 	
	2	PE3 	IN_PORT 	LK_F(forward)		
	3	PE4 	IN_PORT 	LK_B(backward)		
	4	PE5 	IN_PORT 	LK_L(left)			
	5	PE6 	IN_PORT 	LK_R(right) 		
	38	PE7 	
	39	PE8 	OUT_PORT	STR_BREAK(Ready)	
	40	PE9 	OUT_PORT	STR_C/CCW			CON-01,   9
	41	PE10	PUT_PORT	DRV_BREAK			CON-01,   5	
	42	PE11	OUT_PORT	DRV_C/CCW			CON-01,   3 
	43	PE12	OUT_PORT	SOL_V_1()		CON-01,  15
	44	PE13	OUT_PORT						CON-01,  18
	45	PE14	IN_PORT 	SPEED OPTION	CON-01,  16
	46	PE15	IN_PORT 	 OPTION 	CON-01,  14			
#endif
#define DBG_LED_R  			GPIO_PIN_0
#define DBG_LED_G  			GPIO_PIN_1
#define ST_KEY_TEMP 		GPIO_PIN_2
#define ST_KEY_FORWARD		GPIO_PIN_3
#define ST_KEY_BACKWORD		GPIO_PIN_4
#define ST_KEY_LEFT			GPIO_PIN_5
#define ST_KEY_RIGHT		GPIO_PIN_6

#define E_strM_BREAK		GPIO_PIN_8
#define E_strM_CWCCW		GPIO_PIN_9

#define E_drvM_BREAK		GPIO_PIN_10
#define E_drvM_CWCCW		GPIO_PIN_11
#define E_SOLv_1			GPIO_PIN_12		/* 	CON01-15 */
//#define E_SOLv_2			GPIO_PIN_13		/*  CON-01-18 --> Not Used */
#define E_OPT_Pumpspeed		GPIO_PIN_14		/* Pump �з�	  f_OPT_Pumpspeed	 CON01- 14 */
#define E_OPT_Autospeed		GPIO_PIN_15		/*  f_OPT_AutodrvSPD	 CON01- 16 */

//#define GPIO_USB_DISCONNECT_PIN    GPIO_PIN_8
 
#define GPIO_PORTSOURCE_KEY        GPIO_PortSourceGPIOC
#define GPIO_PORTSOURCE_CRASH      GPIO_PortSourceGPIOC
#define GPIO_PORTSOURCE_STR_R      GPIO_PortSourceGPIOD
#define GPIO_PORTSOURCE_STR_L      GPIO_PortSourceGPIOD

#define GPIO_PINSOURCE_KEY1        GPIO_PINSource0
#define GPIO_PINSOURCE_KEY2        GPIO_PINSource1
#define GPIO_PINSOURCE_KEY7        GPIO_PINSource7
#define GPIO_PINSOURCE_CRASH	   GPIO_PINSource8

#define GPIO_PINSOURCE_STR_R	   GPIO_PINSource8
#define GPIO_PINSOURCE_STR_L	   GPIO_PINSource9

#define GPIO_EXTI_Line_KEY1        EXTI_Line0
#define GPIO_EXTI_Line_KEY2        EXTI_Line1
#define GPIO_EXTI_Line_KEY7        EXTI_Line7
#define GPIO_EXTI_Line_CRASH       EXTI_Line8

#define GPIO_EXTI_Line_STR_R       EXTI_Line8
#define GPIO_EXTI_Line_STR_L       EXTI_Line9


/* u16_DebugFlag  DBG_Print [DBG-xxxx][ENT] */
#define fDBG_Every1S 	(1 << 0)		/* Every 1 Sec, �Ϲ� Status Debug [DBG-0001] */
#define fDBG_StatusCHG	(1 << 1)		/* Systus ����� Debug [DBG-0002] */
//
#define fDBG_Print		(1 << 7)		/* UART 1 Print */


/* uTimerFlag */
#define TIM_10ms			(1 << 1)
#define TIM_30ms			(1 << 2)
#define TIM_50ms			(1 << 3)
#define TIM_100ms			(1 << 4)
#define TIM_200ms			(1 << 5)
#define TIM_500ms			(1 << 6)
#define TIM_1Sec			(1 << 7)
//
#define TIM_1SecMaker		(1 << 8)



/* u2SysStatusF f_ENGrunEXTout */
#define f_LimitCenter		(1 << 0)	/* 1 =   */
#define f_LimitLeft			(1 << 1)	/* 1 =  Limit   */
#define f_LimitRight		(1 << 2)	/* 1 =  Limit   */
#define f_ALLWLEmpty		(1 << 3)	/* 1 =    */
#define f_LowBat			(1 << 4)	/* 1 = Battery V. Low 35V  */
#define f_Crash				(1 << 5)	/* 1 =  */
#define f_RFR_Emergency		(1 << 6)	/* 1 = RFR   */
#define f_AutoRun			(1 << 7)	/* 1 = Req. */
//
#define f_EnginRuning     	(1 << 8)	/* Engin Running */
#define f_PumpACT			(1 << 9)	/* PUMP */
#define f_FanACT     		(1 << 10)	/* FAN */
#define f_DMotorACT  		(1 << 11)	/* Motor   */
#define f_SMotorACT			(1 << 12)	/* Motor   */
#define f_Heartbeat			(1 << 13)	/* Can  */
#define f_RTKRdy			(1 << 14)	/* Ready .. */
#define f_TraceLine			(1 << 15)	/* 1 = RTK  */
//
#define f_DMForward 		(1 << 16)	/* Motor CWCCW */
#define f_DMBreak			(1 << 17)	/* Motor Break */
#define f_SMLeft       		(1 << 18)
#define f_WLEmpty1			(1 << 19)	
#define f_WLEmpty2			(1 << 20)	
#define f_WTEmptBuzReq		(1 << 21)
#define f_CenterAlignment	(1 << 23)	/* 1 = Init Center Alignment Req. */
//
#define f_CarFanSel			(1 << 24)	/* 1 = FAN On, 0 = FAN Off */
#define f_CarAutoSel		(1 << 25)	/* 1 = Auto On, 0 = Auto Off */

#define f_ADRVnoWaterStop	(1 << 26)	
#define f_ADRVnoCANData		(1 << 27)	
#define f_ENGrunEXTout		(1 << 28)	


/* uKeyStatusFlag  */
#define flk_Forward			(1 << 0)
#define flk_Backward		(1 << 1)
#define flk_Left			(1 << 2)
#define flk_Right			(1 << 3)

#define frk_Emergency		(1 << 4)
#define frk_Forward			(1 << 5)
#define frk_Backward		(1 << 6)
#define frk_Left			(1 << 7)
//
#define frk_Right			(1 << 8)
#define frk_AutoDrv			(1 << 9)
#define frk_Pump			(1 << 10)
#define frk_FanOnUp			(1 << 11)
#define frk_FanOff			(1 << 12)

#define fLK_Ok   			(1 << 16)
#define fLK_Repeat 			(1 << 17)
#define fRK_Ok				(1 << 18)
#define fRK_Repeat			(1 << 19)

#define smt_Forward			(1 << 25)
#define smt_Backward		(1 << 26)
#define smt_Left			(1 << 27)
#define smt_Right			(1 << 28)

#define DMOTOR_STOP		0
#define	DMOTOR_START	1		/*  Port Set */
#define	DMOTOR_BRKOFF	2		/* Drive M. Break Release */
#define	DMOTOR_ACCEL	3		/* Tarket Accel PWM  */
#define	DMOTOR_ACCELACT	4		/* PWM Set */
#define	DMOTOR_END		5

#define SMOTOR_STOP		0
#define	SMOTOR_START	1		/*Port Set */
#define	SMOTOR_BRKOFF	2		/* Drive M. Break Release */
#define	SMOTOR_ACCEL	3		/* Tarket Accel PWM  */
#define	SMOTOR_ACCELACT	4		/* PWM Set */
#define	SMOTOR_END		5



#define KEY_NONE		0
#define KEY_FORWARD		0x01
#define KEY_BACKWORD	0x02
#define KEY_LEFT		0x04
#define KEY_RIGHT		0x08
//
#define KEY_PUMP		0x10
#define KEY_AUTORUN		0x20
#define KEY_FANONUP		0x40
#define KEY_FANOFF		0x80

#define RFR_NONE		0
#define RFR_FORWARD		0x100		
#define RFR_ATDRV		0x02		
#define RFR_FANONUP		0x04		
#define RFR_FANOFF		0x08	
#define RFR_BACKWORD	0x200
#define RFR_LEFT		0x01
#define RFR_RIGHT		0x02
#define RFR_PUMP 		0x80
#define RFR_EMERGENCY	0x100



#define NONE 0x01
#define BACK 0x02
#define FRONT 0x04
#define CAN_FRONT_REQ 0x01
#define CAN_BACK_REQ 0x02
//




#endif 
