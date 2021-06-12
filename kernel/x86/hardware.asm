[bits 32]


global manualPCIProbe

manualPCIProbe:
    xor eax, eax

;Detect if mechanism #1 is supported
   mov dx,0x0CF8
   in eax,dx
   mov ebx,eax
   mov eax,0x80000000
   out dx,eax
   in eax,dx
   cmp eax,0x80000000
   jne .noMech1
   mov eax,0x01
   jmp .gotPCI
.noMech1:
   mov eax,ebx
   out dx, eax

;Detect if mechanism #2 is supported

   mov dx,0x0CF8
   in al,dx
   mov bl,al
   xor al, al
   out dx,al
   in al,dx
   test al,al
   jne .noPCI

   mov dx,0x0CFA
   in al,dx
   mov bh,al
   xor al, al
   out dx,al
   in al,dx
   test al,al
   jne .noPCI
   mov eax,0x02

.gotPCI:       ; Value in EAX will be 1 if mechanism #1 is supported, or 2 if mechanism #2 is supported
    ret

.noPCI:
    xor eax, eax
    ret

global prepareTramp
prepareTramp:
    sgdt [0xFE0]
    sidt [0xFE8]
    push eax
    mov eax, cr3
    mov [0xFF0], eax
    pop eax
    ret

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
	times 45 db 0x90
	xor eax, eax
	ret


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


global goToVM86

goToVM86:
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
	push dword 0x20202
	push ebx
	push eax

	iretd


goToUsermode:
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
	push dword 0x202
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
	jne .firstTime

	mov esp, [esi + 0x4]			;ESP stored at offset 0x4 into the struct

	call changeTSS

	pop ebp
	pop edi
	pop esi
	pop edx
	pop ecx
	pop ebx
	pop eax
	popf

	ret

.firstTime:
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

	pop ebp
	pop edi
	pop esi
	pop ecx			;don't pop edx
	pop ecx
	pop ebx
	pop eax
	add esp, 4          ;DON'T POP FLAGS
        
    push byte 0x2
    popf                ;get a safe set of flags

	;and we're off!
	push edx					;start point
	call taskStartupFunction	;jumps to start point when it returns
	pop edx						;EDX contains the start point
	push eax					;EAX was the return value of the previous thing, and the argument of the next function
	call edx					;go to the start point
	call taskReturned			;in case anything returns

	jmp $

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


global memcpy
extern __not_memcpy
memcpy:
    jmp __not_memcpy
