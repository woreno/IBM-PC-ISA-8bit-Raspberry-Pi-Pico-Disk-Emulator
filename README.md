# ISA-raspberry-pi-pico-disk-emulator
A Raspberrry Pi Pico floppy disk and harddisk emulator for older computers/operating systems that relies only on BIOS for disk accesses. ISA-8 bit board. "It can let you use it your physical floppy drives or, floppy images on demand, using a tiny screen".

Included: 
  - Kicad ISA-8bit schematic
  - C and ASM code
  - building scripts (windows only)

Project Description:
  This board implements new INT13h and INT19h BIOS software interrupts handlers for disk access and bootstrapping at 0xC8000. Theres a mini TFT (ST7735) a Joystick, and a SDCard. The SDCard supports a FAT16 file system containing directories, floppy disk images, and a raw harddisk image (it must be named "hdd.ima" at the root directory). Using the joystick is possible to enable the harddisk image use, navigate SDCard filesystem, and assign floppy disk images to A: and B: drives; also theres the option to select the physical drive instead of floppy disks. The bootstrap code (int19h) is needed for older computers not supporting booting from hard disks so it will place INT13h passing the drive (0x80) and if the hdd.ima file exists, it will boot just as fine.

Electronics side:
  * Uses 2 74LS244 for multiplexing the address lines A0:A11 to the Raspberry Pi Pico, these lines have
    voltage dividers with smd resistances.
  * Uses 1 74HC244 for multiplexing the SDCard and TFT lines. The code calls turn_SD() and turnDisplay()
    to activate these lines before placing calls.
  * Uses one GAL Atmel ATF16v8B for decoding the address 0xC8000 using the A15:A19 lines, along the
    memory read and memory write signals (/MEMR, /MEMW)
  * It pulls down the signal IOREADY using a 2N3904 transistor to it can finish the requests.
  * Uses a 2-axis joystick which swings 2 lines between -5V to 5V according to the side (left/right, up/down); these
    lines are connected to 2 ADC channels on the Raspberry Pi Pico

Software side - Raspberry Pi Pico - Core 0:
  * This CPU is on loop waiting for data from one main PIO program (master_pio). This master_pio is waiting for memr_pio or memw_pio for producing and IRQ0.  
  * 2 PIO programs MEMR and MEMW (they are equal, just differ in the line use): the PIO program keeps waiting for
these signals (from the ATF16v8b) to be high; when these signals are high, immediatly the IOWAIT line is put to
HIGH and the transistor will pull down the IOREADY line to indicate the PC that needs more time. After, the PIO program transfer  control to the C program which reads the address lines and makes the 0xC8000 space reading or writing as well controling the databus converter signal DB_ENABLE_OE. At the end, the IOWAIT is lowered, in case of a writing the databus this one is let active for more a period for data to settle.
  
Software side - Raspberry Pi Pico - Core 1:
* This CPU is on loop pooling
    1) pooling the shared area variable "START_OPERATION" flag
    2) pooling the joystick values
    3) updating the graphical interface in the TFT in case of joystick movement
* As soon the INT13h writes the START_OPERATION flag, the INT13h is handled by reading or writing the SDCard


Software side - 8086 PC Option ROM aspects:
  * The 8086 PC BIOS scans the upper memory addresses for option ROMs. These ROMs must include at their first bytes 0xAA55 (2 bytes), the total of 512-bytes blocks(1 byte) and all their bytes shall have a 8-bit sum equal to zero.
  
Software side - 8086 Boot ROM:
  * This part in written in ASM and compiled in Turbo Assembler in a DOSBOX enviroment. 
  After that an utility strips the MZ-header and produces an C array to be included 
  in the Raspberry Pi Pico C++ program. This array is served as the beggining of 0xC8000: boot code, INT13h, INT19h
handlers, a buffer for transfering data used by INT13h

  The Raspberry Pi Pico program, 

  
  
  
