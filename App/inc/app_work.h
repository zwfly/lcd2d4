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
			unsigned ra2 :1;
			unsigned ra3 :1;
			unsigned ra4 :1;
			unsigned ra5 :1;
			unsigned ra6 :1;
			unsigned ra9 :1;
		} bits;
	} status;

	uint8_t vol;
	char mode;

	uint8_t track;

} WORK_T;
extern idata WORK_T g_tWork;

void app_work_Init(void);
void app_work_1s_pro(void);
void app_work_100ms_pro(void);

#endif /* APP_INC_APP_WORK_H_ */
