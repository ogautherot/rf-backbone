/**
 *
 */

#include "lpc11u6x_symbols.h"
#include "event.h"

void SystickISR(void)
{
    Event ev = {.cmd = EVENT_SYSTICK, .arg1 = 0, .arg2 = 0};
    eventqueue.Push(ev);
}
