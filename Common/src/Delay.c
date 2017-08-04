/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2015 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

//***********************************************************************************************************
//  Nuvoton Technoledge Corp. 
//  Website: http://www.nuvoton.com
//  E-Mail : MicroC-8bit@nuvoton.com
//  Date   : Sep/1/2015
//***********************************************************************************************************
#include <N76E616.h>
#include "Version.h"
#include "Typedef.h"
#include "Define.h"
#include "SFR_Macro.h"
#include "Common.h"
#include "Delay.h"
#include "Display.h"

#ifdef FOSC_110592
#define VALUE_10us          65536-9     //9*12  /11.0592 = 10 uS, Timer Clock = Fsys/12
#define VALUE_1ms           65536-923   //923*12/11.0592 = 1 mS,  Timer Clock = Fsys/12
#define TM3_VALUE_10us      65536-28    //28*4  /11.0592 = 10 uS, Timer Clock = Fsys/4
#define TM3_VALUE_1ms       65536-2765  //2765*4/11.0592 = 1 mS,  Timer Clock = Fsys/4
#endif
#ifdef FOSC_165888
#define VALUE_10us          65536-14    //15*12  /16.5888 = 10 uS, Timer Clock = Fsys/12
#define VALUE_1ms           65536-1382  //1536*12/16.5888 = 1 mS,  Timer Clock = Fsys/12
#define TM3_VALUE_10us      65536-42    //46*4   /16.5888 = 10 uS, Timer Clock = Fsys/4
#define TM3_VALUE_1ms       65536-4147  //4608*4 /16.5888 = 1 mS,  Timer Clock = Fsys/4
#endif

//-------------------------------------------------------------------------
void Random_Delay(void)
reentrant //reentrant --> 在中斷 ISR 調用此 function 時候
{
	UINT32 u32CNT,u32Tmp;

	for (u32CNT=0;u32CNT<0x0000FFFF;u32CNT++)
	{
		u32Tmp ++;
	}
}
//-------------------------------------------------------------------------
void Delay10us(UINT16 u16CNT) {
	clr_T0M;                                //T0M=0, Timer0 Clock = Fsys/12
	TMOD |= 0x01;                           //Timer0 is 16-bit mode
	set_TR0;                                //Trigger Timer0
	while (u16CNT != 0) {
		TL0 = LOBYTE(VALUE_10us);
		TH0 = HIBYTE(VALUE_10us);
		while (TF0 != 1)
			;                   //Check Timer0 Time-Out Flag
		clr_TF0;
		u16CNT--;
	}
	clr_TR0;                                //Stop the Timer0
}
//------------------------------------------------------------------------------
void Timer0_Delay1ms(UINT32 u32CNT) {
	clr_T0M;                                //T0M=0, Timer0 Clock = Fsys/12
	TMOD |= 0x01;                           //Timer0 is 16-bit mode
	set_TR0;                                //Trigger Timer0
	while (u32CNT != 0) {
		TL0 = LOBYTE(VALUE_1ms);
		TH0 = HIBYTE(VALUE_1ms);
		while (TF0 != 1)
			;                   //Check Timer0 Time-Out Flag
		clr_TF0;
		u32CNT--;
	}
	clr_TR0;                                //Stop the Timer0
}
//------------------------------------------------------------------------------
void Timer1_Delay1ms(UINT32 u32CNT) {
	clr_T1M;                                //T1M=0, Timer1 Clock = Fsys/12
	TMOD |= 0x10;                           //Timer1 is 16-bit mode
	set_TR1;                                //Trigger Timer1
	while (u32CNT != 0) {
		TL1 = LOBYTE(VALUE_1ms);
		TH1 = HIBYTE(VALUE_1ms);
		while (TF1 != 1)
			;                   //Check Timer1 Time-Out Flag
		clr_TF1;
		u32CNT--;
	}
	clr_TR1;                                //Stop the Timer1
}
//------------------------------------------------------------------------------
void Timer3_Delay1ms(UINT32 u32CNT) {
	T3CON = 0x02;                           //Timer3 Clock = Fsys/4
	set_TR3;                                //Trigger Timer3
	while (u32CNT != 0) {
		R3L = LOBYTE(TM3_VALUE_1ms);
		R3H = HIBYTE(TM3_VALUE_1ms);
		while ((T3CON & SET_BIT4) != SET_BIT4)
			;                                //Check Timer3 Time-Out Flag
		clr_TF3;
		u32CNT--;
	}
	clr_TR3;                                //Stop the Timer3
}
//------------------------------------------------------------------------------
void WakeUp_Timer_Delay25ms(UINT32 u32CNT)  //Clock source is 10KHz
{
	clr_WKPS2;                              //Clock Divider Scale is 1
	clr_WKPS1;
	clr_WKPS0;

	RWK = 0x00;

	clr_WKTCK;                           //WDT Clock source is form LIRC (10KHz)
	set_WKTR;                               //Trigger Watch Dog Timer
	while (u32CNT != 0) {
		while ((WKCON & SET_BIT4) != SET_BIT4)
			;                               //Check Time-Out Flag
		clr_WKTF;
		u32CNT--;
	}
	clr_WKTR;                              //Stop the Watch Dog Timer
}
