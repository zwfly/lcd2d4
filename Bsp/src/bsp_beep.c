#include "bsp.h"

static idata BEEP_T g_tBeep; /* ���������ȫ�ֽṹ����� */
static BIT delay_flag = 0;
/*
 *********************************************************************************************************
 *	�� �� ��: BEEP_InitHard
 *	����˵��: ��ʼ��������Ӳ��
 *	��    �Σ���
 *	�� �� ֵ: ��
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
 *	�� �� ��: BEEP_Start
 *	����˵��: ������������
 *	��    �Σ�  _usInitTime : ��ʱʱ�䣬��λ10ms; beep��֮ǰ��ʱ��ʱ��; 0��ʾ����ʱ
 *		  _usBeepTime : ����ʱ�䣬��λ10ms; 0 ��ʾ������
 *		  _usStopTime : ֹͣʱ�䣬��λ10ms; 0 ��ʾ��������
 *		  _usCycle : ���д����� 0 ��ʾ��������
 *	�� �� ֵ: ��
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
	g_tBeep.ucEnalbe = 1; /* ������ȫ�ֲ�������ʹ�ܷ�����־ */

	delay_flag = 1;
//	BEEP_ENABLE(); /* ��ʼ���� */
}

/*
 *********************************************************************************************************
 *	�� �� ��: BEEP_Stop
 *	����˵��: ֹͣ��������
 *	��    �Σ���
 *	�� �� ֵ: ��
 *********************************************************************************************************
 */
void BEEP_Stop(void) {
	g_tBeep.ucEnalbe = 0;

	BEEP_DISABLE(); /* ����������Ʊ�־����ֹͣ����������ֹͣ�����ж����ֿ��� */
}

/*
 *********************************************************************************************************
 *	�� �� ��: BEEP_KeyTone
 *	����˵��: ���Ͱ�����
 *	��    �Σ���
 *	�� �� ֵ: ��
 *********************************************************************************************************
 */
void BEEP_KeyTone(void) {
	BEEP_Start(0, 5, 1, 1); /* ����50ms��ͣ10ms�� 1�� */
}

/*
 *********************************************************************************************************
 *	�� �� ��: BEEP_Pro
 *	����˵��: ÿ��10ms����1�θú��������ڿ��Ʒ������������ú����� bsp_timer.c �б����á�
 *	��    �Σ���
 *	�� �� ֵ: ��
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
		if (g_tBeep.usStopTime > 0) /* ��Ϸ��� */
		{
			if (++g_tBeep.usCount >= g_tBeep.usBeepTime) {
				BEEP_DISABLE(); /* ֹͣ���� */
				g_tBeep.usCount = 0;
				g_tBeep.ucState = 1;
			}
		} else {
			; /* �����κδ����������� */
		}
	} else if (g_tBeep.ucState == 1) {
		if (++g_tBeep.usCount >= g_tBeep.usStopTime) {
			/* ��������ʱ��ֱ������stopֹͣΪֹ */
			if (g_tBeep.usCycle > 0) {
				if (++g_tBeep.usCycleCount >= g_tBeep.usCycle) {
					/* ѭ����������ֹͣ���� */
					g_tBeep.ucEnalbe = 0;
				}

				if (g_tBeep.ucEnalbe == 0) {
					g_tBeep.usStopTime = 0;
					return;
				}
			}

			g_tBeep.usCount = 0;
			g_tBeep.ucState = 0;

			BEEP_ENABLE(); /* ��ʼ���� */
		}
	}
}

