Facultad:	FIUBA
Materia:	Seminario de SISTEMAS EMBEBIDOS - 2C 2012
Proyecto:	CAPEAR (Cortacorriente Automatico Para Equipamiento Autonomo de Red)


Estado actual del proyecto (26/02/2013):

Se puede: invertir el estado, asegurar encendido y asegurar apagado de dos puertos:
- GPIO 0.22 (el LED2 de la plaquita LPCXpresso)
- GPIO 0.09 (PIO0.9 en el baseboard, apagado es V=0.5 y encendido es V=3.3 medidos con voltimetro)
...mediante la pulsación de botones a tal fin en una página web alojada dentro del LPC1769

Fallos:
Lo conseguido para los puertos anteriores no puede obtenerse con los puertos GPIO 0.5/7/11 pese
a que se configuraron de manera análoga al GPIO 0.9.
*Posibles causas*: mal seteo de jumpers en el baseboard? 


Instrucciones para probar:

0. Establecer una dirección IP en el código (main.c) que pertenezca a la sub-red local; por defecto: 192.168.0.200 [/24]
1. Compilar el proyecto
2. Transferir el binario a LPCXpresso
3. Conectar el puerto Ethernet del baseboard a la red local
4. Desde un browser, acceder a la página http://192.168.0.200 (o la que corresponda si se cambió)
5. Hacer clic en cualquiera de los botones de la página web y observar LED2 o medir el puerto con voltímetro.
