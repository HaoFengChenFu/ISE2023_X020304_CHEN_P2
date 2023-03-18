#include "cmsis_os2.h"                          // CMSIS RTOS header file
#include "stm32f4xx_hal.h"
#include "Parpadeo.h"
#include "stdio.h"
/*----------------------------------------------------------------------------
 *      Thread 1 'Thread_Name': Sample thread
 *---------------------------------------------------------------------------*/
 
osThreadId_t tid_Thread_Parpadeo;                        // thread id

uint16_t valorPeriodoAlarma;

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
		
		for(int i = 0; i < (5*1000)/(valorPeriodoAlarma); i++){		// Parpadea durante 5 segundos ---> 5 segundos / Periodo de la Alarma, con esto obtienes cuantas veces debe parpadear hasta llegar a los 5 segundos
			//printf("Funciona\n");
			HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);
			osDelay(valorPeriodoAlarma);
		}
		
		
		
//		// Parpadea durante 5 segundos
//		for(int i = 0; i < 20; i++){		// Parpadea 20 veces
//			//printf("Funciona\n");
//			HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);
//			osDelay(250);									// 0,25 ms * 20 =  5 segundos
//		}
		osThreadYield();
  }
}
