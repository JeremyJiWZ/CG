data segment
tips1 db "press a key from keyboard(0~256), and show its ascii value by the light!",0ah,0dh,"$"
tips2 db "press q to exit!",0ah,0dh,"$"
tips3 db "end!$"

data ends

code segment
assume ds:data,cs:code
start:
        mov ax,data
        mov ds,ax

        mov dx,offset tips1
        mov ah,09h
        int 21h

	mov dx,offset tips2
        mov ah,09h
        int 21h

DOTHIS:
	mov ah,01h
	int 21h
	cmp al,'q'
	jz exit

        mov dx,0DE00H
        add dx,60h
        out dx,al
        jmp DOTHIS

exit:
	mov dx,offset tips3
        mov ah,09h
        int 21h

        mov ah,4ch
        int 21h
        



code ends
end start

 
