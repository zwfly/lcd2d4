/*
 * app_key.c
 *
 *  Created on: 2017年7月7日
 *      Author: admin
 */

#include "app.h"

static idata uint8_t buf[PAYLOAD_WIDTH] = {0};

void app_key_init(void) {

}

void app_power_on(void) {
	SW_Reset();  //复位
}
void app_power_off(void) {
	lcd_bright_off();
	LCD_Clear_All();
}

void app_key_100ms_pro(void) {

}

void app_key_1s_pro(void) {

}
void app_key_clear_noOps_timeoutCnt(void) {
}

void app_key_pro(uint8_t keyCode) {
	uint8_t index = 0;
	uint8_t i = 0;

	app_key_clear_noOps_timeoutCnt();

//	key_bright_toggle();

	index = 0;
	memset(buf, 0, sizeof(buf));
	switch (keyCode) {
	case KEY_UP_K1:   // power short
		buf[index++] = LCD2LAMP_HEADER;
		buf[index++] = 0x02;
		buf[index++] = POWER_SHORT_CMD;
		buf[index++] = 0x03;
		for (i = 0; i < (buf[1] + 1); i++) {
			buf[index] += buf[i + 1];
		}

		break;
	case KEY_DOWN_K1:

		break;
	case KEY_LONG_K1:   //power long
		buf[index++] = LCD2LAMP_HEADER;
		buf[index++] = 0x02;
		buf[index++] = POWER_LONG_CMD;
		buf[index++] = 0x03;
		for (i = 0; i < (buf[1] + 1); i++) {
			buf[index] += buf[i + 1];
		}

		break;
	case KEY_UP_K2:   //play/pause
		buf[index++] = LCD2LAMP_HEADER;
		buf[index++] = 0x02;
		buf[index++] = PLAY_CMD;
		buf[index++] = 0x03;
		for (i = 0; i < (buf[1] + 1); i++) {
			buf[index] += buf[i + 1];
		}

		break;
	case KEY_DOWN_K2:

		break;
	case KEY_LONG_K2:

		break;
	case KEY_UP_K3:   // down
		buf[index++] = LCD2LAMP_HEADER;
		buf[index++] = 0x02;
		buf[index++] = DOWN_CMD;
		buf[index++] = 0x01;
		for (i = 0; i < (buf[1] + 1); i++) {
			buf[index] += buf[i + 1];
		}
		break;
	case KEY_DOWN_K3:

		break;
	case KEY_LONG_K3:

		break;
	case KEY_UP_K4:   // up
		buf[index++] = LCD2LAMP_HEADER;
		buf[index++] = 0x02;
		buf[index++] = UP_CMD;
		buf[index++] = 0x01;
		for (i = 0; i < (buf[1] + 1); i++) {
			buf[index] += buf[i + 1];
		}
		break;
	case KEY_DOWN_K4:

		break;
	case KEY_LONG_K4:

		break;
	case KEY_UP_K5:   //vol+
		buf[index++] = LCD2LAMP_HEADER;
		buf[index++] = 0x02;
		buf[index++] = VOL_ADD_CMD;
		buf[index++] = 0x01;
		for (i = 0; i < (buf[1] + 1); i++) {
			buf[index] += buf[i + 1];
		}

		break;
	case KEY_DOWN_K5:

		break;
	case KEY_LONG_K5:

		break;
	case KEY_UP_K6:   //ACC  继电器

		buf[index++] = LCD2LAMP_HEADER;
		buf[index++] = 0x02;
		buf[index++] = ACC_CMD;
		buf[index++] = 0x03;
		for (i = 0; i < (buf[1] + 1); i++) {
			buf[index] += buf[i + 1];
		}

		break;
	case KEY_DOWN_K6:

		break;
	case KEY_LONG_K6:

		break;
	case KEY_UP_K7:   // vol-
		buf[index++] = LCD2LAMP_HEADER;
		buf[index++] = 0x02;
		buf[index++] = VOL_MINUS_CMD;
		buf[index++] = 0x02;
		for (i = 0; i < (buf[1] + 1); i++) {
			buf[index] += buf[i + 1];
		}

		break;
	case KEY_DOWN_K7:

		break;
	case KEY_LONG_K7:

		break;
	case KEY_UP_K8:   // mode

		buf[index++] = LCD2LAMP_HEADER;
		buf[index++] = 0x02;
		buf[index++] = MODE_CMD;
		buf[index++] = 0x01;
		for (i = 0; i < (buf[1] + 1); i++) {
			buf[index] += buf[i + 1];
		}

		break;
	case KEY_DOWN_K8:

		break;
	case KEY_LONG_K8:

		break;
	case KEY_UP_K9:   // dome
		buf[index++] = LCD2LAMP_HEADER;
		buf[index++] = 0x02;
		buf[index++] = DOME_CMD;
		buf[index++] = 0x01;
		for (i = 0; i < (buf[1] + 1); i++) {
			buf[index] += buf[i + 1];
		}

		break;
	case KEY_DOWN_K9:

		break;
	case KEY_LONG_K9:

		break;
	case KEY_UP_K_1AND6:    //power ACC

		break;
	case KEY_DOWN_K_1AND6:

		break;
	case KEY_LONG_K_1AND6:

		break;
	default:

		break;

	}
	if (index) {
		index++;
		app_2d4_send(buf, index);
	}

}

