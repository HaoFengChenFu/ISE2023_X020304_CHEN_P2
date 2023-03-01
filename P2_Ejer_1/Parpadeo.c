#include "cmsis_os2.h"                          // CMSIS RTOS header file
#include "stm32f4xx_hal.h"
#include "Parpadeo.h"
/*----------------------------------------------------------------------------
 *      Thread 1 'Thread_Name': Sample thread
 *---------------------------------------------------------------------------*/
 
osThreadId_t tid_Thread_Parpadeo;                        // thread id
 
void Parpadeo (void *argument);                   // thread function
 
int Init_Parpadeo (void) {
 
  tid_Thread_Parpadeo = osThreadNew(Parpadeo, NULL, NULL);
  if (tid_Thread_Parpadeo == NULL) {
    return(-1);
  }
 
  return(0);
}
 
void Parpadeo (void *argument) {
 
  while (1) {
		osThreadFlagsWait(1, osFlagsWaitAny, osWaitForever);	
		// Parpadea durante 5 segundos
		for(int i = 0; i < 10; i++){		// Parpadea 10 veces
			HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);
			osDelay(500);									// 0,5 ms * 10 =  5 segundos
		}
		osThreadYield();
  }
}
