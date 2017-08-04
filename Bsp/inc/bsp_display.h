/*
 * bsp_display.h
 *
 *  Created on: 2017Äê6ÔÂ26ÈÕ
 *      Author: fly
 */

#ifndef BSP_INC_BSP_DISPLAY_H_
#define BSP_INC_BSP_DISPLAY_H_

void LCD_Clear_All(void);
void LCD_Clear_Bluetooth_ICO(void);
void LCD_Show_Bluetooth_ICO(void);
void LCD_Clear_Bluetooth_Fill_ICO(void);
void LCD_Show_Bluetooth_Fill_ICO(void);
void LCD_Clear_Line_up(void);
void LCD_Show_Line_up(void);
void LCD_Clear_Battery_ICO(void);
void LCD_Show_Battery_ICO(void);
void LCD_Clear_REP_ICO(void);
void LCD_Show_REP_ICO(void);
void LCD_Clear_REP_Num(void);
void LCD_Show_REP_Num(uint8_t num);
void LCD_Clear_ABCD(void);
void LCD_Show_ABCD_all(void);
void LCD_Show_ABCD(char c);
void LCD_Clear_Pulls_Num(void);
void LCD_Show_Pulls_Num(uint16_t num);
void LCD_Clear_QS_ICO(void);
void LCD_Show_QS_ICO(void);
void LCD_Clear_COACH_ICO(void);
void LCD_Show_COACH_ICO(void);
void LCD_Clear_Line_down(void);
void LCD_Show_Line_down(void);
void LCD_Clear_Heart_ICO(void);
void LCD_Show_Heart_ICO(void);
void LCD_Clear_CAL_Num(void);
void LCD_Show_CAL_Num(uint16_t num);
void LCD_Clear_CAL_ICO(void);
void LCD_Show_CAL_ICO(void);

void LCD_display_InitHard(void);

#endif /* BSP_INC_BSP_DISPLAY_H_ */
