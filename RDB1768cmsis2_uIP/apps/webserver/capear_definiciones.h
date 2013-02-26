// *********************************************************************
// Define the IP address to be used for the MCU running the TCP/IP stack
// *********************************************************************

//la máscara está prefijada a /24 en forma dura en el código
#define SRV_IP_1	192
#define SRV_IP_2	168
#define SRV_IP_3	0
#define SRV_IP_4	200
//solo es necesario definir el ultimo octeto por ser mascara /24
#define DFG_IP_4	3	//default gateway octeto final

//#define LED_PORT 0 // Port for led
#define GPIO_ALL LPC_GPIO0	//define que todos los "PuertoX" estaran sacados del GPIO#0

//define los pines que asignaré a cada puerto del webserver
//  no confundir "puerto del webserver" (0 a 4, re-arbitrarios) con los GPIO(0 a 3)
#define PRT0_pin 22		//pin correspndiente al Puerto0, es el del LED2!!
#define PRT1_pin 5		//pin correspndiente al Puerto1
#define PRT2_pin 7		//pin correspndiente al Puerto2
#define PRT3_pin 9		//pin correspndiente al Puerto3
#define PRT4_pin 11		//pin correspndiente al Puerto4

#define PRT0_BIT (1<<PRT0_pin) // Valor absoluto de la palabra si solo cuenta el pin de este puerto
#define PRT1_BIT (1<<PRT1_pin) // Valor absoluto de la palabra si solo cuenta el pin de este puerto
#define PRT2_BIT (1<<PRT2_pin) // Valor absoluto de la palabra si solo cuenta el pin de este puerto
#define PRT3_BIT (1<<PRT3_pin) // Valor absoluto de la palabra si solo cuenta el pin de este puerto
#define PRT4_BIT (1<<PRT4_pin) // Valor absoluto de la palabra si solo cuenta el pin de este puerto