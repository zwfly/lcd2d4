/*
 * app_eeprom.c
 *
 *  Created on: 2017Äê9ÔÂ8ÈÕ
 *      Author: fly
 */
#include "app.h"
#include <string.h>

void app_eeprom_Init(void) {

}

void app_eeprom_erase(uint16_t addr) {
	erase_DATAFLASH(WIRELESS_ADDRESS_START_ADDR + addr);
}
void app_eeprom_write_byte(uint16_t addr, uint8_t d) {
	write_DATAFLASH_BYTE(WIRELESS_ADDRESS_START_ADDR + addr, d);
}
void app_eeprom_write_buf(uint16_t addr, uint8_t *pt, uint8_t len) {
	write_DATAFLASH_BUF(WIRELESS_ADDRESS_START_ADDR + addr, pt, len);
}
uint8_t app_eeprom_read_byte(uint16_t addr) {
	return read_APROM_BYTE((uint16_t *) addr);
}
void app_eeprom_100ms_pro(void) {

}

static void app_eeprom_pro(void) {

}
