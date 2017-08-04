/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2015 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

//***********************************************************************************************************
//  Nuvoton Technoledge Corp. 
//  Website: http://www.nuvoton.com
//  E-Mail : MicroC-8bit@nuvoton.com
//  Date   : Jan/07/2015
//***********************************************************************************************************
#include <stdio.h>
#include <N76E616.h>
#include "Version.h"
#include "Typedef.h"
#include "Define.h"
#include "SFR_Macro.h"
#include "Common.h"
#include "Delay.h"
#include "Display.h"

void LCD_Initial(void) {
	//step1: enable clock source
	clr_EXTEN1
	;
	set_EXTEN0
	;

	//step2: check ready
	while ((CKSWT & SET_BIT6) == 0)
		;

	LCDCLK = 0x13;      //;Select LXT as LCD clock source

	Set_All_GPIO_Input_Mode();

	LCDCON = 0x40;      //;VLCD = 0.9VDD (VDD = 3.3V, VLCD = 3.0V)
						//;1/4 duty, 1/3 bias, 150kO resistor ladder

	LCDSEG0 = 0xff; //Enable all segments except SEG29 and SEG30(shared with LXT's Xin and Xout)
	LCDSEG1 = 0xff;
	LCDSEG2 = 0xff;
	LCDSEG3 = 0x9f;

	LCDCON |= SET_BIT7;  //LCDEN = 1
}

void LCD_Display_All_Clear() {
	unsigned char i;

	for (i = 0; i < 32; i++)       //clear all previous pattern
			{
		LCDPTR = i;
		LCDDAT = 0;
	}
}

void LCD_Try_Run() {
	unsigned char j;

	for (j = 0; j < 32; j++) {
		LCDPTR = j;
		LCDDAT = 0xff;
	}
	Timer0_Delay1ms(1000);

	LCD_Blank();
	LCD_Blank();

	for (j = 0; j < 10; j++) {
		LCD_Display_All_Clear();
		LCD_Display_Num_1(j);
		LCD_Display_Num_2(j);
		LCD_Display_Num_3(j);
		LCD_Display_Num_4(j);
		LCD_Display_Num_5(j);
		LCD_Display_Num_6(j);
		LCD_Display_Num_7(j);
		Timer0_Delay1ms(300);
	}
	LCD_Blank();
	Timer0_Delay1ms(500);
}

void LCD_Blank() {
	LCDSEG0 = 0x00;
	LCDSEG1 = 0x00;
	LCDSEG2 = 0x00;
	LCDSEG3 = 0x00;

	Timer0_Delay1ms(500);

	LCDSEG0 = 0xff;
	LCDSEG1 = 0xff;
	LCDSEG2 = 0xff;
	LCDSEG3 = 0x9f;

	Timer0_Delay1ms(500);
}

void LCD_Display_Num_1(unsigned char u8Num_1) {
	switch (u8Num_1) {
	case E_NUM_0:    //show "0" -- 1'st 14seg Display
	{
		LCDPTR = 0;
		LCDDAT = (COM0 + COM1 + COM2 + COM3);

		LCDPTR = 28;
		LCDDAT = (COM1 + COM2);
	}
		break;

	case E_NUM_1:    //show "1" -- 1'st 14seg Display
	{
		LCDPTR = 0;
		LCDDAT = (COM1 + COM2);
	}
		break;

	case E_NUM_2:    //show "2" -- 1'st 14seg Display
	{
		LCDPTR = 0;
		LCDDAT = (COM0 + COM2 + COM3);

		LCDPTR = 31;
		LCDDAT = COM2;

		LCDPTR = 1;
		LCDDAT = COM1;

		LCDPTR = 28;
		LCDDAT = COM1;
	}
		break;

	case E_NUM_3:    //show "3" -- 1'st 14seg Display
	{
		LCDPTR = 0;
		LCDDAT = (COM0 + COM1 + COM2 + COM3);

		LCDPTR = 31;
		LCDDAT = COM2;

		LCDPTR = 1;
		LCDDAT = COM1;
	}
		break;

	case E_NUM_4:    //show "4" -- 1'st 14seg Display
	{
		LCDPTR = 28;
		LCDDAT = COM2;

		LCDPTR = 31;
		LCDDAT = COM2;

		LCDPTR = 1;
		LCDDAT = COM1;

		LCDPTR = 0;
		LCDDAT = (COM1 + COM2);
	}
		break;

	case E_NUM_5:    //show "5" -- 1'st 14seg Display
	{
		LCDPTR = 0;
		LCDDAT = (COM0 + COM1 + COM3);

		LCDPTR = 31;
		LCDDAT = COM2;

		LCDPTR = 1;
		LCDDAT = COM1;

		LCDPTR = 28;
		LCDDAT = COM2;
	}
		break;

	case E_NUM_6:    //show "6" -- 1'st 14seg Display
	{
		LCDPTR = 0;
		LCDDAT = (COM0 + COM1 + COM3);

		LCDPTR = 28;
		LCDDAT = (COM1 + COM2);

		LCDPTR = 31;
		LCDDAT = COM2;

		LCDPTR = 1;
		LCDDAT = COM1;
	}
		break;

	case E_NUM_7:    //show "7" -- 1'st 14seg Display
	{
		LCDPTR = 0;
		LCDDAT = (COM1 + COM2 + COM3);

		LCDPTR = 28;
		LCDDAT = COM2;
	}
		break;

	case E_NUM_8:    //show "8" -- 1'st 14seg Display
	{
		LCDPTR = 0;
		LCDDAT = (COM0 + COM1 + COM2 + COM3);

		LCDPTR = 28;
		LCDDAT = (COM1 + COM2);

		LCDPTR = 31;
		LCDDAT = COM2;

		LCDPTR = 1;
		LCDDAT = COM1;
	}
		break;

	case E_NUM_9:    //show "9" -- 1'st 14seg Display
	{
		LCDPTR = 0;
		LCDDAT = (COM0 + COM1 + COM2 + COM3);

		LCDPTR = 28;
		LCDDAT = COM2;

		LCDPTR = 31;
		LCDDAT = COM2;

		LCDPTR = 1;
		LCDDAT = COM1;
	}
		break;
	}
}

void LCD_Display_Num_2(unsigned char u8Num_2) {
	switch (u8Num_2) {
	case E_NUM_0:    //show "0" -- 2'nd 14seg Display
	{
		LCDPTR = 4;
		LCDDAT = (COM0 + COM1 + COM2 + COM3);

		LCDPTR = 2;
		LCDDAT = (COM1 + COM2);
	}
		break;

	case E_NUM_1:    //show "1" -- 2'nd 14seg Display
	{
		LCDPTR = 4;
		LCDDAT = (COM1 + COM2);
	}
		break;

	case E_NUM_2:    //show "2" -- 2'nd 14seg Display
	{
		LCDPTR = 4;
		LCDDAT = (COM0 + COM2 + COM3);

		LCDPTR = 5;
		LCDDAT = COM1;

		LCDPTR = 3;
		LCDDAT = COM2;

		LCDPTR = 2;
		LCDDAT = COM1;
	}
		break;

	case E_NUM_3:    //show "3" -- 2'nd 14seg Display
	{
		LCDPTR = 4;
		LCDDAT = (COM0 + COM1 + COM2 + COM3);

		LCDPTR = 5;
		LCDDAT = COM1;

		LCDPTR = 3;
		LCDDAT = COM2;
	}
		break;

	case E_NUM_4:    //show "4" -- 2'nd 14seg Display
	{
		LCDPTR = 2;
		LCDDAT = COM2;

		LCDPTR = 3;
		LCDDAT = COM2;

		LCDPTR = 5;
		LCDDAT = COM1;

		LCDPTR = 4;
		LCDDAT = (COM1 + COM2);
	}
		break;

	case E_NUM_5:    //show "5" -- 2'nd 14seg Display
	{
		LCDPTR = 4;
		LCDDAT = (COM0 + COM1 + COM3);

		LCDPTR = 2;
		LCDDAT = COM2;

		LCDPTR = 3;
		LCDDAT = COM2;

		LCDPTR = 5;
		LCDDAT = COM1;
	}
		break;

	case E_NUM_6:    //show "6" -- 2'nd 14seg Display
	{
		LCDPTR = 4;
		LCDDAT = (COM0 + COM1 + COM3);

		LCDPTR = 2;
		LCDDAT = (COM1 + COM2);

		LCDPTR = 3;
		LCDDAT = COM2;

		LCDPTR = 5;
		LCDDAT = COM1;
	}
		break;

	case E_NUM_7:    //show "7" -- 2'nd 14seg Display
	{
		LCDPTR = 4;
		LCDDAT = (COM1 + COM2 + COM3);

		LCDPTR = 2;
		LCDDAT = COM2;
	}
		break;

	case E_NUM_8:    //show "8" -- 2'nd 14seg Display
	{
		LCDPTR = 4;
		LCDDAT = (COM0 + COM1 + COM2 + COM3);

		LCDPTR = 2;
		LCDDAT = (COM1 + COM2);

		LCDPTR = 3;
		LCDDAT = COM2;

		LCDPTR = 5;
		LCDDAT = COM1;
	}
		break;

	case E_NUM_9:    //show "9" -- 2'nd 14seg Display
	{
		LCDPTR = 4;
		LCDDAT = (COM0 + COM1 + COM2 + COM3);

		LCDPTR = 2;
		LCDDAT = COM2;

		LCDPTR = 3;
		LCDDAT = COM2;

		LCDPTR = 5;
		LCDDAT = COM1;
	}
		break;
	}
}

void LCD_Display_Num_3(unsigned char u8Num_3) {
	switch (u8Num_3) {
	case E_NUM_0:    //show "0" -- 3'rd 14seg Display
	{
		LCDPTR = 8;
		LCDDAT = (COM0 + COM1 + COM2 + COM3);

		LCDPTR = 6;
		LCDDAT = (COM1 + COM2);
	}
		break;

	case E_NUM_1:    //show "1" -- 3'rd 14seg Display
	{
		LCDPTR = 8;
		LCDDAT = (COM1 + COM2);
	}
		break;

	case E_NUM_2:    //show "2" -- 3'rd 14seg Display
	{
		LCDPTR = 8;
		LCDDAT = (COM0 + COM2 + COM3);

		LCDPTR = 9;
		LCDDAT = COM1;

		LCDPTR = 7;
		LCDDAT = COM2;

		LCDPTR = 6;
		LCDDAT = COM1;
	}
		break;

	case E_NUM_3:    //show "3" -- 3'rd 14seg Display
	{
		LCDPTR = 8;
		LCDDAT = (COM0 + COM1 + COM2 + COM3);

		LCDPTR = 9;
		LCDDAT = COM1;

		LCDPTR = 7;
		LCDDAT = COM2;
	}
		break;

	case E_NUM_4:    //show "4" -- 3'rd 14seg Display
	{
		LCDPTR = 6;
		LCDDAT = COM2;

		LCDPTR = 9;
		LCDDAT = COM1;

		LCDPTR = 7;
		LCDDAT = COM2;

		LCDPTR = 8;
		LCDDAT = (COM1 + COM2);
	}
		break;

	case E_NUM_5:    //show "5" -- 3'rd 14seg Display
	{
		LCDPTR = 8;
		LCDDAT = (COM0 + COM1 + COM3);

		LCDPTR = 6;
		LCDDAT = COM2;

		LCDPTR = 9;
		LCDDAT = COM1;

		LCDPTR = 7;
		LCDDAT = COM2;
	}
		break;

	case E_NUM_6:    //show "6" -- 3'rd 14seg Display
	{
		LCDPTR = 8;
		LCDDAT = (COM0 + COM1 + COM3);

		LCDPTR = 6;
		LCDDAT = (COM1 + COM2);

		LCDPTR = 9;
		LCDDAT = COM1;

		LCDPTR = 7;
		LCDDAT = COM2;
	}
		break;

	case E_NUM_7:    //show "7" -- 3'rd 14seg Display
	{
		LCDPTR = 8;
		LCDDAT = (COM1 + COM2 + COM3);

		LCDPTR = 6;
		LCDDAT = COM2;
	}
		break;

	case E_NUM_8:    //show "8" -- 3'rd 14seg Display
	{
		LCDPTR = 8;
		LCDDAT = (COM0 + COM1 + COM2 + COM3);

		LCDPTR = 6;
		LCDDAT = (COM1 + COM2);

		LCDPTR = 9;
		LCDDAT = COM1;

		LCDPTR = 7;
		LCDDAT = COM2;
	}
		break;

	case E_NUM_9:    //show "9" -- 3'rd 14seg Display
	{
		LCDPTR = 8;
		LCDDAT = (COM0 + COM1 + COM2 + COM3);

		LCDPTR = 6;
		LCDDAT = COM2;

		LCDPTR = 9;
		LCDDAT = COM1;

		LCDPTR = 7;
		LCDDAT = COM2;
	}
		break;
	}
}

void LCD_Display_Num_4(unsigned char u8Num_4) {
	switch (u8Num_4) {
	case E_NUM_0:    //show "0" -- 4'th 14seg Display
	{
		LCDPTR = 12;
		LCDDAT = (COM0 + COM1 + COM2 + COM3);

		LCDPTR = 10;
		LCDDAT = (COM1 + COM2);
	}
		break;

	case E_NUM_1:    //show "1" -- 4'th 14seg Display
	{
		LCDPTR = 12;
		LCDDAT = (COM1 + COM2);
	}
		break;

	case E_NUM_2:    //show "2" -- 4'th 14seg Display
	{
		LCDPTR = 12;
		LCDDAT = (COM0 + COM2 + COM3);

		LCDPTR = 13;
		LCDDAT = COM1;

		LCDPTR = 11;
		LCDDAT = COM2;

		LCDPTR = 10;
		LCDDAT = COM1;
	}
		break;

	case E_NUM_3:    //show "3" -- 4'th 14seg Display
	{
		LCDPTR = 12;
		LCDDAT = (COM0 + COM1 + COM2 + COM3);

		LCDPTR = 13;
		LCDDAT = COM1;

		LCDPTR = 11;
		LCDDAT = COM2;
	}
		break;

	case E_NUM_4:    //show "4" -- 4'th 14seg Display
	{
		LCDPTR = 10;
		LCDDAT = COM2;

		LCDPTR = 13;
		LCDDAT = COM1;

		LCDPTR = 11;
		LCDDAT = COM2;

		LCDPTR = 12;
		LCDDAT = (COM1 + COM2);
	}
		break;

	case E_NUM_5:    //show "5" -- 4'th 14seg Display
	{
		LCDPTR = 12;
		LCDDAT = (COM0 + COM1 + COM3);

		LCDPTR = 10;
		LCDDAT = COM2;

		LCDPTR = 13;
		LCDDAT = COM1;

		LCDPTR = 11;
		LCDDAT = COM2;
	}
		break;

	case E_NUM_6:    //show "6" -- 4'th 14seg Display
	{
		LCDPTR = 12;
		LCDDAT = (COM0 + COM1 + COM3);

		LCDPTR = 10;
		LCDDAT = (COM1 + COM2);

		LCDPTR = 13;
		LCDDAT = COM1;

		LCDPTR = 11;
		LCDDAT = COM2;
	}
		break;

	case E_NUM_7:    //show "7" -- 4'th 14seg Display
	{
		LCDPTR = 10;
		LCDDAT = COM2;

		LCDPTR = 12;
		LCDDAT = (COM1 + COM2 + COM3);

	}
		break;

	case E_NUM_8:    //show "8" -- 4'th 14seg Display
	{
		LCDPTR = 12;
		LCDDAT = (COM0 + COM1 + COM2 + COM3);

		LCDPTR = 10;
		LCDDAT = (COM1 + COM2);

		LCDPTR = 13;
		LCDDAT = COM1;

		LCDPTR = 11;
		LCDDAT = COM2;
	}
		break;

	case E_NUM_9:    //show "9" -- 4'th 14seg Display
	{
		LCDPTR = 12;
		LCDDAT = (COM0 + COM1 + COM2 + COM3);

		LCDPTR = 10;
		LCDDAT = COM2;

		LCDPTR = 13;
		LCDDAT = COM1;

		LCDPTR = 11;
		LCDDAT = COM2;
	}
		break;
	}
}

void LCD_Display_Num_5(unsigned char u8Num_5) {
	switch (u8Num_5) {
	case E_NUM_0:    //show "0" -- 5'th 14seg Display
	{
		LCDPTR = 16;
		LCDDAT = (COM0 + COM1 + COM2 + COM3);

		LCDPTR = 14;
		LCDDAT = (COM1 + COM2);
	}
		break;

	case E_NUM_1:    //show "1" -- 5'th 14seg Display
	{
		LCDPTR = 16;
		LCDDAT = (COM1 + COM2);
	}
		break;

	case E_NUM_2:    //show "2" -- 5'th 14seg Display
	{
		LCDPTR = 16;
		LCDDAT = (COM0 + COM2 + COM3);

		LCDPTR = 14;
		LCDDAT = COM1;

		LCDPTR = 17;
		LCDDAT = COM1;

		LCDPTR = 15;
		LCDDAT = COM2;
	}
		break;

	case E_NUM_3:    //show "3" -- 5'th 14seg Display
	{
		LCDPTR = 16;
		LCDDAT = (COM0 + COM1 + COM2 + COM3);

		LCDPTR = 17;
		LCDDAT = COM1;

		LCDPTR = 15;
		LCDDAT = COM2;
	}
		break;

	case E_NUM_4:    //show "4" -- 5'th 14seg Display
	{
		LCDPTR = 14;
		LCDDAT = COM2;

		LCDPTR = 17;
		LCDDAT = COM1;

		LCDPTR = 15;
		LCDDAT = COM2;

		LCDPTR = 16;
		LCDDAT = (COM1 + COM2);
	}
		break;

	case E_NUM_5:    //show "5" -- 5'th 14seg Display
	{
		LCDPTR = 16;
		LCDDAT = (COM0 + COM1 + COM3);

		LCDPTR = 14;
		LCDDAT = COM2;

		LCDPTR = 17;
		LCDDAT = COM1;

		LCDPTR = 15;
		LCDDAT = COM2;
	}
		break;

	case E_NUM_6:    //show "6" -- 5'th 14seg Display
	{
		LCDPTR = 16;
		LCDDAT = (COM0 + COM1 + COM3);

		LCDPTR = 14;
		LCDDAT = (COM1 + COM2);

		LCDPTR = 17;
		LCDDAT = COM1;

		LCDPTR = 15;
		LCDDAT = COM2;
	}
		break;

	case E_NUM_7:    //show "7" -- 5'th 14seg Display
	{
		LCDPTR = 14;
		LCDDAT = COM2;

		LCDPTR = 16;
		LCDDAT = (COM1 + COM2 + COM3);

	}
		break;

	case E_NUM_8:    //show "8" -- 5'th 14seg Display
	{
		LCDPTR = 16;
		LCDDAT = (COM0 + COM1 + COM2 + COM3);

		LCDPTR = 14;
		LCDDAT = (COM1 + COM2);

		LCDPTR = 17;
		LCDDAT = COM1;

		LCDPTR = 15;
		LCDDAT = COM2;
	}
		break;

	case E_NUM_9:    //show "9" -- 5'th 14seg Display
	{
		LCDPTR = 16;
		LCDDAT = (COM0 + COM1 + COM2 + COM3);

		LCDPTR = 14;
		LCDDAT = COM2;

		LCDPTR = 17;
		LCDDAT = COM1;

		LCDPTR = 15;
		LCDDAT = COM2;
	}
		break;
	}
}

void LCD_Display_Num_6(unsigned char u8Num_6) {
	switch (u8Num_6) {
	case E_NUM_0:    //show "0" -- 6'th 14seg Display
	{
		LCDPTR = 20;
		LCDDAT = (COM0 + COM1 + COM2 + COM3);

		LCDPTR = 18;
		LCDDAT = (COM1 + COM2);
	}
		break;

	case E_NUM_1:    //show "1" -- 6'th 14seg Display
	{
		LCDPTR = 20;
		LCDDAT = (COM1 + COM2);
	}
		break;

	case E_NUM_2:    //show "2" -- 6'th 14seg Display
	{
		LCDPTR = 20;
		LCDDAT = (COM0 + COM2 + COM3);

		LCDPTR = 21;
		LCDDAT = COM1;

		LCDPTR = 19;
		LCDDAT = COM2;

		LCDPTR = 18;
		LCDDAT = COM1;
	}
		break;

	case E_NUM_3:    //show "3" -- 6'th 14seg Display
	{
		LCDPTR = 20;
		LCDDAT = (COM0 + COM1 + COM2 + COM3);

		LCDPTR = 21;
		LCDDAT = COM1;

		LCDPTR = 19;
		LCDDAT = COM2;
	}
		break;

	case E_NUM_4:    //show "4" -- 6'th 14seg Display
	{
		LCDPTR = 18;
		LCDDAT = COM2;

		LCDPTR = 21;
		LCDDAT = COM1;

		LCDPTR = 19;
		LCDDAT = COM2;

		LCDPTR = 20;
		LCDDAT = (COM1 + COM2);
	}
		break;

	case E_NUM_5:    //show "5" -- 6'th 14seg Display
	{
		LCDPTR = 20;
		LCDDAT = (COM0 + COM1 + COM3);

		LCDPTR = 18;
		LCDDAT = COM2;

		LCDPTR = 21;
		LCDDAT = COM1;

		LCDPTR = 19;
		LCDDAT = COM2;
	}
		break;

	case E_NUM_6:    //show "6" -- 6'th 14seg Display
	{
		LCDPTR = 20;
		LCDDAT = (COM0 + COM1 + COM3);

		LCDPTR = 18;
		LCDDAT = (COM1 + COM2);

		LCDPTR = 21;
		LCDDAT = COM1;

		LCDPTR = 19;
		LCDDAT = COM2;
	}
		break;

	case E_NUM_7:    //show "7" -- 6'th 14seg Display
	{
		LCDPTR = 18;
		LCDDAT = COM2;

		LCDPTR = 20;
		LCDDAT = (COM1 + COM2 + COM3);

	}
		break;

	case E_NUM_8:    //show "8" -- 6'th 14seg Display
	{
		LCDPTR = 20;
		LCDDAT = (COM0 + COM1 + COM2 + COM3);

		LCDPTR = 18;
		LCDDAT = (COM1 + COM2);

		LCDPTR = 21;
		LCDDAT = COM1;

		LCDPTR = 19;
		LCDDAT = COM2;
	}
		break;

	case E_NUM_9:    //show "9" -- 6'th 14seg Display
	{
		LCDPTR = 20;
		LCDDAT = (COM0 + COM1 + COM2 + COM3);

		LCDPTR = 18;
		LCDDAT = COM2;

		LCDPTR = 21;
		LCDDAT = COM1;

		LCDPTR = 19;
		LCDDAT = COM2;
	}
		break;
	}
}

void LCD_Display_Num_7(unsigned char u8Num_7) {
	switch (u8Num_7) {
	case E_NUM_0:    //show "0" -- 7'th 14seg Display
	{
		LCDPTR = 24;
		LCDDAT = (COM0 + COM1 + COM2 + COM3);

		LCDPTR = 22;
		LCDDAT = (COM1 + COM2);
	}
		break;

	case E_NUM_1:    //show "1" -- 7'th 14seg Display
	{
		LCDPTR = 24;
		LCDDAT = (COM1 + COM2);
	}
		break;

	case E_NUM_2:    //show "2" -- 7'th 14seg Display
	{
		LCDPTR = 24;
		LCDDAT = (COM0 + COM2 + COM3);

		LCDPTR = 25;
		LCDDAT = COM1;

		LCDPTR = 23;
		LCDDAT = COM2;

		LCDPTR = 22;
		LCDDAT = COM1;
	}
		break;

	case E_NUM_3:    //show "3" -- 7'th 14seg Display
	{
		LCDPTR = 24;
		LCDDAT = (COM0 + COM1 + COM2 + COM3);

		LCDPTR = 25;
		LCDDAT = COM1;

		LCDPTR = 23;
		LCDDAT = COM2;
	}
		break;

	case E_NUM_4:    //show "4" -- 7'th 14seg Display
	{
		LCDPTR = 22;
		LCDDAT = COM2;

		LCDPTR = 25;
		LCDDAT = COM1;

		LCDPTR = 23;
		LCDDAT = COM2;

		LCDPTR = 24;
		LCDDAT = (COM1 + COM2);
	}
		break;

	case E_NUM_5:    //show "5" -- 7'th 14seg Display
	{
		LCDPTR = 24;
		LCDDAT = (COM0 + COM1 + COM3);

		LCDPTR = 22;
		LCDDAT = COM2;

		LCDPTR = 25;
		LCDDAT = COM1;

		LCDPTR = 23;
		LCDDAT = COM2;
	}
		break;

	case E_NUM_6:    //show "6" -- 7'th 14seg Display
	{
		LCDPTR = 24;
		LCDDAT = (COM0 + COM1 + COM3);

		LCDPTR = 22;
		LCDDAT = (COM1 + COM2);

		LCDPTR = 25;
		LCDDAT = COM1;

		LCDPTR = 23;
		LCDDAT = COM2;
	}
		break;

	case E_NUM_7:    //show "7" -- 7'th 14seg Display
	{
		LCDPTR = 22;
		LCDDAT = COM2;

		LCDPTR = 24;
		LCDDAT = (COM1 + COM2 + COM3);

	}
		break;

	case E_NUM_8:    //show "8" -- 7'th 14seg Display
	{
		LCDPTR = 24;
		LCDDAT = (COM0 + COM1 + COM2 + COM3);

		LCDPTR = 22;
		LCDDAT = (COM1 + COM2);

		LCDPTR = 25;
		LCDDAT = COM1;

		LCDPTR = 23;
		LCDDAT = COM2;
	}
		break;

	case E_NUM_9:    //show "9" -- 7'th 14seg Display
	{
		LCDPTR = 24;
		LCDDAT = (COM0 + COM1 + COM2 + COM3);

		LCDPTR = 22;
		LCDDAT = COM2;

		LCDPTR = 25;
		LCDDAT = COM1;

		LCDPTR = 23;
		LCDDAT = COM2;
	}
		break;
	}
}

void LCD_Display_3DP() {
	LCDPTR = 10;
	LCDDAT |= COM0;
}

void LCD_Display_Degree() {
	LCDPTR = 20;
	LCDDAT = (COM2 + COM3);
	LCDPTR = 21;
	LCDDAT = COM1;
	LCDPTR = 19;
	LCDDAT = COM2;
	LCDPTR = 18;
	LCDDAT = COM2;

	LCDPTR = 24;
	LCDDAT = (COM0 + COM3);
	LCDPTR = 22;
	LCDDAT = (COM1 + COM2);
}

void LCD_Display_nuvoTon_Logo() {
	LCDPTR = 27;
	LCDDAT |= COM0;
}

void LCD_Display_Welcome_Pattern() {
	LCDPTR = 22;
	LCDDAT |= COM3;
}

void LCD_Display_N76E616_Pattern() {
	//--------------------------------------

	//show "nuvoTon"
	LCDPTR = 27;                           //MCU's SEG27 -- LCD's SEG37
	LCDDAT = COM0;                         //LCD's COM0

	//--------------------------------------

	//show "N" -- 1'st 13seg Display
	LCDPTR = 0;                            //MCU's SEG0 -- LCD's SEG1
	LCDDAT = (COM1 + COM2);                //LCD's COM1/2

	LCDPTR = 1;                            //MCU's SEG1 -- LCD's SEG2
	LCDDAT = COM0;                         //LCD's COM0

	LCDPTR = 28;                           //MCU's SEG1 -- LCD's SEG43
	LCDDAT = (COM1 + COM2);                //LCD's COM1/2

	LCDPTR = 31;                           //MCU's SEG1 -- LCD's SEG44
	LCDDAT = COM3;                         //LCD's COM3

	//--------------------------------------

	//show "7" -- 2'nd 13seg Display
	LCDPTR = 4;                            //MCU's SEG4 -- LCD's SEG5
	LCDDAT = (COM1 + COM2 + COM3);         //LCD's COM1/2/3

	LCDPTR = 2;                            //MCU's SEG2 -- LCD's SEG3
	LCDDAT = COM2;                         //LCD's COM2

	//--------------------------------------

	//show "6" -- 3'th 13seg Display
	LCDPTR = 6;                            //MCU's SEG6 -- LCD's SEG7
	LCDDAT = (COM1 + COM2);                //LCD's COM1/2

	LCDPTR = 7;                            //MCU's SEG7 -- LCD's SEG8
	LCDDAT = COM2;                         //LCD's COM2

	LCDPTR = 8;                            //MCU's SEG8 -- LCD's SEG9
	LCDDAT = (COM0 + COM1 + COM3);         //LCD's COM0/1/3

	LCDPTR = 9;                            //MCU's SEG9 -- LCD's SEG10
	LCDDAT = COM1;                         //LCD's COM1

	//--------------------------------------

	//show "E" -- 4'th 13seg Display
	LCDPTR = 10;                           //MCU's SEG10 -- LCD's SEG11
	LCDDAT = (COM1 + COM2);                //LCD's COM1/2

	LCDPTR = 11;                           //MCU's SEG11 -- LCD's SEG12
	LCDDAT = COM2;                         //LCD's COM2

	LCDPTR = 12;                           //MCU's SEG12 -- LCD's SEG13
	LCDDAT = (COM0 + COM3);                //LCD's COM0/3

	LCDPTR = 13;                           //MCU's SEG13 -- LCD's SEG14
	LCDDAT = COM1;                         //LCD's COM1

	//--------------------------------------

	//show "6" -- 9'th 7seg Display
	LCDPTR = 14;                           //MCU's SEG14 -- LCD's SEG15
	LCDDAT = (COM1 + COM2);                //LCD's COM1/2

	LCDPTR = 15;                           //MCU's SEG15 -- LCD's SEG16
	LCDDAT = COM2;                         //LCD's COM2

	LCDPTR = 16;                           //MCU's SEG16 -- LCD's SEG17
	LCDDAT = (COM0 + COM1 + COM3);         //LCD's COM0/1/3

	LCDPTR = 17;                           //MCU's SEG17 -- LCD's SEG18
	LCDDAT = COM1;                         //LCD's COM1

	//--------------------------------------

	//show "1" -- 10'th 7seg Display
	LCDPTR = 20;                           //MCU's SEG20 -- LCD's SEG21
	LCDDAT = (COM1 + COM2);                //LCD's COM1/2

	//--------------------------------------

	//show "6" -- 9'th 7seg Display
	LCDPTR = 22;                           //MCU's SEG22 -- LCD's SEG23
	LCDDAT = (COM1 + COM2);                //LCD's COM1/2

	LCDPTR = 23;                           //MCU's SEG23 -- LCD's SEG24
	LCDDAT = COM2;                         //LCD's COM2

	LCDPTR = 24;                           //MCU's SEG23 -- LCD's SEG24
	LCDDAT = (COM0 + COM1 + COM3);                //LCD's COM0/1/3

	LCDPTR = 25;                           //MCU's SEG25 -- LCD's SEG26
	LCDDAT = COM1;                         //LCD's COM1
}

