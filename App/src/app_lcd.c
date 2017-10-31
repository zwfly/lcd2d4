/*
 * app_lcd.c
 *
 *  Created on: 2017Äê8ÔÂ26ÈÕ
 *      Author: fly
 */

#include "app.h"

static char lcd_default_string[16] = { 0 };

void app_lcd_init(void) {
	strcpy(lcd_default_string, "DEFAULT");
}
void app_lcd_default_string_set(char *s, uint8_t len) {
	strncpy(lcd_default_string, s, len);
	if (len < sizeof(lcd_default_string)) {
		lcd_default_string[len] = '\0';
	}
}

void app_lcd_pro(void) {

	if (app_repeat_IsEnable() == 0) {
		LCD_ShowString(lcd_default_string);

	}

}
