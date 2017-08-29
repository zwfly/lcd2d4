/*
 * app_lcd.c
 *
 *  Created on: 2017Äê8ÔÂ26ÈÕ
 *      Author: fly
 */

#include "app.h"

//static idata char lcd_default_string[16] = { 0 };
static char lcd_default_string[16] = { 0 };

void app_lcd_init(void) {
	memcpy(lcd_default_string, "DEFAULT", strlen("DEFAULT"));
}
//void app_lcd_default_string_set(char *s, uint8_t len) {
//	memcpy(lcd_default_string, s, len);
//	lcd_default_string[len] = '\0';
//}
void app_lcd_default_string_set(char *s, uint8_t len) {
	memcpy(lcd_default_string, s, len);
	lcd_default_string[len] = '\0';
}

void app_lcd_pro(void) {

	if (app_repeat_IsEnable() == 0) {

		LCD_ShowString(lcd_default_string);

	}

}
