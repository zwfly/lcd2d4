#include "app.h"

//uint8_t c;
//DEVICE_T g_tDevice;
/******************************************************************************
 * FUNCTION_PURPOSE: ADC interrupt Service Routine
 ******************************************************************************/
void ADC_ISR(void)
interrupt 11
{
	clr_ADCF;                               //clear ADC interrupt flag

	g_tADC_Result.result[g_tADC_Result.channel] = ADCRH;
	g_tADC_Result.result[g_tADC_Result.channel] <<= 2;
	g_tADC_Result.result[g_tADC_Result.channel] |= ADCRL;

}
//static char ss[16] = { 0 };
void main(void) {
	uint8_t ucKeyCode;
	System_Clock_Select(E_HIRCEN);

	/****************/
	bsp_Init();

	/****************/
#if 1
//	app_key_init();
#if 0
	app_2d4_init();
#else
	g_tWork.match_code_mode = 0;
	app_2d4_switch_saved_address();
#endif
	app_lcd_init();
	app_work_Init();
#endif
	/****************/
//	Show_FW_Version_Number_To_PC();
	while (1) {
		if (Task_time.flag_5ms) {
			Task_time.flag_5ms = 0;
			//////////////////
			ADC_Start();
		}
		if (Task_time.flag_10ms) {
			Task_time.flag_10ms = 0;
			//////////////////
			bsp_KeyScan();

			app_2d4_pro();
		}
		if (Task_time.flag_100ms) {
			uint8_t i = 0;

			static uint8_t n = 0;
			Task_time.flag_100ms = 0;
			//////////////////
//			app_key_100ms_pro();
//			app_work_100ms_pro();
//			app_charge_100ms_pro();
			Repeat_Pro();

			app_lcd_pro();

			n++;
			if (n >= 5) {
				n = 0;
//				sprintf(ss, "%04u%04u", g_tADC_Result.result[0],
//						g_tADC_Result.result[1]);
//				LCD_ShowString(ss);
			}
		}
		if (Task_time.flag_1s) {
//			static uint8_t cnt = 0;
			Task_time.flag_1s = 0;
			//////////////////
			app_work_1s_pro();
//			cnt++;
//			sprintf(ss, "cc %u", (uint16_t) cnt);
//			app_lcd_default_string_set(ss, strlen(ss));
		}

#if 1

		ucKeyCode = bsp_GetKey();
		if (ucKeyCode != KEY_NONE) {

			app_key_pro(ucKeyCode);
		}
#endif
	}
}
