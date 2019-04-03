
.model tiny
.code

	public _putchar
	public _getchar
	public _getch

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
 _putchar ENDP

 _getchar PROC
		mov ah,01h
		int 21h
		xor ah,ah ;ax = al
		ret
 _getchar ENDP

 _getch PROC
		mov ah,08
		int 21h
		xor ah,ah
		ret
 _getch ENDP

END
