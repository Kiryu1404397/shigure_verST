#ifndef  _main_header_
#define _main_header_

//--------------------------------------------------
//関数プロトタイプ宣言
void SysTick_Handler(void);
void Init_system(void);
void init_led_pwm(void);
void USART2_Put_c(char c);
void USART2_IRQHandler(void);
void TIM3_IRQHandler(void);

//-------------------------------------------------------------------
//	別名定義
#define USER_SW GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)
#define INTERRUPT_SYSTIC_TIME		0.001
#define INTERRUPT_MAIN_TIME			0.005
#define PC_USART	USART2_Put_c
#define PC			Usb_put_char
#define I2c_lcd		I2c_lcd_put_c







#endif