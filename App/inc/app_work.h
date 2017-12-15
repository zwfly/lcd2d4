/*
 * app_work.h
 *
 *  Created on: 2017年7月6日
 *      Author: admin
 */

#ifndef APP_INC_APP_WORK_H_
#define APP_INC_APP_WORK_H_

#define BT_MODE     0x01
#define FM_MODE     0x02
#define USB_MODE    0x03
#define AUX_MODE    0x04
#define DOME_MODE   0x05
#define CALL_MODE   0x06

typedef struct _WORK_T {

	union {
		uint8_t allbits;
		struct {
			unsigned relay :1;
			unsigned speaker :1;
			unsigned BT1 :1;
			unsigned FM1 :1;
			unsigned AUX1 :1;
			unsigned USB1 :1;
			unsigned ra6 :1;
			unsigned ra9 :1;
		} bits;
	} status;

	uint8_t vol;
	uint8_t mode;
	uint8_t FM_station;
	uint16_t track;
	uint8_t match_code_mode;
} WORK_T;

typedef struct _LED_MODE_MSG_ST {

	union {
		uint8_t allbits;
		struct {
			unsigned pp :1;  //闪法关闭/开启。0：闪法正常工作，1：闪法暂停
			unsigned ra2 :1;
			unsigned ra3 :1;
			unsigned ra5 :1;
			unsigned ra6 :1;
			unsigned ra7 :1;
			unsigned ra8 :1;
			unsigned ra9 :1;
		} bits;
	} status;

//	uint8_t mode;

} LED_MODE_MSG_ST;

extern idata WORK_T g_tWork;

void app_work_Init(void);
void app_work_1s_pro(void);
void app_work_100ms_pro(void);
void app_work_cnt_clear(void);

#endif /* APP_INC_APP_WORK_H_ */
