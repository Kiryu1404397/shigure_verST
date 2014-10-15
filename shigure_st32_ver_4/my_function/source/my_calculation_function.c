#include "my_calculation_function.h"
#include <math.h>

//角度変換DEG=>RAD
double Angle_DtoR(double sita){
	return	((PAI/180)*sita);
}
//角度変換RAD=>DEG
double Angle_RtoD(double sita){
	return	((180/PAI)*sita);
}

//モードの設定
double Angle_mode_set(int mode){
	double
		ans=0;

	if(mode == DEG_MODE)		ans = 360;
	else if(mode == RAD_MODE)	ans = (2*PAI);

	return ans;
}

//------------------------------------------------------------------------------
//	タイトル ： 角度を-180(-π)<θ<=180(π)に変更する関数
//	  関数名 ： in_angle
//	  戻り値 ： なし
//	   引数1 ： double型 sita	（θ）
//	   引数2 ： int型 mode
//------------------------------------------------------------------------------
double In_angle(double sita,int mode){
	double
		dr_all=0,
		ans=0;

	dr_all = Angle_mode_set(mode);

	ans = sita - (((signed int)(sita/dr_all))*dr_all);

	if(ans > (dr_all*0.5)){
		ans = ans - dr_all;
	}else if(ans < ((-1)*dr_all*0.5)){
		ans = ans + dr_all;
	}

	return ans;
}

//2個の角度の差の計算
double Difference_angle(double target_angle,double reference_angle,int mode){
	double
		dr_all=0,
		ans = 0;

	dr_all = Angle_mode_set(mode);

	if(reference_angle > 0){
		if(((reference_angle-(dr_all*0.5)) < target_angle) && (target_angle < (dr_all*0.5))){
			ans = target_angle - reference_angle;
		}else{
			ans = target_angle + dr_all - reference_angle;
		}
	}else if(reference_angle < 0){
		if(((reference_angle+(dr_all*0.5)) > target_angle) && (target_angle > ((-1)*(dr_all*0.5)))){
			ans = target_angle - reference_angle;
		}else{
			ans = target_angle - dr_all - reference_angle;
		}
	}else{
		ans = target_angle;
	}

	return ans;
}

//現在地から目標地との角度を求める関数
double Target_angle(double target_x,double target_y,double my_x,double my_y,int mode){
	double
		dr_all=0,
		ans = 0;

	dr_all = Angle_mode_set(mode);

	if((target_y-my_y) == 0)		ans = 0;
	else if((target_x-my_x) == 0){
		if((target_y-my_y) > 0)		ans = dr_all*0.5;
		else if((target_y-my_y) < 0)ans = (-1)*dr_all*0.5;
		else if(target_y-my_y)		ans = 0;
	}else{
		ans = atan2((target_y-my_y),(target_x-my_x));
		if(mode == DEG_MODE)	ans = Angle_RtoD(ans);
	}
	return ans;
}

//現在の角度と差の角度を合計する関数
double Actual_angle(double sa_angle,double reference_angle,int mode){
	return (In_angle((reference_angle + sa_angle),mode));
}

//データを上限、下限に収める関数
double Limit_ul(double data,double over,double under){
	double
		ans=0;
	if(data > over)			ans = over;
	else if(data < under)	ans = under;
	else 					ans = data;

	return ans;
}

//現在地から目標地との距離を求める関数
double Target_distance(double target_x,double target_y,double my_x,double my_y){
	double
		l=0;

	l = pow(pow(target_x-my_x,2)+pow(target_y-my_y,2),0.5);

	return l;
}
