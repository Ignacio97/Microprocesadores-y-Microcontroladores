.include "m2560def.inc"

;traducir la sig expresion del lenguaje C al ensamblador de AVR 1280/2560
; num &= (1<<n_bit)
;num es apuntada por X y n_bit por Z



;-----------------datos para testear---------------
ldi r16,$ff
sts $200,r16 ;valor para num

ldi r16,$7
sts $202,r16 ;valor para n_bit

ldi XL,$0
ldi XH,$02

ldi ZL,$02
ldi ZH,$02

;--------------comienza programa

ld r0,X ;num
ld r1,Z ;n_bit

ldi r16,$1		
clr r2

	doo: cp r2,r1  ;realizando corrimiento
		 breq endo
		 lsl r16
		 inc r2
		 rjmp doo
	endo:	
	
	and r0,r16
	st Z,r0  ;savin' value	
	nop


