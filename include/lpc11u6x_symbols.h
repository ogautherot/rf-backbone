/**
 *
 */

#ifndef __LPC11U6X_SYMBOLS_H_INCLUDED__
#define __LPC11U6X_SYMBOLS_H_INCLUDED__

#include <stdint.h>

#define ISR_VECTOR __attribute__((__used__, section(".isr_vector")))
#define AFTER_VECTORS __attribute__((__used__, section(".after_vectors")))
#define RESETRAM __attribute__((__used__, section(".resetram")))

#ifdef __cplusplus
extern "C"
{
#endif

  typedef void (*func)(void);

  /** Structure of the .data initialization parameters
   */
  typedef struct DataSectionsDescriptorStruct
  {
    uint32_t *Src;
    uint32_t *Dest;
    uint32_t Len;
  } DataSectionsDescriptorStruct;

  /** Structure of the .bss initialization parameters
   */
  typedef struct BssSectionsDescriptorStruct
  {
    uint32_t *Dest;
    uint32_t *Len;
  } BssSectionsDescriptorStruct;

  extern __attribute__((section(".isr_vector"))) const func vectors[];

  extern DataSectionsDescriptorStruct __data_section_table;
  extern BssSectionsDescriptorStruct __bss_section_table;

  extern uint32_t __base_RAM[], __top_RAM[];
  extern uint32_t __base_resetram[], __top_resetram[];

  extern const func vectors[];
  extern const func __init_array_start[];
  extern const func __init_array_end[];
  extern uint32_t _vStackTop[];

  void DummyISR(void);
  void Nmi(void);
  void HardFaultISR(void);
  void SystickISR(void);
  void PendsvISR(void);
  void SvcISR(void);

  void PinInt0IRQ(void);
  void PinInt1IRQ(void);
  void PinInt2IRQ(void);
  void PinInt3IRQ(void);
  void PinInt4IRQ(void);
  void PinInt5IRQ(void);
  void PinInt6IRQ(void);
  void PinInt7IRQ(void);
  void Gint0IRQ(void);
  void Gint1IRQ(void);
  void I2c1IRQ(void);
  void Usart1_4IRQ(void);
  void Usart2_3IRQ(void);
  void Sct0_1IRQ(void);
  void Ssp1IRQ(void);
  void I2c0IRQ(void);
  void Ct16b0IRQ(void);
  void Ct16b1IRQ(void);
  void Ct32b0IRQ(void);
  void Ct32b1IRQ(void);
  void Ssp0IRQ(void);
  void Usart0IRQ(void);
  void UsbIRQ(void);
  void UsbFIQ(void);
  void AdcaIRQ(void);
  void RtcIRQ(void);
  void BodWdtIRQ(void);
  void FlashIRQ(void);
  void DmaIRQ(void);
  void AdcbIRQ(void);
  void UsbWakeupIRQ(void);

  int main(void);
  void SystemInit(void);
  void exit(int stat);

  extern uint32_t __base_Sram1[];
  extern uint32_t __top_Sram1[];
  extern uint32_t __base_Sram2[];
  extern uint32_t __top_Sram2[];

#ifdef __cplusplus
}
#endif

#endif // __LPC11U6X_SYMBOLS_H_INCLUDED__
