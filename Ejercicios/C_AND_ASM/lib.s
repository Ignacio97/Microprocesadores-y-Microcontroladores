

	.global inc_2

	inc_2:
		ldi r18,2 ;r18 can be freely used 
		add r22,r18
		brcc fin
		clr r18 
		adc r23,r18
		adc r24,r18
		adc r25,r18
	fin :ret
