#ifndef  _external_module_function_header_
#define _external_module_function_header_
#include "stm32f4xx.h"						//STM32F4xxのライブラリを使用する
#include "stm32f4xx_i2c.h"

//I2C_LCDで使用しているI2Cモジュール
#define I2C_LCD_USE_I2C I2C2				//使用するI2cモジュール
#define ERROR_CONFIRMATION_TIME	0.1			//エラー判断時間(s)

//----------------------------------------------------------
/*I2C_LCDの機能 */

void I2c_chack_wait(int flag);
void I2c_lcd_cmd_send(char c);
void I2c_lcd_cmd_send_st(char c);
void I2c_lcd_init(void);
void I2c_lcd_clr(void);
void I2c_lcd_locate(uint8_t x,uint8_t y);
void I2c_lcd_put_c(char c);


#endif
