/*
 * app_charge.c
 *
 *  Created on: 2017Äê7ÔÂ12ÈÕ
 *      Author: fly
 */

#include "app.h"

static idata CHARGE_T g_tCharge;

void app_charge_Init(void) {

	g_tCharge.count = 0;
}

void app_charge_100ms_pro(void) {
	static BIT flag = 0;

	if (g_tDevice.status == E_PowerDown) {
		LCD_Clear_Battery_ICO();
		return;
	}

	g_tCharge.count++;
	switch (g_tCharge.status) {
	case E_NeedCharge:
		if (g_tCharge.count >= 5) {
			g_tCharge.count = 0;

			if (flag) {
				flag = 0;
				LCD_Show_Battery_ICO();
			} else {
				flag = 1;
				LCD_Clear_Battery_ICO();
			}
		}
		break;
	case E_InCharge:
		if (g_tCharge.count >= 10) {
			g_tCharge.count = 0;

			if (flag) {
				flag = 0;
				LCD_Show_Battery_ICO();
			} else {
				flag = 1;
				LCD_Clear_Battery_ICO();
			}
		}
		break;
	case E_FullCharge:
		if (g_tCharge.count >= 9) {
			g_tCharge.count = 0;

			LCD_Show_Battery_ICO();
		}
		break;
	case E_Discharge:
		if (g_tCharge.count >= 9) {
			g_tCharge.count = 0;

			LCD_Clear_Battery_ICO();
		}
		break;
	}

}

static BIT result_flag = 0;

void app_battery_voltage_result(void) {
	BIT cmp = 0;

	set_P01;

	g_tCharge.result = ADCRH;
	g_tCharge.result <<= 2;
	g_tCharge.result |= ADCRL;

	((ADCCON2 & SET_BIT4) == 0) ? (cmp = 1) : (cmp = 0);

	result_flag = 1;

//	printf("battery voltage ADC value = %d, cmp = %d\n", result, cmp);

}

void app_charge_1s_pro(void) {

	if (P50) {
		g_tCharge.status = E_FullCharge;
	} else {
		g_tCharge.status = E_InCharge;
	}

	if (result_flag) {
		result_flag = 0;

		if (g_tCharge.result < 490) {
			g_tCharge.status = E_NeedCharge;
		} else {
			g_tCharge.status = E_Discharge;
		}

//		printf("adc = %d\n", g_tCharge.result);
		printf("adc = %d\n", g_tCharge.result);
	}

}
