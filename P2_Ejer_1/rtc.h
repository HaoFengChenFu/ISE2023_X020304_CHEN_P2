#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_rtc.h"
#include "stdint.h"

#ifndef __RTC_H
#define __RTC_H

#include "stdio.h"
#include "string.h"

void RTC_Init(void);
void Get_Time_RTC_Binary(void);
void Set_Time_RTC(uint16_t hour, uint16_t minute, uint16_t second);
void Get_Date_RTC(void);
void Set_RTC_Date(uint16_t year, uint16_t month,uint16_t week, uint16_t date);
void Set_Alarm(uint16_t hour, uint16_t minute, uint16_t second);

void Display_Date_Time(void);
#endif
