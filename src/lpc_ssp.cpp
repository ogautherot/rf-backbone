/**
 * LPC11U67 SSP driver
 */

#include "lpc_ssp.h"

lpc_ssp_class ssp0(SSP0_BASE);
lpc_ssp_class ssp1(SSP1_BASE);


lpc_ssp_class::lpc_ssp_class(uint32_t addr)
{
    ssp = (SspStruct *) addr;
    handle = 0;
    CsIndex = -1;
}

void lpc_ssp_class::Init(void)
{
    // 8 bits, clock PCLK(SCR + 1) = PCLK/2
    ssp->cr0 = 0x107;

    // Enable port
    ssp->cr1 = 0x02;

    // Release CS of all ports
    GPIO0->pin0 |= (1 << 23) | (1 << 7) | ( 1 << 2);
}

int lpc_ssp_class::Open(int h)
{
    int16_t idx = -1;

    if (0 == handle)    {
        switch (h)  {
        case SSP_HANDLE_ETHERNET:
            idx = SSP_CS_INDEX(0, 7);
            break;

        case SSP_HANDLE_FLASH:
            idx = SSP_CS_INDEX(0, 2);
            break;

        case SSP_HANDLE_RADIO:
            idx = SSP_CS_INDEX(0, 23);
            break;
        }
    }

    if (0 <= idx)   {
        GPIO0->byte_pin0[idx];
        CsIndex = idx;
        handle = h;
    } else {
        h = -1;
    }
    return h;
}

int lpc_ssp_class::Close(int h)
{
    if (h != handle)    {
        h = -1;
    } else {
        handle = 0;
        CsIndex = -1;
    }
    return h;
}

int32_t lpc_ssp_class::ReadByte() {
    return (4 & ssp->sr) ? ssp->dr : -1; 
}

int lpc_ssp_class::WriteByte(uint8_t v)   {
    if (0 == (2 & ssp->sr))    {
        return -1;
    }
    ssp->dr = v;
    return 0;
}
