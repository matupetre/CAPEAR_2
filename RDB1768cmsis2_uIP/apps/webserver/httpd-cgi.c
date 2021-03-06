﻿/**
 * \addtogroup httpd
 * @{
 */

/**
 * \file
 *         Web server script interface
 * \author
 *         Adam Dunkels <adam@sics.se>
 *
 */

/*
 * Copyright (c) 2001-2006, Adam Dunkels.
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
 * 3. The name of the author may not be used to endorse or promote
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
 * $Id: httpd-cgi.c,v 1.2 2006/06/11 21:46:37 adam Exp $
 *
 */

#include "uip.h"
#include "psock.h"
#include "httpd.h"
#include "httpd-cgi.h"
#include "httpd-fs.h"

#include "capear_definiciones.h"	//by CAPEAR

#include <stdio.h>
#include <string.h>


#include "LPC17xx.h"


// Funciones originales
/*
HTTPD_CGI_CALL(file, "file-stats", file_stats);
HTTPD_CGI_CALL(tcp, "tcp-connections", tcp_stats);
HTTPD_CGI_CALL(net, "net-stats", net_stats);
HTTPD_CGI_CALL(port, "port-status", port_status);
HTTPD_CGI_CALL(toggle, "port-toggle", port_toggle);
*/

//Funciones de CAPEAR

//para el puerto 0 (el argumento del medio es el que se invoca desde la pagina web)
HTTPD_CGI_CALL(prt0sw, "prt0-sw", prt0_sw);	//by CAPEAR ; SWITCH ESTADO
HTTPD_CGI_CALL(prt0on, "prt0-on", prt0_on);	//by CAPEAR ; ENCIENDE 
HTTPD_CGI_CALL(prt0of, "prt0-of", prt0_of);	//by CAPEAR ; APAGA
HTTPD_CGI_CALL(prt0st, "prt0-st", prt0_st);	//by CAPEAR ; ESTADO ACTUAL=1/0
HTTPD_CGI_CALL(prt0s1, "prt0-s1", prt0_s1);	//by CAPEAR ; ESTADO ACTUAL=ON?("disable")
HTTPD_CGI_CALL(prt0s0, "prt0-s0", prt0_s0);	//by CAPEAR ; ESTADO ACTUAL=OFF?("")

//para el puerto 1
HTTPD_CGI_CALL(prt1sw, "prt1-sw", prt1_sw);	//by CAPEAR 
HTTPD_CGI_CALL(prt1on, "prt1-on", prt1_on);	//by CAPEAR  
HTTPD_CGI_CALL(prt1of, "prt1-of", prt1_of);	//by CAPEAR 
HTTPD_CGI_CALL(prt1st, "prt1-st", prt1_st);	//by CAPEAR
HTTPD_CGI_CALL(prt1s1, "prt1-s1", prt1_s1);	//by CAPEAR
HTTPD_CGI_CALL(prt1s0, "prt1-s0", prt1_s0);	//by CAPEAR

//para el puerto 2
HTTPD_CGI_CALL(prt2sw, "prt2-sw", prt2_sw);	//by CAPEAR 
HTTPD_CGI_CALL(prt2on, "prt2-on", prt2_on);	//by CAPEAR 
HTTPD_CGI_CALL(prt2of, "prt2-of", prt2_of);	//by CAPEAR 
HTTPD_CGI_CALL(prt2st, "prt2-st", prt2_st);	//by CAPEAR
HTTPD_CGI_CALL(prt2s1, "prt2-s1", prt2_s1);	//by CAPEAR
HTTPD_CGI_CALL(prt2s0, "prt2-s0", prt2_s0);	//by CAPEAR

//para el puerto 3
HTTPD_CGI_CALL(prt3sw, "prt3-sw", prt3_sw);	//by CAPEAR 
HTTPD_CGI_CALL(prt3on, "prt3-on", prt3_on);	//by CAPEAR 
HTTPD_CGI_CALL(prt3of, "prt3-of", prt3_of);	//by CAPEAR 
HTTPD_CGI_CALL(prt3st, "prt3-st", prt3_st);	//by CAPEAR
HTTPD_CGI_CALL(prt3s1, "prt3-s1", prt3_s1);	//by CAPEAR
HTTPD_CGI_CALL(prt3s0, "prt3-s0", prt3_s0);	//by CAPEAR

//para el puerto 4
HTTPD_CGI_CALL(prt4sw, "prt4-sw", prt4_sw);	//by CAPEAR 
HTTPD_CGI_CALL(prt4on, "prt4-on", prt4_on);	//by CAPEAR 
HTTPD_CGI_CALL(prt4of, "prt4-of", prt4_of);	//by CAPEAR 
HTTPD_CGI_CALL(prt4st, "prt4-st", prt4_st);	//by CAPEAR
HTTPD_CGI_CALL(prt4s1, "prt4-s1", prt4_s1);	//by CAPEAR
HTTPD_CGI_CALL(prt4s0, "prt4-s0", prt4_s0);	//by CAPEAR
HTTPD_CGI_CALL(prt4pg, "prt4-pg", prt4_pg);	//by CAPEAR ***NUEVA***

//mapa de puertos (abandonada)
//HTTPD_CGI_CALL(prtmap, "prt-map", prt_map);	//by CAPEAR



/* by CAPEAR antes
HTTPD_CGI_CALL(portof, "port-of", port_of);		//by CAPEAR
HTTPD_CGI_CALL(porton, "port-on", prt0_on);		//by CAPEAR
HTTPD_CGI_CALL(portston, "port-st-on", port_st_on);	//by CAPEAR
HTTPD_CGI_CALL(portstof, "port-st-of", port_st_of);	//by CAPEAR

static const struct httpd_cgi_call *calls[] = { &file, &tcp, &net, &port, &toggle, NULL };
*/


//Listado de funciones
static const struct httpd_cgi_call *calls[] = { &prt0sw, &prt0on, &prt0of, &prt0st, &prt0s1, &prt0s0, \
						&prt1sw, &prt1on, &prt1of, &prt1st, &prt1s1, &prt1s0, \
						&prt2sw, &prt2on, &prt2of, &prt2st, &prt2s1, &prt2s0, \
						&prt3sw, &prt3on, &prt3of, &prt3st, &prt3s1, &prt3s0, \
						&prt4sw, &prt4on, &prt4of, &prt4st, &prt4s1, &prt4s0, &prt4pg, \
					/*	&prtmap, \ 	//funcion abandonada */
						NULL };

/*---------------------------------------------------------------------------*/
static
PT_THREAD(nullfunction(struct httpd_state *s, char *ptr))
{
  PSOCK_BEGIN(&s->sout);
  PSOCK_END(&s->sout);
}
/*---------------------------------------------------------------------------*/
httpd_cgifunction
httpd_cgi(char *name)
{
  const struct httpd_cgi_call **f;

  /* Find the matching name in the table, return the function. */
  for(f = calls; *f != NULL; ++f) {
    if(strncmp((*f)->name, name, strlen((*f)->name)) == 0) {
      return (*f)->function;
    }
  }
  return nullfunction;
}



// ANULO FUNCIONES QUE NO UTILIZAR�



/*---------------TOGGLES (prtX_sw)-------------------------------------------*/
/*---------------------------------------------------------------------------*/
static
PT_THREAD(prt0_sw(struct httpd_state *s, char *ptr))
{
  PSOCK_BEGIN(&s->sout);
  PRT0_PIO->FIOMASK = 0;
  PRT0_PIO->FIOPIN ^= (1 << PRT0_pin);
  PSOCK_END(&s->sout);
}

/*---------------------------------------------------------------------------*/
static
PT_THREAD(prt1_sw(struct httpd_state *s, char *ptr))
{
  PSOCK_BEGIN(&s->sout);
  PRT0_PIO->FIOMASK = 0;
  PRT0_PIO->FIOPIN ^= (1 << PRT1_pin);
  PSOCK_END(&s->sout);
}

/*---------------------------------------------------------------------------*/
static
PT_THREAD(prt2_sw(struct httpd_state *s, char *ptr))
{
  PSOCK_BEGIN(&s->sout);
  PRT2_PIO->FIOMASK = 0;
  PRT2_PIO->FIOPIN ^= (1 << PRT2_pin);
  PSOCK_END(&s->sout);
}

/*---------------------------------------------------------------------------*/
static
PT_THREAD(prt3_sw(struct httpd_state *s, char *ptr))
{
  PSOCK_BEGIN(&s->sout);
  PRT3_PIO->FIOMASK = 0;
  PRT3_PIO->FIOPIN ^= (1 << PRT3_pin);
  PSOCK_END(&s->sout);
}

/*---------------------------------------------------------------------------*/
static
PT_THREAD(prt4_sw(struct httpd_state *s, char *ptr))
{
  PSOCK_BEGIN(&s->sout);
  PRT4_PIO->FIOMASK = 0;
  PRT4_PIO->FIOPIN ^= (1 << PRT4_pin);
  PSOCK_END(&s->sout);
}


/*-----------------ONs (prtX_on)---------------------------------------------*/
/*---------------------------------------------------------------------------*/
static
PT_THREAD(prt0_on(struct httpd_state *s, char *ptr))
{
  PSOCK_BEGIN(&s->sout);
  PRT0_PIO->FIOMASK = 0;
  PRT0_PIO->FIOPIN = (1 << PRT0_pin);
  PSOCK_END(&s->sout);
}

/*---------------------------------------------------------------------------*/
static
PT_THREAD(prt1_on(struct httpd_state *s, char *ptr))
{
  PSOCK_BEGIN(&s->sout);
  PRT1_PIO->FIOMASK = 0;
  PRT1_PIO->FIOPIN = (1 << PRT1_pin);
  PSOCK_END(&s->sout);
}

/*---------------------------------------------------------------------------*/
static
PT_THREAD(prt2_on(struct httpd_state *s, char *ptr))
{
  PSOCK_BEGIN(&s->sout);
  PRT2_PIO->FIOMASK = 0;
  PRT2_PIO->FIOPIN = (1 << PRT2_pin);
  PSOCK_END(&s->sout);
}

/*---------------------------------------------------------------------------*/
static
PT_THREAD(prt3_on(struct httpd_state *s, char *ptr))
{
  PSOCK_BEGIN(&s->sout);
  PRT3_PIO->FIOMASK = 0;
  PRT3_PIO->FIOPIN = (1 << PRT3_pin);
  PSOCK_END(&s->sout);
}

/*---------------------------------------------------------------------------*/
//by CAPEAR
static
PT_THREAD(prt4_on(struct httpd_state *s, char *ptr))
{
  PSOCK_BEGIN(&s->sout);
  PRT4_PIO->FIOMASK = 0;
  PRT4_PIO->FIOPIN = (1 << PRT4_pin);
  PSOCK_END(&s->sout);
}

/*-----------------OFFs (prtX_of)--------------------------------------------*/
/*---------------------------------------------------------------------------*/
static
PT_THREAD(prt0_of(struct httpd_state *s, char *ptr))
{
  PSOCK_BEGIN(&s->sout);
  PRT0_PIO->FIOMASK = 0;
  PRT0_PIO->FIOPIN = (0 << PRT0_pin);
  PSOCK_END(&s->sout);
}

/*---------------------------------------------------------------------------*/
static
PT_THREAD(prt1_of(struct httpd_state *s, char *ptr))
{
  PSOCK_BEGIN(&s->sout);
  PRT1_PIO->FIOMASK = 0;
  PRT1_PIO->FIOPIN = (0 << PRT1_pin);
  PSOCK_END(&s->sout);
}
/*---------------------------------------------------------------------------*/
static
PT_THREAD(prt2_of(struct httpd_state *s, char *ptr))
{
  PSOCK_BEGIN(&s->sout);
  PRT2_PIO->FIOMASK = 0;
  PRT2_PIO->FIOPIN = (0 << PRT2_pin);
  PSOCK_END(&s->sout);
}
/*---------------------------------------------------------------------------*/
static
PT_THREAD(prt3_of(struct httpd_state *s, char *ptr))
{
  PSOCK_BEGIN(&s->sout);
  PRT3_PIO->FIOMASK = 0;
  PRT3_PIO->FIOPIN = (0 << PRT3_pin);
  PSOCK_END(&s->sout);
}
/*---------------------------------------------------------------------------*/
static
PT_THREAD(prt4_of(struct httpd_state *s, char *ptr))
{
  PSOCK_BEGIN(&s->sout);
  PRT4_PIO->FIOMASK = 0;
  PRT4_PIO->FIOPIN = (0 << PRT4_pin);
  PSOCK_END(&s->sout);
}

/*----------------STATUS ST (prtX_st)----------------------------------------*/
/*---------------------------------------------------------------------------*/
static unsigned short
generate_prt0_st(void *arg)		//esta función ayuda a la que debe obtener el estado actual del puerto
{
	unsigned int prt0_st;

	PRT0_PIO->FIOMASK = 0;
	prt0_st = !!(PRT0_PIO->FIOPIN & (1 << PRT0_pin));
	return snprintf((char *)uip_appdata, UIP_APPDATA_SIZE,
			"%s ",  (prt0_st ? "1":"0"));
}

static
PT_THREAD(prt0_st(struct httpd_state *s, char *ptr))
{

  PSOCK_BEGIN(&s->sout);
  PSOCK_GENERATOR_SEND(&s->sout, generate_prt0_st, s);
  PSOCK_END(&s->sout);
}

/*---------------------------------------------------------------------------*/
static unsigned short
generate_prt1_st(void *arg)		//esta función ayuda a la que debe obtener el estado actual del puerto
{
	unsigned int prt1_st;

	PRT1_PIO->FIOMASK = 0;
	prt1_st = !!(PRT1_PIO->FIOPIN & (1 << PRT1_pin));
	return snprintf((char *)uip_appdata, UIP_APPDATA_SIZE,
			"%s ",  (prt1_st ? "1":"0"));
}

static
PT_THREAD(prt1_st(struct httpd_state *s, char *ptr))
{

  PSOCK_BEGIN(&s->sout);
  PSOCK_GENERATOR_SEND(&s->sout, generate_prt1_st, s);
  PSOCK_END(&s->sout);
}

/*---------------------------------------------------------------------------*/
static unsigned short
generate_prt2_st(void *arg)		//esta función ayuda a la que debe obtener el estado actual del puerto
{
	unsigned int prt2_st;

	PRT2_PIO->FIOMASK = 0;
	prt2_st = !!(PRT2_PIO->FIOPIN & (1 << PRT2_pin));
	return snprintf((char *)uip_appdata, UIP_APPDATA_SIZE,
			"%s ",  (prt2_st ? "1":"0"));
}

static
PT_THREAD(prt2_st(struct httpd_state *s, char *ptr))
{

  PSOCK_BEGIN(&s->sout);
  PSOCK_GENERATOR_SEND(&s->sout, generate_prt2_st, s);
  PSOCK_END(&s->sout);
}

/*---------------------------------------------------------------------------*/
static unsigned short
generate_prt3_st(void *arg)		//esta función ayuda a la que debe obtener el estado actual del puerto
{
	unsigned int prt3_st;

	PRT3_PIO->FIOMASK = 0;
	prt3_st = !!(PRT3_PIO->FIOPIN & (1 << PRT3_pin));
	return snprintf((char *)uip_appdata, UIP_APPDATA_SIZE,
			"%s ",  (prt3_st ? "1":"0"));
}

static
PT_THREAD(prt3_st(struct httpd_state *s, char *ptr))
{

  PSOCK_BEGIN(&s->sout);
  PSOCK_GENERATOR_SEND(&s->sout, generate_prt3_st, s);
  PSOCK_END(&s->sout);
}

/*---------------------------------------------------------------------------*/
static unsigned short
generate_prt4_st(void *arg)		//esta función ayuda a la que debe obtener el estado actual del puerto
{
	unsigned int prt4_st;

	PRT4_PIO->FIOMASK = 0;
	prt4_st = !!(PRT4_PIO->FIOPIN & (1 << PRT4_pin));
	return snprintf((char *)uip_appdata, UIP_APPDATA_SIZE,
			"%s ",  (prt4_st ? "1":"0"));
}

static
PT_THREAD(prt4_st(struct httpd_state *s, char *ptr))
{

  PSOCK_BEGIN(&s->sout);
  PSOCK_GENERATOR_SEND(&s->sout, generate_prt4_st, s);
  PSOCK_END(&s->sout);
}


/*----------------STATUS S1 (prtX_st)----------------------------------------*/
/*---------------------------------------------------------------------------*/
static unsigned short
generate_prt0_s1(void *arg)		//esta función ayuda a la que debe obtener el estado actual del puerto
{
	unsigned int prt0_s1;

	PRT0_PIO->FIOMASK = 0;
	prt0_s1 = !!(PRT0_PIO->FIOPIN & (1 << PRT0_pin));
	return snprintf((char *)uip_appdata, UIP_APPDATA_SIZE,
			"%s ",  (prt0_s1 ? "disabled":""));
}

static
PT_THREAD(prt0_s1(struct httpd_state *s, char *ptr))
{

  PSOCK_BEGIN(&s->sout);
  PSOCK_GENERATOR_SEND(&s->sout, generate_prt0_s1, s);
  PSOCK_END(&s->sout);
}

/*---------------------------------------------------------------------------*/
static unsigned short
generate_prt1_s1(void *arg)		//esta función ayuda a la que debe obtener el estado actual del puerto
{
	unsigned int prt1_s1;

	PRT1_PIO->FIOMASK = 0;
	prt1_s1 = !!(PRT1_PIO->FIOPIN & (1 << PRT1_pin));
	return snprintf((char *)uip_appdata, UIP_APPDATA_SIZE,
			"%s ",  (prt1_s1 ? "disabled":""));
}

static
PT_THREAD(prt1_s1(struct httpd_state *s, char *ptr))
{

  PSOCK_BEGIN(&s->sout);
  PSOCK_GENERATOR_SEND(&s->sout, generate_prt1_s1, s);
  PSOCK_END(&s->sout);
}
/*---------------------------------------------------------------------------*/
static unsigned short
generate_prt2_s1(void *arg)		//esta función ayuda a la que debe obtener el estado actual del puerto
{
	unsigned int prt2_s1;

	PRT2_PIO->FIOMASK = 0;
	prt2_s1 = !!(PRT2_PIO->FIOPIN & (1 << PRT2_pin));
	return snprintf((char *)uip_appdata, UIP_APPDATA_SIZE,
			"%s ",  (prt2_s1 ? "disabled":""));
}

static
PT_THREAD(prt2_s1(struct httpd_state *s, char *ptr))
{

  PSOCK_BEGIN(&s->sout);
  PSOCK_GENERATOR_SEND(&s->sout, generate_prt2_s1, s);
  PSOCK_END(&s->sout);
}
/*---------------------------------------------------------------------------*/
static unsigned short
generate_prt3_s1(void *arg)		//esta función ayuda a la que debe obtener el estado actual del puerto
{
	unsigned int prt3_s1;

	PRT3_PIO->FIOMASK = 0;
	prt3_s1 = !!(PRT3_PIO->FIOPIN & (1 << PRT3_pin));
	return snprintf((char *)uip_appdata, UIP_APPDATA_SIZE,
			"%s ",  (prt3_s1 ? "disabled":""));
}

static
PT_THREAD(prt3_s1(struct httpd_state *s, char *ptr))
{

  PSOCK_BEGIN(&s->sout);
  PSOCK_GENERATOR_SEND(&s->sout, generate_prt3_s1, s);
  PSOCK_END(&s->sout);
}
/*---------------------------------------------------------------------------*/
static unsigned short
generate_prt4_s1(void *arg)		//esta función ayuda a la que debe obtener el estado actual del puerto
{
	unsigned int prt4_s1;

	PRT4_PIO->FIOMASK = 0;
	prt4_s1 = !!(PRT4_PIO->FIOPIN & (1 << PRT4_pin));
	return snprintf((char *)uip_appdata, UIP_APPDATA_SIZE,
			"%s ",  (prt4_s1 ? "disabled":""));
}

static
PT_THREAD(prt4_s1(struct httpd_state *s, char *ptr))
{

  PSOCK_BEGIN(&s->sout);
  PSOCK_GENERATOR_SEND(&s->sout, generate_prt4_s1, s);
  PSOCK_END(&s->sout);
}


/*----------------STATUS S0 (prtX_st)----------------------------------------*/
/*---------------------------------------------------------------------------*/
static unsigned short
generate_prt0_s0(void *arg)		//esta función ayuda a la que debe obtener el estado actual del puerto
{
	unsigned int prt0_s0;

	PRT0_PIO->FIOMASK = 0;
	prt0_s0 = !!(PRT0_PIO->FIOPIN & (1 << PRT0_pin));
	return snprintf((char *)uip_appdata, UIP_APPDATA_SIZE,
			"%s ",  (prt0_s0 ? "":"disabled"));
}

static
PT_THREAD(prt0_s0(struct httpd_state *s, char *ptr))
{

  PSOCK_BEGIN(&s->sout);
  PSOCK_GENERATOR_SEND(&s->sout, generate_prt0_s0, s);
  PSOCK_END(&s->sout);
}

/*---------------------------------------------------------------------------*/
static unsigned short
generate_prt1_s0(void *arg)		//esta función ayuda a la que debe obtener el estado actual del puerto
{
	unsigned int prt1_s0;

	PRT1_PIO->FIOMASK = 0;
	prt1_s0 = !!(PRT1_PIO->FIOPIN & (1 << PRT1_pin));
	return snprintf((char *)uip_appdata, UIP_APPDATA_SIZE,
			"%s ",  (prt1_s0 ? "":"disabled"));
}

static
PT_THREAD(prt1_s0(struct httpd_state *s, char *ptr))
{

  PSOCK_BEGIN(&s->sout);
  PSOCK_GENERATOR_SEND(&s->sout, generate_prt1_s0, s);
  PSOCK_END(&s->sout);
}
/*---------------------------------------------------------------------------*/
static unsigned short
generate_prt2_s0(void *arg)		//esta función ayuda a la que debe obtener el estado actual del puerto
{
	unsigned int prt2_s0;

	PRT2_PIO->FIOMASK = 0;
	prt2_s0 = !!(PRT2_PIO->FIOPIN & (1 << PRT2_pin));
	return snprintf((char *)uip_appdata, UIP_APPDATA_SIZE,
			"%s ",  (prt2_s0 ? "":"disabled"));
}

static
PT_THREAD(prt2_s0(struct httpd_state *s, char *ptr))
{

  PSOCK_BEGIN(&s->sout);
  PSOCK_GENERATOR_SEND(&s->sout, generate_prt2_s0, s);
  PSOCK_END(&s->sout);
}
/*---------------------------------------------------------------------------*/
static unsigned short
generate_prt3_s0(void *arg)		//esta función ayuda a la que debe obtener el estado actual del puerto
{
	unsigned int prt3_s0;

	PRT3_PIO->FIOMASK = 0;
	prt3_s0 = !!(PRT3_PIO->FIOPIN & (1 << PRT3_pin));
	return snprintf((char *)uip_appdata, UIP_APPDATA_SIZE,
			"%s ",  (prt3_s0 ? "":"disabled"));
}

static
PT_THREAD(prt3_s0(struct httpd_state *s, char *ptr))
{

  PSOCK_BEGIN(&s->sout);
  PSOCK_GENERATOR_SEND(&s->sout, generate_prt3_s0, s);
  PSOCK_END(&s->sout);
}
/*---------------------------------------------------------------------------*/
static unsigned short
generate_prt4_s0(void *arg)		//esta función ayuda a la que debe obtener el estado actual del puerto
{
	unsigned int prt4_s0;

	PRT4_PIO->FIOMASK = 0;
	prt4_s0 = !!(PRT4_PIO->FIOPIN & (1 << PRT4_pin));
	return snprintf((char *)uip_appdata, UIP_APPDATA_SIZE,
			"%s ",  (prt4_s0 ? "":"disabled"));
}

static
PT_THREAD(prt4_s0(struct httpd_state *s, char *ptr))
{

  PSOCK_BEGIN(&s->sout);
  PSOCK_GENERATOR_SEND(&s->sout, generate_prt4_s0, s);
  PSOCK_END(&s->sout);
}

/*---------------------------------------------------------------------------*/
extern int pong_enable;

static
PT_THREAD(prt4_pg(struct httpd_state *s, char *ptr))	//togglea una variable superglobal
{
  if (pong_enable==0)		{pong_enable=1;}
  else if (pong_enable==1)	{pong_enable=0;}
 }

/*---------------------------------------------------------------------------*/

//función abandonada
/*
static unsigned short
generate_prt_map(void *arg)		//esta función muestra el mapeo de los puertos
{
	char *P0G,*P1G,*P2G,*P3G,*P4G;
	char *P0P,*P1P,*P2P,*P3P,*P4P;

	P0G=(char*) PRT0_PIO;
	P1G=(char*) PRT1_PIO;
	P2G=(char*) PRT2_PIO;
	P3G=(char*) PRT3_PIO;
	P4G=(char*) PRT4_PIO;

	return snprintf((char *) uip_appdata, UIP_APPDATA_SIZE, " \
%s \
%s %s %s %s %s \
%s %s %s %s %s \
%s %s %s %s %s \
%s %s %s %s %s \
%s %s %s %s %s \
%s",
"<br />",
"Puerto 0: GPIO_",P0G,"_",(char*) PRT0_pin,"<br />",
"Puerto 1: GPIO_",P1G,"_",(char*) PRT1_pin,"<br />",
"Puerto 2: GPIO_",P2G,"_",(char*) PRT2_pin,"<br />",
"Puerto 3: GPIO_",P3G,"_",(char*) PRT3_pin,"<br />",
"Puerto 4: GPIO_",P4G,"_",(char*) PRT4_pin,"<br />",
"");
}

static
PT_THREAD(prt_map(struct httpd_state *s, char *ptr))
{

  PSOCK_BEGIN(&s->sout);
  PSOCK_GENERATOR_SEND(&s->sout, generate_prt_map, s);
  PSOCK_END(&s->sout);
}
*/

/*---------------------------------------------------------------------------*/
/** @} */
