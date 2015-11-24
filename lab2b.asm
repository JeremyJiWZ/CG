;----turn a hex number to a dec number----
data segment 
	deci db 5 dup(?)
	tips db "input the number: ",0ah,0dh,"$"
	m dw ?
data ends

stack segment

stack ends

code segment 
	assume cs:code,ss:stack,ds:data
start:
	mov ax,data
	mov ds,ax

	lea dx,tips
	mov ah,09h
	int 21h

	call inputnumber

	mov ah,02h
	mov dl,0ah
	int 21h
	mov ah,02h
	mov dl,0dh
	int 21h

	mov m,bx

ini:
       mov ax,m
       mov bx,10
       mov si,4
change:
       mov dx,0
       div bx
       mov [deci+si],dl
       dec si
       cmp ax,0
       ja change
output:
       inc si
       mov dl,[deci+si]
       add dl,30h
       mov ah,02h
       int 21h
       cmp si,4
       jb output

       mov dl,20h
       mov ah,02h
       int 21h

exit:
      mov ah,4ch
      int 21h



inputnumber proc 
	;input a 4bits number 
	;store it in bx
input:
	mov ah,1 ;1
	int 21h
	mov cl,al
	call toascii ;turn ascii to a 4bits number
	mov bh,cl
	mov cl,4
	shl bh,cl

	mov ah,1 ;2
	int 21h
	mov cl,al
	call toascii
	or bh,cl

	mov ah,1 ;3
	int 21h
	mov cl,al
	call toascii
	mov bl,cl
	mov cl,4
	shl bl,cl

	mov ah,1 ;4
	int 21h
	mov cl,al
	call toascii
	or bl,cl
	ret
inputnumber endp

toascii proc ;turn ascii to a 4bits number
	;ascii stored in cl, don't change bx
	mov al,cl
	cmp al,':' ;   ':' = '0'+1
	jns greaterthan9
	sub al,'0'
	jmp endtoascii
greaterthan9:
	cmp al,'[' ;'Z'+1
	jns greaterthanZ
	sub al,'A'
	add al,10
	jmp endtoascii
greaterthanZ:
	sub al,'a'
	add al,10
	jmp endtoascii
endtoascii:
	mov cl,al
	ret
toascii endp


code ends
end start
