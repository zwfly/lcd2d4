/*
 * app_work.h
 *
 *  Created on: 2017Äê7ÔÂ6ÈÕ
 *      Author: admin
 */

#ifndef APP_INC_APP_WORK_H_
#define APP_INC_APP_WORK_H_

typedef enum {
	E_TRAINING_PLACE = 0,
	E_Simple_metering_mode,
	E_Quick_start_mode,
	E_Coach_mode,
} E_TRAINING_MODE;

typedef struct _WORK_T {
	E_TRAINING_MODE mode;
	char reps_mode;
	uint16_t sum;
	uint8_t reps_num;
	uint16_t pulls_num;
	uint16_t cal_num;

} WORK_T;
extern WORK_T g_tWork;

extern const uint8_t Rep_Pull_num[4][2];

void work_Init(void);
void query_work_sum(void);
void app_work_1s_pro(void);
void app_work_100ms_pro(void);

#endif /* APP_INC_APP_WORK_H_ */
