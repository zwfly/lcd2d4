/*
 * bsp_timer0.c
 *
 *  Created on: 2017Äê6ÔÂ28ÈÕ
 *      Author: fly
 */

#include "bsp.h"

#define TH0_INIT        922
#define TL0_INIT        922

static uint8_t u8TH0_tmp = 0, u8TL0_tmp = 0;

_Task_time Task_time;

static void timer0_ParamInit(void);
void Timer0_InitHard(void) {

	timer0_ParamInit();

	clr_GATE_T0;
	clr_CT_T0;
	clr_M1_T0;
	set_M0_T0;

	u8TH0_tmp = (65536 - TH0_INIT) / 256;
	u8TL0_tmp = (65536 - TL0_INIT) % 256;

	TH0 = u8TH0_tmp;            //initial counter values
	TL0 = u8TL0_tmp;

	set_ET0;                                    //enable Timer0 interrupt
	set_TR0;                                    //Timer0 run

}

static void timer0_ParamInit(void) {

	Task_time.cnt_10ms = 0;
	Task_time.cnt_100ms = 0;
	Task_time.cnt_1s = 0;

	Task_time.flag_10ms = 0;
	Task_time.flag_100ms = 0;
	Task_time.flag_1s = 0;

}

void Timer0_ISR(void)
interrupt 1              //interrupt address is 0x000B
{
	TH0 = u8TH0_tmp;
	TL0 = u8TL0_tmp;

	if (++Task_time.cnt_10ms >= 10) {
		Task_time.cnt_10ms = 0;
		Task_time.flag_10ms = 1;

	}
	if (++Task_time.cnt_100ms >= 100) {
		Task_time.cnt_100ms = 0;
		Task_time.flag_100ms = 1;
	}
	if (++Task_time.cnt_1s >= 1000) {
		Task_time.cnt_1s = 0;
		Task_time.flag_1s = 1;

	}

}

