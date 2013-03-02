﻿/*
 * Copyright (c) 2001, Adam Dunkels.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *      This product includes software developed by Adam Dunkels.
 * 4. The name of the author may not be used to endorse or promote
 *    products derived from this software without specific prior
 *    written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * This file is part of the uIP TCP/IP stack.
 *
 * $Id: main.c,v 1.16 2006/06/11 21:55:03 adam Exp $
 *
 */


//#define LED_ON 1 	// Level to set port to turn on led
//#define LED_OFF 0 	// Level to set port to turn off led

#include "LPC17xx.h"
//#include "lpc17xx_gpio.h"
//#include "lpc17xx_clkpwr.h"
#include "timer.h"
#include "uip.h"
#include "uip_arp.h"
#include "tapdev.h"

#include "capear_definiciones.h"	//by CAPEAR

#define BUF ((struct uip_eth_hdr *)&uip_buf[0])

/*--------------------------- uip_log ---------------------------------*/

void uip_log(char *m)
	{
	//printf("uIP log message: %s\n", m);
	}

/*--------------------------- main ---------------------------------*/

char ipstring [20];

int main(void)
	{
	//Configuracion del pin 22 del puerto 0 GPIO

	/*
	unsigned long LED_PINS  =  ((uint32_t)1<<22);

	//Enable GPIO Clock

	CLKPWR_ConfigPPWR(CLKPWR_PCONP_PCGPIO, ENABLE);

	//LEDs on PORT2.2 & PORT2.4 defined as Output

	//GPIO_SetDir(0, LED_PINS, 1);
	*/

	//LPC_PINCON->PINSEL1    &= (~(3 << 12));
	//LPC_GPIO0->FIODIR |= (PRT0_BIT+PRT1_BIT+PRT2_BIT+PRT3_BIT+PRT4_BIT); //pines definidos como "salida digital"
	PRT0_PIO->FIODIR |= PRT0_BIT;	//pin corresp.al puerto 0 definido como salida digital
	PRT1_PIO->FIODIR |= PRT1_BIT;	//pin corresp.al puerto 1 definido como salida digital
	PRT2_PIO->FIODIR |= PRT2_BIT;	//pin corresp.al puerto 2 definido como salida digital
	PRT3_PIO->FIODIR |= PRT3_BIT;	//pin corresp.al puerto 3 definido como salida digital
	PRT4_PIO->FIODIR |= PRT4_BIT;	//pin corresp.al puerto 4 definido como salida digital

	//LPC_GPIO0->FIOCLR = LED_BIT; //turn off the LED
	//LPC_GPIO0->FIOSET = LED_BIT; //turn off the LED

	//Se continua con el resto del codigo

	unsigned int i;

	uip_ipaddr_t ipaddr;
	/* 
	 La variable "ipaddr" es donde se guardará la IP local. Representa un array
	 de dos enteros sin signo de 16 bits (para el caso de una direccion IPv4).
	 Sacado de uip.h, lineas 61 a 67
	*/

	struct timer periodic_timer, arp_timer;

	//Si se utiliza CMSIS la rutina SystemInit() es llamada en el codigo de inicio
	//(cr_startup_lpc176x.c), caso contrario se la llama aqui

	#ifndef __USE_CMSIS
		SystemInit(); //Setup de los "core clocks"
	#endif

	clock_init(); //Inicializacion del reloj

	//Se utilizan dos timers

	timer_set(&periodic_timer, CLOCK_SECOND / 2); /* 0.5s */
	timer_set(&arp_timer, CLOCK_SECOND * 10);	/* 10s */
	
	//ethernet init

	tapdev_init();

	//Initialize the uIP TCP/IP stack.

	uip_init();

	uip_ipaddr(ipaddr, SRV_IP_1,SRV_IP_2,SRV_IP_3,SRV_IP_4);
	uip_sethostaddr(ipaddr); // host IP address, esto sería el webserver
	uip_ipaddr(ipaddr, SRV_IP_1,SRV_IP_2,SRV_IP_3,DFG_IP_4);
	uip_setdraddr(ipaddr);	// router IP address, esto sería el "def.gateway"
	uip_ipaddr(ipaddr, 255,255,255,0);	//mascara fijada en forma "dura"
	uip_setnetmask(ipaddr);	/* mask */

	//Initialize the HTTP server, listen to port 80.

	httpd_init();

	while(1)
		{
		//receive packet and put in uip_buf
		uip_len = tapdev_read(uip_buf);		//lee si el buffer recibió un frame
		/*
		 * En caso de haber recibido algo, a partir de ahora hay un frame
		 * entero de Ethernet, o sea: [ETH.header+ETH.DATA(=IP.header+IP.DATA)]
		 * dentro de la variable *uip_buf* y la longitud de este paquete está
		 * guardada en la variable*uip_len*.
		 * Si no hay paquete entonces necesariamente uip_len será 0.
		 *
		 * Por ultimo, uip_len y uip_buf no son variables cualquiera (notese
		 * que no fueron definidas en este archivo!). Son variables globales
		 * inherentes a microIP(uIP), las cuales son usadas y leídas por el
		 * "core" de uIP casi permanentemente. De hecho, todas las funciones
		 * propias de uIP (aquellas que comienzan con el prefijo "uip_" se
		 * basarán en los datos que hallen dentro de uip_buf y uip_len
		 */
    	if(uip_len > 0) //received packet		//si efectivamente hay "algo"...
    		{
		
    		/* Si entramos aquí ya sabemos que un frame Ethernet "aterrizó" en
    		 * el puerto LAN, ahora se fijará de qué clase de paquete se trata.
    		 * Esto lo verifica mirando el Ethernet header, el cual tiene un
    		 * campo para especificar el tipo de datos que transporta. Para
    		 * paquetes IP este campo vale 0x0800, para paquetes ARP vale 0x0806
    		 */

      		if(BUF->type == htons(UIP_ETHTYPE_IP))	/* IP packet */
			
			//si recibio un paquete IP (del tipo que sea) procede con esto:
      			{
	      		uip_arp_ipin();	//aprovecha y refresca la tabla ARP cacheada
	      		uip_input();	//es una interfaz Ethernet-->IP
	      		/*Basicamente uip_input hace todo, pero todo lo necesario para
	      		 * el protocolo IP: establece conexiones, continua conexiones
	      		 * abiertas, etc, etc. Obviamente es muy compleja, sin embargo
	      		 * aqui lo que tenemos que saber es que "se hace cargo" de los
	      		 * paquetes entrantes y que por otro lado, como muchos de estos
	      		 * paquetes entrantes podrían requerir que se envíe respuesta,
	      		 * uip_input deja depositada tal respuesta (en caso de ser)
	      		 * en las variables globales uip_buf y uip_len<>0. De hecho
	      		 * uip_input() "limpiará" uip_buf y uip_len=0 si no hay
	      		 * respuesta en puerta, y los llenará con la respuesta en caso
	      		 * de ser necesario.
	      		 */

	      		//If the above function invocation resulted in data that
	         	//should be sent out on the network, the global variable
	         	//uip_len is set to a value > 0.
 
	      		if(uip_len > 0)
        			{
					//#if defined ( _RDB1768_)
	      				//if (firstconnection == 0)
	      					//firstconnection = 1;
					//#endif

	      			uip_arp_out();
	        		tapdev_send(uip_buf,uip_len);
        			}
      			}

      		else if(BUF->type == htons(UIP_ETHTYPE_ARP))	/*ARP packet */

			//si en cambio recibio un miserable ARP, procede con esto otro:

	      		{
	        	uip_arp_arpin();

	        	//If the above function invocation resulted in data that
		        //should be sent out on the network, the global variable
		        //uip_len is set to a value > 0.

		      	if(uip_len > 0)
	        		tapdev_send(uip_buf,uip_len); //ARP ack
		      	}
    		}

    	else if(timer_expired(&periodic_timer))	//no packet but time out (0.5s)
    		{
      		timer_reset(&periodic_timer);
      		for(i = 0; i < UIP_CONNS; i++)
      			{
      			uip_periodic(i);

      			//If the above function invocation resulted in data that
		        //should be sent out on the network, the global variable
		        //uip_len is set to a value > 0.

		        if(uip_len > 0)
		        	{
		        	uip_arp_out();
		        	tapdev_send(uip_buf,uip_len);
		        	}
      			}

			#if UIP_UDP
				for(i = 0; i < UIP_UDP_CONNS; i++)
					{
					uip_udp_periodic(i);

					//If the above function invocation resulted in data that
					//should be sent out on the network, the global variable
					//uip_len is set to a value > 0.

					if(uip_len > 0)
						{
						uip_arp_out();
						tapdev_send();
						}
					}

			#endif //UIP_UDP

			//Call the ARP timer function every 10 seconds.

			if(timer_expired(&arp_timer))
				{
				timer_reset(&arp_timer);
				uip_arp_timer();
				}
    		}
		}
	}
