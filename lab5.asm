data segment
	tips db "enter 'q' to quit the program",0ah,0dh,"$"
data ends


code segment 
	assume cs:code,ds:data
start:
	mov ax,data
	mov ds,ax	;initialization

	mov ah,09h
	lea dx,tips
	int 21h		;print tips

	mov dx,0de03h	;控制端口号
	mov al,80h		;设置控制字，B端口输出
	out dx,al		;输出

rotate:
;电机不停旋转，直到输入'q'
	mov dx,0de01h
	mov al,04h	;4
	out dx,al	;输出
	mov cx,100
	rep nop 	;简单的延时

	mov dx,0de01h
	mov al,08h	;8
	out dx,al	;输出
	mov cx,100
	rep nop 	;简单的延时

	mov dx,0de01h
	mov al,01h	;1
	out dx,al	;输出
	mov cx,100
	rep nop 	;简单的延时

	mov dx,0de01h
	mov al,02h	;2
	out dx,al	;输出
	mov cx,100
	rep nop 	;简单的延时

	mov ah,01h 	;检查键盘输入
	int 21h		;调用DOS中断
	mov bl,'q'
	cmp al,bl	;与'q'比较
	jz exit		;若q按下则为结束
	jmp rotate

exit:
	mov ah,4ch
	int 21h	
code ends
end start