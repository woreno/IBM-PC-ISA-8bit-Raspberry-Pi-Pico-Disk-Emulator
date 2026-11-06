;*****************************************************
; Serviço de BIOS de Discos
; ****************************************************

MODO_DEBUG              EQU 0
MODO_DEBUG_NO_HDD	    EQU 0

 ;******************************************************************************************************************************
INT13h_HANDLE_READ_:
	jmp INT13h_HANDLE_READ
INT13h_HANDLE_WRITE_:
	jmp INT13h_HANDLE_WRITE

 INT13h_HANDLE_VIRTUAL_PROC: 
  	
	cmp ah, 2						; status?
	jb INT13h_HANDLE_STATUS
	cmp ah, 2						; funcao de ler?
	jz INT13h_HANDLE_READ_
	cmp ah, 3						; funcao de escrita?
	jz INT13h_HANDLE_WRITE_
	cmp ah, 8						; funcao de escrita?
	jz INT13h_HANDLE_PARAMS
	cmp ah, 15h						; funcao de escrita?
	jz INT13h_HANDLE_F15
	cmp ah, 16h						; funcao de escrita?
	jz INT13h_HANDLE_F16
		
INT13h_HANDLE_STATUS:				
	call CPU_RESTORE_REGISTERS_FROM_PICO
	xor AH, AH						; STATUS = OK
	clc
	M_retFarWithout 2 

INT13h_HANDLE_ERROR:
	call RESTORE_OPERATION_FLAGS
	call CPU_RESTORE_REGISTERS_FROM_PICO
	;mov AH, 1
	stc
	M_retFarWithout 2  

INT13h_HANDLE_PARAMS:
INT13h_HANDLE_F15:
	call CPU_SET_OPERATION_FOR_PICO	 
	mov byte ptr cs:[FLAG_CMD], 1	
	call CPU_WAIT_RES
	call RESTORE_OPERATION_FLAGS
	call CPU_RESTORE_REGISTERS_FROM_PICO
	clc
	M_retFarWithout 2  

INT13h_HANDLE_F16:
	;call INT13h_PRINT_PROLOG
	call CPU_SET_OPERATION_FOR_PICO	 
	mov byte ptr cs:[FLAG_CMD], 1	
	call CPU_WAIT_RES
	call RESTORE_OPERATION_FLAGS
	call CPU_RESTORE_REGISTERS_FROM_PICO  
	;call tty_regs
	;call longwait
	;call longwait
	clc
	M_retFarWithout 2

INT13h_HANDLE_INVALID_DRIVE:
	
	cmp AH, 15h							; é drive type?
	jz INT13h_HANDLE_INV_DRVTYPE		; se é outra funcao devolver erro
	
		call CPU_RESTORE_REGISTERS_FROM_PICO
		mov AH, 07h
		stc
		M_retFarWithout 2  

	INT13h_HANDLE_INV_DRVTYPE:
		call CPU_RESTORE_REGISTERS_FROM_PICO
		xor CX, CX						; zerar setores
		xor DX, DX
		xor AH, AH						; indicar unidade não-presente
		;call tty_regs
		;call longwait
		;call longwait
		clc
		M_retFarWithout 2  


									

;******************************************************************************************************************************
;*
;*      |
;*      |
;*    \ | /
;*     \|/
;*      v
INT13h_HANDLER:
 
	call CPU_SAVE_REGISTERS_FOR_PICO			; gravar todos os registos para
		 
	IF MODO_DEBUG
		call INT13h_PRINT_PROLOG
	ENDIF

	IF MODO_DEBUG_NO_HDD						; modo debug
		cmp dl, 80h								; se 1º disco rigido
		jae INT13h_HANDLE_PHYSICAL				; manda para INT original
	ELSE
		cmp dl, 80h									; é disco rigido? 
		ja INT13h_HANDLE_INVALID_DRIVE

		cmp dl, 80h								; é drive 0x80	
		jz INT13h_isHDD0
	ENDIF

	mov ax, word ptr cs:[FLAG_DRVA_IS_PHYSICAL]	; a drive 0/1 é fisica?
	  
	cmp dl, 1									; é drive 1?
	jz INT13h_isFDD1
	
	cmp dl, 0									; é drive 0?
	jz INT13h_isFDD0

	jz INT13h_HANDLE_PHYSICAL					; drive desconhecida


	INT13h_isHDD0:
		cmp byte ptr cs:[FLAG_DRVC_EXISTS], 0	; existe HDD emulado?
		jz INT13h_HANDLE_PHYSICAL
		cmp byte ptr cs:[FLAG_DRVC_USE], 1		; usar?
		jz INT13h_HANDLE_VIRTUAL
		jmp INT13h_HANDLE_PHYSICAL

	INT13h_isFDD0:								; é decerteza drive 0!
		cmp al, 1
		jz INT13h_HANDLE_PHYSICAL				; saltar para INT13h original
		jmp INT13h_HANDLE_VIRTUAL				; ou saltar para virtual

	INT13h_isFDD1:
		cmp ah, 1
		jz INT13h_HANDLE_PHYSICAL				; saltar para INT13h original
		jmp INT13h_HANDLE_VIRTUAL				; ou saltar para virtual

	INT13h_HANDLE_VIRTUAL:
		IF MODO_DEBUG
			call INT13h_PRINT_VIRTUAL
		ENDIF
		call CPU_RESTORE_REGISTERS_FROM_PICO
		jmp INT13h_HANDLE_VIRTUAL_PROC

	INT13h_HANDLE_PHYSICAL:
		IF MODO_DEBUG
			call INT13h_PRINT_FAR
		ENDIF
		call CPU_RESTORE_REGISTERS_FROM_PICO
		call RESTORE_OPERATION_FLAGS
		clc
		jmp INT13_FACTORY_JUMP			; salto NEAR (para outro salto)
		 
	INT13_STR          db "[INT13-",0 
	INT13_FARJP_STR    db "-FAR",0 
	INT13_VIRTUAL_STR  db "-VIR",0  
	
INT13h_GOTO_FACTORY_DEBUG:


 ;*****************************************************
 INT13h_HANDLE_WRITE:			; ES:DI	= target (C820:0000)
					 			; DS:SI = source (ES:BX)
	
	cli
	call CPU_SET_OPERATION_FOR_PICO	

	push es						; guardar ES
	pop ds						; DS:SI = source (ES:BX)
	
	push DISK_BUFFER_SEG		; ES:DI = C820:0000 (target)
	pop es
	
	
	INT13h_HANDLE_WRITE_LOOP:
	
		mov si, bx
		xor di, di
		
		;call tty_printX
		
		cld	
		mov cx, 256							; copiar 512 bytes
		rep movsw							; es:di=destino
											; ds:si=origem
		
		mov byte ptr cs:[FLAG_CMD], 1		; mandar flag de COMANDO


		call CPU_WAIT_RES						 
												 
											
		mov cx, ds							; adicionar 512 bytes
		add cx, 020h						; ao segmento de DS	(+0x20)
		mov ds, cx

		dec al								; decrementar numero de setores
		jnz INT13h_HANDLE_WRITE_LOOP		; a copiar
		
JMP INT13h_HANDLE_RW_EXIT
	 
;*****************************************************
 INT13h_HANDLE_READ:			; ES:DI	= target
								; DS:SI = source (C820:0000)
    cli
	call CPU_SET_OPERATION_FOR_PICO	

	push DISK_BUFFER_SEG		; DS:SI = C820:0000
	pop ds

	INT13h_HANDLE_READ_LOOP:

		;call tty_printX

		mov si, 0							; DS:SI = C820:0000 SI sempre a 0
		mov di, bx							; ES:DI = destino tem de manter DI
		
		;call shortwait 
		
		mov byte ptr cs:[FLAG_CMD], 1		; mandar flag de COMANDO
		call CPU_WAIT_RES					; esperar RESULTADO 

		cld									; COPIAR 512-BYTES
		mov cx, 256
		rep movsw	
											;mov di, bx	
											;call tty_buffer
											;call shortwait


		mov cx, es							; adicionar 512 bytes
		add cx, 020h						; ao segmento de ES	(+0x20)
		mov es, cx
		
		dec al								; decrementar numero de setores
		cmp al, 0
		jnz INT13h_HANDLE_READ_LOOP			; loop de AL!=0

INT13h_HANDLE_RW_EXIT:
	call RESTORE_OPERATION_FLAGS
	call CPU_RESTORE_REGISTERS_FROM_PICO
	xor AH, AH								; STATUS = OK
	sti
	clc
	M_retFarWithout 2 

;*****************************************************
INSTALL_SPECIAL_INT13h:

	mov al, 0EAh
	mov byte ptr cs:[INT13h_JUMP_OPCODE], al

	push 0
	pop es
	mov word ptr dx, es:[13h*4]
	mov word ptr cs:[INT13h_ORIGINAL_IP], dx
	mov word ptr dx, es:[13h*4+2]
	mov word ptr cs:[INT13h_ORIGINAL_IP+2], dx


	mov word ptr es:[13h*4], OFFSET INT13h_HANDLER
	mov word ptr es:[13h*4+2], 0C800h

	ret
	


IF MODO_DEBUG 

;*****************************************************
tty_int13h:
push ax
push cx
push bp

	push ax
		mov bp, offset INT13_DRV_STR
		call tty_str
		mov al, dl
		call tty_toHex_byte
    pop ax

	
	cmp AH,02
	jb tty_int13h_skip
	cmp AH,03
	ja tty_int13h_skip

	
	;                             
	; mask =            0xFFFF        0x3    0x3F
	; bits =   15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
	;          |_____________________||__||_________|
	;               cils (baixo)       |      | 
	;                           cils(alto)    |
	;                                        sector 


	push ax
		mov bp, offset INT13_C_STR		; imprimir cilindro
		call tty_str
		mov ax, cx
		shr ax, 8		; ax>>8
		shr cx, 5		; cx>>5		
		shl cx, 8		; cx<<8
		or  ax, cx		; ax|cx
		call tty_toHex_byte

	
		mov bp, offset INT13_H_STR		; imprimir cabeca
		call tty_str
		mov al, dh
		call tty_toHex_byte
	
		mov bp, offset INT13_S_STR		; imprimir sector
		call tty_str
		mov al, cl
		and al, 01Fh
		call tty_toHex_byte
	pop ax
	
		mov bp, offset INT13_N_STR
		call tty_str
		call tty_toHex_byte
		call tty_space
 
		mov ax, es
		call tty_space
		call tty_toHex_word

		mov al, ':'
		call tty_char

		mov ax, bx
		call tty_toHex_word
		call tty_space

	tty_int13h_skip:
pop bp
pop cx
pop ax
ret 
;*****************************************************
INT13h_PRINT_FAR:
		mov bp, offset INT13_FARJP_STR			; TEST
		call tty_str 							; TEST 
	ret
;*****************************************************
INT13h_PRINT_VIRTUAL:
		mov bp, offset INT13_VIRTUAL_STR		; TEST
		call tty_str							; TEST 
	ret
;*****************************************************
INT13h_PRINT_PROLOG:
	
		 call tty_crlf								; IMPRIMIR
		 push ax										; CONTADOR
	 		inc byte ptr cs:[FLAG_BOOT]				;
	 		mov al,cs:[FLAG_BOOT]					;
	 		call tty_toHex_byte						;
	 		call tty_space							;
		 pop ax
	
		 ; cmp byte ptr cs:[FLAG_BOOT], 36h
		 ;jz INT13h_GOTO_FACTORY_DEBUG

		  mov bp, offset INT13_STR					; IMPRIMIR
		  call tty_str 							; INT13h
		  push ax									; 
	  		xchg al, ah								; 
	  		call tty_toHex_byte						; 
	  		mov al, ']'								; 
	  		call tty_char							; 
		  pop ax									; 
		  call tty_int13h							; 
	 
ret
;*****************************************************

ENDIF