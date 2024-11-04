/**
 * LPC11U6x timer driver
 */

#include <stdint.h>

#include "lpc11u6x.h"
#include "event.h"

typedef class lpc_ct32_class
{
private:
    Ct32bStruct *ct;
    Event ev[4];

public:
    lpc_ct32_class(uint32_t addr);
    void Init();
    uint32_t GetTimer()
    {
        return ct->tc;
    }
    int SetTimerEvent(int channel, uint32_t delay, Event ev);
    void ClearEvent(int channel) { ct->mcr &= ~(1 << (3 * channel)); }
    Event &GetEvent(int channel) { return ev[channel]; }
    int GetIntMask(void) { return ct->ir; }
    void ServiceInt(int mask) { ct->ir = mask; }
    int GetFirstFreeChannel(void);
} lpc_ct32_t;

extern lpc_ct32_t ct32b0;
extern lpc_ct32_t ct32b1;
