
tty_buffer:
	push ax
	push bx
	push cx
	push dx
	mov ah, 0Eh
	mov bh, 0	
	mov dx, 6

	tty_buffer_loop_rows:
		
		mov cl, 16
		call tty_crlf

		push ax
			mov ax, di
			call tty_toHex_word
			mov al, ':'
			call tty_char
		pop ax
		
		call tty_space

		tty_buffer_loop_cols:
			mov al, es:[di]
			call tty_toHex_byte
			inc di
			call tty_space
			dec cl
			jnz tty_buffer_loop_cols
			
		mov cl, 16
		sub di, 16
		call tty_space

		tty_buffer_loop_text:
			mov al, es:[di]
			cmp al, 32
			jl tty_buffer_loop_text_skip
			int 10h
			jmp tty_buffer_loop_text_end
			tty_buffer_loop_text_skip:
			mov al, '_'
			int 10h
			tty_buffer_loop_text_end:
			inc di
			dec cl
			jnz tty_buffer_loop_text

		;cmp dx, 16
		;jnz tty_buffer_skip
		;	call shortwait
		
		tty_buffer_skip:

		dec dx
		jnz tty_buffer_loop_rows

	pop dx
	pop cx
	pop bx
	pop ax
ret