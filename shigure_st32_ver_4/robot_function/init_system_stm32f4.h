#ifndef _init_system_header_
#define _init_system_header_
#include "stm32f4xx.h"			//STM32F4xxのライブラリを使用する

#include "select_port_on_module.h"


//別名定義
#define OUTPUT	0
#define INPUT	1

#define PORT_PP			0x01
#define PORT_OD			0x02
#define PORT_PULL_UP	0x10
#define PORT_PULL_DOWN	0x20
#define PORT_PULL_NO	0x30


//------------------------------------------------------------------------------
//I2Cのポート設定
#ifdef I2C1_SCL_PB6
#define I2C1_SCL_PIN	GPIO_Pin_6
#endif

#ifdef I2C1_SDA_PB7
#define I2C1_SDA_PIN	GPIO_Pin_7
#endif

#ifdef I2C1_SCL_PB8
#define I2C1_SCL_PIN	GPIO_Pin_8
#endif

#ifdef	I2C1_SDA_PB9
#define I2C1_SDA_PIN	GPIO_Pin_9
#endif

#define I2C1_PORT	GPIOB

#define I2C2_SCL_PIN	GPIO_Pin_10
#define I2C2_SDA_PIN	GPIO_Pin_11
#define I2C2_PORT	GPIOB

#define I2C3_SCL_PIN	GPIO_Pin_8
#define I2C3_SDA_PIN	GPIO_Pin_9
#define I2C3_SCL_PORT	GPIOA
#define I2C3_SDA_PORT	GPIOC

//------------------------------------------------------------------------------
//TIMの設定

//TIM1,2,3の設定

#ifdef TIM1_CH1N_PA7
#define	TIM1_CH1_PIN	GPIO_Pin_7
#define TIM1_CH1_PORT	GPIOA
#endif
#ifdef TIM1_CH1_PA8
#define	TIM1_CH1_PIN	GPIO_Pin_8
#define TIM1_CH1_PORT	GPIOA
#endif
#ifdef TIM1_CH1N_PB13
#define	TIM1_CH1_PIN	GPIO_Pin_13
#define TIM1_CH1_PORT	GPIOB
#endif
#ifdef TIM1_CH1N_PE8
#define	TIM1_CH1_PIN	GPIO_Pin_8
#define TIM1_CH1_PORT	GPIOE
#endif
#ifdef TIM1_CH1_PE9
#define	TIM1_CH1_PIN	GPIO_Pin_9
#define TIM1_CH1_PORT	GPIOE
#endif

#ifdef TIM1_CH2_PA9
#define	TIM1_CH2_PIN	GPIO_Pin_9
#define TIM1_CH2_PORT	GPIOA
#endif
#ifdef TIM1_CH2N_PB0
#define	TIM1_CH2_PIN	GPIO_Pin_0
#define TIM1_CH2_PORT	GPIOB
#endif
#ifdef TIM1_CH2N_PB14
#define	TIM1_CH2_PIN	GPIO_Pin_14
#define TIM1_CH2_PORT	GPIOB
#endif
#ifdef TIM1_CH2N_PE10
#define	TIM1_CH2_PIN	GPIO_Pin_10
#define TIM1_CH2_PORT	GPIOE
#endif
#ifdef TIM1_CH2_PE11
#define	TIM1_CH2_PIN	GPIO_Pin_11
#define TIM1_CH2_PORT	GPIOE
#endif

#ifdef TIM1_CH3_PA10
#define	TIM1_CH3_PIN	GPIO_Pin_10
#define TIM1_CH3_PORT	GPIOA
#endif
#ifdef TIM1_CH3N_PB1
#define	TIM1_CH3_PIN	GPIO_Pin_1
#define TIM1_CH3 _PORT	GPIOB
#endif
#ifdef TIM1_CH3N_PB15
#define	TIM1_CH3_PIN	GPIO_Pin_15
#define TIM1_CH3_PORT	GPIOB
#endif
#ifdef TIM1_CH3N_PE12
#define	TIM1_CH3_PIN	GPIO_Pin_12
#define TIM1_CH3_PORT	GPIOE
#endif
#ifdef TIM1_CH3_PE13
#define	TIM1_CH3_PIN	GPIO_Pin_13
#define TIM1_CH3_PORT	GPIOE
#endif

#ifdef TIM1_CH4_PA11
#define	TIM1_CH4_PIN	GPIO_Pin_11
#define TIM1_CH4_PORT	GPIOA
#endif
#ifdef TIM1_CH4_PE14
#define	TIM1_CH4_PIN	GPIO_Pin_14
#define TIM1_CH4_PORT	GPIOE
#endif

#ifdef TIM2_CH1_PA0
#define	TIM2_CH1_PIN	GPIO_Pin_0
#endif
#ifdef TIM2_CH1_PA5
#define	TIM2_CH1_PIN	GPIO_Pin_5
#endif
#ifdef TIM2_CH1_PA15
#define	TIM2_CH1_PIN	GPIO_Pin_15
#endif
#define TIM2_CH1_PORT	GPIOA

#ifdef TIM2_CH2_PA1
#define	TIM2_CH2_PIN	GPIO_Pin_1
#define TIM2_CH2_PORT	GPIOA
#endif
#ifdef TIM2_CH2_PB3
#define	TIM2_CH2_PIN	GPIO_Pin_3
#define TIM2_CH2_PORT	GPIOB
#endif

#ifdef TIM2_CH3_PA2
#define	TIM2_CH3_PIN	GPIO_Pin_2
#define TIM2_CH3_PORT	GPIOA
#endif
#ifdef TIM2_CH3_PB10
#define	TIM2_CH3_PIN	GPIO_Pin_10
#define TIM2_CH3_PORT	GPIOB
#endif

#ifdef TIM2_CH4_PA3
#define	TIM2_CH4_PIN	GPIO_Pin_3
#define TIM2_CH4_PORT	GPIOA
#endif
#ifdef TIM2_CH4_PB11
#define	TIM2_CH4_PIN	GPIO_Pin_11
#define TIM2_CH4_PORT	GPIOB
#endif

#ifdef TIM3_CH1_PA6
#define	TIM3_CH1_PIN	GPIO_Pin_6
#define TIM3_CH1_PORT	GPIOA
#endif
#ifdef TIM3_CH1_PB4
#define	TIM3_CH1_PIN	GPIO_Pin_4
#define TIM3_CH1_PORT	GPIOB
#endif
#ifdef TIM3_CH1_PC6
#define	TIM3_CH1_PIN	GPIO_Pin_6
#define TIM3_CH1_PORT	GPIOC
#endif

#ifdef TIM3_CH2_PA7
#define	TIM3_CH2_PIN	GPIO_Pin_7
#define TIM3_CH2_PORT	GPIOA
#endif
#ifdef TIM3_CH2_PB5
#define	TIM3_CH2_PIN	GPIO_Pin_5
#define TIM3_CH2_PORT	GPIOB
#endif
#ifdef TIM3_CH2_PC7
#define	TIM3_CH2_PIN	GPIO_Pin_7
#define TIM3_CH2_PORT	GPIOC
#endif

#ifdef TIM3_CH3_PB0
#define	TIM3_CH3_PIN	GPIO_Pin_0
#define TIM3_CH3_PORT	GPIOB
#endif
#ifdef TIM3_CH3_PC8
#define	TIM3_CH3_PIN	GPIO_Pin_8
#define TIM3_CH3_PORT	GPIOC
#endif

#ifdef TIM3_CH4_PB1
#define	TIM3_CH4_PIN	GPIO_Pin_1
#define TIM3_CH4_PORT	GPIOB
#endif
#ifdef TIM3_CH4_PC9
#define	TIM3_CH4_PIN	GPIO_Pin_9
#define TIM3_CH4_PORT	GPIOC
#endif


//TIM4,8,9の設定
#ifdef TIM4_CH1_PB6
#define	TIM4_CH1_PIN	GPIO_Pin_6
#define TIM4_CH1_PORT	GPIOB
#endif
#ifdef TIM4_CH1_PD12
#define	TIM4_CH1_PIN	GPIO_Pin_12
#define TIM4_CH1_PORT	GPIOD
#endif
#ifdef TIM4_CH2_PB7
#define	TIM4_CH2_PIN	GPIO_Pin_7
#define TIM4_CH2_PORT	GPIOB
#endif
#ifdef TIM4_CH2_PD13
#define	TIM4_CH2_PIN	GPIO_Pin_13
#define TIM4_CH2_PORT	GPIOD
#endif
#ifdef TIM4_CH3_PB8
#define	TIM4_CH3_PIN	GPIO_Pin_8
#define TIM4_CH3_PORT	GPIOB
#endif
#ifdef TIM4_CH3_PD14
#define	TIM4_CH3_PIN	GPIO_Pin_14
#define TIM4_CH3_PORT	GPIOD
#endif
#ifdef TIM4_CH4_PB9
#define	TIM4_CH4_PIN	GPIO_Pin_9
#define TIM4_CH4_PORT	GPIOB
#endif
#ifdef TIM4_CH4_PD15
#define	TIM4_CH4_PIN	GPIO_Pin_15
#define TIM4_CH4_PORT	GPIOD
#endif

#ifdef TIM8_CH1_PA5
#define	TIM8_CH1_PIN	GPIO_Pin_5
#define TIM8_CH1_PORT	GPIOA
#endif
#ifdef TIM8_CH1_PA6
#define	TIM8_CH1_PIN	GPIO_Pin_6
#define TIM8_CH1_PORT	GPIOA
#endif
#ifdef TIM8_CH1_PC6
#define	TIM8_CH1_PIN	GPIO_Pin_6
#define TIM8_CH1_PORT	GPIOC
#endif

#ifdef TIM8_CH2N_PB0
#define	TIM8_CH2_PIN	GPIO_Pin_0
#define TIM8_CH2_PORT	GPIOB
#endif
#ifdef TIM8_CH2N_PB14
#define	TIM8_CH2_PIN	GPIO_Pin_14
#define TIM8_CH2_PORT	GPIOB
#endif
#ifdef TIM8_CH2_PC7
#define	TIM8_CH2_PIN	GPIO_Pin_7
#define TIM8_CH2_PORT	GPIOC
#endif

#ifdef TIM8_CH3N_PB1
#define	TIM8_CH3_PIN	GPIO_Pin_1
#define TIM8_CH3_PORT	GPIOB
#endif
#ifdef TIM8_CH3N_PB15
#define	TIM8_CH3_PIN	GPIO_Pin_15
#define TIM8_CH3_PORT	GPIOB
#endif
#ifdef TIM8_CH3_PC8
#define	TIM8_CH3_PIN	GPIO_Pin_8
#define TIM8_CH3_PORT	GPIOC
#endif

#define	TIM8_CH4_PIN	GPIO_Pin_9
#define TIM8_CH4_PORT	GPIOC

#ifdef TIM9_CH1_PA2
#define	TIM9_CH1_PIN	GPIO_Pin_2
#define TIM9_CH1_PORT	GPIOA
#endif
#ifdef TIM9_CH1_PE5
#define	TIM9_CH1_PIN	GPIO_Pin_5
#define TIM9_CH1_PORT	GPIOE
#endif
#ifdef TIM9_CH2_PA3
#define	TIM9_CH2_PIN	GPIO_Pin_3
#define TIM9_CH2_PORT	GPIOA
#endif
#ifdef TIM9_CH2_PE6
#define	TIM9_CH2_PIN	GPIO_Pin_6
#define TIM9_CH2_PORT	GPIOE
#endif


//TIM5,10,11の設定
#define TIM5_CH1_PIN	GPIO_Pin_0
#define TIM5_CH1_PORT	GPIOA
#define TIM5_CH2_PIN	GPIO_Pin_1
#define TIM5_CH2_PORT	GPIOA
#define TIM5_CH3_PIN	GPIO_Pin_2
#define TIM5_CH3_PORT	GPIOA
#define TIM5_CH4_PIN	GPIO_Pin_3
#define TIM5_CH4_PORT	GPIOA

#define TIM10_CH1_PIN	GPIO_Pin_8
#define TIM10_CH1_PORT	GPIOB

#define TIM11_CH1_PIN	GPIO_Pin_9
#define TIM11_CH1_PORT	GPIOB

//------------------------------------------------------------------------------
//USART/UARTの設定

#ifdef USART1_TX_PA9
#define	USART1_TX_PIN	GPIO_Pin_9
#define USART1_TX_PORT	GPIOA
#endif
#ifdef USART1_TX_PB6
#define	USART1_TX_PIN	GPIO_Pin_6
#define USART1_TX_PORT	GPIOB
#endif
#ifdef USART1_RX_PA10
#define	USART1_RX_PIN	GPIO_Pin_10
#define USART1_RX_PORT	GPIOA
#endif
#ifdef USART1_RX_PB7
#define	USART1_RX_PIN	GPIO_Pin_7
#define USART1_RX_PORT	GPIOB
#endif

#ifdef USART2_TX_PA2
#define	USART2_TX_PIN	GPIO_Pin_2
#define USART2_TX_PORT	GPIOA
#endif
#ifdef USART2_TX_PD5
#define	USART2_TX_PIN	GPIO_Pin_5
#define USART2_TX_PORT	GPIOD
#endif
#ifdef USART2_RX_PA3
#define	USART2_RX_PIN	GPIO_Pin_3
#define USART2_RX_PORT	GPIOA
#endif
#ifdef USART2_RX_PD6
#define	USART2_RX_PIN	GPIO_Pin_6
#define USART2_RX_PORT	GPIOD
#endif

#ifdef USART3_TX_PB10
#define	USART3_TX_PIN	GPIO_Pin_10
#define USART3_TX_PORT	GPIOB
#endif
#ifdef USART3_TX_PC10
#define	USART3_TX_PIN	GPIO_Pin_10
#define USART3_TX_PORT	GPIOC
#endif
#ifdef USART3_TX_PD8
#define	USART3_TX_PIN	GPIO_Pin_8
#define USART3_TX_PORT	GPIOD
#endif
#ifdef USART3_RX_PB11
#define	USART3_RX_PIN	GPIO_Pin_11
#define USART3_RX_PORT	GPIOB
#endif
#ifdef USART3_RX_PC11
#define	USART3_RX_PIN	GPIO_Pin_11
#define USART3_RX_PORT	GPIOC
#endif
#ifdef USART3_RX_PD9
#define	USART3_RX_PIN	GPIO_Pin_9
#define USART3_RX_PORT	GPIOD
#endif

#ifdef UART4_TX_PA0
#define	UART4_TX_PIN	GPIO_Pin_0
#define UART4_TX_PORT	GPIOA
#endif
#ifdef UART4_TX_PC10
#define	UART4_TX_PIN	GPIO_Pin_10
#define UART4_TX_PORT	GPIOC
#endif
#ifdef UART4_RX_PA1
#define	UART4_RX_PIN	GPIO_Pin_1
#define UART4_RX_PORT	GPIOA
#endif
#ifdef UART4_RX_PC11
#define	UART4_RX_PIN	GPIO_Pin_11
#define UART4_RX_PORT	GPIOC
#endif

#define	UART5_TX_PIN		GPIO_Pin_12
#define UART5_TX_PORT	GPIOC
#define	UART5_RX_PIN		GPIO_Pin_2
#define UART5_RX_PORT	GPIOD

#define	USART6_TX_PIN	GPIO_Pin_6
#define USART6_TX_PORT	GPIOC
#define	USART6_RX_PIN	GPIO_Pin_7
#define USART6_RX_PORT	GPIOC

//------------------------------------------------------------------------------
//関数プロトタイプ宣言

//ポートのクロック供給
void RCC_PeriphClock_GPIO(GPIO_TypeDef *port);
//TIMのクロック供給
void RCC_PeriphClock_TIM(TIM_TypeDef *tim);
//USART/UARTのクロック供給
void RCC_PeriphClock_USART(USART_TypeDef *usart);
//割り込み関数の許可
void NVIC_Configuration(int irqn);
//割り込み関数の許可TIM専用
void NVIC_config_TIM(TIM_TypeDef *tim);
//割り込み関数の許可USART専用
void NVIC_config_USART(USART_TypeDef *usart);
//ポートをAFで使用する場合の設定
void Init_af_port(GPIO_TypeDef *port,uint16_t pin,uint8_t af,uint16_t mode);
//ポートをANで使用する場合の設定
void Init_an_port(GPIO_TypeDef *port,uint16_t pin,uint16_t mode);
//ポートのソース選択
uint8_t Pin_select_source(uint16_t pin);
//TIMのチャンネル設定(port)
GPIO_TypeDef* Tim_select_port(TIM_TypeDef *tim,uint8_t ch);
//TIMのチャンネル設定(pin)
uint8_t Tim_select_pin(TIM_TypeDef *tim,uint8_t ch);
//TIMのAF選択
uint8_t Tim_select_af(TIM_TypeDef *tim);


//systick割り込みの設定
void Init_systick(float time);
//I/Oの設定
void Init_io_port(uint16_t mode,GPIO_TypeDef *port,uint16_t pin);
//	I2Cnの設定
void Init_i2c(I2C_TypeDef *use_i2c);
//	USART/UARTの設定
void Init_usart(USART_TypeDef *usart);
//エンコーダーの設定
void Init_encoder(TIM_TypeDef *tim);
//TIM PWMモードの設定
void Init_pwm(TIM_TypeDef *tim,uint8_t ch);
//TIM PWMモード時のパルス幅変更
void Tim_pulse_set(TIM_TypeDef *tim,int ch,unsigned int pulse);

void Init_adc(ADC_TypeDef *adc);
void Init_dma_adc(ADC_TypeDef *adc,uint16_t *container,unsigned int data_num);
void Start_adc(ADC_TypeDef *adc);



#endif
