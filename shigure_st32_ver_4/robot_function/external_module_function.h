#ifndef  _external_module_function_header_
#define _external_module_function_header_
#include "stm32f4xx.h"						//STM32F4xx�̃��C�u�������g�p����
#include "stm32f4xx_i2c.h"

//I2C_LCD�Ŏg�p���Ă���I2C���W���[��
#define I2C_LCD_USE_I2C I2C2				//�g�p����I2c���W���[��
#define ERROR_CONFIRMATION_TIME	0.1			//�G���[���f����(s)

//----------------------------------------------------------
/*I2C_LCD�̋@�\ */

void I2c_chack_wait(int flag);
void I2c_lcd_cmd_send(char c);
void I2c_lcd_cmd_send_st(char c);
void I2c_lcd_init(void);
void I2c_lcd_clr(void);
void I2c_lcd_locate(uint8_t x,uint8_t y);
void I2c_lcd_put_c(char c);


#endif
