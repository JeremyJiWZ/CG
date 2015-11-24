data segment
	helloworld db "Hello World!!$"
	len equ $-helloworld
        ;input data segment code here
data ends

extend segment
	hhh db len dup(?)
extend ends

stack segment
	dw 20 dup(?)
stack ends

code segment
    assume cs:code,ds:data, es:extend
start:
    mov ax,data
    mov ds,ax
        ;data segment
    mov ax,extend
    mov es,ax
	  ;extend segment
    mov si,offset helloworld
    mov di,offset hhh
    mov cx,len
loop1:
    mov al,ds:[si]
    mov es:[di],al
    inc si
    inc di
    dec cx
    jnz loop1
    push es
    pop ds
    mov dx,offset hhh
    mov ah,09h
    int 21h
    mov ah,4ch
    int 21h
code ends
end start