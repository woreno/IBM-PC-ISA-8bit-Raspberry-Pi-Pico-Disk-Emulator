	;*****************************************************
CPU_RESTORE_REGISTERS_FROM_PICO:

	 mov ax, word ptr cs:[FLAG_AX]	
	 mov bx, word ptr cs:[FLAG_BX]	
	 mov cx, word ptr cs:[FLAG_CX]	
	 mov dx, word ptr cs:[FLAG_DX]	
	 mov es, word ptr cs:[FLAG_ES]	
	 mov ds, word ptr cs:[FLAG_DS]	
	 mov si, word ptr cs:[FLAG_SI]	
	 mov di, word ptr cs:[FLAG_DI]	
	 mov bp, word ptr cs:[FLAG_BP]	

ret


;*****************************************************
CPU_SAVE_REGISTERS_FOR_PICO:
	 mov word ptr cs:[FLAG_AX], ax	
	 mov word ptr cs:[FLAG_BX], bx	
	 mov word ptr cs:[FLAG_CX], cx	
	 mov word ptr cs:[FLAG_DX], dx	
	 mov word ptr cs:[FLAG_DS], ds	
	 mov word ptr cs:[FLAG_ES], es	
	 mov word ptr cs:[FLAG_DS], ds	
	 mov word ptr cs:[FLAG_SI], si	
	 mov word ptr cs:[FLAG_DI], di	
	 mov word ptr cs:[FLAG_BP], bp
ret


tty_printX:
	push ax				
		mov al,'x'		
		call tty_char 	
	pop ax				
ret

longwait:
	push cx
		M_Countdown cx, 5FFFh	; obrigatório
	pop cx
ret
shortwait:
	push cx
		M_Countdown cx, 0Fh	; obrigatório
	pop cx
ret



;*****************************************************
CPU_SET_OPERATION_FOR_PICO:
	mov byte ptr cs:[FLAG_CMD]	, 0
	mov byte ptr cs:[FLAG_START_OPERATION]	, 1
ret

CPU_WAIT_RES:	
	push ax

		WAIT_RES_LOOP:
				
			mov al, byte ptr cs:[FLAG_CMDRES]
			cmp al, 0
			jnz WAIT_RES_EXIT
			
			;mov al, '.'
			;call tty_char
			call shortwait
			jmp WAIT_RES_LOOP

		WAIT_RES_EXIT:
			mov byte ptr cs:[FLAG_CMDRES], 0
  pop ax
ret

RESTORE_OPERATION_FLAGS:
	mov byte ptr cs:[FLAG_CMDRES], 0
	mov byte ptr cs:[FLAG_CMD], 0
	ret




;*****************************************************
tty_crlf:
	push ax
	push bx
		mov ax, 0E0Ah
		mov bx, 0Fh	
		int 10h
		mov al, 13
		int 10h
	pop bx
	pop ax
ret
;*****************************************************
tty_str:
	push ax
	push bx
	push bp
		mov ax, 0E0Ah
		mov bx, 0Fh	
		;int 10h
		;mov al, 13
		;int 10h
		
		;mov al, cl
		;int 10h
		;inc cl

		tty_str_loop:
			mov al, cs:[bp]
			cmp al, 0
			jz STR_PRINT_EXIT
			int 10h
			inc bp
			jnz tty_str_loop
		
		STR_PRINT_EXIT:
	pop bp
	pop bx
	pop ax
	ret

;*****************************************************
FOREVER:
	jmp FOREVER



;*****************************************************
;TEST_VARS:
; mov word ptr cs:[INT13h_ORIGINAL_IP]	, 0201h				
; mov word ptr cs:[INT13h_ORIGINAL_SEG]	, 0403h
; mov word ptr cs:[INT19h_ORIGINAL_IP]	, 0605h
; mov word ptr cs:[INT19h_ORIGINAL_SEG]	, 0807h			
; mov word ptr cs:[FLAG_AX]				, 1009h		
; mov word ptr cs:[FLAG_BX]				, 1211h		
; mov word ptr cs:[FLAG_CX]				, 1413h		
; mov word ptr cs:[FLAG_DX]				, 1615h		
; mov word ptr cs:[FLAG_ES]				, 1817h		
; mov word ptr cs:[FLAG_SI]				, 2019h	
; mov word ptr cs:[FLAG_DI]				, 2221h	
; mov byte ptr cs:[FLAG_START_OPERATION]	, 23h
; mov byte ptr cs:[FLAG_BLOCK_RASPBERRY]	, 24h		
; mov byte ptr cs:[FLAG_BLOCK_CPU]		, 25h			
; mov byte ptr cs:[FLAG_BOOT]			, 26h			
; mov byte ptr cs:[FLAG_DRVA_IS_PHYSICAL], 27h
; mov byte ptr cs:[FLAG_DRVB_IS_PHYSICAL], 28h
; mov byte ptr cs:[FLAG_DRVC_EXISTS]		, 29h
; mov byte ptr cs:[FLAG_DRVC_USE]		, 2Ah
;ret

;BEEP: 
;push ax
;	M_beep 1000
;pop ax
;ret

;tty_bit:
;push bx
;	mov bx, 0Fh
;	mov ah, 0Eh
;	add al, '0'
;	int 10h
;pop bx
;ret

;tty_bits:
;	push ax
;	push cx
;	push dx
;		mov dl, al
;		mov cl, 8
;		tty_bits_loop:
;			mov al, dl
;			and al, 1
;			call tty_bit
;			shr dl, 1
;			dec cl
;			jnz tty_bits_loop
;	pop dx
;	pop cx
;	pop ax
;ret


tty_char:
	push ax
	push bx
		mov ah, 0Eh
		mov bx, 0Fh	
		int 10h
	pop bx
	pop ax
ret

tty_space:
	push ax
	push bx
		mov ax, 0E20h
		mov bx, 0Fh	
		int 10h
	pop bx
	pop ax
ret

; imprime lower 4 bits hexadecimal
tty_toHex_lowNibble:
	push AX
	push BX
	and AX, 0Fh

	cmp al, 10
	jl tty_toHex_lowNibble_number
	
	sub al, 10
	add al, 'A'

	jmp tty_toHex_lowNibble_done

	tty_toHex_lowNibble_number:
	add al, '0'

	tty_toHex_lowNibble_done:
	mov ah, 0Eh
	mov bx, 0Fh	
	int 10h
	pop BX
	pop AX
ret

; imprime byte hexadecimal
tty_toHex_byte:
	push AX
		shr AX, 4
		call tty_toHex_lowNibble
	pop AX		
	call tty_toHex_lowNibble
ret

; imprime byte hexadecimal
tty_toHex_word:
	push ax
	push ax
		xchg al, ah
		call tty_toHex_byte
	pop ax
		call tty_toHex_byte
	pop ax
ret

tty_regs:
	
	push ax
	push es
	push bx
	push bp
	call tty_crlf

		mov bp, offset STR_AX
		call tty_str
		call tty_toHex_word
		
		mov ax, bx
		mov bp, offset STR_BX
		call tty_str
		call tty_toHex_word
		
		mov ax, cx
		mov bp, offset STR_CX
		call tty_str
		call tty_toHex_word
		
		mov ax, dx
		mov bp, offset STR_DX
		call tty_str
		call tty_toHex_word
		

		mov ax, es
		mov bp, offset STR_ES
		call tty_str
		call tty_toHex_word

		mov ax, di
		mov bp, offset STR_DI
		call tty_str
		call tty_toHex_word

		call tty_crlf

		mov ax, ds
		mov bp, offset STR_DS
		call tty_str
		call tty_toHex_word
		
		mov ax, si
		mov bp, offset STR_SI
		call tty_str
		call tty_toHex_word
		
		mov ax, cs
		mov bp, offset STR_CS
		call tty_str
		call tty_toHex_word
		
		push ss
		pop es
		mov bx, sp
		mov ax, word ptr es:[bx]
		mov bp, offset STR_IP
		call tty_str
		call tty_toHex_word
		
		mov ax, ss
		mov bp, offset STR_SS
		call tty_str
		call tty_toHex_word

		mov ax, sp
		mov bp, offset STR_SP
		call tty_str
		call tty_toHex_word

	pop bp
	pop bx
	pop es
	pop ax
ret


INT13_DRV_STR  db " dr:",0  
INT13_C_STR    db " C:",0  
INT13_H_STR    db " H:",0  
INT13_S_STR    db " S:",0 
INT13_N_STR    db " #:",0  

STR_AX  db " AX:",0  
STR_BX  db " BX:",0  
STR_CX  db " CX:",0  
STR_DX  db " DX:",0 
STR_ES  db " ES:",0  
STR_DI  db " DI:",0  
STR_DS  db " DS:",0  
STR_SI  db " SI:",0  

STR_CS  db " CS:",0  
STR_IP  db " IP:",0  
STR_SS  db " SS:",0  
STR_SP  db " SP:",0  