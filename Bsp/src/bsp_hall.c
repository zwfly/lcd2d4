/*
 * bsp_hall.c
 *
 *  Created on: 2017年6月26日
 *      Author: fly
 */

#include "bsp.h"
#include "app_work.h"


#define HALL_NUM  3
#define HALL_CNT_UP  100
#define HALL_CNT_DOWN  10

static HALL_T g_tHall;

static void Hall_InitHard(void) {
	PICON = 0x00;
	PITYP = 0x00;
	PINEN = 0x00;
	PIPEN = 0x00;

	set_EPI;
}
static void Hall_InitVar(void) {
	g_tHall.count = 0;
	g_tHall.direction = 0;
	g_tHall.lastPos = 0;

}
void Hall_Init(void) {
	Hall_InitHard();
	Hall_InitVar();
}



void hall_pro(uint8_t n) {
	static BIT valid_flag = 0;

	if (((n - g_tHall.lastPos) == 1) || ((g_tHall.lastPos - n) == 2)) {
		g_tHall.direction = 1;  //拉长方向
		if (g_tHall.count < 255) {
			g_tHall.count++;
		}

	} else {
		g_tHall.direction = 0;  //收缩方向
		if (g_tHall.count) {
			g_tHall.count--;
		}
	}
	g_tHall.lastPos = n;

	if (valid_flag) {
		if (g_tHall.count < HALL_CNT_DOWN) {
			valid_flag = 0;
		}
	} else {
		if (g_tHall.count > HALL_CNT_UP) {
			valid_flag = 1;
			/* your code   --start */
			// 拉一次计数一次，计数一次调用一次
			query_work_sum();
			/* your code   --end */
		}
	}

}

void hall_1_interrupt(void) {
	hall_pro(1);
}
void hall_2_interrupt(void) {
	hall_pro(2);
}
void hall_3_interrupt(void) {
	hall_pro(3);
}
