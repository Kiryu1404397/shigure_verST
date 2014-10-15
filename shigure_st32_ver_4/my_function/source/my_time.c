#include "my_time.h"

//�^�C�}���荞�ݓ��ł̎��ԑ҂��ƃ��C�����[�v�p�֐�
void Interrput_timer(float interrput_time){
	Elapsed_time(TIMER_DELAY,interrput_time);
	Elapsed_time(TIMER_MAIN,interrput_time);
}

//���ԃf�[�^�ۑ�
float Time_data(int use_timer,float data,int wr_mode){
	static float delay_timer = 0;
	static float main_loop_timer = 0;

	float ans;

	if(wr_mode == TIMER_READ){
		if(use_timer == TIMER_DELAY){
			ans = delay_timer;
		}else if(use_timer == TIMER_MAIN){
			ans = main_loop_timer;
		}
	}else if(wr_mode == TIMER_WRITE){
		if(data < 0)	data = 0;

		if(use_timer == TIMER_DELAY){
			delay_timer = data;
		}else if(use_timer == TIMER_MAIN){
			main_loop_timer = data;
		}
	}


	return ans;
}
//���ԓǂݍ���
float Read_time(int use_timer){
	return (Time_data(use_timer,0,TIMER_READ));
}
//���ԏ�������
void Write_time(int use_timer,float data){
	Time_data(use_timer,data,TIMER_WRITE);
}

//�o�ߎ���
void Elapsed_time(int use_timer,float elapsed_time){
	float f=0;
	f = Read_time(use_timer) - elapsed_time;
	if(f >= 0)	Write_time(use_timer,f);
	else		Write_time(use_timer,0);
}
//���ԑ҂��֐�(�����̓~���b�P�ʂŎw��)
void Delay_ms(unsigned int wait_time){
  Write_time(TIMER_DELAY,(float)wait_time/1000);	//�O���ϐ��ɑ҂����Ԃ�ݒ�
  while(Chack_timer(TIMER_DELAY) == 0);
}

//�J�E���g�_�E���I���m�F
unsigned int Chack_timer(int chack_timer){
	if(Read_time(chack_timer) == 0){
		return 1;
	}else{
		return 0;
	}
}

//���C���������[�v�p�֐�
unsigned int Main_roop_flag(float interrput_time){
	if(Chack_timer(TIMER_MAIN)){
		Write_time(TIMER_MAIN,interrput_time);
		return 1;
	}else{
		return 0;
	}
}

