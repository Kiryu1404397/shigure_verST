/* *******************************************************************
 * 時雨プログラム ver_stm32f407
 * ******************************************************************/

//-------------------------------------------------------------------
//micro-usbのヘッダファイル
#include "usb_communication.h"
#include <math.h>
//-------------------------------------------------------------------
//STM32F407VGのモジュール
#include "stm32f4xx_conf.h"
#include "stm32f4xx.h"

#include "misc.h"
#include "stm32f4xx_adc.h"
#include "stm32f4xx_crc.h"
#include "stm32f4xx_dma.h"
#include "stm32f4xx_exti.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_i2c.h"
#include "stm32f4xx_pwr.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_spi.h"
#include "stm32f4xx_syscfg.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_usart.h"

#include "stm32_ub_lis302dl.h"
#include "stm32_ub_spi1.h"
//-------------------------------------------------------------------
//自作ライブラリ
#include "my_standard_io_ver_2.h"
#include "my_calculation_function.h"
#include "my_robot_config.h"
#include "my_time.h"
#include "external_module_function.h"
#include "init_system_stm32f4.h"
#include "robot_function.h"
#include "SRC_route.h"

#include "main.h"

void ADC3_DMA_Config(void);
#define ADC3_DR_ADDRESS     ((uint32_t)0x4001224C)	//ADC3の変換結果レジスタのアドレス
/* Private variables */
uint16_t ADC3ConvertedValue[2];	//変換結果がDMA転送される配列



void Init_encoder_1(TIM_TypeDef *tim);


void Init_motor_port(void);
void Motor_move(double l_pwm,double r_pwm);

#define MOTOR_LF	0x01
#define MOTOR_LB	0x02
#define MOTOR_RF	0x04
#define MOTOR_RB	0x08

#define MOTOR_PIN_ON	0
#define MOTOR_PIN_OFF	1

#define MOTOR_DUTY_BASE 1000


//-------------------------------------------------------------
//グローバル変数の宣言
static signed long
	g_encl_ou=0,
	g_enc5_ou=0,
	g_enc8_ou=0,
	g_encr_ou=0;



void SysTick_Handler(void){
	Interrput_timer(INTERRUPT_SYSTIC_TIME);
}

void USART2_Put_c(char c){
	while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
	USART_SendData(USART2,c);
}

void USART2_IRQHandler(void){
	char c=0;
	c = USART_ReceiveData(USART2);
	Put_c(PC_USART,c);
	GPIO_SetBits(GPIOD,GPIO_Pin_12);
}
void TIM3_IRQHandler(void){
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
	if(((TIM3->CR1) >> 4) != 0){
		g_encl_ou-=1;
	}else{
		g_encl_ou+=1;
	}
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
}
void TIM4_IRQHandler(void){
	if(TIM4->CR1 >> 4){
		g_encr_ou-=1;
	}else{
		g_encr_ou+=1;
	}
    TIM_ClearITPendingBit(TIM4,TIM_IT_Update);
}

void TIM5_IRQHandler(void){
	if(TIM5->CR1 >> 4){
		g_enc5_ou-=1;
	}else{
		g_enc5_ou+=1;
	}
	TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
}
void TIM8_UP_TIM13_IRQHandler(void){
	if(TIM8->CR1 >> 4){
		g_enc8_ou-=1;
	}else{
		g_enc8_ou+=1;
	}
	TIM_ClearITPendingBit(TIM8, TIM_IT_Update);
}
void Init_system(void){
	SystemInit();
	Init_io_port(OUTPUT,GPIOD,GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);	//USER_LED
//	Init_io_port(INPUT,GPIOA,GPIO_Pin_0);	//USER_SW
	Init_systick(INTERRUPT_SYSTIC_TIME);
	GPIO_SetBits(GPIOD,GPIO_Pin_14);

	Delay_ms(100);
	Init_usb();
//	Init_usart(USART2);

//	Init_encoder_1(TIM1);
//	Init_encoder(TIM1);
//	Init_encoder(TIM2);
	Init_encoder(TIM3);
//	Init_encoder(TIM4);
//	Init_encoder(TIM5);
//	Init_encoder(TIM8);
	Init_motor_port();

	TIM_SetCounter(TIM1,0);
	TIM_SetCounter(TIM3,0);
	TIM_SetCounter(TIM4,0);
	g_encl_ou=0;	g_encr_ou=0;

	UB_LIS302_Init(SCALE_8G);
	UB_LIS302_SetFilter(FILTER_OFF);

	ADC3_DMA_Config();

	//AD変換開始
	ADC_SoftwareStartConv(ADC3);

	GPIO_ResetBits(GPIOD,GPIO_Pin_14);

	GPIO_SetBits(GPIOD,GPIO_Pin_13);
	Delay_ms(300);
	GPIO_ResetBits(GPIOD,GPIO_Pin_13);

}

int main(void){
//	uint32_t ADvoltage[2];

	machine_t
		robo={0};

	chased_t
		victim={0};

	motor_t
		mt={0};

	signed long
		encl_ct=0,
		encr_ct=0;

	unsigned int
//		ad_data=0,
		init_flag=0,
		dosa_ct=0,
		mode_ct=0,
		takashima_flag=0,
		court_mode=0,
//		sw_data=0,
		print_change=0;

	Init_system();
	GPIO_SetBits(GPIOD,GPIO_Pin_15);
//	while(USER_SW == 0); Delay_ms(20);
//	while(USER_SW == 1);
	GPIO_ResetBits(GPIOD,GPIO_Pin_15);

//	g_t1s=0;

	//モード説明
//	Talk_mode(mode_ct);
//	Delay_ms(1000);

	TIM_SetCounter(TIM3,0);
	TIM_SetCounter(TIM4,0);
	TIM_SetCounter(TIM5,0);
	TIM_SetCounter(TIM8,0);
	g_encl_ou=0;	g_encr_ou=0;
	g_enc5_ou=0;	g_enc8_ou=0;


	Delay_ms(300);

	mode_ct = 1;
	court_mode = RED_COURT;

	victim.m_l = 170;
	init_flag = INIT_MODE; 

/*	while(1){
		ADvoltage[0] = ADC3ConvertedValue[0] *3300/0xFFF;
		ADvoltage[1] = ADC3ConvertedValue[1] *3300/0xFFF;
		F_print(PC,"PC1",(float)ADvoltage[0]*0.001);
		Put_enter(PC);
		Delay_ms(100);
	}*/
/*	while(1){
		if(Main_roop_flag(INTERRUPT_MAIN_TIME)){
			I_print(PC,"tim1",TIM_GetCounter(TIM1));
			Put_enter(PC);
		}
	}*/
	while (1){
		if(Main_roop_flag(INTERRUPT_MAIN_TIME)){
			encl_ct = TIM_GetCounter(TIM3) + (g_encl_ou*0x10000);
			encl_ct *= (-1);
			encr_ct = TIM_GetCounter(TIM4) + (g_encr_ou*0x10000);

			LIS302_RAW.x_achse = 0;
			LIS302_RAW.y_achse = 0;
			LIS302_RAW.z_achse = 0;
			UB_LIS302_Read();

/*			if(abs(encl_ou_old - g_encl_ou) > 1){
				g_encl_ou = encl_ou_old;
			}
			encl_ou_old = g_encl_ou;*/

			My_position(&robo,encl_ct,encr_ct);
			Victim_position(robo,&victim);

			Clear_motor_t(&mt);
			if(victim.f_arrest == 0){
				dosa_ct = Course_run(robo,&victim,mode_ct,court_mode);
				Point_move(robo,&mt,victim.x,victim.y,0.3,takashima_flag);
				init_flag=INIT_MODE;
			}
			else{
				Machine_roll(robo,&mt,-45,DEG_MODE,&init_flag);
			}

			if(mode_ct == 6 && dosa_ct >= 1)		takashima_flag = 1;
			else if(mode_ct == 2 && dosa_ct >= 1)	takashima_flag = 1;
			else if(mode_ct == 0 && dosa_ct >= 1)	takashima_flag = 1;
			else if(mode_ct == 3 && dosa_ct >= 1)	takashima_flag = 1;
			else									takashima_flag = 0;

			if(victim.f_arrest == 0){
				if(takashima_flag == 1){
					mt.l_s_pwm *= (-1);		mt.r_s_pwm *= (-1);
				}
				Stop_back(robo,&mt,100,takashima_flag);
			}
			Motor_move(mt.l_s_pwm+mt.l_r_pwm,mt.r_s_pwm+mt.r_r_pwm);
//			Motor_move(mt.l_r_pwm,mt.r_r_pwm);


			//画面表示
			switch(print_change++){
/*				case 0:	if(victim.f_arrest == 0)	F_print(PC,"t_x",victim.x);
						else						Put_st(PC,"t_x,,");
				break;
				case 1:	if(victim.f_arrest == 0)	F_print(PC,"t_y",victim.y);
						else						Put_st(PC,"t_y,,");
				break;
				case 2:	F_print(PC,"m_x",robo.x);
				break;
				case 3:	F_print(PC,"m_y",robo.y);
				break;
				case 4: F_print(PC,"deg",robo.deg);
				break;
				case 5: I_print(PC,"ct",dosa_ct);
				break;
				case 6: I_print(PC,"tim",(TIM3->CR1));
				break;*/
				case 0: I_print(PC,"tim3",encl_ct);
				break;
				case 1: I_print(PC,"ad",ADC3ConvertedValue[1]);
				break;
//				case 2: I_print(PC,"tim5",enc5_ct);
//				break;
//				case 3: I_print(PC,"tim8",enc8_ct);
//				break;
/*				case 2: I_print(PC,"tim3_ou",g_encl_ou);
				break;
				case 3: I_print(PC,"tim4_ou",g_encr_ou);
				break;*/
/*				case 6: I_print(PC,"tim5_ou",g_enc5_ou);
				break;
				case 7: I_print(PC,"tim8_ou",g_enc8_ou);
				break;*/
/*				case 0:F_print(PC,"x_a",LIS302.x_achse);
				break;
				case 1:F_print(PC,"y_a",LIS302.y_achse);
				break;
				case 2:F_print(PC,"z_a",LIS302.z_achse);
				break;*/
				default:print_change=0;
						Put_enter(PC);
				break;
			}
 		}
	}
	return 0;
}

void Init_motor_port(void){
	Init_pwm(TIM1,TIM_CH1 | TIM_CH3);
	Init_io_port(OUTPUT,GPIOA,GPIO_Pin_7);					//l
	Init_io_port(OUTPUT,GPIOC,GPIO_Pin_5);					//l
	Init_io_port(OUTPUT,GPIOE,GPIO_Pin_12 | GPIO_Pin_14);	//R
}
void Motor_pin(int on,int off){
	if( (on&MOTOR_LF) != 0)	GPIO_SetBits(GPIOA,GPIO_Pin_7);
	if( (on&MOTOR_LB) != 0)	GPIO_SetBits(GPIOC,GPIO_Pin_5);
	if( (on&MOTOR_RF) != 0)	GPIO_SetBits(GPIOE,GPIO_Pin_12);
	if( (on&MOTOR_RB) != 0)	GPIO_SetBits(GPIOE,GPIO_Pin_14);
	if((off&MOTOR_LF) != 0)	GPIO_ResetBits(GPIOA,GPIO_Pin_7);
	if((off&MOTOR_LB) != 0)	GPIO_ResetBits(GPIOC,GPIO_Pin_5);
	if((off&MOTOR_RF) != 0)	GPIO_ResetBits(GPIOE,GPIO_Pin_12);
	if((off&MOTOR_RB) != 0)	GPIO_ResetBits(GPIOB,GPIO_Pin_14);
}
void Motor_move(double l_pwm,double r_pwm){
	const double min_out = 3.0;

	int
		r_pwm_out = 0,
		l_pwm_out = 0;


	//左モータ回転方向
	if(l_pwm >= min_out){
		Motor_pin(MOTOR_LF,MOTOR_LB);
	}else if(l_pwm <= ((-1)*min_out)){
		Motor_pin(MOTOR_LB,MOTOR_LF);
	}else{
		Motor_pin(0,MOTOR_LF|MOTOR_LB);
	}
	//右モータ回転方向
	if(r_pwm >= min_out){
		Motor_pin(MOTOR_RF,MOTOR_RB);
	}else if(r_pwm <= ((-1)*min_out)){
		Motor_pin(MOTOR_RB,MOTOR_RF);
	}else{
		Motor_pin(0,MOTOR_RF|MOTOR_RB);
	}

	//出力計算
	l_pwm_out = (int)((fabs(l_pwm)*(MOTOR_DUTY_BASE*0.01)) + 0.5);
	r_pwm_out = (int)((fabs(r_pwm)*(MOTOR_DUTY_BASE*0.01)) + 0.5);

	Tim_pulse_set(TIM1,TIM_CH3,Limit_ul(l_pwm_out,MOTOR_DUTY_BASE-1,1));
	Tim_pulse_set(TIM1,TIM_CH1,Limit_ul(r_pwm_out,MOTOR_DUTY_BASE-1,1));
}
void ADC3_DMA_Config(void){
	ADC_InitTypeDef ADC_InitStructure;
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	DMA_InitTypeDef DMA_InitStructure;

	//必要なペリフェラルにクロック供給開始
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3, ENABLE);

	Init_an_port(GPIOC,GPIO_Pin_1 | GPIO_Pin_2,PORT_PULL_NO);

	//DMAの設定
	//送り元のアドレスを固定し、送り先をADC3ConvertedValueにしてアドレスをインクリメント、送るデータ数を2つに
	DMA_InitStructure.DMA_Channel = DMA_Channel_2;								//指定したストリームに使用されるチャネルを指定
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&ADC3->DR;				//周辺回路側の起点となるアドレスの指定
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)&ADC3ConvertedValue;		//メモリ側の起点となるアドレスの指定
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;						//データの転送方向を指定
	DMA_InitStructure.DMA_BufferSize = 2;	//２チャンネルの変換結果を送るからデータ数は２（チャネルを増やしたらここを変える）
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;			//メモリアドレスをインクリメントするかどうかを指定
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;						//送り先アドレスをインクリメントするかどうかを指定
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;	//周辺回路が送信または受信するデータのビット長の指定
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;			//メモリが送信または受信するデータのビット長の指定
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;								//通常モード、サーキュラモードの選択
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;							//設定したDMAチャネルの転送優先度を指定
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;						//FIFOの選択
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;			//FIFOのしきい値レベルを指定
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;					//メモリ転送のバースト転送の設定を指定
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;			//周辺転送のバースト転送の設定を指定
	DMA_Init(DMA2_Stream0, &DMA_InitStructure);
	DMA_Cmd(DMA2_Stream0, ENABLE);

	//ADC3の基本設定
	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;						//ADCのモード選択
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;					//ADCのプリスケーラの選択
	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;		//ADCのDMAアクセスの設定
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;	//AD変換時の１つ１つの間隔の指定
	ADC_CommonInit(&ADC_CommonInitStructure);

	//ADC3の変換モード設定。入力2本をスキャン変換モードで逐次変換
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;						//ADC分解能のデュアルモードを設定
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;								//変換はスキャン（マルチチャンネル）またはシングル（1チャネル）モードの指定
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;							//変換は連続またはシングルモードで実行するかどうかを指定
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;	//外部トリガエッジを選択して、定期的なグループのトリガの指定
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;						//データ右詰め
	ADC_InitStructure.ADC_NbrOfConversion = 2;									//正規のチャネルグループのシーケンサーを使用して実行されるADC変換の数を指定
	ADC_Init(ADC3, &ADC_InitStructure);

	//ADC3のアナログ入力を定義する
	//ADC_Channel_11がPA1,ADC_Channel_12がPA2。マニュアル(UM1472)のピン配表を見るとわかる
	//"ADC123_IN11"という表記は、ADC1,ADC2,ADC3で使える入力でchannel_11に割り当てられる、ということ
	//使うチャネルを増やすには、ここに追記する。チャネル指定の次のパラメータは変換シーケンスの順序
	ADC_RegularChannelConfig(ADC3, ADC_Channel_11, 1, ADC_SampleTime_3Cycles);
	ADC_RegularChannelConfig(ADC3, ADC_Channel_12, 2, ADC_SampleTime_3Cycles);

	ADC_DMARequestAfterLastTransferCmd(ADC3, ENABLE);	//変換結果がDMA転送されるごとに、ADCは次の変換を開始するように設定
	ADC_DMACmd(ADC3, ENABLE);							//DMAをADCで使用する際の使用許可
	ADC_Cmd(ADC3, ENABLE);								//ADCの使用許可
}
void Init_encoder_1(TIM_TypeDef *tim){
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;			//TIMを設定するための構造体

	GPIO_InitTypeDef GPIO_InitStructure;					//GPIO初期化のための構造体
//	uint8_t pin;


	RCC_PeriphClock_GPIO(GPIOE);
	GPIO_StructInit(&GPIO_InitStructure);					//初期化用構造体にパラメータをセットしていくため、いったん初期値に戻す
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		//出力ポートのタイプをプッシュプルに指定する
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_10;						//設定するピンを指定する（スイッチのピン・アクティブハイ）
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;		//指定したピンを出力に指定する
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;		//GPIOのスピードを100MHz（最高速）にセットする
	GPIO_Init(GPIOE, &GPIO_InitStructure);					//PORT設定入力

	GPIO_PinAFConfig(GPIOE,Pin_select_source(GPIO_Pin_8),GPIO_AF_TIM1);
	GPIO_PinAFConfig(GPIOE,Pin_select_source(GPIO_Pin_10),GPIO_AF_TIM1);


	RCC_PeriphClock_TIM(TIM1);

	TIM_PrescalerConfig(TIM1,0,TIM_PSCReloadMode_Update);

	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Period = 0xffff;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseStructure);

	TIM_EncoderInterfaceConfig(TIM1,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);

	TIM_Cmd(TIM1,ENABLE);

	NVIC_config_TIM(TIM1);
}
