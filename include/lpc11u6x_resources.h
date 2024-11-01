/* ****************************************************************************
 * LPC11U6x resources
 *
 * (C) Olivier Gautherot, 2023
 **************************************************************************** */

/* Memory map:
 *   Flash:    128KB (0x00000000-0x0001ffff)
 *   Boot ROM: 32KB  (0x1fff0000-0x1fff7fff)
 *
 *   SRAM0:    16KB  (0x10000000-0x10003fff)
 *   SRAM1:    2KB   (0x20000000-0x200007ff)
 *   SRAM2:    2KB   (0x20004000-0x200047ff)
 *   EEPROM:   4KB
 */

#include <stdint.h>

typedef struct
{
  const uint32_t usbdApiBase;      /*!< USBD API function table base address */
  const uint32_t reserved0;        /*!< Reserved */
  const uint32_t reserved1;        /*!< Reserved */
  const PWRD_API_T *pPWRD;         /*!< Power API function table base address */
  const ROM_DIV_API_T *divApiBase; /*!< Divider API function table base address */
  const I2CD_API_T *pI2CD;         /*!< I2C driver API function table base address */
  const DMAD_API_T *pDMAD;         /*!< DMA driver API function table base address */
  const uint32_t reserved2;        /*!< Reserved */
  const uint32_t reserved3;        /*!< Reserved */
  const UARTD_API_T *pUARTND;      /*!< USART 1/2/3/4 driver API function table base address */
  const uint32_t reserved4;        /*!< Reserved */
  const UARTD_API_T *pUART0D;      /*!< USART 0 driver API function table base address */
} LPC_ROM_API_T;

#define ROM_DRIVER_BASE_LOC (0x1FFF1FF8UL)
#define LPC_ROM_API (*(LPC_ROM_API_T **)LPC_ROM_API_BASE_LOC)

#define IAP_LOCATION 0x1FFF1FF1
#define IAP_ENTRY ((IAP)IAP_LOCATION)
#define LPC_PWRD_API ((LPC_ROM_API)->pPWRD)
#define LPC_I2CD_API ((LPC_ROM_API)->pI2CD)
#define LPC_DMAD_API ((LPC_ROM_API)->pDMAD)
#define LPC_UARTND_API ((LPC_ROM_API)->pUARTND)
#define LPC_UART0D_API ((LPC_ROM_API)->pUART0D)

ROM_DIV_API_T const *pROMDiv = LPC_ROM_API->divApiBase;

unsigned int command_param[5];
unsigned int status_result[5];

typedef void (*IAP)(unsigned int[], unsigned int[]);
IAP iap_entry = (IAP)IAP_LOCATION;

extern IAP iap_entry;

/*
  IAP Command   Command Code  Described in
  Prepare sector(s) for write operation 50 (decimal)  Table 383
  Copy RAM to flash                     51 (decimal)  Table 384
  Erase sector(s)                       52 (decimal)  Table 385
  Blank check sector(s)                 53 (decimal)  Table 386
  Read Part ID                          54 (decimal)  Table 387
  Read Boot code version                55 (decimal)  Table 388
  Compare                               56 (decimal)  Table 389
  Reinvoke ISP                          57 (decimal)  Table 390
  Read UID                              58 (decimal)  Table 391
  Erase page                            59 (decimal)  Table 392
  EEPROM Write                          61 (decimal)  Table 393
  EEPROM Read                           62(decimal)   Table 394
*/

typedef struct PWRD_API
{
  void (*set_pll)(uint32_t cmd[], uint32_t resp[]);         /*!< Set PLL function */
  void (*set_pll)(unsigned int cmd[], unsigned int resp[]); /*!< Set power function */
} PWRD_API_T;

typedef struct
{
  int quot; /*!< Quotient */
  int rem;  /*!< Remainder */
} IDIV_RETURN_T;

typedef struct
{
  unsigned quot; /*!< Quotient */
  unsigned rem;  /*!< Reminder */
} UIDIV_RETURN_T;

typedef struct
{
  int (*sidiv)(int numerator, int denominator);                /*!< Signed integer division */
  unsigned (*uidiv)(unsigned numerator, unsigned denominator); /*!< Unsigned integer division */
  IDIV_RETURN_T(*sidivmod)
  (int numerator, int denominator); /*!< Signed integer division with remainder */
  UIDIV_RETURN_T(*uidivmod)
  (unsigned numerator, unsigned denominator); /*!< Unsigned integer division with remainder */
} ROM_DIV_API_T;

typedef struct I2CD_API
{
  /*!< Interrupt Support Routine */
  void (*i2c_isr_handler)(I2C_HANDLE_T *handle);
  /*!< MASTER functions */
  ErrorCode_t (*i2c_master_transmit_poll)(I2C_HANDLE_T *handle, I2C_PARAM_T *param, I2C_RESULT_T *result);
  ErrorCode_t (*i2c_master_receive_poll)(I2C_HANDLE_T *handle, I2C_PARAM_T *param, I2C_RESULT_T *result);
  ErrorCode_t (*i2c_master_tx_rx_poll)(I2C_HANDLE_T *handle, I2C_PARAM_T *param, I2C_RESULT_T *result);
  ErrorCode_t (*i2c_master_transmit_intr)(I2C_HANDLE_T *handle, I2C_PARAM_T *param, I2C_RESULT_T *result);
  ErrorCode_t (*i2c_master_receive_intr)(I2C_HANDLE_T *handle, I2C_PARAM_T *param, I2C_RESULT_T *result);
  ErrorCode_t (*i2c_master_tx_rx_intr)(I2C_HANDLE_T *handle, I2C_PARAM_T *param, I2C_RESULT_T *result);
  /*!< SLAVE functions */
  ErrorCode_t (*i2c_slave_receive_poll)(I2C_HANDLE_T *handle, I2C_PARAM_T *param, I2C_RESULT_T *result);
  ErrorCode_t (*i2c_slave_transmit_poll)(I2C_HANDLE_T *handle, I2C_PARAM_T *param, I2C_RESULT_T *result);
  ErrorCode_t (*i2c_slave_receive_intr)(I2C_HANDLE_T *handle, I2C_PARAM_T *param, I2C_RESULT_T *result);
  ErrorCode_t (*i2c_slave_transmit_intr)(I2C_HANDLE_T *handle, I2C_PARAM_T *param, I2C_RESULT_T *result);
  ErrorCode_t (*i2c_set_slave_addr)(I2C_HANDLE_T *handle, uint32_t slave_addr_0_3, uint32_t slave_mask_0_3);
  /*!< OTHER support functions */
  uint32_t (*i2c_get_mem_size)(void);
  I2C_HANDLE_T *(*i2c_setup)(uint32_t i2c_base_addr, uint32_t *start_of_ram);
  ErrorCode_t (*i2c_set_bitrate)(I2C_HANDLE_T *handle, uint32_t p_clk_in_hz, uint32_t bitrate_in_bps);
  uint32_t (*i2c_get_firmware_version)(void);
  CHIP_I2C_MODE_T(*i2c_get_status)
  (I2C_HANDLE_T *handle);
} I2CD_API_T;

typedef enum
{
  ERR_I2C_BASE = 0x00060000,
  /*0x00060001*/ ERR_I2C_NAK = ERR_I2C_BASE + 1,
  /*0x00060002*/ ERR_I2C_BUFFER_OVERFLOW,
  /*0x00060003*/ ERR_I2C_BYTE_COUNT_ERR,
  /*0x00060004*/ ERR_I2C_LOSS_OF_ARBRITRATION,
  /*0x00060005*/ ERR_I2C_SLAVE_NOT_ADDRESSED,
  /*0x00060006*/ ERR_I2C_LOSS_OF_ARBRITRATION_NAK_BIT,
  /*0x00060007*/ ERR_I2C_GENERAL_FAILURE,
  /*0x00060008*/ ERR_I2C_REGS_SET_TO_DEFAULT,
  /*0x00060009*/ ERR_I2C_TIMEOUT,
  /*0x0006000A*/ ERR_I2C_BUFFER_UNDERFLOW
} ErrorCode_t;

typedef struct I2C_PARAM
{
  uint32_t num_bytes_send;  /*!< No. of bytes to send */
  uint32_t num_bytes_rec;   /*!< No. of bytes to receive */
  uint8_t *buffer_ptr_send; /*!< Pointer to send buffer */
  uint8_t *buffer_ptr_rec;  /*!< Pointer to receive buffer */
  I2C_CALLBK_T func_pt;     /*!< Callback function */
  uint8_t stop_flag;        /*!< Stop flag */
  uint8_t dummy[3];
} I2C_PARAM_T;

typedef struct I2C_RESULT
{
  uint32_t n_bytes_sent; /*!< No. of bytes sent */
  uint32_t n_bytes_recd; /*!< No. of bytes received */
} I2C_RESULT_T;

typedef enum CHIP_I2C_MODE
{
  IDLE,
  /*!< IDLE state */
  MASTER_SEND,    /*!< Master send state */
  MASTER_RECEIVE, /*!< Master Receive state */
  SLAVE_SEND,     /*!< Slave send state */
  SLAVE_RECEIVE   /*!< Slave receive state */
} CHIP_I2C_MODE_T;

typedef struct UARTD_API
{
  // index of all the UART driver functions
  uint32_t (*uart_get_mem_size)(void);
  UART_HANDLE_T(*uart_setup)
  (uint32_t base_addr, uint8_t *ram);
  uint32_t (*uart_init)(UART_HANDLE_T handle, UART_CONFIG_T *set);
  uint8_t (*uart_get_char)(UART_HANDLE_T handle);
  void (*uart_put_char)(UART_HANDLE_T handle, uint8_t data);
  uint32_t (*uart_get_line)(UART_HANDLE_T handle, UART_PARAM_T *param);
  uint32_t (*uart_put_line)(UART_HANDLE_T handle, UART_PARAM_T *param);
  void (*uart_isr)(UART_HANDLE_T handle);
} UARTD_API_T; // end of structure

typedef enum
{
  ERR_UART_BASE = 0x00080000,
  /*0x00080001*/ ERR_UART_RXD_BUSY = ERR_UART_BASE + 1, // UART rxd is busy
  /*0x00080002*/ ERR_UART_TXD_BUSY,                     // UART txd is busy
  /*0x00080003*/ ERR_UART_OVERRUN_FRAME_PARITY_NOISE,   // overrun err, frame err, parity
                                                        // err, RxNoise err
  /*0x00080004*/ ERR_UART_UNDERRUN,                     // underrun err
  /*0x00080005*/ ERR_UART_PARAM,
  // parameter error
  /*0x00080006*/ ERR_UART_BAUDRATE // baudrate setting error
} ErrorCode_t;

typedef struct UART_CONFIG
{
  uint32_t sys_clk_in_hz;  // Sytem clock in hz.
  uint32_t baudrate_in_hz; // Baudrate in hz
  uint8_t config;
  // bit 1:0
  //  00: 7 bits length, 01: 8 bits lenght, others: reserved
  // bit3:2
  //  00: No Parity, 01: reserved, 10: Even, 11: Odd
  // bit4
  //  0: 1 Stop bit, 1: 2 Stop bits
  uint8_t sync_mod;
  // bit0: 0 = Async mode, 1 = Sync mode
  // bit1: 0 = Un_RXD is sampled on the falling edge of SCLK
  // 1 = Un_RXD is sampled on the rising edge of SCLK
  // bit2: 0 = Start and stop bits are transmitted as in asynchronous
  // mode
  // 1 = Start and stop bits are not transmitted
  // bit3: 0 = the UART is a slave on Sync mode
  // 1 = the UART is a master on Sync mode
  // bit4: 0 = SCLK cycles only when characters are being sent on TxD)
  // 1 = SCLK runs continuously (characters can be received )
  uint16_t error_en;
  // 0 = Disable overrun error, parity error, framing error,
  //  break indica tion or transmission error detection.
  //  1 = Enable overrun error, parity error, framing error,
  //  break indica tion or transmission error detection.
} UART_CONFIG_T;

typedef struct uart_A
{                  // parms passed to UART driver function
  uint8_t *buffer; // The pointer of buffer.
  // For uart_get_line function, buffer for receiving data.
  // For uart_put_line function, buffer for transmitting data.
  uint32_t size; // [IN] The size of buffer.
  //[OUT] The number of bytes transmitted/received.
  uint16_t transfer_mode;
  // 0x00: For uart_get_line function, stop transfer when the buffer is full.
  // For uart_put_line function, stop transfer when the buffer is empty.
  // 0x01: For uart_get_line function, stop transfer when
  // <CR><LF> characters have been received.
  // For uart_put_line function, transfer is stoppred after
  // reaching \0. <CR><LF> characters are sent out after that.
  // 0x02: For uart_get_line function, stop transfer when <LF>
  // is received.
  // For uart_put_line function, transfer is stopped after
  // reaching \0. A <LF> character is sent out after that.
  // 0x03: For uart_get_line function, RESERVED.
  // For uart_put_line function, transfer is stopped after
  // reaching \0.
  // NOTE: if (transfer_mode & 0x0F) != 0, transfer also stops
  // when all data in buffer has been transferred.
  uint8_t driver_mode;
  // 0x00: Polling mode, function is blocked until transfer is
  // finished.
  // 0x01: Interrupt mode, function exit immediately. The callback
  // function
  // is invoked when transfer is finished.
  // 0x02: DMA mode (transfer_mode must be 0).
  // DMA req function is called for Uart DMA channel setup, then
  // DMA ISR indicate that transfer is finished.
  uint8_t dma_num;
  // DMA channel number in case DMA mode is enabled
  UART_CALLBK_T callback_func_pt;
  // callback function
  // In case DMA mode is enabled, callback function is invoked
  // after transfer. If callback_func_pt = NULL, no DMA interrupt
  // is issued for this UART channel.
  uint32_t dma; // DMA handler
} UART_PARAM_T;

typedef void (*CALLBK_T)(uint32_t res0, uint32_t res1);
// define callback func TYPE
// res0: error code
// res1: number of bytes transferred

typedef struct UARTD_API
{
  // index of all the UART driver functions
  uint32_t (*uart_get_mem_size)(void);
  UART_HANDLE_T(*uart_setup)
  (uint32_t base_addr, uint8_t *ram);
  uint32_t (*uart_init)(UART_HANDLE_T handle, UART_CONFIG_T *set);
  //--polling only functions--//
  uint8_t (*uart_get_char)(UART_HANDLE_T handle);
  void (*uart_put_char)(UART_HANDLE_T handle, uint8_t data);
  //--polling or interrupt functions--//
  uint32_t (*uart_get_line)(UART_HANDLE_T handle, UART_PARAM_T *param);
  uint32_t (*uart_put_line)(UART_HANDLE_T handle, UART_PARAM_T *param);
  void (*uart_isr)(UART_HANDLE_T handle);
} UARTD_API_T; // end of structure

typedef enum
{
  ERR_UART_BASE = 0x00080000,
  /*0x00080001*/ ERR_UART_RXD_BUSY = ERR_UART_BASE + 1, // UART rxd is busy
  /*0x00080002*/ ERR_UART_TXD_BUSY,                     // UART txd is busy
  /*0x00080003*/ ERR_UART_OVERRUN_FRAME_PARITY_NOISE,   // overrun err, frame err, parity
                                                        // err, RxNoise err
  /*0x00080004*/ ERR_UART_UNDERRUN,                     // underrun err
  /*0x00080005*/ ERR_UART_PARAM,                        // parameter error
  /*0x00080006*/ ERR_UART_BAUDRATE                      // baudrate setting error

      ERR_DMA_BASE = 0x000D0000,
  /*0x000D0001*/ ERR_DMA_ERROR_INT = ERR_DMA_BASE + 1,
  /*0x000D0002*/ ERR_DMA_CHANNEL_NUMBER,
  /*0x000D0003*/ ERR_DMA_CHANNEL_DISABLED,
  /*0x000D0004*/ ERR_DMA_BUSY,
  /*0x000D0005*/ ERR_DMA_NOT_ALIGNMENT,
  /*0x000D0006*/ ERR_DMA_PING_PONG_EN,
  /*0x000D0007*/ ERR_DMA_CHANNEL_VALID_PENDING
} ErrorCode_t;

typedef struct UART_CONFIG
{
  uint32_t sys_clk_in_hz;  // Sytem clock in hz.
  uint32_t baudrate_in_hz; // Baudrate in hz
  uint8_t config;
  // bit 1:0
  //  00: 7 bits length, 01: 8 bits lenght, others: reserved
  // bit3:2
  //  00: No Parity, 01: reserved, 10: Even, 11: Odd
  // bit4
  //  0: 1 Stop bit, 1: 2 Stop bits
  uint8_t sync_mod;
  // bit0: 0(Async mode), 1(Sync mode)
  // bit1: 0(Un_RXD is sampled on the falling edge of SCLK)
  //  1(Un_RXD is sampled on the rising edge of SCLK)
  // bit2: 0(Start and stop bits are transmitted as in asynchronous mode)
  //  1(Start and stop bits are not transmitted)
  // bit3: 0(the UART is a slave on Sync mode)
  //  1(the UART is a master on Sync mode)
  uint16_t error_en;
  // bit0: OverrunEn, bit1: UnderrunEn, bit2: FrameErrEn,
  // bit3: ParityErrEn, bit4: RxNoiseEn
} UART_CONFIG_T;

typedef struct uart_A
{                  // parms passed to UART driver function
  uint8_t *buffer; // The pointer of buffer.
  // For uart_get_line function, buffer for receiving data.
  // For uart_put_line function, buffer for transmitting data.
  uint32_t size;
  // [IN] The size of buffer.
  //[OUT] The number of bytes transmitted/received.
  uint16_t transfer_mode;
  // 0x00: For uart_get_line function, transfer without
  // termination.
  // For uart_put_line function, transfer without termination.
  // 0x01: For uart_get_line function, stop transfer when
  // <CR><LF> are received.
  // For uart_put_line function, transfer is stopped after
  // reaching \0. <CR><LF> characters are sent out after that.
  // 0x02: For uart_get_line function, stop transfer when <LF>
  // is received.
  // For uart_put_line function, transfer is stopped after
  // reaching \0. A <LF> character is sent out after that.
  // 0x03: For uart_get_line function, RESERVED.
  // For uart_put_line function, transfer is stopped after
  // reaching \0.
  // NOTE: if (transfer_mode & 0x0F) != 0, transfer also stops
  // when all data in buffer has been transferred.
  uint8_t driver_mode;
  // 0x00: Polling mode, function is blocked until transfer is
  // finished.
  // 0x01: Interrupt mode, function exit immediately, callback
  // function
  // is invoked when transfer is finished.
  // 0x02: DMA mode (transfer_mode must be 0).
  // DMA req function is called for Uart DMA channel setup, then
  // DMA ISR indicate that transfer is finished.
  uint8_t dma_num;
  // DMA channel number in case DMA mode is enabled
  UART_CALLBK_T callback_func_pt;
  // callback function
  // In case DMA mode is enabled, callback function is invoked
  // after transfer. If callback_func_pt = NULL, no DMA interrupt
  // is issued for this UART channel.
  uint32_t dma; // DMA handler
} UART_PARAM_T;

typedef struct DMAD_API
{ // index of all the DMA driver functions
  void (*dma_isr)(DMA_HANDLE_T *handle);
  uint32_t (*dma_get_mem_size)(void);
  DMA_HANDLE_T *(*dma_setup)(uint32_t base_addr, uint8_t *ram);
  ErrorCode_t (*dma_init)(DMA_HANDLE_T *handle, DMA_CHANNEL_T *channel, DMA_TASK_T *task);
  ErrorCode_t (*dma_link)(DMA_HANDLE_T *handle, DMA_TASK_T *task, uint8_t valid);
  ErrorCode_t (*dma_set_valid)(DMA_HANDLE_T *handle, uint8_t chl_num);
  ErrorCode_t (*dma_pause)(DMA_HANDLE_T *handle, uint8_t chl_num);
  ErrorCode_t (*dma_unpause)(DMA_HANDLE_T *handle, uint8_t chl_num);
  ErrorCode_t (*dma_abort)(DMA_HANDLE_T *handle, uint8_t chl_num);
} DMAD_API_T;

typedef struct DMA_CHANNEL
{
  uint8_t event;
  // event type selection for DMA transfer
  // 0: software request
  // 1: peripheral request
  // 2: hardware trigger
  // others: reserved
  uint8_t hd_trigger; // In case hardware trigger is enabled, the trigger burst is // set up here.
  // Rising edge triggered is fixed.
  // bit0~bit3: burst size
  // 0: burst size =1, 1: 21, 2: 22... 10: 1024, others: reserved.
  // bit4: Source Burst Wrap
  // 0: Source burst wrapping is not enabled
  // 1: Source burst wrapping is enabled
  // bit5: Destination Burst Wrap
  // 0: Destination burst wrapping is not enabled
  // 1: Destination burst wrapping is enabled
  // bit6: Trigger Burst
  // 0: Hardware trigger cause a single transfer
  // 1: Hardware trigger cause a burst transfer
  // bit7: reserved
  uint8_t Priority;
  // priority level
  // 0 -> 7: Highest priority -> Lowest priority.
  // other: reserved.
  CALLBK_T callback_func_pt; // callback function, Callback function is only
  // invoked when INTA or INTB is enabled.
} DMA_CHANNEL_T;

typedef void DMA_HANDLE_T; // define TYPE for DMA handle pointer

typedef struct DMA_ TASK
{
  unit8_t ch_num      // DMA channel number.
      uint8_t config; // configuration of this task
  // bit0: Ping_Pong transfer
  // 0: Not Ping_Pong transfer
  // 1: Linked with previous task for Ping_Pong transfer
  // bit1: Software Trigger
  // 0: the trigger for this channel is not set.
  // 1: the trigger for this channel is set immediately.
  // bit2: Clear Trigger
  // 0: The trigger is not cleared when this task is finished.
  // 1: The trigger is cleared when this task is finished.
  // bit3: Select INTA
  // 0: No IntA.
  // 1: The IntB flag for this channel will be set when this task is
  //  finished.
  // bit4: Select INTB
  // 0: No IntB.
  // 1: The IntB flag for this channel will be set when this task is finished.
  // bit5~bit7: reserved
  uint8_t data_type;
  // bit0~bit1: Data width. 0: 8-bit, 1: 16-bit, 2: 32-bit, 3: reserved
  // bit2~bit3: How is source address incremented?
  // 0: The source address is not incremented for each transfer.
  // 1: The source address is incremented by the amount specified by
  //  Width for each transfer.
  // 2: The source address is incremented by 2 times the amount specified
  //  by Width for each transfer.
  // 3: The source address is incremented by 4 times the amount specified
  //  by Width for each transfer.
  // bit4~bit5: How is the destination address incremented?
  // 0: The destination address is not incremented for each transfer.
  // 1: The destination address is incremented by the amount specified by
  //  Width for each transfer.
  // 2: The destination address is incremented by 2 times the amount
  //  specified by Width for each transfer.
  // 3: The destination address is incremented by 4 times the amount
  //  specified by Width for each transfer.
  // bit6~bit7: reserved.
  uint16_t data_length; // 0: 1 transfer, 1: 2 transfer, ... 1023: 1024 transfer.
  // Others: reserved.
  uint32_t src;       // Source data end address
  uint32_t dst;       // Destination end address
  uint32_t task_addr; // the address of RAM for saving this task.
  //(NOTE: each task need 16 bytes RAM for storing configuration,
  // and DMA API could set it according user input parameter,
  // but it is responsible of user to allocate this RAM space and
  // make sure that the base address must be 16-byte alignment.
  // And if user has setup the next_tast(!=0), the dma_task_link
  // must be called for this task setup, otherwise unpredictable error will
  // happen.)
} DMA_TASK_T;

typedef struct USBD_API
{
  const USBD_HW_API_T *hw;
  const USBD_CORE_API_T *core;
  const USBD_MSC_API_T *msc;
  const USBD_DFU_API_T *dfu;
  const USBD_HID_API_T *hid;
  const USBD_CDC_API_T *cdc;
  const uint32_t *reserved6;
  const uint32_t version;
} USBD_API_T;

/* set_pll mode options */
#define CPU_FREQ_EQU 0
#define CPU_FREQ_LTE 1
#define CPU_FREQ_GTE 2
#define CPU_FREQ_APPROX 3

/* set_pll result0 options */
#define PLL_CMD_SUCCESS 0
#define PLL_INVALID_FREQ 1
#define PLL_INVALID_MODE 2
#define PLL_FREQ_NOT_FOUND 3
#define PLL_NOT_LOCKED 4

/* set_power mode options */
#define PWR_DEFAULT 0
#define PWR_CPU_PERFORMANCE 1
#define PWR_EFFICIENCY 2
#define PWR_LOW_CURRENT 3

/* set_power result0 options */
#define PWR_CMD_SUCCESS 0
#define PWR_INVALID_FREQ 1
#define PWR_INVALID_MODE 2

#define PLL_CMD_SUCCESS 0
#define PLL_INVALID_FREQ 1
#define PLL_INVALID_MODE 2
#define PLL_FREQ_NOT_FOUND 3
#define PLL_NOT_LOCKED 4

#define PARAM_CMD_SUCCESS 0
#define PARAM_INVALID_FREQ 1
#define PARAM_INVALID_MODE 2
