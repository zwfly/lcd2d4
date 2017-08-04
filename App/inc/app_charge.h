/*
 * app_charge.h
 *
 *  Created on: 2017年7月12日
 *      Author: fly
 */

#ifndef APP_INC_APP_CHARGE_H_
#define APP_INC_APP_CHARGE_H_

typedef enum {
	E_CHARGE_STATUS_PLACE = 0,
	E_NeedCharge,
	E_InCharge,
	E_FullCharge,
	E_Discharge,  //正在放电
} E_CHARGE_STATUS;

typedef struct _CHARGE_T {
	E_CHARGE_STATUS status;
	uint8_t count;

	uint16_t result;

} CHARGE_T;

void app_charge_Init(void);
void app_charge_100ms_pro(void);
void app_battery_voltage_result(void);
void app_charge_1s_pro(void);

#endif /* APP_INC_APP_CHARGE_H_ */
