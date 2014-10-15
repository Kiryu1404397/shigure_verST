#include "my_robot_config.h"
#include "robot_function.h"
#include "my_calculation_function.h"
#include "main.h"
#include <math.h>

/******************************************************************************
*	タイトル ： 角度固定用PID制御
*	  関数名 ： angle_fixing
*	  戻り値 ： double型 モータ制御量(回転)
*	   引数1 ： double型 angle  固定したい角度
*	   引数2 ： int型 p_gain  Pゲイン値
*	   引数3 ： int型 d_gain  Dゲイン値
*	   引数4 ： int型 i_gain  Iゲイン値
*	  作成者 ： 桐生
*	  作成日 ： 2014/06/21
******************************************************************************/
double Angle_fixing(double angle,double my_angle,float p_gain,float d_gain,float i_gain){
	static double
		sa_zen = 0,
		sa_all = 0;
	double
		sa = 0,
		v=0;

	sa = Difference_angle(angle,my_angle,DEG_MODE);

	v = sa*p_gain;
	v += (sa-sa_zen)*d_gain;
	v += sa_all*i_gain;

	sa_all += sa;
	sa_zen = sa;

	return (v);
}

double Distance_fixing(double sa,float p_gain,float d_gain,float i_gain){
	static double
		sa_zen = 0,
		sa_all = 0;
	double
		v=0;

	v = sa*p_gain;
	v += (sa-sa_zen)*d_gain;
	v += sa_all*i_gain;

	sa_all += sa;
	sa_zen = sa;

	return (v);
}

/******************************************************************************
*	タイトル ： スピード固定用PID制御
*	  関数名 ： speed_fixing
*	  戻り値 ： double型 モータ制御量(直線)
*	   引数1 ： double型 speed  固定したい速度
*	   引数2 ： int型 p_gain  Pゲイン値
*	   引数3 ： int型 d_gain  Dゲイン値
*	   引数4 ： int型 i_gain  Iゲイン値
*	  作成者 ： 桐生
*	  作成日 ： 2014/06/21
******************************************************************************/
double Speed_fixing(double speed,double my_speed,float p_gain,float d_gain,float i_gain){
	static double
		sa_zen = 0,
		sa_all = 0;
	double
		sa = 0,
		v=0;

	if(speed >= my_speed){
		sa = speed-my_speed;
	}else{
		sa = speed-my_speed;
		sa = sa_zen + sa;
		sa_all = 0;
	}

	v = sa*p_gain;
	v += (sa-sa_zen)*d_gain;
	v += sa_all*i_gain;

	sa_all += sa;
	sa_zen = sa;

	v = Limit_ul(v,100,0);
	if(speed < 0)	v*=(-1);

	return v;
}




//移動関数
int robot_move(machine_t robot,motor_t *mt,move_set_t set,unsigned int *set_flag){
	unsigned int f;
	static int move_mode=0;

	if(*set_flag == INIT_MODE){
		move_mode = set.move_mode;
	}
	switch(move_mode){
		case MOVE_STRAIGHT:
			f=Machine_move(robot,mt,set.target_x,set.target_y,set.v_max,set.start_acc,set.end_acc,set_flag);
		break;
		case MOVE_ROLL:
			f=Machine_roll(robot,mt,set.target_angle,set.angle_mode,set_flag);
		break;
		case MOVE_CURVE:
			f=Machine_curve(robot,mt,set.target_x,set.target_y,set.v_max,set.start_acc,set.end_acc,set_flag);
		break;
		default:break;
	}
	return f;
}

int Machine_curve(machine_t robot,motor_t *mt,double target_x,double target_y,double v_max,double s_acc,double e_acc,unsigned int *set_flag){
	const double
		start_v_min = 0.05,
//		bun = 5,
		p_gosa = 5,

		rp_gain=140,
		rd_gain=350,
		ri_gain=0,

		sp_gain=1000,
		sd_gain=0,
		si_gain=10;

	static position_t
		st = {0},
		t = {0},
		old_at = {0},
		at = {0};

	static double
		at_l=0,
		at_k=0,
		m_s_acc=0,
		m_e_acc=0,
		t_l=0,
		t_deg=0,
		v=0,
		st_deg=0;
		
	static int
		bun=5,
		ct=0;

	int
		f=0,
		f_end=0;

	double
		s_pwm=0,
		r_pwm=0,
		set_speed=0,
		target_deg=0;

	if(*set_flag == INIT_MODE){
		t.x=target_x;		t.y=target_y;
		m_s_acc=s_acc;		m_e_acc=e_acc;
		st.x=robot.x;		st.y=robot.y;
		v=v_max;
		st_deg = robot.deg;
		t_l = pow(pow(t.y-st.y,2)+pow(t.x-st.x,2),0.5);
		bun = t_l/5;
		t_deg = Target_angle(t.x,t.y,st.x,st.y,DEG_MODE);

		ct=1;
		at_k = Difference_angle(t_deg,st_deg,DEG_MODE) * ct / bun + st_deg;
		at_l = t_l*ct/bun;
		old_at.x = st.x;	old_at.y=st.y;
		at.x = at_l * cos(Angle_DtoR(at_k))+st.x;
		at.y = at_l * sin(Angle_DtoR(at_k))+st.y;

		ct=0; f=0;
		*set_flag = MOVE_MODE;
	}
	if(*set_flag == MOVE_MODE){
		f_end = 0;
		//x
		if(fabs(t_deg) < 90){
			if(robot.x > at.x-p_gosa)	f_end += 1;
		}else{
			if(robot.x < at.x+p_gosa)	f_end += 1;
		}
		//y
		if(t_deg >= 0){
			if(robot.y > at.y-p_gosa)	f_end += 1;
		}else{
			if(robot.y < at.y+p_gosa)	f_end += 1;
		}

		if(f_end >= 2){
			old_at.x = at.x;	old_at.y = at.y;

			ct++;
			at_k = Difference_angle(t_deg,st_deg,DEG_MODE) * ct / bun + st_deg;
			at_l = t_l*ct/bun;

			at.x = (at_l * cos(Angle_DtoR(at_k)))+st.x;
			at.y = (at_l * sin(Angle_DtoR(at_k)))+st.y;
		}

		target_deg = Target_angle(at.x,at.y,old_at.x,old_at.y,DEG_MODE);
		set_speed = Trapezoid_control(robot.x,robot.y,st,t,v,start_v_min,m_s_acc,m_e_acc);
		s_pwm += Limit_ul(Speed_fixing(set_speed,robot.speed,sp_gain,sd_gain,si_gain),100,-100);
		r_pwm += Limit_ul(Angle_fixing(target_deg,robot.deg,rp_gain,rd_gain,ri_gain),100,-100);
		mt->l_s_pwm+=s_pwm;		mt->l_r_pwm+=r_pwm;
		mt->l_r_pwm-=r_pwm;		mt->r_r_pwm+=r_pwm;

	}
	if(ct > bun)	f=1;
	else			f=0;

	return f;
}

//回転関数
int Machine_roll(machine_t robot,motor_t *mt,double target_angle,int angle_mode,unsigned int *set_flag){
	const double
		angle_gosa = 5,
		stop_ct = 5,

		sp_gain=10,
		sd_gain=70,
		si_gain=0,

		rp_gain=25,
		rd_gain=60,
		ri_gain=0;

	static position_t
		lock={0};

	static double
		t_angle=0;

	static int
		ct=0;
	double
		l=0,
//		aqua=0,
		fall=0,
		angle=0,

		s_pwm=0,
		r_pwm=0;
	int
		f=0;

	if(*set_flag == INIT_MODE){
		if(angle_mode == RAD_MODE){
			t_angle = Angle_RtoD(target_angle);
		}else if(angle_mode == DEG_MODE){
			t_angle = target_angle;
		}
		*set_flag = MOVE_MODE;

		lock.x = robot.x;
		lock.y = robot.y;
	}
	if(*set_flag == MOVE_MODE){
		if(((t_angle+angle_gosa) >= robot.deg) && ((t_angle-angle_gosa) <= robot.deg))	ct+= 1;
		else																			ct = 0;

		l = Target_distance(lock.x,lock.y,robot.x,robot.y); 
		angle = Difference_angle(Target_angle(lock.x,lock.y,robot.x,robot.y,RAD_MODE),Angle_DtoR(robot.deg),RAD_MODE);
		fall = 	l*cos(angle);
//		aqua = 	l*sin(angle);

		s_pwm += Limit_ul(Distance_fixing(fall,sp_gain,sd_gain,si_gain),100,-100);
		r_pwm += Limit_ul(Angle_fixing(t_angle,robot.deg,rp_gain,rd_gain,ri_gain),100,-100);
		mt->l_s_pwm += s_pwm;		mt->r_s_pwm += s_pwm;
		mt->l_r_pwm -= r_pwm;		mt->r_r_pwm += r_pwm;


		if(ct >= (stop_ct*INTERRUPT_MAIN_TIME))	f=1;
		else									f=0;
	}

	return f;
}



//移動関数
int Machine_move(machine_t robot,motor_t *mt,double target_x,double target_y,double v_max,double s_acc,double e_acc,unsigned int *set_flag){
	const double
		start_v_min = 0.05,
//		p_gosa = 0,

		rp_gain=50,
		rd_gain=80,
/*		rp_gain=140,
		rd_gain=350,*/
		ri_gain=0,

		sp_gain=1000,
		sd_gain=0,
		si_gain=10;


	static position_t
		t={0},
		st={0};

	static double
		m_s_acc=0,
		m_e_acc=0,
		t_angle=0,
		v=0;
	int
		f_end=0,
		f=0;
	double
		s_pwm=0,
		r_pwm=0,
 		set_speed=0,
		target_deg=0;

	if(*set_flag == INIT_MODE){
		t.x=target_x,	t.y=target_y;
		st.x=robot.x;	st.y=robot.y;
		m_s_acc=s_acc;	m_e_acc=e_acc;
		v=v_max;
		t_angle = Target_angle(t.x,t.y,st.x,st.y,DEG_MODE);
		*set_flag = MOVE_MODE;
	}
	if(*set_flag == MOVE_MODE){
		f_end = 0;
		//x
		if(fabs(t_angle) < 90){
			if(robot.x >= t.x)	f_end += 1;
		}else{
			if(robot.x <= t.x)	f_end += 1;
		}
		//y
		if(t_angle == 0){
			f_end += 1;
		}else if(t_angle > 0){
			if(robot.y >= t.y)	f_end += 1;
		}else{
			if(robot.y <= t.y)	f_end += 1;
		}

		if(f_end >= 2){
			f=1;
		}else{
			target_deg = Target_angle(t.x,t.y,robot.x,robot.y,DEG_MODE);
			set_speed = Trapezoid_control(robot.x,robot.y,st,t,v,start_v_min,m_s_acc,m_e_acc);
			s_pwm += Limit_ul(Speed_fixing(set_speed,robot.speed,sp_gain,sd_gain,si_gain),100,-100);
			r_pwm += Limit_ul(Angle_fixing(target_deg,robot.deg,rp_gain,rd_gain,ri_gain),100,-100);
			mt->l_s_pwm+=s_pwm;		mt->l_r_pwm+=r_pwm;
			mt->l_r_pwm-=r_pwm;		mt->r_r_pwm+=r_pwm;
			f=0;
		}
	}


	return f;
}
int Machine_crab(machine_t robot,motor_t *mt,double target_dis,unsigned int *set_flag){

	const double
		sp_gain=10,
		sd_gain=70,
		si_gain=0,

		rp_gain=25,
		rd_gain=60,
		ri_gain=0;

	static double
		t_dis=0,
		muki=0,
		st_deg=0,
		set_angle=20,
		t_angle=0;

	static unsigned int
		f_ct=0;
//		init_f=0;

	static position_t
		st={0};

	double
		fall=0,
		aqua=0,
		angle=0,
		l=0,
		s_pwm=0,
		r_pwm=0;

	unsigned int
//		f=0,
		f_end=0;

	if(*set_flag == INIT_MODE){
		t_dis = target_dis;
		if(t_dis < 0){
			muki = CRAB_RIGHT;
			t_angle = st_deg+(set_angle*0.5);
		}else{
			muki = CRAB_LEFT;
			t_angle = st_deg-(set_angle*0.5);
		}
		st_deg = robot.deg;
		st.x = robot.x;
		st.y = robot.y;
		*set_flag = MOVE_MODE;
		t_angle = st_deg+(set_angle*0.5);
		f_ct=0;
	}
	if(*set_flag == MOVE_MODE){
		l = Target_distance(st.x,st.y,robot.x,robot.y); 
		angle = Difference_angle(Target_angle(st.x,st.y,robot.x,robot.y,RAD_MODE),Angle_DtoR(st_deg),RAD_MODE);
		fall = 	l*cos(angle);
		aqua = 	l*sin(angle);

		if(muki == CRAB_RIGHT){
			if((robot.deg >= t_angle) && f_ct == 0){
				t_angle = st_deg;
				f_ct = 1;
			}else if((robot.deg <= t_angle) && f_ct == 1){
				t_angle = st_deg-(set_angle*0.5);
				f_ct = 2;
			}else if((robot.deg <= t_angle) && f_ct == 2){
				t_angle = st_deg;
				f_ct = 3;
			}else if((robot.deg >= t_angle) && f_ct == 3){
				t_angle = st_deg+ (set_angle*0.5);
				f_ct = 0;
			}
		}
		if(muki == CRAB_LEFT){
			if((robot.deg <= t_angle) && f_ct == 0){
				t_angle = st_deg;
				f_ct = 1;
			}else if((robot.deg >= t_angle) && f_ct == 1){
				t_angle = st_deg+(set_angle*0.5);
				f_ct = 2;
			}else if((robot.deg >= t_angle) && f_ct == 2){
				t_angle = st_deg;
				f_ct = 3;
			}else if((robot.deg <= t_angle) && f_ct == 3){
				t_angle = st_deg- (set_angle*0.5);
				f_ct = 0;
			}
		}
		s_pwm = Limit_ul(Distance_fixing(fall,sp_gain,sd_gain,si_gain),100,-100);
		r_pwm = Limit_ul(Angle_fixing(t_angle,robot.deg,rp_gain,rd_gain,ri_gain),100,-100);

		mt->l_s_pwm += s_pwm;		mt->r_s_pwm += s_pwm;
		if(muki == CRAB_RIGHT){
			if(f_ct == 0)		mt->l_r_pwm += r_pwm;
			else if(f_ct == 1)	mt->r_r_pwm -= r_pwm;
			else if(f_ct == 2)	mt->l_r_pwm += r_pwm;
			else if(f_ct == 3)	mt->r_r_pwm -= r_pwm;

//			if((f_ct%2) == 0)		mt->l_r_pwm += r_pwm;
//			else if((f_ct%2) == 1)	mt->r_r_pwm -= r_pwm;
		}else if(muki == CRAB_LEFT){
			if(f_ct == 0)		mt->r_r_pwm -= r_pwm;
			else if(f_ct == 1)	mt->l_r_pwm += r_pwm;
			else if(f_ct == 2)	mt->r_r_pwm -= r_pwm;
			else if(f_ct == 3)	mt->l_r_pwm += r_pwm;

//			if((f_ct%2) == 0)		mt->r_r_pwm -= r_pwm;
//			else if((f_ct%2) == 1)	mt->l_r_pwm += r_pwm;
		}

		if(fabs(aqua) >= fabs(t_dis))	f_end = 1;
		else							f_end = 0;  
	}

	return f_end;
}

/******************************************************************************
*	タイトル ： 現在地判断関数
*	  関数名 ： My_position
*	   引数1 ： machine型 *robot  マシンデータのアドレス
*	   引数2 ： signed long型 enc1_cnt  エンコーダ1カウント
*	   引数3 ： signed long型 enc2_cnt  エンコーダ2カウント
*	  作成者 ： 桐生
*	  作成日 ： 2014/06/25
******************************************************************************/
void My_position(machine_t *robot,signed long encl_cnt,signed long encr_cnt){
	const double
		a_fc = (1-exp((-2)*PAI*5*0.005));							//ローパス用(1-exp(-2*π*fc*dt))


	static double
		sp_lo=0,
		degsp_lo=0,
		speed_zen = 0,
		r_dis_zen = 0,
		l_dis_zen = 0;

	double
		d=0,
		sita=0,
		r_dis=0,
		l_dis=0,
 		deg_s=0;

	r_dis = Enc_distance(encr_cnt,ENC_PULSE,R_TIRE_DIAMETER);
	l_dis = Enc_distance(encl_cnt,ENC_PULSE,L_TIRE_DIAMETER);

	//角度計算
	sita = Angle_RtoD(((r_dis-r_dis_zen)-(l_dis-l_dis_zen))/ENC_WIDTH);
	deg_s = sita/INTERRUPT_MAIN_TIME*1000;

	//直線移動距離計算
	d = (r_dis-r_dis_zen+l_dis-l_dis_zen)/2;
	sp_lo += (d/INTERRUPT_MAIN_TIME - sp_lo)*a_fc;

	//直線移動速度計算
	degsp_lo += (deg_s - degsp_lo)*a_fc;

	//値の格納
	robot->deg = In_angle(robot->deg + sita,DEG_MODE);
	robot->deg_speed = degsp_lo;

	robot->x += d*cos(Angle_DtoR(robot->deg));
	robot->y += d*sin(Angle_DtoR(robot->deg));
	robot->speed = sp_lo;
	robot->acc = (robot->speed - speed_zen) / INTERRUPT_MAIN_TIME * 1000;

	//値の保存
	r_dis_zen = r_dis;
	l_dis_zen = l_dis;
	speed_zen = robot->speed;
}

//移動関数
void Point_move(machine_t robot,motor_t *mt,double target_x,double target_y,double v_max,unsigned int back_f){
	const double
		rp_gain=5,
		rd_gain=10,
		ri_gain=0,

		sp_gain=1000,
		sd_gain=0,
		si_gain=0;

	double
		t_l=0,
		s_pwm=0,
		r_pwm=0,
 		set_speed=0,
		set_deg = 0,  
		target_deg=0;

	target_deg = Target_angle(target_x,target_y,robot.x,robot.y,DEG_MODE);
	t_l = pow(pow(target_x-robot.x,2)+pow(target_y-robot.y,2),0.5);
	set_speed = t_l/INTERRUPT_MAIN_TIME;
	if(set_speed > v_max) set_speed = v_max;

	if(back_f == 1)	set_deg = Actual_angle(180,robot.deg,DEG_MODE);
	else			set_deg = robot.deg;

	s_pwm += Limit_ul(Speed_fixing(set_speed,robot.speed,sp_gain,sd_gain,si_gain),200,-200);
	r_pwm += Limit_ul(Angle_fixing(target_deg,set_deg,rp_gain,rd_gain,ri_gain),200,-200);
	mt->l_s_pwm+=s_pwm;		mt->l_r_pwm+=r_pwm;
	mt->l_r_pwm-=r_pwm;		mt->r_r_pwm+=r_pwm;
}

unsigned int Stop_chack(machine_t robot,double sa){
	static position_t
		old = {0};
	static unsigned int
		stop_ct=0;

	stop_ct+=INTERRUPT_MAIN_TIME;
	if(((old.x-sa) > robot.x) || ((old.x+sa) < robot.x)){
		old.x = robot.x;
		stop_ct = 0;
	}
	if(((old.y-sa) > robot.y) || ((old.y+sa) < robot.y)){
		old.y = robot.y;
		stop_ct = 0;
	}

	return stop_ct;
}

void Victim_position(machine_t robot,chased_t *victim){
	double
		l=0;

//	static double angle=0;

	l = Target_distance(victim->x,victim->y,robot.x,robot.y); 
	if((l >= 0) && (l <= victim->m_l));
	else	l = victim->m_l;
	if(l < 0)	l=0;
	victim->l = victim->m_l-l;
	victim->x += victim->l*cos(Angle_DtoR(victim->angle));
	victim->y += victim->l*sin(Angle_DtoR(victim->angle));

//	angle += l/170*2;
//	victim->x += victim->l*cos(DtoR(angle));
//	victim->y += victim->l*sin(DtoR(angle));

}

void Sw_mode_change(unsigned int sw_now,unsigned int *mode_ct){
	unsigned int
		sw=0,
		sw_zen=0;

	if(sw_now != sw){
		sw_zen = sw;
		sw = sw_now;
		sw_now = ((sw^sw_zen)&sw_zen);
		if((sw_now&SW0_p) == SW0_p){
			*mode_ct += 1;
			*mode_ct %= 7;
		}
		if((sw_now&SW1_p) == SW1_p){
			if(mode_ct > 0)	*mode_ct-=1;
			else 			*mode_ct=6;
		}
	}
}
/*void Court_mode_change(unsigned int sw_now,unsigned int *write){
	unsigned int
		sw=0,
		sw_zen=0,
		f=0;

	if(sw_now != sw){
		sw_zen = sw;
		sw = sw_now;
		sw_now = ((sw^sw_zen)&sw_zen);
		if((sw_now&SW3_p) == SW3_p){
			f = ++f % 2;
		}
	}
	if(write == 0)	*write = BULE_COURT;
	else			*write = RED_COURT;
}*/

/*double Get_ad(void){
	double ad_data=0;

	if(F_VOL == 0){
		ad_data = VOL & 0x3ff;
		F_VOL = 1;			//A/D変換開始
	}

	return ad_data;
}*/

void Clear_motor_t(motor_t *mt){
	mt->l_s_pwm = 0;	mt->l_r_pwm = 0;
	mt->r_s_pwm = 0;	mt->r_r_pwm = 0;
}

unsigned int Stop_back(machine_t robo,motor_t *mt,unsigned int move_dis,unsigned int back_flag){
	const unsigned int
		rp_gain=5,
		rd_gain=10,
		ri_gain=0,

		move_time = 500,
		stop_time = 250;

	const double
		gosa_dis = 2;

	static unsigned int
		f_back = 0,
//		mt_r=0,
//		mt_l=0,
		back_ct=0,
		back_dis=0;

	static position_t
		stop_point={0};

	static double
		r_pwm=0,
		set_deg = 0,
		stop_deg=0;


	if((Stop_chack(robo,gosa_dis) > stop_time)){
		f_back=1;
		back_ct=0;
		stop_point.x = robo.x;
		stop_point.y = robo.y;
		stop_deg = robo.deg;
	}
	if(f_back == 1){
		if(back_flag == 0){
			mt->l_s_pwm = -100;
			mt->r_s_pwm = -100;
//			set_deg = robo.deg;
		}else{
			mt->l_s_pwm = 100;
			mt->r_s_pwm = 100;
//			set_deg = robo.deg;// + 180;
		}
		r_pwm += Limit_ul(Angle_fixing(stop_deg,set_deg,rp_gain,rd_gain,ri_gain),200,-200);
		mt->l_r_pwm+=r_pwm;	mt->r_r_pwm-=r_pwm;

		back_ct += INTERRUPT_MAIN_TIME;
		back_dis = Target_distance(stop_point.x,stop_point.y,robo.x,robo.y);
		if(back_dis > 100)		f_back = 0;
		if(back_ct > move_time)	f_back = 0;
	}

	return f_back;
}
