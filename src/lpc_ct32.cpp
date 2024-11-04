/**
 * LPC11U6x timer driver
 */

#include <stdint.h>

#include "board.h"
#include "lpc11u6x.h"
#include "lpc_ct32.h"

lpc_ct32_t ct32b0(CT32B0_BASE);
lpc_ct32_t ct32b1(CT32B1_BASE);

/**
 *
 */
lpc_ct32_class::lpc_ct32_class(uint32_t addr)
{
    // Set base address
    ct = (Ct32bStruct *)addr;
}

/**
 *
 */
void lpc_ct32_class::Init(void)
{
    // By default, set to free-running counter
    ct->tcr = 3;
    ct->tcr = 1;
    ct->ctcr = 0x0;
}

int lpc_ct32_class::GetFirstFreeChannel(void)
{
    int ir = ct->ir;

    for (int i = 0; i < 4; i++)
    {
        int mask = (1 << (3 * i));

        if (mask & ir)
        {
            return i;
        }
    }
    return -1;
}

/**
 *
 */
int lpc_ct32_class::SetTimerEvent(int channel, uint32_t delay, Event new_ev)
{
    int ret = -1;

    if ((ct->mcr & (1 << (3 * channel))) == 0)
    {
        NVIC_EnableIRQ((ct == CT32B0) ? IRQ_CT32B0 : IRQ_CT32B1);
        ev[channel] = new_ev;
        ct->mr0 = ct->tc + delay;
        ct->mcr = (1 << (3 * channel));
        ret = 0;
    }
    return ret;
}

/**
 *
 */
void Ct32b1IRQ(void)
{
    int channel;

    for (channel = 0; channel < 4; channel++)
    {
        int mask = (1 << (3 * channel));

        if (ct32b1.GetIntMask() & mask)
        {
            eventqueue.Push(ct32b1.GetEvent(channel));
            ct32b1.ClearEvent(channel);
            ct32b1.ServiceInt(mask);
        }
    }
}

/**
 *
 */
void Ct32b0IRQ(void)
{
    int channel;

    for (channel = 0; channel < 4; channel++)
    {
        int mask = (1 << (3 * channel));

        if (ct32b0.GetIntMask() & mask)
        {
            eventqueue.Push(ct32b0.GetEvent(channel));
            ct32b0.ClearEvent(channel);
            ct32b0.ServiceInt(mask);
        }
    }
}
