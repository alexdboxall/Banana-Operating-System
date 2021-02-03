[bits 32]

global switchToThreadASM
currentTaskTCB equ 0xC2002000		;JUST FOR NOW, NEEDS CHANGING IS prcssthr.hpp AS WELL IF CHANGED
extern taskStartupFunction
extern taskReturned
extern changeTSS
global switchToThreadASMFirstTime
global goToUsermode
extern mapVASFirstTime

global doTPAUSE

doTPAUSE:
	sti
	xor eax, eax
	xor edx, edx
	tpause eax
	ret

global is486
global hasLegacyFPU

hasLegacyFPU:
	MOV EDX, CR0                            ; Start probe, get CR0
	AND EDX, ~0xC	       ; clear TS and EM to force fpu access
	MOV CR0, EDX                            ; store control word
	FNINIT                                  ; load defaults to FPU
	FNSTSW [testword]                      ; store status word
    xor eax, eax
	CMP word [testword], 0                 ; compare the written status with the expected FPU state
	JNE .nofpu                              ; jump if the FPU hasn't written anything (i.e. it's not there)
.hasfpu:
    inc eax
 .nofpu:
	ret

testword: DW 0x55AA                    ; store garbage to be able to detect a change


is486:
	wbinvd
	xor eax, eax
    inc eax
	ret
	times 90 db 0x90
	xor eax, eax
	ret

global goToVM86

goToVM86:
	cli
	push ebp
	mov ebp, esp

	mov eax, [ebp + 8]
	mov ebx, [ebp + 12]
	mov ecx, [ebp + 16]
	mov edx, [ebp + 20]

	and eax, 0xFFFF
	and ebx, 0xFFFF
	and ecx, 0xFFFF
	and edx, 0xFFFF
	
	push edx
	push ecx
	push 0x20202
	push ebx
	push eax
	iretd


goToUsermode:
	cli
	push ebp
	mov ebp, esp

	mov ebx, [ebp + 8]
	mov ax, 0x23
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	
	mov eax, esp			;user mode uses the same stack (this is only called on the first 0->3 switch, in all the others IRET takes care of moving the kernel stack to the user stack)
	push 0x23
	push eax
	push 0x202
	push 0x1B
	push ebx
	iretd


switchToThreadASMFirstTime:
	pushf
	cli

	push eax
	push ebx
	push ecx
	push edx
	push esi
	push edi
	push ebp

	jmp commonThreadSwitch

switchToThreadASM:
	;Save previous task's state

	pushf
	;cli

	push eax
	push ebx
	push ecx
	push edx
	push esi
	push edi
	push ebp

	mov edi, [currentTaskTCB]				;get the address of the TCB
	mov [edi+0x4], esp				;save ESP to the TCB at offset 0x4
	
commonThreadSwitch:
	;load the next task's state
	mov esi, [esp+(8+1)*4]			;esi = address of the next task's "thread control block" (parameter passed on stack)
									;8 = we pushed 8 registers to the stack earlier, 1 = the next parameter is the address

	mov [currentTaskTCB], esi				;update the pointer to point to the new task

	mov eax, [esi + 0x0]			;CR3 stored at offset 0x0 into the struct
	mov ebx, [esi + 0x8]			;address of top of kernel stack
	mov edx, [esi + 0xC]			;load first time EIP / a zero

	mov ecx, cr3					;the task we just switched from's register
	cmp eax, ecx					;does the virtual address space need to be changed?
	je .doneVAS						;to save time, skip reloading if not needed
	mov cr3, eax					;change it if needed
.doneVAS:

	test edx, edx
	je .notFirstTime

		cli

		;REMEMBER:	NOTHING IS ACTUALLY MAPPED IN YET!!!
		;			THIS IS WHAT WE DO HERE
		;
		;			WE NEED A STACK (THE OLD ONE)
		;			IN ORDER TO DO THIS, OTHERWISE 'call'
		;			WILL TRIPLE FAULT (CANNOT PUSH DUE TO PAGE FAULT, CANNOT PUSH INTERRUPT CODE DUE TO PAGE FAULT, BOOM!)

		mov eax, [esi + 0x4]	;ESP stored at offset 0x4 into the struct
		mov esp, 0xC207FE00

		pusha
		call mapVASFirstTime
		popa

		mov esp, eax			

		;first time, so we can trash registers to make it work

		push esi
		push edx
		call changeTSS
		pop edx
		pop esi

		;don't keep EIP stored, so it won't be the first time next time
		mov [esi + 0xC], dword 0

		cmp edx, 1
		je .cameOffAFork

		pop ebp
		pop edi
		pop esi
		pop ecx			;don't pop edx
		pop ecx
		pop ebx
		pop eax
		popf

		;and we're off!
		push edx					;start point
		call taskStartupFunction	;jumps to start point when it returns
		pop edx						;EDX contains the start point
		push eax					;EAX was the return value of the previous thing, and the argument of the next function
		call edx					;go to the start point
		call taskReturned			;in case anything returns

		jmp $

.notFirstTime:
	mov esp, [esi + 0x4]			;ESP stored at offset 0x4 into the struct

	push esi
	push edx
	call changeTSS
	pop edx
	pop esi

	pop ebp
	pop edi
	pop esi
	pop edx
	pop ecx
	pop ebx
	pop eax
	popf

	ret

.cameOffAFork:
	;heavy wizardry
	xor eax, eax
	xor edx, edx
	mov esp, [esi + 0x1C]

	jmp offAForkJumpThingy








global detectCPUID

detectCPUID:
	pushfd
	pushfd
	xor dword [esp], 0x00200000
	popfd
	pushfd
	pop eax
	xor eax, [esp]
	popfd
	and eax, 0x00200000
	ret

global asmAcquireLock
global asmReleaseLock
global asmQuickAcquireLock
global asmQuickReleaseLock

asmQuickAcquireLock:
	push ebp
	mov ebp, esp

	mov ebx, [ebp + 8]  ; argument

.retry:
    lock bts dword [ebx], 0        ;Attempt to acquire the lock (in case lock is uncontended)
    jc .spin_with_pause
	cli
    ret
 
.spin_with_pause:
    pause						; Tell CPU we're spinning
    cmp dword [ebx], 0			; Is the lock free?
    jne .spin_with_pause		; no, wait
    jmp .retry					; retry
 

asmQuickReleaseLock:
	push ebp
	mov ebp, esp
	
	mov [ebp + 8], dword 0  ; argument

	pop ebp
    ret


asmAcquireLock:
	push ebp
	mov ebp, esp

	mov ebx, [ebp + 8]  ; argument

.retry:
    lock bts dword [ebx], 0        ;Attempt to acquire the lock (in case lock is uncontended)
    jc .spin_with_pause

	pushf
	pop eax		;get the flags ready in eax for the return value
	cli			;disable interrupts
	pop ebp
    ret
 
.spin_with_pause:
    pause						; Tell CPU we're spinning
    cmp dword [ebx], 0			; Is the lock free?
    jne .spin_with_pause		; no, wait
    jmp .retry					; retry
 

asmReleaseLock:
	push ebp
	mov ebp, esp
	
	mov ebx, [ebp + 8]  ; argument
	mov edx, [ebp + 12]  ; argument 2 (old eflags)
    mov dword [ebx], 0

	push edx
	popf

	pop ebp
    ret


global loadGDT
extern gdtDescr
loadGDT:
    lgdt [gdtDescr]
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp flush2
flush2:
    ret

global isr0
global isr1
global isr2
global isr3
global isr4
global isr5
global isr6
global isr7
global isr8
global isr9
global isr10
global isr11
global isr12
global isr13
global isr14
global isr15
global isr16
global isr17
global isr18
global isr96
global irq0
global irq1
global irq2
global irq3
global irq4
global irq5
global irq6
global irq7
global irq8
global irq9
global irq10
global irq11
global irq12
global irq13
global irq14
global irq15
global irq16
global irq17
global irq18
global irq19
global irq20
global irq21
global irq22
global irq23

isr0:
    cli
    push 0
    push 0
    jmp int_common_stub

isr1:
    cli
    push 0
    push 1
    jmp int_common_stub

isr2:
    cli
    push 0
    push 2

    jmp int_common_stub

isr3:
    cli
    push 0
    push 3
    jmp int_common_stub

isr4:
    cli
    push 0
    push 4
    jmp int_common_stub

isr5:
    cli
    push 0
    push 5
    jmp int_common_stub

isr6:
	cli
    push 0
    push 6
    jmp int_common_stub

isr7:
    cli
    push 0
    push 7
    jmp int_common_stub

isr8:
    cli
    push 8
    jmp int_common_stub

isr9:
    cli
    push 0
    push 9
    jmp int_common_stub

isr10:
	cli
    push 10
    jmp int_common_stub

isr11:
    cli
    push 11
    jmp int_common_stub

isr12:
    cli
    push 12
    jmp int_common_stub

isr13:
    cli
    push 13
    jmp int_common_stub

isr14:
    cli
    push 14
    jmp int_common_stub

isr15:
    cli
    push 0
    push 15
    jmp int_common_stub

isr16:
    cli
    push 0
    push 16
    jmp int_common_stub

isr17:
    cli
    push 0
    push 17
    jmp int_common_stub

isr18:
    cli
    push 0
    push 18
    jmp int_common_stub

isr96:
    cli
    push 0
    push 96
    jmp syscall_common_stub

irq0:
    cli
    push 0
    push 32
    jmp int_common_stub

irq1:
    cli
    push 0
    push 33
    jmp int_common_stub

irq2:
    cli
    push 0
    push 34
    jmp int_common_stub

irq3:
    cli
    push 0
    push 35
    jmp int_common_stub

irq4:
    cli
    push 0
    push 36
    jmp int_common_stub

irq5:
    cli
    push 0
    push 37
    jmp int_common_stub

irq6:
    cli
    push 0
    push 38
    jmp int_common_stub

irq7:
    cli
    push 0
    push 39
    jmp int_common_stub

irq8:
    cli
    push 0
    push 40
    jmp int_common_stub

irq9:
    cli
    push 0
    push 41
    jmp int_common_stub

irq10:
    cli
    push 0
    push 42
    jmp int_common_stub

irq11:
    cli
    push 0
    push 43
    jmp int_common_stub

irq12:
    cli
    push 0
    push 44
    jmp int_common_stub

irq13:
    cli
    push 0
    push 45
    jmp int_common_stub

irq14:
    cli
    push 0
    push 46
    jmp int_common_stub

irq15:
    cli
    push 0
    push 47
    jmp int_common_stub

irq16:
    cli
    push 0
    push 48
    jmp int_common_stub

irq17:
    cli
    push 0
    push 49
    jmp int_common_stub

irq18:
    cli
    push 0
    push 50
    jmp int_common_stub

irq19:
    cli
    push 0
    push 51
    jmp int_common_stub

irq20:
    cli
    push 0
    push 52
    jmp int_common_stub

irq21:
    cli
    push 0
    push 53
    jmp int_common_stub

irq22:
    cli
    push 0
    push 54
    jmp int_common_stub

irq23:
    cli
    push 0
    push 55
    jmp int_common_stub

global int_common_stub
extern int_handler

; WHY MUST THESE TWO BE DIFFERENT?
;
;	THE SYSCALL HANDLER ASSUMES EAX AND EDX CAN BE TRASHED (THE RETURN VALUE GOES IN)
;	AN INTERRUPT CAN HAPPEN AT ANY TIME. IF THEY WERE THE SAME HANDLER, ON EVERY 
;	INTERRUPT, EAX AND EDX WOULD 'MAGICALLY CHANGE', WHICH IS *VERY BAD*

int_common_stub:
    pushad

    push ds
    push es
    push fs
    push gs

    mov ax, 0x10   ; Load the Kernel Data Segment descriptor!
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov  ecx, esp		; Push us the stack
    push ecx
    mov  ecx, int_handler
    call ecx			; A special call, preserves the 'eip' register
    pop  ecx				;leave the return value 

	pop gs
    pop fs
    pop es
    pop ds

	popa
    add esp, 8     ; Cleans up the pushed error code and pushed ISR number

    iret           ; pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP!


global syscall_common_stub

;SYSTEM CALL NOTE:
;	RETURN VALUES ARE NOW DONE BY CHANGING EAX AND EDX IN THE REGS STRUCT

syscall_common_stub:
    pusha

    push ds
    push es
    push fs
    push gs

    mov ax, 0x10   ; Load the Kernel Data Segment descriptor!
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

	;save our current stack
	mov ecx, [currentTaskTCB]				;get the address of the TCB
	mov [ecx + 0x1C], esp

    mov  ecx, esp		; Push us the stack
    push ecx
    mov  ecx, int_handler
    call ecx			; A special call, preserves the 'eip' register
    pop  ecx				;leave the return value 

offAForkJumpThingy:
	pop gs
    pop fs
    pop es
    pop ds

	;SYSCALLS NOW ACTUALLY CHANGE THE VALUES THAT GET PUSHED HERE
	;SO POPA IS CORRECT (THE PRE-REWRITE METHOD OF KEEPING EDX:EAX IS *INCORRECT* NOW)
	popa
    add esp, 8     ; Cleans up the pushed error code and pushed ISR number

    iret           ; pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP!

