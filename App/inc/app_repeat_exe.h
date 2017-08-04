/*
 * app_repeat_exe.h
 *
 *  Created on: 2017年7月6日
 *      Author: admin
 */

#ifndef APP_INC_APP_REPEAT_EXE_H_
#define APP_INC_APP_REPEAT_EXE_H_

typedef struct _REPEAT_T {
	uint8_t ucEnalbe;
	uint8_t ucState;
	uint16_t usStartTime;
	uint16_t usStopTime;
	uint16_t usCycle;
	uint16_t usCount;
	uint16_t usCycleCount;

	void (*Start)(void);
	void (*Stop)(void);

} REPEAT_T;

/* 供外部调用的函数声明 */
void Repeat_Init(void);
void Repeat_Start(uint16_t _usStartTime, uint16_t _usStopTime,
		uint16_t _usCycle);
void Repeat_Stop(void);

//void Repeat_Start_exe(void);
//void Repeat_Stop_exe(void);
void Repeat_SetStart(void (*fun)(void));
void Repeat_SetStop(void (*fun)(void));

void Repeat_Pro(void);

#endif /* APP_INC_APP_REPEAT_EXE_H_ */
