/*
 * bsp_keyBright.c
 *
 *  Created on: 2017��8��7��
 *      Author: fly
 */


#include "bsp.h"

void KEY_Bright_InitHard(void) {

	clr_P0M1_5;
	set_P0M2_5;

	key_bright_on();

}
void key_bright_off(void) {
	clr_P05;
}
void key_bright_on() {
	set_P05;
}