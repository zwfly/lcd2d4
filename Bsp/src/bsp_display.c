/*
 * bsp_display.c
 *
 *  Created on: 2017Äê6ÔÂ26ÈÕ
 *      Author: fly
 */

#include "bsp.h"
#include <string.h>

#define COM0    0x01
#define COM1    0x02
#define COM2    0x04
#define COM3    0x08

void LCD_display_InitHard(void) {

#if 1
	P0M2 = 0x00;
	P0M1 = 0x80;

	P1M2 = 0x00;
	P1M1 = 0xFF;

	P2M2 = 0x00;
	P2M1 = 0xFF;

	P3M2 = 0x00;
	P3M1 = 0x0F;

	P4M2 = 0x00;
	P4M1 = 0xFF;

	P5M2 = 0x00;
	P5M1 = 0xFF;
#endif

	//LCDCON = 0x40;      //;VLCD = 0.9VDD (VDD = 3.3V, VLCD = 3.0V)
	LCDCON = 0x00; 			//;1/4 duty, 1/3 bias, 150kO resistor ladder

	LCDCLK = 0x04;      //

	//enable seg pin
	LCDSEG0 = 0xFF;
	LCDSEG1 = 0xFF;
	LCDSEG2 = 0xFF;
	LCDSEG3 = 0xFF;

	LCDCON |= SET_BIT7;  //LCDEN = 1

	LCD_Clear_All();
}

void LCD_Clear_All(void) {
	uint8_t i;
	for (i = 0; i < 32; i++) {
		LCDPTR = i;
		LCDDAT = 0;
	}
}

void LCD_Clear_LED_ICO(void) {
	LCDPTR = 18;
	LCDDAT &= ~ COM3;
}
void LCD_Show_LED_ICO(void) {
	LCDPTR = 18;
	LCDDAT |= COM3;
}
void LCD_Clear_FM_ICO(void) {
	LCDPTR = 14;
	LCDDAT &= ~ COM3;
}
void LCD_Show_FM_ICO(void) {
	LCDPTR = 14;
	LCDDAT |= COM3;
}
void LCD_Clear_BLUETooTH_ICO(void) {
	LCDPTR = 11;
	LCDDAT &= ~ COM3;
}
void LCD_Show_BLUETooTH_ICO(void) {
	LCDPTR = 11;
	LCDDAT |= COM3;
}
void LCD_Clear_AUX_ICO(void) {
	LCDPTR = 10;
	LCDDAT &= ~COM3;
}
void LCD_Show_AUX_ICO(void) {
	LCDPTR = 10;
	LCDDAT |= COM3;
}
void LCD_Clear_USB_ICO(void) {
	LCDPTR = 3;
	LCDDAT &= ~ COM3;
}
void LCD_Show_USB_ICO(void) {
	LCDPTR = 3;
	LCDDAT |= COM3;
}
void LCD_Clear_MHZ_ICO(void) {
	LCDPTR = 2;
	LCDDAT &= ~ COM3;
}
void LCD_Show_MHZ_ICO(void) {
	LCDPTR = 2;
	LCDDAT |= COM3;
}
void LCD_Clear_BAZOOKA_ICO(void) {
	LCDPTR = 15;
	LCDDAT &= ~ COM3;
}
void LCD_Show_BAZOOKA_ICO(void) {
	LCDPTR = 15;
	LCDDAT |= COM3;
}

/*
 * Ã°ºÅ   :
 * */

void LCD_Clear_upColon_ICO(void) {
	LCDPTR = 7;
	LCDDAT &= ~ COM3;
}
void LCD_Show_upColon_ICO(void) {
	LCDPTR = 7;
	LCDDAT |= COM3;
}
void LCD_Clear_downColon_ICO(void) {
	LCDPTR = 6;
	LCDDAT &= ~ COM3;
}
void LCD_Show_downColon_ICO(void) {
	LCDPTR = 6;
	LCDDAT |= COM3;
}
void LCD_Clear_Colon_ICO(void) {
	LCD_Clear_upColon_ICO();
	LCD_Clear_downColon_ICO();
}
void LCD_Show_Colon_ICO(void) {
	LCD_Show_upColon_ICO();
	LCD_Show_downColon_ICO();
}
static void LCD_Clear_mi(uint8_t n) {
	switch (n) {
	case 0:
		LCDPTR = 31;
		LCDDAT &= ~(COM0 + COM1 + COM2);

		LCDPTR = 30;
		LCDDAT &= ~(COM0 + COM1 + COM2);

		LCDPTR = 29;
		LCDDAT &= ~(COM0 + COM1 + COM2 + COM3);

		LCDPTR = 28;
		LCDDAT &= ~(COM0 + COM1 + COM2 + COM3);
		break;
	case 1:
		LCDPTR = 27;
		LCDDAT &= ~(COM0 + COM1 + COM2);

		LCDPTR = 26;
		LCDDAT &= ~(COM0 + COM1 + COM2);

		LCDPTR = 25;
		LCDDAT &= ~(COM0 + COM1 + COM2 + COM3);

		LCDPTR = 24;
		LCDDAT &= ~(COM0 + COM1 + COM2 + COM3);
		break;
	case 2:
		LCDPTR = 23;
		LCDDAT &= ~(COM0 + COM1 + COM2);

		LCDPTR = 22;
		LCDDAT &= ~(COM0 + COM1 + COM2);

		LCDPTR = 21;
		LCDDAT &= ~(COM0 + COM1 + COM2 + COM3);

		LCDPTR = 20;
		LCDDAT &= ~(COM0 + COM1 + COM2 + COM3);
		break;
	case 3:
		LCDPTR = 19;
		LCDDAT &= ~(COM0 + COM1 + COM2);

		LCDPTR = 18;
		LCDDAT &= ~(COM0 + COM1 + COM2);

		LCDPTR = 17;
		LCDDAT &= ~(COM0 + COM1 + COM2 + COM3);

		LCDPTR = 16;
		LCDDAT &= ~(COM0 + COM1 + COM2 + COM3);
		break;
	case 4:
		LCDPTR = 15;
		LCDDAT &= ~(COM0 + COM1 + COM2);

		LCDPTR = 14;
		LCDDAT &= ~(COM0 + COM1 + COM2);

		LCDPTR = 13;
		LCDDAT &= ~(COM0 + COM1 + COM2 + COM3);

		LCDPTR = 12;
		LCDDAT &= ~(COM0 + COM1 + COM2 + COM3);
		break;
	case 5:
		LCDPTR = 11;
		LCDDAT &= ~(COM0 + COM1 + COM2);

		LCDPTR = 10;
		LCDDAT &= ~(COM0 + COM1 + COM2);

		LCDPTR = 9;
		LCDDAT &= ~(COM0 + COM1 + COM2 + COM3);

		LCDPTR = 8;
		LCDDAT &= ~(COM0 + COM1 + COM2 + COM3);
		break;
	case 6:
		LCDPTR = 7;
		LCDDAT &= ~(COM0 + COM1 + COM2);

		LCDPTR = 6;
		LCDDAT &= ~(COM0 + COM1 + COM2);

		LCDPTR = 5;
		LCDDAT &= ~(COM0 + COM1 + COM2 + COM3);

		LCDPTR = 4;
		LCDDAT &= ~(COM0 + COM1 + COM2 + COM3);
		break;
	case 7:
		LCDPTR = 3;
		LCDDAT &= ~(COM0 + COM1 + COM2);

		LCDPTR = 2;
		LCDDAT &= ~(COM0 + COM1 + COM2);

		LCDPTR = 1;
		LCDDAT &= ~(COM0 + COM1 + COM2 + COM3);

		LCDPTR = 0;
		LCDDAT &= ~(COM0 + COM1 + COM2 + COM3);
		break;
	}
}
void LCD_Clear_mi_all(void) {
	uint8_t i = 0;
	for (i = 0; i < 8; i++) {
		LCD_Clear_mi(i);
	}
}
void LCD_ShowChar(uint8_t n, char c) {
	if (n > 7) {
		return;
	}

	if (c == 'S' || c == 's') {
		c = '5';
	} else if (c == 'g') {
		c = '9';
	} else if (c == 'l') {
		c = 'L';
	} else if (c == 'p') {
		c = 'P';
	} else if (c == 'x') {
		c = 'X';
	}
	switch (c) {
	case '0':
		LCDPTR = 31 - n * 4;
		LCDDAT |= COM0 + COM2;
		LCDDAT &= ~ COM1;

		LCDPTR = 30 - n * 4;
		LCDDAT |= COM0 + COM2;
		LCDDAT &= ~ COM1;

		LCDPTR = 29 - n * 4;
		LCDDAT = ( COM0 + COM3);

		LCDPTR = 28 - n * 4;
		LCDDAT = ( COM0 + COM3);
		break;
	case '1':
		LCDPTR = 31 - n * 4;
		LCDDAT &= ~( COM0 + COM1 + COM2);

		LCDPTR = 30 - n * 4;
		LCDDAT &= ~( COM0 + COM1 + COM2);

		LCDPTR = 29 - n * 4;
		LCDDAT = COM0;

		LCDPTR = 28 - n * 4;
		LCDDAT = COM0 + COM3;
		break;
	case '2':
		LCDPTR = 31 - n * 4;
		LCDDAT |= COM1 + COM2;
		LCDDAT &= ~ COM0;

		LCDPTR = 30 - n * 4;
		LCDDAT |= COM0;
		LCDDAT &= ~(COM1 + COM2);

		LCDPTR = 29 - n * 4;
		LCDDAT = COM3;

		LCDPTR = 28 - n * 4;
		LCDDAT = ( COM0 + COM1);
		break;
	case '3':
		LCDPTR = 31 - n * 4;
		LCDDAT |= COM1;
		LCDDAT &= ~(COM0 + COM2);

		LCDPTR = 30 - n * 4;
		LCDDAT |= COM0;
		LCDDAT &= ~(COM1 + COM2);

		LCDPTR = 29 - n * 4;
		LCDDAT = COM3;

		LCDPTR = 28 - n * 4;
		LCDDAT = ( COM0 + COM1 + COM3);
		break;
	case '4':
		LCDPTR = 31 - n * 4;
		LCDDAT |= ( COM0 + COM1);
		LCDDAT &= ~ COM2;

		LCDPTR = 30 - n * 4;
		LCDDAT &= ~( COM0 + COM1 + COM2);

		LCDPTR = 29 - n * 4;
		LCDDAT = 0;

		LCDPTR = 28 - n * 4;
		LCDDAT = ( COM0 + COM1 + COM3);
		break;
	case '5':
		LCDPTR = 31 - n * 4;
		LCDDAT |= ( COM0 + COM1);
		LCDDAT &= ~ COM2;

		LCDPTR = 30 - n * 4;
		LCDDAT |= COM0;
		LCDDAT &= ~(COM1 + COM2);

		LCDPTR = 29 - n * 4;
		LCDDAT = COM3;

		LCDPTR = 28 - n * 4;
		LCDDAT = COM1 + COM3;
		break;
	case '6':
		LCDPTR = 31 - n * 4;
		LCDDAT |= ( COM0 + COM1 + COM2);

		LCDPTR = 30 - n * 4;
		LCDDAT |= COM0;
		LCDDAT &= ~(COM1 + COM2);

		LCDPTR = 29 - n * 4;
		LCDDAT = COM3;

		LCDPTR = 28 - n * 4;
		LCDDAT = ( COM1 + COM3);
		break;
	case '7':
		LCDPTR = 31 - n * 4;
		LCDDAT &= ~( COM0 + COM1 + COM2);

		LCDPTR = 30 - n * 4;
		LCDDAT |= COM0;
		LCDDAT &= ~(COM1 + COM2);

		LCDPTR = 29 - n * 4;
		LCDDAT = 0;

		LCDPTR = 28 - n * 4;
		LCDDAT = ( COM0 + COM3);
		break;
	case '8':
		LCDPTR = 31 - n * 4;
		LCDDAT |= ( COM0 + COM1 + COM2);

		LCDPTR = 30 - n * 4;
		LCDDAT |= COM0;
		LCDDAT &= ~(COM1 + COM2);

		LCDPTR = 29 - n * 4;
		LCDDAT = COM3;

		LCDPTR = 28 - n * 4;
		LCDDAT = ( COM0 + COM1 + COM3);
		break;
	case '9':
		LCDPTR = 31 - n * 4;
		LCDDAT |= ( COM0 + COM1);
		LCDDAT &= ~ COM2;

		LCDPTR = 30 - n * 4;
		LCDDAT |= COM0;
		LCDDAT &= ~(COM1 + COM2);

		LCDPTR = 29 - n * 4;
		LCDDAT = COM3;

		LCDPTR = 28 - n * 4;
		LCDDAT = ( COM0 + COM1 + COM3);
		break;
	case ' ':
		LCD_Clear_mi(n);
		break;
	case 'A':
		LCDPTR = 31 - n * 4;
		LCDDAT |= ( COM0 + COM1 + COM2);

		LCDPTR = 30 - n * 4;
		LCDDAT |= COM0;
		LCDDAT &= ~(COM1 + COM2);

		LCDPTR = 29 - n * 4;
		LCDDAT = 0;

		LCDPTR = 28 - n * 4;
		LCDDAT = ( COM0 + COM1 + COM3);
		break;
	case 'B':
		LCDPTR = 31 - n * 4;
		LCDDAT &= ~( COM0 + COM1 + COM2);

		LCDPTR = 30 - n * 4;
		LCDDAT |= COM0;
		LCDDAT &= ~(COM1 + COM2);

		LCDPTR = 29 - n * 4;
		LCDDAT = ( COM1 + COM2 + COM3);

		LCDPTR = 28 - n * 4;
		LCDDAT = ( COM0 + COM1 + COM3);
		break;
	case 'C':
		LCDPTR = 31 - n * 4;
		LCDDAT |= ( COM0 + COM2);
		LCDDAT &= ~ COM1;

		LCDPTR = 30 - n * 4;
		LCDDAT |= COM0;
		LCDDAT &= ~(COM1 + COM2);

		LCDPTR = 29 - n * 4;
		LCDDAT = COM3;

		LCDPTR = 28 - n * 4;
		LCDDAT = 0;
		break;
	case 'D':
		LCDPTR = 31 - n * 4;
		LCDDAT &= ~( COM0 + COM1 + COM2);

		LCDPTR = 30 - n * 4;
		LCDDAT |= COM0;
		LCDDAT &= ~(COM1 + COM2);

		LCDPTR = 29 - n * 4;
		LCDDAT = ( COM1 + COM2 + COM3);

		LCDPTR = 28 - n * 4;
		LCDDAT = ( COM0 + COM3);
		break;
	case 'E':
		LCDPTR = 31 - n * 4;
		LCDDAT |= COM0 + COM1 + COM2;

		LCDPTR = 30 - n * 4;
		LCDDAT |= COM0;
		LCDDAT &= ~( COM1 + COM2);

		LCDPTR = 29 - n * 4;
		LCDDAT = COM3;

		LCDPTR = 28 - n * 4;
		LCDDAT = COM1;
		break;
	case 'F':
		LCDPTR = 31 - n * 4;
		LCDDAT |= ( COM0 + COM1 + COM2);

		LCDPTR = 30 - n * 4;
		LCDDAT |= COM0;
		LCDDAT &= ~(COM1 + COM2);

		LCDPTR = 29 - n * 4;
		LCDDAT = 0;

		LCDPTR = 28 - n * 4;
		LCDDAT = COM1;
		break;
	case 'G':
		LCDPTR = 31 - n * 4;
		LCDDAT |= ( COM0 + COM2);
		LCDDAT &= ~ COM1;

		LCDPTR = 30 - n * 4;
		LCDDAT |= COM0;
		LCDDAT &= ~(COM1 + COM2);

		LCDPTR = 29 - n * 4;
		LCDDAT = COM3;

		LCDPTR = 28 - n * 4;
		LCDDAT = ( COM1 + COM3);
		break;
	case 'H':
		LCDPTR = 31 - n * 4;
		LCDDAT |= ( COM0 + COM1 + COM2);

		LCDPTR = 30 - n * 4;
		LCDDAT &= ~( COM0 + COM1 + COM2);

		LCDPTR = 29 - n * 4;
		LCDDAT = 0;

		LCDPTR = 28 - n * 4;
		LCDDAT = ( COM0 + COM1 + COM3);
		break;
	case 'I':
		LCDPTR = 31 - n * 4;
		LCDDAT &= ~( COM0 + COM1 + COM2);

		LCDPTR = 30 - n * 4;
		LCDDAT |= COM0;
		LCDDAT &= ~(COM1 + COM2);

		LCDPTR = 29 - n * 4;
		LCDDAT = ( COM1 + COM2 + COM3);

		LCDPTR = 28 - n * 4;
		LCDDAT = 0;
		break;
	case 'J':
		LCDPTR = 31 - n * 4;
		LCDDAT |= COM2;
		LCDDAT &= ~(COM0 + COM1);

		LCDPTR = 30 - n * 4;
		LCDDAT &= ~( COM0 + COM1 + COM2);

		LCDPTR = 29 - n * 4;
		LCDDAT = COM3;

		LCDPTR = 28 - n * 4;
		LCDDAT = ( COM0 + COM3);
		break;
	case 'K':
		LCDPTR = 31 - n * 4;
		LCDDAT |= ( COM0 + COM1 + COM2);

		LCDPTR = 30 - n * 4;
		LCDDAT &= ~( COM0 + COM1 + COM2);

		LCDPTR = 29 - n * 4;
		LCDDAT = COM0;

		LCDPTR = 28 - n * 4;
		LCDDAT = ( COM1 + COM3);
		break;
	case 'L':
		LCDPTR = 31 - n * 4;
		LCDDAT |= ( COM0 + COM2);
		LCDDAT &= ~ COM1;

		LCDPTR = 30 - n * 4;
		LCDDAT &= ~(COM0 + COM1 + COM2);

		LCDPTR = 29 - n * 4;
		LCDDAT = COM3;

		LCDPTR = 28 - n * 4;
		LCDDAT = 0;
		break;
	case 'M':
		LCDPTR = 31 - n * 4;
		LCDDAT |= ( COM0 + COM2);
		LCDDAT &= ~ COM1;

		LCDPTR = 30 - n * 4;
		LCDDAT |= COM1;
		LCDDAT &= ~(COM0 + COM2);

		LCDPTR = 29 - n * 4;
		LCDDAT = ( COM0 + COM2);

		LCDPTR = 28 - n * 4;
		LCDDAT = ( COM0 + COM3);
		break;
	case 'N':
		LCDPTR = 31 - n * 4;
		LCDDAT |= ( COM0 + COM2);
		LCDDAT &= ~ COM1;

		LCDPTR = 30 - n * 4;
		LCDDAT |= COM0;
		LCDDAT &= ~(COM1 + COM2);

		LCDPTR = 29 - n * 4;
		LCDDAT = 0;

		LCDPTR = 28 - n * 4;
		LCDDAT = ( COM0 + COM3);
		break;
	case 'O':
		LCDPTR = 31 - n * 4;
		LCDDAT |= ( COM0 + COM2);
		LCDDAT &= ~ COM1;

		LCDPTR = 30 - n * 4;
		LCDDAT |= COM0;
		LCDDAT &= ~(COM1 + COM2);

		LCDPTR = 29 - n * 4;
		LCDDAT = COM3;

		LCDPTR = 28 - n * 4;
		LCDDAT = ( COM0 + COM3);
		break;
	case 'P':
		LCDPTR = 31 - n * 4;
		LCDDAT |= ( COM0 + COM1 + COM2);

		LCDPTR = 30 - n * 4;
		LCDDAT |= COM0;
		LCDDAT &= ~(COM1 + COM2);

		LCDPTR = 29 - n * 4;
		LCDDAT = 0;

		LCDPTR = 28 - n * 4;
		LCDDAT = ( COM0 + COM1);
		break;
	case 'Q':
		LCDPTR = 31 - n * 4;
		LCDDAT |= ( COM0 + COM2);
		LCDDAT &= ~ COM1;

		LCDPTR = 30 - n * 4;
		LCDDAT |= COM0;
		LCDDAT &= ~(COM1 + COM2);

		LCDPTR = 29 - n * 4;
		LCDDAT = COM3;

		LCDPTR = 28 - n * 4;
		LCDDAT = ( COM0 + COM2 + COM3);
		break;
	case 'R':
		LCDPTR = 31 - n * 4;
		LCDDAT |= ( COM0 + COM1 + COM2);

		LCDPTR = 30 - n * 4;
		LCDDAT |= COM0;
		LCDDAT &= ~(COM1 + COM2);

		LCDPTR = 29 - n * 4;
		LCDDAT = 0;

		LCDPTR = 28 - n * 4;
		LCDDAT = ( COM0 + COM1 + COM2);
		break;
	case 'S':
		break;
	case 'T':
		LCDPTR = 31 - n * 4;
		LCDDAT &= ~( COM0 + COM1 + COM2);

		LCDPTR = 30 - n * 4;
		LCDDAT |= COM0;
		LCDDAT &= ~(COM1 + COM2);

		LCDPTR = 29 - n * 4;
		LCDDAT = ( COM1 + COM2);

		LCDPTR = 28 - n * 4;
		LCDDAT = 0;
		break;
	case 'U':
		LCDPTR = 31 - n * 4;
		LCDDAT |= ( COM0 + COM2);
		LCDDAT &= ~ COM1;

		LCDPTR = 30 - n * 4;
		LCDDAT &= ~( COM0 + COM1 + COM2);

		LCDPTR = 29 - n * 4;
		LCDDAT = COM3;

		LCDPTR = 28 - n * 4;
		LCDDAT = ( COM0 + COM3);
		break;
	case 'V':
		LCDPTR = 31 - n * 4;
		LCDDAT &= ~( COM0 + COM1 + COM2);

		LCDPTR = 30 - n * 4;
		LCDDAT |= COM1;
		LCDDAT &= ~(COM0 + COM2);

		LCDPTR = 29 - n * 4;
		LCDDAT = 0;

		LCDPTR = 28 - n * 4;
		LCDDAT = ( COM0 + COM2 + COM3);
		break;
	case 'W':
		LCDPTR = 31 - n * 4;
		LCDDAT |= ( COM0 + COM2);
		LCDDAT &= ~ COM1;

		LCDPTR = 30 - n * 4;
		LCDDAT &= ~( COM0 + COM1 + COM2);

		LCDPTR = 29 - n * 4;
		LCDDAT = ( COM1 + COM2 + COM3);

		LCDPTR = 28 - n * 4;
		LCDDAT = ( COM0 + COM3);
		break;
	case 'X':
		LCDPTR = 31 - n * 4;
		LCDDAT &= ~( COM0 + COM1 + COM2);

		LCDPTR = 30 - n * 4;
		LCDDAT |= ( COM1 + COM2);
		LCDDAT &= ~ COM0;

		LCDPTR = 29 - n * 4;
		LCDDAT = COM0;

		LCDPTR = 28 - n * 4;
		LCDDAT = COM2;
		break;
	case 'Y':
		LCDPTR = 31 - n * 4;
		LCDDAT |= ( COM0 + COM1);
		LCDDAT &= ~ COM2;

		LCDPTR = 30 - n * 4;
		LCDDAT &= ~( COM0 + COM1 + COM2);

		LCDPTR = 29 - n * 4;
		LCDDAT = COM3;

		LCDPTR = 28 - n * 4;
		LCDDAT = ( COM0 + COM1 + COM3);
		break;
	case 'Z':
		LCDPTR = 31 - n * 4;
		LCDDAT |= COM1;
		LCDDAT &= ~(COM0 + COM2);

		LCDPTR = 30 - n * 4;
		LCDDAT |= ( COM0 + COM2);
		LCDDAT &= ~ COM1;

		LCDPTR = 29 - n * 4;
		LCDDAT = ( COM0 + COM3);

		LCDPTR = 28 - n * 4;
		LCDDAT = COM1;
		break;
	case 'a':
		LCDPTR = 31 - n * 4;
		LCDDAT |= ( COM1 + COM2);
		LCDDAT &= ~ COM0;

		LCDPTR = 30 - n * 4;
		LCDDAT |= COM0;
		LCDDAT &= ~(COM1 + COM2);

		LCDPTR = 29 - n * 4;
		LCDDAT = COM3;

		LCDPTR = 28 - n * 4;
		LCDDAT = ( COM0 + COM1 + COM3);
		break;
	case 'b':
		LCDPTR = 31 - n * 4;
		LCDDAT |= ( COM0 + COM1 + COM2);

		LCDPTR = 30 - n * 4;
		LCDDAT &= ~( COM0 + COM1 + COM2);

		LCDPTR = 29 - n * 4;
		LCDDAT = COM3;

		LCDPTR = 28 - n * 4;
		LCDDAT = ( COM1 + COM3);
		break;
	case 'c':
		LCDPTR = 31 - n * 4;
		LCDDAT |= ( COM1 + COM2);
		LCDDAT &= ~ COM0;

		LCDPTR = 30 - n * 4;
		LCDDAT &= ~( COM0 + COM1 + COM2);

		LCDPTR = 29 - n * 4;
		LCDDAT = COM3;

		LCDPTR = 28 - n * 4;
		LCDDAT = COM1;
		break;
	case 'd':
		LCDPTR = 31 - n * 4;
		LCDDAT |= ( COM1 + COM2);
		LCDDAT &= ~ COM0;

		LCDPTR = 30 - n * 4;
		LCDDAT &= ~( COM0 + COM1 + COM2);

		LCDPTR = 29 - n * 4;
		LCDDAT = COM3;

		LCDPTR = 28 - n * 4;
		LCDDAT = ( COM0 + COM1 + COM3);
		break;
	case 'e':
		LCDPTR = 31 - n * 4;
		LCDDAT |= ( COM0 + COM1 + COM2);

		LCDPTR = 30 - n * 4;
		LCDDAT |= COM0;
		LCDDAT &= ~(COM1 + COM2);

		LCDPTR = 29 - n * 4;
		LCDDAT = COM3;

		LCDPTR = 28 - n * 4;
		LCDDAT = ( COM0 + COM1);
		break;
	case 'f':
		LCDPTR = 31 - n * 4;
		LCDDAT |= ( COM0 + COM1 + COM2);

		LCDPTR = 30 - n * 4;
		LCDDAT |= COM0;
		LCDDAT &= ~(COM1 + COM2);

		LCDPTR = 29 - n * 4;
		LCDDAT = 0;

		LCDPTR = 28 - n * 4;
		LCDDAT = 0;
		break;
	case 'g':
		break;
	case 'h':
		LCDPTR = 31 - n * 4;
		LCDDAT |= ( COM0 + COM1 + COM2);

		LCDPTR = 30 - n * 4;
		LCDDAT &= ~( COM0 + COM1 + COM2);

		LCDPTR = 29 - n * 4;
		LCDDAT = 0;

		LCDPTR = 28 - n * 4;
		LCDDAT = ( COM1 + COM3);
		break;
	case 'i':
		LCDPTR = 31 - n * 4;
		LCDDAT &= ~( COM0 + COM1 + COM2);

		LCDPTR = 30 - n * 4;
		LCDDAT &= ~( COM0 + COM1 + COM2);

		LCDPTR = 29 - n * 4;
		LCDDAT = ( COM1 + COM2);

		LCDPTR = 28 - n * 4;
		LCDDAT = 0;
		break;
	case 'j':
		LCDPTR = 31 - n * 4;
		LCDDAT &= ~( COM0 + COM1 + COM2);

		LCDPTR = 30 - n * 4;
		LCDDAT &= ~( COM0 + COM1 + COM2);

		LCDPTR = 29 - n * 4;
		LCDDAT = COM3;

		LCDPTR = 28 - n * 4;
		LCDDAT = ( COM0 + COM3);
		break;
	case 'k':
		LCDPTR = 31 - n * 4;
		LCDDAT |= ( COM0 + COM1 + COM2);

		LCDPTR = 30 - n * 4;
		LCDDAT &= ~( COM0 + COM1 + COM2);

		LCDPTR = 29 - n * 4;
		LCDDAT = COM0;

		LCDPTR = 28 - n * 4;
		LCDDAT = COM2;
		break;
	case 'l':
		break;
	case 'm':
		LCDPTR = 31 - n * 4;
		LCDDAT |= ( COM1 + COM2);
		LCDDAT &= ~ COM0;

		LCDPTR = 30 - n * 4;
		LCDDAT &= ~( COM0 + COM1 + COM2);

		LCDPTR = 29 - n * 4;
		LCDDAT = COM2;

		LCDPTR = 28 - n * 4;
		LCDDAT = ( COM1 + COM3);
		break;
	case 'n':
		LCDPTR = 31 - n * 4;
		LCDDAT |= ( COM1 + COM2);
		LCDDAT &= ~ COM0;

		LCDPTR = 30 - n * 4;
		LCDDAT &= ~( COM0 + COM1 + COM2);

		LCDPTR = 29 - n * 4;
		LCDDAT = 0;

		LCDPTR = 28 - n * 4;
		LCDDAT = ( COM1 + COM3);
		break;
	case 'o':
		LCDPTR = 31 - n * 4;
		LCDDAT |= ( COM1 + COM2);
		LCDDAT &= ~ COM0;

		LCDPTR = 30 - n * 4;
		LCDDAT &= ~( COM0 + COM1 + COM2);

		LCDPTR = 29 - n * 4;
		LCDDAT = COM3;

		LCDPTR = 28 - n * 4;
		LCDDAT = ( COM1 + COM3);
		break;
	case 'p':
		break;
	case 'q':
		LCDPTR = 31 - n * 4;
		LCDDAT |= ( COM0 + COM1);
		LCDDAT &= ~ COM2;

		LCDPTR = 30 - n * 4;
		LCDDAT |= COM0;
		LCDDAT &= ~(COM1 + COM2);

		LCDPTR = 29 - n * 4;
		LCDDAT = 0;

		LCDPTR = 28 - n * 4;
		LCDDAT = ( COM0 + COM1 + COM3);
		break;
	case 'r':
		LCDPTR = 31 - n * 4;
		LCDDAT &= ~( COM0 + COM1 + COM2);

		LCDPTR = 30 - n * 4;
		LCDDAT &= ~( COM0 + COM1 + COM2);

		LCDPTR = 29 - n * 4;
		LCDDAT = COM2;

		LCDPTR = 28 - n * 4;
		LCDDAT = COM1;
		break;
	case 's':
		break;
	case 't':
		LCDPTR = 31 - n * 4;
		LCDDAT |= ( COM0 + COM1 + COM2);

		LCDPTR = 30 - n * 4;
		LCDDAT &= ~( COM0 + COM1 + COM2);

		LCDPTR = 29 - n * 4;
		LCDDAT = COM3;

		LCDPTR = 28 - n * 4;
		LCDDAT = COM1;
		break;
	case 'u':
		LCDPTR = 31 - n * 4;
		LCDDAT |= COM2;
		LCDDAT &= ~(COM0 + COM1);

		LCDPTR = 30 - n * 4;
		LCDDAT &= ~( COM0 + COM1 + COM2);

		LCDPTR = 29 - n * 4;
		LCDDAT = COM3;

		LCDPTR = 28 - n * 4;
		LCDDAT = COM3;
		break;
	case 'v':
		LCDPTR = 31 - n * 4;
		LCDDAT &= ~( COM0 + COM1 + COM2);

		LCDPTR = 30 - n * 4;
		LCDDAT &= ~( COM0 + COM1 + COM2);

		LCDPTR = 29 - n * 4;
		LCDDAT = 0;

		LCDPTR = 28 - n * 4;
		LCDDAT = ( COM2 + COM3);
		break;
	case 'w':
		LCDPTR = 31 - n * 4;
		LCDDAT |= COM2;
		LCDDAT &= ~(COM0 + COM1);

		LCDPTR = 30 - n * 4;
		LCDDAT &= ~( COM0 + COM1 + COM2);

		LCDPTR = 29 - n * 4;
		LCDDAT = ( COM2 + COM3);

		LCDPTR = 28 - n * 4;
		LCDDAT = COM3;
		break;
	case 'x':
		break;
	case 'y':
		LCDPTR = 31 - n * 4;
		LCDDAT &= ~( COM0 + COM1 + COM2);

		LCDPTR = 30 - n * 4;
		LCDDAT |= COM1;
		LCDDAT &= ~(COM0 + COM2);

		LCDPTR = 29 - n * 4;
		LCDDAT = ( COM0 + COM2);

		LCDPTR = 28 - n * 4;
		LCDDAT = 0;
		break;
	case 'z':
		LCDPTR = 31 - n * 4;
		LCDDAT &= ~( COM0 + COM1 + COM2);

		LCDPTR = 30 - n * 4;
		LCDDAT |= ( COM0 + COM2);
		LCDDAT &= ~ COM1;

		LCDPTR = 29 - n * 4;
		LCDDAT = ( COM0 + COM3);

		LCDPTR = 28 - n * 4;
		LCDDAT = 0;
		break;

	}
}

void LCD_ShowString(char *s) {
	uint8_t i = 0;
	uint8_t len = 0;
	BIT b = 0;

	if (s == 0) {
		return;
	}
	len = strlen(s);
	if (len >= 8) {
		for (i = 0; i < 8; i++) {
			LCD_ShowChar(i, *(s + i));
		}
	} else {
		for (i = 0; i < 8; i++) {
			if (b == 0) {
				if (*(s + i) != 0) {
					LCD_ShowChar(i, *(s + i));
				} else {
					b = 1;
					LCD_ShowChar(i, ' ');
				}
			} else {
				LCD_ShowChar(i, ' ');
			}
		}
	}

}
