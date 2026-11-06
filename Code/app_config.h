// DEBUG DE PINOS --------------------------------------------


//#define FS_USES_EXTERNAL_BUFFER		mcuSharedBuffer
#define FS_FSNODE_HAS_PRINT

#define DEBUG_USB(STR_,...) 
#define mcu_log(STR_,...) 	

#define APP_DEBUG
#define DEBUG(X,...) printf(X, __VA_ARGS__);

// Definiçoes ------------------------------------------------

#define APP_START_DELAY			500 // tempo para poder abrir o putty
#define DELAY_SHORT_			asm volatile("nop \n nop \n nop \n nop \n nop \n nop \n nop \n nop \n nop");
#define DELAY_SHORT				DELAY_SHORT_ DELAY_SHORT_ DELAY_SHORT_ DELAY_SHORT_ DELAY_SHORT_  
 
////////////////////////////////////////////////////////////////////////////////
// ADDRESS BUS
////////////////////////////////////////////////////////////////////////////////

	#define PIN_MEM_WRITE		IO_PIN_5    // pino 7
	#define PIN_MEM_READ		IO_PIN_6	// pino 9

	#define PIN_ADDR_MUX		IO_PIN_22	//ativo a LOW
	#define PIN_ENABLE_DB_OUT	IO_PIN_15	//ativo a HI

	#define PIN_A0				IO_PIN_16
	#define PIN_A1				IO_PIN_17
	#define PIN_A2				IO_PIN_18
	#define PIN_A3				IO_PIN_19
	#define PIN_A4				IO_PIN_20
	#define PIN_A5				IO_PIN_21

	#define PIN_A6				IO_PIN_16
	#define PIN_A7				IO_PIN_17
	#define PIN_A8				IO_PIN_18
	#define PIN_A9				IO_PIN_19
	#define PIN_A10				IO_PIN_20
	#define PIN_A11				IO_PIN_21

	// *5
			

////////////////////////////////////////////////////////////////////////////////
// DATABUS
////////////////////////////////////////////////////////////////////////////////

	#define PIN_D0			IO_PIN_7
	#define PIN_D1			IO_PIN_8
	#define PIN_D2			IO_PIN_9
	#define PIN_D3			IO_PIN_10
	#define PIN_D4			IO_PIN_11
	#define PIN_D5			IO_PIN_12
	#define PIN_D6			IO_PIN_13
	#define PIN_D7			IO_PIN_14

#define DB_PINS_DEF(X_)\
	X_(PIN_D0,			 "p0")\
	X_(PIN_D1,			 "p1")\
	X_(PIN_D2,			 "p2")\
	X_(PIN_D3,			 "p3")\
	X_(PIN_D4,			 "p4")\
	X_(PIN_D5,			 "p5")\
	X_(PIN_D6,			 "p6")\
	X_(PIN_D7,			 "p7")

	//    ... .... . <- inicio databus
	// 6 5432 1098 7654 3210	posicao
	// 0 0111 1111 1000 0000	binario
	//     7    F   8	0		hexadecimal

	#define DATABUS_PIN_MASK		0x7F80
 
	#define DATABUS_OE_ON			PIN_WRITE(PIN_ENABLE_DB_OUT, 1);
	#define DATABUS_OE_OFF			PIN_WRITE(PIN_ENABLE_DB_OUT, 0);

////////////////////////////////////////////////////////////////////////////////
// JOYPAD
////////////////////////////////////////////////////////////////////////////////

	#define PIN_MEM_WAIT			IO_PIN_ADC1
	#define PIN_SMALL_JOYSTICK_Y	IO_PIN_ADC0
	#define PIN_SMALL_JOYSTICK_X	IO_PIN_ADC2

////////////////////////////////////////////////////////////////////////////////
// AUDIO
////////////////////////////////////////////////////////////////////////////////

//	#define AUDIOPLAYER_PIN_GENERIC_BUTTON		PIN_BUTTON_RIGHT
//	#define PIN_BUZZER							IO_PIN_1
//	#define PIN_MIC_IN_LEFT						IO_PIN_ADC2
//	#define PIN_MIC_IN_RIGHT					IO_PIN_ADC1 
//	#define PIN_ULTRASPEAKER					IO_PIN_ADC0


////////////////////////////////////////////////////////////////////////////////
// DISCO SD
////////////////////////////////////////////////////////////////////////////////
	
	#define APP_USES_SD
	#define SD_USES_FAST_CLOCK
	#define SD_ENABLE_DATA_CRC		0
	#define PIN_SD_CS				IO_PIN_0
	#define PIN_SD_OUT				IO_PIN_1
	#define PIN_SD_CLK				IO_PIN_2
	#define PIN_SD_IN				IO_PIN_3 //IO_PIN_5
	#define PIN_DISP_ENABLE			IO_PIN_4

	#include "sd.h"

// no adaptador...
	#define SD_PINS_DEF(X_)\
		X_(PIN_SD_CS,				"p0")\
		X_(PIN_SD_OUT,				"p1")\
		X_(PIN_SD_CLK,				"p2")

////////////////////////////////////////////////////////////////////////////////
// ECRÃ
////////////////////////////////////////////////////////////////////////////////

	#define PIN_DISP_CLK			IO_PIN_0
	#define PIN_DISP_OUT			IO_PIN_1
	#define PIN_DISP_DC				IO_PIN_2
	#define PIN_DISP_CS				IO_PIN_3
	//#define PIN_DISP_RES			IO_PIN_13
	//#define PIN_DISP_BRIGHT		IO_PIN_ADC2

	#define APP_USES_ICONS
	#define DRAW_USES_BUFFER
	#include "st7735.h"
	#include "uiIcons.h"
	#include "draw.h"

#define DISP_PINS_DEF(X_)\
	X_(PIN_DISP_CLK,			 "p0")\
	X_(PIN_DISP_OUT,			 "p1")\
	X_(PIN_DISP_DC,				 "p2")\
	X_(PIN_DISP_CS,				 "p3")


////////////////////////////////////////////////////////////////////////////////
// FS 
////////////////////////////////////////////////////////////////////////////////

	#define FS_FAT_USE_CACHE_WITH_SIZE	512
	#define DEV_RD_BLOCK				sd_rd_block
	#define DEV_WR_BLOCK				sd_wr_block
	#include "fs.h"

////////////////////////////////////////////////////////////////////////////////
// BUZZER 
////////////////////////////////////////////////////////////////////////////////

	#define PIN_BUZZER 99
	#include "sound.h"

////////////////////////////////////////////////////////////////////////////////
// UI 
//////////////////////////////////////////////////////////////////////////////// 
	#define UI_CACHEFILES_MAXSIZE	12		

	#define UI_ANIMATE_SELECTION    0
	#define UI_ANIMATE_DIR          0//40
	#define UI_ANIMATE_DIR_BUFF		1		// se 1 usa um buffer para animacao (+20K)
	#define UI_MENU_TEXT_RBORDER_DX 4
	#define UI_MENU_OPTION_DY		20
	#define UI_MENU_TITLE_DY		20
	#define UI_MENU_TITLE_PENX		2
	#define UI_MENU_TITLE_PENY		(fontBlockY-1)
	#define UI_MENU_TEXT_PENX		22
	#define UI_MENU_TEXT_PENY		(fontBlockY-1)
	#define UI_MENU_ICON_PENX		3
	#define UI_MENU_ICON_PENY		2

	W0 ui_uninstall_buttons(){}
	#include "uiHeads.h"
	 

#if (defined(DEBUG_PINS_SD) || defined(DEBUG_PINS_DISP) || defined(DEBUG_PINS_AUDIO) || defined(DEBUG_PINS_PERIPHERAL))
	#define   DEBUG_PINS
#endif

 



W0  init_pins()
{
	
	PIN_INIT(PIN_MEM_WAIT)
	PIN_MODE(PIN_MEM_WAIT, PIN_MODE_OUTPUT)
	PIN_WRITE(PIN_MEM_WAIT, 0);

	// NÃO CONDUZIR O DATABUS ALTA IMPEDANCIA
	// o DATABUS está direto ao CPU com um conversor de nivel
	PIN_INIT(PIN_ENABLE_DB_OUT)
	PIN_MODE(PIN_ENABLE_DB_OUT, PIN_MODE_OUTPUT)
	DATABUS_OE_OFF			// OE = 0 ALTA IMPEDANCIA
	
	// CS
	DATABUS_OE_ON			// OE = 1

	PIN_INIT(PIN_LED)
	PIN_MODE(PIN_LED,			PIN_MODE_OUTPUT)
	
	PIN_INIT(PIN_DISP_ENABLE)
	PIN_MODE(PIN_DISP_ENABLE,		PIN_MODE_OUTPUT)
	
	PIN_INIT(PIN_DISP_ENABLE)
	PIN_MODE(PIN_DISP_ENABLE,		PIN_MODE_OUTPUT)
	
	PIN_INIT(PIN_SMALL_JOYSTICK_Y)
	PIN_INIT(PIN_SMALL_JOYSTICK_X)
    adc_gpio_init(PIN_SMALL_JOYSTICK_X);
    adc_gpio_init(PIN_SMALL_JOYSTICK_Y);
	adc_init();
	
	PIN_MODE(PIN_SMALL_JOYSTICK_X,   PIN_MODE_INPUT)
	PIN_MODE(PIN_SMALL_JOYSTICK_Y,   PIN_MODE_INPUT)
} 
W0 turnSD()
{
	if (dispMux == DISPSD_MUX_SD_IS_ON) return;
	dispMux = DISPSD_MUX_SD_IS_ON;
	PIN_MODE(PIN_SD_IN, PIN_MODE_INPUT);
	PIN_WRITE(PIN_DISP_ENABLE,  0); 
	DELAY_MS(2);
	sd_init();
	DELAY_MS(2);
}
W0 turnDisplay()
{
	if (dispMux== DISPSD_MUX_DISP_IS_ON) return;
	dispMux = DISPSD_MUX_DISP_IS_ON;
	PIN_MODE(PIN_DISP_CS, PIN_MODE_OUTPUT);
	PIN_WRITE(PIN_DISP_ENABLE,  1); DELAY_MS(2);
}


//#define APP_DEBUG_MEMORY_ACCESS
volatile W32 trapNumberFRD=0;
volatile W32 trapNumberFWR=0;
volatile W32 trapNumberR=0;
volatile W32 trapNumberW=0;
volatile W32 trapNumberBRD=0;
volatile W32 trapNumberBWR=0;
volatile W32 forbiddenWrites=0;
//volatile W32 forbiddenWritesAddr[128];
#ifdef APP_DEBUG_MEMORY_ACCESS
	W32 trapsAddressesR[512];
	W32 trapsAddressesW[512];
#endif
