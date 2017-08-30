/*
 * app_2d4.c
 *
 *  Created on: 2017年8月16日
 *      Author: fly
 */

#include "app.h"

static uint8_t sendRcv_flag = 0; //0 rcv， 1 send
static uint8_t rcvBuf[PAYLOAD_WIDTH] = { 0 };
static uint8_t sendBuf[PAYLOAD_WIDTH] = { 0 };

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

static void repeat_demo_start(void) {
	LCD_ShowString("RELAY ON");

}
static void repeat_demo_stop(void) {
	LCD_ShowString("RELAYOFF");

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

		break;
	case ACC_CMD:

		Repeat_SetStart(repeat_demo_start);
		Repeat_SetStop(repeat_demo_stop);

		Repeat_Start(10, 10, 5);

		break;
	case UP_CMD:

		break;
	case DOWN_CMD:

		break;
	case DOME_CMD:
		break;
	case VOL_ADD_CMD:

		break;
	case VOL_MINUS_CMD:

		break;
	case PLAY_CMD:

		break;
	case MODE_CMD:

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


			app_2d4_Rcv(rcvBuf);
		}

	}

}
