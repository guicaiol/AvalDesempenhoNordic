/*** nRF24L01 Library - Library functions prototypes
  ** Warthog Robotics
  ** University of Sao Paulo at Sao Carlos
  ** http://www.warthog.sc.usp.br
  ** This file is part of the nRF24L01 Library project
  ***/


/* Prevents multiple definitions */
#ifndef NRF24L01
#define NRF24L01


/* Includes library configuration */
#include <nRF24L01/nrf24l01_pinout.h>
#include <nRF24L01/nrf24l01_registers.h>


/* Includes dsPIC33 library */
#include <p33Fxxxx.h>


/* Elementary types definitions */
#ifndef WR_ELEMENTARYTYPES
#define WR_ELEMENTARYTYPES
typedef unsigned char uint8;
typedef unsigned int  uint16;
typedef unsigned long uint32;
typedef char          int8;
typedef int           int16;
typedef long          int32;
#endif


/* Initialization functions */
void nRF24_init(uint8 radio);
void nRF24_configSPI(uint8 radio);
void nRF24_configPorts(uint8 radio);


/* General functions */
void  nRF24_setBit(uint8* byte, uint8 position);
void  nRF24_clearBit(uint8* byte, uint8 position);
uint8 nRF24_getBit(uint8 byte, uint8 position);


/* SPI functions */
void nRF24_exchangeData(uint8 radio, uint8* inData, uint8* outData, uint8 nBytes);
void nRF24_writeData(uint8 radio, uint8* data, uint8 nBytes);


/* Time functions */
void nRF24_ceSleep();


/* Commands */
void  nRF24_readRegister(uint8 radio, uint8 reg, uint8* data, uint8 nBytes);
void  nRF24_writeRegister(uint8 radio, uint8 reg, uint8* data, uint8 nBytes);
void  nRF24_getReceivedPayload(uint8 radio, uint8* data, uint8* nBytes);
void  nRF24_sendPayload(uint8 radio, uint8* address, uint8* data, uint8 nBytes, uint8 enableAck);
void  nRF24_flushTxFIFO(uint8 radio);
void  nRF24_flushRxFIFO(uint8 radio);
void  nRF24_resendLastPayload(uint8 radio);
uint8 nRF24_getReceivedPayloadSize(uint8 radio);
void  nRF24_setAckPayload(uint8 radio, uint8 pipe, uint8* data, uint8 nBytes);
void  nRF24_setRxActive(uint8 radio);
void  nRF24_setStandBy(uint8 radio);


/* Register 0x00 (CONFIG) */
void  nRF24_enableDRInt(uint8 radio, uint8 enable);
void  nRF24_enableDSInt(uint8 radio, uint8 enable);
void  nRF24_enableMaxRTInt(uint8 radio, uint8 enable);
uint8 nRF24_isDRIntEnabled(uint8 radio);
uint8 nRF24_isDSIntEnabled(uint8 radio);
uint8 nRF24_isMaxRTIntEnabled(uint8 radio);

void  nRF24_enableCRC(uint8 radio, uint8 enable, uint8 size);
uint8 nRF24_isCRCEnabled(uint8 radio);
uint8 nRF24_getCRCSize(uint8 radio);

void  nRF24_powerUp(uint8 radio);
void  nRF24_powerDown(uint8 radio);
uint8 nRF24_isPowerUp(uint8 radio);

void  nRF24_setRx(uint8 radio);
void  nRF24_setTx(uint8 radio);
uint8 nRF24_isRx(uint8 radio);
uint8 nRF24_isTx(uint8 radio);


/* Register 0x01 (EN_AA) */
void  nRF24_enableAutoAck(uint8 radio, uint8 pipe, uint8 enable);
uint8 nRF24_isAutoAckEnabled(uint8 radio, uint8 pipe);


/* Register 0x02 (EN_RXADDR) */
void  nRF24_enableRxPipe(uint8 radio, uint8 pipe, uint8 enable);
uint8 nRF24_isRxPipeEnabled(uint8 radio, uint8 pipe);


/* Register 0x03 (SETUP_AW) */
void  nRF24_setAddressSize(uint8 radio, uint8 size);
uint8 nRF24_getAddressSize(uint8 radio);


/* Register 0x04 (SETUP_RETR) */
void  nRF24_setAutoRetransmitDelay(uint8 radio, uint8 delay);
void  nRF24_setAutoRetransmitCount(uint8 radio, uint8 count);
uint8 nRF24_getAutoRetransmitDelay(uint8 radio);
uint8 nRF24_getAutoRetransmitCount(uint8 radio);


/* Register 0x05 (RF_CH) */
void  nRF24_setChannel(uint8 radio, uint8 channel);
uint8 nRF24_getChannel(uint8 radio);


/* Register 0x06 (RF_SETUP) */
void  nRF24_enableCarrierTest(uint8 radio, uint8 enable);
uint8 nRF24_isCarrierTestEnabled(uint8 radio);

void  nRF24_enablePLLLock(uint8 radio, uint8 enable);
uint8 nRF24_isPLLLockEnabled(uint8 radio);

void  nRF24_setDataRate(uint8 radio, uint8 dataRate);
uint8 nRF24_getDataRate(uint8 radio);

void  nRF24_setRFPower(uint8 radio, uint8 power);
uint8 nRF24_getRFPower(uint8 radio);


/* Register 0x07 (STATUS) */
uint8 nRF24_getDRInt(uint8 radio);
uint8 nRF24_getDSInt(uint8 radio);
uint8 nRF24_getMaxRTInt(uint8 radio);
void  nRF24_clearDRInt(uint8 radio);
void  nRF24_clearDSInt(uint8 radio);
void  nRF24_clearMaxRTInt(uint8 radio);

uint8 nRF24_getRxFIFOSource(uint8 radio);


/* Register 0x08 (OBSERVE_TX) */
uint8 nRF24_getLostPacketsCount(uint8 radio);
uint8 nRF24_getRetransmitsCount(uint8 radio);


/* Register 0x09 (RPD) */
uint8 nRF24_getReceivedPower(uint8 radio);


/* Registers 0x0A to 0x0F (RX_ADDR_Px) */
void nRF24_setRxAddress(uint8 radio, uint8 pipe, uint8* addr);
void nRF24_getRxAddress(uint8 radio, uint8 pipe, uint8* data);


/* Register 0x10 (TX_ADDR) */
void nRF24_setTxAddress(uint8 radio, uint8* addr);
void nRF24_getTxAddress(uint8 radio, uint8* data);


/* Registers 0x11 to 0x16 (RX_PW_Px) */
void  nRF24_setRxPayloadSize(uint8 radio, uint8 pipe, uint8 size);
uint8 nRF24_getRxPayloadSize(uint8 radio, uint8 pipe);


/* Register 0x17 (FIFO_STATUS) */
uint8 nRF24_isTxReuseEnabled(uint8 radio);
uint8 nRF24_isTxFIFOFull(uint8 radio);
uint8 nRF24_isTxFIFOEmpty(uint8 radio);
uint8 nRF24_isRxFIFOFull(uint8 radio);
uint8 nRF24_isRxFIFOEmpty(uint8 radio);


/* Register 0x1C (DYNPD) */
void  nRF24_enableDynamicPayloadSize(uint8 radio, uint8 pipe, uint8 enable);
uint8 nRF24_isDynamicPayloadSizeEnabled(uint8 radio, uint8 pipe);


/* Register 0x1D (FEATURE) */
void  nRF24_allowDynamicPayloadSize(uint8 radio, uint8 allow);
uint8 nRF24_isDynamicPayloadSizeAllowed(uint8 radio);

void  nRF24_enableAckPayload(uint8 radio, uint8 enable);
uint8 nRF24_isAckPayloadEnabled(uint8 radio);

void  nRF24_enableDynamicAckPayload(uint8 radio, uint8 enable);
uint8 nRF24_isDynamicAckPayloadEnabled(uint8 radio);


#endif
