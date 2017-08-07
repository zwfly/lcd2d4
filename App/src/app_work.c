/*
 * app_work.c
 *
 *  Created on: 2017Äê7ÔÂ6ÈÕ
 *      Author: admin
 */

#include "app.h"

#define BEEP_SHORT_TIME  10
#define BEEP_LONG_TIME  30
#define COACH_DELAY_TIME 200
#define CAL_a 2

const uint8_t Rep_Pull_num[4][2] = { { 10, 20 }, { 20, 25 }, { 30, 30 }, { 50,
		40 } };

WORK_T g_tWork;
static uint8_t count_NoAction = 0;
static BIT pull_once_flag = 0;

static void app_work_pro(void);

void work_Init(void) {
	g_tWork.mode = E_Simple_metering_mode;
	g_tWork.reps_mode = '\0';
	g_tWork.sum = 0;
	g_tWork.reps_num = 0;
	g_tWork.pulls_num = 0;
	g_tWork.cal_num = 0;

	count_NoAction = 0;
}

void query_work_sum(void) {
	g_tWork.sum++;
	if (g_tWork.sum > 10000) {
		g_tWork.sum = 0;
	}
	pull_once_flag = 1;

}

void app_work_1s_pro(void) {
	if (count_NoAction < 255) {
		count_NoAction++;
	}

}
void app_work_100ms_pro(void) {
	if (pull_once_flag) {
		pull_once_flag = 0;
		///////////////////
		app_key_clear_noOps_timeoutCnt();
		app_work_pro();
	}

}

static void app_work_pro(void) {
	
}

