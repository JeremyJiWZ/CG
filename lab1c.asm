data segment
	INPUT1 DB "INPUT STRING1: ",0ah,0dh,"$"
	INPUT2 DB "INPUT STRING2: ",0ah,0dh,"$"
	OUTPUT1 DB "MATCH: $"
	OUTPUT2 DB "NO MATCH$"
	STRING1 DB 32,0
	STR1 DB 32 DUP(0)
	STRING2 DB 32,0
	STR2 DB 32 DUP(0)

data ends

stack segment

stack ends
extend segment
extend ends

code segment
	assume cs:code, ss:stack, ds:data, es:extend
start:
	mov ax,data
	mov ds,ax
	mov es,ax

	mov dx,offset INPUT1
	mov ah,09h
	int 21h

	mov ah,0ah
	lea dx,STRING1
	int 21h

	mov ah,02h
	mov dl,0ah
	int 21h
	mov ah,02h
	mov dl,0dh
	int 21h

	mov dx,offset INPUT2
	mov ah,09h
	int 21h

	mov ah,0ah
	lea dx,STRING2
	int 21h

	mov ah,02h
	mov dl,0ah
	int 21h
	mov ah,02h
	mov dl,0dh
	int 21h

	lea si,STR1
	lea di,STR2
	cld
	mov cx,32
	repz cmpsb
	jz match
notmatch:
	lea dx,OUTPUT2
	mov ah,09h
	int 21h
	jmp exit
match:
	lea dx,OUTPUT1
	mov ah,09h
	int 21h
	lea dx,STRING1
	add dx,1
	mov bx,dx
	mov bx,ds:[bx]
	and bx,00ffh
	add bx,dx
	mov dl,ds:[bx]
	mov ah,02h
	int 21h
exit:
	mov ah,4ch
	int 21h
code ends
end start





