/*
 * app_key.c
 *
 *  Created on: 2017年7月7日
 *      Author: admin
 */

#include "app.h"

static uint8_t press_long_lock = 0;

//static idata uint8_t buf[PAYLOAD_WIDTH] = {0};
#if 0
void app_key_init(void) {

}

void app_power_on(void) {
	SW_Reset();  //复位
}
void app_power_off(void) {
//	lcd_bright_off();
	LCD_Clear_All();
}
#endif

void app_key_pro(uint8_t keyCode) {

	uint8_t index = 0;
	uint8_t i = 0;

	index = 0;
	memset(sendBuf, 0, PAYLOAD_WIDTH);
	switch (keyCode) {
	case KEY_UP_K1:   // power short
		if (press_long_lock == 0) {
			sendBuf[index++] = LCD2LAMP_HEADER;
			sendBuf[index++] = 0x01;
			sendBuf[index++] = KEY_CARD_POWER_CMD;
			for (i = 0; i < (sendBuf[1] + 1); i++) {
				sendBuf[index] += sendBuf[i + 1];
			}
		}
		press_long_lock = 0;
		break;
	case KEY_DOWN_K1:

		break;
	case KEY_LONG_K1:   //power long
		press_long_lock = 1;
		sendBuf[index++] = LCD2LAMP_HEADER;
		sendBuf[index++] = 0x01;
		sendBuf[index++] = KEY_POWER_SHORT_CMD;
		for (i = 0; i < (sendBuf[1] + 1); i++) {
			sendBuf[index] += sendBuf[i + 1];
		}
		break;
	case KEY_UP_K2:   //play/pause

		break;
	case KEY_DOWN_K2:
		sendBuf[index++] = LCD2LAMP_HEADER;
		sendBuf[index++] = 0x01;
		sendBuf[index++] = KEY_PLAY_SHORT_CMD;
		for (i = 0; i < (sendBuf[1] + 1); i++) {
			sendBuf[index] += sendBuf[i + 1];
		}
		break;
	case KEY_LONG_K2:
		sendBuf[index++] = LCD2LAMP_HEADER;
		sendBuf[index++] = 0x01;
		sendBuf[index++] = KEY_PLAY_LONG_CMD;
		for (i = 0; i < (sendBuf[1] + 1); i++) {
			sendBuf[index] += sendBuf[i + 1];
		}
		break;
	case KEY_UP_K3:   // down

		break;
	case KEY_DOWN_K3:
		sendBuf[index++] = LCD2LAMP_HEADER;
		sendBuf[index++] = 0x01;
		sendBuf[index++] = KEY_DOWN_CMD;
		for (i = 0; i < (sendBuf[1] + 1); i++) {
			sendBuf[index] += sendBuf[i + 1];
		}
		break;
	case KEY_LONG_K3:
		sendBuf[index++] = LCD2LAMP_HEADER;
		sendBuf[index++] = 0x01;
		sendBuf[index++] = KEY_DOWN_CMD;
		for (i = 0; i < (sendBuf[1] + 1); i++) {
			sendBuf[index] += sendBuf[i + 1];
		}
		break;
	case KEY_UP_K4:   // up

		break;
	case KEY_DOWN_K4:  // 连发
		sendBuf[index++] = LCD2LAMP_HEADER;
		sendBuf[index++] = 0x01;
		sendBuf[index++] = KEY_UP_CMD;
		for (i = 0; i < (sendBuf[1] + 1); i++) {
			sendBuf[index] += sendBuf[i + 1];
		}
		break;
	case KEY_LONG_K4:
		sendBuf[index++] = LCD2LAMP_HEADER;
		sendBuf[index++] = 0x01;
		sendBuf[index++] = KEY_UP_CMD;
		for (i = 0; i < (sendBuf[1] + 1); i++) {
			sendBuf[index] += sendBuf[i + 1];
		}
		break;
	case KEY_UP_K5:   //vol+

		break;
	case KEY_DOWN_K5:
		sendBuf[index++] = LCD2LAMP_HEADER;
		sendBuf[index++] = 0x01;
		sendBuf[index++] = KEY_VOL_ADD_CMD;
		for (i = 0; i < (sendBuf[1] + 1); i++) {
			sendBuf[index] += sendBuf[i + 1];
		}
		break;
	case KEY_LONG_K5:
		sendBuf[index++] = LCD2LAMP_HEADER;
		sendBuf[index++] = 0x01;
		sendBuf[index++] = KEY_VOL_ADD_CMD;
		for (i = 0; i < (sendBuf[1] + 1); i++) {
			sendBuf[index] += sendBuf[i + 1];
		}
		break;
	case KEY_UP_K6:   //ACC  继电器

		break;
	case KEY_DOWN_K6:
		sendBuf[index++] = LCD2LAMP_HEADER;
		sendBuf[index++] = 0x02;
		sendBuf[index++] = KEY_ACC_CMD;
		sendBuf[index++] = 0x03;
		for (i = 0; i < (sendBuf[1] + 1); i++) {
			sendBuf[index] += sendBuf[i + 1];
		}
		break;
	case KEY_LONG_K6:

		break;
	case KEY_UP_K7:   // vol-

		break;
	case KEY_DOWN_K7:
		sendBuf[index++] = LCD2LAMP_HEADER;
		sendBuf[index++] = 0x01;
		sendBuf[index++] = KEY_VOL_MINUS_CMD;
		for (i = 0; i < (sendBuf[1] + 1); i++) {
			sendBuf[index] += sendBuf[i + 1];
		}
		break;
	case KEY_LONG_K7:
		sendBuf[index++] = LCD2LAMP_HEADER;
		sendBuf[index++] = 0x01;
		sendBuf[index++] = KEY_VOL_MINUS_CMD;
		for (i = 0; i < (sendBuf[1] + 1); i++) {
			sendBuf[index] += sendBuf[i + 1];
		}
		break;
	case KEY_UP_K8:   // mode
		sendBuf[index++] = LCD2LAMP_HEADER;
		sendBuf[index++] = 0x01;
		sendBuf[index++] = KEY_MODE_CMD;
		for (i = 0; i < (sendBuf[1] + 1); i++) {
			sendBuf[index] += sendBuf[i + 1];
		}
		break;
	case KEY_DOWN_K8:

		break;
	case KEY_LONG_K8:

		break;
	case KEY_UP_K9:   // dome
		sendBuf[index++] = LCD2LAMP_HEADER;
		sendBuf[index++] = 0x01;
		sendBuf[index++] = KEY_DOME_CMD;
		for (i = 0; i < (sendBuf[1] + 1); i++) {
			sendBuf[index] += sendBuf[i + 1];
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
		app_2d4_send(sendBuf, index);
	}

}

