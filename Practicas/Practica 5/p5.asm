.model tiny
.code

;void pokew(word segment,word offset,word value)
  public _pokeW
	public _putchar
  public _poke

_pokeW PROC
    push ds
    push bp
    push bx
    push ax

    mov bp,sp
    mov ds,[bp + 10] ;segment
    mov bx,[bp + 12] ;offset
    mov ax,[bp + 14] ;value
    mov [bx],ax

    pop ax
    pop bx
    pop bp
    pop ds
    ret
ENDP



 _putchar PROC
		push bp
		push dx
		push ax

		mov bp,sp
		mov dl,[bp + 8]
		mov ah,02
		int 21h

		pop ax
		pop dx
		pop bp
		ret
 ENDP



 ;void poke(unsigned int segment, unsigned int offset, unsigned char data)

           _poke PROC
               push bp   ;saving registers
               push bx
               push ds
               push dx

               xor dx,dx ;dx = 0
               mov bp,sp
               mov ds,[bp + 10]  ;segment
               mov bx,[bp + 12]  ;offset
               mov dl,[bp + 14]  ;data

               mov [bx],dl

               pop dx
               pop ds
               pop bx
               pop bp
           ret
           ENDP



END
