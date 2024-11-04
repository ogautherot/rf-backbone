/**
 * LPC11U67 SSP driver
 */

#include <string.h>

#include "lpc_ssp.h"

lpc_ssp_class ssp0(SSP0_BASE);
lpc_ssp_class ssp1(SSP1_BASE);

lpc_ssp_class::lpc_ssp_class(uint32_t addr)
{
    ssp = (SspStruct *)addr;
    handle = 0;
    CsIndex = -1;
}

void lpc_ssp_class::Init(void)
{
    // 8 bits, clock PCLK(SCR + 1) = PCLK/2
    ssp->cr0 = 0x07; // 0x107;

    // Enable port
    ssp->cr1 = 0x02;
    ssp->cpsr = 0x02;

    // Release CS of all ports
    GPIO0->pin0 |= (1 << 23) | (1 << 7) | (1 << 2);
}

#ifdef NEVER
int lpc_ssp_class::Open(int h)
{
    int16_t idx = -1;

    if (0 == handle)
    {
        switch (h)
        {
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

    if (0 <= idx)
    {
        GPIO0->byte_pin0[idx] = 0;
        CsIndex = idx;
        handle = h;
    }
    else
    {
        h = -1;
    }
    return h;
}
#else
static int ConvertHandleToCs(int handle, uint8_t &cs)
{
    const struct
    {
        uint8_t h;
        uint8_t cs;
    } tab[] = {
        {SSP_HANDLE_ETHERNET, SSP_CS_INDEX(0, 7)},
        {SSP_HANDLE_FLASH, SSP_CS_INDEX(0, 2)},
        {SSP_HANDLE_RADIO, SSP_CS_INDEX(0, 23)}};
    uint32_t i;
    int ret = -1;

    for (i = 0; i < sizeof(tab) / sizeof(tab[0]); i++)
    {
        if (tab[i].h == handle)
        {
            cs = tab[i].cs;
            ret = 0;
        }
    }
    return ret;
}

int lpc_ssp_class::Open(int h)
{
    uint8_t idx;
    int ret = ConvertHandleToCs(h, idx);

    if (0 == ret)
    {
        GPIO0->byte_pin0[idx] = 0;
        CsIndex = idx;
        handle = h;
    }
    return ret;
}
#endif
/**
 *
 * */
int lpc_ssp_class::Close(int h)
{
    if (h == handle)
    {
        GPIO0->byte_pin0[CsIndex] = 1;
        CsIndex = -1;
        handle = 0;
    }
    else
    {
        h = -1;
    }
    return h;
}

/**
 *
 */
int32_t lpc_ssp_class::ReadByte()
{
    return (4 & ssp->sr) ? ssp->dr : -1;
}

/**
 *
 */
int lpc_ssp_class::WriteByte(uint8_t v)
{
    if (0 == (2 & ssp->sr))
    {
        return -1;
    }
    ssp->dr = v;
    return 0;
}

#ifdef NEVER
/**
 *
 */
uint8_t TestBuffer[16];

/**
 *
 */
void lpc_ssp_class::Test(void)
{
    uint8_t *ptr = TestBuffer;
    uint8_t cmd = 0x9f;

    memset(TestBuffer, 0, sizeof(TestBuffer));

    Open(SSP_HANDLE_FLASH);
    while (ptr < &TestBuffer[5])
    {
        ssp->dr = cmd;
        while (ssp->sr & 0x10)
            ;
        *ptr = ssp->dr;
        ptr++;
        cmd = 0x00;
    }
    Close(SSP_HANDLE_FLASH);
}
#endif

/**
 *
 */
void Ssp0IRQ(void)
{
    while (1)
        ;
}

/**
 *
 */
void Ssp1IRQ(void)
{
    while (1)
        ;
}
