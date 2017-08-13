/*
 * bsp_display.c
 *
 *  Created on: 2017Äê6ÔÂ26ÈÕ
 *      Author: fly
 */

#include "bsp.h"

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

void LCD_Clear_mi(uint8_t n) {
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
void LCD_Show_mi_(uint8_t n, char c) {
	if (n > 7) {
		return;
	}

	switch (c) {
	case '0':
		LCDPTR = 31 - n * 4;
		LCDDAT = COM0 + COM2;

		LCDPTR = 30 - n * 4;
		LCDDAT = COM0 + COM2;

		LCDPTR = 29 - n * 4;
		LCDDAT = COM0 + COM3;

		LCDPTR = 28 - n * 4;
		LCDDAT = COM0 + COM3;
		break;
	case '1':
		LCDPTR = 31 - n * 4;
		LCDDAT = 0;

		LCDPTR = 30 - n * 4;
		LCDDAT = 0;

		LCDPTR = 29 - n * 4;
		LCDDAT = COM0;

		LCDPTR = 28 - n * 4;
		LCDDAT = COM0 + COM3;
		break;
	case '2':
		LCDPTR = 31 - n * 4;
		LCDDAT = COM1 + COM2;

		LCDPTR = 30 - n * 4;
		LCDDAT = COM0;

		LCDPTR = 29 - n * 4;
		LCDDAT = COM3;

		LCDPTR = 28 - n * 4;
		LCDDAT = COM0 + COM1;
		break;
	case '3':
		LCDPTR = 31 - n * 4;
		LCDDAT = COM1;

		LCDPTR = 30 - n * 4;
		LCDDAT = COM0;

		LCDPTR = 29 - n * 4;
		LCDDAT = COM3;

		LCDPTR = 28 - n * 4;
		LCDDAT = COM0 + COM1 + COM3;
		break;
	case '4':
		LCDPTR = 31 - n * 4;
		LCDDAT = COM0 + COM1;

		LCDPTR = 30 - n * 4;
		LCDDAT = 0;

		LCDPTR = 29 - n * 4;
		LCDDAT = 0;

		LCDPTR = 28 - n * 4;
		LCDDAT = COM0 + COM1 + COM3;
		break;
	case '5':
		LCDPTR = 31 - n * 4;
		LCDDAT = COM0 + COM1;

		LCDPTR = 30 - n * 4;
		LCDDAT = COM0;

		LCDPTR = 29 - n * 4;
		LCDDAT = COM3;

		LCDPTR = 28 - n * 4;
		LCDDAT = COM1 + COM3;
		break;
	case '6':
		LCDPTR = 31 - n * 4;
		LCDDAT = COM0 + COM1 + COM2;

		LCDPTR = 30 - n * 4;
		LCDDAT = COM0;

		LCDPTR = 29 - n * 4;
		LCDDAT = COM3;

		LCDPTR = 28 - n * 4;
		LCDDAT = COM1 + COM3;
		break;
	case '7':
		LCDPTR = 31 - n * 4;
		LCDDAT = 0;

		LCDPTR = 30 - n * 4;
		LCDDAT = COM0;

		LCDPTR = 29 - n * 4;
		LCDDAT = 0;

		LCDPTR = 28 - n * 4;
		LCDDAT = COM0 + COM3;
		break;
	case '8':
		LCDPTR = 31 - n * 4;
		LCDDAT = COM0 + COM1 + COM2;

		LCDPTR = 30 - n * 4;
		LCDDAT = COM0;

		LCDPTR = 29 - n * 4;
		LCDDAT = COM3;

		LCDPTR = 28 - n * 4;
		LCDDAT = COM0 + COM1 + COM3;
		break;
	case '9':
		LCDPTR = 31 - n * 4;
		LCDDAT = COM0 + COM1;

		LCDPTR = 30 - n * 4;
		LCDDAT = COM0;

		LCDPTR = 29 - n * 4;
		LCDDAT = COM3;

		LCDPTR = 28 - n * 4;
		LCDDAT = COM0 + COM1 + COM3;
		break;
	case ' ':
		LCD_Clear_mi(n);
		break;
	case 'A':
		LCDPTR = 31 - n * 4;
		LCDDAT = COM0 + COM1 + COM2;

		LCDPTR = 30 - n * 4;
		LCDDAT = COM0;

		LCDPTR = 29 - n * 4;
		LCDDAT = 0;

		LCDPTR = 28 - n * 4;
		LCDDAT = COM0 + COM1 + COM3;
		break;
	case 'B':
		LCDPTR = 31 - n * 4;
		LCDDAT = 0;

		LCDPTR = 30 - n * 4;
		LCDDAT = COM0;

		LCDPTR = 29 - n * 4;
		LCDDAT = COM1 + COM2 + COM3;

		LCDPTR = 28 - n * 4;
		LCDDAT = COM0 + COM1 + COM3;
		break;
	case 'C':
		LCDPTR = 31 - n * 4;
		LCDDAT = COM0 + COM2;

		LCDPTR = 30 - n * 4;
		LCDDAT = COM0;

		LCDPTR = 29 - n * 4;
		LCDDAT = COM3;

		LCDPTR = 28 - n * 4;
		LCDDAT = 0;
		break;
	case 'D':
		LCDPTR = 31 - n * 4;
		LCDDAT = 0;

		LCDPTR = 30 - n * 4;
		LCDDAT = COM0;

		LCDPTR = 29 - n * 4;
		LCDDAT = COM1 + COM2 + COM3;

		LCDPTR = 28 - n * 4;
		LCDDAT = COM0 + COM3;
		break;
	case 'E':
		LCDPTR = 31 - n * 4;
		LCDDAT = COM0 + COM1 + COM2;

		LCDPTR = 30 - n * 4;
		LCDDAT = COM0;

		LCDPTR = 29 - n * 4;
		LCDDAT = COM3;

		LCDPTR = 28 - n * 4;
		LCDDAT = COM1;
		break;
	case 'F':
		LCDPTR = 31 - n * 4;
		LCDDAT = COM0 + COM1 + COM2;

		LCDPTR = 30 - n * 4;
		LCDDAT = COM0;

		LCDPTR = 29 - n * 4;
		LCDDAT = 0;

		LCDPTR = 28 - n * 4;
		LCDDAT = COM1;
		break;
	case 'G':
		LCDPTR = 31 - n * 4;
		LCDDAT = COM0 + COM2;

		LCDPTR = 30 - n * 4;
		LCDDAT = COM0;

		LCDPTR = 29 - n * 4;
		LCDDAT = COM3;

		LCDPTR = 28 - n * 4;
		LCDDAT = COM1 + COM3;
		break;
	case 'H':
		LCDPTR = 31 - n * 4;
		LCDDAT = COM0 + COM1 + COM2;

		LCDPTR = 30 - n * 4;
		LCDDAT = 0;

		LCDPTR = 29 - n * 4;
		LCDDAT = 0;

		LCDPTR = 28 - n * 4;
		LCDDAT = COM0 + COM1 + COM3;
		break;
	case 'I':

		break;
	case 'J':

		break;
	case 'K':

		break;
	case 'L':

		break;
	case 'M':

		break;
	case 'N':

		break;
	case 'O':

		break;
	case 'P':

		break;
	case 'Q':

		break;
	case 'R':

		break;
	case 'S':

		break;
	case 'T':

		break;
	case 'U':

		break;
	case 'V':

		break;
	case 'W':

		break;
	case 'X':

		break;
	case 'Y':

		break;
	case 'Z':

		break;
	}
}
void LCD_Show_mi(uint8_t n, char c) {
	switch (n) {
	case 0: {
		switch (c) {
		case '0':
			LCDPTR = 31;
			LCDDAT = COM0 + COM2;

			LCDPTR = 30;
			LCDDAT = COM0 + COM2;

			LCDPTR = 29;
			LCDDAT = COM0 + COM3;

			LCDPTR = 28;
			LCDDAT = COM0 + COM3;
			break;
		case '1':
			LCDPTR = 31;
			LCDDAT = 0;

			LCDPTR = 30;
			LCDDAT = 0;

			LCDPTR = 29;
			LCDDAT = COM0;

			LCDPTR = 28;
			LCDDAT = COM0 + COM3;
			break;
		case '2':
			LCDPTR = 31;
			LCDDAT = COM1 + COM2;

			LCDPTR = 30;
			LCDDAT = COM0;

			LCDPTR = 29;
			LCDDAT = COM3;

			LCDPTR = 28;
			LCDDAT = COM0 + COM1;
			break;
		case '3':
			LCDPTR = 31;
			LCDDAT = COM1;

			LCDPTR = 30;
			LCDDAT = COM0;

			LCDPTR = 29;
			LCDDAT = COM3;

			LCDPTR = 28;
			LCDDAT = COM0 + COM1 + COM3;
			break;
		case '4':
			LCDPTR = 31;
			LCDDAT = COM0 + COM1;

			LCDPTR = 30;
			LCDDAT = 0;

			LCDPTR = 29;
			LCDDAT = 0;

			LCDPTR = 28;
			LCDDAT = COM0 + COM1 + COM3;
			break;
		case '5':
			LCDPTR = 31;
			LCDDAT = COM0 + COM1;

			LCDPTR = 30;
			LCDDAT = COM0;

			LCDPTR = 29;
			LCDDAT = COM3;

			LCDPTR = 28;
			LCDDAT = COM1 + COM3;
			break;
		case '6':
			LCDPTR = 31;
			LCDDAT = COM0 + COM1 + COM2;

			LCDPTR = 30;
			LCDDAT = COM0;

			LCDPTR = 29;
			LCDDAT = COM3;

			LCDPTR = 28;
			LCDDAT = COM1 + COM3;
			break;
		case '7':
			LCDPTR = 31;
			LCDDAT = 0;

			LCDPTR = 30;
			LCDDAT = COM0;

			LCDPTR = 29;
			LCDDAT = 0;

			LCDPTR = 28;
			LCDDAT = COM0 + COM3;
			break;
		case '8':
			LCDPTR = 31;
			LCDDAT = COM0 + COM1 + COM2;

			LCDPTR = 30;
			LCDDAT = COM0;

			LCDPTR = 29;
			LCDDAT = COM3;

			LCDPTR = 28;
			LCDDAT = COM0 + COM1 + COM3;
			break;
		case '9':
			LCDPTR = 31;
			LCDDAT = COM0 + COM1;

			LCDPTR = 30;
			LCDDAT = COM0;

			LCDPTR = 29;
			LCDDAT = COM3;

			LCDPTR = 28;
			LCDDAT = COM0 + COM1 + COM3;
			break;
		case ' ':
			LCD_Clear_mi(n);
			break;
		case 'A':

			break;
		case 'B':

			break;
		case 'C':

			break;
		case 'D':

			break;
		case 'E':

			break;
		case 'F':

			break;
		case 'G':

			break;
		}
	}
		break;
	case 1: {
		switch (c) {
		case '0':
			LCDPTR = 27;
			LCDDAT = COM0 + COM2;

			LCDPTR = 26;
			LCDDAT = COM0 + COM2;

			LCDPTR = 25;
			LCDDAT = COM0 + COM3;

			LCDPTR = 24;
			LCDDAT = COM0 + COM3;
			break;
		case '1':
			LCDPTR = 27;
			LCDDAT = 0;

			LCDPTR = 26;
			LCDDAT = 0;

			LCDPTR = 25;
			LCDDAT = COM0;

			LCDPTR = 24;
			LCDDAT = COM0 + COM3;
			break;
		case '2':
			LCDPTR = 27;
			LCDDAT = COM1 + COM2;

			LCDPTR = 26;
			LCDDAT = COM0;

			LCDPTR = 25;
			LCDDAT = COM3;

			LCDPTR = 24;
			LCDDAT = COM0 + COM1;
			break;
		case '3':
			LCDPTR = 27;
			LCDDAT = COM1;

			LCDPTR = 26;
			LCDDAT = COM0;

			LCDPTR = 25;
			LCDDAT = COM3;

			LCDPTR = 24;
			LCDDAT = COM0 + COM1 + COM3;
			break;
		case '4':
			LCDPTR = 27;
			LCDDAT = COM0 + COM1;

			LCDPTR = 26;
			LCDDAT = 0;

			LCDPTR = 25;
			LCDDAT = 0;

			LCDPTR = 24;
			LCDDAT = COM0 + COM1 + COM3;
			break;
		case '5':
			LCDPTR = 27;
			LCDDAT = COM0 + COM1;

			LCDPTR = 26;
			LCDDAT = COM0;

			LCDPTR = 25;
			LCDDAT = COM3;

			LCDPTR = 24;
			LCDDAT = COM1 + COM3;
			break;
		case '6':
			LCDPTR = 27;
			LCDDAT = COM0 + COM1 + COM2;

			LCDPTR = 26;
			LCDDAT = COM0;

			LCDPTR = 25;
			LCDDAT = COM3;

			LCDPTR = 24;
			LCDDAT = COM1 + COM3;
			break;
		case '7':
			LCDPTR = 27;
			LCDDAT = 0;

			LCDPTR = 26;
			LCDDAT = COM0;

			LCDPTR = 25;
			LCDDAT = 0;

			LCDPTR = 24;
			LCDDAT = COM0 + COM3;
			break;
		case '8':
			LCDPTR = 27;
			LCDDAT = COM0 + COM1 + COM2;

			LCDPTR = 26;
			LCDDAT = COM0;

			LCDPTR = 25;
			LCDDAT = COM3;

			LCDPTR = 24;
			LCDDAT = COM0 + COM1 + COM3;
			break;
		case '9':
			LCDPTR = 27;
			LCDDAT = COM0 + COM1;

			LCDPTR = 26;
			LCDDAT = COM0;

			LCDPTR = 25;
			LCDDAT = COM3;

			LCDPTR = 24;
			LCDDAT = COM0 + COM1 + COM3;
			break;
		case ' ':
			LCD_Clear_mi(n);
			break;
		}
	}
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	case 6:
		break;
	case 7:
		break;
	}
}

void LCD_Show_REP_Num(uint8_t num) {
	uint8_t ge;
	uint8_t shi;

	if (num > 99) {
		return;
	}

	shi = num / 10;
	ge = num % 10;
	if (num > 9) {
//		set_SEG14EN;
//		set_SEG15EN;
		switch (shi) {
		case 0:
			LCDPTR = 14;
			LCDDAT = COM1 + COM3;

			LCDPTR = 15;
			LCDDAT = COM0 + COM1 + COM2 + COM3;
			break;
		case 1:
			LCDPTR = 14;
			LCDDAT &= ~(COM1 + COM2 + COM3);

			LCDPTR = 15;
			LCDDAT = COM1 + COM2;
			break;
		case 2:
			LCDPTR = 14;
			LCDDAT = COM2 + COM3;

			LCDPTR = 15;
			LCDDAT = COM0 + COM1 + COM3;
			break;
		case 3:
			LCDPTR = 14;
			LCDDAT = COM2;

			LCDPTR = 15;
			LCDDAT = COM0 + COM1 + COM2 + COM3;
			break;
		case 4:
			LCDPTR = 14;
			LCDDAT = COM1 + COM2;

			LCDPTR = 15;
			LCDDAT = COM1 + COM2;
			break;
		case 5:
			LCDPTR = 14;
			LCDDAT = COM1 + COM2;

			LCDPTR = 15;
			LCDDAT = COM0 + COM2 + COM3;
			break;
		case 6:
			LCDPTR = 14;
			LCDDAT = COM1 + COM2 + COM3;

			LCDPTR = 15;
			LCDDAT = COM0 + COM2 + COM3;
			break;
		case 7:
			LCDPTR = 14;
			LCDDAT &= ~(COM1 + COM2 + COM3);

			LCDPTR = 15;
			LCDDAT = COM0 + COM1 + COM2;
			break;
		case 8:
			LCDPTR = 14;
			LCDDAT = COM1 + COM2 + COM3;

			LCDPTR = 15;
			LCDDAT = COM0 + COM1 + COM2 + COM3;
			break;
		case 9:
			LCDPTR = 14;
			LCDDAT = COM1 + COM2;

			LCDPTR = 15;
			LCDDAT = COM0 + COM1 + COM2 + COM3;
			break;
		}
	} else {
//		clr_SEG14EN;
//		clr_SEG15EN;

		LCDPTR = 14;
		LCDDAT &= ~(COM1 + COM2 + COM3);
//		LCDDAT = COM0 + COM1 + COM2 + COM3;

		LCDPTR = 15;
		LCDDAT = 0;
//		LCDDAT = COM0 + COM1 + COM2 + COM3;
	}
//	set_SEG16EN;
//	set_SEG17EN;
	switch (ge) {
	case 0:
		LCDPTR = 16;
		LCDDAT = COM1 + COM3;

		LCDPTR = 17;
		LCDDAT = COM0 + COM1 + COM2 + COM3;
		break;
	case 1:
		LCDPTR = 16;
		LCDDAT &= ~(COM1 + COM2 + COM3);

		LCDPTR = 17;
		LCDDAT = COM1 + COM2;
		break;
	case 2:
		LCDPTR = 16;
		LCDDAT = COM2 + COM3;

		LCDPTR = 17;
		LCDDAT = COM0 + COM1 + COM3;
		break;
	case 3:
		LCDPTR = 16;
		LCDDAT = COM2;

		LCDPTR = 17;
		LCDDAT = COM0 + COM1 + COM2 + COM3;
		break;
	case 4:
		LCDPTR = 16;
		LCDDAT = COM1 + COM2;

		LCDPTR = 17;
		LCDDAT = COM1 + COM2;
		break;
	case 5:
		LCDPTR = 16;
		LCDDAT = COM1 + COM2;

		LCDPTR = 17;
		LCDDAT = COM0 + COM2 + COM3;
		break;
	case 6:
		LCDPTR = 16;
		LCDDAT = COM1 + COM2 + COM3;

		LCDPTR = 17;
		LCDDAT = COM0 + COM2 + COM3;
		break;
	case 7:
		LCDPTR = 16;
		LCDDAT &= ~(COM1 + COM2 + COM3);

		LCDPTR = 17;
		LCDDAT = COM0 + COM1 + COM2;
		break;
	case 8:
		LCDPTR = 16;
		LCDDAT = COM1 + COM2 + COM3;

		LCDPTR = 17;
		LCDDAT = COM0 + COM1 + COM2 + COM3;
		break;
	case 9:
		LCDPTR = 16;
		LCDDAT = COM1 + COM2;

		LCDPTR = 17;
		LCDDAT = COM0 + COM1 + COM2 + COM3;
		break;
	}
}
void LCD_Clear_ABCD(void) {
//	clr_SEG18EN;
	LCDPTR = 18;
	LCDDAT = 0;
//	LCDDAT = COM0 + COM1 + COM2 + COM3;
}
void LCD_Show_ABCD_all(void) {
//	set_SEG18EN;
	LCDPTR = 18;
	LCDDAT = COM0 + COM1 + COM2 + COM3;
}
void LCD_Show_ABCD(char c) {
//	set_SEG18EN;
	LCDPTR = 18;

	switch (c) {
	case 'A':
		LCDDAT = COM0;
		break;
	case 'B':
		LCDDAT = COM1;
		break;
	case 'C':
		LCDDAT = COM2;
		break;
	case 'D':
		LCDDAT = COM3;
		break;
	default:
//		LCDPTR = 18;
//		LCDDAT = 0;
		break;
	}
}
void LCD_Clear_Pulls_Num(void) {

	LCDPTR = 8;
	LCDDAT &= ~(COM1 + COM2 + COM3);
//	LCDDAT = COM1 + COM2 + COM3;

	LCDPTR = 9;
	LCDDAT = 0;
//	LCDDAT = COM0 + COM1 + COM2 + COM3;

	LCDPTR = 10;
	LCDDAT &= ~(COM1 + COM2 + COM3);
//	LCDDAT = COM1 + COM2 + COM3;

	LCDPTR = 11;
	LCDDAT = 0;
//	LCDDAT = COM0 + COM1 + COM2 + COM3;

	LCDPTR = 12;
	LCDDAT &= ~(COM1 + COM2 + COM3);
//	LCDDAT = COM1 + COM2 + COM3;

	LCDPTR = 13;
	LCDDAT = 0;
//	LCDDAT = COM0 + COM1 + COM2 + COM3;
}
void LCD_Show_Pulls_Num(uint16_t num) {
	uint8_t ge;
	uint8_t shi;
	uint8_t bai;

	if (num > 999) {

		return;
	}
	bai = num / 100;
	shi = num % 100 / 10;
	ge = num % 10;
	if (num > 99) {
//		set_SEG8EN;
//		set_SEG9EN;

		switch (bai) {
		case 0:
			LCDPTR = 8;
			LCDDAT = COM1 + COM3;

			LCDPTR = 9;
			LCDDAT = COM0 + COM1 + COM2 + COM3;
			break;
		case 1:
			LCDPTR = 8;
			LCDDAT &= ~(COM1 + COM2 + COM3);

			LCDPTR = 9;
			LCDDAT = COM1 + COM2;
			break;
		case 2:
			LCDPTR = 8;
			LCDDAT = COM2 + COM3;

			LCDPTR = 9;
			LCDDAT = COM0 + COM1 + COM3;
			break;
		case 3:
			LCDPTR = 8;
			LCDDAT = COM2;

			LCDPTR = 9;
			LCDDAT = COM0 + COM1 + COM2 + COM3;
			break;
		case 4:
			LCDPTR = 8;
			LCDDAT = COM1 + COM2;

			LCDPTR = 9;
			LCDDAT = COM1 + COM2;
			break;
		case 5:
			LCDPTR = 8;
			LCDDAT = COM1 + COM2;

			LCDPTR = 9;
			LCDDAT = COM0 + COM2 + COM3;
			break;
		case 6:
			LCDPTR = 8;
			LCDDAT = COM1 + COM2 + COM3;

			LCDPTR = 9;
			LCDDAT = COM0 + COM2 + COM3;
			break;
		case 7:
			LCDPTR = 8;
			LCDDAT &= ~(COM1 + COM2 + COM3);

			LCDPTR = 9;
			LCDDAT = COM0 + COM1 + COM2;
			break;
		case 8:
			LCDPTR = 8;
			LCDDAT = COM1 + COM2 + COM3;

			LCDPTR = 9;
			LCDDAT = COM0 + COM1 + COM2 + COM3;
			break;
		case 9:
			LCDPTR = 8;
			LCDDAT = COM1 + COM2;

			LCDPTR = 9;
			LCDDAT = COM0 + COM1 + COM2 + COM3;
			break;
		}
	} else {
		LCDPTR = 8;
		LCDDAT &= ~(COM1 + COM2 + COM3);

		LCDPTR = 9;
		LCDDAT = 0;
	}
	if (num > 9) {
		set_SEG10EN;
		set_SEG11EN;

		switch (shi) {
		case 0:
			LCDPTR = 10;
			LCDDAT = COM1 + COM3;

			LCDPTR = 11;
			LCDDAT = COM0 + COM1 + COM2 + COM3;
			break;
		case 1:
			LCDPTR = 10;
			LCDDAT &= ~(COM1 + COM2 + COM3);

			LCDPTR = 11;
			LCDDAT = COM1 + COM2;
			break;
		case 2:
			LCDPTR = 10;
			LCDDAT = COM2 + COM3;

			LCDPTR = 11;
			LCDDAT = COM0 + COM1 + COM3;
			break;
		case 3:
			LCDPTR = 10;
			LCDDAT = COM2;

			LCDPTR = 11;
			LCDDAT = COM0 + COM1 + COM2 + COM3;
			break;
		case 4:
			LCDPTR = 10;
			LCDDAT = COM1 + COM2;

			LCDPTR = 11;
			LCDDAT = COM1 + COM2;
			break;
		case 5:
			LCDPTR = 10;
			LCDDAT = COM1 + COM2;

			LCDPTR = 11;
			LCDDAT = COM0 + COM2 + COM3;
			break;
		case 6:
			LCDPTR = 10;
			LCDDAT = COM1 + COM2 + COM3;

			LCDPTR = 11;
			LCDDAT = COM0 + COM2 + COM3;
			break;
		case 7:
			LCDPTR = 10;
			LCDDAT &= ~(COM1 + COM2 + COM3);

			LCDPTR = 11;
			LCDDAT = COM0 + COM1 + COM2;
			break;
		case 8:
			LCDPTR = 10;
			LCDDAT = COM1 + COM2 + COM3;

			LCDPTR = 11;
			LCDDAT = COM0 + COM1 + COM2 + COM3;
			break;
		case 9:
			LCDPTR = 10;
			LCDDAT = COM1 + COM2;

			LCDPTR = 11;
			LCDDAT = COM0 + COM1 + COM2 + COM3;
			break;
		}
	} else {
//		clr_SEG10EN;
//		clr_SEG11EN;
		LCDPTR = 10;
		LCDDAT &= ~(COM1 + COM2 + COM3);

		LCDPTR = 11;
		LCDDAT = 0;
	}
//	set_SEG12EN;
//	set_SEG13EN;
	switch (ge) {
	case 0:
		LCDPTR = 12;
		LCDDAT = COM1 + COM3;

		LCDPTR = 13;
		LCDDAT = COM0 + COM1 + COM2 + COM3;
		break;
	case 1:
		LCDPTR = 12;
		LCDDAT &= ~(COM1 + COM2 + COM3);

		LCDPTR = 13;
		LCDDAT = COM1 + COM2;
		break;
	case 2:
		LCDPTR = 12;
		LCDDAT = COM2 + COM3;

		LCDPTR = 13;
		LCDDAT = COM0 + COM1 + COM3;
		break;
	case 3:
		LCDPTR = 12;
		LCDDAT = COM2;

		LCDPTR = 13;
		LCDDAT = COM0 + COM1 + COM2 + COM3;
		break;
	case 4:
		LCDPTR = 12;
		LCDDAT = COM1 + COM2;

		LCDPTR = 13;
		LCDDAT = COM1 + COM2;
		break;
	case 5:
		LCDPTR = 12;
		LCDDAT = COM1 + COM2;

		LCDPTR = 13;
		LCDDAT = COM0 + COM2 + COM3;
		break;
	case 6:
		LCDPTR = 12;
		LCDDAT = COM1 + COM2 + COM3;

		LCDPTR = 13;
		LCDDAT = COM0 + COM2 + COM3;
		break;
	case 7:
		LCDPTR = 12;
		LCDDAT &= ~(COM1 + COM2 + COM3);

		LCDPTR = 13;
		LCDDAT = COM0 + COM1 + COM2;
		break;
	case 8:
		LCDPTR = 12;
		LCDDAT = COM1 + COM2 + COM3;

		LCDPTR = 13;
		LCDDAT = COM0 + COM1 + COM2 + COM3;
		break;
	case 9:
		LCDPTR = 12;
		LCDDAT = COM1 + COM2;

		LCDPTR = 13;
		LCDDAT = COM0 + COM1 + COM2 + COM3;
		break;
	}
}
void LCD_Clear_QS_ICO(void) {
//	clr_SEG2EN;
	LCDPTR = 2;
	LCDDAT &= ~ COM0;
}
void LCD_Show_QS_ICO(void) {
//	set_SEG2EN;
	LCDPTR = 2;
	LCDDAT |= COM0;
}
void LCD_Clear_COACH_ICO(void) {
//	clr_SEG4EN;
	LCDPTR = 4;
	LCDDAT &= ~COM0;
}
void LCD_Show_COACH_ICO(void) {
//	set_SEG4EN;
	LCDPTR = 4;
	LCDDAT = COM0;
}
void LCD_Clear_Line_down(void) {
//	clr_SEG8EN;
	LCDPTR = 8;
	LCDDAT &= ~COM0;
}
void LCD_Show_Line_down(void) {
//	set_SEG8EN;
	LCDPTR = 8;
	LCDDAT |= COM0;
}
void LCD_Clear_Heart_ICO(void) {
//	clr_SEG0EN;
	LCDPTR = 0;
	LCDDAT &= ~COM0;
}
void LCD_Show_Heart_ICO(void) {
//	set_SEG0EN;
	LCDPTR = 0;
	LCDDAT |= COM0;
}
void LCD_Clear_CAL_Num(void) {

	LCDPTR = 0;
	LCDDAT &= ~(COM1 + COM2 + COM3);
//	LCDDAT = COM1 + COM2 + COM3;

	LCDPTR = 1;
	LCDDAT = 0;
//	LCDDAT = COM0 + COM1 + COM2 + COM3;

	LCDPTR = 2;
	LCDDAT &= ~(COM1 + COM2 + COM3);
//	LCDDAT = COM1 + COM2 + COM3;

	LCDPTR = 3;
	LCDDAT = 0;
//	LCDDAT = COM0 + COM1 + COM2 + COM3;

	LCDPTR = 4;
	LCDDAT &= ~(COM1 + COM2 + COM3);
//	LCDDAT = COM1 + COM2 + COM3;

	LCDPTR = 5;
	LCDDAT = 0;
//	LCDDAT = COM0 + COM1 + COM2 + COM3;

	LCDPTR = 6;
	LCDDAT &= ~(COM1 + COM2 + COM3);
//	LCDDAT = COM1 + COM2 + COM3;

	LCDPTR = 7;
	LCDDAT = 0;
//	LCDDAT = COM0 + COM1 + COM2 + COM3;
}
void LCD_Show_CAL_Num(uint16_t num) {
	uint8_t ge;
	uint8_t shi;
	uint8_t bai;
	uint8_t qian;

	if (num > 9999) {
		return;
	}
	qian = num / 1000;
	bai = num % 1000 / 100;
	shi = num % 100 / 10;
	ge = num % 10;
	if (num > 999) {
//		set_SEG0EN;
//		set_SEG1EN;

		switch (qian) {
		case 0:
			LCDPTR = 0;
			LCDDAT = COM1 + COM3;

			LCDPTR = 1;
			LCDDAT = COM0 + COM1 + COM2 + COM3;
			break;
		case 1:
			LCDPTR = 0;
			LCDDAT &= ~(COM1 + COM2 + COM3);

			LCDPTR = 1;
			LCDDAT = COM1 + COM2;
			break;
		case 2:
			LCDPTR = 0;
			LCDDAT = COM2 + COM3;

			LCDPTR = 1;
			LCDDAT = COM0 + COM1 + COM3;
			break;
		case 3:
			LCDPTR = 0;
			LCDDAT = COM2;

			LCDPTR = 1;
			LCDDAT = COM0 + COM1 + COM2 + COM3;
			break;
		case 4:
			LCDPTR = 0;
			LCDDAT = COM1 + COM2;

			LCDPTR = 1;
			LCDDAT = COM1 + COM2;
			break;
		case 5:
			LCDPTR = 0;
			LCDDAT = COM1 + COM2;

			LCDPTR = 1;
			LCDDAT = COM0 + COM2 + COM3;
			break;
		case 6:
			LCDPTR = 0;
			LCDDAT = COM1 + COM2 + COM3;

			LCDPTR = 1;
			LCDDAT = COM0 + COM2 + COM3;
			break;
		case 7:
			LCDPTR = 0;
			LCDDAT &= ~(COM1 + COM2 + COM3);

			LCDPTR = 1;
			LCDDAT = COM0 + COM1 + COM2;
			break;
		case 8:
			LCDPTR = 0;
			LCDDAT = COM1 + COM2 + COM3;

			LCDPTR = 1;
			LCDDAT = COM0 + COM1 + COM2 + COM3;
			break;
		case 9:
			LCDPTR = 0;
			LCDDAT = COM1 + COM2;

			LCDPTR = 1;
			LCDDAT = COM0 + COM1 + COM2 + COM3;
			break;
		}
	} else {
		LCDPTR = 0;
		LCDDAT &= ~(COM1 + COM2 + COM3);

		LCDPTR = 1;
		LCDDAT = 0;
	}
	if (num > 99) {

		switch (bai) {
		case 0:
			LCDPTR = 2;
			LCDDAT = COM1 + COM3;

			LCDPTR = 3;
			LCDDAT = COM0 + COM1 + COM2 + COM3;
			break;
		case 1:
			LCDPTR = 2;
			LCDDAT &= ~(COM1 + COM2 + COM3);

			LCDPTR = 3;
			LCDDAT = COM1 + COM2;
			break;
		case 2:
			LCDPTR = 2;
			LCDDAT = COM2 + COM3;

			LCDPTR = 3;
			LCDDAT = COM0 + COM1 + COM3;
			break;
		case 3:
			LCDPTR = 2;
			LCDDAT = COM2;

			LCDPTR = 3;
			LCDDAT = COM0 + COM1 + COM2 + COM3;
			break;
		case 4:
			LCDPTR = 2;
			LCDDAT = COM1 + COM2;

			LCDPTR = 3;
			LCDDAT = COM1 + COM2;
			break;
		case 5:
			LCDPTR = 2;
			LCDDAT = COM1 + COM2;

			LCDPTR = 3;
			LCDDAT = COM0 + COM2 + COM3;
			break;
		case 6:
			LCDPTR = 2;
			LCDDAT = COM1 + COM2 + COM3;

			LCDPTR = 3;
			LCDDAT = COM0 + COM2 + COM3;
			break;
		case 7:
			LCDPTR = 2;
			LCDDAT &= ~(COM1 + COM2 + COM3);

			LCDPTR = 3;
			LCDDAT = COM0 + COM1 + COM2;
			break;
		case 8:
			LCDPTR = 2;
			LCDDAT = COM1 + COM2 + COM3;

			LCDPTR = 3;
			LCDDAT = COM0 + COM1 + COM2 + COM3;
			break;
		case 9:
			LCDPTR = 2;
			LCDDAT = COM1 + COM2;

			LCDPTR = 3;
			LCDDAT = COM0 + COM1 + COM2 + COM3;
			break;
		}
	} else {
//		clr_SEG2EN;
//		clr_SEG3EN;
		LCDPTR = 2;
		LCDDAT &= ~(COM1 + COM2 + COM3);

		LCDPTR = 3;
		LCDDAT = 0;
	}
	if (num > 9) {
//		set_SEG4EN;
//		set_SEG5EN;

		switch (shi) {
		case 0:
			LCDPTR = 4;
			LCDDAT = COM1 + COM3;

			LCDPTR = 5;
			LCDDAT = COM0 + COM1 + COM2 + COM3;
			break;
		case 1:
			LCDPTR = 4;
			LCDDAT &= ~(COM1 + COM2 + COM3);

			LCDPTR = 5;
			LCDDAT = COM1 + COM2;
			break;
		case 2:
			LCDPTR = 4;
			LCDDAT = COM2 + COM3;

			LCDPTR = 5;
			LCDDAT = COM0 + COM1 + COM3;
			break;
		case 3:
			LCDPTR = 4;
			LCDDAT = COM2;

			LCDPTR = 5;
			LCDDAT = COM0 + COM1 + COM2 + COM3;
			break;
		case 4:
			LCDPTR = 4;
			LCDDAT = COM1 + COM2;

			LCDPTR = 5;
			LCDDAT = COM1 + COM2;
			break;
		case 5:
			LCDPTR = 4;
			LCDDAT = COM1 + COM2;

			LCDPTR = 5;
			LCDDAT = COM0 + COM2 + COM3;
			break;
		case 6:
			LCDPTR = 4;
			LCDDAT = COM1 + COM2 + COM3;

			LCDPTR = 5;
			LCDDAT = COM0 + COM2 + COM3;
			break;
		case 7:
			LCDPTR = 4;
			LCDDAT &= ~(COM1 + COM2 + COM3);

			LCDPTR = 5;
			LCDDAT = COM0 + COM1 + COM2;
			break;
		case 8:
			LCDPTR = 4;
			LCDDAT = COM1 + COM2 + COM3;

			LCDPTR = 5;
			LCDDAT = COM0 + COM1 + COM2 + COM3;
			break;
		case 9:
			LCDPTR = 4;
			LCDDAT = COM1 + COM2;

			LCDPTR = 5;
			LCDDAT = COM0 + COM1 + COM2 + COM3;
			break;
		}
	} else {
//		clr_SEG4EN;
//		clr_SEG5EN;
		LCDPTR = 4;
		LCDDAT &= ~(COM1 + COM2 + COM3);

		LCDPTR = 5;
		LCDDAT = 0;
	}

//	set_SEG6EN;
//	set_SEG7EN;
	switch (ge) {
	case 0:
		LCDPTR = 6;
		LCDDAT = COM1 + COM3;

		LCDPTR = 7;
		LCDDAT = COM0 + COM1 + COM2 + COM3;
		break;
	case 1:
		LCDPTR = 6;
		LCDDAT &= ~(COM1 + COM2 + COM3);

		LCDPTR = 7;
		LCDDAT = COM1 + COM2;
		break;
	case 2:
		LCDPTR = 6;
		LCDDAT = COM2 + COM3;

		LCDPTR = 7;
		LCDDAT = COM0 + COM1 + COM3;
		break;
	case 3:
		LCDPTR = 6;
		LCDDAT = COM2;

		LCDPTR = 7;
		LCDDAT = COM0 + COM1 + COM2 + COM3;
		break;
	case 4:
		LCDPTR = 6;
		LCDDAT = COM1 + COM2;

		LCDPTR = 7;
		LCDDAT = COM1 + COM2;
		break;
	case 5:
		LCDPTR = 6;
		LCDDAT = COM1 + COM2;

		LCDPTR = 7;
		LCDDAT = COM0 + COM2 + COM3;
		break;
	case 6:
		LCDPTR = 6;
		LCDDAT = COM1 + COM2 + COM3;

		LCDPTR = 7;
		LCDDAT = COM0 + COM2 + COM3;
		break;
	case 7:
		LCDPTR = 6;
		LCDDAT &= ~(COM1 + COM2 + COM3);

		LCDPTR = 7;
		LCDDAT = COM0 + COM1 + COM2;
		break;
	case 8:
		LCDPTR = 6;
		LCDDAT = COM1 + COM2 + COM3;

		LCDPTR = 7;
		LCDDAT = COM0 + COM1 + COM2 + COM3;
		break;
	case 9:
		LCDPTR = 6;
		LCDDAT = COM1 + COM2;

		LCDPTR = 7;
		LCDDAT = COM0 + COM1 + COM2 + COM3;
		break;
	}
}
void LCD_Clear_CAL_ICO(void) {
//	clr_SEG6EN;
	LCDPTR = 6;
	LCDDAT &= ~ COM0;
}
void LCD_Show_CAL_ICO(void) {
//	set_SEG6EN;
	LCDPTR = 6;
	LCDDAT |= COM0;
}

