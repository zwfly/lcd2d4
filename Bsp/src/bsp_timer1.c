/*
 * bsp_timer1.c
 *
 *  Created on: 2017Äê6ÔÂ28ÈÕ
 *      Author: fly
 */

#include "bsp.h"

void Timer1_InitHard(void) {
	clr_GATE_T1;
	clr_CT_T1;
	set_M1_T1;
	clr_M0_T1;

	TH1 = (256 - 50);            //initial counter values
	TL1 = (256 - 50);

//	set_ET1;                                    //enable Timer0 interrupt
//	set_EA;                                     //enable interrupts
//	set_TR1;                                    //Timer0 run

}
/************************************************************************************************************
 *    TIMER 1 interrupt subroutine
 ************************************************************************************************************/
void Timer1_ISR(void)
interrupt 3           //interrupt address is 0x001B
{

	//P03 = ~P03;                                 //P0/3 toggle when interrupt
}
