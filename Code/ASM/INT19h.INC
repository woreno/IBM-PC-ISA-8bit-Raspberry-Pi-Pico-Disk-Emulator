
;****************************************************
; INT19h Serviço de BIOS de Bootstrap
;****************************************************

	DISK_BOOT_SEG		EQU 07C0h
	DISK_BOOT_OFFSET	EQU 07C00h


;******************************************************************************************************************************

INT19h_TEST_AA55:						; Testar se o buffer
push es
	 
	push DISK_BOOT_SEG
	pop es			
										; contem magic word "AA55h"
	cmp es:[510], 0AA55h				; nos ulimos 2 bytes
	jz INT19h_TEST_AA55_PASS

		mov bp, OFFSET INT19_STR_CROSS
		call tty_str
		stc
		jmp INT19h_TEST_AA55_END

	INT19h_TEST_AA55_PASS:
	
		mov bp, OFFSET INT19_STR_OK
		call tty_str
		clc
	INT19h_TEST_AA55_END:

pop es	
ret
		
INT19_SET_DISK_REGS:
	push DISK_BOOT_SEG
	pop es							; ES = DISK_BOOT_SEG, Segmento de Boot (07C00h)
	mov bx, 0						; BX = 0,  Offset de Boot
	mov al, 1						; AL = 1,  Setores
	mov ah, 2						; AH = 2,  função: Ler setores
	mov cl, 1						; CL = 1,  Setor 1 (notação BIOS para "setor 0")
	mov ch, 0						; CH = 0,  Cilindro 0
	mov dh, 0						; DH = 0,  Cabeça 0
ret

;******************************************************************************************************************************
;*
;*      |
;*      |
;*    \ | /
;*     \|/
;*      v

INT19h_HANDLER:						; Testar cada unidade
									; se arrancável e passar
									; o controlo para 7C00h

	cli
	mov bp, OFFSET INT19_STR_WELCOME
	call tty_str
		

	INT19h_HANDLER_BEGIN:
	; preparar os dados para INT13h, 
	; (gravar no segmento de arranque DISK_BOOT_SEG 
	;  o primeiro sector de cada disco)

	INT19h_HANDLER_TEST_FDD0:		; testar unidade A:
	 
		mov bp, OFFSET INT19_STR_FDD0
		call tty_crlf
		call tty_str
		mov byte ptr cs:[FLAG_BOOT], 1
		
		
		call INT19_SET_DISK_REGS
		mov dl, 0						; DL = 0,  unidade FDD0
		int 13h							; CHAMAR INT13h
		jc INT19h_HANDLER_TEST_FDD1

		call INT19h_TEST_AA55			; se NOT CARRY saltar para o fim
		jnc INT19h_PROCEED_TO_BOOT
	
	INT19h_HANDLER_TEST_FDD1:

		mov bp, OFFSET INT19_STR_FDD1
		call tty_crlf
		call tty_str
		mov byte ptr cs:[FLAG_BOOT], 2

		;
		call INT19_SET_DISK_REGS
		mov dl, 1						; DL = 1,  unidade FDD1
		int 13h							; CHAMAR INT13h	
		jc INT19h_HANDLER_TEST_HDD0
		call INT19h_TEST_AA55			; se NOT CARRY saltar para o fim
		jnc INT19h_PROCEED_TO_BOOT
		
	INT19h_HANDLER_TEST_HDD0:
	
		mov bp, OFFSET INT19_STR_HDD
		call tty_crlf
		call tty_str
		mov byte ptr cs:[FLAG_BOOT], 3

		;
		call INT19_SET_DISK_REGS
		mov dl, 80h						; DL = 0x80,  unidade HDD
		int 13h							; CHAMAR INT13h
		jc INT19h_HANDLER_FAILURE
		call INT19h_TEST_AA55			; se NOT CARRY saltar para o fim
		jnc INT19h_PROCEED_TO_BOOT

INT19h_HANDLER_FAILURE:
		call tty_crlf
		mov bp, OFFSET INT19_STR_NOBOOT
		call tty_str

		mov cl, 3
		INT19h_HANDLER_FAILURE_LOOP:
			mov al, '.'
			call tty_char
			call longwait
			call longwait
			dec cl
			jnz INT19h_HANDLER_FAILURE_LOOP
			
			jmp INT19h_HANDLER_BEGIN


INT19h_PROCEED_TO_BOOT:
		mov bp, OFFSET INT19_STR_BOOT
		call tty_str
		cli
		xor ax, ax
		mov ss, ax
		mov sp, DISK_BOOT_SEG
		xor ax, ax
		sahf
		sti
		db 0EAh					; jump far
		dw DISK_BOOT_OFFSET
		dw 0

		

	INT19_STR_WELCOME db 10,13,"[INT19]",0 
	INT19_STR_FDD0    db "A:?",0 
	INT19_STR_FDD1    db "B:?",0 
	INT19_STR_HDD     db "C:?",0 
	INT19_STR_CROSS   db " x",0
	INT19_STR_OK	   db " ok",0 
	INT19_STR_BOOT    db 10,13,"Booting...",0 
	INT19_STR_NOBOOT  db 10,13,"No bootable medium, retrying in a moment",0 

	
	
INSTALL_SPECIAL_INT19h:

	push 0
	pop es

	mov word ptr dx, es:[19h*4]
	mov word ptr cs:[INT19h_ORIGINAL_IP], dx
	mov word ptr dx, es:[19h*4+2]
	mov word ptr cs:[INT19h_ORIGINAL_IP+2], dx

	
	mov word ptr es:[19h*4], OFFSET INT19h_HANDLER
	mov word ptr es:[19h*4+2], 0C800h

ret