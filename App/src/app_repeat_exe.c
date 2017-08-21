/*
 * app_repeat_exe.c
 *
 *  Created on: 2017��7��6��
 *      Author: admin
 */

#include "app.h"

static REPEAT_T g_tRepeat; /* ���������ȫ�ֽṹ����� */

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
 *	�� �� ��:
 *	����˵��: ������
 *	��    �Σ�_usBeepTime : ����ʱ�䣬��λ100ms; 0 ��ʾ������
 *			  _usStopTime : ֹͣʱ�䣬��λ100ms; 0 ��ʾ��������
 *			 _usCycle : ���д����� 0 ��ʾ��������
 *	�� �� ֵ: ��
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
	g_tRepeat.ucEnalbe = 1; /* ������ȫ�ֲ�������ʹ�ܷ�����־ */

	Repeat_Start_exe(); /* ��ʼ���� */
}

/*
 *********************************************************************************************************
 *	�� �� ��:
 *	����˵��: ֹͣ��
 *	��    �Σ���
 *	�� �� ֵ: ��
 *********************************************************************************************************
 */
void Repeat_Stop(void) {
	g_tRepeat.ucEnalbe = 0;
	Repeat_Stop_exe(); /* ����������Ʊ�־����ֹͣ����������ֹͣ�����ж����ֿ��� */
	Repeat_SetStart(0);
	Repeat_SetStop(0);

}

/*
 *********************************************************************************************************
 *	�� �� ��:
 *	����˵��: ÿ��100ms����1�θú��������ڿ��Ʒ������������ú�����  �б����á�
 *	��    �Σ���
 *	�� �� ֵ: ��
 *********************************************************************************************************
 */
void Repeat_Pro(void) {

	if ((g_tRepeat.ucEnalbe == 0) || (g_tRepeat.usStopTime == 0)) {
		return;
	}

	if (g_tRepeat.ucState == 0) {
		if (g_tRepeat.usStopTime > 0) /* ��� */
		{
			if (++g_tRepeat.usCount >= g_tRepeat.usStartTime) {
				Repeat_Stop_exe(); /* ֹͣ */
				g_tRepeat.usCount = 0;
				g_tRepeat.ucState = 1;
			}
		} else {
			/* �����κδ������� */
		}
	} else if (g_tRepeat.ucState == 1) {
		if (++g_tRepeat.usCount >= g_tRepeat.usStopTime) {
			/* ����ʱ��ֱ������stopֹͣΪֹ */
			if (g_tRepeat.usCycle > 0) {
				if (++g_tRepeat.usCycleCount >= g_tRepeat.usCycle) {
					/* ѭ����������ֹͣ */
					g_tRepeat.ucEnalbe = 0;
				}

				if (g_tRepeat.ucEnalbe == 0) {
					g_tRepeat.usStopTime = 0;
					return;
				}
			}
			g_tRepeat.usCount = 0;
			g_tRepeat.ucState = 0;

			Repeat_Start_exe(); /* ��ʼ */
		}
	}

}
