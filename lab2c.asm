data segment
	INPUT db "INTPUT STRING IN THE WINDOW!$"
data ends

code segment
	assume ds:data,cs:code
start:
	mov ax,data
	mov ds,ax

	mov ah,06h ;initialize the screen
	mov al,0
	mov bh,01110000b
	mov ch,4
	mov cl,9
	mov dh,19
	mov dl,69
	int 10h

	mov ah,02h
	mov bh,00h
	mov dh,12
	mov dl,26
	int 10h

	mov ah,09h
	mov dx,offset INPUT
	int 21h

	mov ah,01h
	int 21h

	mov ah,4ch
	int 21h


code ends
end start