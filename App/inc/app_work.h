/*
 * app_work.h
 *
 *  Created on: 2017Äê7ÔÂ6ÈÕ
 *      Author: admin
 */

#ifndef APP_INC_APP_WORK_H_
#define APP_INC_APP_WORK_H_

typedef enum {
	E_MODE_PLACE = 0, E_BT_mode, E_FM_mode, E_USB_mode, E_AUX_mode,
} E_MODE;

typedef struct _WORK_T {
	E_MODE mode;
	uint8_t vol;
	uint8_t track;

} WORK_T;
extern WORK_T g_tWork;


void work_Init(void);
void query_work_sum(void);
void app_work_1s_pro(void);
void app_work_100ms_pro(void);

#endif /* APP_INC_APP_WORK_H_ */
