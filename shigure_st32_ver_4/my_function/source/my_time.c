#include "my_time.h"

//タイマ割り込み内での時間待ちとメインループ用関数
void Interrput_timer(float interrput_time){
	Elapsed_time(TIMER_DELAY,interrput_time);
	Elapsed_time(TIMER_MAIN,interrput_time);
}

//時間データ保存
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
//時間読み込み
float Read_time(int use_timer){
	return (Time_data(use_timer,0,TIMER_READ));
}
//時間書き込み
void Write_time(int use_timer,float data){
	Time_data(use_timer,data,TIMER_WRITE);
}

//経過時間
void Elapsed_time(int use_timer,float elapsed_time){
	float f=0;
	f = Read_time(use_timer) - elapsed_time;
	if(f >= 0)	Write_time(use_timer,f);
	else		Write_time(use_timer,0);
}
//時間待ち関数(引数はミリ秒単位で指定)
void Delay_ms(unsigned int wait_time){
  Write_time(TIMER_DELAY,(float)wait_time/1000);	//外部変数に待ち時間を設定
  while(Chack_timer(TIMER_DELAY) == 0);
}

//カウントダウン終了確認
unsigned int Chack_timer(int chack_timer){
	if(Read_time(chack_timer) == 0){
		return 1;
	}else{
		return 0;
	}
}

//メイン文内ループ用関数
unsigned int Main_roop_flag(float interrput_time){
	if(Chack_timer(TIMER_MAIN)){
		Write_time(TIMER_MAIN,interrput_time);
		return 1;
	}else{
		return 0;
	}
}

