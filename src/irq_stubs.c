/**
 *
 * */

#include <stdint.h>

extern uint32_t VectNum;
uint32_t VectNum = 0xdeadbeef;

void CpuIdle(void)
{
	while (1)
		;
}

void Nmi(void)
{
	VectNum = -2;
	CpuIdle();
}

void HardFaultISR(void)
{
	VectNum = -3;
	CpuIdle();
}

void SvcISR(void)
{
	//	VectNum = -11;
	//	CpuIdle();
}

void PendsvISR(void)
{
	VectNum = -14;
	CpuIdle();
}

/*
void SystickISR(void)
{
	VectNum = -15;
	CpuIdle();
}
*/

void PinInt0IRQ(void)
{
	VectNum = 0;
	CpuIdle();
}

void PinInt1IRQ(void)
{
	VectNum = 1;
	CpuIdle();
}

void PinInt2IRQ(void)
{
	VectNum = 2;
	CpuIdle();
}

void PinInt3IRQ(void)
{
	VectNum = 3;
	CpuIdle();
}

void PinInt4IRQ(void)
{
	VectNum = 4;
	CpuIdle();
}

void PinInt5IRQ(void)
{
	VectNum = 5;
	CpuIdle();
}

void PinInt6IRQ(void)
{
	VectNum = 6;
	CpuIdle();
}

void PinInt7IRQ(void)
{
	VectNum = 7;
	CpuIdle();
}

void Gint0IRQ(void)
{
	VectNum = 8;
	CpuIdle();
}

void Gint1IRQ(void)
{
	VectNum = 9;
	CpuIdle();
}

void I2c1IRQ(void)
{
	VectNum = 10;
	CpuIdle();
}

void Usart1_4IRQ(void)
{
	VectNum = 11;
	CpuIdle();
}

void Usart2_3IRQ(void)
{
	VectNum = 12;
	CpuIdle();
}

void Sct0_1IRQ(void)
{
	VectNum = 13;
	CpuIdle();
}

void I2c0IRQ(void)
{
	VectNum = 15;
	CpuIdle();
}

#ifdef NEVER
void Ct16b0IRQ(void)
{
	VectNum = 16;
	CpuIdle();
}

void Ct16b1IRQ(void)
{
	VectNum = 17;
	CpuIdle();
}
#endif

void Usart0IRQ(void)
{
	VectNum = 21;
	CpuIdle();
}

void UsbIRQ(void)
{
	VectNum = 22;
	CpuIdle();
}

void UsbFIQ(void)
{
	VectNum = 23;
	CpuIdle();
}

void AdcaIRQ(void)
{
	VectNum = 24;
	CpuIdle();
}

void RtcIRQ(void)
{
	VectNum = 25;
	CpuIdle();
}

void BodWdtIRQ(void)
{
	VectNum = 26;
	CpuIdle();
}

void FlashIRQ(void)
{
	VectNum = 27;
	CpuIdle();
}

void DmaIRQ(void)
{
	VectNum = 28;
	CpuIdle();
}

void AdcbIRQ(void)
{
	VectNum = 29;
	CpuIdle();
}

void UsbWakeupIRQ(void)
{
	VectNum = 30;
	CpuIdle();
}
