.model tiny
.code


  public _inportb
  public _outportb

 _inportb PROC
        push bp
        push dx

        xor ah,ah
        mov bp,sp

        mov dx,[bp + 6] ;port address
        in al,dx

        pop dx
        pop bp

  ret
  ENDP



  _outportb PROC
        push bp
        push dx
        push ax

        mov bp,sp
        mov dx,[bp + 8]
        mov al,[bp + 10]
        out dx,al

        pop ax
        pop dx
        pop bp

   ret
   ENDP
END

;martinez.alondra
