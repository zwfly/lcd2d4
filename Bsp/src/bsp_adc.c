/*
 * bsp_adc.c
 *
 *  Created on: 2017Äê7ÔÂ7ÈÕ
 *      Author: admin
 */

#include "bsp.h"

void ADC_Init(void) {

#if 1

	P0M1 &= ~SET_BIT1;
	P0M2 |= SET_BIT1;
	set_P01;

	set_ADCEN;

	ADCCON0 = 0x00;                   //select ADC pin
	set_P0M1_0;                       //set ADC pin is input only mode
	clr_P0M2_0;
	set_P00DIDS;                      //disable digital connection

	clr_ADCDIV2;
	set_ADCDIV1;
	clr_ADCDIV0;

	//////

	set_ADCMPEN;
	set_ADCMPOP;

	ADCMPH = 0;
	ADCMPL = 0;

	EADC = 1;
#endif
}


