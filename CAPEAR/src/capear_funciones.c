#include "LPC17xx.h"
#include "capear_definiciones.h"
#include "uip.h"

#define ICMPBUF ((struct uip_icmpip_hdr *)&uip_buf[UIP_LLH_LEN])
#define UIP_ICMPH_LEN 8		//tamaño del encabezado ICMP

void
pong(char* destipaddr)

	{
	//PROPOSITO DE LA FUNCION: emitir un  PING!!!

	//pero hasta que se descule lo anterior...
	//se togglea el puerto 0 (LED2 por ahora) para indicar que
	//se recibio una respuesta a nuestro PING enviado.

	//NOTA POST: Ya no es nesario!! el ping funciona OKAPA
	/*
	PRT0_PIO->FIOMASK = 0;
	PRT0_PIO->FIOPIN ^= (1 << PRT0_pin);
	*/

	// *uip_buf[UIP_LLH_LEN+UIP_IPH_LEN+8]=(int) 66;
	u8_t tamano_total_datagrama=UIP_IPH_LEN+UIP_ICMPH_LEN;

	//Encabezado del datagrama IP
	ICMPBUF->vhl=0x45;
	ICMPBUF->tos=0x00;
	ICMPBUF->len[0]=0x00;
	ICMPBUF->len[1]=tamano_total_datagrama;
	ICMPBUF->ipid[0]=0xca;
	ICMPBUF->ipid[1]=0x9e;
	ICMPBUF->ipoffset[0]=0x40;
	ICMPBUF->ipoffset[1]=0x00;
	ICMPBUF->ttl=128;
	ICMPBUF->proto=1;	//indica que el datagrama contiene un ICMP
	ICMPBUF->srcipaddr[0]=HTONS((SRV_IP_1 << 8) | SRV_IP_2);
	ICMPBUF->srcipaddr[1]=HTONS((SRV_IP_3 << 8) | SRV_IP_4);
	ICMPBUF->destipaddr[0]=HTONS((IP1 << 8) | IP2);
	ICMPBUF->destipaddr[1]=HTONS((IP3 << 8) | IP4);
	//el checksum lo calculamos al final, una vez que esta armado el resto del encabezado
	ICMPBUF->ipchksum=0;	//es nesario fijarlo a 0 previo a invocar el siguiente
	ICMPBUF->ipchksum= ~(uip_ipchksum());

	//Encabezado del ICMP
	ICMPBUF->type=8;			//indica PING ECHO REQUEST (la respuesta contiene un cero)
	ICMPBUF->icode=0;
	ICMPBUF->id=0x9eca;			//ca9e = CAPE(AR) ;)
	ICMPBUF->seqno=1;
	//el checksum lo calculamos al final, una vez que esta armado el resto del encabezado
	ICMPBUF->icmpchksum=0;
	ICMPBUF->icmpchksum= ~(uip_ICMPchksum((u16_t) tamano_total_datagrama));

	//la siguiente variable es global!
	uip_len=tamano_total_datagrama;

	};
