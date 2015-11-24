data segment
tips db "hello world$"
data ends

code segment
assume ds:data,cs:code
start:
        mov ax,data
        mov ds,ax

        mov dx,offset tips
        mov ah,09h
        int 21h

        mov cx,1
DOTHIS:
        mov dx,0D000H
        add dx,60h
        in al,dx

        out dx,al
        jmp DOTHIS

        mov ah,4ch
        int 21h

code ends
end start

 
