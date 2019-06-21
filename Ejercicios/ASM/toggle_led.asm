.include "m2560def.inc" 

;hacer prender un led cada 1/2 segundo
;usare el led integrado en la placa, el cual corresponde a PB7
.set ticks = 7811

	cli	

	
	ldi r16,(1<<DDB7)
	out DDRB,r16   ;pin pb7 as out 
	ldi r16,~(1<<PB7)
	out PORTB,r16    ;starts in low
	
	ldi r16,(1<<COM1C0) ;toogle on compare
	sts TCCR1A,r16

	clr r16
	sts TCNT1H,r16
	sts TCNT1L,r16
	
	ldi r16,high(ticks) ;para escribir siemre poner parte alta primero, para leer siempre parte baja primero
	sts OCR1AH,r16
	ldi r16,low(ticks)
	sts OCR1AL,r16

	ldi r16, (1<<WGM12)|(5<<CS10) ;ctc, prescaler to 1024
	sts TCCR1B,r16


	forever : 	nop
				
				rjmp forever


