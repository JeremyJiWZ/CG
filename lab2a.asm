data segment
	tips1 db "input num1: ",0ah,0dh,"$"
	tips2 db "input num2: ",0ah,0dh,"$"
	num1 dw 1 dup(?)
	num2 dw 1 dup(?)
	numb1 dw 0
	numb2 dw 0
	tipsOF db "OVERFLOW!!$"
data ends

stack segment
	dw 512 dup(?)
stack ends

code segment
	assume cs:code,ss:stack,ds:data
start:
	mov ax,data
	mov ds,ax

	mov dx,offset tips1
	mov ah,09h
	int 21h ;input string1
	call inputnumber ;bx store the number
	mov num1,bx ;push to data segment

	mov ah,2 ;input a '\n'
	mov dl,0ah
	int 21h
	mov ah,2
	mov dl,0dh
	int 21h

	mov dx,offset tips2
	mov ah,09h
	int 21h ;input string2
	call inputnumber
	mov num2,bx ;push to data segment

	mov ah,2 ;input a '\n'
	mov dl,0ah
	int 21h
	mov ah,2
	mov dl,0dh
	int 21h

	mov ax,num1
	mov bx,num2
	add ax,bx
	jo overfl

	call tostring ;turn the number to a string
	mov bx,numb1
	mov dl,bh
	mov ah,02h
	int 21h

	mov dl,bl
	mov ah,02h
	int 21h

	mov bx,numb2
	mov dl,bh
	mov ah,02h
	int 21h

	mov dl,bl
	mov ah,02h
	int 21h
	jmp exit

overfl:
	lea dx,tipsOF
	mov ah,09h
	int 21h
	jmp exit

exit:
	mov ah,4ch
	int 21h

inputnumber proc
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

tostring proc
	;turn number in ax to ascii in stack
	mov bx,ax
	and bx,0fh
	cmp bl,0ah
	jl NEXT
	jns GNEXT
NEXT:
	add bl,'0'
	jmp proii
GNEXT:
	add bl,'A'
	sub bl,10
	jmp proii
proii:
	mov dx,ax
	and dl,0f0h
	mov cl,4
	shr dl,cl
	cmp dl,0ah
	jl NEXT2
	jns GNEXT2
NEXT2:
	add dl,'0'
	mov bh,dl
	mov numb2,bx
	jmp proiii
GNEXT2:
	add dl,'A'
	sub dl,10
	mov bh,dl
	mov numb2,bx
	jmp proiii
proiii:
	mov bx,ax
	and bx,0f00h
	mov cl,8
	shr bx,cl
	cmp bl,ah
	jl NEXT3
	jns GNEXT3
NEXT3:
	add bl,'0'
	jmp proiiii
GNEXT3:
	add bl,'A'
	sub bl,10
	jmp proiiii
proiiii:
	mov dx,ax
	and dx,0f000h
	mov cl,12
	shr dx,cl
	cmp dl,ah
	jl NEXT4
	jns GNEXT4
NEXT4:
	add dl,'0'
	mov bh,dl
	mov numb1,bx
	ret
GNEXT4:
	add dl,'A'
	sub dl,10
	mov bh,dl
	mov numb1,bx
	ret
tostring endp


code ends
end start