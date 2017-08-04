/*
 * bsp_timer0.h
 *
 *  Created on: 2017Äê6ÔÂ28ÈÕ
 *      Author: fly
 */

#ifndef BSP_INC_BSP_TIMER0_H_
#define BSP_INC_BSP_TIMER0_H_

typedef struct {

	uint8_t cnt_10ms;
	uint8_t flag_10ms;

	uint8_t cnt_100ms;
	uint8_t flag_100ms;

	uint16_t cnt_1s;
	uint8_t flag_1s;

} _Task_time;

extern _Task_time Task_time;

void Timer0_InitHard(void);

#endif /* BSP_INC_BSP_TIMER0_H_ */
