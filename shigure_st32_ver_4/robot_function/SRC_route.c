#include "SRC_route.h"
#include "my_calculation_function.h"
#include "my_robot_config.h"
#include "robot_function.h"


void Test_run(machine_t robo,chased_t *victim,unsigned int court_mode,unsigned int *dosa_ct){
//一回転コース６
/*	switch(*dosa_ct){
		case 0:
			if(victim->x >= 340*2.25){
				victim->x = 340*2.25;
				victim->y = 0;
				victim->angle = 45;
				*dosa_ct+=1;
			}
		break;
		case 1:
			if(victim->x >= 340*3){
				victim->x = 340*3;
				victim->y = 340*0.75;
				victim->angle = 90;
				*dosa_ct+=1;
			}
		break;
		case 2:
			if(victim->y >= 340*1.25){
				victim->x = 340*3;
				victim->y = 340*1.25;
				victim->angle = 135;
				*dosa_ct+=1;
			}
		break;
		case 3:
			if(victim->x >= 340*2.25){
				victim->x = 340*2.25;
				victim->y = 340*2;
				victim->angle = 180;
				*dosa_ct+=1;
			}
		break;
		case 4:
			if(victim->x <= 340*1.75){
				victim->x = 340*1.75;
				victim->y = 340*2;
				victim->angle = -135;
				*dosa_ct+=1;
			}
		break;
		case 5:
			if(victim->x <= 340*1){
				victim->x = 340*1;
				victim->y = 340*1.25;
				victim->angle = -90;
				*dosa_ct+=1;
			}
		break;
		case 6:
			if(victim->y <= 340*0.75){
				victim->x = 340*1;
				victim->y = 340*0.75;
				victim->angle = -45;
				*dosa_ct+=1;
			}
		break;
		case 7:
			if(victim->x <= 340*1.75){
				victim->x = 340*1.75;
				victim->y = 340*0;
				victim->angle = 0;
				*dosa_ct+=1;
			}
		break;
		case 8:
			if(victim->x >= 340*2.25){
				victim->x = 340*2.25;
				victim->y = 0;
				victim->angle = 45;
				*dosa_ct+=1;
			}
		break;
		case 9:
			if(victim->x >= 340*3){
				victim->x = 340*3;
				victim->y = 340*0.75;
				victim->angle = 90;
				*dosa_ct+=1;
			}
		break;
		case 10:
 			if(victim->y >= 340*2){
				victim->x = 340*3;
				victim->y = 340*2; 
				victim->angle = Target_angle(340*4,340*3,victim->x,victim->y,DEG_MODE);
				*dosa_ct+=1;
			}
		break;
		case 11:
			if(robo.x >= 340*3.85){
				victim->x = 340*4;
				victim->y = 340*3;
				victim->angle = 0;
				*dosa_ct+=1;
			}
		break;
		case 12:
			if(robo.x >= (340*5)){
				victim->f_arrest = 1;
				*dosa_ct+=1;
			}
		break;
	}*/

//行き過ぎてバックのコース３
	if(court_mode == BULE_COURT){
		switch(*dosa_ct){
			case 0:
				if(robo.x >= 340*4){
					victim->x = 340*4;
					victim->y = 0;
					victim->angle = 180;
					*dosa_ct+=1;
				}
			break;
			case 1:
				if(victim->x <= 340*3){
					victim->x = 340*3.5;
					victim->y = 0;
					victim->angle = Target_angle(340*2.75,340*1,victim->x,victim->y,DEG_MODE);
					*dosa_ct+=1;
				}
			break;
			case 2:
				if(victim->x <= (340*2.75)){
					victim->x = 340*2.75;
					victim->y = 340*1;
					victim->angle = Target_angle(340*4.25,340*3,victim->x,victim->y,DEG_MODE);
					*dosa_ct+=1;
				}
			break;
			case 3:
				if(victim->x >= (340*4) || victim->y >= (340*3)){
					victim->x = 340*4.25;
					victim->y = 340*3+30;
					victim->angle = 0;
					*dosa_ct+=1;
				}
			break;
			case 4:
				if(robo.x >= (340*5+20)){
					victim->f_arrest = 1;
					*dosa_ct+=1;
				}
			break;
		}
	}else if(court_mode == RED_COURT){
		switch(*dosa_ct){
			case 0:
				if(robo.x >= 340*4){
					victim->x = 340*4;
					victim->y = 0;
					victim->angle = 180;
					*dosa_ct+=1;
				}
			break;
			case 1:
				if(victim->x <= 340*3){
					victim->x = 340*3.5;
					victim->y = 0;
					victim->angle = Target_angle(340*2.75,340*1,victim->x,victim->y,DEG_MODE);
					*dosa_ct+=1;
				}
			break;
			case 2:
				if(victim->x <= (340*2.75)){
					victim->x = 340*2.75;
					victim->y = 340*1;
					victim->angle = Target_angle(340*4.25,340*3,victim->x,victim->y,DEG_MODE);
					*dosa_ct+=1;
				}
			break;
			case 3:
				if(victim->x >= (340*4) || victim->y >= (340*3)){
					victim->x = 340*4.25;
					victim->y = 340*3;
					victim->angle = 0;
					*dosa_ct+=1;
				}
			break;
			case 4:
				if(robo.x >= (340*5+20)){
					victim->f_arrest = 1;
					*dosa_ct+=1;
				}
			break;
		}
	}

}
//コース１
void Course1_run(machine_t robo,chased_t *victim,unsigned int court_mode,unsigned int *dosa_ct){

	if(court_mode == BULE_COURT){
		switch(*dosa_ct){
			case 0:
				if(victim->x >= (340*1)){
					victim->x = 340*1;
					victim->y = 0;
					victim->angle = 45;
					*dosa_ct+=1;
				}
			break;
			case 1:
				if((victim->x) >= (340*4)){
 					victim->x = 340*4;
					victim->y = 340*3-15;
					victim->angle = 0;
					*dosa_ct+=1;
				}
			break;
			case 2:
				if(robo.x >= (340*5+20)){
					victim->f_arrest = 1;
					*dosa_ct+=1;
				}
			break;
		}
	}else if(court_mode == RED_COURT){
		switch(*dosa_ct){
			case 0:
				if(victim->x >= (340*1)){
					victim->x = 340*1;
					victim->y = 0;
					victim->angle = 45;
					*dosa_ct+=1;  
				}
			break;
			case 1:
				if((victim->x) >= (340*4)){
					victim->x = 340*4;
					victim->y = 340*3+10;
					victim->angle = 0;
					*dosa_ct+=1;
				}
			break;
			case 2:
				if(robo.x >= (340*5+20)){
					victim->f_arrest = 1;
					*dosa_ct+=1;
				}
			break;
		}
	}
}

//コース２
void Course2_run(machine_t robo,chased_t *victim,unsigned int court_mode,unsigned int *dosa_ct){
	if(court_mode == BULE_COURT){
		switch(*dosa_ct){
			case 0:
				if((victim->x) >= (340*2)){
					victim->x = 340*2;
					victim->y = 0;
					victim->angle = Target_angle(340*1+15,340*1,victim->x,victim->y,DEG_MODE);
					*dosa_ct+=1;
				}
			break;
			case 1:
				if((victim->y) >= (340*1) || victim->x <= (340*1+15)){
					victim->x = 340*1+15;
					victim->y = 340*1;
					victim->angle = 90;
					*dosa_ct+=1;
				}
			break;
			case 2:
				if((victim->y) >= (340*3-20)){
					victim->x = 340*1+20;
					victim->y = 340*3-30;
					victim->angle = 0;
					*dosa_ct+=1;
				}
			break;
			case 3:
				if(robo.x >= (340*5+40)){
					victim->f_arrest = 1;
					*dosa_ct+=1;
				}
			break;
		}
	}else if(court_mode == RED_COURT){
		switch(*dosa_ct){
			case 0:
				if((victim->x) >= (340*2)){
					victim->x = 340*2;
					victim->y = 0;
					victim->angle = Target_angle(340*1,340*1,victim->x,victim->y,DEG_MODE);
					*dosa_ct+=1;
				}
			break;
			case 1:
				if((victim->y) >= (340*1)){
					victim->x = 340*1;
					victim->y = 340*1;
					victim->angle = 90;
					*dosa_ct+=1;
				}
			break;
			case 2:
				if((victim->y) >= (340*3)){
					victim->x = 340*1;
					victim->y = 340*3;
					victim->angle = 0;
					*dosa_ct+=1;
				}
			break;
			case 3:
				if(robo.x >= (340*5+40)){
					victim->f_arrest = 1;
					*dosa_ct+=1;
				}
			break;
		}
	}
}
//コース３
void Course3_run(machine_t robo,chased_t *victim,unsigned int court_mode,unsigned int *dosa_ct){
	if(court_mode == BULE_COURT){
		switch(*dosa_ct){
			case 0:
				if(victim->x >= 340*2){
					victim->x = 340*2;
					victim->y = 0;
					victim->angle = Target_angle(340*4.25,340*3,340*2,0,DEG_MODE);
					*dosa_ct+=1;
				}
			break;
			case 1:
				if(victim->x >= (340*4.25)){
					victim->x = 340*4.25;
					victim->y = 340*3;
					victim->angle = 0;
					*dosa_ct+=1;
				}
			break;
			case 2:
				if(robo.x >= (340*5+20)){
					victim->f_arrest = 1;
					*dosa_ct+=1;
				}
			break;
		}
	}else if(court_mode == RED_COURT){
		switch(*dosa_ct){
			case 0:
				if(victim->x >= 340*2){
					victim->x = 340*2;
					victim->y = 0;
					victim->angle = Target_angle(340*4.25,340*3,340*2,0,DEG_MODE);
					*dosa_ct+=1;
				}
			break;
			case 1:
				if(victim->x >= (340*4.25)){
					victim->x = 340*4.25;
					victim->y = 340*3;
					victim->angle = 0;
					*dosa_ct+=1;
				}
			break;
			case 2:
				if(robo.x >= (340*5+20)){
					victim->f_arrest = 1;
					*dosa_ct+=1;
				}
			break;
		}
	}

}
//コース４
void Course4_run(machine_t robo,chased_t *victim,unsigned int court_mode,unsigned int *dosa_ct){
	if(court_mode == BULE_COURT){
		switch(*dosa_ct){
			case 0:
				if(victim->x >= 340*1){
					victim->x = 340*1;
					victim->y = 0;
					victim->angle = 45;
					*dosa_ct+=1;
				}
			break;
			case 1:
				if(victim->x >= 340*2){
					victim->x = 340*2;
					victim->y = 340*1;
					victim->angle = 0;
					*dosa_ct+=1;
				}
			break;
			case 2:
				if(victim->x >= 340*3.25){
					victim->x = 340*3.25;
					victim->y = 340*1;
					victim->angle = 45;
					*dosa_ct+=1;
				}
			break;
			case 3:
				if(victim->x >= 340*4){
					victim->x = 340*4;
					victim->y = 340*1.75;
	//				victim->angle = 90;
					victim->angle = Target_angle(340*3.75,340*2.5,victim->x,victim->y,DEG_MODE);
					*dosa_ct+=1;
				}
			break;
			case 4:
				if(victim->y >= 340*2.5){
					victim->x = 340*3.75;
					victim->y = 340*2.5;
	//				victim->angle = 0;
					victim->angle = Target_angle(340*4.25,340*3,victim->x,victim->y,DEG_MODE);
					victim->m_l = 100;
					*dosa_ct+=1;
				}
			break;
			case 5:
				if(victim->y >= (340*3-5)){
					victim->x = 340*4.25;
					victim->y = 340*3-5;
					victim->angle = 0;
					*dosa_ct+=1;
				}
			break;
			case 6 :
				if(robo.x >= (340*5)){
					victim->f_arrest = 1;
					*dosa_ct+=1;
				}
			break;
		}
	}else if(court_mode == RED_COURT){
		switch(*dosa_ct){
			case 0:
				if(victim->x >= 340*1){
					victim->x = 340*1;
					victim->y = 0;
					victim->angle = 45;
					*dosa_ct+=1;
				}
			break;
			case 1:
				if(victim->x >= 340*2){
					victim->x = 340*2;
					victim->y = 340*1;
					victim->angle = 0;
					*dosa_ct+=1;
				}
			break;
			case 2:
				if(victim->x >= 340*3.25){
					victim->x = 340*3.25;
					victim->y = 340*1;
					victim->angle = 45;
					*dosa_ct+=1;
				}
			break;
			case 3:
				if(victim->x >= 340*4){
					victim->x = 340*4;
					victim->y = 340*1.75;
	//				victim->angle = 90;
					victim->angle = Target_angle(340*3.75,340*2.5,victim->x,victim->y,DEG_MODE);
					*dosa_ct+=1;
				}
			break;
			case 4:
				if(victim->y >= 340*2.5){
					victim->x = 340*3.75;
					victim->y = 340*2.5;
	//				victim->angle = 0;
					victim->angle = Target_angle(340*4.25,340*3,victim->x,victim->y,DEG_MODE);
					victim->m_l = 100;
					*dosa_ct+=1;
				}
			break;
			case 5:
				if(victim->y >= (340*3)){
					victim->x = 340*4.25;
					victim->y = 340*3;
					victim->angle = 0;
					*dosa_ct+=1;
				}
			break;
			case 6 :
				if(robo.x >= (340*5)){
					victim->f_arrest = 1;
					*dosa_ct+=1;
				}
			break;
		}
	}

}
//コース５
void Course5_run(machine_t robo,chased_t *victim,unsigned int court_mode,unsigned int *dosa_ct){
	if(court_mode == BULE_COURT){
		switch(*dosa_ct){
			case 0:
				if(victim->x >= 340*2){
					victim->x = 340*2;
					victim->y = 0;
					victim->angle = 45;
					*dosa_ct+=1;
				}
			break;
			case 1:
				if(victim->x >= 340*3){
					victim->x = 340*3;
					victim->y = 340*1;
					victim->angle = Target_angle(340*4,340*3,340*3,340*1,DEG_MODE);
					*dosa_ct+=1;
				}
			break;
			case 2:
				if(robo.x >= 340*3.8){
					victim->x = 340*4;
					victim->y = 340*3;

					victim->angle = 0;
					*dosa_ct+=1;
				}
			break;
			case 3:
				if(robo.x >= (340*5)){
					victim->f_arrest = 1;
					*dosa_ct+=1;
				}
			break;
		}
	}else if(court_mode == RED_COURT){
		switch(*dosa_ct){
			case 0:
				if(victim->x >= 340*2){
					victim->x = 340*2;
					victim->y = 0;
					victim->angle = 45;
					*dosa_ct+=1;
				}
			break;
			case 1:
				if(victim->x >= 340*3){
					victim->x = 340*3;
					victim->y = 340*1;
					victim->angle = Target_angle(340*4,340*3,340*3,340*1,DEG_MODE);
					*dosa_ct+=1;
				}
			break;
			case 2:
				if(robo.x >= 340*3.8){
					victim->x = 340*4;
					victim->y = 340*3;

					victim->angle = 0;
					*dosa_ct+=1;
				}
			break;
			case 3:
				if(robo.x >= (340*5)){
					victim->f_arrest = 1;
					*dosa_ct+=1;
				}
			break;
		}
	}
}

//コース６
void Course6_run(machine_t robo,chased_t *victim,unsigned int court_mode,unsigned int *dosa_ct){
	if(court_mode == RED_COURT){
		switch(*dosa_ct){
			case 0:
				if(victim->x >= 340*2.25){
					victim->x = 340*2.25;
					victim->y = 0;
					victim->angle = 45;
					*dosa_ct+=1;
				}
			break;
			case 1:
				if(victim->x >= 340*3){
					victim->x = 340*3;
					victim->y = 340*0.75;
					victim->angle = 90;
					*dosa_ct+=1;
				}
			break;
			case 2:
	 			if(victim->y >= 340*2){
					victim->x = 340*3;
					victim->y = 340*2-20 ;
					victim->angle = Target_angle(340*4-10,340*3,victim->x,victim->y,DEG_MODE);
					*dosa_ct+=1;
				}
			break;
			case 3:
				if(robo.x >= 340*3.85){
					victim->x = 340*4-10;
					victim->y = 340*3;
					victim->angle = 0;
					*dosa_ct+=1;
				}
			break;
			case 4:
				if(robo.x >= (340*5)){
					victim->f_arrest = 1;
					*dosa_ct+=1;
				}
			break;
		}
	}else if(court_mode == BULE_COURT){
		switch(*dosa_ct){
			case 0:
				if(victim->x >= 340*2.25){
					victim->x = 340*2.25;
					victim->y = 0;
					victim->angle = 45;
					*dosa_ct+=1;
				}
			break;
			case 1:
				if(victim->x >= 340*3){
					victim->x = 340*3;
					victim->y = 340*0.75;
					victim->angle = 90;
					*dosa_ct+=1;
				}
			break;
			case 2:
	 			if(victim->y >= 340*2){
					victim->x = 340*3;
					victim->y = 340*2;
					victim->angle = Target_angle(340*4,340*3,victim->x,victim->y,DEG_MODE);
					*dosa_ct+=1;
				}
			break;
			case 3:
				if(robo.x >= 340*3.85){
					victim->x = 340*4;
					victim->y = 340*3;
					victim->angle = 0;
					*dosa_ct+=1;
				}
			break;
			case 4:
				if(robo.x >= (340*5)){
					victim->f_arrest = 1;
					*dosa_ct+=1;
				}
			break;
		}
	}
}

unsigned int Course_run(machine_t robo,chased_t *victim,unsigned int mode_ct,unsigned int court_mode){
	static unsigned int dosa_ct=0;

	switch(mode_ct){
		case 0:	Test_run(robo,victim,court_mode,&dosa_ct);
		break;
		case 1:	Course1_run(robo,victim,court_mode,&dosa_ct);
		break; 
		case 2:	Course2_run(robo,victim,court_mode,&dosa_ct);
		break;
		case 3:	Course3_run(robo,victim,court_mode,&dosa_ct);
		break;
		case 4:	Course4_run(robo,victim,court_mode,&dosa_ct);
		break;
		case 5:	Course5_run(robo,victim,court_mode,&dosa_ct);
		break;
		case 6:	Course6_run(robo,victim,court_mode,&dosa_ct);
		break;
		default:break;
	}
	return dosa_ct; 
}

