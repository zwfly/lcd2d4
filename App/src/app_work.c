/*
 * app_work.c
 *
 *  Created on: 2017Äê7ÔÂ6ÈÕ
 *      Author: admin
 */

#include "app.h"

idata WORK_T g_tWork;

static uint8_t cnt = 0;
static uint8_t match_code_cnt = 0;

static void app_work_pro(void);

void app_work_Init(void) {
	cnt = 0;
	match_code_cnt = 0;
	memset((uint8_t *) &g_tWork, 0, sizeof(WORK_T));
	LCD_Show_BAZOOKA_ICO();
}

void app_work_1s_pro(void) {

	if (g_tWork.match_code_mode) {
		match_code_cnt++;
		if (match_code_cnt > 45) {
			g_tWork.match_code_mode = 0;
			app_2d4_switch_saved_address();
		}
	} else {
		match_code_cnt = 0;
	}

	cnt++;
	if (cnt == 6) {
//		cnt = 0;
		Repeat_Stop();
		LCD_Clear_All();
		LCD_Show_BAZOOKA_ICO();
		LCD_ShowString(" PWR OFF");
		app_lcd_default_string_set(" PWR OFF", 8, 0);
	}
}
void app_work_100ms_pro(void) {

}
void app_work_cnt_clear(void) {
	cnt = 0;
}
static void app_work_pro(void) {

}

