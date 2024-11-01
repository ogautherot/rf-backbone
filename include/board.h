/**
 * Board descriptor
 * 
 * PIO0_0:              Reset
 * PIO0_1:              CLKOUT
 * PIO0_2:              SSP0_SSEL
 * PIO0_{3,4,5}:        N.U.
 * PIO0_6:              SSP0_SCK
 * PIO0_7:              Ethernet_SSEL
 * PIO0_8:              SSP0_MISO
 * PIO0_9:              SSP0_MOSI
 * PIO0_10:             SWCLK
 * PIO0_{11,12,13,14}:  N.U.
 * PIO0_15:             SWDIO
 * PIO0_16:             RF_RSSIO (ADC2)
 * PIO0_17:             RS485_DIR
 * PIO0_18:             RS485_TXD
 * PIO0_19:             RS485_RXD
 * PIO0_20:             N.U.
 * PIO0_21:             RF_SDI
 * PIO0_22:             RF_IRO
 * PIO0_23:             RF_CS
 * 
 * PIO1_13:             RF_RESET
 * PIO1_20:             RF_SCK (SSP1)
 * PIO1_21:             RF_SDO (SSP1)
 * PIO1_{23,24}:        N.U.
 * 
 * PIO2_2:              RF_FINT
 * PIO2_5:              N.U.
 * PIO2_7:              ETH_INT
 * 
 * Modules used: SSP0 (shared), SSP1, UART0 (RS485), ADC
 */

#ifndef __BOARD_H_INCLUDED__
#define __BOARD_H_INCLUDED__

#ifdef NEVER
#include "usbd_rom_api.h"
#include "usbd.h"
#include "usbd_core.h"
#include "usbd_mscuser.h"
#include "usbd_dfuuser.h"
#include "usbd_hiduser.h"
#include "usbd_cdcuser.h"
#endif

#include "lpc11u6x.h"
//#include "lpc11u6x_resources.h"
#include "lpc11u6x_symbols.h"

void SystemCoreClockUpdate(void);
//void Board_Init(void);
void Chip_USB_Init(void);
void NVIC_EnableIRQ(uint32_t vector);
void NVIC_DisableIRQ(uint32_t vector);
//void Board_SystemInit(void);

#endif // __BOARD_H_INCLUDED__
