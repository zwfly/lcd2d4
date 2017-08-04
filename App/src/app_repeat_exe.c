/*
 * app_repeat_exe.c
 *
 *  Created on: 2017年7月6日
 *      Author: admin
 */

#include "app.h"

static REPEAT_T g_tRepeat; /* 定义蜂鸣器全局结构体变量 */

void Repeat_SetStart(void (*fun)(void)) {
	g_tRepeat.Start = fun;
}

void Repeat_SetStop(void (*fun)(void)) {
	g_tRepeat.Stop = fun;
}

static void Repeat_Start_exe(void) {
	if (g_tRepeat.Start != 0) {
		g_tRepeat.Start();
	}
}

static void Repeat_Stop_exe(void) {
	if (g_tRepeat.Stop != 0) {
		g_tRepeat.Stop();
	}
}

/*
 *********************************************************************************************************
 *	函 数 名:
 *	功能说明: 启动。
 *	形    参：_usBeepTime : 蜂鸣时间，单位100ms; 0 表示不鸣叫
 *			  _usStopTime : 停止时间，单位100ms; 0 表示持续鸣叫
 *			 _usCycle : 鸣叫次数， 0 表示持续鸣叫
 *	返 回 值: 无
 *********************************************************************************************************
 */
void Repeat_Start(uint16_t _usStartTime, uint16_t _usStopTime,
		uint16_t _usCycle) {
	if (_usStartTime == 0) {
		return;
	}

	g_tRepeat.usStartTime = _usStartTime;
	g_tRepeat.usStopTime = _usStopTime;
	g_tRepeat.usCycle = _usCycle;
	g_tRepeat.usCount = 0;
	g_tRepeat.usCycleCount = 0;
	g_tRepeat.ucState = 0;
	g_tRepeat.ucEnalbe = 1; /* 设置完全局参数后再使能发声标志 */

	Repeat_Start_exe(); /* 开始发声 */
}

/*
 *********************************************************************************************************
 *	函 数 名:
 *	功能说明: 停止。
 *	形    参：无
 *	返 回 值: 无
 *********************************************************************************************************
 */
void Repeat_Stop(void) {
	g_tRepeat.ucEnalbe = 0;
	Repeat_Stop_exe(); /* 必须在清控制标志后再停止发声，避免停止后在中断中又开启 */
	Repeat_SetStart(0);
	Repeat_SetStop(0);

}

/*
 *********************************************************************************************************
 *	函 数 名:
 *	功能说明: 每隔100ms调用1次该函数，用于控制蜂鸣器发声。该函数在  中被调用。
 *	形    参：无
 *	返 回 值: 无
 *********************************************************************************************************
 */
void Repeat_Pro(void) {

	if (g_tDevice.status == E_PowerDown) {
		Repeat_Stop();
		return;
	}

	if ((g_tRepeat.ucEnalbe == 0) || (g_tRepeat.usStopTime == 0)) {
		return;
	}

	if (g_tRepeat.ucState == 0) {
		if (g_tRepeat.usStopTime > 0) /* 间断 */
		{
			if (++g_tRepeat.usCount >= g_tRepeat.usStartTime) {
				Repeat_Stop_exe(); /* 停止 */
				g_tRepeat.usCount = 0;
				g_tRepeat.ucState = 1;
			}
		} else {
			/* 不做任何处理，连续 */
		}
	} else if (g_tRepeat.ucState == 1) {
		if (++g_tRepeat.usCount >= g_tRepeat.usStopTime) {
			/* 连续时，直到调用stop停止为止 */
			if (g_tRepeat.usCycle > 0) {
				if (++g_tRepeat.usCycleCount >= g_tRepeat.usCycle) {
					/* 循环次数到，停止 */
					g_tRepeat.ucEnalbe = 0;
				}

				if (g_tRepeat.ucEnalbe == 0) {
					g_tRepeat.usStopTime = 0;
					return;
				}
			}
			g_tRepeat.usCount = 0;
			g_tRepeat.ucState = 0;

			Repeat_Start_exe(); /* 开始 */
		}
	}

}
