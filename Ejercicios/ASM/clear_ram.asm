.INCLUDE "m2560def.inc"

;Ejemplo de codigo para limpiar toda la memoria ram interna del ATMEGA 2560
;RAM interna inicia en 0x200 y termina en 0x21FF. 


;1- Inicializar la pila
;2- Hacer push de un registro en 0
;3- mientras sp>= $200 hacer paso dos
;4- Inicializar SP nuevamente


.EQU RAMSTART = $0200 ;inicio
.EQU FIN = $21ff-$205 ;para debug 

ldi r16, LOW(RAMEND)
ldi r17, HIGH(RAMEND)
out SPL, r16
out SPH, r17 ;inicializando sp


ldi r16,LOW(RAMSTART) ;cargando Ram dir de inicio
ldi r17,HIGH(RAMSTART)


clr r18 ;r18 = 0

again:  push r18
		in r20,SPL ;leyendo nuevo valor de sp	
		in r21,SPH

		cp r20,r16  ;comparando sp con RAMSTART
		cpc r21,r17

		brsh again

ldi r16, LOW(RAMEND)
ldi r17, HIGH(RAMEND)
out SPL, r16
out SPH, r17 ;inicializando sp nuevamente


;en promedio tarda 4 ms en limpiar toda la ram
; 8kB ram = 8192 locaciones
; clk_freq = 16MHZ; 1  clock machine = 62.5ns
;[(8*8192)-1]*62.5ns = 4.095ms
