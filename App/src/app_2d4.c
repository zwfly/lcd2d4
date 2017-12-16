/*
 * app_2d4.c
 *
 *  Created on: 2017年8月16日
 *      Author: fly
 */

#include "app.h"

#define BT_MODE     0x01
#define FM_MODE     0x02
#define USB_MODE    0x03
#define AUX_MODE    0x04
#define DOME_MODE   0x05
#define CALL_MODE   0x06

static idata uint8_t sendRcv_flag = 0; //0 rcv， 1 send
static idata uint8_t rcvBuf[PAYLOAD_WIDTH] = {0};
idata uint8_t sendBuf[PAYLOAD_WIDTH] = { 0 };

static char tmpBuf[16] = { 0 };

void app_2d4_init(void) {

	sendRcv_flag = 0;
	memset(rcvBuf, 0, PAYLOAD_WIDTH);
	memset(sendBuf, 0, PAYLOAD_WIDTH);

	RF_Init();
	RF_RxMode();

//	RF_Carrier(1);
}

void app_get_saved_address(uint8_t *addr) {
	uint8_t i = 0;
	for (i = 0; i < 5; i++) {
		*(addr + i) = app_eeprom_read_byte(WIRELESS_ADDRESS_START_ADDR + i);
	}
}
void app_2d4_switch_public_address(void) {
	memcpy(TX_ADDRESS_DEF, PUBLIC_ADDRESS_DEF, 5);

	sendRcv_flag = 0;
	memset(rcvBuf, 0, sizeof(rcvBuf));
	memset(sendBuf, 0, sizeof(sendBuf));

	RF_Init();
	RF_RxMode();
}
void app_2d4_switch_saved_address(void) {
	app_get_saved_address(TX_ADDRESS_DEF);
	app_2d4_init();
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
		LCD_ShowString("ACC ON");
	} else {
		LCD_ShowString("ACC OFF");
	}

}
static void vol_resp(void) {
	char str[16] = { 0 };

//	LCD_Clear_MHZ_ICO();
	LCD_Clear_upColon_ICO();
	LCD_Clear_downColon_ICO();

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
#if 0
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
#endif
static void AUX_mute_show_lcd_resp(void) {
	LCD_ShowString("   MUTE ");
}

static void USB_pause_show_lcd_resp(void) {
	LCD_ShowString("   PAUSE");
	LCD_Clear_upColon_ICO();
	LCD_Clear_downColon_ICO();
}
#if 0
static void USB_time_show_lcd_resp(void) {
	LCD_ShowString("     349");
	LCD_Show_upColon_ICO();
	LCD_Show_downColon_ICO();
}
#endif
static void BT_next_show_lcd_resp(void) {
	LCD_ShowString("   NEXT ");
	LCD_Clear_upColon_ICO();
	LCD_Clear_downColon_ICO();
}
static void BT_prev_show_lcd_resp(void) {
	LCD_ShowString("   PREV ");
	LCD_Clear_upColon_ICO();
	LCD_Clear_downColon_ICO();
}
static void FM_station_show_lcd_resp(void) {
	sprintf(tmpBuf, "    ST%u", (uint16_t) g_tWork.FM_station);
	LCD_ShowString(tmpBuf);
	LCD_Clear_MHZ_ICO();
	LCD_Clear_upColon_ICO();
	LCD_Show_downColon_ICO();
}
static void USB_track_show_lcd_resp(void) {
	sprintf(tmpBuf, "TR %u", g_tWork.track);
	LCD_ShowString(tmpBuf);
	LCD_Clear_upColon_ICO();
	LCD_Clear_downColon_ICO();
}
static void LED_show_blink_name_show_lcd_resp(void) {
//	sprintf(tmpBuf, "TR %u", g_tWork.track);
	LCD_ShowString(tmpBuf);
//	LCD_ShowString("PAUSE");
	LCD_Clear_upColon_ICO();
	LCD_Clear_downColon_ICO();
}
static void LED_clear_blink_name_show_lcd_resp(void) {
	//	sprintf(tmpBuf, "TR %u", g_tWork.track);
	LCD_ShowString("        ");
	LCD_Clear_upColon_ICO();
	LCD_Clear_downColon_ICO();
}

//static char testbuf[16] = { 0 };

static void app_2d4_Rcv(uint8_t *buf) {
	uint8_t i = 0;
	uint8_t index = 0;
	uint8_t check = 0;

	if (buf[0] != LAMP2LCD_HEADER) {
		return;
	}
//	key_bright_toggle();
	if (buf[1] > PAYLOAD_WIDTH) {
		return;
	}
	for (i = 0; i < (buf[1] + 1); i++) {
		check += buf[i + 1];
	}
	if (check != buf[buf[1] + 2]) {
		return;
	}

//		memset(testbuf, 0, 16);
//	sprintf(testbuf, "R%02X", (uint16_t)buf[2]);
//	app_lcd_default_string_set(testbuf, strlen(testbuf));

	memset(sendBuf, 0, PAYLOAD_WIDTH);
	index = 0;
	app_work_cnt_clear();
//	switch (0) {
	switch (buf[2]) {
	case WIRELESS_MATCH_CODE_CMD: {
		uint8_t eq = 0;
		idata uint8_t
		address_saved_tmp[5] = {0};
		idata uint8_t
		address_sended_tmp[5] = {0};

		memset(address_saved_tmp, 0, 5);
		memset(address_sended_tmp, 0, 5);

		app_get_saved_address(address_saved_tmp);
		memcpy(address_sended_tmp, buf + 3, 5);

		eq = 1;
		for (i = 0; i < 5; i++) {
			if (address_sended_tmp[i] != address_saved_tmp[i]) {
				eq = 0;
				break;
			}
		}
		if (eq == 0) {
			app_eeprom_erase(0);
			for (i = 0; i < 253; i++)
				;
			app_eeprom_write_buf(0, address_sended_tmp, 5);

//			app_lcd_default_string_set("EQ 0    ", 8, 0);

		} else {
//			app_lcd_default_string_set("EQ 1    ", 8, 0);
		}
		g_tWork.match_code_mode = 0;

		app_2d4_switch_saved_address();

		app_lcd_default_string_set("MATCH OK", 8, 0);
	}
		break;
	case LED_MODE_MSG_CMD: {
		//LED_MODE_MSG_ST led_mode_msg;
//		memset((uint8_t *) &led_mode_msg, 0, sizeof(LED_MODE_MSG_ST));

		LCD_Show_LED_ICO();

		LCD_Clear_MHZ_ICO();
		LCD_Clear_FM_ICO();
		LCD_Clear_USB_ICO();
		LCD_Clear_AUX_ICO();
		LCD_Clear_BLUETooTH_ICO();
		switch (buf[3]) { //蓝牙模块工作模式
		case BT_MODE:
			LCD_Show_BLUETooTH_ICO();
			break;
		case FM_MODE:
			LCD_Show_FM_ICO();
			break;
		case USB_MODE:
			LCD_Show_USB_ICO();
			break;
		case AUX_MODE:
			LCD_Show_AUX_ICO();
			break;
		case DOME_MODE:
			break;
		case CALL_MODE:
			break;
		}

		memset((uint8_t *) tmpBuf, 0, sizeof(tmpBuf));
		memcpy(tmpBuf, buf + 4, 8);
		app_lcd_default_string_set(tmpBuf, strlen(tmpBuf), 0);

		if (*(buf + 12)) {
			Repeat_SetStart(LED_show_blink_name_show_lcd_resp);
			Repeat_SetStop(LED_clear_blink_name_show_lcd_resp);
			if (0 == app_repeat_IsEnable()) {
				Repeat_Start(6, 6, 0);
			}
		} else {
			if (app_repeat_IsEnable()) {
				Repeat_Stop();
			}
		}

	}
		break;
	case RCV_POWER_STATUS_CMD:
		Repeat_Stop();

		LCD_Clear_downColon_ICO();
		LCD_Clear_upColon_ICO();

		LCD_Clear_MHZ_ICO();
		LCD_Clear_FM_ICO();
		LCD_Clear_USB_ICO();
		LCD_Clear_AUX_ICO();
		LCD_Clear_BLUETooTH_ICO();

		if (buf[3] == 0x01) {
			g_tWork.status.bits.speaker = 1;
			Repeat_SetStart(speaker_status_resp);
			Repeat_SetStop(0);
			Repeat_Start(80, 1, 1);
		} else if (buf[3] == 0x02) {
			g_tWork.status.bits.speaker = 0;
			Repeat_SetStart(speaker_status_resp);
			Repeat_SetStop(0);
			Repeat_Start(20, 1, 0);
		}
		break;
	case RCV_X_BOX_STATUS_CMD:
//		switch (buf[3]) {
//		case BT_MODE:
//
//			break;
//		case FM_MODE:
//
//			break;
//		case AUX_MODE:  //AUX
//
//			break;
//		case USB_MODE:  //USB
//
//			break;
//		case DOME_MODE:  //LED
//
//			break;
//		case CALL_MODE:
//			break;
//		}

		break;
	case RCV_BT_STATUS_CMD:
		switch (buf[3]) {
		case BT_MODE:
//			Repeat_Stop();
			if (g_tWork.mode != BT_MODE) {
				Repeat_Stop();
				g_tWork.mode = BT_MODE;
			}
			LCD_Clear_MHZ_ICO();
			LCD_Clear_FM_ICO();
			LCD_Clear_USB_ICO();
			LCD_Clear_AUX_ICO();

			LCD_Show_BLUETooTH_ICO();
			if (buf[4] == 0x01) {
				sprintf(tmpBuf, " PAIRING");
			} else if (buf[4] == 0x02) {
				sprintf(tmpBuf, "  PAIRED");
			} else if (buf[4] == 0x03) {
				sprintf(tmpBuf, "TWS SCAN");
			} else if (buf[4] == 0x04) {
				sprintf(tmpBuf, "  TWS OK");
			}
			app_lcd_default_string_set(tmpBuf, strlen(tmpBuf), 0);
			break;
		case FM_MODE:
			Repeat_Stop();
			LCD_Clear_All();

			sprintf(tmpBuf, "     %u%02u", (uint16_t) buf[3],
					(uint16_t) buf[4]);

//			app_lcd_default_string_set(tmpBuf, strlen(tmpBuf));

			break;
		case AUX_MODE:  //AUX

			break;
		case USB_MODE:  //USB

			break;
		case DOME_MODE:  //LED

			break;
		case CALL_MODE:
			break;
		}
		break;
	case RCV_PLAY_PAUSE_STATUS_CMD:
		switch (buf[3]) {
		case BT_MODE:
			if (1 == buf[4]) {
				Repeat_Stop();

//				Repeat_SetStart(BT_play_show_lcd_resp);
//				Repeat_SetStop(0);
//				Repeat_Start(20, 1, 1);

			} else if (2 == buf[4]) {
				Repeat_SetStart(BT_pause_show_lcd_resp);
				Repeat_SetStop(clear_lcd_resp);
				Repeat_Start(6, 6, 0);
			}
			break;
		case FM_MODE:
			if (2 == buf[4]) {
				sprintf(tmpBuf, "SCANNING");
				app_lcd_default_string_set(tmpBuf, strlen(tmpBuf), 0);
			} else if (1 == buf[4]) {
				//				Repeat_SetStart(FM_ok_show_lcd_resp);
				//				Repeat_SetStop(0);
				//				Repeat_Start(10, 1, 1);
			}
			break;
		case AUX_MODE:  //AUX
		{
			static BIT aux_pause_lock = 0;
			LCD_Clear_downColon_ICO();
			LCD_Clear_upColon_ICO();

			LCD_Clear_MHZ_ICO();
			LCD_Clear_FM_ICO();
			LCD_Clear_USB_ICO();
			LCD_Clear_AUX_ICO();
			LCD_Clear_BLUETooTH_ICO();

			LCD_Show_AUX_ICO();
			if (1 == buf[4]) {
				if (aux_pause_lock) {
					Repeat_Stop();
					aux_pause_lock = 0;
				}
				sprintf(tmpBuf, "    PLAY");
				app_lcd_default_string_set(tmpBuf, strlen(tmpBuf), 0);
			} else if (2 == buf[4]) {
				aux_pause_lock = 1;
				Repeat_SetStart(AUX_mute_show_lcd_resp);
				Repeat_SetStop(clear_lcd_resp);
				Repeat_Start(7, 7, 0);
			}
		}
			break;
		case USB_MODE:  //USB
			if (1 == buf[4]) {
				Repeat_Stop();
				//				Repeat_SetStart(USB_time_show_lcd_resp);
				//				Repeat_SetStop(0);
				//				Repeat_Start(10, 1, 1);
			} else if (2 == buf[4]) {
				Repeat_SetStart(USB_pause_show_lcd_resp);
				Repeat_SetStop(clear_lcd_resp);
				Repeat_Start(10, 10, 0);
			}
			break;
		case DOME_MODE:  //LED
			if (1 == buf[4]) { //pause
				memcpy(tmpBuf, buf + 5, 8);
				Repeat_SetStart(LED_show_blink_name_show_lcd_resp);
				Repeat_SetStop(LED_clear_blink_name_show_lcd_resp);
				Repeat_Start(6, 6, 0);

			} else {
				app_lcd_default_string_set(buf + 5, 8, 0);
//				Repeat_SetStart(LED_show_blink_name_show_lcd_resp);
//				Repeat_SetStop(0);
//				Repeat_Start(1, 1, 1);
			}
			break;
		case CALL_MODE:
			break;
		}
		break;
	case RCV_PREV_NEXT_CMD:
		switch (buf[3]) {
		case BT_MODE:  //BT
			if (buf[4] == 1) { //up
				Repeat_SetStart(BT_prev_show_lcd_resp);
				Repeat_SetStop(0);
				Repeat_Start(30, 1, 1);
			} else if (buf[4] == 2) { //down
				Repeat_SetStart(BT_next_show_lcd_resp);
				Repeat_SetStop(0);
				Repeat_Start(30, 1, 1);
			}
			break;
		case FM_MODE:  //FM
			Repeat_Stop();
			g_tWork.FM_station = buf[5];
			Repeat_SetStart(FM_station_show_lcd_resp);
			Repeat_SetStop(0);
			Repeat_Start(30, 1, 1);
			break;
		case AUX_MODE:  //AUX
			break;
		case USB_MODE:  //USB
			g_tWork.track = buf[6];
			g_tWork.track |= (buf[5] << 8);
			Repeat_SetStart(USB_track_show_lcd_resp);
			Repeat_SetStop(0);
			Repeat_Start(30, 1, 1);

			break;
		case DOME_MODE:  //LED
			app_lcd_default_string_set(buf + 4, 8, 0);
			break;
		case CALL_MODE:
			break;
		default:
			break;
		}
		break;
	case RCV_USB_PLAY_TIME_CMD:
		if (g_tWork.mode != USB_MODE) {
			Repeat_Stop();
			g_tWork.mode = USB_MODE;
		}
		LCD_Clear_MHZ_ICO();
		LCD_Clear_FM_ICO();
		LCD_Clear_BLUETooTH_ICO();
		LCD_Clear_AUX_ICO();

		LCD_Show_USB_ICO();
		if (buf[3] > 9) {
			sprintf(tmpBuf, "    %u%02u", (uint16_t) buf[3], (uint16_t) buf[4]);
		} else {
			sprintf(tmpBuf, "     %u%02u", (uint16_t) buf[3],
					(uint16_t) buf[4]);
		}
		app_lcd_default_string_set(tmpBuf, strlen(tmpBuf), 3);
		break;
	case RCV_FM_HZ_CMD:
		if (g_tWork.mode != FM_MODE) {
			Repeat_Stop();
			g_tWork.mode = FM_MODE;
		}

		LCD_Clear_USB_ICO();
		LCD_Clear_MHZ_ICO();
		LCD_Clear_BLUETooTH_ICO();
		LCD_Clear_AUX_ICO();

		LCD_Show_FM_ICO();
		LCD_Show_MHZ_ICO();

		if (buf[3] > 99) {
			sprintf(tmpBuf, "FM %u%u", (uint16_t) buf[3], (uint16_t) buf[4]);
		} else if (buf[3] > 9) {
			sprintf(tmpBuf, "FM  %u%u", (uint16_t) buf[3], (uint16_t) buf[4]);
		} else {
			sprintf(tmpBuf, "FM   %u%u", (uint16_t) buf[3], (uint16_t) buf[4]);
		}
		app_lcd_default_string_set(tmpBuf, strlen(tmpBuf), 1);
		break;
	case RCV_VOL_CMD:
		g_tWork.vol = buf[3] & 0x7F;
		Repeat_SetStart(vol_resp);
		Repeat_SetStop(0);
		Repeat_Start(30, 1, 1);
		break;
////
	case KEY_POWER_SHORT_CMD:
		if (1 == buf[3]) { //pause
			memcpy(tmpBuf, buf + 4, 8);
			Repeat_SetStart(LED_show_blink_name_show_lcd_resp);
			Repeat_SetStop(LED_clear_blink_name_show_lcd_resp);
			Repeat_Start(6, 6, 0);
		} else {
			app_lcd_default_string_set(buf + 4, 8, 0);
			Repeat_SetStart(LED_show_blink_name_show_lcd_resp);
			Repeat_SetStop(0);
			Repeat_Start(1, 1, 1);
		}
		break;
	case KEY_ACC_CMD:
		LCD_Clear_downColon_ICO();
		LCD_Clear_upColon_ICO();
		if (buf[3] == 1) {
			g_tWork.status.bits.relay = 1;
		} else {
			g_tWork.status.bits.relay = 0;
		}
		Repeat_SetStart(relay_status_resp);
		Repeat_SetStop(0);
		Repeat_Start(20, 1, 1);
		break;
	case KEY_DOME_CMD:
#if 0
		sendBuf[index++] = LAMP2LCD_HEADER;
		sendBuf[index++] = 11;
		sendBuf[index++] = KEY_DOME_CMD;
		sendBuf[index++] = g_tWork.status.bits.DOME;
		sendBuf[index++] = g_tWork.status.bits.pause;
		app_dome_get_current_Name(sendBuf + index, 8);
		index += 8;
		for (i = 0; i < (sendBuf[1] + 1); i++) {
			sendBuf[index] += sendBuf[i + 1];
		}
#endif
		if (buf[3] == 1) {
			LCD_Show_LED_ICO();
			if (1 == buf[4]) { //pause
				memcpy(tmpBuf, buf + 5, 8);
				for (i = 0; i < sizeof(tmpBuf); i++) {
					if (*(tmpBuf + i) == 0) {
						*(tmpBuf + i) = ' ';
					}
				}
				Repeat_SetStart(LED_show_blink_name_show_lcd_resp);
				Repeat_SetStop(LED_clear_blink_name_show_lcd_resp);
				Repeat_Start(5, 5, 0);
			} else {
//				memcpy(tmpBuf, buf + 5, 8);
				app_lcd_default_string_set(buf + 5, 8, 0);

//				Repeat_SetStart(LED_show_blink_name_show_lcd_resp);
//				Repeat_SetStop(0);
//				Repeat_Start(1, 1, 1);
			}
		} else {
			LCD_Clear_LED_ICO();
		}
		break;
	case KEY_UP_CMD:
		memcpy(tmpBuf, buf + 3, 8);
		app_lcd_default_string_set(buf + 3, 8, 0);
		Repeat_SetStart(LED_show_blink_name_show_lcd_resp);
		Repeat_SetStop(0);
		Repeat_Start(1, 1, 1);
		break;
	case KEY_DOWN_CMD:
		memcpy(tmpBuf, buf + 3, 8);
		app_lcd_default_string_set(buf + 3, 8, 0);
		Repeat_SetStart(LED_show_blink_name_show_lcd_resp);
		Repeat_SetStop(0);
		Repeat_Start(1, 1, 1);
		break;
	case MODE_CHANGE_CMD:
		LCD_Clear_MHZ_ICO();
		LCD_Clear_upColon_ICO();
		LCD_Clear_downColon_ICO();
		LCD_Clear_BLUETooTH_ICO();
		LCD_Clear_FM_ICO();
		LCD_Clear_AUX_ICO();
		LCD_Clear_USB_ICO();

		switch (buf[3]) {
		case BT_MODE:  //BT
			LCD_Show_BLUETooTH_ICO();
			if (1 == buf[4]) {
				strcpy(tmpBuf, "PRIRED");
			} else if (2 == buf[4]) {
				strcpy(tmpBuf, "PAIRING");
			}
			app_lcd_default_string_set(tmpBuf, strlen(tmpBuf), 0);
			break;
		case FM_MODE:  //FM

			break;
		case AUX_MODE:  //AUX
			LCD_Show_AUX_ICO();
			if (1 == buf[4]) {
				strcpy(tmpBuf, "PLAY");
			} else if (2 == buf[4]) {
				strcpy(tmpBuf, "MUTE");
			}
			app_lcd_default_string_set(tmpBuf, strlen(tmpBuf), 0);
			break;
		case USB_MODE:  //USB

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
	uint8_t i = 0;
	if (sendRcv_flag) {
		switch (ucRF_GetStatus()) {
		case TX_DS_FLAG: 		// 普通型发送完成 或 增强型发送成功

			RF_ClearFIFO();
			RF_ClearStatus();

			sendRcv_flag = 0;

			for (i = 0; i < 100; i++) {
				nop
				nop
			}

			RF_RxMode();

			for (i = 0; i < 100; i++) {
				nop
				nop
			}
//			key_bright_toggle();

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

			for (i = 0; i < 130; i++) {
				nop
				nop
			}

			RF_TxData(sendBuf, PAYLOAD_WIDTH);

			break;
		}

	} else {
		if (ucRF_DumpRxData(rcvBuf, PAYLOAD_WIDTH)) {

			app_2d4_Rcv(rcvBuf);
		}

	}

}
#if 0
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
#endif
