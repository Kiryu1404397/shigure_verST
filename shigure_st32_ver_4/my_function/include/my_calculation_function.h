#ifndef _my_calculation_function_header_
#define _my_calculation_function_header_

#include <math.h>

#define RAD_MODE 1
#define DEG_MODE 2

//------------------------------------------------------------------------------
//”šŠÖŒW‚Ì’è‹`
#define PAI 3.14159265358979


//Šp“xŒvZ
double Angle_DtoR(double sita);
double Angle_RtoD(double sita);
double Angle_mode_set(int mode);
double In_angle(double sita,int mode);
double Difference_angle(double target_angle,double reference_angle,int mode);
double Target_angle(double target_x,double target_y,double my_x,double my_y,int mode);
double Actual_angle(double sa_angle,double reference_angle,int mode);
//‚»‚Ì‘¼
double Limit_ul(double data,double over,double under);

double Target_distance(double target_x,double target_y,double my_x,double my_y);

#endif
