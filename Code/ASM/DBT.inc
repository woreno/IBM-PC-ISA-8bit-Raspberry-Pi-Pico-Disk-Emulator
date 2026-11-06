M_printReg MACRO REG_, REG_STR

	mov al, DBT_&REG_
	call tty_crlf
	call tty_toHex_byte
	call tty_space

	mov al, es:[di + DBT_&REG_]
	call tty_toHex_byte

ENDM

M_printReg2 MACRO REG_
	mov al, DBT_&REG_
	call tty_crlf
	call tty_toHex_byte
	call tty_space

	mov ax, es:[di + DBT_&REG_]
	call tty_toHex_word

ENDM

DBT_SPEC1		  EQU 0 ; nibble alto: taxa do step; nibble baixo: tempo desmontar a cabeca
DBT_SPEC2		  EQU 1 ; bit 1=DMA ativo, restante tempo montar cabeca
DBT_WAITMOTOR	  EQU 2 ; ticks a esperar antes de parar o motor
DBT_BYTESPERSECT  EQU 3 ; bytes/setor  0=128 1=256 2=512 3=1024
DBT_SECTPERCIL    EQU 4 ; setores/cilindro
DBT_GAPLENGTH     EQU 5 ; bytes entre setores
DBT_DATALENGTH    EQU 6 ; tamanho do setor (se dif. do anterior)
DBT_FGAPLENGTH    EQU 7 ; tam. byte entre setores formatados
DBT_FILLBYTE      EQU 8 ; para setores formatados
DBT_HEADSETTLE    EQU 9 ; em ms. tempo de estabilizacao da cabeca
DBT_MOTORSTART    EQU 10 ; em s. tempo de estabilizacao do motor ao arrancar
DBT_CILS		  EQU (11+0)
DBT_HEADS         EQU (11+2)
DBT_RWC_CIL       EQU (11+3) ; em que pista começa a redução de currente para escrita
DBT_WPRC_CIL      EQU (11+5) ; em que pista começa a precompensação de escrita
DBT_ECC_MAXBURST  EQU (11+7) ; em que pista começa a precompensação
DBT_CTRLBYTE      EQU (11+8)
	; bit 7: desligar tentativas de acesso
	; bit 6: desligar ECC
	; bit 5: sempre a zero
	; bit 3: opção da drive

	
	mov ax, 0800h
	int 13h

	call tty_crlf
	mov ax, es
	call tty_toHex_word
	mov al, ':'
	mov ax, di
	call tty_toHex_word
	call tty_crlf

	M_printReg  SPEC1
	M_printReg  SPEC2
	M_printReg  WAITMOTOR
	M_printReg  BYTESPERSECT
	M_printReg  SECTPERCIL
	M_printReg  GAPLENGTH
	M_printReg  DATALENGTH
	M_printReg  FGAPLENGTH
	M_printReg  FILLBYTE
	M_printReg  HEADSETTLE
	M_printReg  MOTORSTART
	M_printReg  CILS
	M_printReg  HEADS
	M_printReg2 RWC_CIL
	M_printReg2 WPRC_CIL
	M_printReg  ECC_MAXBURST
	M_printReg  CTRLBYTE

	call forever
