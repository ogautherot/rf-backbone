/**
 *
 */

#include <string.h>

#include "lpc11u6x.h"
#include "lpc11u6x_symbols.h"

#pragma GCC optimize("Og")

void ResetISR(void);
__attribute__((noreturn)) void _main(void);

void JmpResetISR(void);
void JmpNmi(void);
void JmpHardFaultISR(void);

void SvcISR(void) __attribute__((weak, alias("DummyISR")));
void PendsvISR(void) __attribute__((weak, alias("DummyISR")));
void SystickISR(void) __attribute__((weak, alias("DummyISR")));
void HardFaultISR(void) __attribute__((weak, alias("DummyISR")));
void Nmi(void) __attribute__((weak, alias("DummyISR")));

void PinInt0IRQ(void) __attribute__((weak, alias("DummyISR")));
void PinInt1IRQ(void) __attribute__((weak, alias("DummyISR")));
void PinInt2IRQ(void) __attribute__((weak, alias("DummyISR")));
void PinInt3IRQ(void) __attribute__((weak, alias("DummyISR")));
void PinInt4IRQ(void) __attribute__((weak, alias("DummyISR")));
void PinInt5IRQ(void) __attribute__((weak, alias("DummyISR")));
void PinInt6IRQ(void) __attribute__((weak, alias("DummyISR")));
void PinInt7IRQ(void) __attribute__((weak, alias("DummyISR")));
void Gint0IRQ(void) __attribute__((weak, alias("DummyISR")));
void Gint1IRQ(void) __attribute__((weak, alias("DummyISR")));
void I2c1IRQ(void) __attribute__((weak, alias("DummyISR")));
void Usart1_4IRQ(void) __attribute__((weak, alias("DummyISR")));
void Usart2_3IRQ(void) __attribute__((weak, alias("DummyISR")));
void Sct0_1IRQ(void) __attribute__((weak, alias("DummyISR")));
void Ssp1IRQ(void) __attribute__((weak, alias("DummyISR")));
void I2c0IRQ(void) __attribute__((weak, alias("DummyISR")));
void Ct16b0IRQ(void) __attribute__((weak, alias("DummyISR")));
void Ct16b1IRQ(void) __attribute__((weak, alias("DummyISR")));
void Ct32b0IRQ(void) __attribute__((weak, alias("DummyISR")));
void Ct32b1IRQ(void) __attribute__((weak, alias("DummyISR")));
void Ssp0IRQ(void) __attribute__((weak, alias("DummyISR")));
void Usart0IRQ(void) __attribute__((weak, alias("DummyISR")));
void UsbIRQ(void) __attribute__((weak, alias("DummyISR")));
void UsbFIQ(void) __attribute__((weak, alias("DummyISR")));
void AdcaIRQ(void) __attribute__((weak, alias("DummyISR")));
void RtcIRQ(void) __attribute__((weak, alias("DummyISR")));
void BodWdtIRQ(void) __attribute__((weak, alias("DummyISR")));
void FlashIRQ(void) __attribute__((weak, alias("DummyISR")));
void DmaIRQ(void) __attribute__((weak, alias("DummyISR")));
void AdcbIRQ(void) __attribute__((weak, alias("DummyISR")));
void UsbWakeupIRQ(void) __attribute__((weak, alias("DummyISR")));

/**
 *
 */
ISR_VECTOR const func vectors[] = {
    (func)_vStackTop, // 0x00
    JmpResetISR,      // 0x04
    JmpNmi,           // 0x08
    JmpHardFaultISR,  // 0x0c
    0,                // 0x10
    0,                // 0x14
    0,                // 0x18
    (func)0xefffdcf1, // 0x1c, checksum

    0,          // 0x20
    0,          // 0x24
    0,          // 0x28
    SvcISR,     // 0x2c
    0,          // 0x30
    0,          // 0x34
    PendsvISR,  // 0x38
    SystickISR, // 0x3c

    PinInt0IRQ,   // 0x40 (0)
    PinInt1IRQ,   // 0x44 (1)
    PinInt2IRQ,   // 0x48 (2)
    PinInt3IRQ,   // 0x4c (3)
    PinInt4IRQ,   // 0x50 (4)
    PinInt5IRQ,   // 0x54 (5)
    PinInt6IRQ,   // 0x58 (6)
    PinInt7IRQ,   // 0x5c (7)
    Gint0IRQ,     // 0x60 (8)
    Gint1IRQ,     // 0x64 (9)
    I2c1IRQ,      // 0x68 (10)
    Usart1_4IRQ,  // 0x6c (11)
    Usart2_3IRQ,  // 0x70 (12)
    Sct0_1IRQ,    // 0x74 (13)
    Ssp1IRQ,      // 0x78 (14)
    I2c0IRQ,      // 0x7c (15)
    Ct16b0IRQ,    // 0x80 (16)
    Ct16b1IRQ,    // 0x84 (17)
    Ct32b0IRQ,    // 0x88 (18)
    Ct32b1IRQ,    // 0x8c (19)
    Ssp0IRQ,      // 0x90 (20)
    Usart0IRQ,    // 0x94 (21)
    UsbIRQ,       // 0x98 (22)
    UsbFIQ,       // 0x9c (23)
    AdcaIRQ,      // 0xa0 (24)
    RtcIRQ,       // 0xa4 (25)
    BodWdtIRQ,    // 0xa8 (26)
    FlashIRQ,     // 0xac (27)
    DmaIRQ,       // 0xb0 (28)
    AdcbIRQ,      // 0xb4 (29)
    UsbWakeupIRQ, // 0xb8 (30)
                  //    Pinint7IRQ   // 0xbc (31)
};

AFTER_VECTORS void JmpResetISR(void)
{
  return ResetISR();
}

AFTER_VECTORS void JmpNmi(void)
{
  return Nmi();
}

AFTER_VECTORS void JmpHardFaultISR(void)
{
  return HardFaultISR();
}

/**
 */
AFTER_VECTORS void DummyISR(void)
{
  while (1)
  {
  }
}

/** Reset vector
 * - Initialize memory
 */
#pragma GCC push_options
#pragma GCC optimize("optimize-sibling-calls")
AFTER_VECTORS void ResetISR(void)
{
  /* Data section */
  uint32_t *dest = __data_section_table.Dest;
  uint32_t *src = __data_section_table.Src;
  uint32_t *end = (uint32_t *)((uint32_t)dest + __data_section_table.Len);

  while (dest < end)
  {
    *dest++ = *src++;
  }

  /* BSS section */
  dest = __bss_section_table.Dest;
  end = (uint32_t *)((uint32_t)dest + __data_section_table.Len);
  while (dest < end)
  {
    *dest++ = 0;
  }

  while (dest < __top_RAM)
  {
    *dest++ = 0;
  }

  // asm(".global _main\n  b _main");
  return _main();
}
#pragma GCC pop_options

AFTER_VECTORS void _cold_reset(void)
{
  uint32_t *dest = __base_resetram;
  uint32_t *end = __top_resetram;

  while (dest < end)
  {
    *dest++ = 0;
  }
}

AFTER_VECTORS void *memset(void *dest, int c, unsigned int n)
{
  uint32_t *ptr32 = dest;
  uint8_t *ptr8;

  while (n >= 4)
  {
    *ptr32 = c;
    ptr32++;
    n -= 4;
  }

  ptr8 = (uint8_t *)ptr32;
  while (n > 0)
  {
    *ptr8 = (uint8_t)c;
    n--;
    ptr8++;
    c = ((uint8_t)c) >> 8;
  }

  return dest;
}

AFTER_VECTORS void *memcpy(void *dest, const void *src, unsigned int n)
{
  const uint32_t *src32 = src;
  uint32_t *dest32 = dest;
  const uint8_t *src8;
  uint8_t *dest8;

  while (n >= 4)
  {
    *dest32++ = *src32++;
    n -= 4;
  }

  dest8 = (uint8_t *)dest32;
  src8 = (uint8_t *)src32;
  while (n > 0)
  {
    *dest8++ = *src8++;
    n--;
  }

  return dest;
}

RESETRAM struct
{
  uint16_t extrst;
  uint16_t wdt;
  uint16_t bod;
  uint16_t sysrst;
} ResetInstances = {0, 0, 0, 0};

AFTER_VECTORS void _main(void)
{
  uint32_t stat = SYSCON->SysRstStat;

  if (1 & stat)
  {
    _cold_reset();
  }
  else if (2 & stat)
  {
    _cold_reset();
    ++ResetInstances.extrst;
  }
  else if (4 & stat)
  {
    ++ResetInstances.wdt;
  }
  else if (8 & stat)
  {
    ++ResetInstances.bod;
  }
  else if (16 & stat)
  {
    ++ResetInstances.sysrst;
  }
  SYSCON->SysRstStat = 0x1f;

  // Run constructors
  do
  {
    const func *constructor = __init_array_start;
    const func *end = __init_array_end;

    while (constructor < end)
    {
      (*constructor)();
      constructor++;
    }
  } while (0);

  SystemInit();

  int status = main();
  exit(status);
}

AFTER_VECTORS void exit(int status)
{
  (void)status;

  // freeze CPU
  while (1)
  {
    asm("wfi");
  }
}