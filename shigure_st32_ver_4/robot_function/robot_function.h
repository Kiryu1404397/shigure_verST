#ifndef _robot_fanction_header_
#define _robot_fanction_header_

#include "my_robot_config.h"
#include <math.h>

//--------------------------------------------------------------------------------------------------
//別名定義
#define L_ENC 0
#define R_ENC 1

#define INIT_MODE 1
#define MOVE_MODE 0

//マシン情報
#define ENC_PULSE 100		//エンコーダパルス
#define ENC_WIDTH 226		//エンコーダ間の距離(mm)

#define L_TIRE_DIAMETER	22//21.96832933
#define R_TIRE_DIAMETER	22//22.03167067
/*#define L_TIRE_DIAMETER	21.96832933
#define R_TIRE_DIAMETER	22.03167067*/

#define ACC_ALL 0
#define ACC_NO 1
#define ACC_FRONT 2
#define ACC_BACK 3

#define MOVE_STRAIGHT	0
#define MOVE_ROLL		1
#define MOVE_CURVE		2

#define CRAB_RIGHT		0
#define CRAB_LEFT		1

//スイッチのポジション（チャタリング回避関数用）
#define SW0_p 0x01
#define SW1_p 0x02
#define SW2_p 0x04
#define SW3_p 0x08


//--------------------------------------------------------------------------------------------------
//構造体宣言
//モータ出力
typedef struct{
	double l_r_pwm;
	double l_s_pwm;
	double r_r_pwm;
	double r_s_pwm;
}motor_t;
//移動データ
typedef struct{
	int move_mode;
	double target_x;
	double target_y;
	double v_max;
	double start_acc;
	double end_acc;
	int acc_mode;
	double target_angle;
	int angle_mode;
}move_set_t;
//追われる点のデータ
typedef struct{
	double x;
	double y;
	double l;
	double angle;
	double m_l;
	unsigned int f_arrest;
}chased_t;




double Angle_fixing(double angle,double my_angle,float p_gain,float d_gain,float i_gain);
double Speed_fixing(double speed,double my_speed,float p_gain,float d_gain,float i_gain);
double Trapezoid_control(double my_x,double my_y,position_t start,position_t end,double v_max,double start_v_min,double s_acc,double e_acc);

//現在地取得
void My_position(machine_t *robot,signed long encl_cnt,signed long encr_cnt);

//目的地移動関数
int Machine_roll(machine_t robot,motor_t *mt,double target_rad,int angle_mode,unsigned int *);
int Machine_move(machine_t robot,motor_t *mt,double target_x,double target_y,double v_max,double s_acc,double e_acc,unsigned int *);
int Machine_curve(machine_t robot,motor_t *mt,double target_x,double target_y,double v_max,double s_acc,double e_acc,unsigned int *);
int Machine_crab(machine_t robot,motor_t *mt,double target_dis,unsigned int *set_flag);

void Point_move(machine_t robot,motor_t *mt,double target_x,double target_y,double v_max,unsigned int);
int robot_move(machine_t,motor_t*,move_set_t,unsigned int *);

void Victim_position(machine_t robot,chased_t *victim);

unsigned int Stop_chack(machine_t robot,double sa);

void Clear_motor_t(motor_t *mt);
unsigned int Stop_back(machine_t robot,motor_t *mt,unsigned int move_dis,unsigned int);


#endif
