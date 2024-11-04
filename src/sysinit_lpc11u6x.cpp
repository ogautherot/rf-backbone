/*
 * @brief Common SystemInit function for LPC11u6x chips
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2013
 * All rights reserved.
 *
 */

#include "lpc11u6x.h"
#include "RomAPI.h"
#include "board.h"
// #include "lpc11u6x_resources.h"

#define assert(x)           \
	{                       \
		if ((x) != 0)       \
		{                   \
			while (1)       \
			{               \
				asm("nop"); \
			}               \
		}                   \
	}

#define check_address(a, b) (((uint32_t)(a)) == ((uint32_t)(b)))

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Private functions
 ****************************************************************************/

/*****************************************************************************
 * Public functions
 ****************************************************************************/

/**
 *
 */
void SysconDefaultsPreset(void)
{
	volatile SysConStruct *syscon = SYSCON;

	syscon->SysPllClkUEn = 0;
	syscon->SysPllClkUEn = 1;

	syscon->UsbPllClkUEn = 0;
	syscon->UsbPllClkUEn = 1;

	syscon->MainClkUEn = 0;
	syscon->MainClkUEn = 1;

	syscon->UsbClkUen = 0;
	syscon->UsbClkUen = 1;

	syscon->ClkOutUEn = 0;
	syscon->ClkOutUEn = 1;
}

/**
 *
 */
void SystickInit(void)
{
	volatile SystickStruct *systick = SYSTICK;
	volatile SysConStruct *syscon = SYSCON;

	systick->rvr = 48000;
	systick->cvr = 48000;
	syscon->SysTckCal = 9;
	systick->csr = (1 << 2) | (1 << 0);
}

/**
 *
 */
void SystickEnable()
{
	volatile SystickStruct *systick = SYSTICK;

	systick->csr |= (1 << 0);
}

/**
 *
 */
void SystickIntEnable()
{
	volatile SystickStruct *systick = SYSTICK;

	systick->csr |= (1 << 1);
}

/**
 *
 */
void WatchdogInit()
{
	volatile SysConStruct *syscon = SYSCON;

	syscon->WdtOscCtrl = 0x3f;
}

/**
 *
 */
void PowerUpPeriph(void)
{
	uint32_t cnt = 5000;
	volatile SysConStruct *syscon = SYSCON;

	syscon->PdRunCfg &= 0xfffff800;
	syscon->PdAwakeCfg &= 0xffffc800;
	//~((1 << 13) | (1 << 10) | (1 << 8) |
	//(1 << 7) | (1 << 6) | (1 << 5) | (1 << 4));
	syscon->PdSleepCfg &= 0xffffffb7;
	// ~((1 << 3) | (1 << 6));

	while (cnt > 0)
	{
		asm("nop");
		--cnt;
	}
}

/**
 *
 */
void SetClockDividers(void)
{
	volatile SysConStruct *syscon = SYSCON;

	syscon->SysAhbClkCtrl |= (1 << 31) | (1 << 30) | (1 << 29) | (1 << 28) |
							 (1 << 26) | (1 << 19) | (1 << 18) | (1 << 16) |
							 (1 << 15) | (1 << 13) | (1 << 12) | (1 << 10) |
							 (1 << 9) | (1 << 8) | (1 << 7);
	syscon->Usart0ClkDiv = 12;
	syscon->Ssp0ClkDiv = 2;
	syscon->Ssp1ClkDiv = 2;
}

/**
 *
 */
void SystemCoreClockUpdate(void) {}

/**
 *
 */
void Board_Init(void) {}

/**
 *
 */
void Chip_USB_Init(void) {}

/**
 *
 */
void NVIC_Init(void)
{
	// Disable all interrupts
	NVIC->icer0 = 0xffffffff;
}

/**
 *
 */
void NVIC_EnableIRQ(uint32_t vector)
{
	// Set enable bit in ISER
	NVIC->iser0 = (1 << vector);
}

/**
 *
 */
void NVIC_DisableIRQ(uint32_t vector)
{
	// Clear enable bit in ICER
	NVIC->icer0 = (1 << vector);
}

/**
 *
 */
void ClkOutInit()
{
	volatile SysConStruct *syscon = SYSCON;

	syscon->ClkOutDiv = 1;
	syscon->ClkOutSel = 3;
	syscon->ClkOutUEn = 0;
	syscon->ClkOutUEn = 1;
}

/** Set PLL.
 * @param src	0 for IRC, 1 for crystal
 */
void SysPllInit(uint32_t src)
{
	const uint32_t IrcPllParams[] = {12000, 48000, CPU_FREQ_EQU, 1000};
	const uint32_t XtalPllParams[] = {10000, 50000, CPU_FREQ_EQU, 1000};
	const uint32_t *PllParams = (src == 0) ? IrcPllParams : XtalPllParams;
	uint32_t PllResp[2];
	volatile SysConStruct *syscon = SYSCON;

	syscon->MainClkSel = 0;
	syscon->MainClkUEn = 0;
	syscon->MainClkUEn = 1;
	LPC_ROM_API->pPWRD->set_pll(PllParams, PllResp);
	if (PLL_CMD_SUCCESS == PllResp[0])
	{
		syscon->MainClkSel = 3;
		syscon->MainClkUEn = 0;
		syscon->MainClkUEn = 1;
	}
}

/** Set PLL clock source. As no crystal is attached, the RF chip must be
 * initialized to use the system oscillator
 *
 */
void SysOscInit(uint32_t src)
{
	volatile SysConStruct *syscon = SYSCON;

	syscon->SysPllClkSel = src;
	syscon->SysPllClkUEn = 0;
	syscon->SysPllClkUEn = 1;
}

/** USB PLL setup. Requires a 12MHz crystal
 *
 */
uint32_t UsbPllInit()
{
	uint32_t cnt = 1000;
	volatile SysConStruct *syscon = SYSCON;

	syscon->UsbPllCtrl = 0x23;
	do
	{
		if (1 == syscon->UsbPllStat)
		{
			syscon->UsbPllClkSel = 3;
			syscon->UsbPllClkUEn = 0;
			syscon->UsbPllClkUEn = 1;
			return cnt;
		}
		--cnt;
	} while (0 < cnt);
	return -1;
}

/**
 *
 */
void ReleaseReset(void)
{
	volatile SysConStruct *syscon = SYSCON;

	syscon->PResetCtrl |= 0x3f; // (1 << 10) | (1 << 9) | (1 << 2) | (1 << 0);
}

/**
 *
 */
void IoconfigInit(void)
{
	volatile IoconStruct *iocon = IOCON;

	// iocon->pio0_01 = 0x91;
	iocon->pio0_06 = 0x92;
	iocon->pio0_08 = 0x91;
	iocon->pio0_09 = 0x91;
	iocon->pio0_17 = 0x91;
	iocon->pio0_18 = 0x91;
	iocon->pio0_19 = 0x91;
	iocon->pio0_21 = 0x91;
	iocon->pio1_20 = 0x92;
	iocon->pio1_21 = 0x92;
}

/**
 *
 */
void GpioInit(void)
{
	volatile GpioStruct *gpio = GPIO0;

	gpio->dir0 = 0x00800084;
	gpio->dir1 = 0x00002000;
}

/**
 *
 */
void ForceResetState(void)
{
	volatile SysConStruct *syscon = SYSCON;

	syscon->ClkOutUEn = 1;	  // 0
	syscon->MainClkUEn = 1;	  // 0
	syscon->SysPllClkUEn = 1; // 0
	syscon->UsbClkUen = 1;	  // 0
	syscon->UsbPllClkUEn = 1; // 0
}

/**
 *
 */
void Chip_Init(void)
{
	// SysconDefaultsPreset();
	SysOscInit(0); // Use IRC
	PowerUpPeriph();
	ReleaseReset();
	SysPllInit(0);
	SetClockDividers();
	IoconfigInit();
	GpioInit();
	// SystickInit();
	ClkOutInit();
	// UsbPllInit();

	WatchdogInit();
}

/**
 *
 */
void Board_SystemInit(void)
{
	NVIC_Init();
	SystickIntEnable();
	SystickEnable();
}

/**
 *
 */
void CheckMapping(void) {}

/* Set up and initialize hardware prior to call to main */
void SystemInit(void)
{
	// CheckMapping();
	Chip_Init();

	/* Setup system clocking and muxing */
	Board_SystemInit();
}
