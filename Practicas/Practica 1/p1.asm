
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

@@sigue:
         mov  al,'x'
   call putchar
   jmp @@sigue

   ret						; nunca se llega aqu�
   ENDP


;***************************************************************
;  procedimientos
;***************************************************************
 putchar	proc
   push ax
   push dx
   mov dl,al
   mov ah,2				; imprimir caracter DL
   int 21h					; usando servico 2 (ah=2)
   pop dx					; del int 21h
   pop ax
   ret
   endp

end   principal              ; End of program




;recibe en CH dividendo, en CL divisor
;reduelve en CH residuo
residuo PROC
    push ax

    xor ax,ax
    mov al,ch
    div cl
    mov ch,ah

    pop ax
ENDP

;recide en al numero a checar
;devuelve en ah 1 si es feo, caso contrario 0
es_feo PROC
  push cx

  xor cx,cx
  divisor = 2

  mov ch,al
  mov cl,divisor

  doo1: call residuo
        cmp ch,0
        jne findoo1
        xor ah,ah
        div cl
        mov ch,al
        jmp doo1
findoo1:

        divisor = 3
        mov cl,divisor
        mov ch,al

  doo2: call residuo
        cmp ch,0
        jne findoo2
        mov ch,divisor
        xor ah,ah
        div ch
        mov ch,al
        jmp doo1
findoo2:

        divisor = 5
        mov cl,divisor
        mov ch,al

  doo3:  call residuo
        cmp ch,0
        jne findoo3
        mov ch,divisor
        xor ah,ah
        div ch
        mov ch,al
        jmp doo1
findoo3:

            cmp al,1
            jne noEsUno
            mov ah,al
  noEsUno:  mov ah,0

  pop cx
ENDP
