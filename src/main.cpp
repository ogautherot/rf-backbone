/**
 *
 */

#include <stdint.h>

#include "lpc11u6x.h"
#include "event.h"
#include "lpc11u6x_symbols.h"
#include "lpc_ssp.h"
#include "lpc_ct32.h"

extern volatile uint32_t iterations;
volatile uint32_t iterations = -1;

/**
 *
 */
void SetupPeripherals(void)
{
    Event ev_timer = {EVENT_TIMER1, 0, 0};
    volatile NvicStruct *nvic = NVIC;

    nvic->icer0 = 0xffffffff;
    // nvic->iser0 = (1 << IRQ_CT32B0) | (1 << IRQ_CT32B1);
    asm volatile("cpsie i" : : : "memory");
    ssp0.Init();
    ssp1.Init();
    ct32b0.Init();
    ct32b1.Init();
    ct32b1.SetTimerEvent(0, 96000000, ev_timer);
}

/**
 * Main loop
 */
int main(void)
{
    SetupPeripherals();

    while (1)
    {
        Event ev;

        while (eventqueue.Pop(ev) == 0)
        {
            switch (ev.cmd)
            {
            case EVENT_SYSTICK:
                iterations = 1;
                break;

            case EVENT_TIMER0:
                iterations = 2;
                break;

            case EVENT_TIMER1:
                iterations = 3;
                break;

            case EVENT_SSP0:
                iterations = 4;
                break;

            case EVENT_SSP1:
                iterations = 5;
                break;

            default:
                break;
            }
        }
        asm("wfi");
    }
}
