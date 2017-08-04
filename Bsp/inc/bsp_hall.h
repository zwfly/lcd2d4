/*
 * bsp_hall.h
 *
 *  Created on: 2017Äê6ÔÂ26ÈÕ
 *      Author: fly
 */

#ifndef BSP_INC_BSP_HALL_H_
#define BSP_INC_BSP_HALL_H_

typedef struct _HALL_T {
	uint8_t count;
	uint8_t direction;
	uint8_t lastPos;
} HALL_T;

void Hall_Init(void);
void hall_1_interrupt(void);
void hall_2_interrupt(void);
void hall_3_interrupt(void);

#endif /* BSP_INC_BSP_HALL_H_ */
