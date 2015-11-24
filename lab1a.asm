data segment
    helloworld db "INPUT STRING, THE END FLAG IS '#'",0ah,0dh,"$"
        ;input data segment code here
data ends

stack segment

        ;input stack segment code here
stack ends

code segment
    assume cs:code,ds:data,ss:stack
start:
    mov ax,data
    mov ds,ax
        ;input code segment code here
    mov dx, offset helloworld
    mov ah,09h
    int 21h
loop1:    
    mov ah,07h
    int 21h ;?????al
    cmp al,23h ;'#'is the end flag
    je exit
    ;display
    cmp al,61h
    js display
    cmp al,7bh
    jns display
    sub al,20h
display:;display char
    mov dl,al
    mov ah,02h
    int 21h
    jmp loop1 ;loop
    
exit:    
    mov ah,4ch
    int 21h
code ends
end start
