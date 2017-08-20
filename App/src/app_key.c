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

}

void app_flash_Show(void) {

}
void app_flash_Clear(void) {

}
void app_key_power_or_return(void) {

}
void app_key_set(void) {

}

void app_key_add(void) {

}
void app_key_ok(void) {

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

}

void app_key_1s_pro(void) {

}
void app_key_clear_noOps_timeoutCnt(void) {
	noOps_timeoutCnt = 0;
}

void app_key_pro(uint8_t keyCode) {

	app_key_clear_noOps_timeoutCnt();

	key_bright_toggle();

	switch (keyCode) {
	case KEY_UP_K1:

		break;
	case KEY_DOWN_K1:

		break;
	case KEY_LONG_K1:

		break;
	case KEY_UP_K2:

		break;
	case KEY_DOWN_K2:

		break;
	case KEY_LONG_K2:

		break;
	case KEY_UP_K3:

		break;
	case KEY_DOWN_K3:

		break;
	case KEY_LONG_K3:

		break;
	case KEY_UP_K4:

		break;
	case KEY_DOWN_K4:

		break;
	case KEY_LONG_K4:

		break;
	case KEY_UP_K5:

		break;
	case KEY_DOWN_K5:

		break;
	case KEY_LONG_K5:

		break;
	case KEY_UP_K6:

		break;
	case KEY_DOWN_K6:

		break;
	case KEY_LONG_K6:

		break;
	case KEY_UP_K7:

		break;
	case KEY_DOWN_K7:

		break;
	case KEY_LONG_K7:

		break;
	case KEY_UP_K8:

		break;
	case KEY_DOWN_K8:

		break;
	case KEY_LONG_K8:

		break;
	case KEY_UP_K9:

		break;
	case KEY_DOWN_K9:

		break;
	case KEY_LONG_K9:

		break;
	default:

		break;

	}
}

