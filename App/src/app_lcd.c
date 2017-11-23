/*
 * app_lcd.c
 *
 *  Created on: 2017Äê8ÔÂ26ÈÕ
 *      Author: fly
 */

#include "app.h"

static char lcd_default_string[16] = { 0 };
static uint8_t dotn = 0;

void app_lcd_init(void) {
	dotn = 0;
	strcpy(lcd_default_string, " PWR OFF");
}
void app_lcd_default_string_set(char *s, uint8_t len, uint8_t _dotn) {
	strncpy(lcd_default_string, s, len);
	if (len < sizeof(lcd_default_string)) {
		lcd_default_string[len] = '\0';
	}
	dotn = _dotn;
}

void app_lcd_pro(void) {

	if (app_repeat_IsEnable() == 0) {
		LCD_ShowString(lcd_default_string);
		if (dotn == 0) {
			LCD_Clear_downColon_ICO();
			LCD_Clear_upColon_ICO();
		} else if (dotn == 1) {
			LCD_Clear_upColon_ICO();
			LCD_Show_downColon_ICO();
		} else if (dotn == 2) {
			LCD_Show_upColon_ICO();
			LCD_Clear_downColon_ICO();

		} else if (dotn == 3) {
			LCD_Show_upColon_ICO();
			LCD_Show_downColon_ICO();
		}
	}

}
