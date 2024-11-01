/**
 *
 */

#include <stdint.h>

#include "event.h"
#include "lpc11u6x_symbols.h"
#include "lpc_ssp.h"

/**
 *
 */
void SetupPeripherals(void)
{
    ssp0.Init();
    ssp1.Init();
}

extern uint32_t iterations;
uint32_t iterations = -1;

/**
 * Main loop
 */
int main(void)
{
    SetupPeripherals();
    // eventInit();

    while (1)
    {
        Event ev;

        while (eventqueue.Pop(ev) == 0)
        {
            switch (ev.cmd)
            {
            case EVENT_SYSTICK:
                iterations++;
                break;

            default:
                break;
            }
        }
        asm("wfi");
    }
}
