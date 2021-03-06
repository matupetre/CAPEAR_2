﻿// *********************************************************************
// Define la dirección IP que tendrá el Webserver
// *********************************************************************
//la máscara está prefijada a /24 en forma dura en el código
#define SRV_IP_1	192
#define SRV_IP_2	168
#define SRV_IP_3	0
#define SRV_IP_4	200
//solo es necesario definir el ultimo octeto por ser mascara /24
#define DFG_IP_4	3	//default gateway octeto final


// Define la dirección IP que se pingeará
#define IP1 192
#define IP2 168
#define IP3 0
#define IP4 3


//#define LED_PORT 0 // Port for led
#define GPIO_ALL LPC_GPIO0	//define que todos los "PuertoX" estaran sacados del GPIO#0
//lo anterior se abandona en favor de lo que sigue abajo

//O alternativamente define un GPIO para cada puerto (distinto o no)
#define PRT0_PIO LPC_GPIO0

	/* 	 Definición de los pines que asignaré a cada puerto del webserver
	 *   no confundir "puerto del webserver" (0 a 4) con los GPIO 0 a 3
	 *   Las siguientes elecciones de GPIO/PINES deberían ser totalmente arbitrarias pero se encontró que
	 *   no cualquier elección de GPIO/PIN funciona bien. Se dejaron 4 que sí lo hacen y por lo tanto no
	 *   se garantiza funcionamiento si alguno se cambia
	 */
#define PRT0_PIO LPC_GPIO0	//puerto GPIO corrsp al Puerto0
#define PRT0_pin 22			//pin correspndiente al Puerto0, es el del LED2 de LPCXpresso, para control de funcionamiento

#define PRT1_PIO LPC_GPIO2	//puerto GPIO corrsp al Puerto1
#define PRT1_pin 10			//pin correspndiente al Puerto1

#define PRT2_PIO LPC_GPIO2	//puerto GPIO corrsp al Puerto2
#define PRT2_pin 8			//pin correspndiente al Puerto2

#define PRT3_PIO LPC_GPIO2	//puerto GPIO corrsp al Puerto3
#define PRT3_pin 11			//pin correspndiente al Puerto3

#define PRT4_PIO LPC_GPIO2	//puerto GPIO corrsp al Puerto4
#define PRT4_pin 12			//pin correspndiente al Puerto4


#define PRT0_BIT (1<<PRT0_pin) // Valor absoluto de la palabra si solo cuenta el pin de este puerto
#define PRT1_BIT (1<<PRT1_pin) // Valor absoluto de la palabra si solo cuenta el pin de este puerto
#define PRT2_BIT (1<<PRT2_pin) // Valor absoluto de la palabra si solo cuenta el pin de este puerto
#define PRT3_BIT (1<<PRT3_pin) // Valor absoluto de la palabra si solo cuenta el pin de este puerto
#define PRT4_BIT (1<<PRT4_pin) // Valor absoluto de la palabra si solo cuenta el pin de este puerto

int pong_flag, pong_enable;

//u16_t uip_ICMPchksum(u16_t tamano_total_datagrama);		//by CAPEAR
void pong(char* destipaddr);
