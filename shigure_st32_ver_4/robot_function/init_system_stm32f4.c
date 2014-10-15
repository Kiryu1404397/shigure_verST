#include "select_port_on_module.h"

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
#include "stm32f4xx_tim.h"
#include "stm32f4xx_usart.h"

//----------------------------------------------------------
//割り込み関数の許可TIM専用
void NVIC_config_TIM(TIM_TypeDef *tim){
	NVIC_InitTypeDef	NVIC_InitStructure;

	switch(tim){
		case TIM1:	//NVIC_Configuration(TIM1_IRQn);
		break;
		case TIM2:	NVIC_Configuration(TIM2_IRQn,0,0);
		break;
		case TIM3:	NVIC_Configuration(TIM3_IRQn,0,0);
		break;
		case TIM4:	NVIC_Configuration(TIM4_IRQn,0,1);
        break;
		case TIM5:	NVIC_Configuration(TIM5_IRQn,0,2);
        break;
		case TIM8:	NVIC_Configuration(TIM8_UP_TIM13_IRQn,1,0);
        break;
		case TIM9:	//NVIC_Configuration(TIM9_IRQn);
        break;
		case TIM10:	//NVIC_Configuration(TIM10_IRQn);
        break;
		case TIM11:	//NVIC_Configuration(TIM11_IRQn);
        break;
	}
}
//----------------------------------------------------------
//割り込み関数の許可USART専用
void NVIC_config_USART(USART_TypeDef *usart){
	if(usart == USART1){
		NVIC_Configuration(USART1_IRQn);
	}else if(usart == USART2){
		NVIC_Configuration(USART2_IRQn);
	}else if(usart == USART3){
		NVIC_Configuration(USART3_IRQn);
	}else if(usart == UART4){
		NVIC_Configuration(UART4_IRQn);
	}else if(usart == UART5){
		NVIC_Configuration(UART5_IRQn);
	}else if(usart == USART6){
		NVIC_Configuration(USART6_IRQn);
	}
}

//----------------------------------------------------------
//TIMのチャンネル設定(port)
GPIO_TypeDef* Tim_select_port(TIM_TypeDef *tim,uint8_t ch){
	GPIO_TypeDef *port;
	if(tim == TIM1){
		if(ch == TIM_CH1)	port = TIM1_CH1_PORT;
		if(ch == TIM_CH2)	port = TIM1_CH2_PORT;
		if(ch == TIM_CH3)	port = TIM1_CH3_PORT;
		if(ch == TIM_CH4)	port = TIM1_CH4_PORT;
	}else if(tim == TIM2){
		if(ch == TIM_CH1)	port = TIM2_CH1_PORT;
		if(ch == TIM_CH2)	port = TIM2_CH2_PORT;
		if(ch == TIM_CH3)	port = TIM2_CH3_PORT;
		if(ch == TIM_CH4)	port = TIM2_CH4_PORT;
	}else if(tim == TIM3){
		if(ch == TIM_CH1)	port = TIM3_CH1_PORT;
		if(ch == TIM_CH2)	port = TIM3_CH2_PORT;
		if(ch == TIM_CH3)	port = TIM3_CH3_PORT;
		if(ch == TIM_CH4)	port = TIM3_CH4_PORT;
	}else if(tim == TIM4){
		if(ch == TIM_CH1)	port = TIM4_CH1_PORT;
		if(ch == TIM_CH2)	port = TIM4_CH2_PORT;
		if(ch == TIM_CH3)	port = TIM4_CH3_PORT;
		if(ch == TIM_CH4)	port = TIM4_CH4_PORT;
	}else if(tim == TIM5){
		if(ch == TIM_CH1)	port = TIM5_CH1_PORT;
		if(ch == TIM_CH2)	port = TIM5_CH2_PORT;
		if(ch == TIM_CH3)	port = TIM5_CH3_PORT;
		if(ch == TIM_CH4)	port = TIM5_CH4_PORT;
	}else if(tim == TIM8){
		if(ch == TIM_CH1)	port = TIM8_CH1_PORT;
		if(ch == TIM_CH2)	port = TIM8_CH2_PORT;
		if(ch == TIM_CH3)	port = TIM8_CH3_PORT;
		if(ch == TIM_CH4)	port = TIM8_CH4_PORT;
	}else if(tim == TIM9){
		if(ch == TIM_CH1)	port = TIM9_CH1_PORT;
		if(ch == TIM_CH2)	port = TIM9_CH2_PORT;
	}else if(tim == TIM10){
		if(ch == TIM_CH1)	port = TIM10_CH1_PORT;
	}else if(tim == TIM11){
		if(ch == TIM_CH1)	port = TIM11_CH1_PORT;
	}

	return port;
}

//----------------------------------------------------------
//TIMのチャンネル設定(pin)
uint8_t Tim_select_pin(TIM_TypeDef *tim,uint8_t ch){
	uint16_t	pin;
	if(tim == TIM1){
		if(ch == TIM_CH1)	pin = TIM1_CH1_PIN;
		if(ch == TIM_CH2)	pin = TIM1_CH2_PIN;
		if(ch == TIM_CH3)	pin = TIM1_CH3_PIN;
		if(ch == TIM_CH4)	pin = TIM1_CH4_PIN;
	}else if(tim == TIM2){
		if(ch == TIM_CH1)	pin = TIM2_CH1_PIN;
		if(ch == TIM_CH2)	pin = TIM2_CH2_PIN;
		if(ch == TIM_CH3)	pin = TIM2_CH3_PIN;
		if(ch == TIM_CH4)	pin = TIM2_CH4_PIN;
	}else if(tim == TIM3){
		if(ch == TIM_CH1)	pin = TIM3_CH1_PIN;
		if(ch == TIM_CH2)	pin = TIM3_CH2_PIN;
		if(ch == TIM_CH3)	pin = TIM3_CH3_PIN;
		if(ch == TIM_CH4)	pin = TIM3_CH4_PIN;
	}else if(tim == TIM4){
		if(ch == TIM_CH1)	pin = TIM4_CH1_PIN;
		if(ch == TIM_CH2)	pin = TIM4_CH2_PIN;
		if(ch == TIM_CH3)	pin = TIM4_CH3_PIN;
		if(ch == TIM_CH4)	pin = TIM4_CH4_PIN;
	}else if(tim == TIM5){
		if(ch == TIM_CH1)	pin = TIM5_CH1_PIN;
		if(ch == TIM_CH2)	pin = TIM5_CH2_PIN;
		if(ch == TIM_CH3)	pin = TIM5_CH3_PIN;
		if(ch == TIM_CH4)	pin = TIM5_CH4_PIN;
	}else if(tim == TIM8){
		if(ch == TIM_CH1)	pin = TIM8_CH1_PIN;
		if(ch == TIM_CH2)	pin = TIM8_CH2_PIN;
		if(ch == TIM_CH3)	pin = TIM8_CH3_PIN;
		if(ch == TIM_CH4)	pin = TIM8_CH4_PIN;
	}else if(tim == TIM9){
		if(ch == TIM_CH1)	pin = TIM9_CH1_PIN;
		if(ch == TIM_CH2)	pin = TIM9_CH2_PIN;
	}else if(tim == TIM10){
		if(ch == TIM_CH1)	pin = TIM10_CH1_PIN;
	}else if(tim == TIM11){
		if(ch == TIM_CH1)	pin = TIM11_CH1_PIN;
	}

	return pin;
}

//----------------------------------------------------------
//	I2Cnの設定
void Init_i2c(I2C_TypeDef *use_i2c){
	I2C_InitTypeDef	I2C_InitStructure;

	if(use_i2c == I2C1){
		Init_af_port(I2C1_PORT,I2C1_SCL_PIN,GPIO_AF_I2C1,PORT_OD|PORT_PULL_UP);
		Init_af_port(I2C1_PORT,I2C1_SDA_PIN,GPIO_AF_I2C1,PORT_OD|PORT_PULL_UP);

	}else if(use_i2c == I2C2){
		Init_af_port(I2C2_PORT,I2C2_SCL_PIN,GPIO_AF_I2C2,PORT_OD|PORT_PULL_UP);
		Init_af_port(I2C2_PORT,I2C2_SDA_PIN,GPIO_AF_I2C2,PORT_OD|PORT_PULL_UP);

	}else if(use_i2c == I2C3){
		Init_af_port(I2C3_SCL_PORT,I2C3_SCL_PIN,GPIO_AF_I2C3,PORT_OD|PORT_PULL_UP);
		Init_af_port(I2C3_SDA_PORT,I2C3_SDA_PIN,GPIO_AF_I2C3,PORT_OD|PORT_PULL_UP);
	}

	I2C_StructInit(&I2C_InitStructure);
	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStructure.I2C_OwnAddress1 = 0x00;
	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitStructure.I2C_ClockSpeed = 50000;
	I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_Init(use_i2c,&I2C_InitStructure);

	I2C_Cmd(use_i2c,ENABLE);
}
//----------------------------------------------------------
//	USART/UARTの設定
void Init_usart(USART_TypeDef *usart){
	USART_InitTypeDef USART_InitStructure;
	RCC_PeriphClock_USART(usart);

	if(usart == USART1){
		Init_af_port(USART1_TX_PORT,USART1_TX_PIN,GPIO_AF_USART1,PORT_OD|PORT_PULL_NO);
		Init_af_port(USART1_RX_PORT,USART1_RX_PIN,GPIO_AF_USART1,PORT_OD|PORT_PULL_NO);
	}else if(usart == USART2){
		Init_af_port(USART2_TX_PORT,USART2_TX_PIN,GPIO_AF_USART2,PORT_OD|PORT_PULL_NO);
		Init_af_port(USART2_RX_PORT,USART2_RX_PIN,GPIO_AF_USART2,PORT_OD|PORT_PULL_NO);
	}else if(usart == USART3){
		Init_af_port(USART3_TX_PORT,USART3_TX_PIN,GPIO_AF_USART3,PORT_OD|PORT_PULL_NO);
		Init_af_port(USART3_RX_PORT,USART3_RX_PIN,GPIO_AF_USART3,PORT_OD|PORT_PULL_NO);
	}else if(usart == UART4){
		Init_af_port(UART4_TX_PORT,UART4_TX_PIN,GPIO_AF_UART4,PORT_OD|PORT_PULL_NO);
		Init_af_port(UART4_RX_PORT,UART4_RX_PIN,GPIO_AF_UART4,PORT_OD|PORT_PULL_NO);
	}else if(usart == UART5){
		Init_af_port(UART5_TX_PORT,UART5_TX_PIN,GPIO_AF_UART5,PORT_OD|PORT_PULL_NO);
		Init_af_port(UART5_RX_PORT,UART5_RX_PIN,GPIO_AF_UART5,PORT_OD|PORT_PULL_NO);
	}else if(usart == USART6){
		Init_af_port(USART6_TX_PORT,USART6_TX_PIN,GPIO_AF_USART6,PORT_OD|PORT_PULL_NO);
		Init_af_port(USART6_RX_PORT,USART6_RX_PIN,GPIO_AF_USART6,PORT_OD|PORT_PULL_NO);
	}

	USART_InitStructure.USART_BaudRate = 38400;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_Init(usart, &USART_InitStructure);

	NVIC_config_USART(usart);

	USART_ITConfig(usart,USART_IT_RXNE,ENABLE);
	USART_Cmd(usart, ENABLE);

}

//----------------------------------------------------------
//エンコーダーの設定
void Init_encoder(TIM_TypeDef *tim){
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;			//TIMを設定するための構造体

	RCC_PeriphClock_TIM(tim);

	Init_af_port(Tim_select_port(tim,TIM_CH1),Tim_select_pin(tim,TIM_CH1),Tim_select_af(tim),PORT_PP|PORT_PULL_UP);
	Init_af_port(Tim_select_port(tim,TIM_CH2),Tim_select_pin(tim,TIM_CH2),Tim_select_af(tim),PORT_PP|PORT_PULL_UP);

	TIM_PrescalerConfig(tim,0,TIM_PSCReloadMode_Update);

	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Period = 0xffff;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(tim,&TIM_TimeBaseStructure);

	TIM_EncoderInterfaceConfig(tim,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);

	TIM_Cmd(tim,ENABLE);

	NVIC_config_TIM(tim);
	TIM_ITConfig(tim,TIM_IT_Update,ENABLE);

}

//-------------------------------------------------------------
//SPIの初期化
void Init_spi(void){
	SPI_InitTypeDef SPI_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,ENABLE);

	Init_af_port(GPIOA,GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7,GPIO_AF_SPI1,PORT_PP | PORT_PULL_NO);
	Init_io_port(OUTPUT,GPIOE,GPIO_Pin_3);

	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32;
	SPI_InitStructure.SPI_CPHA		= SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_CPOL		= SPI_CPOL_High;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_InitStructure.SPI_DataSize	= SPI_DataSize_8b;
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_RxOnly;
	SPI_InitStructure.SPI_FirstBit	= SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_Mode		= SPI_Mode_Master;
	SPI_InitStructure.SPI_NSS		= SPI_NSS_Soft;
	SPI_Init(SPI1,&SPI_InitStructure);

	SPI_Cmd(SPI1,ENABLE);
}
