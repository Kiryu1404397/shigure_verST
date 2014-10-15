#ifndef	_my_robot_config_header_
#define	_my_robot_config_header_

//--------------------------------------------------------------------------------------------------
//�\���̐錾

//�ʒu�f�[�^
typedef struct{
	double x;
	double y;
}position_t;

//���{�b�g���
typedef struct{
	double	x;
	double	y;
	double	deg;
	double	speed;
	double	deg_speed;
	double	acc;
}machine_t;

double Enc_distance(signed long enc_ct,unsigned int pulse,float tire_diameter);
double Trapezoid_control(double my_x,double my_y,position_t start,position_t end,double v_max,double start_v_min,double s_acc,double e_acc);


#endif
