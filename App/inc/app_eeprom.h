/*
 * app_eeprom.h
 *
 *  Created on: 2017Äê9ÔÂ8ÈÕ
 *      Author: fly
 */

#ifndef APP_INC_APP_EEPROM_H_
#define APP_INC_APP_EEPROM_H_

#define WIRELESS_ADDRESS_START_ADDR   (0x4800 - PAGE_SIZE)

void app_eeprom_Init(void);

void app_eeprom_erase(uint16_t addr);
void app_eeprom_write_byte(uint16_t addr, uint8_t d);
void app_eeprom_write_buf(uint16_t addr, uint8_t *pt, uint8_t len);
uint8_t app_eeprom_read_byte(uint16_t addr) ;

#endif /* APP_INC_APP_EEPROM_H_ */
