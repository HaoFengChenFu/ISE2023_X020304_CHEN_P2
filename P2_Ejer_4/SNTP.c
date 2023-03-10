#include "stm32f4xx_hal.h"
#include <stdio.h>
#include <string.h>
#include "cmsis_os2.h"                          // CMSIS RTOS header file
#include "SNTP.h"
#include "rl_net.h"
#include <time.h>

const  NET_ADDR4 ntp_server = { NET_ADDR_IP4 , 0, 217, 79, 179, 106 };
static void time_callback (uint32_t seconds, uint32_t seconds_fraction);
 
void get_time (void) {
  if (netSNTPc_GetTime (NULL, time_callback) == netOK) {
    printf ("SNTP request sent.\n");
  }
  else {
    printf ("SNTP not ready or bad parameters.\n");
  }
}
 
static void time_callback (uint32_t seconds, uint32_t seconds_fraction) {
  if (seconds == 0) {
    printf ("Server not responding or bad response.\n");
  }
  else {
    printf ("%d seconds elapsed since 1.1.1970\n", seconds);
    getLocalTime(seconds);
  }
}

void getLocalTime(uint32_t seconds)
{
  time_t rawtime = seconds;
  struct tm ts;
  char buf[80];
  
  ts = *localtime(&rawtime);
  strftime(buf, sizeof(buf), "%a %Y-%m-%d %H:%M:%S %Z", &ts);
  printf("%s\n", buf);
}
