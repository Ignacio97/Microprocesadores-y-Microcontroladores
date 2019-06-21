.include "m2560def.inc" 


	sbi DDRB,DDB7 ;pb7 as out
	cbi PORTB,PB7 ;pb7 to low

	main : 
		call delay3
		sbi PINB,PB7 ;toggle led
		nop ;for debug
	rjmp main




	;delay que dure 123us
	delay1:
		ldi r16,178

	wh:	push r16 
		push r16
		pop  r16
		pop  r16
		dec r16
		brne wh
	ret  
	
	;delay que dure 45ms 
	delay2:
		ldi r16,10

		L1:	ldi r17,80
		L2: ldi r18,180	
		L3: nop
			nop
			dec r18
			brne L3
			
			dec r17
			brne L2

			dec r16
			brne L1
		ret


	;delay que tarde 678ms
	delay3:
		ldi r16,113
		
		A1:ldi r17,120
		A2:ldi r18,200
		A3:	nop
			dec r18
			brne A3 
			
			dec r17
			brne A2

			dec r16
			brne A1
	ret
