/*
 * bsp_adc.c
 *
 *  Created on: 2017��7��7��
 *      Author: admin
 */

#include "bsp.h"

idata ADC_RESULT_T g_tADC_Result;

void ADC_Init(void) {
	g_tADC_Result.channel = 0;
	g_tADC_Result.result[0] = 1023;
	g_tADC_Result.result[1] = 1023;
#if 1

//	clr_P0M1_0;
//	clr_P0M2_0;

//	clr_P0M1_1;
//	clr_P0M2_1;

	set_ADCEN;

	ADCCON0 = 0x00;                   //select ADC pin
#if 1
	set_P0M1_0;                       //set ADC pin is input only mode
	clr_P0M2_0;
	set_P00DIDS;                      //disable digital connection

	set_P0M1_1;                       //set ADC pin is input only mode
	clr_P0M2_1;
	set_P01DIDS;

#else
	clr_P0M1_0;                       //set ADC pin is input only mode
	clr_P0M2_0;

	clr_P0M1_1;//set ADC pin is input only mode
	clr_P0M2_1;

#endif

	clr_ADCDIV2;
	set_ADCDIV1;
	clr_ADCDIV0;

	EADC = 1;
#endif
}

void ADC_Start(void) {
	if (g_tADC_Result.channel) {
		g_tADC_Result.channel = 0;
		clr_ADCHS3;
		clr_ADCHS2;
		clr_ADCHS1;
		clr_ADCHS0;
		nop
		nop
		nop
		set_ADCS;  //Trigger ADC start conversion
	} else {
		g_tADC_Result.channel = 1;
		clr_ADCHS3;
		clr_ADCHS2;
		clr_ADCHS1;
		set_ADCHS0;
		nop
		nop
		nop
		set_ADCS;  //Trigger ADC start conversion
	}

}
