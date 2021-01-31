drawScreen:
	mov ax, 0xB800
	mov gs, ax

	mov bx, 0
.lp:
	mov [gs:bx], dword 0x0020
	add bx, 2
	cmp bx, 80 * 2
	jl .lp

	mov cx, 0
.lp2: 
	mov [gs:bx], dword 0x9920	;0x19B1
	cmp cx, 16
	jge .skipblack
	mov [gs:bx], dword 0x0020
.skipblack:
	inc cx
	cmp cx, 80
	jne .skipthat
	mov cx, 0
.skipthat:
	add bx, 2
	cmp bx, 80 * 25 * 2
	jl .lp2

	mov ax, 20
	mov bx, 3
	mov ch, 0x1F
	mov bp, title
	call drawText

	mov cx, 19
	mov bx, 4
.lp3:
	pusha
	mov ax, 20
	mov ch, 0xFF
	mov bp, blank
	call drawText
	popa
	inc bx
	loop .lp3

	mov ax, 16
	mov bx, 0
	mov ch, 0x0F
	mov bp, setuptitle
	call drawText

	ret

	;AX = x, BX = y, CH = colour, BP = string
drawText:
	mov di, ax		;start X
	mov si, bx		;start Y
dtx2:
	push cx
	mov cx, bx

	push ax
	mov ax, 0xB800
	mov gs, ax
	pop ax

.redo:
	mov bx, 0		
	cmp cx, 0
	je .skip
	mov dx, cx		;y pos
.looping:
	add bx, 160
	dec dx
	cmp dx, 0
	jne .looping

.skip:
	shl ax, 1		;double because two bytes / character
	add bx, ax		;xpos
	
	pop cx

	;CX = char + col, BX = pos
.again:
	mov cl, [bp]

	cmp cl, 0
	je .end
	cmp cl, 0xA
	je .newline
	mov [gs:bx], cx
	add bx, 2
	inc bp

	jmp .again

.end:
	ret

.newline:
	inc si
	mov ax, di
	mov bx, si
	inc bp
	jmp dtx2

drawStep1:
	mov ax, 1
	mov bx, 1
	mov ch, 0x0E
	mov bp, step1
	call drawText
	mov ax, 1
	mov bx, 5
	mov ch, 0x0F
	mov bp, step2
	call drawText
	mov ax, 1
	mov bx, 9
	mov ch, 0x0F
	mov bp, step3
	call drawText
	mov ax, 1
	mov bx, 13
	mov ch, 0x0F
	mov bp, step4
	call drawText
	mov ax, 1
	mov bx, 16
	mov ch, 0x0F
	mov bp, step5
	call drawText
	mov ax, 1
	mov bx, 21
	mov ch, 0x0B
	mov bp, timeleft1
	call drawText
	ret

drawStep2:
	mov ax, 1
	mov bx, 1
	mov ch, 0x0F
	mov bp, step1
	call drawText
	mov ax, 1
	mov bx, 5
	mov ch, 0x0E
	mov bp, step2
	call drawText
	mov ax, 1
	mov bx, 9
	mov ch, 0x0F
	mov bp, step3
	call drawText
	mov ax, 1
	mov bx, 13
	mov ch, 0x0F
	mov bp, step4
	call drawText
	mov ax, 1
	mov bx, 16
	mov ch, 0x0F
	mov bp, step5
	call drawText
	mov ax, 1
	mov bx, 21
	mov ch, 0x0B
	mov bp, timeleft2
	call drawText
	ret

drawStep3:
	mov ax, 1
	mov bx, 1
	mov ch, 0x0F
	mov bp, step1
	call drawText
	mov ax, 1
	mov bx, 5
	mov ch, 0x0E
	mov bp, step2
	call drawText
	mov ax, 1
	mov bx, 9
	mov ch, 0x0F
	mov bp, step3
	call drawText
	mov ax, 1
	mov bx, 13
	mov ch, 0x0F
	mov bp, step4
	call drawText
	mov ax, 1
	mov bx, 16
	mov ch, 0x0F
	mov bp, step5
	call drawText
	mov ax, 1
	mov bx, 21
	mov ch, 0x0B
	mov bp, timeleft3
	call drawText
	ret

firstLaunch:
	mov ax, 3
	int 0x13

	;disable hardware text blinking
	mov dx, 0x3DA
    in al, dx
    mov dx, 0x3C0
    mov al, 0x30
    out dx, al
    inc dx
    in al, dx
    and al, 0xF7
    dec dx
    out dx, al  

	;BIOS method, just in case
	mov ax, 0x1003
	mov bl, 0			;enable bg intensity, disable blinking
	mov bh, 0			;avoid problems on some adapters
	int 0x10

	call drawScreen

	call drawStep1

	mov ax, 22
	mov bx, 5
	mov ch, 0xF0
	mov bp, thank
	call drawText

.AwaitKeyPress:
	xor ax, ax
	int 0x16

	cmp ah, 0x1C	;ENTER
	je Stage2
	cmp ah, 0x01	;ESC			;0x3D	;F3
	je .doshutdown
	jmp .AwaitKeyPress

.doshutdown:
	call shutdown
	jmp .AwaitKeyPress

align 64
DAPACK22:
		db	0x10
		db	0
blkcnt2:	dw	4		; int 13 resets this to # of blocks actually read/written
dd_ad2:	dw	0x4000	; memory buffer destination address (0:7c00)
db_seg2:	dw	0x0000	; in memory page zero
d_lba2:	dd	0		; put the lba to read in this spot
		dd	0			; more storage bytes only for big lbas ( > 4 bytes )
times 64 db 0
align 8

driveParamBuffer db 256

Stage2:
	mov ax, 0
	mov fs, ax
	cmp [fs:0x4000], byte 0xFE
	;je forceMode

	call drawScreen
	call drawStep1
	mov ax, 22
	mov bx, 5
	mov ch, 0xF0
	mov bp, insertDisk
	call drawText

	mov dl, 0xDF
retry:
	inc dl
	cmp dl, 0xDF
	je .notFound

	mov eax, 64 / 4
	mov [blkcnt2], word 8
	mov [dd_ad2], word 0x4000
	mov [db_seg2], word 0
	mov [d_lba2], eax
	mov ah, 0x42
	mov si, DAPACK22
	cld
	push dx
	int 0x13
	pop dx
	jnc .maybeFound

	jmp retry

.maybeFound:
	mov ax, 0
	mov fs, ax

	cmp [fs:0x4000], byte 1
	jne .t2
	jmp .t3

.t2:
	mov eax, 64
	mov [blkcnt2], word 8
	mov [dd_ad2], word 0x4000
	mov [db_seg2], word 0
	mov [d_lba2], eax
	mov ah, 0x42
	mov si, DAPACK22
	cld
	push dx
	int 0x13
	pop dx
	jnc .t3
	jmp retry
.t3:
	mov bx, 0x4028
	cmp [fs:bx], byte 'B'
	jne retry
	inc bx
	cmp [fs:bx], byte 'A'
	jne retry
	inc bx
	cmp [fs:bx], byte 'N'
	jne retry
	inc bx
	cmp [fs:bx], byte 'A'
	jne retry
	inc bx
	cmp [fs:bx], byte 'N'
	jne retry
	inc bx
	cmp [fs:bx], byte 'A'
	jne retry
	inc bx
	cmp [fs:bx], byte ' '
	jne retry
	inc bx
	cmp [fs:bx], byte 'O'
	jne retry
	inc bx
	cmp [fs:bx], byte 'S'
	jne retry
	inc bx
	cmp [fs:bx], byte ' '
	jne retry
	inc bx
	cmp [fs:bx], byte '1'
	jne retry
	inc bx
	cmp [fs:bx], byte '.'
	jne retry
	inc bx
	cmp [fs:bx], byte '0'
	jne retry
	inc bx
	;cmp [fs:0x4807], byte 'E'
	;jne retry
	;cmp [fs:0x4808], byte 'L'
	;jne retry
	jmp found

.notFound:
	mov ax, 0
	int 0x16
	cmp ah, 0x12
	je .forceE0
	jmp Stage2

.forceE0:
	mov dl, 0xE0
	jmp found

forceMode:
	mov dl, [fs:0x4001]
	mov byte [fs:0x4000], 0
	jmp found

found:
	mov eax, 0xFFFF0000
	mov [cdromDriveNumber], dl
	jmp Stage5

cdromDriveNumber db 0

Stage3:
	call drawScreen
	call drawStep2
	mov ax, 22
	mov bx, 5
	mov ch, 0xF0
	mov bp, s2txt
	call drawText
	jmp Stage4

cselectedMode dw 0x4118
stuff times 5 db 0
hex db '0123456789ABCDEF', 0


lastmove db 1		;start it as 'up' so that it does something if the first mode doesn't work	

Stage4:
	call drawScreen
	call drawStep3
	mov ax, 22
	mov bx, 5
	mov ch, 0xF0
	mov bp, vidmtxt
	call drawText

	;make things invalid so if the mode info fails it goes with these, which makes "MODE cANNOT BE USED" appear
	mov [XRes], word 0
	mov [YRes], word 0
	mov [Bpp], byte 0

	mov cx, [cselectedMode]
	mov ax, 0x4F01
	mov bx, ds
	mov es, bx
	mov di, MODEINFO
	int 0x10

	mov ax, 22
	mov bx, 18
	mov ch, 0x70
	mov bp, currentmode1
	call drawText

	mov ax, [cselectedMode]
	and ax, 0xF
	mov bx, hex
	xlat
	mov [stuff + 2], al
	mov ax, [cselectedMode]
	shr ax, 4
	and ax, 0xF
	mov bx, hex
	xlat
	mov [stuff + 1], al
	mov ax, [cselectedMode]
	shr ax, 8
	and ax, 0xF
	mov bx, hex
	xlat
	mov [stuff + 0], al

	mov ax, 37
	mov bx, 18
	mov ch, 0x70
	mov bp, stuff
	call drawText

	mov ax, 22
	mov bx, 19
	mov ch, 0x70
	mov bp, currentmode2
	call drawText
	mov ax, 22
	mov bx, 20
	mov ch, 0x70
	mov bp, currentmode3
	call drawText

	mov bx, 19
	mov eax, 0
	mov ax, [XRes]
	call drawXYRes

	mov bx, 20
	mov eax, 0
	mov ax, [YRes]
	call drawXYRes

	cmp [Bpp], byte 8
	je .bit8
	cmp [Bpp], byte 15
	je .bit15
	cmp [Bpp], byte 16
	je .bit16
	cmp [Bpp], byte 24
	je .bit24
	cmp [Bpp], byte 32
	je .bit32

.BADMODE:
	mov ax, 22
	mov bx, 21
	mov ch, 0x70
	mov bp, invalid
	call drawText

	cmp word [cselectedMode], 0x4100
	je up
	cmp word [cselectedMode], 0x43FF
	je down

	cmp [lastmove], byte 1
	je up
	cmp [lastmove], byte 2
	je down

	jmp Stage4

.bit8:
	mov ax, 22
	mov bx, 21
	mov ch, 0x70
	mov bp, lowcolour
	call drawText
	jmp .endbit

.bit15:
	mov ax, 22
	mov bx, 21
	mov ch, 0x70
	mov bp, midcolour
	call drawText
	jmp .endbit

.bit16:
	mov ax, 22
	mov bx, 21
	mov ch, 0x70
	mov bp, midcolourbetter
	call drawText
	jmp .endbit

.bit24:
	mov ax, 22
	mov bx, 21
	mov ch, 0x70
	mov bp, highcolour
	call drawText
	jmp .endbit

.bit32:
	mov ax, 22
	mov bx, 21
	mov ch, 0x70
	mov bp, highcolourbetter
	call drawText
	jmp .endbit

.endbit:
	
.AwaitKeyPress:
	xor ax, ax
	int 0x16

	cmp ah, 0x1C	;ENTER
	je Stage6
	cmp ah, 0xF
	je resetmde
	cmp ah, 0x48
	je up
	cmp ah, 0x50
	je down
	cmp ah, 0x39
	je testVideoMode
	cmp ah, 0x1E
	je four3
	cmp ah, 0x1F
	je sixteen9
	jmp .AwaitKeyPress

down:
	mov [lastmove], byte 0
	cmp word [cselectedMode], 0x4100
	je Stage4
	mov [lastmove], byte 2
	dec word [cselectedMode]
	jmp Stage4

up:
	mov [lastmove], byte 0
	cmp word [cselectedMode], 0x43FF
	je Stage4
	mov [lastmove], byte 1
	inc word [cselectedMode]
	jmp Stage4

resetmde:
	mov [cselectedMode], word 0x4118
	mov [lastmove], byte 1		;start it as 'up' so that it does something if the first mode doesn't work
	jmp Stage4

testVideoMode:
	jmp Stage4

four3:
.retry:
	cmp word [cselectedMode], 0x43FF
	je Stage4
	inc word [cselectedMode]
	
	;setup a non 4:3 situation so if it fails, it doesn't accept it
	mov [XRes], word 16
	mov [YRes], word 9
	mov [Bpp], byte 0

	mov cx, [cselectedMode]
	mov ax, 0x4F01
	mov bx, ds
	mov es, bx
	mov di, MODEINFO
	int 0x10

	mov ax, [XRes]
	mov bx, [YRes]
	mov cx, ax
	add cx, ax
	add cx, ax
	shl bx, 2
	cmp bx, cx
	jne .retry

	jmp Stage4

sixteen9:
.retry:
	cmp word [cselectedMode], 0x43FF
	je Stage4
	inc word [cselectedMode]
	
	mov [XRes], word 0
	mov [YRes], word 0
	mov [Bpp], byte 0

	mov cx, [cselectedMode]
	mov ax, 0x4F01
	mov bx, ds
	mov es, bx
	mov di, MODEINFO
	int 0x10

	mov ax, [XRes]
	mov bx, [YRes]
	mov cx, ax
	add cx, ax
	add cx, ax
	shl bx, 2
	cmp bx, cx
	je .retry

	jmp Stage4

licensePage db 0
Stage5:
	call drawScreen
	call drawStep2
	mov ax, 22
	mov bx, 5
	mov ch, 0xF0
	mov bp, licenseIntro
	call drawText

	cmp [licensePage], byte 0
	je .l1
	cmp [licensePage], byte 1
	je .l2
	cmp [licensePage], byte 2
	je .l3
	cmp [licensePage], byte 3
	je .l4
	cmp [licensePage], byte 4
	je .l5
	cmp [licensePage], byte 5
	je .l6
	cmp [licensePage], byte 6
	je .l7
	cmp [licensePage], byte 7
	je .l8
	cmp [licensePage], byte 8
	je .l9
	cmp [licensePage], byte 9
	je .l10
.l1:
	mov bp, license1
	jmp .end
.l2:
	mov bp, license2
	jmp .end
.l3:
	mov bp, license3
	jmp .end
.l4:
	mov bp, license4
	jmp .end
.l5:
	mov bp, license5
	jmp .end
.l6:
	mov bp, license6
	jmp .end
.l7:
	mov bp, license7
	jmp .end
.l8:
	mov bp, license8
	jmp .end
.l9:
	mov bp, license9
	jmp .end
.l10:
	mov bp, license10
	jmp .end
.end:
	mov ax, 22
	mov bx, 10
	mov ch, 0xF1
	call drawText

	mov ax, 71
	mov bx, 5
	mov ch, 0xF0
	mov bp, topScroll
	call drawText
	mov ax, 71
	mov bx, 6
	mov ch, 0xF7
	mov bp, bo
	call drawText

	mov ax, 71
	mov bh, 0
	mov bl, [licensePage]
	add bl, [licensePage]
	add bl, [licensePage]
	shr bl, 1
	add bx, 6
	mov ch, 0x70
	mov bp, scrbar
	call drawText

	mov ax, 71
	mov bx, 5 + 16
	mov ch, 0xF0
	mov bp, btmScroll
	call drawText

.AwaitKeyPress:
	xor ax, ax
	int 0x16

	cmp ah, 0x1C
	je AGREE
	cmp ah, 0x51
	je .PDOWN
	cmp ah, 0x49
	je .PUP
	cmp ah, 0x01
	je shutdown
	jmp .AwaitKeyPress

	jmp $

.PDOWN:
	cmp [licensePage], byte 9
	je Stage5
	inc byte [licensePage]
	jmp Stage5
.PUP:
	cmp [licensePage], byte 0
	je Stage5
	dec byte [licensePage]
	jmp Stage5

topScroll db 30, 0
btmScroll db 31, 0
bo db 0xB0, 0xA, 0xB0, 0xA, 0xB0, 0xA, 0xB0, 0xA, 0xB0, 0xA, 0xB0, 0xA, 0xB0, 0xA, 0xB0, 0xA, 0xB0, 0xA, 0xB0, 0xA, 0xB0, 0xA, 0xB0, 0xA, 0xB0, 0xA, 0xB0, 0xA, 0xB0, 0xA, 0
scrbar db 0xB2, 0xA, 0xB2, 0

AGREE:
	cmp [licensePage], byte 9
	jne Stage5

	jmp Stage3
	ret

Stage6:
;	PMODE for the rest, although RMODE will be called for disk access
	xor ax, ax
	mov fs, ax
	mov ax, [cselectedMode]
	mov [fs:0x7001], ax
	mov [fs:0x7000], byte 1

	jmp backToOriginal				;this exits the first setup screen

shutdown:
	;save a copy of video memory
	;puts "Are you sure you want to exit Banana setup?"
	;if not:
		;load old video memory
		;use a 'ret'
	;else:
		;shutdown/reset/go to next disk/etc.

sizeout times 8 db 0
;sizeout db '0', '0', '0', '0', 0, 0, 0, 0

drawXYRes:
	;clear memory
	mov [sizeout], dword 0
	mov [sizeout + 4], dword 0
	push bx
	mov di, 0
.looping:
	mov ecx, 0
    .divisions:
        cmp eax, 10
        jl  .finish        ; IF DIVIDEND < DIVISOR
        sub eax, 10		; DIVIDEND - DIVISOR. EXAMPLE :  23 - 4.
        inc ecx      ; DIVISIONS COUNTER.
        jmp .divisions
    .finish:
	mov ebx, eax		;EBX has remainder
	mov eax, ecx		;EAX has quotent

	add bl, '0'			;make it nicer to display
	mov [sizeout + di], bl
	inc di
	
	cmp eax, 0
	je .donelooping

	jmp .looping

.donelooping:
	;time to reverse the string 'sizeout'

	mov ecx, 0
	mov cx, di
	mov eax, sizeout
	mov esi, eax  ; esi points to start of string
	add eax, ecx
	mov edi, eax
	dec edi       ; edi points to end of string
	shr ecx, 1    ; ecx is count (length/2)
	jz done       ; if string is 0 or 1 characters long, done
	reverseLoop:
	mov al, [esi] ; load characters
	mov bl, [edi]
	mov [esi], bl ; and swap
	mov [edi], al
	inc esi       ; adjust pointers
	dec edi
	dec ecx       ; and loop
	jnz reverseLoop
done:
	mov ax, 37
	pop bx
	mov ch, 0x70
	mov bp, sizeout
	call drawText

	ret
	

setuptitle db "Banana Setup", 0

insertDisk db "The Banana installation disk was not found.", 0xA, 0xA, "Please insert the Banana installation CD", 0xA, "and then press any key to continue.", 0;xA, 0xA, 0xA, 0xA, "If this doesn't work, try pressing 'E' to", 0xA, "assume it is drive 0xE0. If this doesn't", 0xA, "work, reboot the computer with the CD in.", 0

vidmtxt db "Video Mode Selection", 0xA, 0xA, \
		  "A video mode must now be selected that Banana", 0xA, \
		  "will run in. It will not effect Setup.", 0xA, 0xA, \
		  "Use the UP and DOWN arrow keys to change between", 0xA, \
		  "video modes. Hold SPACE to test the video mode.", 0xA, \
		  "When you have selected the best mode,", 0xA, \
		  "press RETURN. Press TAB to reset mode number.", 0xA, 0xA, \
		  "You can also press A to go to the next 4:3 mode,", 0xA, \
		  "and press S to go to the next non-4:3 mode.", 0

currentmode1		db " Mode Number :                ", 0
currentmode2		db " X Resolution:                ", 0
currentmode3		db " Y Resolution:                ", 0
lowcolour			db " Hundreds of colours          ", 0
midcolour			db " Thousands of colours         ", 0
midcolourbetter		db " Thousands of colours (better)", 0
highcolour			db " Millions of colours          ", 0
highcolourbetter	db " Millions of colours (better) ", 0

invalid		 db " MODE CANNOT BE USED  ", 0
s2txt db  "Please wait while Setup ensures your hard", 0xA, \
		  "drive has enough space and is configured", 0xA, \
		  "correctly.", 0
thank db  "Welcome to Banana setup.", 0xA, 0xA, \
		  "Congratulations on chosing Banana, the software", 0xA, \
		  "that makes your computer LESS powerful, reliable,", 0xA, \
		  "manageable and entertaining.", 0xA, 0xA,\
		  "With Banana, you can't connect to the internet.", 0xA, 0xA, 0xA, \
		  "Setup will take from 10 to 20 minutes, depending", 0xA, \
		  "on the speed of your computer.", 0xA, 0xA, \
		  "Press ENTER to continue or ESC to quit.", 0

;Setup will take from 10 to 20 minutes, dependin|
licenseIntro db "Please read the following license agreement", 0xA, "carefully. You cannot install Banana unless", 0xA, "you sign the agreement. Press PAGE UP and", 0xA, "PAGE DOWN to scroll through the pages.", 0xA, 0xA, 0
license1 db \
"BANANA OPERATING SYSTEM AND RELATED COMPONENTS", 0xA,\
"END USER LICENSE AGREEMENT", 0xA,\
0xA,\
"PLEASE READ THE FOLLOWING LICENSE CAREFULLY" , 0xA,\
"BEFORE USING THIS SOFTWARE. BY USING THIS" , 0xA,\
"SOFTWARE, YOU AGREE TO BE BOUND BY THE TERMS OF", 0xA,\
"THIS LICENSE.", 0xA, 0xA,\
"This End User License Agreement ('EULA') is a", 0xA, \
"legal agreement between (a) you (either as an", 0xA, \
"individual or a single entity) and (b) Alex ", 0xA, \
"Boxall ('AB'), which governs the use the", 0

license2 db \
"Banana Operating System and any related ", 0xA, \
"software components, installation media and", 0xA, \
"the data recorded on it (excluding the ", 0xA, \
"installation program currently being used, but", 0xA, \
"including any related electronic files that it", 0xA, \
"may or may not install), documentation and ", 0xA, \
"electronic files (the 'Software'). The ", 0xA, \
"Software is licensed, not sold to you by AB", 0xA, \
"for use only under the terms of this EULA. ", 0xA, \
"AB reserves all rights not explicitly granted", 0xA, \
"to you by this EULA. ", 0

license3 db \
"BY PRESSING RETURN TO AGREE TO THIS LICENSE,", 0xA, \
"OR BY INSTALLING OR OTHERWISE USING THE THE",0xA, \
"SOFTWARE YOU AGREE TO BE BOUND BY THE THE ",0xA, \
"TERMS OF THIS EULA. IF YOU DO NOT AGREE TO ",0xA, \
"THE TERMS OF THIS EULA, YOU MAY NOT USE OR ", 0xA, \
"INSTALL THE SOFTWARE. YOU MAY, HOWEVER, RETURN", 0xA, \
"THE SOFTWARE TO YOUR PLACE OF PURCHASE FOR A ", 0xA, \
"FULL REFUND.", 0xA, 0xA, \
"1. LIMITED LICENSE. This EULA grants you a ", 0xA, \
"revocable, non-exclusive, limited license to", 0xA, \
"use the Software as follows: You may install, ", 0

license4 db \
"use, access and display one copy of the ", 0xA, \
"Software on a single computer or device. To ", 0xA, \
"'use' this software means that the software is", 0xA, \
"loaded into temporary memory (i.e., RAM) of a", 0xA, \
"computer or installed on the permanent memory", 0xA, \
"of a computer (i.e., hard disk, etc.). You may", 0xA, \
"make one backup copy of the Software for backup", 0xA, \
"and archival purposes only. The Software is ", 0xA, \
"licensed, not sold.", 0xA, 0xA, \
"2. RESTRICTIONS ON USE. You must not remove or", 0xA, \
"alter any of the copyright notices on all ", 0xA, 0

license5 db \
"copies of the Software. You may not distribute ", 0xA, \
"copies of the Software to third parties. You ", 0xA, \
"may not sell or copy this software. This EULA", 0xA, \
"does not grant any rights in connection with ", 0xA, \
"any trademarks or service marks of AB. You may", 0xA, \
"not reverse engineer, decompile, or disassemble", 0xA, \
"the Software, except and only to the extent ", 0xA, \
"that such activity is expressly permitted by ", 0xA, \
"applicable law notwithstanding this limitation.", 0xA, \
"You may not rent, lease, or lend the Software. ", 0xA, \
"You may permanently transfer all of your rights", 0xA, \
"under this EULA, provided the recipient agrees", 0xA, 0

license6 db \
"to the terms of this EULA. You must comply with", 0xA, \
"all applicable laws regarding use of the ", 0xA, \
"Software. ", 0xA, \
 0xA, \
"3. TERMINATION. This license is perpetual or", 0xA, \
"until you fail to comply with the terms and ", 0xA, \
"conditions of this EULA or AB terminates it ", 0xA, \
"with or without cause. In such event, you ", 0xA, \
"must destroy all copies of the Software.", 0xA, \
 0xA, \
"4. COPYRIGHT. All title, including but not", 0xA, \
"limited to copyrights, in and to the Software", 0xA, 0

license7 db \
"and any copies thereof are owned by AB. All ", 0xA, \
"title and intellectual property rights in and", 0xA, \
"to the content which may be accessed through ", 0xA, \
"use of the Software is the property of the ", 0xA, \
"respective content owner and may be protected", 0xA, \
"by applicable copyright or other intellectual", 0xA, \
"property laws and treaties. This EULA grants", 0xA, \
"you no rights to use such content. All rights", 0xA, \
"not expressly granted are reserved by AB.", 0xA, \
 0xA, \
"5. NO WARRANTIES. THE SOFTWARE IS PROVIDED ", 0xA, \
"'AS IS', WITHOUT WARRANTY OF ANY KIND, EXPRESS", 0xA, 0

license8 db \
"OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE ", 0xA, \
"WARRANTIES OF MERCHANTABILITY, FITNESS FOR A ", 0xA, \
"PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO", 0xA, \
"EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE", 0xA, \
"LIABLE FOR ANY CLAIM, DAMAGES OR OTHER ", 0xA, \
"LIABILITY, WHETHER IN AN ACTION OF CONTRACT,", 0xA, \
"TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN", 0xA, \
"CONNECTION WITH THE SOFTWARE OR THE USE OR ", 0xA, \
"OTHER DEALINGS IN THE SOFTWARE.", 0xA, \
0xA, \
"6. LIMITATION OF LIABILITY. TO THE MAXIMUM ", 0xA, \
"EXTENT PERMITTED BY APPLICABLE LAW, IN NO ", 0xA, 0

license9 db \
"EVENT SHALL AB OR ITS SUPPLIERS BE LIABLE ", 0xA, \
"FOR ANY SPECIAL, INCIDENTAL, INDIRECT, OR ", 0xA, \
"CONSEQUENTIAL DAMAGES WHATSOEVER (INCLUDING, ", 0xA, \
"WITHOUT LIMITATION, DAMAGES FOR LOSS OF BUSINESS", 0xA, \
"PROFITS, BUSINESS INTERRUPTION, LOSS OF BUSINESS", 0xA, \
"INFORMATION, OR ANY OTHER PECUNIARY LOSS) ", 0xA, \
"ARISING OUT OF THE USE OF OR INABILITY TO USE", 0xA, \
"THE SOFTWARE PRODUCT OR THE FAILURE TO PROVIDE", 0xA, \
"SUPPORT SERVICES, EVEN IF AB HAS BEEN ADVISED", 0xA, \
"OF THE POSSIBILITY OF SUCH DAMAGES. IN ANY CASE,", 0xA, \
"AB’S ENTIRE LIABILITY UNDER ANY PROVISION OF ", 0xA, \
"THIS EULA SHALL BE LIMITED TO THE THE AMOUNT ", 0xA, 0

license10 db \
"ACTUALLY PAID BY YOU FOR THE SOFTWARE PRODUCT.", 0xA, \
"BECAUSE SOME STATES/JURISDICTIONS DO NOT ALLOW", 0xA, \
"THE EXCLUSION OR LIMITATION OF LIABILITY, THE ", 0xA, \
"ABOVE LIMITATION MAY NOT APPLY TO YOU.", 0xA, \
0xA, \
"7. If any section of this agreement is found", 0xA, \
"to be unenforceable the remaining sections", 0xA, \
"still apply.", 0xA, \
 0xA, \
"Press RETURN to agree or ESC to quit Setup.", 0


blank db "                                                      ", 0
title db "                     Banana Setup                     ", 0

;         0123456789ABCDEF
		   
step1 db  "Preparing to  ", 0xA, \
		  "run Banana", 0xA, \
		  "setup.", 0xA, 0xA,0
step2 db  "Collecting", 0xA, \
		  "info about", 0xA, \
		  "your computer", 0xA,0xA,0
step3 db  "Copying Banana", 0xA, \
		  "files to your", 0xA, \
		  "computer", 0xA, 0xA,0
step4 db  "Setting up", 0xA, \
		  "hardware", 0xA, 0xA,0
step5 db  "Finalizing", 0xA, \
		  "settings.", 0xA, 0xA, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196,0
timeleft1 db "Estimated time", 0xA, "remaining:", 0xA, "25 minutes", 0
timeleft2 db "Estimated time", 0xA, "remaining:", 0xA, "24 minutes", 0
timeleft3 db "Estimated time", 0xA, "remaining:", 0xA, "21 minutes", 0

