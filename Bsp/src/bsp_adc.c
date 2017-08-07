/*
 * bsp_adc.c
 *
 *  Created on: 2017Äê7ÔÂ7ÈÕ
 *      Author: admin
 */

#include "bsp.h"

ADC_RESULT_T g_tADC_Result;

void ADC_Init(void) {
	g_tADC_Result.busy = 0;
	g_tADC_Result.channel = 0;
	g_tADC_Result.result = 1023;

#if 1

	clr_P0M1_0;
	clr_P0M2_0;

	clr_P0M1_1;
	clr_P0M2_1;

	set_ADCEN;

	ADCCON0 = 0x00;                   //select ADC pin
	set_P0M1_0;                       //set ADC pin is input only mode
	clr_P0M2_0;
	set_P00DIDS;                      //disable digital connection

	clr_ADCDIV2;
	set_ADCDIV1;
	clr_ADCDIV0;

	EADC = 1;
#endif
}

void ADC_Start(void) {

	g_tADC_Result.busy = 1;

	if (g_tADC_Result.channel) {
		g_tADC_Result.channel = 0;
		clr_ADCHS3;
		clr_ADCHS2;
		clr_ADCHS1;
		clr_ADCHS0;
		set_ADCS;  //Trigger ADC start conversion
	} else {
		g_tADC_Result.channel = 1;
		clr_ADCHS3;
		clr_ADCHS2;
		clr_ADCHS1;
		set_ADCHS0;
		set_ADCS;  //Trigger ADC start conversion
	}

}
