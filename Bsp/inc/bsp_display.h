/*
 * bsp_display.h
 *
 *  Created on: 2017Äê6ÔÂ26ÈÕ
 *      Author: fly
 */

#ifndef BSP_INC_BSP_DISPLAY_H_
#define BSP_INC_BSP_DISPLAY_H_

#define MI_LENGTH   8

void LCD_display_InitHard(void);

void LCD_Clear_All(void);

void LCD_Clear_LED_ICO(void);
void LCD_Show_LED_ICO(void);
void LCD_Clear_FM_ICO(void);
void LCD_Show_FM_ICO(void);
void LCD_Clear_BLUETooTH_ICO(void);
void LCD_Show_BLUETooTH_ICO(void);
void LCD_Clear_AUX_ICO(void);
void LCD_Show_AUX_ICO(void);
void LCD_Clear_USB_ICO(void);
void LCD_Show_USB_ICO(void);
void LCD_Clear_MHZ_ICO(void);
void LCD_Show_MHZ_ICO(void);
void LCD_Clear_BAZOOKA_ICO(void);
void LCD_Show_BAZOOKA_ICO(void);
void LCD_Clear_upColon_ICO(void);
void LCD_Show_upColon_ICO(void);
void LCD_Clear_downColon_ICO(void);
void LCD_Show_downColon_ICO(void);
void LCD_Clear_Colon_ICO(void);
void LCD_Show_Colon_ICO(void);
void LCD_Clear_mi_all(void);
void LCD_ShowChar(uint8_t n, char c);
void LCD_ShowString(char *s);

#endif /* BSP_INC_BSP_DISPLAY_H_ */
