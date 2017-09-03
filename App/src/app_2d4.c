/*
 * app_2d4.c
 *
 *  Created on: 2017��8��16��
 *      Author: fly
 */

#include "app.h"

static idata uint8_t sendRcv_flag = 0; //0 rcv�� 1 send
static idata uint8_t rcvBuf[PAYLOAD_WIDTH] = {0};
static idata uint8_t sendBuf[PAYLOAD_WIDTH] = {0};

void app_2d4_init(void) {

	sendRcv_flag = 0;
	memset(rcvBuf, 0, PAYLOAD_WIDTH);
	memset(sendBuf, 0, PAYLOAD_WIDTH);

	RF_Init();
	RF_RxMode();

//	RF_Carrier(1);
}

void app_2d4_send(uint8_t *d, uint8_t len) {

	if (len > PAYLOAD_WIDTH) {
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
static void clear_lcd_resp(void) {
	LCD_ShowString("        ");

	LCD_Clear_upColon_ICO();
	LCD_Clear_downColon_ICO();
}
static void BT_pause_show_lcd_resp(void) {
	LCD_ShowString("   PAUSE");
}

static void BT_play_show_lcd_resp(void) {
	LCD_ShowString("    PLAY");
}
static void FM_scanning_show_lcd_resp(void) {
	LCD_ShowString("SCANNING");
	LCD_Clear_upColon_ICO();
	LCD_Clear_downColon_ICO();
	LCD_Clear_MHZ_ICO();
}

static void FM_ok_show_lcd_resp(void) {
	LCD_ShowString("FM 1027 ");
	LCD_Clear_upColon_ICO();
	LCD_Show_downColon_ICO();
	LCD_Show_MHZ_ICO();

}
static void AUX_mute_show_lcd_resp(void) {
	LCD_ShowString("   MUTE ");
}

static void AUX_play_show_lcd_resp(void) {
	LCD_ShowString("    PLAY");

}
static void USB_pause_show_lcd_resp(void) {
	LCD_ShowString("   PAUSE");
	LCD_Clear_upColon_ICO();
	LCD_Clear_downColon_ICO();
}

static void USB_time_show_lcd_resp(void) {
	LCD_ShowString("     349");
	LCD_Show_upColon_ICO();
	LCD_Show_downColon_ICO();
}
static void app_2d4_Rcv(uint8_t *buf) {
	uint8_t i = 0;
	uint8_t index = 0;
	uint8_t check = 0;

	if (buf[0] != LAMP2LCD_HEADER) {
		return;
	}	key_bright_toggle();
	if (buf[1] > PAYLOAD_WIDTH) {
		return;
	}
	for (i = 0; i < (buf[1] + 1); i++) {
		check += buf[i + 1];
	}
	if (check != buf[buf[1] + 2]) {
		return;
	}


	memset(sendBuf, 0, PAYLOAD_WIDTH);
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

		g_tWork.mode = (char) buf[3];

		switch (g_tWork.mode) {
		case 'B':
			g_tWork.status.bits.BT = buf[4];
			if (g_tWork.status.bits.BT) {
				Repeat_SetStart(BT_play_show_lcd_resp);
				Repeat_SetStop(0);
				Repeat_Start(20, 1, 1);
			} else {
				Repeat_SetStart(BT_pause_show_lcd_resp);
				Repeat_SetStop(clear_lcd_resp);
				Repeat_Start(10, 10, 0);
			}
			break;
		case 'F':
			g_tWork.status.bits.FM = buf[4];
			if (g_tWork.status.bits.FM) {
				Repeat_SetStart(FM_scanning_show_lcd_resp);
				Repeat_SetStop(0);
				Repeat_Start(20, 1, 0);
			} else {
				Repeat_SetStart(FM_ok_show_lcd_resp);
				Repeat_SetStop(0);
				Repeat_Start(10, 1, 1);
			}
			break;
		case 'A':
			g_tWork.status.bits.AUX = buf[4];
			if (g_tWork.status.bits.AUX) {
				Repeat_SetStart(AUX_play_show_lcd_resp);
				Repeat_SetStop(clear_lcd_resp);
				Repeat_Start(10, 10, 0);
			} else {
				Repeat_SetStart(AUX_mute_show_lcd_resp);
				Repeat_SetStop(clear_lcd_resp);
				Repeat_Start(10, 10, 0);
			}

			break;
		case 'U':
			g_tWork.status.bits.USB = buf[4];
			if (g_tWork.status.bits.USB) {
				Repeat_SetStart(USB_time_show_lcd_resp);
				Repeat_SetStop(0);
				Repeat_Start(10, 1, 1);
			} else {
				Repeat_SetStart(USB_pause_show_lcd_resp);
				Repeat_SetStop(clear_lcd_resp);
				Repeat_Start(10, 10, 0);
			}
			break;
		}

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
		case TX_DS_FLAG: 		// ��ͨ�ͷ������ �� ��ǿ�ͷ��ͳɹ�

			RF_ClearFIFO();
			RF_ClearStatus();

			sendRcv_flag = 0;
			RF_RxMode();

//			key_bright_toggle();

			break;
		case RX_DR_FLAG:		//���ͳɹ����յ�payload

			RF_ClearFIFO();
			RF_ClearStatus();
			break;
		case MAX_RT_FLAG:		// ��ǿ�ͷ��ͳ�ʱʧ��

			RF_ClearFIFO();
			RF_ClearStatus();
			break;
		default:		// rf ���ڿ���״̬�ŷ�������

			RF_TxData(sendBuf, PAYLOAD_WIDTH);

			break;
		}

	} else {
		if (ucRF_DumpRxData(rcvBuf, PAYLOAD_WIDTH)) {



			LCD_Clear_MHZ_ICO();
			LCD_Clear_upColon_ICO();
			LCD_Clear_downColon_ICO();

			app_2d4_Rcv(rcvBuf);
		}

	}

}

void app_2d4_1S_pro(void) {

	switch (g_tWork.mode) {
	case 'B':

		app_lcd_default_string_set(" PAIRING", 8);
		LCD_Clear_MHZ_ICO();

		LCD_Clear_upColon_ICO();
		LCD_Clear_downColon_ICO();

		break;
	case 'F':
		app_lcd_default_string_set("FM  821 ", 8);
		LCD_Clear_upColon_ICO();
		LCD_Show_downColon_ICO();

		LCD_Show_MHZ_ICO();
		break;
	case 'A':
		app_lcd_default_string_set("    PLAY", 8);
		LCD_Clear_MHZ_ICO();
		LCD_Clear_upColon_ICO();
		LCD_Clear_downColon_ICO();
		break;
	case 'U':
		app_lcd_default_string_set("     349", 8);
		LCD_Show_upColon_ICO();
		LCD_Show_downColon_ICO();

		LCD_Clear_MHZ_ICO();
		break;
	}

}

