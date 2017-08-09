/*
 * bsp_bright.c
 *
 *  Created on: 2017Äê6ÔÂ26ÈÕ
 *      Author: fly
 */

#include "bsp.h"

void LCD_Bright_InitHard(void) {

#if 1
	clr_P0M1_6;
	set_P0M2_6;

	lcd_bright_on();
#endif

}
void lcd_bright_off(void) {
	clr_P06;
}
void lcd_bright_on() {
	set_P06;
}
