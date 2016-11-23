/*** nRF24L01 Library - Registers
  ** Warthog Robotics
  ** University of Sao Paulo at Sao Carlos
  ** http://www.warthog.sc.usp.br
  ** This file is part of the nRF24L01 Library project
  ***/


/* Prevents multiple definitions */
#ifndef NRF24_REGISTERS
#define NRF24_REGISTERS


/* Commands codes */
#define NRF24_R_REGISTER_COMMAND          0x00
#define NRF24_W_REGISTER_COMMAND          0x20
#define NRF24_R_RX_PAYLOAD_COMMAND        0x61
#define NRF24_W_TX_PAYLOAD_COMMAND        0xA0
#define NRF24_FLUSH_TX_COMMAND            0xE1
#define NRF24_FLUSH_RX_COMMAND            0xE2
#define NRF24_REUSE_TX_PL_COMMAND         0xE3
#define NRF24_R_RX_PL_WID_COMMAND         0x60
#define NRF24_W_ACK_PAYLOAD_COMMAND       0xA8
#define NRF24_W_TX_PAYLOAD_NO_ACK_COMMAND 0xB0
#define NRF24_NULL_COMMAND                0xFF


/* Registers addresses */
#define NRF24_REG_CONFIG      0x00
#define NRF24_REG_EN_AA       0x01
#define NRF24_REG_EN_RXADDR   0x02
#define NRF24_REG_SETUP_AW    0x03
#define NRF24_REG_SETUP_RETR  0x04
#define NRF24_REG_RF_CH       0x05
#define NRF24_REG_RF_SETUP    0x06
#define NRF24_REG_STATUS      0x07
#define NRF24_REG_OBSERVE_TX  0x08
#define NRF24_REG_RPD         0x09
#define NRF24_REG_RX_ADDR_P0  0x0A
#define NRF24_REG_RX_ADDR_P1  0x0B
#define NRF24_REG_RX_ADDR_P2  0x0C
#define NRF24_REG_RX_ADDR_P3  0x0D
#define NRF24_REG_RX_ADDR_P4  0x0E
#define NRF24_REG_RX_ADDR_P5  0x0F
#define NRF24_REG_TX_ADDR     0x10
#define NRF24_REG_RX_PW_P0    0x11
#define NRF24_REG_RX_PW_P1    0x12
#define NRF24_REG_RX_PW_P2    0x13
#define NRF24_REG_RX_PW_P3    0x14
#define NRF24_REG_RX_PW_P4    0x15
#define NRF24_REG_RX_PW_P5    0x16
#define NRF24_REG_FIFO_STATUS 0x17
#define NRF24_REG_DYNPD       0x1C
#define NRF24_REG_FEATURE     0x1D


#endif
