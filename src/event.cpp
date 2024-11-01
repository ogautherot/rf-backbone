
#include <string.h>

#include "event.h"

/**
 *
 */
EventQueue::EventQueue()
{
    idx_in = idx_out = flags = 0;
    memset(queue, 0, sizeof(queue));
}

/**
 *
 */
int EventQueue::Push(Event &ev)
{
    if (eventGetDepth() < EVENT_QUEUE_MASK)
    {
        queue[idx_in] = ev;
        incrIndexIn();
        return 0;
    }

    flags |= EVENT_FLAGS_OVF;
    return -1;
}

/**
 *
 */
int EventQueue::Pop(Event &ev)
{
    if (eventGetDepth() > 0)
    {
        ev = queue[idx_out];
        incrIndexOut();
        return 0;
    }
    return -1;
}

/**
 *
 */
EventQueue eventqueue;
