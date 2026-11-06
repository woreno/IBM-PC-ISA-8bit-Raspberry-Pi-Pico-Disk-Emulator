//////////////////////////////////////////////////////////////////////////////////////////
// Variaveis partilhadas com o CPU 8086
//////////////////////////////////////////////////////////////////////////////////////////

#define DEBUG_INT13h
//#define DEBUG_INT13h_BUFFERS

namespace CPU8086_shared_flags {
	// a primeira FLAG em DISK_FLAGS é o opcode 0xEA :
	#define DISK_FLAG_JUMP_CODE				((W8*)(DISK_FLAGS))
	// 2 bytes cada (não escrever! não estão alinhadas):
	#define DISK_FLAG_INT13h_ORIGINAL_IP	((W16*)(DISK_FLAGS+1))
	#define DISK_FLAG_INT13h_ORIGINAL_SEG	((W16*)(DISK_FLAGS+3))
	#define DISK_FLAG_INT19h_ORIGINAL_IP	((W16*)(DISK_FLAGS+5))
	#define DISK_FLAG_INT19h_ORIGINAL_SEG	((W16*)(DISK_FLAGS+7))
	// 1 byte de alinhamento a 2bytes:
	#define DISK_FLAG_CARRY					(( W16*)(DISK_FLAGS+9)) 
	// 2 bytes cada:								
	#define DISK_FLAG_AX					(( W16*)(DISK_FLAGS+10))
	#define DISK_FLAG_BX					(( W16*)(DISK_FLAGS+12))
	#define DISK_FLAG_CX					(( W16*)(DISK_FLAGS+14))
	#define DISK_FLAG_DX					(( W16*)(DISK_FLAGS+16))
	#define DISK_FLAG_ES					(( W16*)(DISK_FLAGS+18))
	#define DISK_FLAG_DS					(( W16*)(DISK_FLAGS+20))
	#define DISK_FLAG_SI					(( W16*)(DISK_FLAGS+22))
	#define DISK_FLAG_DI					(( W16*)(DISK_FLAGS+24))
	#define DISK_FLAG_BP					(( W16*)(DISK_FLAGS+26))
	// 1 byte cada:										
	#define DISK_FLAG_START_OPERATION		(( W8*) (DISK_FLAGS+28))
	#define DISK_FLAG_CMD					(( W8*) (DISK_FLAGS+29))
	#define DISK_FLAG_CMDRES				(( W8*) (DISK_FLAGS+30))
	#define DISK_FLAG_BOOT					(( W8*) (DISK_FLAGS+31))
	#define DISK_FLAG_DRVA_IS_PHYSICAL		(( W8*) (DISK_FLAGS+32))
	#define DISK_FLAG_DRVB_IS_PHYSICAL		(( W8*) (DISK_FLAGS+33))
	#define DISK_FLAG_DRVC_EXISTS			(( W8*) (DISK_FLAGS+34))
	#define DISK_FLAG_DRVC_USE				(( W8*) (DISK_FLAGS+35))

	#define DISK_FLAG_DBT_OFFSET			36

	
	//#define DISK_FLAG_FDPT_OFFSET			(36+(3*20))
}
namespace CPU8086_regs_access {
	
	#define SET_AX(X_)	*DISK_FLAG_AX = X_;
	#define SET_BX(X_)	*DISK_FLAG_BX = X_;
	#define SET_CX(X_)	*DISK_FLAG_CX = X_;
	#define SET_DX(X_)	*DISK_FLAG_DX = X_;
	#define SET_ES(X_)	*DISK_FLAG_ES = X_;
	#define SET_DI(X_)	*DISK_FLAG_DI = X_;

	#define GET_AX()	(*DISK_FLAG_AX)
	#define GET_BX()	(*DISK_FLAG_BX)
	#define GET_CX()	(*DISK_FLAG_CX)
	#define GET_DX()	(*DISK_FLAG_DX)
	#define GET_ES()	(*DISK_FLAG_ES)
	#define GET_DI()	(*DISK_FLAG_DI)

	#define SET_AL(Y_)	*DISK_FLAG_AX = W16_SET_LOW(*DISK_FLAG_AX, (Y_));
	#define SET_AH(Y_)	*DISK_FLAG_AX =  W16_SET_HI(*DISK_FLAG_AX, (Y_));
	#define SET_BL(Y_)	*DISK_FLAG_BX = W16_SET_LOW(*DISK_FLAG_BX, (Y_));
	#define SET_BH(Y_)	*DISK_FLAG_BX =  W16_SET_HI(*DISK_FLAG_BX, (Y_));
	#define SET_CL(Y_)	*DISK_FLAG_CX = W16_SET_LOW(*DISK_FLAG_CX, (Y_));
	#define SET_CH(Y_)	*DISK_FLAG_CX =  W16_SET_HI(*DISK_FLAG_CX, (Y_));
	#define SET_DL(Y_)	*DISK_FLAG_DX = W16_SET_LOW(*DISK_FLAG_DX, (Y_));
	#define SET_DH(Y_)	*DISK_FLAG_DX =  W16_SET_HI(*DISK_FLAG_DX, (Y_));

	#define GET_AL()	 W16_GET_LOW(*DISK_FLAG_AX)
	#define GET_AH()	  W16_GET_HI(*DISK_FLAG_AX)
	#define GET_BL()	 W16_GET_LOW(*DISK_FLAG_BX)
	#define GET_BH()	  W16_GET_HI(*DISK_FLAG_BX)
	#define GET_CL()	 W16_GET_LOW(*DISK_FLAG_CX)
	#define GET_CH()	  W16_GET_HI(*DISK_FLAG_CX)
	#define GET_DL()	 W16_GET_LOW(*DISK_FLAG_DX)
	#define GET_DH()	  W16_GET_HI(*DISK_FLAG_DX)


};
//////////////////////////////////////////////////////////////////////////////////////////
// Enumeração das funções da INT13h
//////////////////////////////////////////////////////////////////////////////////////////

enum INT13h_FX
{  
	INT13h_reset					= 0x00 ,
	INT13h_status					= 0x01 ,
	INT13h_read						= 0x02 ,
	INT13h_write					= 0x03 ,
	INT13h_verify					= 0x04 ,
	INT13h_format					= 0x05 ,
	INT13h_formatflags				= 0x06 ,
	INT13h_formattrack				= 0x07 ,
	INT13h_params					= 0x08 ,
	INT13h_init						= 0x09 ,
	INT13h_read_with_ECC			= 0x0A ,
	INT13h_write_with_ECC			= 0x0B ,
	INT13h_seekcyl					= 0x0C ,
	INT13h_reset_alt				= 0x0D ,
	INT13h_read_sect_buffer			= 0x0E ,
	INT13h_write_sect_buffer		= 0x0F ,
	INT13h_test_drive				= 0x10 ,
	INT13h_test_recalibrate			= 0x11 ,
	INT13h_test_ctl_ram_diagn		= 0x12 ,
	INT13h_drv_diagn				= 0x13 ,
	INT13h_internal_drv_diagn		= 0x13 ,
	INT13h_internal_ctl_diagn		= 0x14 ,
	INT13h_read_drv_type			= 0x15 ,
	INT13h_disk_change				= 0x16 ,
	INT13h_set_dasd					= 0x17 ,
	INT13h_set_mediatype			= 0x18 ,
	INT13h_set_park_hdd_heads		= 0x19 ,
	INT13h_fmt_esdi_hdd				= 0x1A ,

	INT13h_verifyExts				= 0x41 ,
	INT13h_readExt					= 0x42 ,
	INT13h_writeExt					= 0x43 ,
	INT13h_paramsExt				= 0x44
};
SW8* INT13h_FXStrs[] = { 
	"rst",
	"stat",
	"rd",
	"wr",
	"vrf",
	"fmt",
	"fmtflags",
	"fmttrk",
	"params",
	"init",
	"rd_long",
	"wr_long",
	"seekcyl",
	"rst_alt",
	"rd_buf",
	"wr_buf",
	"tstdrv",
	"tstrecal",
	"tstram",
	"drvdiagn",
	"intdrvalign",
	"intctlalign",
	"rddrvtpe",
	"dskchange",
	"setdsad",
	"setmediaty",
	"setparkhd",
	"esdifmt"

};

//////////////////////////////////////////////////////////////////////////////////////////
// Disk Base Table, ponteiro dado pela função 08 (GET PARAMS) da Int13h
//////////////////////////////////////////////////////////////////////////////////////////

VL_PACK_BEGIN

struct VL_PACK_MIDDLE BIOS_DBT
{
	W8 BIOS_DBT_SPEC1;			//
	W8 BIOS_DBT_SPEC2;		  	//1
	W8 BIOS_DBT_WAITMOTOR;	  	//2
	W8 BIOS_DBT_BYTESPERSECT; 	//3
	W8 BIOS_DBT_SECTPERCIL;   	//4
	W8 BIOS_DBT_GAPLENGTH;    	//5
	W8 BIOS_DBT_DATALENGTH;   	//6
	W8 BIOS_DBT_FGAPLENGTH;   	//7
	W8 BIOS_DBT_FILLBYTE;     	//8
	W8 BIOS_DBT_HEADSETTLE;   	//9
	W8 BIOS_DBT_MOTORSTART;   	//10
	W8 BIOS_DBT2_CILS;		  	//11
	W8 BIOS_DBT2_HEADS;       	//12
	W16 BIOS_DBT2_RWC_CIL;     	//13
	W16 BIOS_DBT2_WPRC_CIL;    	//15
	W8 BIOS_DBT2_ECC_MAXBURST;	//17
	W8 BIOS_DBT2_CTRLBYTE;		//18
	W8 RESERVED;				//19
								//20
	
	W0  update(const W32 heads_, const W32 cyls_, const W32 sectsPerTracks_)
	{
		BIOS_DBT_SPEC1				= 0xDF; 
		BIOS_DBT_SPEC2		  		= 0x02; 
		BIOS_DBT_WAITMOTOR	  		= 0x64; 
		BIOS_DBT_BYTESPERSECT		= 0x02; 
		BIOS_DBT_SECTPERCIL   		= sectsPerTracks_; 
		BIOS_DBT_GAPLENGTH    		= 0x2A; 
		BIOS_DBT_DATALENGTH   		= 0xFF; 
		BIOS_DBT_FGAPLENGTH   		= 0x80; 
		BIOS_DBT_FILLBYTE     		= 0xF6; 
		BIOS_DBT_HEADSETTLE   		= 0x0F; 
		BIOS_DBT_MOTORSTART   		= 0x04; 
		BIOS_DBT2_CILS		  		= cyls_; 
		BIOS_DBT2_HEADS      		= heads_; 
		BIOS_DBT2_RWC_CIL			= 0x3FA0; 
		BIOS_DBT2_WPRC_CIL			= 0; 
		BIOS_DBT2_ECC_MAXBURST		= 0; 
		BIOS_DBT2_CTRLBYTE			= 0; 
	}
};
VL_PACK_END
	
VL_PACK_BEGIN
struct VL_PACK_MIDDLE BIOS_FDPT
{
	W16  CYLINDERS;			//
	W8   HEAD_MAX;			//2
	W16  RED_WR_CURRENT;	//3	
	W16  WR_PRECOMP;		//5
	W8   ECC_BURST;			//7
	W8   CTL_BYTE;			//8
	W8	 STD_TIMEOUT;		//9
	W8	 FMT_TIMEOUT;		//10
	W8   RESERVED;			//11
	W16  LAND_ZONE;			//12
	W8	 SECTPERTRACK;		//14
	W8   RESERVED2;			//15
							//16

	W0  update(const W32 heads_, const W32 cyls_, const W32 sectsPerTracks_)
	{
		CYLINDERS		= cyls_;
		HEAD_MAX		= heads_-1;
		RED_WR_CURRENT	= 0;
		WR_PRECOMP		= 0;
		ECC_BURST		= 0;
		CTL_BYTE		= 0;
		STD_TIMEOUT		= 0;
		FMT_TIMEOUT		= 0;
		RESERVED		= 0;
		LAND_ZONE		= 0;
		SECTPERTRACK	= sectsPerTracks_;
		RESERVED		= 0;
	}
};
VL_PACK_END

BIOS_DBT* dbts	=  (BIOS_DBT*) (DISK_FLAGS + DISK_FLAG_DBT_OFFSET);
//BIOS_FDPT* fdpt =  (BIOS_FDPT*) (DISK_FLAGS + DISK_FLAG_FDPT_OFFSET);

//////////////////////////////////////////////////////////////////////////////////////////
// Representação das 3 unidades (2 disquetes, 1 HDD)
//////////////////////////////////////////////////////////////////////////////////////////

class Drive
{
public:
	enum DISK_TYPE
	{ 
		DISK_TYPE_FD_PHYSICAL = 0, 
		DISK_TYPE_FD_720 = 3, 
		DISK_TYPE_FD_1440 = 4, 
		DISK_TYPE_HD = 5, 
		DISK_TYPE_NONE = 100 };

	W8				id;
	FSNode			node;
	SW8				letter[3]; //123
	SW8				name[15]; //12345678.0123 
	DISK_TYPE		type;
	W32				size;
	W1				changed;
	W32				heads, cyls, sectorsPerTrack; //cyls=tracks
	W1				valid;
//
	W32 get_LBA(const W32 C_, const W32 H_, const W32 S_)
	{
		return chsToLBA(C_, H_, S_, heads, sectorsPerTrack);
	}
	W32 get_total_sectors()
	{
		return heads*cyls*sectorsPerTrack;
	} 
	W16 encode_for_bios_CX()
	{
		W16 cx;
		//printf("\nCyls:%i", cyls);
		//printf("\nsectorsPerTrack:%i", sectorsPerTrack);

		bios_encode_cylinder_sectorspertrack(cyls,sectorsPerTrack,cx);
		return cx;
	}
//
	W0 init_type_and_chs(const W32 size_)
	{
		changed = true;
		size = size_;

		if (id<2)
		{
			if (size==737280)
			{
				heads = 2;
				cyls  = 80;
				sectorsPerTrack  = 9;
				type  = DISK_TYPE_FD_720;
				valid = true;
			}
			else if (size==1474560) 
			{
				heads = 2;
				cyls  = 80;
				sectorsPerTrack  = 18;
				type=DISK_TYPE_FD_1440;
				valid = true;
			}
			else
				valid = false;
		}
		else 
		{
			
			type=DISK_TYPE_HD;
			heads = 16;
			sectorsPerTrack = 0x1F;
			cyls = size_/(512*heads*sectorsPerTrack);
			W32 cilsR = size_%(512*heads*sectorsPerTrack);
			
			// cyls tem de ser menor

			//heads = 1;
			//sectorsPerTrack = 1;
			//cyls = 1;
			W16 cx = encode_for_bios_CX();
			
			W32 totalBytes =  heads*cyls*sectorsPerTrack*512;
			printf("\nGeometria:%i bytes %i MB [C:%i H:%i S:%i] CX:%X", totalBytes, totalBytes>>20, 
					cyls, heads, sectorsPerTrack, cx);

			//W16 cyls_, heads_, sects_;
			//bios_decode_cylinder_sectorspertrack(cx, cyls_, sects_);
			//printf("\nReverse: [C:%i S:%i]", cyls_,sects_);

			valid = true;
		}

		dbts[id].update(heads, cyls, sectorsPerTrack);
		//if (id ==2)
		//	fdpt->update(heads, cyls, sectorsPerTrack);
	}

	Drive(){}
	Drive(W32 id_, SW8* letter_)
	{
		changed = true;
		strcpy(name,"TEST");
		strcpy(letter, letter_);
		id = id_;
	}

	W0 init(std::string path_)
	{
		W32 bytesRXTX;

		if (id==0){ *DISK_FLAG_DRVA_IS_PHYSICAL = 0; }
		if (id==1){ *DISK_FLAG_DRVB_IS_PHYSICAL = 0; }
	
		printf("\n\nDisk %i: %s", id, path_.c_str());

		changed = true;

		turnSD();

		FS_FLAGS res = fs_createFileNode(path_.c_str(), &node, 0, true);
		if (res!=FS_OK) fatal(0,0);
	 
		fs_checkSequence(&node);
		printf("\nNode is sequential? %c",(node.isSequential)?'Y':'N');
		
		SW8* str  = getFilename((SW8*)path_.c_str());
		strcpy(name, str);
		//tirar a extensao
		
		for (W32 i=0; i< 15; i++)
		{
			if (name[i]==0) break;
			if (name[i]=='.')
			{
				name[i]=0;
				break;
			}
		}

		
		init_type_and_chs(node.file.fileSize);
	}
	W0 initDontUse()
	{
		if (id==2) *DISK_FLAG_DRVC_USE = 0;
	}
	W0 initPhysical()
	{
		changed = true;
		if (id==0){ *DISK_FLAG_DRVA_IS_PHYSICAL = 1; type = DISK_TYPE_FD_PHYSICAL; valid=true;}
		if (id==1){ *DISK_FLAG_DRVB_IS_PHYSICAL = 1; type = DISK_TYPE_FD_PHYSICAL; valid=true;}
	}


	
		

};
Drive drives[3];

//////////////////////////////////////////////////////////////////////////////////////////
// Currente estado da INT13h
//////////////////////////////////////////////////////////////////////////////////////////

Drive  *d_drive;	
W8		d_driveId;
W8		d_function;	
W16		d_number_sectors;			
W16		d_head;				
W16		d_sector;			
W16		d_currsector;			
W16		d_cylinder;	
W32		d_lba;		
W32		d_operation;

//////////////////////////////////////////////////////////////////////////////////////////
// Routinas da INT13h
//////////////////////////////////////////////////////////////////////////////////////////

W0  ui_regs_display()
{
	SW8 str[128];
	printf("\r\nAX= %04X  BX=%04X", GET_AX(), GET_BX());
	printf("\r\nCX= %04X  DX=%04X", GET_CX(), GET_DX());
	printf("\r\nES= %04X  DI=%04X", GET_ES(), GET_DI());
	printf("\r\nSI=%04X",   *DISK_FLAG_SI);
	printf("\r\nBP= %04X",	*DISK_FLAG_BP);
//	printf("\r\nInt13h: %04X:%04X ", *DISK_FLAG_INT13h_ORIGINAL_SEG, *DISK_FLAG_INT13h_ORIGINAL_IP);

}
W0  ui_int13h_display(W1 err_ = false)
{

	//turnDisplay();
	SW8 str[256];
	
	if (err_)
		draw_clear(Color_Red);
	 
	//draw_clear(0xEEEE);
	sprintf(str, " *** %02Xh %s *** drive:%i", d_function, INT13h_FXStrs[d_function], d_driveId);
		printf("\n");
		printf(str);
		//draw_text(5,17,str);

	if (d_function==2 || d_function==3)
	{
		sprintf(str, " C:%02X H:%02X S:%02X", d_cylinder, d_head, d_sector);
			printf("\n");
			printf(str);
			//draw_text(5,35,str);

		sprintf(str, " LBA:%Xh (%Xh, aos %i Kbytes) #:%i/%i (%i sectors)", d_lba, d_lba*512,(d_lba*512)>>10, d_currsector, d_currsector+d_number_sectors, d_number_sectors);
			printf("\n");
			printf(str);
			//draw_text(5,55,str);
	}

//	sprintf(str, "AX:%Xh BX:%Xh ", *DISK_FLAG_AX, *DISK_FLAG_BX);
//	draw_text(5,75,str);

	if (err_)
	{
		sprintf(str, "*********ERRO ");
		draw_text(5,75,str,0xFFFF);
		printf("\n");
		printf(str);
		while(1){}
	}
			
	//DRAW_UPDATE

	//turnSD();

}

W0  int13h_02h_read()
{
	turnSD();
	W32 bytesRXTX;

	for (W32 i=0; i< d_number_sectors; i++, d_currsector++)
	{
		
		while(*DISK_FLAG_CMD==0){}
		*DISK_FLAG_CMD=0;
		 
		FS_FLAGS fs_res = fs_rw_sequential_512B(&(d_drive->node), DISK_BUFFER, FS_OP_READ);
		if (fs_res!=FS_OK) 
		{
			ui_int13h_display(1);
			fatal(0,0);
		}
		
		*DISK_FLAG_CMDRES = 1;
		
		#ifdef DEBUG_INT13h_BUFFERS
			printf("\n*** Buffer: sector %i/%i offset:%X", i, d_number_sectors-1, d_lba*512+i*512);
			prnBuff(DISK_BUFFER, 6); 
		#endif
	}
}
W0  int13h_03h_write()
{
	W32 bytesRXTX;
	
	for (W32 i=0; i< d_number_sectors; i++, d_currsector++)
	{ 
		
		while(*DISK_FLAG_CMD==0){}
		*DISK_FLAG_CMD=0;

		FS_FLAGS fs_res = fs_rw_sequential_512B(&(d_drive->node), DISK_BUFFER, FS_OP_WRITE);
		
		#ifdef DEBUG_INT13h_BUFFERS
			printf("\n*** Buffer: sector %i/%i offset:%X", i, d_number_sectors-1, d_lba*512+i*512);
			prnBuff(DISK_BUFFER, 6); 
		#endif

		*DISK_FLAG_CMDRES = 1;

		if (fs_res!=FS_OK) 
		{
			ui_int13h_display(1);
			fatal(0,0);
		}
	}
} 
W0  int13h_08h_params()
{
	while(*DISK_FLAG_CMD==0){}

	// ES:DI pointer to a 11 byte Disk Base Table

	SET_CX(d_drive->encode_for_bios_CX())	// CX: cilindros, setores por cilindro
	SET_DH(d_drive->heads-1)				// DH: number of cabecas-1 (heads)

	if (d_driveId < 2)
	{
		printf("\nFDD?");
		
		//SET_ES(0xC800)
		//SET_DI(DISK_FLAG_DBT_OFFSET + d_driveId * sizeof(BIOS_DBT))

		SET_BL(d_drive->type)				// BL: CMOS drive type
		SET_DL(2)							// DL: number of drives attached
	}
	else
	{ 
		//SET_DH(0xFE)
		//SET_CX(0xFFFF)
		SET_DL(1)							// DL: number of drives attached
	}
			
	SET_AX(0)								// AH: result
	*DISK_FLAG_CMDRES=1;
		
} 
W0  int13h_15h_read_drv_type()
{ 
	while(*DISK_FLAG_CMD==0){}
	if (d_driveId<2)
	{
		SET_AH(2)			// floppy com suporte de detecao: 2
	}
	else
	{
		if (*DISK_FLAG_DRVC_EXISTS && *DISK_FLAG_DRVC_USE)
		{
			printf("\nHDD PRESENT?");
			SET_AH(3)			// hdd presente
			W32 sectors = d_drive->get_total_sectors();
			SET_CX(sectors >> 16)
			SET_DX(sectors)
		}
		else
		{
			printf("\nHDD NOT PRESENT");
			SET_AH(0)			// hdd nao presente
		}
	}
	*DISK_FLAG_CMDRES=1;

}
W0  int13h_16h_disk_change()
{
	while(*DISK_FLAG_CMD==0){}
	  
	if (d_driveId<2)
	{
		//printf("\nLINE CHANGE? %i", d_drive->changed?1:0);
		SET_AH(d_drive->changed?1:0)	// mudança de disquete
	}
	else
	{
		SET_AH(0)						 // hdd nunca mudado
	}

	*DISK_FLAG_CMDRES=1; 

 }
W0  INT13h_01_status()
{
	while(*DISK_FLAG_CMD==0){}

	if (d_drive->changed)
	{
		SET_AH(6)	//drive changed
		d_drive->changed = false;
	}
	else
		SET_AH(0)

	*DISK_FLAG_CMDRES=1; 
}
W0  INT13h_others()
{

	while(*DISK_FLAG_CMD==0){}
	
	SET_AH(0)						 // hdd nunca mudado

	*DISK_FLAG_CMDRES=1; 
}
 
W0  int13h_handler()
{ 
	if (*DISK_FLAG_START_OPERATION==0) return;
	*DISK_FLAG_START_OPERATION=0;
	idleTimer = 0;
	
	d_function			= GET_AH();
	d_number_sectors	= GET_AL();
	d_head				= GET_DH();
	d_driveId			= GET_DL();
	d_operation			= *DISK_FLAG_BOOT;
	if (d_driveId>1) d_driveId = 2;
	

	#ifdef DEBUG_INT13h
		printf("\n **************** Inicio Operacao %X %X **************** ",*DISK_FLAG_BOOT, d_function);
		fflush(stdout);
	#endif

	// opcional	-- optional
	ui_set_drive_operation_icons(d_driveId, d_function);3
	//
	
	bios_decode_cylinder_sectorspertrack(GET_CX(), d_cylinder, d_sector);

	d_drive				= &(drives[d_driveId]);
	d_lba				= d_drive->get_LBA(d_cylinder, d_head, d_sector);
	d_currsector		= d_sector;
	
	

	#ifdef DEBUG_INT13h
		ui_int13h_display();
	#endif

	switch(d_function)
	{
		default:
			INT13h_others();
			break;
		case INT13h_status:
			INT13h_01_status();
		case INT13h_read:
		case INT13h_write:
		{
			turnSD();
			if (d_lba*512 >= d_drive->size )
			{
				printf("\n***ACESSO FORA DO TAMANHO lba:%i (%i / %i bytes)", d_lba, d_lba*512, d_drive->size );
				fatal(FS,0xFF);
			}
			
			FS_FLAGS fs_res = fs_seek_sequential(&(d_drive->node), d_lba*512);
			
			if (fs_res!=FS_OK)  { printf("\n***FSEEK!!!"); fatal(FS,0xFE); }
			
			if (d_function==INT13h_read)
				int13h_02h_read();
			else
				int13h_03h_write();
		
			break;
		}
		case INT13h_read_drv_type:
			int13h_15h_read_drv_type();
			break;
		case INT13h_disk_change:
			int13h_16h_disk_change();
			break;
		case INT13h_params:
			int13h_08h_params();
			break;
	}
	//printf("\n *** ");
} 

