#include "rtc.h"
#include "lcd.h"
/*********************************************************************
		Inspiración: https://controllerstech.com/internal-rtc-in-stm32/
*********************************************************************/

RTC_HandleTypeDef hrtc;
RTC_AlarmTypeDef sAlarm;
RTC_TimeTypeDef sTime;
RTC_DateTypeDef sDate;

char time[30];
char date[30];
/***********************************************************
							Inicialización del RTC
***********************************************************/
void RTC_Init(void)
{
	__HAL_RCC_RTC_ENABLE();
	__HAL_RCC_PWR_CLK_ENABLE();		// Para poder leer los registros
	HAL_PWR_EnableBkUpAccess();
	hrtc.Instance = RTC;
	hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
	hrtc.Init.AsynchPrediv = 0x7f;
	hrtc.Init.SynchPrediv = 0x17ff;
	hrtc.Init.OutPut = RTC_OUTPUT_ALARMA;
	hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
	hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
	
	// Ajustamos el tiempo
	sTime.Hours = 12;
	sTime.Minutes = 24;
	sTime.Seconds = 15;
	sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
	sTime.StoreOperation = RTC_STOREOPERATION_RESET;
	HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
	
	// Ajustamos la fecha
	sDate.Year = 23;
	sDate.Month = RTC_MONTH_FEBRUARY;
	sDate.WeekDay = RTC_WEEKDAY_MONDAY;
	sDate.Date = 21;
	
	HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
	
	HAL_NVIC_EnableIRQ(RTC_Alarm_IRQn);		// Habilitamos las interrupciones de las alarma del RTC
	HAL_RTC_Init(&hrtc);
}

/***********************************************************
						Obtención del tiempo en binario
***********************************************************/
void Get_Time_RTC_Binary(void)
{
	HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
}

/***********************************************************
						Ajusta un nuevo tiempo
***********************************************************/
void Set_Time_RTC(uint16_t hour, uint16_t minute, uint16_t second)
{
	sTime.Hours = hour;
	sTime.Minutes = minute;
	sTime.Seconds = second;
	sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
	sTime.StoreOperation = RTC_STOREOPERATION_RESET;
	
	HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
}
/***********************************************************
						Obtención de la fecha en binario
***********************************************************/
void Get_Date_RTC()
{
	HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
}

/***********************************************************
						Ajusta una nueva fecha
***********************************************************/
void Set_RTC_Date(uint16_t year, uint16_t month,uint16_t week, uint16_t date)
{
	sDate.Year = year;
	sDate.Month = month;
	sDate.WeekDay = week;
	sDate.Date = date;
	HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
}
/***********************************************************
						Coloca una alarma
***********************************************************/
void Set_Alarm(uint16_t hour, uint16_t minute, uint16_t second)
{

	sAlarm.AlarmTime.Hours = hour;
	sAlarm.AlarmTime.Minutes = minute;
	sAlarm.AlarmTime.Seconds = second;
	
	sAlarm.AlarmMask = RTC_ALARMMASK_ALL;
	sAlarm.AlarmTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE; 
	sAlarm.AlarmTime.StoreOperation = RTC_STOREOPERATION_RESET;
	sAlarm.Alarm = RTC_ALARM_A;
	
	HAL_RTC_AlarmIRQHandler(&hrtc);
	HAL_RTC_SetAlarm_IT(&hrtc, &sAlarm, RTC_FORMAT_BIN);

}

/***********************************************************
						Callback de la alarma
***********************************************************/
void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *hrtc) 
{ 
	//if(hrtc->Instance == RTC){
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0); // turn on the LED 
		Get_Time_RTC_Binary();
		sTime.Seconds = sTime.Seconds + 5;
		HAL_RTC_SetAlarm_IT(hrtc, &sAlarm, RTC_FORMAT_BIN);
	//}
}

/***********************************************************
			Muestra la fecha y el tiempo en el display
***********************************************************/
void Display_Date_Time(void)
{
	Get_Time_RTC_Binary();
	sprintf(time, "Time: %.2d:%.2d:%.2d", sTime.Hours, sTime.Minutes, sTime.Seconds);
	
	Get_Date_RTC();
	sprintf(date, "Date: %.2d-%.2d-%.2d", sDate.Date, sDate.Month, sDate.Year);

	LCD_symbolToLocalBuffer_L1(time, strlen(time));
	LCD_symbolToLocalBuffer_L2(date, strlen(date));
	LCD_update();
}
