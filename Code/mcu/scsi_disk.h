volatile W1  scsi_interrupt = false;
volatile W16 scsi_selcnt = 0;
W8  scsi_buf[20];

#if (APP_TARGET==APP_TARGET_RASPBERRY_PICO)
	#define SCSI_GET_DATABUS		((PIN_GETIO_RAW >> (SCSI_PIN_D0))&0xFF)
	#define SCSI_SET_DATABUS(X_)	\
					PIN_SETHI_RAW( X_<<SCSI_PIN_D0  ) \
					PIN_SETLO_RAW( X_<<SCSI_PIN_D0  )

#elif (APP_TARGET==APP_TARGET_ARDUINO_NANO)

	#define RD_DB(X_)  ((PIN_READ(X_)==HIGH)?1:0)

	#define SCSI_GET_DATABUS \
			((RD_DB(SCSI_PIN_D0))|\
			 (RD_DB(SCSI_PIN_D1)<<1)|\
			 (RD_DB(SCSI_PIN_D2)<<2)|\
			 (RD_DB(SCSI_PIN_D3)<<3)|\
			 (RD_DB(SCSI_PIN_D4)<<4)|\
			 (RD_DB(SCSI_PIN_D5)<<5)|\
			 (RD_DB(SCSI_PIN_D6)<<6)|\
			 (RD_DB(SCSI_PIN_D7)<<7))

	#define SCSI_SET_DATABUS(X_) \
		SCSI_PINS_ARDUINO_DATABUS_PORT=X_; \
		PORT_WRITE(SCSI_PIN_D6); \
		PORT_WRITE(SCSI_PIN_D7); 

#endif


enum SCSI_DATABUS_MODE { SCSI_DATABUS_OUTPUT = 0, SCSI_DATABUS_INPUT = 1, SCSI_DATABUS_UNKNOWN=2  };

SCSI_DATABUS_MODE  scsi_databus = SCSI_DATABUS_UNKNOWN;
#define SCSI_OPS_Defs(X_)\
X_(CHGDEF		, CHANGE_DEFINITION				, 0x40)\
X_(CMP			, COMPARE						, 0x39)\
X_(CPY			, COPY							, 0x18)\
X_(CPY&VER		, COPY_AND_VERIFY				, 0x3A)\
X_(FMTUNIT		, FORMAT_UNIT					, 0x04)\
X_(INQ			, INQUIRY						, 0x12)\
X_(LOCKUNLCACH	, LOCK_UNLOCK_CACHE				, 0x36)\
X_(LOGSEL		, LOG_SELECT					, 0x4C)\
X_(LOGSENS		, LOG_SENSE						, 0x4D)\
X_(MODESEL6		, MODE_SELECT_6					, 0x15)\
X_(MODESEL10	, MODE_SELECT_10				, 0x55)\
X_(MODESENS6	, MODE_SENSE_6					, 0x1A)\
X_(MODESENS10	, MODE_SENSE_10					, 0x5A)\
X_(MOVEMED		, MOVE_MEDIUM					, 0xA7)\
X_(PERSRESIN	, PERSISTENT_RESERVE_IN			, 0x5E)\
X_(PERSRESOUT	, PERSISTENT_RESERVE_OUT		, 0x5F)\
X_(PREFTCH		, PREFETCH						, 0x34)\
X_(PREVALLREM	, PREVENT_ALLOW_MEDIUM_REMOVAL	, 0x1E)\
X_(RD			, READ							, 0x08)\
X_(RDBUF		, READ_BUFFER					, 0x3C)\
X_(RDCAP		, READ_CAPACITY					, 0x25)\
X_(RDDDAT10		, READ_DEFECT_DATA_10			, 0x37)\
X_(RDDDAT12		, READ_DEFECT_DATA_12			, 0xB7)\
X_(RDELEM_STAT	, READ_ELEMENT_STATUS			, 0xB4)\
X_(RDEX			, READ_EXTENDED					, 0x28)\
X_(RDLONG		, READ_LONG						, 0x3E)\
X_(REASSGBLKS	, REASSIGN_BLOCKS				, 0x07)\
X_(REB			, REBUILD						, 0x81)\
X_(TXDIAGRES	, TX_DIAGNOSTIC_RESULTS			, 0x1C)\
X_(REGEN		, REGENERATE					, 0x82)\
X_(REL6			, RELEASE_6						, 0x17)\
X_(REL10		, RELEASE_10					, 0x57)\
X_(REPDEV_ID	, REPORT_DEV_IDENTIFICATION		, 0xA3)\
X_(REPLUNS		, REPORT_LUNS					, 0xA0)\
X_(REQSENS		, REQUEST_SENSE					, 0x03)\
X_(RESV6		, RESERVE_6						, 0x16)\
X_(RESV10		, RESERVE_10					, 0x56)\
X_(RE0UNI		, REZERO_UNIT					, 0x01)\
X_(SRCH=		, SEARCH_DATA_EQUAL				, 0x31)\
X_(SRCH>		, SEARCH_DATA_HIGH				, 0x30)\
X_(SRCH<		, SEARCH_DATA_LOW				, 0x32)\
X_(SEEK			, SEEK							, 0x0B)\
X_(SEEKEX		, SEEK_EXTENDED					, 0x2B)\
X_(TXDIAG		, TX_DIAGNOSTICS				, 0x1D)\
X_(SETDEVID		, SET_DEVICE_IDENTIFIER			, 0xA4)\
X_(SETLIMS		, SET_LIMITS					, 0x33)\
X_(STSTPUNI		, START_STOP_UNIT				, 0x1B)\
X_(SYNCCACH		, SYNC_CACHE					, 0x35)\
X_(TESTRDY		, TEST_UNIT_READY				, 0x00)\
X_(VER			, VERIFY						, 0x2F)\
X_(WR			, WRITE							, 0x0A)\
X_(WRVER		, WRITE_VERIFY					, 0x2E)\
X_(WRBUF		, WRITE_BUFFER					, 0x3B)\
X_(WREX			, WRITE_EXTENDED				, 0x2A)\
X_(WRLON		, WRITE_LONG					, 0x3F)\
X_(WRSAM		, WRITE_SAME					, 0x41)\
X_(XDRD			, XDREAD						, 0x52)\
X_(XDWR			, XDWRITE						, 0x50)\
X_(XDRD_EX		, XDREAD_EXTENDED				, 0x80)\
X_(XPWR			, XPWRITE						, 0x51)

#define SCSI_MAKE_OPS_STR_(CODENAME_, NAME_, CODE_)			"" #CODENAME_"",
#define SCSI_MAKE_OPS_STR_IDX_(CODENAME_, NAME_, CODE_)		CODE_,
#define SCSI_MAKE_OPS_ENUM_(CODENAME_, NAME_, CODE_)		SCSI_OP_##NAME_ = CODE_, 
#define SCSI_MAKE_OPS_ENUM(DEF_)							enum SCSI_OPS { DEF_(SCSI_MAKE_OPS_ENUM_) };
#define SCSI_MAKE_OPS_STRS(DEF_) \
	const SW8* scsi_ops_strs[]      =  { DEF_(SCSI_MAKE_OPS_STR_) }; \
	const W8   scsi_ops_strsIndex[] =  { DEF_(SCSI_MAKE_OPS_STR_IDX_) -1 };

SCSI_MAKE_OPS_ENUM(SCSI_OPS_Defs)
SCSI_MAKE_OPS_STRS(SCSI_OPS_Defs)


W1  scsi_checkParity(W8 byte_, const W1 target_)
{
	W8 par  = 0;
	for (W8 i=0; i< 8; i++)
	{
		par+=(byte_&1);
		byte_>>=1;
	}
	if (target_!=(par&1))
	{
		DEBUG_PRINT(F("\nPAR!!"));
		return 1;	
	}
	return 0;
}
W0  scsi_setDatabusFor(const SCSI_DATABUS_MODE mode_)
{
	if (scsi_databus==mode_) return;
	scsi_databus = mode_;
	const W8 pin_mode = (mode_==SCSI_DATABUS_OUTPUT)? PIN_MODE_OUTPUT:PIN_MODE_INPUT;
	DEBUG("\nDB%s",mode_==SCSI_DATABUS_OUTPUT?"out":"in");
	PIN_MODE(SCSI_PIN_D0, pin_mode)
	PIN_MODE(SCSI_PIN_D1, pin_mode)
	PIN_MODE(SCSI_PIN_D2, pin_mode)
	PIN_MODE(SCSI_PIN_D3, pin_mode)
	PIN_MODE(SCSI_PIN_D4, pin_mode)
	PIN_MODE(SCSI_PIN_D5, pin_mode)
	PIN_MODE(SCSI_PIN_D6, pin_mode)
	PIN_MODE(SCSI_PIN_D7, pin_mode)
	PIN_MODE(SCSI_PIN_DP, pin_mode)
}
// se SCSI_SEL = 0
PIN_IRQ_HANDLER(scsi_a_dev_is_selected)					
{ 
	const W8 db = SCSI_GET_DATABUS;
	DEBUG("\nS%i:%02X", ++scsi_selcnt, db);
	if (db!=0)
	{
		if ( db == (1<<SCSI_DEV_ID) )
		{
			//e' para este dispositivo
			scsi_interrupt = true; 
			return; 
		}
	}
	return;
}

W0 scsi_adquire_bus()
{
	 PIN_MODE(SCSI_PIN_REQ,  PIN_MODE_OUTPUT)
	 PIN_MODE(SCSI_PIN_CD,   PIN_MODE_OUTPUT)
	 PIN_MODE(SCSI_PIN_IO,   PIN_MODE_OUTPUT)
}
W0 scsi_release_bus()
{
	 PIN_MODE(SCSI_PIN_REQ,  PIN_MODE_INPUT)
	 PIN_MODE(SCSI_PIN_CD,   PIN_MODE_INPUT)
	 PIN_MODE(SCSI_PIN_IO,   PIN_MODE_INPUT)
}
W0 scsi_get_message()
{
	DEBUG_PRINT("\nS!");
	SCSI_PIN_SET_BUSY
	
	// o alvo (este disco) diz que o iniciador 
	// tem o CMD+SAÍDA e mete REQ para aceitar o tal comando
	scsi_setDatabusFor(SCSI_DATABUS_INPUT);
	SCSI_PIN_SET_INITIATOR_OUT
	SCSI_PIN_SET_INITIATOR_CMD
	SCSI_PIN_SET_REQ

	// este disco (o alvo) espera que iniciador 
	// meta os dados no databus e mande ACK
	while(SCSI_PIN_ACK_IS_UNSET){}

	// este 1. byte da mensagem e' o código
	// a operação e define o tamanho
	const W8 opcode = SCSI_GET_DATABUS;

	scsi_checkParity(opcode, PIN_READ(SCSI_PIN_DP));

	W8 msgLen;
	if (opcode < 0x20) msgLen = 6; 
		else if (opcode < 0x60) msgLen = 10; 
		else if (opcode == 0x7E) msgLen = 0x7E; 
		else if (opcode == 0x7F) msgLen = 0x7F; 
		else if (opcode  < 0x90) msgLen = 16; 
		else if (opcode >= 0xA0 && opcode <= 0xBF) msgLen = 12; 
		else if (opcode >= 0xC0) msgLen = 0xC0;
		else msgLen = 0xFF;
		
	SCSI_PIN_UNSET_REQ

	if (msgLen >= 0x7E)
	{
		DEBUG("\nopcode: %X!!!", opcode);
		STOP
	}

	// ler seguintes bytes da mensagem (opcode que define o tamanho)
	scsi_buf[0] = opcode;
	for (W8 i=i; i< msgLen; i++)
	{
		SCSI_PIN_SET_REQ
		while(SCSI_PIN_ACK_IS_UNSET){}
		scsi_buf[i] = SCSI_GET_DATABUS;
		scsi_checkParity(opcode, PIN_READ(SCSI_PIN_DP));

		SCSI_PIN_UNSET_REQ
	}
	
	SW8* cmdStr = searchString(opcode, scsi_ops_strs, scsi_ops_strsIndex);
	DEBUG("--> CMD %2X %s", opcode, cmdStr);

	switch(opcode)
	{
		#include "scsi_handle_msg.h"
	}

	STOP
	SCSI_PIN_UNSET_BUSY
}
W0 scsi_init()
{
	 PIN_INIT(SCSI_PIN_SEL)
	 PIN_INIT(SCSI_PIN_BSY)
	 PIN_INIT(SCSI_PIN_REQ)
	 PIN_INIT(SCSI_PIN_ACK)
	 PIN_INIT(SCSI_PIN_CD)
	 PIN_INIT(SCSI_PIN_IO)
	 PIN_INIT(SCSI_PIN_D0)
	 PIN_INIT(SCSI_PIN_D1)
	 PIN_INIT(SCSI_PIN_D2)
	 PIN_INIT(SCSI_PIN_D3)
	 PIN_INIT(SCSI_PIN_D4)
	 PIN_INIT(SCSI_PIN_D5)
	 PIN_INIT(SCSI_PIN_D6)
	 PIN_INIT(SCSI_PIN_D7)
	 PIN_INIT(SCSI_PIN_MSG)
	 PIN_INIT(SCSI_PIN_RST)
	 PIN_INIT(SCSI_PIN_ATN)
	 //					 
	 PIN_MODE(SCSI_PIN_SEL,  PIN_MODE_INPUT)	//OpenColector
	 PIN_MODE(SCSI_PIN_BSY,  PIN_MODE_INPUT)	//OpenColector
	 PIN_MODE(SCSI_PIN_REQ,  PIN_MODE_INPUT)
	 PIN_MODE(SCSI_PIN_ACK,  PIN_MODE_INPUT)
	 PIN_MODE(SCSI_PIN_CD,   PIN_MODE_INPUT)
	 PIN_MODE(SCSI_PIN_IO,   PIN_MODE_INPUT)
	 PIN_MODE(SCSI_PIN_MSG,  PIN_MODE_INPUT) //?
	 PIN_MODE(SCSI_PIN_RST,  PIN_MODE_INPUT) //?
	 PIN_MODE(SCSI_PIN_ATN,  PIN_MODE_INPUT) //?
	 scsi_setDatabusFor(SCSI_DATABUS_INPUT);

	#ifdef DEBUG_PINS_SCSI
		scsi_setDatabusFor(SCSI_DATABUS_OUTPUT);
		TEST_PINS(SCSI_PINS_DEF)
	#endif
			
	PIN_INSTALL_IRQ_ONFALL(SCSI_PIN_SEL, scsi_a_dev_is_selected) 
	while (PIN_READ(SCSI_PIN_RST)==LOW) {}
	while(1)
	{
		 // instalar interrupção para SEL
		while(!scsi_interrupt){}
		scsi_adquire_bus();
		scsi_get_message();
	}
}

 