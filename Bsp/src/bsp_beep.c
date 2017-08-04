#include "bsp.h"

static idata BEEP_T g_tBeep; /* 定义蜂鸣器全局结构体变量 */
static BIT delay_flag = 0;
/*
 *********************************************************************************************************
 *	函 数 名: BEEP_InitHard
 *	功能说明: 初始化蜂鸣器硬件
 *	形    参：无
 *	返 回 值: 无
 *********************************************************************************************************
 */
void BEEP_InitHard(void) {
#if 1
	P3M1 &= ~SET_BIT0;
	P3M2 |= SET_BIT0;

	clr_P30;
#endif

	/*  PWM period = (R2AH + R2AL) * Pre-scale / Fsys, Fsys = 11.0592MHz (HIRC)
	 If R2AH = R2AL, PWM output 50% duty cycle
	 Min frequency is about 20Hz, while Pre-scale = 1/1024 and R2AH = R2AL = 255
	 Max frequency is around 5.5MHz, while Pre-scale = 1/1 and R2AH = R2AL = 1   */

	/* Determine Timer 2D pre-scalar */
	clr_T2DPS2;
	set_T2DPS1;
	set_T2DPS0;

	/* Determine Timer 2D Reload Low Byte */
	R2DL = 128;
	/* Determine Timer 2D Reload High Byte */
	R2DH = 128;

	/* Set T2D as PWM mode */
	set_T2DM;

	/* Enable Timer2D interrupt */
//	set_ET2D;
//	set_EA;
	/* set T2AO1(P1.5)/T2AO2(P1.6) pin to toggling output */
//	set_T2DOE1;
//	set_T2DOE2;
	/* start Timer2D */
	set_TR2D;

	g_tBeep.ucEnalbe = 0;

}

void BEEP_ENABLE() {
	set_T2DOE1;
	set_P30;
}

void BEEP_DISABLE() {
	clr_T2DOE1;

	clr_P30;

}
/*
 *********************************************************************************************************
 *	函 数 名: BEEP_Start
 *	功能说明: 启动蜂鸣音。
 *	形    参：  _usInitTime : 延时时间，单位10ms; beep响之前延时的时间; 0表示不延时
 *		  _usBeepTime : 蜂鸣时间，单位10ms; 0 表示不鸣叫
 *		  _usStopTime : 停止时间，单位10ms; 0 表示持续鸣叫
 *		  _usCycle : 鸣叫次数， 0 表示持续鸣叫
 *	返 回 值: 无
 *********************************************************************************************************
 */
void BEEP_Start(uint16_t _usDelayTime, uint16_t _usBeepTime,
		uint16_t _usStopTime, uint16_t _usCycle) {
	if (_usBeepTime == 0) {
		return;
	}
	g_tBeep.usDelayTime = _usDelayTime;
	g_tBeep.usBeepTime = _usBeepTime;
	g_tBeep.usStopTime = _usStopTime;
	g_tBeep.usCycle = _usCycle;
	g_tBeep.usCount = 0;
	g_tBeep.usCycleCount = 0;
	g_tBeep.ucState = 0;
	g_tBeep.ucEnalbe = 1; /* 设置完全局参数后再使能发声标志 */

	delay_flag = 1;
//	BEEP_ENABLE(); /* 开始发声 */
}

/*
 *********************************************************************************************************
 *	函 数 名: BEEP_Stop
 *	功能说明: 停止蜂鸣音。
 *	形    参：无
 *	返 回 值: 无
 *********************************************************************************************************
 */
void BEEP_Stop(void) {
	g_tBeep.ucEnalbe = 0;

	BEEP_DISABLE(); /* 必须在清控制标志后再停止发声，避免停止后在中断中又开启 */
}

/*
 *********************************************************************************************************
 *	函 数 名: BEEP_KeyTone
 *	功能说明: 发送按键音
 *	形    参：无
 *	返 回 值: 无
 *********************************************************************************************************
 */
void BEEP_KeyTone(void) {
	BEEP_Start(0, 5, 1, 1); /* 鸣叫50ms，停10ms， 1次 */
}

/*
 *********************************************************************************************************
 *	函 数 名: BEEP_Pro
 *	功能说明: 每隔10ms调用1次该函数，用于控制蜂鸣器发声。该函数在 bsp_timer.c 中被调用。
 *	形    参：无
 *	返 回 值: 无
 *********************************************************************************************************
 */
void BEEP_Pro(void) {
	if ((g_tBeep.ucEnalbe == 0) || (g_tBeep.usStopTime == 0)) {
		return;
	}
	if (g_tBeep.usDelayTime) {
		g_tBeep.usDelayTime--;
		return;
	}
	if (delay_flag) {
		delay_flag = 0;
		BEEP_ENABLE();
	}

	if (g_tBeep.ucState == 0) {
		if (g_tBeep.usStopTime > 0) /* 间断发声 */
		{
			if (++g_tBeep.usCount >= g_tBeep.usBeepTime) {
				BEEP_DISABLE(); /* 停止发声 */
				g_tBeep.usCount = 0;
				g_tBeep.ucState = 1;
			}
		} else {
			; /* 不做任何处理，连续发声 */
		}
	} else if (g_tBeep.ucState == 1) {
		if (++g_tBeep.usCount >= g_tBeep.usStopTime) {
			/* 连续发声时，直到调用stop停止为止 */
			if (g_tBeep.usCycle > 0) {
				if (++g_tBeep.usCycleCount >= g_tBeep.usCycle) {
					/* 循环次数到，停止发声 */
					g_tBeep.ucEnalbe = 0;
				}

				if (g_tBeep.ucEnalbe == 0) {
					g_tBeep.usStopTime = 0;
					return;
				}
			}

			g_tBeep.usCount = 0;
			g_tBeep.ucState = 0;

			BEEP_ENABLE(); /* 开始发声 */
		}
	}
}

