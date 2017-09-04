/*
 * app_work.h
 *
 *  Created on: 2017Äê7ÔÂ6ÈÕ
 *      Author: admin
 */

#ifndef APP_INC_APP_WORK_H_
#define APP_INC_APP_WORK_H_

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

	uint8_t track;

} WORK_T;
extern idata WORK_T g_tWork;

void app_work_Init(void);
void app_work_1s_pro(void);
void app_work_100ms_pro(void);

#endif /* APP_INC_APP_WORK_H_ */
