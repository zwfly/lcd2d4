#include "bsp.h"

BIT BIT_TMP;  //WTF

void bsp_Init(void) {

//	clr_BODEN

//	Set_All_GPIO_Quasi_Mode();
	Set_All_GPIO_Input_Mode();

	LCD_display_InitHard();

	ADC_Init();
	bsp_InitKey();
	KEY_Bright_InitHard();
//	LCD_Bright_InitHard();

	Timer0_InitHard();

	Wireless2d4_InitHard();

	LCD_Bright_InitHard();

	set_EA;         //enable interrupts
}

