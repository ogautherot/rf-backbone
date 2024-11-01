/*
 */

#ifndef _EVENT_H_
#define _EVENT_H_

#include <stdint.h>

#define EVENT_QUEUE_SIZE 32U
#define EVENT_QUEUE_MASK (EVENT_QUEUE_SIZE - 1)

#define EVENT_FLAGS_OVF 1

/**
 *
 */
typedef enum eventEnum
{
    EVENT_NOP = 0,
    EVENT_SYSTICK, // 1
} eventEnum;

/**
 *
 */
typedef struct Event
{
    uint8_t cmd;
    uint8_t arg1;
    uint16_t arg2;
} Event;

/**
 *
 */
typedef class EventQueue
{
public:
    /**
     *
     */
    EventQueue();

    /**
     *
     */
    uint32_t eventGetDepth()
    {
        return (idx_in - idx_out) & EVENT_QUEUE_MASK;
    }

    /**
     *
     */
    int Append(uint8_t c, uint8_t a1, uint16_t a2)
    {
        Event ev = {.cmd = c, .arg1 = a1, .arg2 = a2};
        return Push(ev);
    }

    /**
     *
     */
    int Push(Event &ev);

    /**
     *
     */
    int Pop(Event &ev);

private:
    /**
     *
     */
    Event queue[EVENT_QUEUE_SIZE];
    /**
     *
     */
    uint16_t idx_in;
    /**
     *
     */
    uint16_t idx_out;

    /**
     *
     */
    uint16_t flags;

    /**
     *
     */
    uint16_t incrIndexIn()
    {
        return idx_in = (idx_in + 1) & EVENT_QUEUE_MASK;
    }

    /**
     *
     */
    uint16_t incrIndexOut()
    {
        return idx_out = (idx_out + 1) & EVENT_QUEUE_MASK;
    }

} EventQueue;

/**
 *
 */
extern EventQueue eventqueue;

#endif // _EVENT_H_
