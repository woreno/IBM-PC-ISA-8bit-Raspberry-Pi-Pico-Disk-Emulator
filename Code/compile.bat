echo ON
call "C:\Program Files\Microsoft Visual Studio\18\Community\Common7\Tools\VsDevCmd.bat"
setlocal EnableDelayedExpansion
setx /M PATH "%PATH%;C:\Development\toolchains\gcc-arm\bin";



@rem **********************************************************************
@rem ** CONSTANTS
@rem **********************************************************************

@rem number of 512-blocks and size in bytes of the ASM-compiled code
set DISK_ROM_SIZE_BLOCKS=3
set DISK_ROM_SIZE=1536 

@rem ROM size plus 512-byte buffer and shared-variables area
set DISK_ROM_RESIZED=2200

@rem **********************************************************************
@rem ** PATHS
@rem **********************************************************************

@rem Paths: Development tools (bmp2other, stamp, etc)
	set     DEV_TOOLS_PATH=C:\Development\tools

@rem Paths: Raspberry Pi Pico util headers (screen, sdcard, etc)
	set       MCU_INC_PATH=C:\Development\velociraptor\include\mcu 

@rem Paths: Raspberry Pi Pico
	set      PICO_SDK_PATH=C:\Development\toolchains\pico-sdk
	set        SOURCE_PATH=E:\Hardware\operacaoPPC640-emu\code
	set        TARGET_PATH=C:\Development\toolchains\pico-sdk\pico-examples\project
	set     TARGET_USB_DRV=F:\
 
@rem Paths: DOSBOX 
	set    TARGET_ASM_PATH=C:\development\dosbox\asm
	set        DOSBOX_PATH="C:\Program Files (x86)\DOSBox-0.74-3"



:first_part

@echo **************************************************************************
@echo **************************************************************************
@echo **************************************************************************
@echo **************************************************************************
@echo **************************************************************************



@echo *
@echo **********************************************************
@echo   1.0) SETTING CONSTANTS IN DISKBLKS.INC 
@echo **********************************************************
@echo *

del ASM\DISKBLKS.INC
echo DISK_ROM_BLOCKS		EQU  %DISK_ROM_SIZE_BLOCKS%						; numero de blocos da ROM		> ASM\DISKBLKS.INC
echo DISK_ROM_SIZE			EQU  (%DISK_ROM_SIZE_BLOCKS% * 512)				; tamanho da ROM				>> ASM\DISKBLKS.INC
echo DISK_BUFFER_SEG		EQU  0C800h + (%DISK_ROM_SIZE_BLOCKS% * 32)		; C800 + tamanho da ROM			>> ASM\DISKBLKS.INC
echo DISK_BUFFER_OFFSET		EQU  (%DISK_ROM_SIZE_BLOCKS% * 512)				; C800 + tamanho da ROM			>> ASM\DISKBLKS.INC
echo INT13h_JUMP_OPCODE		EQU  (DISK_BUFFER_OFFSET+512)					; offset para código com salto FAR para a INT13h de fabrica>> ASM\DISKBLKS.INC
echo FLAGS_OFFSETS			EQU  (DISK_BUFFER_OFFSET+512)					; offset para os registos e flags de controlo >> ASM\DISKBLKS.INC
echo FLAG_FDPT_OFFSET		EQU  (FLAGS_OFFSETS+(36+(3*20)))				; offset para tabela do disco rigido>> ASM\DISKBLKS.INC

@echo *
@echo **********************************************************
@echo   1.1) COPY ASM FILES TO  %TARGET_ASM_PATH%
@echo **********************************************************
@echo *

del  %TARGET_ASM_PATH%\*.exe
del  %TARGET_ASM_PATH%\*.asm
del  %TARGET_ASM_PATH%\*.inc
copy ASM\*.asm %TARGET_ASM_PATH%
copy ASM\*.inc %TARGET_ASM_PATH%


@echo *
@echo **********************************************************
@echo   1.2) ASM COMPILING IN DOSBOX
@echo **********************************************************
@echo *
%DOSBOX_PATH%\dosbox -conf dosbox.config -noconsole

@echo *
@echo **********************************************************
@echo   1.3) ASM COMPILE RESULTS FROM %TARGET_ASM_PATH%
@echo **********************************************************
@echo *
type %TARGET_ASM_PATH%\EMU_ERR.TXT

%DEV_TOOLS_PATH%\stamp search  %TARGET_ASM_PATH%\EMU_ERR.TXT -str="**Error**"
IF %ERRORLEVEL% EQU -1 GOTO compile_resume

	:compile_err
	@echo *
	@echo **********************************************************
	@echo    ASM COMPILE ERRORS!!
	@echo **********************************************************
	@echo *
	exit
	
%DEV_TOOLS_PATH%\stamp search  %TARGET_ASM_PATH%\EMU_ERR.TXT -str="**Fatal**"
IF %ERRORLEVEL% NEQ -1 GOTO compile_err
	
:compile_resume
%DEV_TOOLS_PATH%\stamp search  %TARGET_ASM_PATH%\EMU_ERR.TXT -str="encountered"
IF %ERRORLEVEL% NEQ -1 GOTO compile_err


@echo *
@echo **********************************************************
@echo   1.4) STRIPPING ROM IMAGE DOS-HEADER
@echo **********************************************************
@echo *

CD %DEV_TOOLS_PATH%\
del disk.bin
%DEV_TOOLS_PATH%\stamp copy %TARGET_ASM_PATH%\disk.exe disk.bin -s=512

@echo *
@echo **********************************************************
@echo   1.5) STAMPING CHECKSUM ON ROM IMAGE
@echo **********************************************************
@echo *

%DEV_TOOLS_PATH%\stamp search   disk.bin -str="checksum:" -post
IF %ERRORLEVEL% NEQ -1 GOTO stamp_checksum_resume
 
	@echo *
	@echo **********************************************************
	@echo   CHECKSUM FIELD NOT FOUND!!!
	@echo **********************************************************
	exit

:stamp_checksum_resume

	set /a  ROM_CHECKSUM_POS = %ERRORLEVEL%
	
@echo *
@echo **********************************************************
@echo   1.6) CHECKSUM OFFSET: %ROM_CHECKSUM_POS%
@echo **********************************************************
@echo *

%DEV_TOOLS_PATH%\stamp sum   disk.bin -d=%ROM_CHECKSUM_POS% -tagsz=1
%DEV_TOOLS_PATH%\stamp asksize   disk.bin 

set /a  ROM_SIZE = %ERRORLEVEL%

if %ROM_SIZE% LEQ 1536  GOTO stamp_resize_resume
 
	@echo *
	@echo **********************************************************
	@echo   ROM IMAGE GREATER >= 3*512 !!!!
	@echo **********************************************************
	@echo *
	exit

:stamp_resize_resume 

@echo *
@echo **********************************************************
@echo   ROM IMAGE IS %ERRORLEVEL% BYTES
@echo **********************************************************
@echo *


@echo *
@echo **********************************************************
@echo   1.7) RESIZING ROM IMAGE TO %DISK_ROM_RESIZED% BYTES
@echo **********************************************************
@echo *

del diskresized.bin 
%DEV_TOOLS_PATH%\stamp copy disk.bin diskresized.bin   -s=0 -d=0 -init=%DISK_ROM_RESIZED%
 
@echo *
@echo **********************************************************
@echo   1.8) DISKRESIZED.BIN TO HEXADECIMAL > DISK_ARRAY.H
@echo **********************************************************

del  %SOURCE_PATH%\disk_array.h
%DEV_TOOLS_PATH%\stamp chex diskresized.bin %SOURCE_PATH%\disk_array.h -title=" W8 DISK_ROM[] VL_ALIGN(4)  " -tagsz=1
@rem VL_STORE_FLASH_GROUP(\"DISK_ROM\")

	@echo **********************************************************
	@echo   FLAGS OFFSETS: %ERRORLEVEL%
	@echo **********************************************************
	set /a  ROM_FLAGS_POS = %ERRORLEVEL%
	
@echo **********************************************************
@echo   1.10) SETTING FLAGS IN DISK_ARRAY.H
@echo **********************************************************

@echo // >> disk_array.h 
@echo // >> disk_array.h 
@echo #define DISK_ROM_SIZE				%DISK_ROM_SIZE%					>> disk_array.h 
@echo #define DISK_ROM_TOTAL_SIZE		%DISK_ROM_RESIZED%				// total da ROM incluindo o BUFFER de disco e flags	>> disk_array.h 
@echo W8* DISK_BUFFER					=(DISK_ROM+%DISK_ROM_SIZE%);	>> disk_array.h 
@echo W8* DISK_FLAGS					=(DISK_BUFFER+512);				>> disk_array.h 



:second_part

@echo ******************************************************************************************
@echo ******************************************************************************************
@echo ******************************************************************************************
@echo ******************************************************************************************
@echo ******************************************************************************************
@echo ******************************************************************************************
@echo ******************************************************************************************
@echo ******************************************************************************************

@echo *
@echo ************************************************
@echo  2.1) GENERATING ICONS
@echo ************************************************
@echo *

 cd %SOURCE_PATH%
 %DEV_TOOLS_PATH%\bmp2other chex icons.bmp uiIconsData.hpp -a=4 -l  -n=iconData -N="const W8 iconData[] VL_STORE_IN_FLASH VL_ALIGN(4) = "  
  

@echo ************************************************
@echo .
@echo ************************************************
@echo  2.2) COPYING TO RASPBERRY PI PICO FOLDER
@echo ************************************************

	del %TARGET_PATH%\*.* /F /Q
	rem del %TARGET_PATH%\build\*.* /F /Q
	mkdir %TARGET_PATH%
	mkdir %TARGET_PATH%\rasp_pico
	
	 
	cd %SOURCE_PATH%
	copy %SOURCE_PATH%\*.* %TARGET_PATH%\						  > nul
	copy %SOURCE_PATH%\PIO\*.* %TARGET_PATH%\					  > nul
	copy %MCU_INC_PATH%\*.* %TARGET_PATH%\						  > nul
	copy %MCU_INC_PATH%\rasp_pico\*.* %TARGET_PATH%\rasp_pico\*.* > nul 

	
@echo ************************************************
@echo  2.3) ENTERING RASPBERRY PI PICO FOLDER
@echo ************************************************
@echo *
 
	cd %TARGET_PATH%

@echo *
@echo ************************************************
@echo ************************************************
@echo  2.4) COMPILING RASPBERRY PI PICO    
@echo ************************************************
@echo ************************************************
@echo *
echo %UCRTVersion%
echo %WindowsSDkDir%


		cmake -G "NMake Makefiles" . 
		nmake
		IF %ERRORLEVEL% NEQ 0 GOTO process_error1
				

@echo *
@echo ************************************************
@echo  2.5) COPYING uf2 TO RASPBERRY PI PICO DRIVE
@echo       DISK.ASM:%TARGET_ASM_BIN_SIZE% bytes
@echo ************************************************
@echo *
cd %TARGET_PATH%

@echo Raspberry pi pico
@echo Atencao RAM interna: 264KB / 2MB flash
dir  PROJECT.uf2 
copy PROJECT.uf2 %TARGET_USB_DRV%
IF %ERRORLEVEL% NEQ 0 GOTO process_error2 

C:\Development\toolchains\gcc-arm\bin\arm-none-eabi-size PROJECT.elf

@echo *
@echo *****************************************************
@echo *****    OK    DISK.BIN:
@echo *****                  %ROM_SIZE% bytes
@echo *****                  (%DISK_ROM_SIZE_BLOCKS% blocks)
@echo *****     flag offset: %ROM_FLAGS_POS%
@echo *****   flag checksum: %ROM_CHECKSUM_POS%
@echo *****************************************************
@echo *
exit

 

:process_error1
@echo ******************************************
@echo ******* COMPILE ERROR   ******************
@echo ******************************************
exit

:process_error2
@echo *******************************************
@echo ******* A PLACA NAO ESTA MONTADA! **********
@echo ********************************************
@echo * OU JA' NAO E A UNIDADE %TARGET_USB_DRV%? *
@echo *                                          *
@echo * OU ESTA DESLIGADA DO USB?                *
@echo *                                          *
@echo * MANTER O BOTAO DE PROGRAMACAO PREMIDO    *
@echo * E TOCAR RAPIDAMENTE NO BOTAO DE RESET    *
@echo ********************************************

@echo *******************************************
@echo ******* RASPBERRY PI PICO NOT MOUNTED ******
@echo ********************************************
@echo * ISNT AT DRIVE  %TARGET_USB_DRV%?         *
@echo *                                          *
@echo * IS CONNECTED TO USB?                     *
@echo *                                          *
@echo * KEEP PRESSING PROGRAMMING BUTTON WHILE   *
@echo * TOUCHING RESET ONCE                      *
@echo ********************************************
exit


