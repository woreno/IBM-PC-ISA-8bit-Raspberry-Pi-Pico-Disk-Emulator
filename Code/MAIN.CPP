
#define DISP_CLK_DELAY1    // __asm volatile ("nop\n"); // DELAY_IDLE(37)
#define DISP_CLK_DELAY2		//__asm volatile ("nop\n"); //DELAY_IDLE(7) // obrigatório para NFP096H-01AF

#define DEBUG_PINS

#define ST7735_PARTNUMBER_IS				ST7735_NFP096H_01AY
#define APP_USE_USB_PERIPHERALS				0
 
#include "mcu.h"
#define FATAL

#define APP_TARGET							APP_TARGET_RASPBERRY_PICO
#include "mcu_util.h"
#include "pico/stdlib.h"
//#include "pico/stdio.h"
#include "pico/multicore.h"
#include "hardware/pio.h"
#include <cmath>
#include <string>

//#define APP_DEBUG_MEMORY_ACCESS

W32 idleTimerHi = 0;
W32 idleTimer = 0;

enum DISPSD_MUX { DISPSD_MUX_DISP_IS_START, DISPSD_MUX_DISP_IS_ON, DISPSD_MUX_SD_IS_ON }; 
DISPSD_MUX dispMux = DISPSD_MUX_DISP_IS_START;
W0 turnSD();
W0 turnDisplay();
W0 fatal(W8 section_, W16 err_);
	
#include "app_strings.h"
#include "app_config.h"
#include "memr_pio.pio.h"
#include "memw_pio.pio.h"
#include "master_pio.pio.h" 
#include "disk_array.h"  

W8 ui_drives_last_operation = -1;
W8 ui_drives_first_time = 1;
W8 ui_drives_last_used = -1;

W0 ui_set_drive_operation_icons(W8 driveId_, W32 function_);
W0 ui_unset_drive_operation_icons();

#include "int13h_handler.h"


W32 startTimer = 0;
FSNode rootNode;
#include "ui.h"
#include "app_core_0.h" 
	
void fatal(W8 section_, W16 err_)
{ 
	SW8 str[32];
	turnDisplay(); 
	draw_clear(Color_Red);
	
	draw_text_centered(-1, 35, "FATAL", 0xFFFF);
	sprintf(str, "%s %02X", SECTIONS_STRINGS[section_], err_); 
	draw_text_centered(-1, 60, str, 0xFFFF);

	DRAW_UPDATE
	printf("fatal: %s %i", SECTIONS_STRINGS[section_],  err_);
	while(1){}
}


SW32 main()
{ 	
	mcu_init(0);			// inicializar PI PICO / init pi pico
	init_pins();			// inicializar pinos / init pins
		
	
	///////////////////////////////////////////////////////////////////////
	// Lançar tratador de MEMR/MEMW / Launch MEMR/MEMW handlers
	///////////////////////////////////////////////////////////////////////

	multicore_reset_core1();
	multicore_launch_core1(&app_core_0);

	PIN_WRITE(PIN_LED, 1);
	printf("hi\n");
	
	turnDisplay(); 
	draw_init();  
	
	drives[0] = Drive(0,"A:");
	drives[1] = Drive(1,"B:");
	drives[2] = Drive(2,"C:");

	/*
	W8 drive=0;
	while(1)
	{
		ui_set_drive_operation_icons(drive,2);
		DELAY_MS(2000);
		ui_set_drive_operation_icons(drive,3);
		DELAY_MS(2000);
		drive++;
		if (drive==3) drive=0;
	}
	while(1){}
	*/
	
	///////////////////////////////////////////////////////////////////////
	// Inicializar SD e FS / Init SD and FS
	///////////////////////////////////////////////////////////////////////

	turnSD(); 
	
		W8 status;
		do 
		{ 
			ui_draw_sd_question(1);
			DELAY_MS(30);
		}
		while (RES_OK != sd_init());
		ui_draw_sd_question_mark = true;
		do
		{
			ui_draw_sd_question(0);
			DELAY_MS(30);
		}
		while (RES_OK != fs_init());
	
	ui_draw_wait();

	
	///////////////////////////////////////////////////////////////////////
	// Obter o rootNode da partição 0 / Get the rootNode at partition 0
	///////////////////////////////////////////////////////////////////////

	printf("fs ok\n");
	turnSD(); 
	if (fs_getRootDirNode(&rootNode, 0)==RES_FAIL)
	{
		printf("root node invalid!\n");
		fatal(FS,0);
	}
	printf("root node ok\n");
	
	
	///////////////////////////////////////////////////////////////////////
	// Configurar unidades (teste) / Set the drives (test)
	///////////////////////////////////////////////////////////////////////

	*DISK_FLAG_BOOT = 0;
	
	//drives[0].init("/AMS/DISK.IMA"); 
	//drives[0].init("/DOS5/DISK01.IMG"); 
	drives[0].init("/DOS622/DISK01.IMG"); 
	//drives[0].init("/DOS33/DISK.IMA"); 
	drives[1].initPhysical(); 
	drives[2].init("/HDD.IMA"); 
	if (drives[2].valid) 
	{
		*DISK_FLAG_DRVC_EXISTS=1;
		*DISK_FLAG_DRVC_USE=1;
	}

	
	///////////////////////////////////////////////////////////////////////
	// Criar interface gráfico / Create User Interface
	///////////////////////////////////////////////////////////////////////

		turnDisplay(); 
		ui_create_pages();
		ui_update_main_page();
		uiCurrPage = ui_main_page;

		uiCurrPage->draw();
		DRAW_UPDATE

	///////////////////////////////////////////////////////////////////////
	// Loop de tratamento da Int13h e gráfico 
	// Graphical/Joystick and Int13h handler Loop
	///////////////////////////////////////////////////////////////////////

	while(1)
	{
		int13h_handler();

		// opcional / optional
		ui_unset_drive_operation_icons();
		//

		adc_select_input(IO_PIN_ADC_ID(PIN_SMALL_JOYSTICK_X));
		const W16 x = adc_read();
		adc_select_input(IO_PIN_ADC_ID(PIN_SMALL_JOYSTICK_Y));
		const W16 y = adc_read();
		
		ui_menus_update(x,y);
	}
	

	

	return 0;
}
