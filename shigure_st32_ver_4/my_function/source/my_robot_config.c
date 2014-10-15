#include "my_robot_config.h"
#include "my_calculation_function.h"

//エンコーダの回転距離計算
double Enc_distance(signed long enc_ct,unsigned int pulse,float tire_diameter){
	double
		ans=0;

		ans = (((double)enc_ct/((pulse*4)))*tire_diameter*PAI);

	return ans;
}
//台形制御のスピード計算
double Trapezoid_control(double my_x,double my_y,position_t start,position_t end,double v_max,double start_v_min,double s_acc,double e_acc){
	double
		s_my_p=0,
		e_my_p=0,
		hf_my_p=0,
 		speed=0;

	s_my_p = pow(pow(my_y-start.y,2)+pow(my_x-start.x,2),0.5);
	e_my_p = pow(pow(end.y-my_y,2)+pow(end.x-my_x,2),0.5);
	hf_my_p = (s_my_p + e_my_p)*0.5;

	//台形制御
	if(s_my_p<hf_my_p)		speed = (hf_my_p - fabs(hf_my_p - s_my_p))*s_acc;
	else if(s_my_p>hf_my_p)	speed = (hf_my_p - fabs(hf_my_p - s_my_p))*e_acc;

	if(s_my_p < 0)								speed *= (-1);
	else if(s_my_p < hf_my_p && speed < start_v_min)	speed += start_v_min;

	speed = Limit_ul(speed,v_max,(-1)*v_max);

	return speed;
}
