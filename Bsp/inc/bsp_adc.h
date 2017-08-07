/*
 * bsp_adc.h
 *
 *  Created on: 2017Äê7ÔÂ7ÈÕ
 *      Author: admin
 */

#ifndef BSP_INC_BSP_ADC_H_
#define BSP_INC_BSP_ADC_H_

typedef struct {
	uint8_t busy;
	uint8_t channel;
	uint16_t result;

} ADC_RESULT_T;

extern ADC_RESULT_T g_tADC_Result;

void ADC_Init(void);
void ADC_Start(void);

#endif /* BSP_INC_BSP_ADC_H_ */
