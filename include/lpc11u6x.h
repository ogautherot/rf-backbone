/**
 * LPC824 registers mapping
 */

#ifndef __LPC11U67_H_INCLUDED__
#define __LPC11U67_H_INCLUDED__

#include <stdint.h>

#define __I volatile
#define __IO volatile
#define __O volatile const

/* Base address of the various peripherals
 * */

#define I2C0_BASE (0x40000000)
#define WWDT_BASE (0x40004000)
#define USART0_BASE (0x40008000)
#define CT16B0_BASE (0x4000c000)
#define CT16B1_BASE (0x40010000)
#define CT32B0_BASE (0x40014000)
#define CT32B1_BASE (0x40018000)
#define ADC_BASE (0x4001c000)
#define I2C1_BASE (0x40020000)
#define RTC_BASE (0x40024000)
#define DMA_TRIGMUX_BASE (0x40028000)
#define PMU_BASE (0x40038000)
#define FLASH_CTLR_BASE (0x4003c000)
#define SSP0_BASE (0x40040000)
#define IOCON_BASE (0x40044000)
#define SYSCON_BASE (0x40048000)
#define USART4_BASE (0x4004c000)
#define SSP1_BASE (0x40058000)
#define GPIO_GRP0_BASE (0x4005c000)
#define GPIO_GRP1_BASE (0x40060000)
#define USART1_BASE (0x4006c000)
#define USART2_BASE (0x40070000)
#define USART3_BASE (0x40074000)
#define USB0_BASE (0x40080000)
#define CRC_BASE (0x50000000)
#define DMA_BASE (0x50004000)
#define SCT0_BASE (0x5000c000)
#define SCT1_BASE (0x5000e000)
#define GPIO0_BASE (0xa0000000)      // GPIO
#define GPIO0_PINT_BASE (0xa0004000) // GPIO PINT

#define NVIC_BASE (0xe000e000)

// MTB - Micro-Trace Buffer


// CT16B

typedef struct Ct16bStruct
{
  __IO uint32_t ir;  // 0x00
  __IO uint32_t tcr; // 0x04
  __IO uint32_t tc;  // 0x08
  __IO uint32_t pr;  // 0x0c
  __IO uint32_t pc;  // 0x10
  __IO uint32_t mcr; // 0x14
  __IO uint32_t mr0; // 0x18
  __IO uint32_t mr1; // 0x1c

  __IO uint32_t mr2; // 0x20
  __IO uint32_t mr3; // 0x24
  __IO uint32_t ccr; // 0x28
  __IO uint32_t cr0; // 0x2c
  __IO uint32_t cr1; // 0x30
  __IO uint32_t cr2; // 0x34, CT16B0 only
  uint32_t : 32;     // 0x38
  __IO uint32_t emr; // 0x3c

  uint32_t : 32; // 0x40
  uint32_t : 32; // 0x44
  uint32_t : 32; // 0x48
  uint32_t : 32; // 0x4c
  uint32_t : 32; // 0x50
  uint32_t : 32; // 0x54
  uint32_t : 32; // 0x58
  uint32_t : 32; // 0x5c

  uint32_t : 32;      // 0x60
  uint32_t : 32;      // 0x64
  uint32_t : 32;      // 0x68
  uint32_t : 32;      // 0x6c
  __IO uint32_t ctcr; // 0x70
  __IO uint32_t pmwc; // 0x74
} Ct16bStruct;

#define CT16B0 ((volatile Ct16bStruct *)CT16B0_BASE)
#define CT16B1 ((volatile Ct16bStruct *)CT16B1_BASE)

// CT32B

typedef struct Ct32bStruct
{
  __IO uint32_t ir;  // 0x00
  __IO uint32_t tcr; // 0x04
  __IO uint32_t tc;  // 0x08
  __IO uint32_t pr;  // 0x0c
  __IO uint32_t pc;  // 0x10
  __IO uint32_t mcr; // 0x14
  __IO uint32_t mr0; // 0x18
  __IO uint32_t mr1; // 0x1c

  __IO uint32_t mr2; // 0x20
  __IO uint32_t mr3; // 0x24
  __IO uint32_t ccr; // 0x28
  __IO uint32_t cr0; // 0x2c
  __IO uint32_t cr1; // 0x30
  __IO uint32_t cr2; // 0x34, CT32B0 only
  uint32_t : 32;     // 0x38
  __IO uint32_t emr; // 0x3c

  uint32_t : 32; // 0x40
  uint32_t : 32; // 0x44
  uint32_t : 32; // 0x48
  uint32_t : 32; // 0x4c
  uint32_t : 32; // 0x50
  uint32_t : 32; // 0x54
  uint32_t : 32; // 0x58
  uint32_t : 32; // 0x5c

  uint32_t : 32;      // 0x60
  uint32_t : 32;      // 0x64
  uint32_t : 32;      // 0x68
  uint32_t : 32;      // 0x6c
  __IO uint32_t ctcr; // 0x70
  __IO uint32_t pmwc; // 0x74
} Ct32bStruct;

#define CT32B0 ((volatile Ct32bStruct *)CT32B0_BASE)
#define CT32B1 ((volatile Ct32bStruct *)CT32B1_BASE)

// RTC

typedef struct RtcStruct
{
  __IO uint32_t ctrl;  // 0x00
  __IO uint32_t match; // 0x04
  __IO uint32_t count; // 0x08
  __IO uint32_t wake;  // 0x0c
} RtcStruct;

#define RTC ((volatile RtcStruct *)RTC_BASE)

// WWDT - Windowed Watch Dog Timer

typedef struct WwdtStruct
{
  __IO uint32_t mod;     // 0x00
  __IO uint32_t tc;      // 0x04
  __I uint32_t feed;     // 0x08
  __O uint32_t tv;       // 0x0c
  __IO uint32_t clksel;  // 0x10
  __IO uint32_t warnint; // 0x14
  __IO uint32_t window;  // 0x18
} WwdtStruct;

#define WWDT ((volatile WwdtStruct *)WWDT_BASE)

// ADC

typedef struct AdcStruct
{
  __IO uint32_t ctrl;        // 0x00
  uint32_t : 32;             // 0x04
  __IO uint32_t seqa_ctrl;   // 0x08
  __IO uint32_t seqb_ctrl;   // 0x0c
  __IO uint32_t seqa_gdat;   // 0x10
  __IO uint32_t seqb_gdat;   // 0x14
  uint32_t : 32;             // 0x18
  uint32_t : 32;             // 0x1c
  __O uint32_t dat0;         // 0x20
  __O uint32_t dat1;         // 0x24
  __O uint32_t dat2;         // 0x28
  __O uint32_t dat3;         // 0x2c
  __O uint32_t dat4;         // 0x30
  __O uint32_t dat5;         // 0x34
  __O uint32_t dat6;         // 0x38
  __O uint32_t dat7;         // 0x3c
  __O uint32_t dat8;         // 0x40
  __O uint32_t dat9;         // 0x44
  __O uint32_t dat10;        // 0x48
  __O uint32_t dat11;        // 0x4c
  __IO uint32_t thr0_low;    // 0x50
  __IO uint32_t thr1_low;    // 0x54
  __IO uint32_t thr0_high;   // 0x58
  __IO uint32_t thr1_high;   // 0x5c
  __IO uint32_t chan_thrsel; // 0x60
  __IO uint32_t inten;       // 0x64
  __IO uint32_t flags;       // 0x68
  __IO uint32_t trm;         // 0x6c
} AdcStruct;

#define ADC ((volatile AdcStruct *)ADC_BASE)

// PMU

typedef struct PmuStruct
{
  __IO uint32_t pcon;    // 0x00
  __IO uint32_t gpreg0;  // 0x04
  __IO uint32_t gpreg1;  // 0x08
  __IO uint32_t gpreg2;  // 0x0c
  __IO uint32_t gpreg3;  // 0x10
  __IO uint32_t dpdctrl; // 0x14
} PmuStruct;

#define PMU ((volatile PmuStruct *)PMU_BASE)

// DMA Trigger Mux

typedef struct DmaTrigMuxStruct
{
  __IO uint32_t inmux0;  // 0x00
  __IO uint32_t inmux1;  // 0x04
  __IO uint32_t inmux2;  // 0x08
  __IO uint32_t inmux3;  // 0x0c
  __IO uint32_t inmux4;  // 0x10
  __IO uint32_t inmux5;  // 0x14
  __IO uint32_t inmux6;  // 0x18
  __IO uint32_t inmux7;  // 0x1c
  __IO uint32_t inmux8;  // 0x20
  __IO uint32_t inmux9;  // 0x24
  __IO uint32_t inmux10; // 0x28
  __IO uint32_t inmux11; // 0x2c
  __IO uint32_t inmux12; // 0x30
  __IO uint32_t inmux13; // 0x34
  __IO uint32_t inmux14; // 0x38
  __IO uint32_t inmux15; // 0x3c
} DmaTrigMuxStruct;

#define DMA_TRIGMUX ((volatile DmaTrigMuxStruct *)DMA_TRIGMUX_BASE)

// Flash controller

typedef struct FlashCtlStruct
{
  uint32_t : 32;          // 0x00
  uint32_t : 32;          // 0x04
  uint32_t : 32;          // 0x08
  __IO uint32_t flashcfg; // 0x0c
  uint32_t : 32;          // 0x10
  uint32_t : 32;          // 0x14
  uint32_t : 32;          // 0x18
  uint32_t : 32;          // 0x1c
  __IO uint32_t fmsstart; // 0x20
  __IO uint32_t fmsstop;  // 0x24
  uint32_t : 32;          // 0x28
  __O uint32_t fmsw0;     // 0x2c
} FlashCtrlStruct;

#define FLASH_CTRL ((volatile FlashCtrlStruct *)FLASH_CTRL_BASE)

// IOCON

typedef struct IoconStruct
{
  __IO uint32_t reset_pio0_0; // 0x00
  __IO uint32_t pio0_01;      // 0x04
  __IO uint32_t pio0_02;      // 0x08
  __IO uint32_t pio0_03;      // 0x0c
  __IO uint32_t pio0_04;      // 0x10
  __IO uint32_t pio0_05;      // 0x14
  __IO uint32_t pio0_06;      // 0x18
  __IO uint32_t pio0_07;      // 0x1c

  __IO uint32_t pio0_08;       // 0x20
  __IO uint32_t pio0_09;       // 0x24
  __IO uint32_t swclk_pio0_10; // 0x28
  __IO uint32_t tdi_pio0_11;   // 0x2c
  __IO uint32_t tms_pio0_12;   // 0x30
  __IO uint32_t tdo_pio0_13;   // 0x34
  __IO uint32_t trst_pio0_14;  // 0x38
  __IO uint32_t swdio_pio0_15; // 0x3c

  __IO uint32_t pio0_16; // 0x40
  __IO uint32_t pio0_17; // 0x44
  __IO uint32_t pio0_18; // 0x48
  __IO uint32_t pio0_19; // 0x4c
  __IO uint32_t pio0_20; // 0x50
  __IO uint32_t pio0_21; // 0x54
  __IO uint32_t pio0_22; // 0x58
  __IO uint32_t pio0_23; // 0x5c

  __IO uint32_t pio1_00; // 0x60
  __IO uint32_t pio1_01; // 0x64
  __IO uint32_t pio1_02; // 0x68
  __IO uint32_t pio1_03; // 0x6c
  __IO uint32_t pio1_04; // 0x70
  __IO uint32_t pio1_05; // 0x74
  __IO uint32_t pio1_06; // 0x78
  __IO uint32_t pio1_07; // 0x7c

  __IO uint32_t pio1_08; // 0x80
  __IO uint32_t pio1_09; // 0x84
  __IO uint32_t pio1_10; // 0x88
  __IO uint32_t pio1_11; // 0x8c
  __IO uint32_t pio1_12; // 0x90
  __IO uint32_t pio1_13; // 0x94
  __IO uint32_t pio1_14; // 0x98
  __IO uint32_t pio1_15; // 0x9c

  __IO uint32_t pio1_16; // 0xa0
  __IO uint32_t pio1_17; // 0xa4
  __IO uint32_t pio1_18; // 0xa8
  __IO uint32_t pio1_19; // 0xac
  __IO uint32_t pio1_20; // 0xb0
  __IO uint32_t pio1_21; // 0xb4
  __IO uint32_t pio1_22; // 0xb8
  __IO uint32_t pio1_23; // 0xbc

  __IO uint32_t pio1_24; // 0xc0
  __IO uint32_t pio1_25; // 0xc4
  __IO uint32_t pio1_26; // 0xc8
  __IO uint32_t pio1_27; // 0xcc
  __IO uint32_t pio1_28; // 0xd0
  __IO uint32_t pio1_29; // 0xd4
  __IO uint32_t pio1_30; // 0xd8
  __IO uint32_t pio1_31; // 0xdc

  uint32_t : 32;         // 0xe0
  uint32_t : 32;         // 0xe4
  uint32_t : 32;         // 0xe8
  uint32_t : 32;         // 0xec
  __IO uint32_t pio2_00; // 0xf0
  __IO uint32_t pio2_01; // 0xf4
  uint32_t : 32;         // 0xf8
  __IO uint32_t pio2_02; // 0xfc

  __IO uint32_t pio2_03; // 0x100
  __IO uint32_t pio2_04; // 0x104
  __IO uint32_t pio2_05; // 0x108
  __IO uint32_t pio2_06; // 0x10c
  __IO uint32_t pio2_07; // 0x110
  __IO uint32_t pio2_08; // 0x114
  __IO uint32_t pio2_09; // 0x118
  __IO uint32_t pio2_10; // 0x11c

  __IO uint32_t pio2_11; // 0x120
  __IO uint32_t pio2_12; // 0x124
  __IO uint32_t pio2_13; // 0x128
  __IO uint32_t pio2_14; // 0x12c
  __IO uint32_t pio2_15; // 0x130
  __IO uint32_t pio2_16; // 0x134
  __IO uint32_t pio2_17; // 0x138
  __IO uint32_t pio2_18; // 0x13c

  __IO uint32_t pio2_19; // 0x140
  __IO uint32_t pio2_20; // 0x144
  __IO uint32_t pio2_21; // 0x148
  __IO uint32_t pio2_22; // 0x14c
  __IO uint32_t pio2_23; // 0x150

} IoconStruct;

#define IOCON ((volatile IoconStruct *)IOCON_BASE)

// SYSCON
typedef struct SysConStruct
{
  __IO uint32_t SysMemRemap; // 0x000
  __IO uint32_t PResetCtrl;  // 0x004
  __IO uint32_t SysPllCtrl;  // 0x008
  __O uint32_t SysPllStat;   // 0x00c
  __IO uint32_t UsbPllCtrl;  // 0x010
  __O uint32_t UsbPllStat;   // 0x014
  uint32_t : 32;             // 0x018
  __IO uint32_t RtcOscCtrl;  // 0x01c

  __IO uint32_t SysOscCtrl; // 0x020
  __IO uint32_t WdtOscCtrl; // 0x024
  __IO uint32_t IrcCtrl;    // 0x028
  uint32_t : 32;            // 0x02c
  __IO uint32_t SysRstStat; // 0x030
  uint32_t : 32;            // 0x034
  uint32_t : 32;            // 0x038
  uint32_t : 32;            // 0x03c

  __IO uint32_t SysPllClkSel; // 0x040
  __IO uint32_t SysPllClkUEn; // 0x044
  __IO uint32_t UsbPllClkSel; // 0x048
  __IO uint32_t UsbPllClkUEn; // 0x04c
  uint32_t : 32;              // 0x050
  uint32_t : 32;              // 0x054
  uint32_t : 32;              // 0x058
  uint32_t : 32;              // 0x05c

  uint32_t : 32;              // 0x060
  uint32_t : 32;              // 0x064
  uint32_t : 32;              // 0x068
  uint32_t : 32;              // 0x06c
  __IO uint32_t MainClkSel;   // 0x070
  __IO uint32_t MainClkUEn;   // 0x074
  __IO uint32_t SysAhbClkDiv; // 0x078
  uint32_t : 32;              // 0x07c

  __IO uint32_t SysAhbClkCtrl; // 0x080
  uint32_t : 32;               // 0x084
  uint32_t : 32;               // 0x088
  uint32_t : 32;               // 0x08c
  uint32_t : 32;               // 0x90
  __IO uint32_t Ssp0ClkDiv;    // 0x094
  __IO uint32_t Usart0ClkDiv;  // 0x098
  __IO uint32_t Ssp1ClkDiv;    // 0x09c

  __IO uint32_t FrgClkDiv; // 0x0a0
  uint32_t : 32;           // 0x0a4
  uint32_t : 32;           // 0x0a8
  uint32_t : 32;           // 0x0ac
  uint32_t : 32;           // 0x0b0
  uint32_t : 32;           // 0x0b4
  uint32_t : 32;           // 0x0b8
  uint32_t : 32;           // 0x0bc

  __IO uint32_t UsbClkSel; // 0x0c0
  __IO uint32_t UsbClkUen; // 0x0c4
  __IO uint32_t UsbClkDiv; // 0x0c8
  uint32_t : 32;           // 0x0cc
  uint32_t : 32;           // 0x0d0
  uint32_t : 32;           // 0x0d4
  uint32_t : 32;           // 0x0d8
  uint32_t : 32;           // 0x0dc

  __IO uint32_t ClkOutSel;   // 0x0e0
  __IO uint32_t ClkOutUEn;   // 0x0e4
  __IO uint32_t ClkOutDiv;   // 0x0e8
  uint32_t : 32;             // 0x0ec
  __IO uint32_t UartFrgDiv;  // 0x0f0
  __IO uint32_t UartFrgMult; // 0x0f4
  uint32_t : 32;             // 0x0f8
  __IO uint32_t ExtTraceCmd; // 0x0fc

  __O uint32_t PioPorCap0; // 0x100
  __O uint32_t PioPorCap1; // 0x104
  __O uint32_t PioPorCap2; // 0x108
  uint32_t : 32;           // 0x10c
  uint32_t : 32;           // 0x110
  uint32_t : 32;           // 0x114
  uint32_t : 32;           // 0x118
  uint32_t : 32;           // 0x11c

  uint32_t : 32;              // 0x120
  uint32_t : 32;              // 0x124
  uint32_t : 32;              // 0x128
  uint32_t : 32;              // 0x12c
  uint32_t : 32;              // 0x130
  __IO uint32_t IoConClkDiv6; // 0x134
  __IO uint32_t IoConClkDiv5; // 0x138
  __IO uint32_t IoConClkDiv4; // 0x13c

  __IO uint32_t IoConClkDiv3; // 0x140
  __IO uint32_t IoConClkDiv2; // 0x144
  __IO uint32_t IoConClkDiv1; // 0x148
  __IO uint32_t IoConClkDiv0; // 0x14c
  __IO uint32_t BodCtrl;      // 0x150
  __IO uint32_t SysTckCal;    // 0x154
  uint32_t : 32;              // 0x158
  uint32_t : 32;              // 0x15c

  uint32_t : 32;            // 0x160
  uint32_t : 32;            // 0x164
  uint32_t : 32;            // 0x168
  uint32_t : 32;            // 0x16c
  __IO uint32_t IrqLatency; // 0x170
  __IO uint32_t NmiSrc;     // 0x174
  __IO uint32_t PintSel0;   // 0x178
  __IO uint32_t PintSel1;   // 0x17c

  __IO uint32_t PintSel2;   // 0x180
  __IO uint32_t PintSel3;   // 0x184
  __IO uint32_t PintSel4;   // 0x188
  __IO uint32_t PintSel5;   // 0x18c
  __IO uint32_t PintSel6;   // 0x190
  __IO uint32_t PintSel7;   // 0x194
  __IO uint32_t UsbClkCtrl; // 0x198
  __IO uint32_t UsbClkSt;   // 0x19c

  uint32_t : 32; // 0x1a0
  uint32_t : 32; // 0x1a4
  uint32_t : 32; // 0x1a8
  uint32_t : 32; // 0x1ac
  uint32_t : 32; // 0x1b0
  uint32_t : 32; // 0x1b4
  uint32_t : 32; // 0x1b8
  uint32_t : 32; // 0x1bc

  uint32_t : 32; // 0x1c0
  uint32_t : 32; // 0x1c4
  uint32_t : 32; // 0x1c8
  uint32_t : 32; // 0x1cc
  uint32_t : 32; // 0x1d0
  uint32_t : 32; // 0x1d4
  uint32_t : 32; // 0x1d8
  uint32_t : 32; // 0x1dc

  uint32_t : 32; // 0x1e0
  uint32_t : 32; // 0x1e4
  uint32_t : 32; // 0x1e8
  uint32_t : 32; // 0x1ec
  uint32_t : 32; // 0x1f0
  uint32_t : 32; // 0x1f4
  uint32_t : 32; // 0x1f8
  uint32_t : 32; // 0x1fc

  uint32_t : 32;           // 0x200
  __IO uint32_t StarterP0; // 0x204
  uint32_t : 32;           // 0x208
  uint32_t : 32;           // 0x20c
  uint32_t : 32;           // 0x210
  __IO uint32_t StarterP1; // 0x214
  uint32_t : 32;           // 0x218
  uint32_t : 32;           // 0x21c

  uint32_t : 32;            // 0x220
  uint32_t : 32;            // 0x224
  uint32_t : 32;            // 0x228
  uint32_t : 32;            // 0x22c
  __IO uint32_t PdSleepCfg; // 0x230
  __IO uint32_t PdAwakeCfg; // 0x234
  __IO uint32_t PdRunCfg;   // 0x238
  uint32_t : 32;            // 0x23c

  uint32_t Reserved15[108]; // 0x240

  uint32_t : 32;         // 0x3f0
  uint32_t : 32;         // 0x3f4
  __O uint32_t DeviceId; // 0x3f8
} SysConStruct;

#define SYSCON ((volatile SysConStruct *)SYSCON_BASE)

// I2C 0/1

typedef  struct I2cStruct
{

  __IO uint32_t conset; // 0x00
  __O uint32_t stat;    // 0x04
  __IO uint32_t dat;    // 0x08
  __IO uint32_t adr0;   // 0x0c
  __IO uint32_t sclh;   // 0x10
  __IO uint32_t scll;   // 0x14
  __I uint32_t conclr;  // 0x18
  __IO uint32_t mmctrl; // 0x1c

  __IO uint32_t adr1;       // 0x20
  __IO uint32_t adr2;       // 0x24
  __IO uint32_t adr3;       // 0x28
  __O uint32_t data_buffer; // 0x2c
  __IO uint32_t mask0;      // 0x30
  __IO uint32_t mask1;      // 0x34
  __IO uint32_t mask2;      // 0x38
  __IO uint32_t mask3;      // 0x3c
} I2cStruct;

#define I2C0 ((volatile I2cStruct *)I2C0_BASE)
#define I2C1 ((volatile I2cStruct *)I2C1_BASE)

// SSP 0/1

typedef struct SspStruct
{
  __IO uint32_t cr0;  // 0x00
  __IO uint32_t cr1;  // 0x04
  __IO uint32_t dr;   // 0x08
  __O uint32_t sr;    // 0x0c
  __IO uint32_t cpsr; // 0x10
  __IO uint32_t imsc; // 0x14
  __IO uint32_t ris;  // 0x18
  __IO uint32_t mis;  // 0x1c

  __IO uint32_t icr;   // 0x20
  __IO uint32_t dmacr; // 0x24
} SspStruct;

#define SSP0 ((volatile SspStruct *)SSP0_BASE)
#define SSP1 ((volatile SspStruct *)SSP1_BASE)

// USART 0/1/2/3/4

typedef struct Usart0Struct
{
  union
  {                    // 0x00
    __O uint32_t rbr;  // DLAB=0, receiver buffer register
    __I uint32_t thr;  // DLAB=0, transmit holding register
    __IO uint32_t dll; // DLAB=1, divisor latch LSB
  };
  union
  {                    // 0x04
    __IO uint32_t ier; // DLAB=0, interrupt enable register
    __IO uint32_t dlm; // DLAB=1, divisor latch MSB
  };
  union
  {                   // 0x08
    __O uint32_t iir; // Interrupt ID register
    __I uint32_t fcr; // FIFO control register
  };
  __IO uint32_t lcr; // 0x0c, line control register
  __IO uint32_t mcr; // 0x10, modem control register
  __IO uint32_t lsr; // 0x14, line status register
  __IO uint32_t msr; // 0x18, modem status register
  __IO uint32_t scr; // 0x1c, scratch pad register

  __IO uint32_t acr; // 0x20, auto-baud control
  __IO uint32_t icr; // 0x24
  __IO uint32_t fdr; // 0x28, fractional divider register
  __IO uint32_t osr; // 0x2c
  __IO uint32_t ter; // 0x30, transmit enable register
  uint32_t : 32;     // 0x34
  uint32_t : 32;     // 0x38
  uint32_t : 32;     // 0x3c

  __IO uint32_t hden;           // 0x40
  uint32_t : 32;                // 0x44
  __IO uint32_t scictrl;        // 0x48
  __IO uint32_t rs485ctrl;      // 0x4c, mode control
  __IO uint32_t rs485addrmatch; // 0x50, address match
  __IO uint32_t rs485dly;       // 0x54, direction control delay
  __IO uint32_t syncctrl;       // 0x58
} Usart0Struct;

#define UART0 ((volatile Usart0Struct *)USART0_BASE)

// USART 1/2/3/4

// USART 0/1/2

typedef struct UsartStruct
{
  __IO uint32_t cfg;      // 0x00
  __IO uint32_t ctl;      // 0x04
  __IO uint32_t stat;     // 0x08
  __IO uint32_t intenset; // 0x0c
  __I uint32_t intenclr;  // 0x10
  __O uint32_t rxdat;     // 0x14
  __O uint32_t rxdatstat; // 0x18
  __IO uint32_t txdat;    // 0x1c

  __IO uint32_t brg;    // 0x20
  __O uint32_t intstat; // 0x24
  __IO uint32_t osr;    // 0x28
  __IO uint32_t addr;   // 0x2c
} UsartStruct;

#define UART1 ((volatile UsartStruct *)USART1_BASE)
#define UART2 ((volatile UsartStruct *)USART2_BASE)
#define UART3 ((volatile UsartStruct *)USART3_BASE)
#define UART4 ((volatile UsartStruct *)USART4_BASE)

// USB

typedef struct UsbStruct
{
  __IO uint32_t devcmdstat;   // 0x00
  __IO uint32_t info;         // 0x04
  __IO uint32_t epliststart;  // 0x08
  __IO uint32_t databufstart; // 0x0c
  __IO uint32_t lpm;          // 0x10
  __IO uint32_t epskip;       // 0x14
  __IO uint32_t epinuse;      // 0x18
  __IO uint32_t epbufcfg;     // 0x1c

  __IO uint32_t intstat;    // 0x20
  __IO uint32_t inten;      // 0x24
  __IO uint32_t intsetstat; // 0x28
  __IO uint32_t introuting; // 0x2c
  uint32_t : 32;            // 0x30
  __IO uint32_t eptoggle;   // 0x34
} UsbStruct;

#define USB0 ((volatile UsbStruct *)USB0_BASE)

// CRC

typedef struct CrcStruct
{
  __IO uint32_t mode;     // 0x00
  __IO uint32_t seed;     // 0x04
  __IO uint32_t sum_data; // 0x08
} CrcStruct;

#define CRC ((volatile CrcStruct *)CRC_BASE)

// SCT

typedef struct SctStruct
{
  __IO uint32_t config; // 0x00
  union
  { // 0x04
    __IO uint32_t ctrl;
    struct
    {
      __IO uint16_t ctrl_l;
      __IO uint16_t ctrl_h;
    };
  };
  union
  { // 0x08
    __IO uint32_t limit;
    struct
    {
      __IO uint32_t limit_l;
      __IO uint32_t limit_h;
    };
  };
  union
  { // 0x0c
    __IO uint32_t halt;
    struct
    {
      __IO uint32_t halt_l;
      __IO uint32_t halt_h;
    };
  };
  union
  { // 0x10
    __IO uint32_t stop;
    struct
    {
      __IO uint32_t stop_l;
      __IO uint32_t stop_h;
    };
  };
  union
  { // 0x14
    __IO uint32_t start;
    struct
    {
      __IO uint32_t start_l;
      __IO uint32_t start_h;
    };
  };
  uint32_t : 32; // 0x18
  uint32_t : 32; // 0x1c

  uint32_t : 32; // 0x20
  uint32_t : 32; // 0x24
  uint32_t : 32; // 0x28
  uint32_t : 32; // 0x2c
  uint32_t : 32; // 0x30
  uint32_t : 32; // 0x34
  uint32_t : 32; // 0x38
  uint32_t : 32; // 0x3c

  union
  { // 0x40
    __IO uint32_t count;
    struct
    {
      __IO uint32_t count_l;
      __IO uint32_t count_h;
    };
  };
  union
  { // 0x44
    __IO uint32_t state;
    struct
    {
      __IO uint32_t state_l;
      __IO uint32_t state_h;
    };
  };
  __O uint32_t input; // 0x48
  union
  { // 0x4c
    __IO uint32_t regmode;
    struct
    {
      __IO uint32_t regmode_l;
      __IO uint32_t regmode_h;
    };
  };
  __IO uint32_t output;        // 0x50
  __IO uint32_t outputdirctrl; // 0x54
  __IO uint32_t res;           // 0x58
  __IO uint32_t dmareq0;       // 0x5c

  __IO uint32_t dmareq1; // 0x60
  uint32_t reserved[35];

  __IO uint32_t even;    // 0xf0
  __IO uint32_t evflag;  // 0xf4
  __IO uint32_t conen;   // 0xf8
  __IO uint32_t conflag; // 0xfc

  union
  {
    __IO uint32_t match[8];
    __IO uint32_t cap[8];
  };

  uint32_t reserved1[56];

  __IO uint32_t matchrel[8];

  uint32_t reserved2[56];

  struct
  {
    __IO uint32_t state;
    __IO uint32_t ctrl;
  } ev[8];

  uint32_t reserved3[48 + 64];

  struct
  {
    __IO uint32_t set;
    __IO uint32_t clr;
  } out[4];
} SctStruct;

#define SCT0 ((volatile SctStruct *)SCT0_BASE)
#define SCT1 ((volatile SctStruct *)SCT1_BASE)

// DMA

typedef struct DmaStruct
{
  __IO uint32_t ctrl;     // 0x00
  __O uint32_t intstat;   // 0x04
  __IO uint32_t srambase; // 0x08
  uint32_t : 32;          // 0x0c
  uint32_t : 32;          // 0x10
  uint32_t : 32;          // 0x14
  uint32_t : 32;          // 0x18
  uint32_t : 32;          // 0x1c

  __IO uint32_t enableset0; // 0x20
  uint32_t : 32;            // 0x14
  __I uint32_t enableclr0;  // 0x28
  uint32_t : 32;            // 0x2c
  __O uint32_t active0;     // 0x30
  uint32_t : 32;            // 0x34
  __O uint32_t busy0;       // 0x38
  uint32_t : 32;            // 0x3c

  __IO uint32_t errint0;   // 0x40
  uint32_t : 32;           // 0x44
  __IO uint32_t intenset0; // 0x48
  uint32_t : 32;           // 0x4c
  __IO uint32_t intenclr0; // 0x50
  uint32_t : 32;           // 0x54
  __IO uint32_t inta0;     // 0x58
  uint32_t : 32;           // 0x5c

  __IO uint32_t intb0;    // 0x60
  uint32_t : 32;          // 0x64
  __I uint32_t setvalid0; // 0x68
  uint32_t : 32;
  __I uint32_t settrig0; // 0x70
  uint32_t : 32;         // 0x74
  __I uint32_t abort0;   // 0x78
  uint32_t : 32;         // 0x7c

  uint32_t reserved[224];

  struct
  {
    __IO uint32_t cfg;
    __O uint32_t ctlstat;
    __IO uint32_t xfercfg;
    uint32_t : 32;
  } ch[16];
} DmaStruct;

#define DMA ((volatile DmaStruct *)DMA_BASE)

// GPIO

typedef struct GpioStruct
{
  __IO uint8_t byte_pin0[32];
  __IO uint8_t byte_pin1[32];
  __IO uint8_t byte_pin2[32];
  uint32_t reserved1[1000];

  __IO uint32_t word_pin0[32];
  __IO uint32_t word_pin1[32];
  __IO uint32_t word_pin2[32];
  uint32_t reserved2[928];

  __IO uint32_t dir0;
  __IO uint32_t dir1;
  __IO uint32_t dir2;
  uint32_t reserved3[29];

  __IO uint32_t mask0;
  __IO uint32_t mask1;
  __IO uint32_t mask2;
  uint32_t reserved4[29];

  __IO uint32_t pin0;
  __IO uint32_t pin1;
  __IO uint32_t pin2;
  uint32_t reserved5[29];

  __IO uint32_t mpin0;
  __IO uint32_t mpin1;
  __IO uint32_t mpin2;
  uint32_t reserved6[29];

  __IO uint32_t set0;
  __IO uint32_t set1;
  __IO uint32_t set2;
  uint32_t reserved7[29];

  __I uint32_t clr0;
  __I uint32_t clr1;
  __I uint32_t clr2;
  uint32_t reserved8[29];

  __I uint32_t xor0;
  __I uint32_t xor1;
  __I uint32_t xor2;
} GpioStruct;

#define GPIO0 ((volatile GpioStruct *)GPIO0_BASE)

// GPIO GROUP interrupts

typedef struct GpioGrpStruct
{
  __IO uint32_t ctrl; // 0x00
  uint32_t : 32;      // 0x04
  uint32_t : 32;      // 0x08
  uint32_t : 32;      // 0x0c
  uint32_t : 32;      // 0x10
  uint32_t : 32;      // 0x14
  uint32_t : 32;      // 0x18
  uint32_t : 32;      // 0x1c

  __IO uint32_t pol0; // 0x20
  __IO uint32_t pol1; // 0x24
  __IO uint32_t pol2; // 0x28
  uint32_t : 32;      // 0x2c
  uint32_t : 32;      // 0x30
  uint32_t : 32;      // 0x34
  uint32_t : 32;      // 0x38
  uint32_t : 32;      // 0x3c

  __IO uint32_t ena0; // 0x40
  __IO uint32_t ena1; // 0x44
  __IO uint32_t ena2; // 0x48

} GpioGrpStruct;

#define GPIO_GRP0 ((volatile GpioGrpStruct *)GPIO_GRP0_BASE)

// GPIO PINT

typedef struct GpioPintStruct
{
  __IO uint32_t isel;   // 0x00
  __IO uint32_t ienr;   // 0x04
  __IO uint32_t sienr;  // 0x08
  __IO uint32_t cienr;  // 0x0c
  __IO uint32_t ienf;   // 0x10
  __IO uint32_t sienf;  // 0x14
  __IO uint32_t cienf;  // 0x18
  __IO uint32_t rise;   // 0x1c
  __IO uint32_t fall;   // 0x20
  __IO uint32_t ist;    // 0x24
  __IO uint32_t pmctrl; // 0x28
  __IO uint32_t pmsrc;  // 0x2c
  __IO uint32_t pmcfg;  // 0x30
} GpioPintStruct;

#define GPIO0_PINT ((volatile GpioPintStruct *)GPIO0_PINT_BASE)

// // NVIC

typedef struct NvicStruct
{
  uint32_t _reserved1[64];
  __IO uint32_t iser0;
  uint32_t _reserved2[31];
  __IO uint32_t icer0;
  uint32_t _reserved3[31];
  __IO uint32_t ispr0;
  uint32_t _reserved4[31];
  __IO uint32_t icpr0;
  uint32_t _reserved5[31];
  __IO uint32_t iabr0[8];
  uint32_t _reserved6[63];
  __IO uint32_t ipr[8];
} NvicStruct;

#define NVIC ((volatile NvicStruct *)NVIC_BASE)

// SysTick

typedef struct SystickStruct
{
  uint32_t : 32;
  uint32_t : 32;
  uint32_t : 32;
  uint32_t : 32;

  __IO uint32_t csr;
  __IO uint32_t rvr;
  __IO uint32_t cvr;
  __IO uint32_t calib;
} SystickStruct;

#define SYSTICK ((volatile SystickStruct *)NVIC_BASE)

enum IrqMappingEnum
{
  IRQ_PINT0_0 = 0,
  IRQ_PINT0_1,
  IRQ_PINT0_2,
  IRQ_PINT0_3,
  IRQ_PINT0_4,
  IRQ_PINT0_5,
  IRQ_PINT0_6,
  IRQ_PINT0_7,
  IRQ_GINT0,     // 8
  IRQ_GINT1,     // 9
  IRQ_I2C1,      // 10
  IRQ_USART14,   // 11
  IRQ_USART23,   // 12
  IRQ_SCT01,     // 13
  IRQ_SSP1,      // 14
  IRQ_I2C0,      // 15
  IRQ_CT16B0,    // 16
  IRQ_CT16B1,    // 17
  IRQ_CT32B0,    // 18
  IRQ_CT32B1,    // 19
  IRQ_SSP0,      // 20
  IRQ_USART0,    // 21
  IRQ_USB0,       // 22
  FIQ_USB,       // 23
  IRQ_ADC_A,     // 24
  IRQ_RTC,       // 25
  IRQ_BOD_WDT,   // 26
  IRQ_FLASH,     // 27
  IRQ_DMA,       // 28
  IRQ_ADC_B,     // 29
  IRQ_USB_WAKEUP // 23
};

#endif // __LPC11U67_H_INCLUDED__
