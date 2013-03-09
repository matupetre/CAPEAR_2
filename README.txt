Facultad:	FIUBA
Materia:	Seminario de SISTEMAS EMBEBIDOS - 2C 2012
Proyecto:	CAPEAR (Cortacorriente Automatico Para Equipamiento Autonomo de Red)


Estado actual del proyecto (08/03/2013):

NEW: Se puede PINGuear un host en forma sostenida y escuchar las respuestas; en caso que se acumulen 3 peticiones
sin respuesta, el puerto correspondiente al host (actualmente PUERTO 4) se apaga durante unos instantes y luego
se lo vuelve a encender. NOTA: "Unos instantes" son milesimas de segundo, ya que por el momento no se consigue
introducir un delay, probablemente el pre-compilador lo anula en un intento por optimizar el c�digo.


Se puede: invertir el estado, asegurar encendido y asegurar apagado de 5 puertos:

- PUERTO 0: GPIO 0.22 (el LED2 de la plaquita LPCXpresso)
- PUERTO 1: GPIO 0.09 (PIO0.9 en el baseboard, apagado es V=0.5 y encendido es V=3.3 medidos con voltimetro)
- PUERTO 2: GPIO 2.03 (PIO2.3 en el baseboard, apagado es V=0.1 y encendido es V=3.1 medidos con voltimetro)
- PUERTO 3: GPIO 2.05 (PIO2.5 en el baseboard, apagado es V=0.1 y encendido es V=3.1 medidos con voltimetro)
- PUERTO 4: GPIO 2.07 (PIO2.7 en el baseboard, apagado es V=0.1 y encendido es V=3.1 medidos con voltimetro)

...mediante la pulsaci�n de botones a tal fin en una p�gina web alojada dentro del LPC1769


Instrucciones para probar:
==========================
0. Establecer una direcci�n IP en el c�digo (main.c) que pertenezca a la sub-red local; por defecto: 192.168.0.200 [/24]
1. Compilar el proyecto
2. Transferir el binario a LPCXpresso
3. Conectar el puerto Ethernet del baseboard a la red local
4. Desde un browser, acceder a la p�gina http://192.168.0.200 (o la que corresponda si se cambi�)
5. Hacer clic en cualquiera de los botones de la p�gina web y observar LED2 o medir el puerto afectado con volt�metro


----------------------------------------------------------------------------------
Queda pendiente:

1.
Los conseguido para los puertos anteriores no puede obtenerse con cualquier puerto GPIO arbitrario,
tan solo con algunos (c�digo ceteris-paribus). Se escogieron 4 puertos "adecuados" mediante prueba/error.

*Posibles causas*: 
-�mal seteo de jumpers en el baseboard? --> Descartado, se prob� y no se hall� soluci�n por esta v�a.

2.
Habilitar el PING saliente para todos los puertos (actualmente s�lo puerto 4)

3.
Recibir argumentos complejos desde la p�gina web y ejecutar funciones que los tomen como tales.



