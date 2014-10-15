#include "external_module_function.h"
#include "my_time.h"

static int f_i2c_error=0;						//エラー時のフラグ



void I2c_lcd_cmd_send(char c){
	I2C_GenerateSTART(I2C_LCD_USE_I2C,ENABLE);
	 I2c_chack_wait(I2C_EVENT_MASTER_MODE_SELECT);
	I2C_Send7bitAddress(I2C_LCD_USE_I2C,0xa0,I2C_Direction_Transmitter);
	 I2c_chack_wait(I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED);
	I2C_SendData(I2C_LCD_USE_I2C,0x00);
	 I2c_chack_wait(I2C_EVENT_MASTER_BYTE_TRANSMITTED);
	I2C_SendData(I2C_LCD_USE_I2C,c);
	 I2c_chack_wait(I2C_EVENT_MASTER_BYTE_TRANSMITTED);
	I2C_GenerateSTOP(I2C_LCD_USE_I2C,ENABLE);
}
void I2c_lcd_init(void){
	if(f_i2c_error > 2){
		Delay_ms(200);
		I2c_lcd_cmd_send(0x01);
		Delay_ms(5);
		I2c_lcd_cmd_send(0x38);
		Delay_ms(5);
		I2c_lcd_cmd_send(0x0c);
		Delay_ms(5);
		I2c_lcd_cmd_send(0x06);
		Delay_ms(5);
	}
}
void I2c_lcd_clr(void){
	if(f_i2c_error > 2){
		I2c_lcd_cmd_send(0x01);
		Delay_ms(2);
	}
}
void I2c_lcd_locate(uint8_t x,uint8_t y){
	if(f_i2c_error > 2){
		I2c_lcd_cmd_send(0x80 | y*0x40 | x );
	}
}
void I2c_lcd_put_c(char c){
	if(f_i2c_error > 2){
		I2C_GenerateSTART(I2C_LCD_USE_I2C,ENABLE);
		 I2c_chack_wait(I2C_EVENT_MASTER_MODE_SELECT);
		I2C_Send7bitAddress(I2C_LCD_USE_I2C,0xa0,I2C_Direction_Transmitter);
		 I2c_chack_wait(I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED);
		I2C_SendData(I2C_LCD_USE_I2C,0x80);
		 I2c_chack_wait(I2C_EVENT_MASTER_BYTE_TRANSMITTED);
		I2C_SendData(I2C_LCD_USE_I2C,c);
		 I2c_chack_wait(I2C_EVENT_MASTER_BYTE_TRANSMITTED);
		I2C_GenerateSTOP(I2C_LCD_USE_I2C,ENABLE);
	}
}
void I2c_chack_wait(int flag){
	Write_time(TIMER_DELAY,ERROR_CONFIRMATION_TIME);
	while(!I2C_CheckEvent(I2C_LCD_USE_I2C,flag)){
		if(Chack_timer(TIMER_DELAY)){
			f_i2c_error+=1;
			break;
		}
	}
}
