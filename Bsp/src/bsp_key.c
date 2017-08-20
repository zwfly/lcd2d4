/*
 *********************************************************************************************************
 *
 *	模块名称 : 独立按键驱动模块
 *	文件名称 : bsp_key.c
 *	版    本 : V1.0
 *	说    明 : 扫描独立按键，具有软件滤波机制，具有按键FIFO。可以检测如下事件：
 *				(1) 按键按下
 *				(2) 按键弹起
 *				(3) 长按键
 *				(4) 长按时自动连发
 *
 *********************************************************************************************************
 */

#include "bsp.h"

#define KEY_AD_ERROR 5

#define S2_AD  980
#define S3_AD  955
#define S4_AD  884
#define S5_AD  0
#define S6_AD  991
#define S7_AD  977
#define S8_AD  952
#define S9_AD  881

static idata KEY_T s_tBtn[KEY_COUNT];
static idata KEY_FIFO_T s_tKey; /* 按键FIFO变量,结构体 */

static void bsp_InitKeyVar(void);
static void bsp_InitKeyHard(void);
static void bsp_DetectKey(uint8_t i);

/*
 *********************************************************************************************************
 *	函 数 名: IsKeyDownX
 *	功能说明: 判断按键是否按下
 *	形    参: 无
 *	返 回 值: 返回值1 表示按下，0表示未按下
 *********************************************************************************************************
 */

//S1
static uint8_t IsKeyDown1(void) {
	if (P02) {
		return 0;
	} else {
		return 1;
	}
}
uint16_t max = 0;
uint16_t min = 0;
static uint8_t IsKeyDown(uint16_t key_ad, uint16_t result_ad) {

	max = (key_ad + KEY_AD_ERROR) > 1023 ? 1023 : key_ad + KEY_AD_ERROR;
	min = (key_ad < KEY_AD_ERROR) ? 0 : (key_ad - KEY_AD_ERROR);

	return ((result_ad >= min) && (result_ad <= max));
}

//CH1, S2 ad = 980
static uint8_t IsKeyDown2(void) {

	return IsKeyDown(S2_AD, g_tADC_Result.result[0]);
}
//CH1, S3 ad = 954
static uint8_t IsKeyDown3(void) {
	return IsKeyDown(S3_AD, g_tADC_Result.result[0]);
}
//CH1, S4 ad = 884
static uint8_t IsKeyDown4(void) {
	return IsKeyDown(S4_AD, g_tADC_Result.result[0]);
}
//CH1, S5 ad = 0
static uint8_t IsKeyDown5(void) {

	return IsKeyDown(S5_AD, g_tADC_Result.result[0]);
}
//CH2, S6 ad = 1020
static uint8_t IsKeyDown6(void) {
	return IsKeyDown(S6_AD, g_tADC_Result.result[1]);
}
//CH2, S7 ad = 1018
static uint8_t IsKeyDown7(void) {
	return IsKeyDown(S7_AD, g_tADC_Result.result[1]);
}
//CH2, S8 ad = 1016
static uint8_t IsKeyDown8(void) {
	return IsKeyDown(S8_AD, g_tADC_Result.result[1]);
}
//CH2, S9 ad = 1009
static uint8_t IsKeyDown9(void) {
	return IsKeyDown(S9_AD, g_tADC_Result.result[1]);
}

/*
 *********************************************************************************************************
 *	函 数 名: bsp_InitKey
 *	功能说明: 初始化按键. 该函数被 bsp_Init() 调用。
 *	形    参:  无
 *	返 回 值: 无
 *********************************************************************************************************
 */
void bsp_InitKey(void) {
	bsp_InitKeyVar(); /* 初始化按键变量 */
	bsp_InitKeyHard(); /* 初始化按键硬件 */
}

/*
 *********************************************************************************************************
 *	函 数 名: bsp_PutKey
 *	功能说明: 将1个键值压入按键FIFO缓冲区。可用于模拟一个按键。
 *	形    参:  _KeyCode : 按键代码
 *	返 回 值: 无
 *********************************************************************************************************
 */
void bsp_PutKey(uint8_t _KeyCode) {
	s_tKey.Buf[s_tKey.Write] = _KeyCode;

	if (++s_tKey.Write >= KEY_FIFO_SIZE) {
		s_tKey.Write = 0;
	}
}

/*
 *********************************************************************************************************
 *	函 数 名: bsp_GetKey
 *	功能说明: 从按键FIFO缓冲区读取一个键值。
 *	形    参:  无
 *	返 回 值: 按键代码
 *********************************************************************************************************
 */
uint8_t bsp_GetKey(void) {
	uint8_t ret;

	if (s_tKey.Read == s_tKey.Write) {
		return KEY_NONE;
	} else {
		ret = s_tKey.Buf[s_tKey.Read];

		if (++s_tKey.Read >= KEY_FIFO_SIZE) {
			s_tKey.Read = 0;
		}
		return ret;
	}
}

/*
 *********************************************************************************************************
 *	函 数 名: bsp_GetKey2
 *	功能说明: 从按键FIFO缓冲区读取一个键值。独立的读指针。
 *	形    参:  无
 *	返 回 值: 按键代码
 *********************************************************************************************************
 */
uint8_t bsp_GetKey2(void) {
	uint8_t ret;

	if (s_tKey.Read2 == s_tKey.Write) {
		return KEY_NONE;
	} else {
		ret = s_tKey.Buf[s_tKey.Read2];

		if (++s_tKey.Read2 >= KEY_FIFO_SIZE) {
			s_tKey.Read2 = 0;
		}
		return ret;
	}
}

/*
 *********************************************************************************************************
 *	函 数 名: bsp_GetKeyState
 *	功能说明: 读取按键的状态
 *	形    参:  _ucKeyID : 按键ID，从0开始
 *	返 回 值: 1 表示按下， 0 表示未按下
 *********************************************************************************************************
 */
uint8_t bsp_GetKeyState(KEY_ID_E _ucKeyID) {
	return s_tBtn[_ucKeyID].State;
}

/*
 *********************************************************************************************************
 *	函 数 名: bsp_SetKeyParam
 *	功能说明: 设置按键参数
 *	形    参：_ucKeyID : 按键ID，从0开始
 *			_LongTime : 长按事件时间
 *			 _RepeatSpeed : 连发速度
 *	返 回 值: 无
 *********************************************************************************************************
 */
void bsp_SetKeyParam(uint8_t _ucKeyID, uint16_t _LongTime, uint8_t _RepeatSpeed) {
	s_tBtn[_ucKeyID].LongTime = _LongTime; /* 长按时间 0 表示不检测长按键事件 */
	s_tBtn[_ucKeyID].RepeatSpeed = _RepeatSpeed; /* 按键连发的速度，0表示不支持连发 */
	s_tBtn[_ucKeyID].RepeatCount = 0; /* 连发计数器 */
}

/*
 *********************************************************************************************************
 *	函 数 名: bsp_ClearKey
 *	功能说明: 清空按键FIFO缓冲区
 *	形    参：无
 *	返 回 值: 按键代码
 *********************************************************************************************************
 */
void bsp_ClearKey(void) {
	s_tKey.Read = s_tKey.Write;
}

/*
 *********************************************************************************************************
 *	函 数 名: bsp_InitKeyHard
 *	功能说明: 配置按键对应的GPIO
 *	形    参:  无
 *	返 回 值: 无
 *********************************************************************************************************
 */
static void bsp_InitKeyHard(void) {

	set_P0M1_2;
	clr_P0M2_2;

}

/*
 *********************************************************************************************************
 *	函 数 名: bsp_InitKeyVar
 *	功能说明: 初始化按键变量
 *	形    参:  无
 *	返 回 值: 无
 *********************************************************************************************************
 */
static void bsp_InitKeyVar(void) {
	uint8_t i;

	/* 对按键FIFO读写指针清零 */
	s_tKey.Read = 0;
	s_tKey.Write = 0;
	s_tKey.Read2 = 0;

	/* 给每个按键结构体成员变量赋一组缺省值 */
	for (i = 0; i < KEY_COUNT; i++) {
		s_tBtn[i].LongTime = KEY_LONG_TIME; /* 长按时间 0 表示不检测长按键事件 */
		s_tBtn[i].Count = KEY_FILTER_TIME / 2; /* 计数器设置为滤波时间的一半 */
		s_tBtn[i].State = 0; /* 按键缺省状态，0为未按下 */
		//s_tBtn[i].KeyCodeDown = 3 * i + 1;				/* 按键按下的键值代码 */
		//s_tBtn[i].KeyCodeUp   = 3 * i + 2;				/* 按键弹起的键值代码 */
		//s_tBtn[i].KeyCodeLong = 3 * i + 3;				/* 按键被持续按下的键值代码 */
		s_tBtn[i].RepeatSpeed = 0; /* 按键连发的速度，0表示不支持连发 */
		s_tBtn[i].RepeatCount = 0; /* 连发计数器 */
	}

	/* 判断按键按下的函数 */
	s_tBtn[0].IsKeyDownFunc = IsKeyDown1;
	s_tBtn[1].IsKeyDownFunc = IsKeyDown2;
	s_tBtn[2].IsKeyDownFunc = IsKeyDown3;
	s_tBtn[3].IsKeyDownFunc = IsKeyDown4;
	s_tBtn[4].IsKeyDownFunc = IsKeyDown5;
	s_tBtn[5].IsKeyDownFunc = IsKeyDown6;
	s_tBtn[6].IsKeyDownFunc = IsKeyDown7;
	s_tBtn[7].IsKeyDownFunc = IsKeyDown8;
	s_tBtn[8].IsKeyDownFunc = IsKeyDown9;

}

/*
 *********************************************************************************************************
 *	函 数 名: bsp_DetectKey
 *	功能说明: 检测一个按键。非阻塞状态，必须被周期性的调用。
 *	形    参:  按键结构变量指针
 *	返 回 值: 无
 *********************************************************************************************************
 */
KEY_T *pBtn;
static void bsp_DetectKey(uint8_t i) {
	pBtn = &s_tBtn[i];
	if (pBtn->IsKeyDownFunc()) {
		if (pBtn->Count < KEY_FILTER_TIME) {
			pBtn->Count = KEY_FILTER_TIME;
		} else if (pBtn->Count < 2 * KEY_FILTER_TIME) {
			pBtn->Count++;
		} else {
			if (pBtn->State == 0) {
				pBtn->State = 1;

				/* 发送按钮按下的消息 */
				bsp_PutKey((uint8_t) (3 * i + 1));
			}

			if (pBtn->LongTime > 0) {
				if (pBtn->LongCount < pBtn->LongTime) {
					/* 发送按钮持续按下的消息 */
					if (++pBtn->LongCount == pBtn->LongTime) {
						/* 键值放入按键FIFO */
						bsp_PutKey((uint8_t) (3 * i + 3));
					}
				} else {
					if (pBtn->RepeatSpeed > 0) {
						if (++pBtn->RepeatCount >= pBtn->RepeatSpeed) {
							pBtn->RepeatCount = 0;
							/* 常按键后，每隔10ms发送1个按键 */
							bsp_PutKey((uint8_t) (3 * i + 1));
						}
					}
				}
			}
		}
	} else {
		if (pBtn->Count > KEY_FILTER_TIME) {
			pBtn->Count = KEY_FILTER_TIME;
		} else if (pBtn->Count != 0) {
			pBtn->Count--;
		} else {
			if (pBtn->State == 1) {
				pBtn->State = 0;

				/* 发送按钮弹起的消息 */
				bsp_PutKey((uint8_t) (3 * i + 2));
			}
		}
		pBtn->LongCount = 0;
		pBtn->RepeatCount = 0;
	}
}

/*
 *********************************************************************************************************
 *	函 数 名: bsp_KeyScan
 *	功能说明: 扫描所有按键。非阻塞，被systick中断周期性的调用
 *	形    参:  无
 *	返 回 值: 无
 *********************************************************************************************************
 */
void bsp_KeyScan(void) {
	uint8_t i;

	for (i = 0; i < KEY_COUNT; i++) {
		bsp_DetectKey(i);
	}
}

/***************************** (END OF FILE) *********************************/
