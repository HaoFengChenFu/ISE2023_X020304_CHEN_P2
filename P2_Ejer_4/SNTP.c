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
*
*			Puertos de red: https://es.wikipedia.org/wiki/Anexo:Puertos_de_red
*/


NET_ADDR SNTP_Address;
uint8_t address_spain_server[4] = {51, 145, 123, 29};

void Init_SNTP(void){
	for(int i = 0; i < 4; i++){
		SNTP_Address.addr[i] = address_spain_server[i];
	}
	SNTP_Address.addr_type = NET_ADDR_IP4;
	SNTP_Address.port = 123;			// Esta es para UDP, para la de TCP es 119
	
	
	netSNTPc_SetMode(netSNTPc_ModeUnicast);
	// Haciendo nslookup time.windows.com sacamos las direcciones IP
	// Otra información importante: https://www.pool.ntp.org/zone/es
	netSNTPc_GetTime(&SNTP_Address, (netSNTPc_cb_t) &SNTP_Callback);
	
}

void SNTP_Callback(uint32_t seconds, uint32_t seconds_fraction){
	
}