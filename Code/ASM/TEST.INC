
INT13h_HANDLER:
INT19h_HANDLER:
	mov bp, OFFSET INT19_STR_WELCOME
	mov cl, 'A'
	call tty_str
 

	mov bp, OFFSET PROGRAM_TITLE
	call tty_str
	call FOREVER
	
	INT19_STR_WELCOME db "INT19!",0 