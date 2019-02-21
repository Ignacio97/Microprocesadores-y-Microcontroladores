
.model tiny
.code

	public _my_putchar
	public _my_getchar
	public _my_getch

 _my_putchar PROC
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
 _my_putchar ENDP

 _my_getchar PROC
		mov ah,01h
		int 21h
		xor ah,ah ;ax = al
		ret
 _my_getchar ENDP

 _my_getch PROC
		mov ah,08
		int 21h
		xor ah,ah
		ret
 _my_getch ENDP

END
