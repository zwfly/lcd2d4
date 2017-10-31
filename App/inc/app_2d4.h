/*
 * app_2d4.h
 *
 *  Created on: 2017Äê8ÔÂ16ÈÕ
 *      Author: fly
 */

#ifndef  APP_INC_APP_2D4_H_
#define  APP_INC_APP_2D4_H_

#define  LCD2LAMP_HEADER   0xF2
#define  LAMP2LCD_HEADER   0xF8


//#define POWER_LONG_CMD      0xBA

#define  KEY_ACC_CMD        0x09
#define  KEY_DOME_CMD       0xB9

#define  KEY_POWER_SHORT_CMD  0x01
#define  KEY_UP_CMD           0x02
#define  KEY_DOWN_CMD         0x03
#define  KEY_VOL_ADD_CMD      0x04
#define  KEY_VOL_MINUS_CMD    0x05
#define  KEY_PLAY_SHORT_CMD   0x06
#define  KEY_PLAY_LONG_CMD    0x07
#define  KEY_MODE_CMD         0x08

//////
#define  RCV_POWER_STATUS_CMD                0x31
#define  RCV_X_BOX_STATUS_CMD                0x32
#define  RCV_BT_STATUS_CMD                   0x33
#define  RCV_PLAY_PAUSE_STATUS_CMD           0x34
#define  RCV_PREV_NEXT_CMD                   0x35

#define  RCV_USB_PLAY_TIME_CMD               0x36
#define  RCV_FM_HZ_CMD                       0x37
#define  RCV_VOL_CMD                         0x38

#define  MODE_CHANGE_CMD                     0x41




extern idata uint8_t sendBuf[PAYLOAD_WIDTH];

void app_2d4_init(void);
void app_2d4_send(uint8_t *d, uint8_t len);
void app_2d4_pro(void);
//void app_2d4_1S_pro(void);

#endif /* APP_INC_APP_2D4_H_ */
