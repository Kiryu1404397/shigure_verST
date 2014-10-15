#ifndef	_my_time_header_
#define _my_time_header_

#define TIMER_READ	0
#define TIMER_WRITE	1

#define TIMER_DELAY	2
#define TIMER_MAIN	3

float Time_data(int use_timer,float data,int wr_mode);

float Read_time(int use_timer);
void Write_time(int use_timer,float data);

unsigned int Chack_timer(int chack_time);
void Elapsed_time(int use_timer,float elapsed_time);

unsigned int Main_roop_flag(float interrput_time);
void Delay_ms(unsigned int wait_time);
void Interrput_timer(float interrput_time);


#endif
