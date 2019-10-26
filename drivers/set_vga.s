;设置vga模式
[GLOBAL setvga]
setvga:
sti
mov al,00h         
mov ah,13h            
int 10h               
ret
