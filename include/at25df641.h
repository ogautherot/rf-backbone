/**
 *
 */

#include <stdint.h>

#include "lpc_ssp.h"

class At25df641Class
{
private:
    uint8_t buf[160];
    lpc_ssp_t *ssp;

public:
    At25df641Class(lpc_ssp_t *dev);
    uint8_t *ReadPage(uint32_t addr);
    uint8_t *ReadByte(uint32_t addr, uint32_t rsize);
    uint8_t *BlockErase(uint32_t addr);
    uint8_t *ChipErase(void);
    uint8_t *ProgramPage(uint32_t addr);
    uint8_t *ProgramByte(uint32_t addr, uint32_t size);
    uint8_t *WriteEnable(void);
    uint8_t *WriteDisable(void);
    uint8_t *ReadSectorProtection(uint32_t addr);
    uint8_t *ReadStatusRegister(uint32_t addr);
    uint8_t *Reset(void);
    uint8_t *ReadManufacturerId(void);
    uint8_t *DeepPowerDown(void);
    uint8_t *ResumePowerDown(void);
};

extern At25df641Class at25;
