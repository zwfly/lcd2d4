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
	static BIT finish_flag = 0;
	static BIT reps_num_appear_flag = 0;

	level = 0;
	Repeat_Stop();

	switch (g_tWork.mode) {
	case E_Simple_metering_mode:

		if (g_tWork.sum % 10 == 0) {
			BEEP_Start(1, BEEP_LONG_TIME, 1, 1);
		} else {
			BEEP_Start(1, BEEP_SHORT_TIME, 1, 1);
		}
		g_tWork.pulls_num = g_tWork.sum;
		g_tWork.cal_num = g_tWork.sum * CAL_a;

		/********************/
		LCD_Show_Pulls_Num(g_tWork.pulls_num);
		LCD_Show_CAL_Num(g_tWork.cal_num);

		LCD_Clear_REP_Num();
		LCD_Clear_REP_ICO();
		LCD_Clear_ABCD();
		LCD_Clear_QS_ICO();
		LCD_Clear_COACH_ICO();

		LCD_Show_CAL_ICO();
		LCD_Show_Line_up();
		break;
	case E_Quick_start_mode:

		if (finish_flag) {
			BEEP_Start(1, BEEP_SHORT_TIME, 1, 1);
			g_tWork.sum = Rep_Pull_num[g_tWork.reps_mode - 'A'][0]
					* Rep_Pull_num[g_tWork.reps_mode - 'A'][1];
		} else {
			if (g_tWork.sum
					== Rep_Pull_num[g_tWork.reps_mode - 'A'][0]
							* Rep_Pull_num[g_tWork.reps_mode - 'A'][1]) {
				finish_flag = 1;
				BEEP_Start(1, 3 * BEEP_SHORT_TIME, 1, 1);
			} else {
				if (g_tWork.sum % Rep_Pull_num[g_tWork.reps_mode - 'A'][1]
						== 0) {
					BEEP_Start(1, BEEP_SHORT_TIME, BEEP_SHORT_TIME, 3);
				} else {
					BEEP_Start(1, BEEP_SHORT_TIME, 1, 1);
				}
			}
			reps_num_appear_flag = 1;
			g_tWork.reps_num = g_tWork.sum
					/ Rep_Pull_num[g_tWork.reps_mode - 'A'][1];
			g_tWork.pulls_num = g_tWork.sum
					% Rep_Pull_num[g_tWork.reps_mode - 'A'][1];
			g_tWork.cal_num = g_tWork.sum * CAL_a;
		}
		LCD_Show_REP_Num(g_tWork.reps_num);
		LCD_Show_Pulls_Num(g_tWork.pulls_num);
		LCD_Show_CAL_Num(g_tWork.cal_num);

		LCD_Show_REP_ICO();
		LCD_Show_ABCD(g_tWork.reps_mode);

		LCD_Show_QS_ICO();
		LCD_Clear_COACH_ICO();

		LCD_Show_CAL_ICO();
		LCD_Show_Line_up();

		break;
	case E_Coach_mode:
		if (finish_flag) {
			BEEP_Start(COACH_DELAY_TIME, BEEP_SHORT_TIME, 1, 1);
			g_tWork.sum = Rep_Pull_num[g_tWork.reps_mode - 'A'][0]
					* Rep_Pull_num[g_tWork.reps_mode - 'A'][1];
		} else {
			if (g_tWork.sum
					== Rep_Pull_num[g_tWork.reps_mode - 'A'][0]
							* Rep_Pull_num[g_tWork.reps_mode - 'A'][1]) {
				finish_flag = 1;
				BEEP_Start(1, 3 * BEEP_SHORT_TIME, 1, 1);
			} else {
				if (g_tWork.sum % Rep_Pull_num[g_tWork.reps_mode - 'A'][1]
						== 0) {
					BEEP_Start(1, BEEP_SHORT_TIME, BEEP_SHORT_TIME, 3);
				} else {
					BEEP_Start(COACH_DELAY_TIME, BEEP_SHORT_TIME, 1, 1);
				}
			}
			reps_num_appear_flag = 1;
			g_tWork.reps_num = g_tWork.sum
					/ Rep_Pull_num[g_tWork.reps_mode - 'A'][1];
			g_tWork.pulls_num = g_tWork.sum
					% Rep_Pull_num[g_tWork.reps_mode - 'A'][1];
			g_tWork.cal_num = g_tWork.sum * CAL_a;
		}
		LCD_Show_REP_Num(g_tWork.reps_num);
		LCD_Show_Pulls_Num(g_tWork.pulls_num);
		LCD_Show_CAL_Num(g_tWork.cal_num);

		LCD_Show_REP_ICO();
		LCD_Show_ABCD(g_tWork.reps_mode);

		LCD_Clear_QS_ICO();
		LCD_Show_COACH_ICO();

		LCD_Show_CAL_ICO();
		LCD_Show_Line_up();

		break;
	}

#if 0
	LCD_Show_Pulls_Num(g_tWork.pulls_num);
	LCD_Show_CAL_Num(g_tWork.cal_num);
	if (reps_num_appear_flag) {
		LCD_Show_REP_Num(g_tWork.reps_num);
	} else {
		LCD_Clear_REP_Num();
	}
#endif
}

