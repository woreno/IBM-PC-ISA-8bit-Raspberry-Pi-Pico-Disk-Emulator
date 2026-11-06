DISK_ROM_BLOCKS		EQU  3						; numero de blocos da ROM		
DISK_ROM_SIZE			EQU  (3 * 512)				; tamanho da ROM				
DISK_BUFFER_SEG		EQU  0C800h + (3 * 32)		; C800 + tamanho da ROM			
DISK_BUFFER_OFFSET		EQU  (3 * 512)				; C800 + tamanho da ROM			
INT13h_JUMP_OPCODE		EQU  (DISK_BUFFER_OFFSET+512)					; offset para código com salto FAR para a INT13h de fabrica
FLAGS_OFFSETS			EQU  (DISK_BUFFER_OFFSET+512)					; offset para os registos e flags de controlo 
FLAG_FDPT_OFFSET		EQU  (FLAGS_OFFSETS+(36+(3*20)))				; offset para tabela do disco rigido
