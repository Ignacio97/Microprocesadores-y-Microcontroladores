.INCLUDE "m2560def.inc"


;sumar dos numeros apuntados por X y Y y guardar el resultado el la dir 
;apuntada por Z 


;----------------datos para testear-----------
ldi r16,8 
sts $0200,r16  ;valor para x

ldi r16,2
sts $0201,r16 ;valor para y

ldi XL,$0
ldi XH,$02 ;x apunta a $200

ldi YL,$01
ldi YH,$02 ;y apunta a $201

ldi ZL,$03
ldi ZH,$02 ;z apunta a $203

;---------comienza programa

ld r0,X  
ld r1,Y 
add r0,r1
st Z,r0
nop
