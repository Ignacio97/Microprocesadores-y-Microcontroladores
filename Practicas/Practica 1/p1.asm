
.model tiny

;----- Insert INCLUDE "filename" directives here
;----- Insert EQU and = equates here

locals

.data

.code
          org 100h

;*************************************************************
;  Procedimiento principal
;*************************************************************
principal PROC
         mov sp,0fffh			; inicializa SP (Stack Pointer)

again:   numero = 100
         mov ax,numero
         call n_numero_feo

         base = 10
         mov bx,base
         call printNumBase
         jmp again

   ret						; nunca se llega aqu�
   ENDP



   ;recibe en al el numero
   ;devuelve en ax el n numero feo
   n_numero_feo PROC
       push cx


       mov cl,1   ;cl = 1  ;cont
       mov ch,al  ;ch = al
       mov ax,1

     WH: cmp ch,cl
         jbe finWH
         inc ax

         push ax
         call esfeo
         cmp ah,1
         jne nofeo
         inc cl
   nofeo:pop ax
         jmp WH
   finWH:
       pop cx
     ret
   ENDP


   ;recibe en ax dividendo, en bx divisor
   ;reduelve en cx el residuo
   residuo PROC
   push ax
   push dx
   push bx

       xor dx,dx
       div bx
       mov cx,dx

   pop bx
   pop dx
   pop ax
       ret
   ENDP

   ;recide en ax numero a checar
   ;devuelve en ah 1 si es feo, caso contrario 0
   esfeo PROC
     push cx
     push dx
     push bx

     xor cx,cx
     divisor = 2
     mov bx,divisor

     doo1: call residuo
           cmp cx,0
           jne findoo1
           xor dx,dx
           div bx
           jmp doo1
   findoo1:

           divisor = 3
           mov bx,divisor

     doo2: call residuo
           cmp cx,0
           jne findoo2
           xor dx,dx
           div bx
           jmp doo2
   findoo2:

           divisor = 5
           mov bx,divisor

     doo3:  call residuo
           cmp cx,0
           jne findoo3
           xor dx,dx
           div bx
           jmp doo3
   findoo3:

               cmp ax,1
               jne noEsUno
               mov ah,al
               jmp final
     noEsUno:  mov ah,0
     final:

     pop bx
     pop dx
     pop cx
     ret
   ENDP



   ;recibe en ax numero a imprimir y bx la base solicitada.
   printNumBase PROC
           push ax ;salvar registros
           push cx
           push dx

           xor dx,dx ;dx=0
           contador = 0
           mov cx,contador

     doo:
           div bx      ;ax=ax/bx
           add dx,30h  ;dx=ax%bx + 30h
           cmp dx,39h  ;residuo mayor a 9?
           jbe l1      ;no then push
           add dx,7h   ;si, then add 7
     l1:   push dx
           inc cx
           xor dx,dx ;dx=0
           cmp ax,0  ;cociente != 0 ?
           jne doo

           mov ah,2
   print:  pop dx
           int 21h
           loop print

           pop dx  ;recuperar registros
           pop cx
           pop ax


           ret
       ENDP



END; End of program
