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

static KEY_T s_tBtn[KEY_COUNT];
static KEY_FIFO_T s_tKey; /* ����FIFO����,�ṹ�� */

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
#if 0
static uint8_t IsKeyDown1(void) {
	return !P03;
}
static uint8_t IsKeyDown2(void) {
	return !P04;
}
static uint8_t IsKeyDown3(void) {
	return !P05;
}
static uint8_t IsKeyDown4(void) {
	return !P06;
}
#else
static uint8_t IsKeyDown1(void) {
	if (P03) {
		return 0;
	} else {
		return 1;
	}
}
static uint8_t IsKeyDown2(void) {
	if (P04) {
		return 0;
	} else {
		return 1;
	}
}
static uint8_t IsKeyDown3(void) {
	if (P05) {
		return 0;
	} else {
		return 1;
	}
}
static uint8_t IsKeyDown4(void) {
	if (P06) {
		return 0;
	} else {
		return 1;
	}
}
#if DEBUG_KEY
static uint8_t IsKeyDown5(void) {
	if (P55) {
		return 0;
	} else {
		return 1;
	}
}
#endif
#endif

/* S1 S3��ϼ� */
static uint8_t IsKeyDown_1and3(void) {
	if ((P03 == 0) && (P05 == 0)) {
		return 1;
	} else {
		return 0;
	}
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

	set_P0M1_3;
	clr_P0M2_3;

	set_P0M1_4;
	clr_P0M2_4;

	set_P0M1_5;
	clr_P0M2_5;

	set_P0M1_6;
	clr_P0M2_6;

#if DEBUG_KEY
	P5M1 |= 0x20;
	P5M2 &= ~0x20;
#endif
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
#if DEBUG_KEY
	s_tBtn[4].IsKeyDownFunc = IsKeyDown5;
	s_tBtn[5].IsKeyDownFunc = IsKeyDown_1and3;
#else
	s_tBtn[4].IsKeyDownFunc = IsKeyDown_1and3;
#endif

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
