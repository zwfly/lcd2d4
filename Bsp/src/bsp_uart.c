/*
 * bsp_uart.c
 *
 *  Created on: 2017Äê6ÔÂ27ÈÕ
 *      Author: fly
 */

#include "bsp.h"

#include "bsp_beep.h"

BIT riflag;

void Uart_InitHard(void) {

	P5M1 &= ~SET_BIT7;
	P5M2 |= SET_BIT7;

	InitialUART1_Timer3(9600);
//	set_ES_1;
//	set_ET1;
}
#if 1
BIT Get_Data_From_UART1(uint8_t *c) {
	BIT b;

	if (RI_1) {
		*c = SBUF_1;
		RI_1 = 0;
		b = TRUE;
	} else {
		b = FALSE;
	}
	return b;
}
#endif

#if 0
void serial_IT(void)
interrupt 15
{
	if (RI_1) { /* if reception occur */
		clr_RI_1; /* clear reception flag for next reception */
		if (SBUF_1) {
			BEEP_Start(0, 5, 5, 2);
		} else {
			BEEP_Start(0, 5, 5, 1);
		}

		//	riflag = 1;
	}
	if (TI_1) {
		clr_TI_1; /* if emission occur */
	}
}
#endif
