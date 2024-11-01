/*
 * Copyright 2008-2013 Code Red Technologies Ltd,
 * Copyright 2013-2024 NXP
 * Generated linker script file for LPC824
 * Created from memory.ldt by FMCreateLinkMemory
 * Using Freemarker v2.3.30
 * MCUXpresso IDE v11.9.0 [Build 2144] [2024-01-05] on Aug 16, 2024, 10:09:59 PM
 */

MEMORY
{
    /* Define each memory region */
    MFlash (rx) : ORIGIN = 0x0, LENGTH = 0x40000 /* 256K bytes (alias Flash) */
    /* ResetRam is preserved upon warm resets */
    ResetRam (rwx) : ORIGIN = 0x10000000, LENGTH = 0x20 /* 64 bytes (alias RESETRAM) */  
    RamLoc8 (rwx) : ORIGIN = 0x10000020, LENGTH = 0x7fe0 /* (32K - 64) bytes (alias RAM) */
    Sram1(rwx) :    ORIGIN = 0x20000000, LENGTH = 0x800     /* 2KB  */
    Sram2(rwx) :    ORIGIN = 0x20004000, LENGTH = 0x800     /* 2KB  */
    Eeprom(rw) :    ORIGIN = 0x20000000, LENGTH = 0x1000     /* 4KB  */

    /*
     * MTB:         0x14000000, 0x1000
     * Boot ROM:    0x1fff0000, 0x8000
     * CRC:         0x50000000, 0x4000
    */
}

    __base_Sram1 = ORIGIN(Sram1);
    __top_Sram1 = ORIGIN(Sram1) + LENGTH(Sram1);
    __base_Sram2 = ORIGIN(Sram2);
    __top_Sram2 = ORIGIN(Sram2) + LENGTH(Sram2);

include "common.ld"
