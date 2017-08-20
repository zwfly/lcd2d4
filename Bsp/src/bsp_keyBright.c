/*
 * bsp_keyBright.c
 *
 *  Created on: 2017Äê8ÔÂ7ÈÕ
 *      Author: fly
 */

#include "bsp.h"

void KEY_Bright_InitHard(void) {

	clr_P0M1_5;
	set_P0M2_5;

	key_bright_off();

}
void key_bright_off(void) {
	clr_P05;
}
void key_bright_on(void) {
	set_P05;
}
void key_bright_toggle(void) {
	P05 = ~P05;
}
