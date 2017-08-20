/*
 *********************************************************************************************************
 *
 *	ģ������ : ������������ģ��
 *	�ļ����� : bsp_key.c
 *	��    �� : V1.0
 *	˵    �� : ɨ�������������������˲����ƣ����а���FIFO�����Լ�������¼���
 *				(1) ��������
 *				(2) ��������
 *				(3) ������
 *				(4) ����ʱ�Զ�����
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
static idata KEY_FIFO_T s_tKey; /* ����FIFO����,�ṹ�� */

static void bsp_InitKeyVar(void);
static void bsp_InitKeyHard(void);
static void bsp_DetectKey(uint8_t i);

/*
 *********************************************************************************************************
 *	�� �� ��: IsKeyDownX
 *	����˵��: �жϰ����Ƿ���
 *	��    ��: ��
 *	�� �� ֵ: ����ֵ1 ��ʾ���£�0��ʾδ����
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
 *	�� �� ��: bsp_InitKey
 *	����˵��: ��ʼ������. �ú����� bsp_Init() ���á�
 *	��    ��:  ��
 *	�� �� ֵ: ��
 *********************************************************************************************************
 */
void bsp_InitKey(void) {
	bsp_InitKeyVar(); /* ��ʼ���������� */
	bsp_InitKeyHard(); /* ��ʼ������Ӳ�� */
}

/*
 *********************************************************************************************************
 *	�� �� ��: bsp_PutKey
 *	����˵��: ��1����ֵѹ�밴��FIFO��������������ģ��һ��������
 *	��    ��:  _KeyCode : ��������
 *	�� �� ֵ: ��
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
 *	�� �� ��: bsp_GetKey
 *	����˵��: �Ӱ���FIFO��������ȡһ����ֵ��
 *	��    ��:  ��
 *	�� �� ֵ: ��������
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
 *	�� �� ��: bsp_GetKey2
 *	����˵��: �Ӱ���FIFO��������ȡһ����ֵ�������Ķ�ָ�롣
 *	��    ��:  ��
 *	�� �� ֵ: ��������
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
 *	�� �� ��: bsp_GetKeyState
 *	����˵��: ��ȡ������״̬
 *	��    ��:  _ucKeyID : ����ID����0��ʼ
 *	�� �� ֵ: 1 ��ʾ���£� 0 ��ʾδ����
 *********************************************************************************************************
 */
uint8_t bsp_GetKeyState(KEY_ID_E _ucKeyID) {
	return s_tBtn[_ucKeyID].State;
}

/*
 *********************************************************************************************************
 *	�� �� ��: bsp_SetKeyParam
 *	����˵��: ���ð�������
 *	��    �Σ�_ucKeyID : ����ID����0��ʼ
 *			_LongTime : �����¼�ʱ��
 *			 _RepeatSpeed : �����ٶ�
 *	�� �� ֵ: ��
 *********************************************************************************************************
 */
void bsp_SetKeyParam(uint8_t _ucKeyID, uint16_t _LongTime, uint8_t _RepeatSpeed) {
	s_tBtn[_ucKeyID].LongTime = _LongTime; /* ����ʱ�� 0 ��ʾ����ⳤ�����¼� */
	s_tBtn[_ucKeyID].RepeatSpeed = _RepeatSpeed; /* �����������ٶȣ�0��ʾ��֧������ */
	s_tBtn[_ucKeyID].RepeatCount = 0; /* ���������� */
}

/*
 *********************************************************************************************************
 *	�� �� ��: bsp_ClearKey
 *	����˵��: ��հ���FIFO������
 *	��    �Σ���
 *	�� �� ֵ: ��������
 *********************************************************************************************************
 */
void bsp_ClearKey(void) {
	s_tKey.Read = s_tKey.Write;
}

/*
 *********************************************************************************************************
 *	�� �� ��: bsp_InitKeyHard
 *	����˵��: ���ð�����Ӧ��GPIO
 *	��    ��:  ��
 *	�� �� ֵ: ��
 *********************************************************************************************************
 */
static void bsp_InitKeyHard(void) {

	set_P0M1_2;
	clr_P0M2_2;

}

/*
 *********************************************************************************************************
 *	�� �� ��: bsp_InitKeyVar
 *	����˵��: ��ʼ����������
 *	��    ��:  ��
 *	�� �� ֵ: ��
 *********************************************************************************************************
 */
static void bsp_InitKeyVar(void) {
	uint8_t i;

	/* �԰���FIFO��дָ������ */
	s_tKey.Read = 0;
	s_tKey.Write = 0;
	s_tKey.Read2 = 0;

	/* ��ÿ�������ṹ���Ա������һ��ȱʡֵ */
	for (i = 0; i < KEY_COUNT; i++) {
		s_tBtn[i].LongTime = KEY_LONG_TIME; /* ����ʱ�� 0 ��ʾ����ⳤ�����¼� */
		s_tBtn[i].Count = KEY_FILTER_TIME / 2; /* ����������Ϊ�˲�ʱ���һ�� */
		s_tBtn[i].State = 0; /* ����ȱʡ״̬��0Ϊδ���� */
		//s_tBtn[i].KeyCodeDown = 3 * i + 1;				/* �������µļ�ֵ���� */
		//s_tBtn[i].KeyCodeUp   = 3 * i + 2;				/* ��������ļ�ֵ���� */
		//s_tBtn[i].KeyCodeLong = 3 * i + 3;				/* �������������µļ�ֵ���� */
		s_tBtn[i].RepeatSpeed = 0; /* �����������ٶȣ�0��ʾ��֧������ */
		s_tBtn[i].RepeatCount = 0; /* ���������� */
	}

	/* �жϰ������µĺ��� */
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
 *	�� �� ��: bsp_DetectKey
 *	����˵��: ���һ��������������״̬�����뱻�����Եĵ��á�
 *	��    ��:  �����ṹ����ָ��
 *	�� �� ֵ: ��
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

				/* ���Ͱ�ť���µ���Ϣ */
				bsp_PutKey((uint8_t) (3 * i + 1));
			}

			if (pBtn->LongTime > 0) {
				if (pBtn->LongCount < pBtn->LongTime) {
					/* ���Ͱ�ť�������µ���Ϣ */
					if (++pBtn->LongCount == pBtn->LongTime) {
						/* ��ֵ���밴��FIFO */
						bsp_PutKey((uint8_t) (3 * i + 3));
					}
				} else {
					if (pBtn->RepeatSpeed > 0) {
						if (++pBtn->RepeatCount >= pBtn->RepeatSpeed) {
							pBtn->RepeatCount = 0;
							/* ��������ÿ��10ms����1������ */
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

				/* ���Ͱ�ť�������Ϣ */
				bsp_PutKey((uint8_t) (3 * i + 2));
			}
		}
		pBtn->LongCount = 0;
		pBtn->RepeatCount = 0;
	}
}

/*
 *********************************************************************************************************
 *	�� �� ��: bsp_KeyScan
 *	����˵��: ɨ�����а���������������systick�ж������Եĵ���
 *	��    ��:  ��
 *	�� �� ֵ: ��
 *********************************************************************************************************
 */
void bsp_KeyScan(void) {
	uint8_t i;

	for (i = 0; i < KEY_COUNT; i++) {
		bsp_DetectKey(i);
	}
}

/***************************** (END OF FILE) *********************************/
