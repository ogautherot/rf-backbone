/**
 * AT25DF641 driver
 * - 75MHz SPI
 * - 2048x 4KB blocks (erase)
 * - 32768x 256B pages (write)
 *
 * - Read array (page)
 * - Program (page)
 * - Erase (block)
 * - Protect sector
 * - Read status
 * - Reset
 * - Read manufacturer and device ID
 * - Deep Power down
 * - Resume from power down
 */

#include <string.h>

#include "lpc11u6x.h"
#include "at25df641.h"

At25df641Class at25(&ssp0);

At25df641Class::At25df641Class(lpc_ssp_t *dev)
{
    ssp = dev;
    memset(buf, 0, sizeof(buf));
}

uint8_t *At25df641Class::ReadPage(uint32_t addr)
{
    uint16_t wsize = 4, rsize = 256;

    buf[0] = 0x03;
    buf[3] = addr & 0xff;
    addr >>= 8;
    buf[2] = addr & 0xff;
    addr >>= 8;
    buf[1] = addr & 0xff;
    ssp->RequestWriteRead(SSP_HANDLE_FLASH, buf, wsize, rsize);
    return buf + wsize;
}

uint8_t *At25df641Class::ReadByte(uint32_t addr, uint32_t rsize)
{
    uint16_t wsize = 4;

    buf[0] = 0x03;
    buf[3] = addr & 0xff;
    addr >>= 8;
    buf[2] = addr & 0xff;
    addr >>= 8;
    buf[1] = addr & 0xff;
    ssp->RequestWriteRead(SSP_HANDLE_FLASH, buf, wsize, rsize);
    return buf + wsize;
}

uint8_t *At25df641Class::BlockErase(uint32_t addr)
{
    uint16_t wsize = 4;

    buf[0] = 0x20;
    buf[3] = addr & 0xff;
    addr >>= 8;
    buf[2] = addr & 0xff;
    addr >>= 8;
    buf[1] = addr & 0xff;
    ssp->RequestWrite(SSP_HANDLE_FLASH, buf, wsize);
    return buf + wsize;
}

uint8_t *At25df641Class::ChipErase(void)
{
    uint16_t wsize = 1;

    buf[0] = 0x20;
    ssp->RequestWrite(SSP_HANDLE_FLASH, buf, wsize);
    return buf + wsize;
}

uint8_t *At25df641Class::ProgramPage(uint32_t addr)
{
    uint16_t wsize = 4 + 256;

    buf[0] = 0x02;
    buf[3] = addr & 0xff;
    addr >>= 8;
    buf[2] = addr & 0xff;
    addr >>= 8;
    buf[1] = addr & 0xff;
    ssp->RequestWrite(SSP_HANDLE_FLASH, buf, wsize);
    return buf + wsize;
}

uint8_t *At25df641Class::ProgramByte(uint32_t addr, uint32_t size)
{
    uint16_t wsize = 4 + size;

    buf[0] = 0x20;
    buf[3] = addr & 0xff;
    addr >>= 8;
    buf[2] = addr & 0xff;
    addr >>= 8;
    buf[1] = addr & 0xff;
    ssp->RequestWrite(SSP_HANDLE_FLASH, buf, wsize);
    return buf + wsize;
}

uint8_t *At25df641Class::WriteEnable(void)
{
    uint16_t wsize = 1;

    buf[0] = 0x06;
    ssp->RequestWrite(SSP_HANDLE_FLASH, buf, wsize);
    return buf + wsize;
}

uint8_t *At25df641Class::WriteDisable(void)
{
    uint16_t wsize = 1;

    buf[0] = 0x04;
    ssp->RequestWrite(SSP_HANDLE_FLASH, buf, wsize);
    return buf + wsize;
}

uint8_t *At25df641Class::ReadSectorProtection(uint32_t addr)
{
    uint16_t wsize = 5, rsize = 1;

    buf[0] = 0x20;
    buf[3] = addr & 0xff;
    addr >>= 8;
    buf[2] = addr & 0xff;
    addr >>= 8;
    buf[1] = addr & 0xff;
    buf[4] = 0;
    ssp->RequestWriteRead(SSP_HANDLE_FLASH, buf, wsize, rsize);
    return buf + wsize;
}

uint8_t *At25df641Class::ReadStatusRegister(uint32_t addr)
{
    return buf;
}

uint8_t *At25df641Class::Reset(void)
{
    return buf;
}

uint8_t *At25df641Class::ReadManufacturerId(void)
{
    return buf;
}

uint8_t *At25df641Class::DeepPowerDown(void)
{
    return buf;
}

uint8_t *At25df641Class::ResumePowerDown(void)
{
    return buf;
}
