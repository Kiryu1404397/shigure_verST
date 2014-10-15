#ifndef _select_port_on_module_header_
#define _select_port_on_module_header_

#define TIM_CH1			((uint8_t)0x01)
#define TIM_CH2			((uint8_t)0x02)
#define TIM_CH3			((uint8_t)0x04)
#define TIM_CH4			((uint8_t)0x08)


//----------------------------------------------------------
//	TIMのポート選択

//	TIM1
//#define TIM1_CH1N_PA7
#define TIM1_CH1_PA8
//#define TIM1_CH1N_PB13
//#define TIM1_CH1N_PE8
//#define TIM1_CH1_PE9
#define TIM1_CH2_PA9
//#define TIM1_CH2N_PB0
//#define TIM1_CH2N_PB14
//#define TIM1_CH2N_PE10
//#define TIM1_CH2_PE11
//#define TIM1_CH3_PA10
//#define TIM1_CH3N_PB1
//#define TIM1_CH3N_PB15
#define TIM1_CH3N_PE12
//#define TIM1_CH3_PE13
#define TIM1_CH4_PA11
//#define TIM1_CH4_PE14

//	TIM2
#define TIM2_CH1_PA0
//#define TIM2_CH1_PA5
//#define TIM2_CH1_PA15
#define TIM2_CH2_PA1
//#define TIM2_CH2_PB3
#define TIM2_CH3_PA2
//#define TIM2_CH3_PB10
#define TIM2_CH4_PA3
//#define TIM2_CH4_PB11

//	TIM3
//#define TIM3_CH1_PA6
#define TIM3_CH1_PB4
//#define TIM3_CH1_PC6
//#define TIM3_CH2_PA7
#define TIM3_CH2_PB5
//#define TIM3_CH2_PC7
#define TIM3_CH3_PB0
//#define TIM3_CH3_PC8
#define TIM3_CH4_PB1
//#define TIM3_CH4_PC9

//	TIM4
#define TIM4_CH1_PB6
//#define TIM4_CH1_PD12
#define TIM4_CH2_PB7
//#define TIM4_CH2_PD13
#define TIM4_CH3_PB8
//#define TIM4_CH3_PD14
#define TIM4_CH4_PB9
//#define TIM4_CH4_PD15

//	TIM5
#define TIM5_CH1_PA0
#define TIM5_CH2_PA1
#define TIM5_CH3_PA2
#define TIM5_CH4_PA3

//	TIM8
//#define TIM8_CH1_PA5
//#define TIM8_CH1_PA6
#define TIM8_CH1_PC6
//#define TIM8_CH2N_PB0
//#define TIM8_CH2N_PB14
#define TIM8_CH2_PC7
#define TIM8_CH3N_PB1
//#define TIM8_CH3N_PB15
//#define TIM8_CH3_PC8
#define TIM8_CH4_PC9

//	TIM9
#define TIM9_CH1_PA2
//#define TIM9_CH1_PE5
#define TIM9_CH2_PA3
//#define TIM9_CH2_PE6

//	TIM10
#define TIM10_CH1_PB8

//	TIM11
#define TIM11_CH1_PB9

//----------------------------------------------------------
//	I2C
#define I2C1_SCL_PB6
//#define I2C1_SCL_PB8
#define I2C1_SDA_PB7
//#define I2C1_SDA_PB9

#define I2C2_SCL_PB10
#define I2C2_SDA_PB11

#define I2C3_SCL_PA8
#define I2C3_SDA_PC9

//----------------------------------------------------------
//	USART/UART
#define USART1_TX_PA9
//#define USART1_TX_PB6
#define USART1_RX_PA10
//#define USART1_RX_PB7

#define USART2_TX_PA2
//#define USART2_TX_PD5
#define USART2_RX_PA3
//#define USART2_RX_PD6

#define USART3_TX_PB10
//#define USART3_TX_PC10
//#define USART3_TX_PD8
#define USART3_RX_PB11
//#define USART3_RX_PC11
//#define USART3_RX_PD9

#define UART4_TX_PA0
//#define UART4_TX_PC10
#define UART4_RX_PA1
//#define UART4_RX_PC11

#define UART5_TX_PC12
#define UART5_RX_PD2

#define USART6_TX_PC6
#define USART6_RX_PC7


#endif
