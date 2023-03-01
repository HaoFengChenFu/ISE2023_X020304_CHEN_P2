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
	//__HAL_RCC_RTC_CONFIG(RCC_RTCCLKSOURCE_LSE);					// RCC_RTCCLKSOURCE_HSE_DIV10			RCC_RTCCLKSOURCE_LSE
	__HAL_RCC_RTC_ENABLE();
	HAL_PWR_EnableBkUpAccess();
	__HAL_RCC_PWR_CLK_ENABLE();		// Para poder leer los registros

	hrtc.Instance = RTC;
	hrtc.Init.HourFormat = RTC_HOURFORMAT_24;					// 32,768kHz/((127+1)(255+1)) = 1 Hz			// Para LSE 127 y 255, para HSE de 8 MHz es 127 y 6249
	hrtc.Init.AsynchPrediv = 127;			//127;		//0x7f;
	hrtc.Init.SynchPrediv = 255;			//255;		//0x17ff;
	hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
	hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
	hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
	
	// Ajustamos el tiempo
	sTime.Hours = 12;
	sTime.Minutes = 24;
	sTime.Seconds = 56;
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
void Set_Time_RTC(uint8_t hour, uint8_t minute, uint8_t second)
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
void Set_RTC_Date(uint8_t year, uint8_t month, uint8_t week, uint8_t date)
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
void Set_Alarm(uint8_t hour, uint8_t minute, uint8_t second)
{

	sAlarm.AlarmTime.Hours = hour;
	sAlarm.AlarmTime.Minutes = minute;
	sAlarm.AlarmTime.Seconds = second;
	
	sAlarm.AlarmDateWeekDaySel = RTC_ALARMDATEWEEKDAYSEL_DATE;
	sAlarm.AlarmDateWeekDay = 21;
	
	sAlarm.AlarmMask = RTC_ALARMMASK_MINUTES;
	sAlarm.AlarmTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE; 
	sAlarm.AlarmTime.StoreOperation = RTC_STOREOPERATION_RESET;
	sAlarm.Alarm = RTC_ALARM_A;
	
	HAL_RTC_AlarmIRQHandler(&hrtc);
	HAL_NVIC_SetPriority(RTC_Alarm_IRQn, 0, 0);
	HAL_RTC_SetAlarm_IT(&hrtc, &sAlarm, RTC_FORMAT_BIN);

}

/***********************************************************
						Handler de las alarmas
***********************************************************/
void RTC_Alarm_IRQHandler(void)
{
  HAL_RTC_AlarmIRQHandler(&hrtc);
}

/***********************************************************
						Callback de la alarma
***********************************************************/
void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *hrtc) 
{ 
	if(hrtc->Instance == RTC){
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0); // turn on the LED 
		Get_Time_RTC_Binary();
		sTime.Minutes = sTime.Minutes + 1;
		HAL_RTC_SetAlarm_IT(hrtc, &sAlarm, RTC_FORMAT_BIN);
	}
}

/***********************************************************
			Muestra la fecha y el tiempo en el display
***********************************************************/
void Display_Date_Time(void)
{
	RTC_TimeTypeDef gTime;
	RTC_DateTypeDef gDate;
	HAL_RTC_GetTime(&hrtc, &gTime, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc, &gDate, RTC_FORMAT_BIN);
	sprintf(time, "Time: %.2d:%.2d:%.2d", gTime.Hours, gTime.Minutes, gTime.Seconds);
	printf(time, "Time: %.2d:%.2d:%.2d", gTime.Hours, gTime.Minutes, gTime.Seconds);
	HAL_RTC_GetDate(&hrtc, &gDate, RTC_FORMAT_BIN);
	sprintf(date, "Date: %.2d-%.2d-%.4d", gDate.Date, gDate.Month, gDate.Year);

	LCD_symbolToLocalBuffer_L1(time, strlen(time));
	LCD_symbolToLocalBuffer_L2(date, strlen(date));
	LCD_update();
}
