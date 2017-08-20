/*
 * app_2d4.c
 *
 *  Created on: 2017年8月16日
 *      Author: fly
 */

#include "app.h"
void app_2d4_init(void) {

	RF_Init();
//	RF_Carrier(1);

#if 0
	RF_TxMode();
#else
	RF_RxMode();
#endif
}
uint8_t ss[16] = { 0 };
uint8_t ucPayload[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };
static uint16_t n = 0;
void app_2d4_pro(void) {
	uint16_t sta = 0;
#if 0
	//send data
	sta = ucRF_GetStatus();
	switch (sta) {
		case TX_DS_FLAG: 		// 普通型发送完成 或 增强型发送成功
		//...
		sprintf(ss, "ok %X", sta);

		RF_ClearFIFO();
		RF_ClearStatus();
		break;
		case RX_DR_FLAG://发送成功且收到payload
		//...
		sprintf(ss, "rx %X", sta);
		RF_ClearFIFO();
		RF_ClearStatus();
		break;
		case MAX_RT_FLAG:// 增强型发送超时失败
		//...

		sprintf(ss, "fail %X", sta);

		RF_ClearFIFO();
		RF_ClearStatus();
		break;
		default:// rf 处于空闲状态才发送数据
		{

			RF_TxData(ucPayload, PAYLOAD_WIDTH);
			n++;
			sprintf(ss, "T%u %X", n, sta);

		}

		break;

	}
	LCD_Clear_All();
	LCD_ShowString(ss);
#else
	if (ucRF_DumpRxData(ucPayload, PAYLOAD_WIDTH)) {
		//接收成功
		static uint16_t n = 0;
		n++;
		sprintf(ss, "rcv %u", n);

		LCD_Clear_All();
		LCD_ShowString(ss);
	}
#endif
}
