/**
 * LPC11U67 SSP driver
 */

#include <stdint.h>

#include "lpc11u6x.h"

#define SSP_HANDLE_ETHERNET 1
#define SSP_HANDLE_FLASH 2
#define SSP_HANDLE_RADIO 3

#define SSP_CS_INDEX(p, b) (((p) << 5) + (b))

typedef class lpc_ssp_class
{
private:
    SspStruct *ssp;
    int16_t handle;
    int16_t CsIndex;
    uint16_t WriteSize, ReadSize;
    uint8_t *TransferBuffer;

    int32_t ReadByte();
    int WriteByte(uint8_t v);

public:
    lpc_ssp_class(uint32_t base);

    void Init();
    int Open(int h);
    int Close(int h);
    int GetHandle(void) { return handle; }
    int RequestRead(uint32_t h, uint8_t *buf, uint32_t size);
    int RequestWrite(uint32_t h, uint8_t *buf, uint32_t size);
    int RequestWriteRead(uint32_t h, uint8_t *buf, uint32_t wsize, uint32_t rsize);
    void Test(void);
} lpc_ssp_t;

extern lpc_ssp_class ssp0;
extern lpc_ssp_class ssp1;
