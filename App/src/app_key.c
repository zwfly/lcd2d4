/*
 * app_key.c
 *
 *  Created on: 2017年7月7日
 *      Author: admin
 */

#include "app.h"

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
		sendBuf[index++] = LCD2LAMP_HEADER;
		sendBuf[index++] = 0x02;
		sendBuf[index++] = POWER_SHORT_CMD;
		sendBuf[index++] = 0x03;
		for (i = 0; i < (sendBuf[1] + 1); i++) {
			sendBuf[index] += sendBuf[i + 1];
		}

		break;
	case KEY_DOWN_K1:

		break;
	case KEY_LONG_K1:   //power long
		sendBuf[index++] = LCD2LAMP_HEADER;
		sendBuf[index++] = 0x02;
		sendBuf[index++] = POWER_LONG_CMD;
		sendBuf[index++] = 0x03;
		for (i = 0; i < (sendBuf[1] + 1); i++) {
			sendBuf[index] += sendBuf[i + 1];
		}

		break;
	case KEY_UP_K2:   //play/pause
		sendBuf[index++] = LCD2LAMP_HEADER;
		sendBuf[index++] = 0x02;
		sendBuf[index++] = PLAY_CMD;
		sendBuf[index++] = 0x03;
		for (i = 0; i < (sendBuf[1] + 1); i++) {
			sendBuf[index] += sendBuf[i + 1];
		}

		break;
	case KEY_DOWN_K2:

		break;
	case KEY_LONG_K2:

		break;
	case KEY_UP_K3:   // down

		break;
	case KEY_DOWN_K3:
		sendBuf[index++] = LCD2LAMP_HEADER;
		sendBuf[index++] = 0x02;
		sendBuf[index++] = DOWN_CMD;
		sendBuf[index++] = 0x01;
		for (i = 0; i < (sendBuf[1] + 1); i++) {
			sendBuf[index] += sendBuf[i + 1];
		}
		break;
	case KEY_LONG_K3:

		break;
	case KEY_UP_K4:   // up

		break;
	case KEY_DOWN_K4:  // 连发
		sendBuf[index++] = LCD2LAMP_HEADER;
		sendBuf[index++] = 0x02;
		sendBuf[index++] = UP_CMD;
		sendBuf[index++] = 0x01;
		for (i = 0; i < (sendBuf[1] + 1); i++) {
			sendBuf[index] += sendBuf[i + 1];
		}
		break;
	case KEY_LONG_K4:

		break;
	case KEY_UP_K5:   //vol+
		sendBuf[index++] = LCD2LAMP_HEADER;
		sendBuf[index++] = 0x02;
		sendBuf[index++] = VOL_ADD_CMD;
		sendBuf[index++] = 0x01;
		for (i = 0; i < (sendBuf[1] + 1); i++) {
			sendBuf[index] += sendBuf[i + 1];
		}

		break;
	case KEY_DOWN_K5:

		break;
	case KEY_LONG_K5:

		break;
	case KEY_UP_K6:   //ACC  继电器

		sendBuf[index++] = LCD2LAMP_HEADER;
		sendBuf[index++] = 0x02;
		sendBuf[index++] = ACC_CMD;
		sendBuf[index++] = 0x03;
		for (i = 0; i < (sendBuf[1] + 1); i++) {
			sendBuf[index] += sendBuf[i + 1];
		}

		break;
	case KEY_DOWN_K6:

		break;
	case KEY_LONG_K6:

		break;
	case KEY_UP_K7:   // vol-
		sendBuf[index++] = LCD2LAMP_HEADER;
		sendBuf[index++] = 0x02;
		sendBuf[index++] = VOL_MINUS_CMD;
		sendBuf[index++] = 0x02;
		for (i = 0; i < (sendBuf[1] + 1); i++) {
			sendBuf[index] += sendBuf[i + 1];
		}

		break;
	case KEY_DOWN_K7:

		break;
	case KEY_LONG_K7:

		break;
	case KEY_UP_K8:   // mode

		sendBuf[index++] = LCD2LAMP_HEADER;
		sendBuf[index++] = 0x02;
		sendBuf[index++] = MODE_CMD;
		sendBuf[index++] = 0x01;
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
		sendBuf[index++] = 0x02;
		sendBuf[index++] = DOME_CMD;
		sendBuf[index++] = 0x01;
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

