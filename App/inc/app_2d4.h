/*
 * app_2d4.h
 *
 *  Created on: 2017Äê8ÔÂ16ÈÕ
 *      Author: fly
 */

#ifndef APP_INC_APP_2D4_H_
#define APP_INC_APP_2D4_H_

#define LCD2LAMP_HEADER   0xF2
#define LAMP2LCD_HEADER   0xF8

#define POWER_SHORT_CMD      0xB1
#define POWER_LONG_CMD      0xBA

#define ACC_CMD        0xB6

#define UP_CMD         0xB3
#define DOWN_CMD       0xB4
#define DOME_CMD       0xB9
#define VOL_ADD_CMD    0xB5
#define VOL_MINUS_CMD  0xB7

#define PLAY_CMD       0xB2
#define MODE_CMD       0xB8

void app_2d4_init(void);
void app_2d4_send(uint8_t *d, uint8_t len);
void app_2d4_pro(void);

#endif /* APP_INC_APP_2D4_H_ */
