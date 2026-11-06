# ISA-Raspberry-Pi-Pico-Disk-Emulator
A Raspberry Pi Pico **floppy disk and harddisk emulator** for older computers/operating systems that **relies only** on BIOS for disk accesses. Its a ISA-8 bit board. "It can let you use it your physical floppy drives or, floppy images on demand, using a tiny screen and a joystick". As this is a DIY electronics and software project, use this at your own risk.

**Included** 
  - Kicad ISA-8bit schematic
  - C and ASM code
  - building scripts (windows only)
  - Amstrad PPC512/640 rear expansion ports diagram (for doing a "box" for this computer, instead of a ISA-slot card)
  - Memory addressing and connection simple diagrams

**Project Description**

   This ISA-8bit board implements new INT13h and INT19h BIOS software interrupts handlers for disk access and bootstrapping at 0xC8000. Instead of a having the typical ROM, a Raspberry Pi Pico serves these addresses with its own memory. Theres a mini TFT (ST7735), a Joystick, and a SDCard adapter connected by flat ribbon cables that can be attached to a front-panel. The board supports a FAT16 file system containing directories, floppy disk images, and a raw harddisk image (it must be named "hdd.ima" at the root directory). Using the joystick is possible to enable the harddisk image use, navigate SDCard filesystem, and assign floppy disk images to A: and B: drives at any time; theres also the option to select the physical drive instead of floppy disks. The bootstrap code (int19h) is needed for older computers not supporting booting from hard disks so it will place INT13h passing the drive (0x80) and if the hdd.ima file exists, it will boot just as fine.
   The advantage of replacing INT13h or jumping to the factory INT13h, is that is possible to enable the use of the physical drive or using a floppy disk image on demand. However, only ancients Operating Systems uses INT13h directly, so everything that is Windows-386 enhanced mode and beyond - that uses drivers for talking directly with floppy drives and harddisk via IO ports - doesn't belong to this project. 

**Electronics side**
  * Uses 2 74LS244 for multiplexing the address lines A0:A11 to the Raspberry Pi Pico
  * Uses 1 74HC244 for multiplexing the SDCard and TFT lines. The code calls turn_SD() and turnDisplay()
    to activate these lines before placing calls
  * Uses 1 GAL Atmel ATF16v8B for decoding the address 0xC8000 using the A15:A19 lines, along the
    memory read and memory write signals (/MEMR, /MEMW)
  * It pulls down the signal IOREADY using a 2N3904 transistor to it can finish the requests
  * Uses a 2-axis joystick which swings 2 lines between -5V to 5V according to the side (left/right, up/down); these
    lines are connected to 2 ADC channels on the Raspberry Pi Pico
  * Uses 1 74HCT04 for inverting ENABLE_SD and /ENABLE_LOW_ADDR for multiplexing lines, using the 244 buffers.
  * Uses some voltage dividers with resistors for 5V to 3.3V level conversion at the Raspberry Pi Pico
  * Uses a bidirectional bus converter TXS0108E, for the databus to level databus signals from/to 3.3V to 5V, operated with a Output Enable Signal to block them from the main 8086 PC databus

**Software side - Raspberry Pi Pico - Core 0**
  * This CPU is on loop waiting for data from one master PIO program (master_pio). This master_pio is waiting for memr_pio or memw_pio PIO programs for producing and IRQ0.  
  * These previous 2 PIO programs (they are equal, just differ in the line use MEMR or MEMW): the PIO program keeps waiting for these signals to be HIGH - they come HIGH from the ATF16v8b when the base address 0xC8000 is on the address bus as well one of /MEMR or /MEMW are LOW; after, immediately the IOWAIT line is put to HIGH and the transistor will pull down the IOREADY line to indicate the 8086 that needs more time. After, one the master PIO program transfers control to the C program which reads the all the address lines (de/activating /EN_ADDR_LOW) reads which MEMR/W line is HIGH accordantely reads or writes locally from the C-Array, as well controling the databus converter signal DB_ENABLE_OE. At the end, the IOWAIT is lowered, and in case of a writing, the databus is let active for more a period for settling.
  
**Software side - Raspberry Pi Pico - Core 1**
* This CPU is always on a loop:
    1) pooling the shared area variable "START_OPERATION" flag
    2) pooling the joystick values
    3) updating the graphical interface in the TFT in case of joystick movement
* The INT13h code saves the registers to the shared-variable area, and writes the START_OPERATION flag, as soon this happen the code knowns how to handle INT13h by reading or writing the SDCard. The code extracts the Cylinder-Head-Sector from the CPU registers, converts to LBA and reads and writes accordantly. The core code and INT13h code uses the shared-buffer for transfering the r/w data; the 8086 CPU or the Raspberry Core is put to rest when shared-buffer is being wrote by one of them.

**Software side - Raspberry Pi Pico - Core 1 - FileSystem and SDCard**
  * The FAT file system access is done with my own  library. Once a floppy disk image is loaded by using the user interface (or hdd.ima is present) the file is checked for contiguity on their clusters using (that's it if the file clusters are sequential) using "fs_checkSequence" is this is true, then the r/w disk access is done faster using "fs_rw_sequential_512B", as the contents are indexed as 512 bytes starting the start-cluster.
  * The sdcard access is done with my own library it can read/write 512blocks - incomplete code alert: OLDER SD CARDS might not work. 

**Software side - Raspberry Pi Pico - Core 1 - User interface**
  * The ST7735 TFT screen library its my own. The initialization code was borrowed from https://github.com/afiskon/stm32-st7735/ . This screen seems to demand a RESET line, i don't use it and i connect both RESET and BACKLIGHT lines to a pullup. If found if the initialization code is sent at lower speed the screen will work at faster speed without requiring a RESET signal several toogling at the initialization. This saved me a GPIO.
  * My own draw library abstracts calls to the screen primitive functions (drawing pixels, rectangles) with preprocessor DEFINEs.
  * My own user-interface library have base classes to create lists and options, and derived classes to create lists from a source, like a TextFileSource or FSSource to render a menu to navigate the master-boot-records and filesystems. 

**Software side - 8086 PC Option ROM aspects**
  * The 8086 PC BIOS scans the upper memory addresses for option ROMs. These ROMs must include at their first bytes 0xAA55 (2 bytes), the total of 512-bytes blocks(1 byte) and all their bytes shall have a 8-bit sum equal to zero.
  
**Software side - 8086 PC Option ROM**
  * The ROM in written in ASM and compiled in Turbo Assembler in a DOSBOX enviroment.
  * After the 8086 code is compiled and linked with TASM, a utility strips the MZ-header, sums all bytes and writes the remain to 0, and place this remain in a reserved place. After, the utility converts the code to an C hexadecimal array, and this one is included into Raspberry Pi Pico C++ program. This array is served as the beggining of 0xC8000: boot code, INT13h, INT19h handlers, a buffer reserved for transfering data used by INT13h, a shared-flag-area, and the DBTs (disk base table). The DBTs are BIOS structures used by INT13h, function 8 (get params) and need to be dinamically changed accordantly the floppy disk image selected (ie, 720KB or 1440KB).
  








  
  
  
