extern get_breg_a
extern get_ax_a
extern get_eax_a
extern divide_by_zero
extern double_fault
extern get_cs_a
extern get_ip_a 
global get_breg
global get_ax
global get_eax
global idt_load
global get_cs
global get_ip
global enable_interrupts
global disable_interrupts
global isr0
global isr8
extern idtp 
get_breg:	
	pushad
	call get_breg_a
	popad 
get_ax:
	push ax
	call get_ax_a
	pop ax 
get_eax:
	push ebx
	call get_eax_a
	pop ebx
idt_load:
	lidt [idtp]
	ret
enable_interrupts:
	sti
	ret 
disable_interrupts	:
	cli
	ret
isr0:
	pushad
	mov eax, divide_by_zero 
	call eax 
	popad
	ret 
isr8:
	pushad
	mov eax, double_fault
	call eax 
	popad
	ret
get_ip:
	mov eax,cs 
	push eax
	call get_ip_a
	pop eax
	ret
get_cs: 			; Arguments need to be passed in reverse order. 
	mov eax, cs 		; Short value  
	push eax
	mov eax, get_cs		; int value. it will always give the value in decimal form. 
	push eax 
	call get_cs_a
	pop eax
	ret


	




