/*
 * bsp_eeprom.c
 *
 *  Created on: 2017Äê9ÔÂ8ÈÕ
 *      Author: fly
 */
#include "bsp.h"



void EEPROM_InitHard(void) {

}

/*****************************************************************************************************************
 write_DATAFLASH_BYTE :
 user can copy all this subroutine into project, then call this function in main.
 ******************************************************************************************************************/
void write_DATAFLASH_BYTE(UINT16 u16_addr, UINT8 u8_data) {
#if 0
//Check page start address
	u8_addrl_r = u16_addr;
	if (u8_addrl_r < 0x80) {
		u8_addrl_r = 0;
	} else {
		u8_addrl_r = 0x80;
	}
//Save APROM data to XRAM
	xd_tmp = 0x80;
	cd_longaddr = (u16_addr & 0xff00) + u8_addrl_r;
	while (xd_tmp != 0x100) {
		*xd_tmp = *cd_longaddr;
		looptmp++;
		xd_tmp++;
		cd_longaddr++;
	}
// Modify customer data in XRAM
	u8_addrl_r = u16_addr;
	if (u8_addrl_r < 0x80) {
		xd_tmp = u8_addrl_r + 0x80;
	} else {
		xd_tmp = u8_addrl_r + 0;
	}
	*xd_tmp = u8_data;

//Erase APROM DATAFLASH page
	IAPAL = u16_addr;
	IAPAH = u16_addr >> 8;
	IAPFD = 0xFF;
	set_IAPEN
	;
	set_APUEN
	;
	IAPCN = 0x22;
	set_IAPGO
	;
#endif
//Save changed RAM data to APROM DATAFLASH

	IAPAL = u16_addr & 0xFF;
	IAPAH = (u16_addr >> 8) & 0xFF;
	set_IAPEN
	;
	set_APUEN
	;
	IAPCN = 0x21;

	IAPFD = u8_data;
	set_IAPGO
	;
//	IAPAL++;

	clr_APUEN
	;
	clr_IAPEN
	;
}
void erase_DATAFLASH(UINT16 u16_addr) {
	IAPAL = u16_addr;
	IAPAH = u16_addr >> 8;
	IAPFD = 0xFF;
	set_IAPEN
	;
	set_APUEN
	;
	IAPCN = 0x22;
	set_IAPGO
	;
}
void write_DATAFLASH_BUF(UINT16 u16_addr, UINT8 *pt, uint8_t len) {
	uint16_t i = 0;
	IAPAL = u16_addr & 0xFF;
	IAPAH = (u16_addr >> 8) & 0xFF;
	set_IAPEN
	;
	set_APUEN
	;
	IAPCN = 0x21;
	for (i = 0; i < len; ++i) {
		IAPFD = *(pt + i);
		set_IAPGO
		;
	}

	clr_APUEN
	;
	clr_IAPEN
	;
}

//-------------------------------------------------------------------------
uint8_t read_APROM_BYTE(uint16_t code *u16_addr) {
	uint8_t rdata;
	rdata = *u16_addr>>8;
	return rdata;
}

/******************************************************************************************************************/
