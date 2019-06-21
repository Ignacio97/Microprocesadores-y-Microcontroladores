.include "m2560def.inc"


;hacer un procedimiento que consuma 2590 ciclos,tome en cuenta que manejamos 
;un atmega 2560 a 16mhz



	call delay ; 5 clock * 1
	nop ;debuggin'


	delay:                        ;2590 - (5 + 5) = 2580
			ldi r16,215 ; 1 clk
			
		L0:	push r16 ;2 clks
			push r16   
			pop r16
			pop r16  ;2 clks
			dec r16
			nop
			brne L0	
			ret ;5 clocks * 1
			
			; 10 (call and ret) + 1(ldi) + (215*12)-1 = 2590 
