#ifndef _BSP_H_
#define _BSP_H

#include <stdio.h>
#include <N76E616.h>
#include "Version.h"
#include "Typedef.h"
#include "Define.h"
#include "SFR_Macro.h"
#include "Common.h"
#include "Delay.h"
//#include "Display.h"

#include "bsp_key.h"
#include "bsp_lcdBright.h"
#include "bsp_keyBright.h"
#include "bsp_display.h"
#include "bsp_2d4.h"
#include "bsp_timer0.h"
#include "bsp_timer1.h"
#include "bsp_adc.h"


#ifndef TRUE
#define TRUE  1
#endif

#ifndef FALSE
#define FALSE 0
#endif

void bsp_Init(void);


#endif

/***************************** (END OF FILE) *********************************/
