#define MEMORY_ENABLE_LOW_ADDRESS	PIN_WRITE(PIN_ADDR_MUX,0);
#define MEMORY_ENABLE_HI_ADDRESS	PIN_WRITE(PIN_ADDR_MUX,1);

//#define MEMORY_DEBUG_PRINT

//2
#define MEMORY_ENABLE_DELAY1 \
		DELAY_ATOMIC        

//7
#define MEMORY_ENABLE_DELAY2 \
		DELAY_ATOMIC  DELAY_ATOMIC DELAY_ATOMIC DELAY_ATOMIC \
		DELAY_ATOMIC  DELAY_ATOMIC DELAY_ATOMIC
		  

#define ADDRESS_BUS_GET_ADDR \
		

// 54 3210					posicao
// 11 1111					binario
// 3    F   			    hexadecimal

	#define ADDRESS_PIN_LENGTH_MASK	0x3F		

	
//4
#define MEMORY_READ_END_DELAY \
			ATOMIC_DELAY ATOMIC_DELAY ATOMIC_DELAY ATOMIC_DELAY

//3
#define MEMORY_READ_MIDDLE_DELAY \
			ATOMIC_DELAY ATOMIC_DELAY ATOMIC_DELAY 
		 

const W32 sm0 = 0, sm1 = 1, sm2= 2;

W0 init_buses_as_gpio(W1 initMemRead_=true, 
					  W1 initMemWrite_=true, 
					  W1 initAddrMux_=true,
					  W1 initMemWait_=true)
{
	
	if (initMemWait_)
	{
		PIN_INIT(PIN_MEM_WAIT)
		PIN_MODE(PIN_MEM_WAIT, PIN_MODE_OUTPUT)
		PIN_WRITE(PIN_MEM_WAIT, 0);
	}

	if (initAddrMux_)
	{
		PIN_INIT(PIN_ADDR_MUX)
		PIN_MODE(PIN_ADDR_MUX,			PIN_MODE_OUTPUT)
	}
	if (initMemRead_)
	{
		PIN_INIT(PIN_MEM_READ)
		PIN_MODE(PIN_MEM_READ,			PIN_MODE_INPUT)
	}
	if (initMemWrite_)
	{
		PIN_INIT(PIN_MEM_WRITE)
		PIN_MODE(PIN_MEM_WRITE,			PIN_MODE_INPUT)
	}

	// ADDRESS BUS (atras do buffer)
	PIN_INIT(PIN_A0)
	PIN_INIT(PIN_A1)
	PIN_INIT(PIN_A2)
	PIN_INIT(PIN_A3)
	PIN_INIT(PIN_A4)
	PIN_INIT(PIN_A5)
	PIN_MODE(PIN_A0, PIN_MODE_INPUT)
	PIN_MODE(PIN_A1, PIN_MODE_INPUT)
	PIN_MODE(PIN_A2, PIN_MODE_INPUT)
	PIN_MODE(PIN_A3, PIN_MODE_INPUT)
	PIN_MODE(PIN_A4, PIN_MODE_INPUT)
	PIN_MODE(PIN_A5, PIN_MODE_INPUT)

	PIN_INIT(PIN_D0)
	PIN_INIT(PIN_D1)
	PIN_INIT(PIN_D2)
	PIN_INIT(PIN_D3)
	PIN_INIT(PIN_D4)
	PIN_INIT(PIN_D5)
	PIN_INIT(PIN_D6)
	PIN_INIT(PIN_D7)
	PIN_MODE(PIN_D0, PIN_MODE_INPUT)
	PIN_MODE(PIN_D1, PIN_MODE_INPUT)
	PIN_MODE(PIN_D2, PIN_MODE_INPUT)
	PIN_MODE(PIN_D3, PIN_MODE_INPUT)
	PIN_MODE(PIN_D4, PIN_MODE_INPUT)
	PIN_MODE(PIN_D5, PIN_MODE_INPUT)
	PIN_MODE(PIN_D6, PIN_MODE_INPUT)
	PIN_MODE(PIN_D7, PIN_MODE_INPUT)

}


W0 config_MasterPIO(W32 sm_)
{
	W32 offset = pio_add_program(pio0, &master_pio_program);
		
	pio_sm_config config = master_pio_program_get_default_config(offset);

	pio_sm_clear_fifos(pio0, sm_);

	pio_sm_init(pio0, sm_, offset, &config);
	pio_sm_set_enabled(pio0, sm_, true);
}
W0 config_PIO(W32 sm_, W1 irq_=false)
{

	pio_gpio_init(pio0, PIN_MEM_WAIT);

	pio_sm_config config;
	W32 offset;
	
	if (sm_==0)
	{
		offset = pio_add_program(pio0, &memr_pio_program);
		config = memr_pio_program_get_default_config(offset);
	}
	else
	{
		offset = pio_add_program(pio0, &memw_pio_program);
		config = memw_pio_program_get_default_config(offset);
	}
	
	
	sm_config_set_set_pins(&config, PIN_MEM_WAIT, 1);
	pio_sm_set_consecutive_pindirs(pio0, sm_, PIN_MEM_WAIT  , 1  , GPIO_OUT);

	gpio_set_dir(PIN_MEM_WRITE, GPIO_IN);
	gpio_set_dir(PIN_MEM_READ,  GPIO_IN);

	pio_sm_clear_fifos(pio0, sm_);
	pio_sm_init(pio0, sm_, offset, &config);
	pio_sm_set_enabled(pio0, sm_, true);
	
}

W0 app_core_0()
{
	init_buses_as_gpio(true,true,true,false);
	
	

	config_MasterPIO(2);
	config_PIO(1);
	config_PIO(0);

	MEMORY_ENABLE_HI_ADDRESS
	DATABUS_OE_OFF
	//DATABUS_OE_ON
	while(1)
	{ 
		// (1) esperar pela transição no PIO / Wait PIO transition
		while(pio_sm_is_rx_fifo_empty(pio0, sm2)){}
		
		// Formar endereço / Compose Address
		MEMORY_ENABLE_DELAY1														
		const W32 stateHi  =  (sio_hw->gpio_in >> PIN_A0) &  (ADDRESS_PIN_LENGTH_MASK);	
		MEMORY_ENABLE_LOW_ADDRESS														
		MEMORY_ENABLE_DELAY2														
		const W32 stateLow = (sio_hw->gpio_in >> PIN_A0) & 	 (ADDRESS_PIN_LENGTH_MASK);	
		const W32 addr =  ( (stateHi << 6) | stateLow);		
		MEMORY_ENABLE_HI_ADDRESS

		if (PIN_READ(PIN_MEM_READ))
		{

			#ifdef MEMORY_DEBUG_PRINT
				printf("\nMEMR: %X", addr);
			#endif

			// Colocar os pinos do databus para OUTPUT / Set Databus pins for OUTPUT
			sio_hw->gpio_oe_set = DATABUS_PIN_MASK;

			// ROM
			if (addr < DISK_ROM_TOTAL_SIZE )
			{
				const W32 value = DISK_ROM[addr] << PIN_D0; 
				gpio_put_masked(DATABUS_PIN_MASK, value);
				trapNumberR++;
			}else
			{
				gpio_put_masked(DATABUS_PIN_MASK, 0);
			}
		

			DATABUS_OE_ON
			pio_sm_get(pio0, sm2);

			#ifdef APP_DEBUG_MEMORY_ACCESS 
				if (trapNumberR<DISK_ROM_SIZE)
				{
					trapsAddressesR[trapNumberR] = addr;
					trapNumberR++;
				}
			#else
				MEMORY_READ_MIDDLE_DELAY
			#endif
		
			// (2) Passar controlo ao PIO / Transfer control for PIO
			pio_sm_put_blocking(pio0,sm0,0);
		
			// (3) Esperar pela transição no PIO / Wait transition from PIO
			while(pio_sm_is_rx_fifo_empty(pio0,sm0)){}
			pio_sm_get(pio0, sm0);
		
			MEMORY_READ_END_DELAY	

			
			#ifdef MEMORY_DEBUG_PRINT
				printf("\nMEMR LEAVING");
			#endif

			// Colocar os pinos do databus para INPUT / Set Databus pins for INPUT
			// Colocar transceiver de databus OFF / Set Databus transceiver OFF
			DATABUS_OE_OFF
			sio_hw->gpio_oe_clr = DATABUS_PIN_MASK;

		}
		else
		{ 
			
			#ifdef MEMORY_DEBUG_PRINT
				printf("\nMEMW: %X", addr);
			#endif
			//blink(1000,100);

			// Gravar na RAM
			// Colocar os pinos do databus para INPUT / Set Databus pins for INPUT
			// Colocar transceiver de databus ON / Set Databus transceiver ON
			sio_hw->gpio_oe_clr = DATABUS_PIN_MASK;
			DATABUS_OE_ON
			pio_sm_get(pio0, sm2);
				
			MEMORY_READ_MIDDLE_DELAY
			const W8 data = (sio_hw->gpio_in >> PIN_D0) & 0xFF;

			 if (addr<DISK_ROM_TOTAL_SIZE)	
			 {
				 if (addr<DISK_ROM_SIZE)
				 {
					#ifdef MEMORY_DEBUG_PRINT
						printf("\nFORBIDEN");
					#endif
					// forbiddenWritesAddr[forbiddenWrites]=addr;
					 forbiddenWrites++;
				 }
				 else
				 {
					 DISK_ROM[addr]=data;
				 }
				trapNumberBWR++;
			 }

			#ifdef APP_DEBUG_MEMORY_ACCESS
				if (trapNumberW<DISK_ROM_SIZE)
				{
					trapsAddressesW[trapNumberW] = addr;
					trapNumberW++;
				}
			#else
				MEMORY_READ_MIDDLE_DELAY
				trapNumberW++;
			#endif
				
			#ifdef MEMORY_DEBUG_PRINT
				printf("\nMEMW*3");
			#endif
			// (2) Passar controlo ao PIO
			pio_sm_put_blocking(pio0, sm1, 0);
		
			#ifdef MEMORY_DEBUG_PRINT
				printf("\nMEMW*4");
			#endif

			// (3) Esperar pela transição no PIO / Wait transition from PIO
			while(pio_sm_is_rx_fifo_empty(pio0, sm1)){}
			pio_sm_get(pio0, sm1);
		
			MEMORY_READ_END_DELAY
			
			#ifdef MEMORY_DEBUG_PRINT
				printf("\nMEMW LEAVING");
			#endif

			// Colocar transceiver de databus OFF / Set Databus transceiver OFF
			DATABUS_OE_OFF
			sio_hw->gpio_oe_clr = DATABUS_PIN_MASK;
		}
	}
} 

