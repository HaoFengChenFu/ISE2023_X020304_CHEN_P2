#include "stdint.h"

#ifndef __SNTP_H
#define __SNTP_H
	#include "cmsis_os2.h"                  // ::CMSIS:RTOS2
	#include "rl_net.h"                     // Keil.MDK-Pro::Network:CORE
	#include "Net_Config_SNTP_Client.h"
	
	#include "stm32f4xx_hal.h"
	
	int Init_SNTP(void);
	void SNTP_Callback(uint32_t seconds, uint32_t seconds_fraction);
	
#endif
