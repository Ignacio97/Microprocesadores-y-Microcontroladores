
.model tiny
.code

  public _peek
  public _poke

;unsigned char peek(unsigned int segment, unsigned int offset)
        _peek PROC
          push bp  ;saving registers
          push ds
          push bx

          xor ax,ax       ;ax = 0
          mov bp,sp
          mov ds,[bp + 8]  ;moving the given segment to ds
          mov bx,[bp + 10]  ;||     ||   ||   ||     ||  offset
          mov al,[bx]     ;byte stored in ds*10h+offset has been moved to al

          pop bx
          pop ds
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
