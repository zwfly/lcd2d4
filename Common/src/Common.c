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

/***************************************************************************************************
 System Clock Source Select
 ****************************************************************************************************/
void System_Clock_Select(E_SYSTEM_CLOCK clock) {
	switch (clock) {
	case E_HXTEN: {
		//step1: enable clock source
		set_EXTEN1
		;
		clr_EXTEN0
		;

		//step2: check ready
		while ((CKSWT & SET_BIT7) == 0)
			;

		//step3: switching system clock source
		clr_OSC2
		;
		set_OSC1
		;
		clr_OSC0
		;
	}
		break;

	case E_LXTEN: {
		//step1: enable clock source
		clr_EXTEN1
		;
		set_EXTEN0
		;

		//step2: check ready
		while ((CKSWT & SET_BIT6) == 0)
			;

		//step3: switching system clock source
		clr_OSC2
		;
		set_OSC1
		;
		clr_OSC0
		;
	}
		break;

	case E_HIRCEN: //power on default
	{
		//step1: enable clock source
		set_HIRCEN
		;

		//step2: check ready
		while ((CKSWT & SET_BIT5) == 0)
			;

		//step3: switching system clock source
		clr_OSC2
		;
		clr_OSC1
		;
		clr_OSC0
		;
	}
		break;

	case E_LIRCEN: {
		//step1: enable clock source
		set_LIRCEN
		;

		//step2: check ready
		while ((CKSWT & SET_BIT4) == 0)
			;

		//step3: switching system clock source
		set_OSC2
		;
		clr_OSC1
		;
		clr_OSC0
		;
	}
		break;

	case E_OSCEN: {
		//step1: enable clock source
		clr_EXTEN1
		;
		clr_EXTEN0
		;

		//step2: check ready
		while ((CKSWT & SET_BIT3) == 0)
			;

		//step3: switching system clock source
		clr_OSC2
		;
		set_OSC1
		;
		clr_OSC0
		;
	}
		break;

	}
	//step4: check system clock switching OK or NG?
	while ((CKEN & SET_BIT0) == 1)
		;  //Check Clock switch fault flag.
}
//-----------------------------------------------------------------------------------------------------------
/* use timer1 as Baudrate generator
 */
void InitialUART0_Timer1_Type1(UINT32 u32Baudrate)    //T1M = 0, SMOD = 0
{
	SCON = 0x52;     //UART0 Mode1,REN=1,TI=1
	TMOD |= 0x20;    //Timer1 Mode1

	clr_SMOD;
	clr_T1M;
	clr_BRCK;        //Serial port 0 baud rate clock source = Timer1

#ifdef FOSC_110592
	TH1 = 256 - (28800 / u32Baudrate); /*11.0592 MHz */
#endif    
#ifdef FOSC_165888
	TH1 = 256 - (43200/u32Baudrate); /*16.5888 MHz */
#endif
	set_TR1;
}

//-----------------------------------------------------------------------------------------------------------
/* use timer1 as Baudrate generator
 */
void InitialUART0_Timer1_Type2(UINT32 u32Baudrate)    //T1M = 0, SMOD = 1
{
	SCON = 0x52;     //UART0 Mode1,REN=1,TI=1
	TMOD |= 0x20;    //Timer1 Mode1

	set_SMOD;        //UART0 Double Rate Enable
	clr_T1M;
	clr_BRCK;        //Serial port 0 baud rate clock source = Timer1

#ifdef FOSC_110592
	TH1 = 256 - (57600 / u32Baudrate); /*11.0592 MHz */
#endif    
#ifdef FOSC_165888
	TH1 = 256 - (86400/u32Baudrate); /*16.5888 MHz */
#endif
	set_TR1;
}

//-----------------------------------------------------------------------------------------------------------
/* use timer1 as Baudrate generator
 */
void InitialUART0_Timer1_Type3(UINT32 u32Baudrate)    //T1M = 1, SMOD = 0
{
	SCON = 0x52;     //UART0 Mode1,REN=1,TI=1
	TMOD |= 0x20;    //Timer1 Mode1

	clr_SMOD;
	set_T1M;
	clr_BRCK;        //Serial port 0 baud rate clock source = Timer1

#ifdef FOSC_110592
	TH1 = 256 - (345600 / u32Baudrate); /*11.0592 MHz */
#endif    
#ifdef FOSC_165888
	TH1 = 256 - (518400/u32Baudrate); /*16.5888 MHz */
#endif
	set_TR1;
}

//-----------------------------------------------------------------------------------------------------------
/* use timer1 as Baudrate generator
 */
void InitialUART0_Timer1_Type4(UINT32 u32Baudrate)    //T1M = 1, SMOD = 1
{
	SCON = 0x52;     //UART0 Mode1,REN=1,TI=1
	TMOD |= 0x20;    //Timer1 Mode1

	set_SMOD;        //UART0 Double Rate Enable
	set_T1M;
	clr_BRCK;        //Serial port 0 baud rate clock source = Timer1

#ifdef FOSC_110592
	TH1 = 256 - (691200 / u32Baudrate); /*11.0592 MHz */
#endif    
#ifdef FOSC_165888
	TH1 = 256 - (1036800/u32Baudrate); /*16.5888 MHz */
#endif
	set_TR1;
}
//---------------------------------------------------------------
void InitialUART0_Timer3_Type5(UINT32 u32Baudrate) //use timer3 as Baudrate generator
{
	SCON = 0x52;     //UART0 Mode1,REN=1,TI=1
	clr_SMOD;
	T3CON &= 0xF8;   //T3PS2=0,T3PS1=0,T3PS0=0(Prescale=1)
	set_BRCK;        //Serial port 0 baud rate clock source = Timer3

#ifdef FOSC_110592
	R3H = HIBYTE(65536 - (345600 / u32Baudrate)); /*11.0592 MHz */
	R3L = LOBYTE(65536 - (345600 / u32Baudrate)); /*11.0592 MHz */
#endif
#ifdef FOSC_165888
	R3H = HIBYTE(65536 - (518400/u32Baudrate)); /*16.5888 MHz */
	R3L = LOBYTE(65536 - (518400/u32Baudrate)); /*16.5888 MHz */
#endif
	set_TR3;         //Trigger Timer3
}
//---------------------------------------------------------------
void InitialUART0_Timer3_Type6(UINT32 u32Baudrate) //use timer3 as Baudrate generator
{
	SCON = 0x52;     //UART0 Mode1,REN=1,TI=1
	set_SMOD;        //UART0 Double Rate Enable
	T3CON &= 0xF8;   //T3PS2=0,T3PS1=0,T3PS0=0(Prescale=1)
	set_BRCK;        //UART0 baud rate clock source = Timer3

#ifdef FOSC_110592
	R3H = HIBYTE(65536 - (691200 / u32Baudrate)); /*11.0592 MHz */
	R3L = LOBYTE(65536 - (691200 / u32Baudrate)); /*11.0592 MHz */
#endif
#ifdef FOSC_165888
	R3H = HIBYTE(65536 - (1036800/u32Baudrate)); /*16.5888 MHz */
	R3L = LOBYTE(65536 - (1036800/u32Baudrate)); /*16.5888 MHz */
#endif
	set_TR3;         //Trigger Timer3
}
//---------------------------------------------------------------
void InitialUART1_Timer3(UINT32 u32Baudrate) //use timer3 as Baudrate generator
{
	SCON_1 = 0x52;   //UART1 Mode1,REN_1=1,TI_1=1
	T3CON &= 0xF8;   //T3PS2=0,T3PS1=0,T3PS0=0(Prescale=1)

#ifdef FOSC_110592  //max BR=230400 bps
	R3H = HIBYTE(65536 - (691200 / u32Baudrate)); /*11.0592 MHz */
	R3L = LOBYTE(65536 - (691200 / u32Baudrate)); /*11.0592 MHz */
#endif
#ifdef FOSC_165888
	R3H = HIBYTE(65536 - (1036800/u32Baudrate)); /*16.5888 MHz */
	R3L = LOBYTE(65536 - (1036800/u32Baudrate)); /*16.5888 MHz */
#endif
	set_TR3;         //Trigger Timer3
}
/**************************************************************************
 *
 *  Function Name: Receive_Data_From_UART0()
 *
 *  Descriptions: Receive PC data to SBUF of N76E616
 *
 *  Arguments:
 *
 *  Returns: PC Data
 *
 **************************************************************************/
UINT8 Receive_Data_From_UART0(void) {
	UINT8 c;

	while (!RI)
		;
	c = SBUF;
	RI = 0;
	return (c);
}
/**************************************************************************
 *
 *  Function Name: Send_Data_To_UART0()
 *
 *  Descriptions: Send SBUF of N76E616 to PC
 *
 *  Arguments:
 *
 *  Returns: None
 *
 **************************************************************************/
void Send_Data_To_UART0(UINT8 c) {
	TI = 0;
	SBUF = c;
	while (TI == 0)
		;
}
/**************************************************************************
 *
 *  Function Name: Receive_Data_From_UART1()
 *
 *  Descriptions: Receive PC data to SBUF of N76E616
 *
 *  Arguments:
 *
 *  Returns: PC Data
 *
 **************************************************************************/
UINT8 Receive_Data_From_UART1(void) {
	UINT8 c;

	while (!RI_1)
		;
	c = SBUF_1;
	RI_1 = 0;
	return (c);
}
/**************************************************************************
 *
 *  Function Name: Send_Data_To_UART1()
 *
 *  Descriptions: Send SBUF of N76E616 to PC
 *
 *  Arguments:
 *
 *  Returns: None
 *
 **************************************************************************/
void Send_Data_To_UART1(UINT8 c) {
	TI_1 = 0;
	SBUF_1 = c;
	while (TI_1 == 0)
		;
}
/*==========================================================================*/
void Set_All_GPIO_Quasi_Mode(void) {
	P0M1 = 0x00;
	P0M2 = 0x00;
	P1M1 = 0x00;
	P1M2 = 0x00;
	P2M1 = 0x00;
	P2M2 = 0x00;
	P3M1 = 0x00;
	P3M2 = 0x00;
	P4M1 = 0x00;
	P4M2 = 0x00;
	P5M1 = 0x00;
	P5M2 = 0x00;
}
/*==========================================================================*/
void Set_All_GPIO_Input_Mode(void) {
	P0M1 = 0xFF;
	P0M2 = 0x00;
	P1M1 = 0xFF;
	P1M2 = 0x00;
	P2M1 = 0xFF;
	P2M2 = 0x00;
	P3M1 = 0xFF;
	P3M2 = 0x00;
	P4M1 = 0xFF;
	P4M2 = 0x00;
	P5M1 = 0xFF;
	P5M2 = 0x00;
}

/*==========================================================================*/
void SW_Reset(void) {
	TA = 0xAA;
	TA = 0x55;
	set_SWRST
	;
}
/*==========================================================================*/
void Fsys_Clock_Output_On_P26(void) {
	set_CLOEN;                                  //System Clock Output Enable
}

/*****************************************************************************
 * putchar (full version):  expands '\n' into CR LF and handles
 *                          XON/XOFF (Ctrl+S/Ctrl+Q) protocol
 ****************************************************************************/
#define XON  0x11
#define XOFF 0x13

char putchar(char c) {
#if DEBUG_PORT == 0
	if (c == '\n')
	{
		if (RI)
		{
			if (SBUF == XOFF)
			{
				do
				{
					clr_RI_1;
					while (!RI);
				}
				while (SBUF != XON);
				clr_RI;
			}
		}
		while (!TI);
		clr_TI;
		SBUF = 0x0d; /* output CR  */
	}
	if (RI)
	{
		if (SBUF == XOFF)
		{
			do
			{
				clr_RI;
				while (!RI);
			}while (SBUF != XON);
			clr_RI;
		}
	}
	while (!TI);
	clr_TI;
	return (SBUF = c);
	;
#elif DEBUG_PORT == 1
	if (c == '\n') {
		if (RI_1) {
			if (SBUF_1 == XOFF) {
				do {
					clr_RI_1;
					while (!RI_1)
						;
				} while (SBUF_1 != XON);
				clr_RI_1;
			}
		}
		while (!TI_1)
			;
		clr_TI_1;
		SBUF_1 = 0x0d; /* output CR  */
	}
	if (RI_1) {
		if (SBUF_1 == XOFF) {
			do {
				clr_RI_1;
				while (!RI_1)
					;
			} while (SBUF_1 != XON);
			clr_RI_1;
		}
	}
	while (!TI_1)
		;
	clr_TI_1;
	return (SBUF_1 = c);
#endif
}
