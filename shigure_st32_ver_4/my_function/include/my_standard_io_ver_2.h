#ifndef _my_standard_io_ver_2_header_
#define _my_standard_io_ver_2_header_

#include <math.h>

//--------------------------------------------------------------
//別名定義
#define END '\r'				//通信データの終端文字
//#define NULL 0					//NULL文字

#define READ_MODE 0
#define WRITE_MODE 1
//---------------------------------------------------------------
//画面表示用関数
double pow_for_my_stdio(double num,int p);

void Put_c(void (*put_c)(char c),char data);
void Put_i(void (*put_c)(char c),unsigned long data);
void Put_si(void (*put_c)(char c),signed long data);
void Put_f(void (*put_c)(char c),double data);
void Put_st(void (*put_c)(char c),char *word);
void Put_enter(void (*put_c)(char c));

void F_print(void (*put_c)(char c),char *moji,double kazu);
void I_print(void (*put_c)(char c),char *moji,int kazu);

//---------------------------------------------------------------
//シリアルの受信による変数変更
void Receive_order_c(char character);
float Value_wr_data(char character,float num,int mode);
void Write_value(char c,float num);
float Read_value(char c);

#endif
