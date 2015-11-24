data segment
  tips db "press q to exit$"
data ends

code segment
        assume cs:code,ds:data

start:
        mov ax,data
        mov ds,ax

        mov ah,09h
        mov dx,offset tips
        int 21h

        mov dx,0de23h ;caculator 0
        mov al,16h
        out dx,al

        mov dx,0de20h
        mov al,0fh
        out dx,al

        mov dx,0de23h
        mov al,56h    ;calculator 1
        out dx,al

        mov dx,0de21h
        mov al,0ffh
        out dx,al

        mov dx,0de23h
        mov al,96h    ;calculator 2
        out dx,al

        mov dx,0de22h
        mov al,123
        out dx,al

;to display the number in the screen
display:
        mov dx,0de20h
        in al,dx
        call tostring

        mov dl,bh
        mov ah,02h
        int 21h         ;show the number

        mov dl,bl
        mov ah,02h
        int 21h         ;show the next number

        mov ah,01h
        int 21h         ;exit or not?
        cmp al,'q'
        jz exit

        jmp display

exit:
        mov ah,4ch
        int 21h

tostring proc
        ;turn the number in al to ascii in bx
        mov bl,al
        and bl,0fh
        cmp bl,0ah
        jl next
        jns gnext
next:
        add bl,'0'
        jmp proii
gnext:
        add bl,'A'
        sub bl,10
        jmp proii
proii:
        mov dl,al
        and dl,0f0h
        mov cl,4
        shr dl,cl
        cmp dl,0ah
        jl next2
        jns gnext2

next2:
        add dl,'0'
        mov bh,dl
        ret
gnext2:
        add dl,'A'
        sub dl,10
        mov bh,dl
        ret
tostring endp

code ends
end start





