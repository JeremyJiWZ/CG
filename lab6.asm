data segment
	keyTable db 0eeh,0edh,0ebh,0e7h,
			0deh,0ddh,0dbh,0d7h,
			0beh,0bdh,0bbh,0b7h,
			07eh,07dh,07bh,077h
data ends

code segment
	assume cs:code,ds:data
start:
	mov ax,data
	mov ds,ax

;设置控制字
	mov dx,0de03h
	mov al,10001000b;方式0，行（C低位）输出，列（C高位）输入
	out dx,al
scankey:	;扫面键盘码，并存在AL中
	;设置第0行
	mov dx,0de02h
	mov al,0eh
	out dx,al
	;输入列数据
	mov dx,0de02h
	in al,dx
	;处理AL，恢复低4位数值
	and al,0f0h 	;先把低位清空
	or al,0eh 		;再把低位置为该行值
	;处理bl,若有输入bl!=0f0h
	mov bl,0f0h
	and bl,al
	cmp bl,0f0h
	jnz display

	;设置第1行
	mov dx,0de02h
	mov al,0dh
	out dx,al
	;输入列数据
	mov dx,0de02h
	in al,dx
	;处理AL，恢复低4位数值
	and al,0f0h	 	;先把低位清空
	or al,0dh 		;再把低位置为该行值
	;处理bl,若有输入bl!=0f0h
	mov bl,0f0h
	and bl,al
	cmp bl,0f0h
	jnz display

	;设置第2行
	mov dx,0de02h
	mov al,0bh
	out dx,al
	;输入列数据
	mov dx,0de02h
	in al,dx
	;处理AL，恢复低4位数值
	and al,0f0h 	;先把低位清空
	or al,0bh 		;再把低位置为该行值
	;处理bl,若有输入bl!=0f0h
	mov bl,0f0h
	and bl,al
	cmp bl,0f0h
	jnz display

	;设置第3行
	mov dx,0de02h
	mov al,07h
	out dx,al
	;输入列数据
	mov dx,0de02h
	in al,dx
	;处理AL，恢复低4位数值
	and al,0f0h 	;先把低位清空
	or al,07h 		;再把低位置为该行值
	;处理bl,若有输入bl!=0f0h
	mov bl,0f0h
	and bl,al
	cmp bl,0f0h
	jnz display
	;若没有键按下，则重新扫描
	jmp scankey
display:
;根据AL的值，显示对应的ASCII码在屏幕上
	mov si,offset keyTable
runloop: 		;在data段中查找与AL相符的值，显示此时计数器值
	cmp al,77h  ;ff对应F键，设为退出键
	jz exit
	mov ah,[si] 
	cmp ah,al
	jz show
	inc si
	jmp runloop
show: 			;将数值转成ASCII码，并输出在屏幕上
	cmp si,10
	jl show1234
	jge showabcd
show1234: 		;显示0~9
	add si,'0'
	mov dx,si
	mov ah,02h
	int 21h
	jmp display
showabcd: 		;显示ABCDEF
	add si,'A'-10
	mov dx,si
	mov ah,02h
	int 21h
	jmp display
;延时，双重嵌套
delay:
	mov bx,1fffh ;第一重
delay1:
	dec bx
	cmp bx,0
	jz scankey
	mov cx,0ffffh
getdelay: 	;第二重循环
	dec cx
	cmp cx,0
	jnz getdelay
	jmp delay1
exit:
	mov ah,4ch
	int 21h 
code ends
end start