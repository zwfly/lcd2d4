/*
 * app_2d4.c
 *
 *  Created on: 2017年8月16日
 *      Author: fly
 */

#include "app.h"

static idata uint8_t sendRcv_flag = 0; //0 rcv， 1 send
static idata uint8_t rcvBuf[PAYLOAD_WIDTH] = { 0 };
static idata uint8_t sendBuf[PAYLOAD_WIDTH] = { 0 };

void app_2d4_init(void) {


	sendRcv_flag = 0;
	memset(rcvBuf, 0, sizeof(rcvBuf));
	memset(sendBuf, 0, sizeof(sendBuf));

	RF_Init();
	RF_RxMode();

//	RF_Carrier(1);

}

void app_2d4_send(uint8_t *d, uint8_t len) {

	if (len > sizeof(sendBuf)) {
		return;
	}

	RF_TxMode();
	sendRcv_flag = 1;

	if (sendBuf != d) {
		memcpy(sendBuf, d, len);
	}

}
static void speaker_status_resp(void) {
	if (g_tWork.status.bits.speaker) {
		LCD_ShowString(" BAZOOKA");
	} else {
		LCD_ShowString(" PWR OFF");
	}

}
static void relay_status_resp(void) {
	if (g_tWork.status.bits.relay) {
		LCD_ShowString("RELAY ON");
	} else {
		LCD_ShowString("RELAYOFF");
	}

}
static void vol_resp(void) {
	char str[16] = { 0 };

	sprintf(str, " VOL %u", (uint16_t) g_tWork.vol);
	LCD_ShowString(str);
}
static void mode_resp(void) {
	char str[16] = { 0 };

	switch (g_tWork.mode) {
	case 'B':
		g_tWork.mode = 'F';
		break;
	case 'F':
		g_tWork.mode = 'A';
		break;
	case 'A':
		g_tWork.mode = 'U';
		break;
	case 'U':
		g_tWork.mode = 'B';
		break;
	}

	sprintf(str, " VOL %u", (uint16_t) g_tWork.vol);
	LCD_ShowString(str);
}
static void app_2d4_Rcv(uint8_t *buf) {
	uint8_t i = 0;
	uint8_t index = 0;
	uint8_t check = 0;

	if (buf[0] != LAMP2LCD_HEADER) {
		return;
	}
	if (buf[1] > sizeof(rcvBuf)) {
		return;
	}
	for (i = 0; i < (buf[1] + 1); i++) {
		check += buf[i + 1];
	}
	if (check != buf[buf[1] + 2]) {
		return;
	}

	memset(sendBuf, 0, sizeof(sendBuf));
	index = 0;
	switch (buf[2]) {
	case POWER_SHORT_CMD:

		break;
	case POWER_LONG_CMD:

		if (buf[3]) {
			g_tWork.status.bits.speaker = 1;
			Repeat_SetStart(speaker_status_resp);
			Repeat_SetStop(0);

			Repeat_Start(20, 1, 1);
		} else {
			g_tWork.status.bits.speaker = 0;
			Repeat_SetStart(speaker_status_resp);
			Repeat_SetStop(0);

			Repeat_Start(20, 1, 0);
		}

		break;
	case ACC_CMD:

		if (buf[3] == 1) {
			g_tWork.status.bits.relay = 1;
		} else {
			g_tWork.status.bits.relay = 0;
		}

		Repeat_SetStart(relay_status_resp);
		Repeat_SetStop(0);

		Repeat_Start(20, 1, 1);

		break;
	case UP_CMD:

		break;
	case DOWN_CMD:

		break;
	case DOME_CMD:
		break;
	case VOL_ADD_CMD:
		g_tWork.vol = buf[3];

		Repeat_SetStart(vol_resp);
		Repeat_SetStop(0);

		Repeat_Start(20, 1, 1);
		break;
	case VOL_MINUS_CMD:
		g_tWork.vol = buf[3];

		Repeat_SetStart(vol_resp);
		Repeat_SetStop(0);

		Repeat_Start(20, 1, 1);
		break;
	case PLAY_CMD:

		break;
	case MODE_CMD:
		g_tWork.mode = (char) buf[3];

		switch (g_tWork.mode) {
		case 'B':
			LCD_Clear_FM_ICO();
//			LCD_Show_FM_ICO();
//			LCD_Clear_BLUETooTH_ICO();
			LCD_Show_BLUETooTH_ICO();
			LCD_Clear_AUX_ICO();
//			LCD_Show_AUX_ICO();
			LCD_Clear_USB_ICO();
//			LCD_Show_USB_ICO();
			break;
		case 'F':
//			LCD_Clear_FM_ICO();
			LCD_Show_FM_ICO();
			LCD_Clear_BLUETooTH_ICO();
//			LCD_Show_BLUETooTH_ICO();
			LCD_Clear_AUX_ICO();
//			LCD_Show_AUX_ICO();
			LCD_Clear_USB_ICO();
//			LCD_Show_USB_ICO();
			break;
		case 'A':
			LCD_Clear_FM_ICO();
//			LCD_Show_FM_ICO();
			LCD_Clear_BLUETooTH_ICO();
//			LCD_Show_BLUETooTH_ICO();
//			LCD_Clear_AUX_ICO();
			LCD_Show_AUX_ICO();
			LCD_Clear_USB_ICO();
//			LCD_Show_USB_ICO();
			break;
		case 'U':
			LCD_Clear_FM_ICO();
//			LCD_Show_FM_ICO();
			LCD_Clear_BLUETooTH_ICO();
//			LCD_Show_BLUETooTH_ICO();
			LCD_Clear_AUX_ICO();
//			LCD_Show_AUX_ICO();
//			LCD_Clear_USB_ICO();
			LCD_Show_USB_ICO();
			break;
		}
		break;
	}
	if (index) {
		index++;
//	app_2d4_send(buf, index);
	}

}

void app_2d4_pro(void) {
	if (sendRcv_flag) {

		switch (ucRF_GetStatus()) {
		case TX_DS_FLAG: 		// 普通型发送完成 或 增强型发送成功

			RF_ClearFIFO();
			RF_ClearStatus();

			sendRcv_flag = 0;
			RF_RxMode();

			key_bright_toggle();

			break;
		case RX_DR_FLAG:		//发送成功且收到payload

			RF_ClearFIFO();
			RF_ClearStatus();
			break;
		case MAX_RT_FLAG:		// 增强型发送超时失败

			RF_ClearFIFO();
			RF_ClearStatus();
			break;
		default:		// rf 处于空闲状态才发送数据

			RF_TxData(sendBuf, sizeof(sendBuf));

			break;
		}

	} else {
		if (ucRF_DumpRxData(rcvBuf, sizeof(rcvBuf))) {

//			key_bright_toggle();

			app_2d4_Rcv(rcvBuf);
		}

	}

}
