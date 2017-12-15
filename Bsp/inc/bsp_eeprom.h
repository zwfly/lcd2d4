/*
 * bsp_eeprom.h
 *
 *  Created on: 2017Äê9ÔÂ8ÈÕ
 *      Author: fly
 */

#ifndef BSP_INC_BSP_EEPROM_H_
#define BSP_INC_BSP_EEPROM_H_

#define     PAGE_SIZE           128

void EEPROM_InitHard(void);

void write_DATAFLASH_BYTE(UINT16 u16_addr, UINT8 u8_data);
void erase_DATAFLASH(UINT16 u16_addr);
void write_DATAFLASH_BUF(UINT16 u16_addr, UINT8 *pt, uint8_t len);

uint8_t read_APROM_BYTE(UINT16 code *u16_addr);

#endif /* BSP_INC_BSP_EEPROM_H_ */
