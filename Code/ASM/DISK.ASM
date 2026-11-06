.8086
.model tiny
include			MACROS.INC	
include			DISKBLKS.inc
DISK_SEG		EQU 0C800h

;*****************************************************
; ZONA de VARIAVEIS PARTILHADAS COM O RASPBERRY (em C)
	
		;INT13h_JUMP_CODE			EQU FLAGS_OFFSETS
	; 2 bytes cada:
		INT13h_ORIGINAL_IP			EQU	FLAGS_OFFSETS+1
		INT13h_ORIGINAL_SEG			EQU	FLAGS_OFFSETS+3
		INT19h_ORIGINAL_IP			EQU	FLAGS_OFFSETS+5
		INT19h_ORIGINAL_SEG			EQU	FLAGS_OFFSETS+7
	; 1 bytes cada:
		FLAG_CARRY					EQU	FLAGS_OFFSETS+9
	; 2 bytes cada:
		FLAG_AX						EQU FLAGS_OFFSETS+10
		FLAG_BX						EQU FLAGS_OFFSETS+12
		FLAG_CX						EQU FLAGS_OFFSETS+14
		FLAG_DX						EQU FLAGS_OFFSETS+16
		FLAG_ES						EQU FLAGS_OFFSETS+18
		FLAG_DS						EQU FLAGS_OFFSETS+20
		FLAG_SI						EQU FLAGS_OFFSETS+22
		FLAG_DI						EQU FLAGS_OFFSETS+24
		FLAG_BP						EQU FLAGS_OFFSETS+26
	; 1 byte cada:
		FLAG_START_OPERATION		EQU FLAGS_OFFSETS+28
		FLAG_CMD					EQU FLAGS_OFFSETS+29
		FLAG_CMDRES					EQU FLAGS_OFFSETS+30
		FLAG_BOOT					EQU FLAGS_OFFSETS+31
		FLAG_DRVA_IS_PHYSICAL		EQU FLAGS_OFFSETS+32
		FLAG_DRVB_IS_PHYSICAL		EQU FLAGS_OFFSETS+33
		FLAG_DRVC_EXISTS			EQU FLAGS_OFFSETS+34
		FLAG_DRVC_USE				EQU FLAGS_OFFSETS+35


;*****************************************************
; INICIO DO CÓDIGO
org 0
code SEGMENT PUBLIC USE16 '_TEXT'
ASSUME cs:code, ds:code, es:code

									; PRIMEIROS 3 BYTES:
		dw 0AA55h					; IDENTIFICADOR 0xAA55
		db DISK_ROM_BLOCKS			; TAMANHO EM BLOCOS DE 512B 

START:

CODE_START:
	M_pushall

		mov bp, OFFSET PROGRAM_TITLE	; IMPRIMIR TITULO DO PROGRAMA
		call tty_str 
		
		call INSTALL_INT40h				; INSTALAR TRATADOR DE INTERRUPÇÕES
		call INSTALL_SPECIAL_INT13h
		call INSTALL_SPECIAL_INT19h
		
	M_popall
	retf								; SAIR
	
include INT13h.INC
include INT19h.INC
include UTIL.INC

INSTALL_INT40h:
	push ds
	push 0
	pop ds
	mov word ptr ds:[41h*4],   FLAG_FDPT_OFFSET
	mov word ptr ds:[41h*4+2], 0C800h
	pop ds
ret

;*****************************************************
CHECKSUM:
	db "checksum:"
	db 0
PROGRAM_TITLE:
	db "Disk-emulator",10,13,0


ORG FLAGS_OFFSETS
INT13_FACTORY_JUMP:

code ends
end Start
END 