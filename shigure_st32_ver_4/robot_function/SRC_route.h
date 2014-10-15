#ifndef	_SRC_route_headler_
#define _SRC_route_headler_

#include "my_calculation_function.h"
#include "my_robot_config.h"
#include "robot_function.h"


#define BULE_COURT 0x40
#define RED_COURT 0x80

void Test_run(machine_t robo,chased_t *victim,unsigned int court_mode,unsigned int *dosa_ct);
void Course1_run(machine_t robo,chased_t *victim,unsigned int court_mode,unsigned int *dosa_ct);
void Course2_run(machine_t robo,chased_t *victim,unsigned int court_mode,unsigned int *dosa_ct);
void Course3_run(machine_t robo,chased_t *victim,unsigned int court_mode,unsigned int *dosa_ct);
void Course4_run(machine_t robo,chased_t *victim,unsigned int court_mode,unsigned int *dosa_ct);
void Course5_run(machine_t robo,chased_t *victim,unsigned int court_mode,unsigned int *dosa_ct);
void Course6_run(machine_t robo,chased_t *victim,unsigned int court_mode,unsigned int *dosa_ct);
unsigned int Course_run(machine_t robo,chased_t *victim,unsigned int mode_ct,unsigned int court_mode);

#endif
