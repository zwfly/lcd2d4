/*
 *********************************************************************************************************
 *
 *	ģ������ : ��������ģ��
 *	�ļ����� : bsp_key.h
 *	��    �� : V1.0
 *	˵    �� : ͷ�ļ�
 *
 *********************************************************************************************************
 */

#ifndef __BSP_KEY_H
#define __BSP_KEY_H

#define KEY_COUNT    10

/* ����Ӧ�ó���Ĺ��������������� */
#define KEY_DOWN_K1		KEY_1_DOWN
#define KEY_UP_K1		KEY_1_UP
#define KEY_LONG_K1		KEY_1_LONG

#define KEY_DOWN_K2		KEY_2_DOWN
#define KEY_UP_K2		KEY_2_UP
#define KEY_LONG_K2		KEY_2_LONG

#define KEY_DOWN_K3		KEY_3_DOWN
#define KEY_UP_K3		KEY_3_UP
#define KEY_LONG_K3		KEY_3_LONG

#define KEY_DOWN_K4		KEY_4_DOWN
#define KEY_UP_K4		KEY_4_UP
#define KEY_LONG_K4		KEY_4_LONG

#define KEY_DOWN_K5		KEY_5_DOWN
#define KEY_UP_K5		KEY_5_UP
#define KEY_LONG_K5		KEY_5_LONG

#define KEY_DOWN_K6		KEY_6_DOWN
#define KEY_UP_K6		KEY_6_UP
#define KEY_LONG_K6		KEY_6_LONG

#define KEY_DOWN_K7		KEY_7_DOWN
#define KEY_UP_K7		KEY_7_UP
#define KEY_LONG_K7		KEY_7_LONG

#define KEY_DOWN_K8		KEY_8_DOWN
#define KEY_UP_K8		KEY_8_UP
#define KEY_LONG_K8		KEY_8_LONG

#define KEY_DOWN_K9		KEY_9_DOWN
#define KEY_UP_K9		KEY_9_UP
#define KEY_LONG_K9		KEY_9_LONG

#define KEY_DOWN_K2_6	KEY_2_6_DOWN
#define KEY_UP_K2_6		KEY_2_6_UP
#define KEY_LONG_K2_6	KEY_2_6_LONG

/* ����ID, ��Ҫ����bsp_KeyState()��������ڲ��� */
typedef enum {
	KID_K1 = 0,
	KID_K2,
	KID_K3,
	KID_K4,
	KID_K5,
	KID_K6,
	KID_K7,
	KID_K8,
	KID_K9,
	KID_K2_6,

} KEY_ID_E;

/*
 �����˲�ʱ��50ms, ��λ10ms��
 ֻ��������⵽50ms״̬�������Ϊ��Ч����������Ͱ��������¼�
 ��ʹ������·����Ӳ���˲������˲�����Ҳ���Ա�֤�ɿ��ؼ�⵽�����¼�
 */
#define KEY_FILTER_TIME   5
#define KEY_LONG_TIME     150			/* ��λ10ms�� ����1�룬��Ϊ�����¼� */

/*
 ÿ��������Ӧ1��ȫ�ֵĽṹ�������
 */
typedef struct {
	/* ������һ������ָ�룬ָ���жϰ����ַ��µĺ��� */
	uint8_t (*IsKeyDownFunc)(void); /* �������µ��жϺ���,1��ʾ���� */

	uint8_t Count; /* �˲��������� */
	uint16_t LongCount; /* ���������� */
	uint16_t LongTime; /* �������³���ʱ��, 0��ʾ����ⳤ�� */
	uint8_t State; /* ������ǰ״̬�����»��ǵ��� */
	uint8_t RepeatSpeed; /* ������������ */
	uint8_t RepeatCount; /* �������������� */
} KEY_T;

/*
 �����ֵ����, ���밴���´���ʱÿ�����İ��¡�����ͳ����¼�

 �Ƽ�ʹ��enum, ����#define��ԭ��
 (1) ����������ֵ,�������˳��ʹ���뿴���������
 (2) �������ɰ����Ǳ����ֵ�ظ���
 */
typedef enum {
	KEY_NONE = 0, /* 0 ��ʾ�����¼� */

	KEY_1_DOWN, /* 1������ */
	KEY_1_UP, /* 1������ */
	KEY_1_LONG, /* 1������ */

	KEY_2_DOWN, /* 2������ */
	KEY_2_UP, /* 2������ */
	KEY_2_LONG, /* 2������ */

	KEY_3_DOWN, /* 3������ */
	KEY_3_UP, /* 3������ */
	KEY_3_LONG, /* 3������ */

	KEY_4_DOWN, /* 4������ */
	KEY_4_UP, /* 4������ */
	KEY_4_LONG, /* 4������ */

	KEY_5_DOWN, /* 5������ */
	KEY_5_UP, /* 5������ */
	KEY_5_LONG, /* 5������ */

	KEY_6_DOWN, /* 6������ */
	KEY_6_UP, /* 6������ */
	KEY_6_LONG, /* 6������ */

	KEY_7_DOWN, /* 7������ */
	KEY_7_UP, /* 7������ */
	KEY_7_LONG, /* 7������ */

	KEY_8_DOWN, /* 8������ */
	KEY_8_UP, /* 8������ */
	KEY_8_LONG, /* 8������ */

	KEY_9_DOWN, /* 9������ */
	KEY_9_UP, /* 9������ */
	KEY_9_LONG, /* 9������ */

	KEY_2_6_DOWN, KEY_2_6_UP, KEY_2_6_LONG,
} KEY_ENUM;

/* ����FIFO�õ����� */
#define KEY_FIFO_SIZE	10
typedef struct {
	uint8_t Buf[KEY_FIFO_SIZE]; /* ��ֵ������ */
	uint8_t Read; /* ��������ָ��1 */
	uint8_t Write; /* ������дָ�� */
	uint8_t Read2; /* ��������ָ��2 */
} KEY_FIFO_T;

/* ���ⲿ���õĺ������� */
void bsp_InitKey(void);
void bsp_KeyScan(void);
void bsp_PutKey(uint8_t _KeyCode);
uint8_t bsp_GetKey(void);
uint8_t bsp_GetKey2(void);
uint8_t bsp_GetKeyState(KEY_ID_E _ucKeyID);
void bsp_SetKeyParam(uint8_t _ucKeyID, uint16_t _LongTime, uint8_t _RepeatSpeed);
void bsp_ClearKey(void);

#endif

/*****************************(END OF FILE) *********************************/
