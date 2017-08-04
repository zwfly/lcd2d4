/*
 * app_key.c
 *
 *  Created on: 2017年7月7日
 *      Author: admin
 */

#include "app.h"

DEVICE_T g_tDevice;

static E_TRAINING_MODE mode;
static char letter = '\0';

#define BLINK_FLASH_TIME   4

/*
 * level: 0, 拉动时候的界面
 *        1,
 * */
uint8_t level = 0;

static void app_UI_init(void);

void app_key_init(void) {
	level = 0;

	clr_PIPS2;
	clr_PIPS1;
	clr_PIPS0;

	set_PIT3;
	set_PINEN3;
	clr_PIPEN3;

	mode = E_Simple_metering_mode;
	g_tWork.mode = E_Simple_metering_mode;
	g_tDevice.status = E_PowerOn;
	app_UI_init();
}

static void app_UI_init(void) {
	switch (mode) {
	case E_Simple_metering_mode:

		LCD_Show_Pulls_Num(0);
		LCD_Show_CAL_Num(0);

		LCD_Show_Line_up();
		LCD_Clear_REP_ICO();

		LCD_Clear_ABCD();

		LCD_Show_CAL_ICO();
		LCD_Clear_QS_ICO();
		LCD_Clear_COACH_ICO();

		break;
	case E_Quick_start_mode:

		LCD_Show_REP_ICO();
		LCD_Show_Line_up();

		LCD_Show_ABCD('A');
		LCD_Show_ABCD('B');
		LCD_Show_ABCD('C');
		LCD_Show_ABCD('D');

		LCD_Show_CAL_ICO();

		LCD_Clear_COACH_ICO();

		Repeat_Stop();
		Repeat_SetStart(LCD_Show_QS_ICO);
		Repeat_SetStop(LCD_Clear_QS_ICO);
		Repeat_Start(4, 4, 0);
		break;
	case E_Coach_mode:
		LCD_Show_REP_ICO();
		LCD_Show_Line_up();

		LCD_Show_ABCD('A');
		LCD_Show_ABCD('B');
		LCD_Show_ABCD('C');
		LCD_Show_ABCD('D');

		LCD_Show_CAL_ICO();

		LCD_Clear_QS_ICO();

		Repeat_Stop();
		Repeat_SetStart(LCD_Show_COACH_ICO);
		Repeat_SetStop(LCD_Clear_COACH_ICO);
		Repeat_Start(4, 4, 0);
		break;
	}
}

void app_flash_Show(void) {

	LCD_Show_Line_up();
	switch (level) {
	case 0:
		break;
	case 1:
		if (mode == E_Quick_start_mode) {
			LCD_Show_QS_ICO();
		} else if (mode == E_Coach_mode) {
			LCD_Show_COACH_ICO();
		}
		break;
	case 2:

		switch (letter) {
		case '\0':
			break;
		case 'A':
			LCD_Show_REP_Num(Rep_Pull_num['A' - 'A'][0]);
			LCD_Show_Pulls_Num(Rep_Pull_num['A' - 'A'][1]);
			break;
		case 'B':
			LCD_Show_REP_Num(Rep_Pull_num['B' - 'A'][0]);
			LCD_Show_Pulls_Num(Rep_Pull_num['B' - 'A'][1]);
			break;
		case 'C':
			LCD_Show_REP_Num(Rep_Pull_num['C' - 'A'][0]);
			LCD_Show_Pulls_Num(Rep_Pull_num['C' - 'A'][1]);
			break;
		case 'D':
			LCD_Show_REP_Num(Rep_Pull_num['D' - 'A'][0]);
			LCD_Show_Pulls_Num(Rep_Pull_num['D' - 'A'][1]);
			break;
		}
		if (mode == E_Quick_start_mode) {
			LCD_Show_QS_ICO();
		} else if (mode == E_Coach_mode) {
			LCD_Show_COACH_ICO();
		}
		LCD_Show_ABCD_all();

		break;
	case 3:
		break;
	}
	LCD_Show_Line_up();
}
void app_flash_Clear(void) {

	switch (level) {
	case 0:
		break;
	case 1:
//		LCD_Clear_ABCD();
//		if (mode == E_Quick_start_mode) {
//			LCD_Clear_QS_ICO();
//		} else if (mode == E_Coach_mode) {
//			LCD_Clear_COACH_ICO();
//		}

		LCD_Clear_QS_ICO();
		LCD_Clear_COACH_ICO();
		break;
	case 2:

		if (letter == '\0') {
			LCD_Clear_ABCD();
		}
		if (letter == 'A') {
			LCD_Clear_ABCD();
			LCD_Show_ABCD('A');
		}
		if (letter == 'B') {
			LCD_Clear_ABCD();
			LCD_Show_ABCD('B');
		}
		if (letter == 'C') {
			LCD_Clear_ABCD();
			LCD_Show_ABCD('C');
		}
		if (letter == 'D') {
			LCD_Clear_ABCD();
			LCD_Show_ABCD('D');
		}
		if (mode == E_Quick_start_mode) {
			LCD_Clear_QS_ICO();
		} else if (mode == E_Coach_mode) {
			LCD_Clear_COACH_ICO();
		}
		break;
	case 3:
		break;
	}

}
void app_key_power_or_return(void) {

	switch (level) {
	case 0:
		switch (mode) {
		case E_Simple_metering_mode:
			g_tWork.sum = 0;
			g_tWork.cal_num = 0;

			LCD_Show_Pulls_Num(g_tWork.sum);
			LCD_Show_CAL_Num(g_tWork.cal_num);

			LCD_Show_Line_up();
			LCD_Clear_REP_ICO();

			LCD_Clear_ABCD();

			LCD_Show_CAL_ICO();
			LCD_Clear_QS_ICO();
			LCD_Clear_COACH_ICO();

			break;
		case E_Quick_start_mode:
			g_tWork.sum = 0;
			g_tWork.cal_num = 0;

			LCD_Show_REP_Num(0);
			LCD_Show_Pulls_Num(0);
			LCD_Show_CAL_Num(0);

			LCD_Show_Line_up();
			LCD_Show_REP_ICO();

			LCD_Show_ABCD(g_tWork.reps_mode);

			LCD_Show_CAL_ICO();
			LCD_Show_QS_ICO();
			LCD_Clear_COACH_ICO();
			break;
		case E_Coach_mode:
			g_tWork.sum = 0;
			g_tWork.cal_num = 0;

			LCD_Show_REP_Num(0);
			LCD_Show_Pulls_Num(0);
			LCD_Show_CAL_Num(0);

			LCD_Show_Line_up();
			LCD_Show_REP_ICO();

			LCD_Show_ABCD(g_tWork.reps_mode);

			LCD_Show_CAL_ICO();
			LCD_Clear_QS_ICO();
			LCD_Show_COACH_ICO();

			break;
		}
		break;
	case 1:
		Repeat_Stop();
		if (level) {
			level--;
		}

		break;
	case 2:
		if (level) {
			level--;
		}
		break;
	case 3:
		if (level) {
			level--;
		}
		break;
	}

}
void app_key_set(void) {
//	static BIT power_on_mode_flag = 0;

	switch (level) {
	case 0:

		switch (g_tWork.mode) {
		case E_Simple_metering_mode:
			//g_tWork.mode = E_Quick_start_mode;
			//mode = E_Quick_start_mode;
			level = 1;
			break;
		case E_Quick_start_mode:

			break;
		case E_Coach_mode:

			break;
		}

		LCD_Show_REP_Num(0);
		LCD_Show_Pulls_Num(0);
		LCD_Show_CAL_Num(0);

		LCD_Show_Line_up();
		LCD_Show_REP_ICO();

		LCD_Show_ABCD_all();

		LCD_Show_CAL_ICO();

		mode = g_tWork.mode;
		mode = E_Quick_start_mode;
		level = 1;
		Repeat_Stop();
		Repeat_SetStart(app_flash_Show);
		Repeat_SetStop(app_flash_Clear);
		Repeat_Start(BLINK_FLASH_TIME, BLINK_FLASH_TIME, 0);
		break;
	case 1:
//		level = 2;

		break;
	case 2:
		break;
	case 3:
		break;
	}

//	app_UI_init();
}

void app_key_add(void) {

	switch (level) {
	case 0:

		break;
	case 1:
		switch (mode) {
		case E_Simple_metering_mode:
			mode = E_Quick_start_mode;

			break;
		case E_Quick_start_mode:
			mode = E_Coach_mode;

			break;
		case E_Coach_mode:

			mode = E_Simple_metering_mode;

			break;
		}
		break;
	case 2:
		switch (mode) {
		case E_Simple_metering_mode:

			break;
		case E_Quick_start_mode:

			if (letter == '\0') {
				letter = 'A';
			} else {
				letter++;
				if (letter > 'D') {
					letter = 'A';
				}
			}

			break;
		case E_Coach_mode:
			if (letter == '\0') {
				letter = 'A';
			} else {
				letter++;
				if (letter > 'D') {
					letter = 'A';
				}
			}
			break;
		}
		break;
	case 3:
		break;
	}

}
void app_key_ok(void) {
	//g_tWork.mode = mode;

	switch (level) {
	case 0:

		break;
	case 1:

		switch (mode) {
		case E_Simple_metering_mode:

			break;
		case E_Quick_start_mode:

			LCD_Show_QS_ICO();
			LCD_Clear_COACH_ICO();

			break;
		case E_Coach_mode:
			LCD_Clear_QS_ICO();
			LCD_Show_COACH_ICO();

			break;
		}
		letter = 'A';
		level = 2;
		break;
	case 2:
		switch (mode) {
		case E_Simple_metering_mode:

			break;
		case E_Quick_start_mode:

			Repeat_Stop();
			LCD_Show_QS_ICO();
			LCD_Clear_COACH_ICO();

			break;
		case E_Coach_mode:

			break;
		}
		g_tWork.mode = mode;
		g_tWork.reps_mode = letter;
		g_tWork.sum = 0;
		level = 0;
		break;
	case 3:
		break;
	}

//	level++;
//	if (level >= 3) {
//		level = 0;
//	}
}

void app_power_on(void) {
	SW_Reset();  //复位
}
void app_power_off(void) {
	lcd_bright_off();
	LCD_Clear_All();
}

static uint8_t noOps_timeoutCnt = 0;
static BIT offBight_flag = 0;
//static BIT keyInvalid_flag = 0;
void app_key_100ms_pro(void) {
	static uint8_t cnt = 0;

	if (g_tDevice.status == E_PowerDown) {
		cnt++;
		if (cnt >= 3) {
			cnt = 0;

			app_key_clear_noOps_timeoutCnt();
//			keyInvalid_flag = 1;
			set_PD;
		}
	} else {
		cnt = 0;
	}
}

void app_key_1s_pro(void) {

	noOps_timeoutCnt++;
	if (noOps_timeoutCnt == 10) {
		offBight_flag = 1;
//		keyInvalid_flag = 1;
		lcd_bright_off();
		printf("off bright\n");
	} else if (noOps_timeoutCnt == 20) {
		app_power_off();
		printf("power off\n");
		g_tDevice.status = E_PowerDown;
	}

}
void app_key_clear_noOps_timeoutCnt(void) {
	noOps_timeoutCnt = 0;
}
void app_key_pro(uint8_t keyCode) {

	app_key_clear_noOps_timeoutCnt();

	if (offBight_flag && (g_tDevice.status == E_PowerOn)) {
		offBight_flag = 0;
		lcd_bright_on();
		//	keyInvalid_flag = 1;
		return;
	}

	switch (keyCode) {
	case KEY_UP_K1:

		if (g_tDevice.status == E_PowerReady) {
			app_power_off();
			printf("power off\n");
			g_tDevice.status = E_PowerDown;
		}

		break;
	case KEY_DOWN_K1:
		BEEP_KeyTone();
		if (g_tDevice.status == E_PowerOn) {
			app_key_power_or_return();
		}

		break;
	case KEY_LONG_K1:
		BEEP_KeyTone();
		if (g_tDevice.status == E_PowerOn) {
			g_tDevice.status = E_PowerDown;
			app_power_off();
		} else if (g_tDevice.status == E_PowerDown) {
			g_tDevice.status = E_PowerOn;
			app_power_on();
		} else if (g_tDevice.status == E_PowerReady) {
			g_tDevice.status = E_PowerOn;
			app_power_on();
		}

		break;
	case KEY_UP_K2:

		break;
	case KEY_DOWN_K2:
		BEEP_KeyTone();
		app_key_set();
		break;
	case KEY_LONG_K2:

		break;
	case KEY_UP_K3:

		break;
	case KEY_DOWN_K3:
		BEEP_KeyTone();
		app_key_add();
		break;
	case KEY_LONG_K3:

		break;
	case KEY_UP_K4:

		break;
	case KEY_DOWN_K4:
		BEEP_KeyTone();
		app_key_ok();
		break;
	case KEY_LONG_K4:

		break;
#if DEBUG_KEY
	case KEY_UP_K5:

		break;
	case KEY_DOWN_K5:
		//BEEP_KeyTone();
		query_work_sum();
		break;
	case KEY_LONG_K5:

		break;
#endif
	case KEY_UP_K1K3:

		break;
	case KEY_DOWN_K1K3:

		break;
	case KEY_LONG_K1K3:

		break;
	default:
//		BEEP_KeyTone();
		break;

	}
}

