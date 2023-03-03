#include "SNTP.h"

/**
*			Información sobre el SNTP
*
*			Enlace: https://www.keil.com/pack/doc/mw6/Network/html/group__sntp__routines.html
*				 			file:///C:/Users/fengc/AppData/Local/Arm/Packs/Keil/MDK-Middleware/7.13.0/Doc/Network/html/group__net_s_n_t_pc___func.html
*
*			Información sobre el NET_ADDR, para acceder ir a Network -> Service -> SNTP Server -> Pinchar enlace de la descripción
*			
*			Enlace: file:///C:/Users/fengc/AppData/Local/Arm/Packs/Keil/MDK-Middleware/7.13.0/Doc/Network/html/group__network__structs.html#struct_n_e_t___a_d_d_r
*/


NET_ADDR SNTP_Address;


void Init_SNTP(void){

	SNTP_Address.addr
	SNTP_Address.addr_type = NET_ADDR_IP4;
	SNTP_Address.port
	
	
	netSNTPc_SetMode(netSNTPc_ModeUnicast);
	netSNTPc_GetTime("time.windows.com", (netSNTPc_cb_t) &SNTP_Callback);
	
}

void SNTP_Callback(uint32_t seconds, uint32_t seconds_fraction){
	
}