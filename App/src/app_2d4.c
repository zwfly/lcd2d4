/*
 * app_2d4.c
 *
 *  Created on: 2017��8��16��
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
		case TX_DS_FLAG: 		// ��ͨ�ͷ������ �� ��ǿ�ͷ��ͳɹ�
		//...
		sprintf(ss, "ok %X", sta);

		RF_ClearFIFO();
		RF_ClearStatus();
		break;
		case RX_DR_FLAG://���ͳɹ����յ�payload
		//...
		sprintf(ss, "rx %X", sta);
		RF_ClearFIFO();
		RF_ClearStatus();
		break;
		case MAX_RT_FLAG:// ��ǿ�ͷ��ͳ�ʱʧ��
		//...

		sprintf(ss, "fail %X", sta);

		RF_ClearFIFO();
		RF_ClearStatus();
		break;
		default:// rf ���ڿ���״̬�ŷ�������
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
		//���ճɹ�
		static uint16_t n = 0;
		n++;
		sprintf(ss, "rcv %u", n);

		LCD_Clear_All();
		LCD_ShowString(ss);
	}
#endif
}
