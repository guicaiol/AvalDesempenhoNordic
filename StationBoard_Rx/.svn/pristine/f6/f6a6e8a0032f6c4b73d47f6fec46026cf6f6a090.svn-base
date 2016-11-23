/*** nRF24L01 Library - Library functions implementation
  ** Warthog Robotics
  ** University of Sao Paulo at Sao Carlos
  ** http://www.warthog.sc.usp.br
  ** This file is part of the nRF24L01 Library project
  ***/


/* Includes nRF24L01 library */
#include <nRF24L01/nrf24l01.h>


/* Includes dsPIC33 libraries */
#include <p33Fxxxx.h>
#include <libpic30.h>
#include <stdlib.h>
#include <math.h>
#include <spi.h>


/* Initialization functions */
void nRF24_init(uint8 radio) {
    nRF24_configPorts(radio);
    nRF24_configSPI(radio);
}

void nRF24_configPorts(uint8 radio) {
    if (radio == 0) {
        #if NRF24_HAS_AN_SS0
            NRF24_ADPCFG_SS0 = 1;
        #endif
        #if NRF24_HAS_AN_CE0
            NRF24_ADPCFG_CE0 = 1;
        #endif

        AD1PCFGLbits.PCFG4 = 1;

        NRF24_TRIS_SS0 = 0;
        NRF24_TRIS_CE0 = 0;

        NRF24_SS0 = 1;
        NRF24_CE0 = 0;
    }

    else {
        #if NRF24_HAS_AN_SS1
            NRF24_ADPCFG_SS1 = 1;
        #endif
        #if NRF24_HAS_AN_CE1
            NRF24_ADPCFG_CE1 = 1;
        #endif

        NRF24_TRIS_SS1 = 0;
        NRF24_TRIS_CE1 = 0;

        NRF24_SS1 = 1;
        NRF24_CE1 = 0;
    }
}

void nRF24_configSPI(uint8 radio) {
    if (radio == 0) {
        __builtin_write_OSCCONL(OSCCONL & 0xBF);
        RPINR20bits.SDI1R = NRF24_MISO0_RPIN;
        NRF24_MOSI0_RPOR  = 7;
        NRF24_SCLK0_RPOR  = 8;
        __builtin_write_OSCCONL(OSCCONL | 0x40);

        CloseSPI1();
        OpenSPI1(ENABLE_SCK_PIN & ENABLE_SDO_PIN & SPI_MODE16_OFF & SPI_SMP_OFF &
                 SPI_CKE_ON & SLAVE_ENABLE_OFF & CLK_POL_ACTIVE_HIGH & MASTER_ENABLE_ON &
                 SEC_PRESCAL_6_1 & PRI_PRESCAL_1_1,
                 FRAME_ENABLE_OFF,
                 SPI_ENABLE & SPI_IDLE_CON & SPI_RX_OVFLOW_CLR);

        DisableIntSPI1;
    }

    else {
        __builtin_write_OSCCONL(OSCCONL & 0xBF);
        RPINR22bits.SDI2R = NRF24_MISO1_RPIN;
        NRF24_MOSI1_RPOR  = 10;
        NRF24_SCLK1_RPOR  = 11;
        __builtin_write_OSCCONL(OSCCONL | 0x40);

        CloseSPI2();
        OpenSPI2(ENABLE_SCK_PIN & ENABLE_SDO_PIN & SPI_MODE16_OFF & SPI_SMP_OFF &
                 SPI_CKE_ON & SLAVE_ENABLE_OFF & CLK_POL_ACTIVE_HIGH & MASTER_ENABLE_ON &
                 SEC_PRESCAL_6_1 & PRI_PRESCAL_1_1,
                 FRAME_ENABLE_OFF,
                 SPI_ENABLE & SPI_IDLE_CON & SPI_RX_OVFLOW_CLR);

        DisableIntSPI2;
    }
}


/* General functions */
void nRF24_setBit(uint8* byte, uint8 position) {
    *byte |= (1 << position);
}

void nRF24_clearBit(uint8* byte, uint8 position) {
    *byte &= ~(1 << position);
}

uint8 nRF24_getBit(uint8 byte, uint8 position) {
    return((byte & (1 << position)) >> position);
}


/* SPI functions */
void nRF24_exchangeData(uint8 radio, uint8* inData, uint8* outData, uint8 nBytes) {
    uint8 i;

    if (radio == 0) {
        NRF24_SS0 = 0;

        for (i = 0; i < nBytes; i++) {
            WriteSPI1(outData[i]);
            while (SPI1STATbits.SPITBF == 1) {}
            while (SPI1STATbits.SPIRBF == 0) {}
            inData[i] = ReadSPI1();
        }

        NRF24_SS0 = 1;
    }

    else {
        NRF24_SS1 = 0;

        for (i = 0; i < nBytes; i++) {
            WriteSPI2(outData[i]);
            while (SPI2STATbits.SPITBF == 1) {}
            while (SPI2STATbits.SPIRBF == 0) {}
            inData[i] = ReadSPI2();
        }

        NRF24_SS1 = 1;
    }
}

void nRF24_writeData(uint8 radio, uint8* data, uint8 nBytes) {
    uint8 i;

    if (radio == 0) {
        NRF24_SS0 = 0;

        for (i = 0; i < nBytes; i++) {
            WriteSPI1(data[i]);
            while (SPI1STATbits.SPITBF == 1) {}
            while (SPI1STATbits.SPIRBF == 0) {}
            (void) ReadSPI1();
        }

        NRF24_SS0 = 1;
    }

    else {
        NRF24_SS1 = 0;

        for (i = 0; i < nBytes; i++) {
            WriteSPI2(data[i]);
            while (SPI2STATbits.SPITBF == 1) {}
            while (SPI2STATbits.SPIRBF == 0) {}
            (void) ReadSPI2();
        }

        NRF24_SS1 = 1;
    }
}


/* Time functions */
void nRF24_ceSleep() {
    __delay32(500);
}


/* Commands */
void nRF24_readRegister(uint8 radio, uint8 reg, uint8* data, uint8 nBytes) {
    uint8  i;
    uint8* command;

    command = (uint8*) malloc((nBytes+1)*sizeof(uint8));

    command[0] = NRF24_R_REGISTER_COMMAND | reg;

    for (i = 0; i < nBytes; i++) {
        command[i+1] = 0xFF;
    }

    nRF24_exchangeData(radio, command, command, nBytes+1);

    for (i = 0; i < nBytes; i++) {
        data[i] = command[i+1];
    }

    free(command);
}

void nRF24_writeRegister(uint8 radio, uint8 reg, uint8* data, uint8 nBytes) {
    uint8  i;
    uint8* command;

    command = (uint8*) malloc((nBytes+1)*sizeof(uint8));

    command[0] = NRF24_W_REGISTER_COMMAND | reg;

    for (i = 0; i < nBytes; i++) {
        command[i+1] = data[i];
    }

    nRF24_writeData(radio, command, nBytes+1);

    free(command);
}

void nRF24_getReceivedPayload(uint8 radio, uint8* data, uint8* nBytes) {
    uint8  i, j;
    uint8  payloadSize;
    uint8* command;

    payloadSize = nRF24_getReceivedPayloadSize(radio);

    command = (uint8*) malloc((payloadSize+1)*sizeof(uint8));

    command[0] = NRF24_R_RX_PAYLOAD_COMMAND;

    for (i = 0; i < payloadSize; i++) {
        command[i+1] = 0xFF;
    }

    nRF24_exchangeData(radio, command, command, payloadSize+1);

    for (i = 0; i < payloadSize; i++) {
        j = command[i+1];
        data[i] = command[i+1];
    }

    free(command);

    *nBytes = payloadSize;

    nRF24_clearDRInt(radio);
}

void nRF24_sendPayload(uint8 radio, uint8* address, uint8* data, uint8 nBytes, uint8 enableAck) {
    uint8  i;
    uint8* command;

    nRF24_setTxAddress(radio, address);

    command = (uint8*) malloc((nBytes+1)*sizeof(uint8));

    if (enableAck == 0) {
        command[0] = NRF24_W_TX_PAYLOAD_NO_ACK_COMMAND;
    }
    else {
        nRF24_setRxAddress(radio,0,address);
        command[0] = NRF24_W_TX_PAYLOAD_COMMAND;
    }

    for (i = 0; i < nBytes; i++) {
        command[i+1] = data[i];
    }

    nRF24_writeData(radio, command, nBytes+1);

    if (radio == 0) {
        NRF24_CE0 = 1;
        nRF24_ceSleep();
        NRF24_CE0 = 0;
    }
    else {
        NRF24_CE1 = 1;
        nRF24_ceSleep();
        NRF24_CE1 = 0;
    }

    free(command);
}

void nRF24_flushTxFIFO(uint8 radio) {
    uint8 command;

    command = NRF24_FLUSH_TX_COMMAND;

    nRF24_writeData(radio, &command, 1);
}

void nRF24_flushRxFIFO(uint8 radio) {
    uint8 command;

    command = NRF24_FLUSH_RX_COMMAND;

    nRF24_writeData(radio, &command, 1);
}

void nRF24_resendLastPayload(uint8 radio) {
    uint8 command;

    command = NRF24_REUSE_TX_PL_COMMAND;

    nRF24_writeData(radio, &command, 1);
}

uint8 nRF24_getReceivedPayloadSize(uint8 radio) {
    uint8 payloadSize;
    uint8 command[2];

    command[0] = NRF24_R_RX_PL_WID_COMMAND;
    command[1] = 0xFF;

    nRF24_exchangeData(radio, command, command, 2);

    payloadSize = command[1];

    return(payloadSize);
}

void nRF24_setAckPayload(uint8 radio, uint8 pipe, uint8* data, uint8 nBytes) {
    uint8  i;
    uint8* command;

    command = (uint8*) malloc((nBytes+1)*sizeof(uint8));

    command[0] = NRF24_W_ACK_PAYLOAD_COMMAND | pipe;

    for (i = 0; i < nBytes; i++) {
        command[i+1] = data[i];
    }

    nRF24_writeData(radio, command, nBytes+1);

    free(command);
}

void nRF24_setRxActive(uint8 radio) {
    if (radio == 0) {
        NRF24_CE0 = 1;
    }
    else {
        NRF24_CE1 = 1;
    }
}

void nRF24_setStandBy(uint8 radio) {
    if (radio == 0) {
        NRF24_CE0 = 0;
    }
    else {
        NRF24_CE1 = 0;
    }
}


/* Register 0x00 (CONFIG) */
void nRF24_enableDRInt(uint8 radio, uint8 enable) {
    uint8 config;

    nRF24_readRegister(radio, NRF24_REG_CONFIG, &config, 1);

    if (enable == 0) {
        nRF24_setBit(&config, 6);
    }
    else {
        nRF24_clearBit(&config, 6);
    }

    nRF24_writeRegister(radio, NRF24_REG_CONFIG, &config, 1);
}

void nRF24_enableDSInt(uint8 radio, uint8 enable) {
    uint8 config;

    nRF24_readRegister(radio, NRF24_REG_CONFIG, &config, 1);

    if (enable == 0) {
        nRF24_setBit(&config, 5);
    }
    else {
        nRF24_clearBit(&config, 5);
    }

    nRF24_writeRegister(radio, NRF24_REG_CONFIG, &config, 1);
}

void nRF24_enableMaxRTInt(uint8 radio, uint8 enable) {
    uint8 config;

    nRF24_readRegister(radio, NRF24_REG_CONFIG, &config, 1);

    if (enable == 0) {
        nRF24_setBit(&config, 4);
    }
    else {
        nRF24_clearBit(&config, 4);
    }

    nRF24_writeRegister(radio, NRF24_REG_CONFIG, &config, 1);
}

uint8 nRF24_isDRIntEnabled(uint8 radio) {
    uint8 config;
    uint8 isEnabled;

    nRF24_readRegister(radio, NRF24_REG_CONFIG, &config, 1);

    isEnabled = nRF24_getBit(config, 6) ? 0 : 1;

    return(isEnabled);
}

uint8 nRF24_isDSIntEnabled(uint8 radio) {
    uint8 config;
    uint8 isEnabled;

    nRF24_readRegister(radio, NRF24_REG_CONFIG, &config, 1);

    isEnabled = nRF24_getBit(config, 5) ? 0 : 1;

    return(isEnabled);
}

uint8 nRF24_isMaxRTIntEnabled(uint8 radio) {
    uint8 config;
    uint8 isEnabled;

    nRF24_readRegister(radio, NRF24_REG_CONFIG, &config, 1);

    isEnabled = nRF24_getBit(config, 4) ? 0 : 1;

    return(isEnabled);
}

void nRF24_enableCRC(uint8 radio, uint8 enable, uint8 size) {
    uint8 config;

    nRF24_readRegister(radio, NRF24_REG_CONFIG, &config, 1);

    if (enable == 0) {
        nRF24_clearBit(&config, 3);
    }
    else {
        nRF24_setBit(&config, 3);

        if (size == 0) {
            nRF24_clearBit(&config, 2);
        }
        else {
            nRF24_setBit(&config, 2);
        }
    }

    nRF24_writeRegister(radio, NRF24_REG_CONFIG, &config, 1);
}

uint8 nRF24_isCRCEnabled(uint8 radio) {
    uint8 config;
    uint8 isEnabled;

    nRF24_readRegister(radio, NRF24_REG_CONFIG, &config, 1);

    isEnabled = nRF24_getBit(config, 3);

    return(isEnabled);
}

uint8 nRF24_getCRCSize(uint8 radio) {
    uint8 config;
    uint8 size;

    nRF24_readRegister(radio, NRF24_REG_CONFIG, &config, 1);

    size = nRF24_getBit(config, 2);

    return(size);
}

void nRF24_powerUp(uint8 radio) {
    uint8 config;

    nRF24_readRegister(radio, NRF24_REG_CONFIG, &config, 1);

    nRF24_setBit(&config, 1);

    nRF24_writeRegister(radio, NRF24_REG_CONFIG, &config, 1);
}

void nRF24_powerDown(uint8 radio) {
    uint8 config;

    nRF24_readRegister(radio, NRF24_REG_CONFIG, &config, 1);

    nRF24_clearBit(&config, 1);

    nRF24_writeRegister(radio, NRF24_REG_CONFIG, &config, 1);
}

uint8 nRF24_isPowerUp(uint8 radio) {
    uint8 config;
    uint8 isUp;

    nRF24_readRegister(radio, NRF24_REG_CONFIG, &config, 1);

    isUp = nRF24_getBit(config, 1);

    return(isUp);
}

void nRF24_setRx(uint8 radio) {
    uint8 config;

    nRF24_readRegister(radio, NRF24_REG_CONFIG, &config, 1);

    nRF24_setBit(&config, 0);

    nRF24_writeRegister(radio, NRF24_REG_CONFIG, &config, 1);
}

void nRF24_setTx(uint8 radio) {
    uint8 config;

    nRF24_readRegister(radio, NRF24_REG_CONFIG, &config, 1);

    nRF24_clearBit(&config, 0);

    nRF24_writeRegister(radio, NRF24_REG_CONFIG, &config, 1);
}

uint8 nRF24_isRx(uint8 radio) {
    uint8 config;
    uint8 isRx;

    nRF24_readRegister(radio, NRF24_REG_CONFIG, &config, 1);

    isRx = nRF24_getBit(config, 0);

    return(isRx);
}

uint8 nRF24_isTx(uint8 radio) {
    uint8 config;
    uint8 isTx;

    nRF24_readRegister(radio, NRF24_REG_CONFIG, &config, 1);

    isTx = nRF24_getBit(config, 0) ? 0 : 1;

    return(isTx);
}


/* Register 0x01 (EN_AA) */
void nRF24_enableAutoAck(uint8 radio, uint8 pipe, uint8 enable) {
    uint8 enAA;

    nRF24_readRegister(radio, NRF24_REG_EN_AA, &enAA, 1);

    if (enable == 0) {
        nRF24_clearBit(&enAA, pipe);
    }
    else {
        nRF24_setBit(&enAA, pipe);
    }

    nRF24_writeRegister(radio, NRF24_REG_EN_AA, &enAA, 1);
}

uint8 nRF24_isAutoAckEnabled(uint8 radio, uint8 pipe) {
    uint8 enAA;
    uint8 isEnabled;

    nRF24_readRegister(radio, NRF24_REG_EN_AA, &enAA, 1);

    isEnabled = nRF24_getBit(enAA, pipe);

    return(isEnabled);
}


/* Register 0x02 (EN_RXADDR) */
void nRF24_enableRxPipe(uint8 radio, uint8 pipe, uint8 enable) {
    uint8 enRxAddr;

    nRF24_readRegister(radio, NRF24_REG_EN_RXADDR, &enRxAddr, 1);

    if (enable == 0) {
        nRF24_clearBit(&enRxAddr, pipe);
    }
    else {
        nRF24_setBit(&enRxAddr, pipe);
    }

    nRF24_writeRegister(radio, NRF24_REG_EN_RXADDR, &enRxAddr, 1);
}

uint8 nRF24_isRxPipeEnabled(uint8 radio, uint8 pipe) {
    uint8 enRxAddr;
    uint8 isEnabled;

    nRF24_readRegister(radio, NRF24_REG_EN_RXADDR, &enRxAddr, 1);

    isEnabled = nRF24_getBit(enRxAddr, pipe);

    return(isEnabled);
}


/* Register 0x03 (SETUP_AW) */
void nRF24_setAddressSize(uint8 radio, uint8 size) {
    uint8 setupAw;

    nRF24_readRegister(radio, NRF24_REG_SETUP_AW, &setupAw, 1);

    switch (size) {
        case 1: {
            nRF24_clearBit(&setupAw, 1);
            nRF24_setBit(&setupAw, 0);
            break;
        }

        case 2: {
            nRF24_setBit(&setupAw, 1);
            nRF24_clearBit(&setupAw, 0);
            break;
        }

        case 3: {
            nRF24_setBit(&setupAw, 1);
            nRF24_setBit(&setupAw, 0);
            break;
        }

        default: {
            return;
        }
    }

    nRF24_writeRegister(radio, NRF24_REG_SETUP_AW, &setupAw, 1);
}

uint8 nRF24_getAddressSize(uint8 radio) {
    uint8 setupAw;
    uint8 size;

    nRF24_readRegister(radio, NRF24_REG_SETUP_AW, &setupAw, 1);

    size = nRF24_getBit(setupAw, 0) | (nRF24_getBit(setupAw, 1) << 1);

    return(size);
}



/* Register 0x04 (SETUP_RETR) */
void nRF24_setAutoRetransmitDelay(uint8 radio, uint8 delay) {
    uint8 setupRetr;

    nRF24_readRegister(radio, NRF24_REG_SETUP_RETR, &setupRetr, 1);

    setupRetr &= 0x0F;
    setupRetr |= delay << 4;

    nRF24_writeRegister(radio, NRF24_REG_SETUP_RETR, &setupRetr, 1);
}

void nRF24_setAutoRetransmitCount(uint8 radio, uint8 count) {
    uint8 setupRetr;

    nRF24_readRegister(radio, NRF24_REG_SETUP_RETR, &setupRetr, 1);

    setupRetr &= 0xF0;
    setupRetr |= count;

    nRF24_writeRegister(radio, NRF24_REG_SETUP_RETR, &setupRetr, 1);
}

uint8 nRF24_getAutoRetransmitDelay(uint8 radio) {
    uint8 setupRetr;
    uint8 delay;

    nRF24_readRegister(radio, NRF24_REG_SETUP_RETR, &setupRetr, 1);

    delay = (setupRetr >> 4) & 0x0F;

    return(delay);
}

uint8 nRF24_getAutoRetransmitCount(uint8 radio) {
    uint8 setupRetr;
    uint8 count;

    nRF24_readRegister(radio, NRF24_REG_SETUP_RETR, &setupRetr, 1);

    count = setupRetr & 0x0F;

    return(count);
}


/* Register 0x05 (RF_CH) */
void nRF24_setChannel(uint8 radio, uint8 channel) {
    nRF24_writeRegister(radio, NRF24_REG_RF_CH, &channel, 1);
}

uint8 nRF24_getChannel(uint8 radio) {
    uint8 channel;

    nRF24_readRegister(radio, NRF24_REG_RF_CH, &channel, 1);

    return(channel);
}


/* Register 0x06 (RF_SETUP) */
void nRF24_enableCarrierTest(uint8 radio, uint8 enable) {
    uint8 rfSetup;

    nRF24_readRegister(radio, NRF24_REG_RF_SETUP, &rfSetup, 1);

    if (enable == 0) {
        nRF24_clearBit(&rfSetup, 7);
    }
    else {
        nRF24_setBit(&rfSetup, 7);
    }

    nRF24_writeRegister(radio, NRF24_REG_RF_SETUP, &rfSetup, 1);
}

uint8 nRF24_isCarrierTestEnabled(uint8 radio) {
    uint8 rfSetup;
    uint8 isEnabled;

    nRF24_readRegister(radio, NRF24_REG_RF_SETUP, &rfSetup, 1);

    isEnabled = nRF24_getBit(rfSetup, 7);

    return(isEnabled);
}

void nRF24_enablePLLLock(uint8 radio, uint8 enable) {
    uint8 rfSetup;

    nRF24_readRegister(radio, NRF24_REG_RF_SETUP, &rfSetup, 1);

    if (enable == 0) {
        nRF24_clearBit(&rfSetup, 4);
    }
    else {
        nRF24_setBit(&rfSetup, 4);
    }

    nRF24_writeRegister(radio, NRF24_REG_RF_SETUP, &rfSetup, 1);
}

uint8 nRF24_isPLLLockEnabled(uint8 radio) {
    uint8 rfSetup;
    uint8 isEnabled;

    nRF24_readRegister(radio, NRF24_REG_RF_SETUP, &rfSetup, 1);

    isEnabled = nRF24_getBit(rfSetup, 4);

    return(isEnabled);
}

void nRF24_setDataRate(uint8 radio, uint8 dataRate) {
    uint8 rfSetup;

    nRF24_readRegister(radio, NRF24_REG_RF_SETUP, &rfSetup, 1);

    switch (dataRate) {
        case 0: {
            nRF24_clearBit(&rfSetup, 5);
            nRF24_clearBit(&rfSetup, 3);
            break;
        }

        case 1: {
            nRF24_clearBit(&rfSetup, 5);
            nRF24_setBit(&rfSetup, 3);
            break;
        }

        case 2: {
            nRF24_setBit(&rfSetup, 5);
            nRF24_clearBit(&rfSetup, 3);
            break;
        }

        default: {
            return;
        }
    }

    nRF24_writeRegister(radio, NRF24_REG_RF_SETUP, &rfSetup, 1);
}

uint8 nRF24_getDataRate(uint8 radio) {
    uint8 rfSetup;
    uint8 dataRate;

    nRF24_readRegister(radio, NRF24_REG_RF_SETUP, &rfSetup, 1);

    dataRate = nRF24_getBit(rfSetup, 3) | (nRF24_getBit(rfSetup, 5) << 1);

    return(dataRate);
}

void nRF24_setRFPower(uint8 radio, uint8 power) {
    uint8 rfSetup;

    nRF24_readRegister(radio, NRF24_REG_RF_SETUP, &rfSetup, 1);

    switch (power) {
        case 0: {
            nRF24_clearBit(&rfSetup, 2);
            nRF24_clearBit(&rfSetup, 1);
            break;
        }

        case 1: {
            nRF24_clearBit(&rfSetup, 2);
            nRF24_setBit(&rfSetup, 1);
            break;
        }

        case 2: {
            nRF24_setBit(&rfSetup, 2);
            nRF24_clearBit(&rfSetup, 1);
            break;
        }

        case 3: {
            nRF24_setBit(&rfSetup, 2);
            nRF24_setBit(&rfSetup, 1);
            break;
        }

        default: {
            return;
        }
    }

    nRF24_writeRegister(radio, NRF24_REG_RF_SETUP, &rfSetup, 1);
}

uint8 nRF24_getRFPower(uint8 radio) {
    uint8 rfSetup;
    uint8 power;

    nRF24_readRegister(radio, NRF24_REG_RF_SETUP, &rfSetup, 1);

    power = nRF24_getBit(rfSetup, 1) | (nRF24_getBit(rfSetup, 2) << 1);

    return(power);
}


/* Register 0x07 (STATUS) */
uint8 nRF24_getDRInt(uint8 radio) {
    uint8 status;
    uint8 drInt;

    nRF24_readRegister(radio, NRF24_REG_STATUS, &status, 1);

    drInt = nRF24_getBit(status, 6);

    return(drInt);
}

uint8 nRF24_getDSInt(uint8 radio) {
    uint8 status;
    uint8 dsInt;

    nRF24_readRegister(radio, NRF24_REG_STATUS, &status, 1);

    dsInt = nRF24_getBit(status, 5);

    return(dsInt);
}

uint8 nRF24_getMaxRTInt(uint8 radio) {
    uint8 status;
    uint8 maxRtInt;

    nRF24_readRegister(radio, NRF24_REG_STATUS, &status, 1);

    maxRtInt = nRF24_getBit(status, 4);

    return(maxRtInt);
}

void nRF24_clearDRInt(uint8 radio) {
    uint8 status;

    nRF24_readRegister(radio, NRF24_REG_STATUS, &status, 1);

    nRF24_setBit(&status, 6);

    nRF24_writeRegister(radio, NRF24_REG_STATUS, &status, 1);
}

void nRF24_clearDSInt(uint8 radio) {
    uint8 status;

    nRF24_readRegister(radio, NRF24_REG_STATUS, &status, 1);

    nRF24_setBit(&status, 5);

    nRF24_writeRegister(radio, NRF24_REG_STATUS, &status, 1);
}

void nRF24_clearMaxRTInt(uint8 radio) {
    uint8 status;

    nRF24_readRegister(radio, NRF24_REG_STATUS, &status, 1);

    nRF24_setBit(&status, 4);

    nRF24_writeRegister(radio, NRF24_REG_STATUS, &status, 1);
}

uint8 nRF24_getRxFIFOSource(uint8 radio) {
    uint8 status;
    uint8 source;

    nRF24_readRegister(radio, NRF24_REG_STATUS, &status, 1);

    source = nRF24_getBit(status, 1) | (nRF24_getBit(status, 2) << 1) | (nRF24_getBit(status, 3) << 2);

    return(source);
}


/* Register 0x08 (OBSERVE_TX) */
uint8 nRF24_getLostPacketsCount(uint8 radio) {
    uint8 observeTx;
    uint8 count;

    nRF24_readRegister(radio, NRF24_REG_OBSERVE_TX, &observeTx, 1);

    count = (observeTx >> 4) & 0x0F;

    return(count);
}

uint8 nRF24_getRetransmitsCount(uint8 radio) {
    uint8 observeTx;
    uint8 count;

    nRF24_readRegister(radio, NRF24_REG_OBSERVE_TX, &observeTx, 1);

    count = observeTx & 0x0F;

    return(count);
}


/* Register 0x09 (RPD) */
uint8 nRF24_getReceivedPower(uint8 radio) {
    uint8 rpd;
    uint8 power;

    nRF24_readRegister(radio, NRF24_REG_RPD, &rpd, 1);

    power = nRF24_getBit(rpd, 0);

    return(power);
}


/* Registers 0x0A to 0x0F (RX_ADDR_Px) */
void nRF24_setRxAddress(uint8 radio, uint8 pipe, uint8* addr) {
    uint8  i;
    uint8  addrSize;
    uint8  firstCommand;
    uint8  commandSize;
    uint8* command;

    addrSize  = nRF24_getAddressSize(radio);
    addrSize += 2;

    switch (pipe) {
        case 0: {
            firstCommand = NRF24_W_REGISTER_COMMAND | NRF24_REG_RX_ADDR_P0;
            commandSize  = addrSize+1;
            break;
        }

        case 1: {
            firstCommand = NRF24_W_REGISTER_COMMAND | NRF24_REG_RX_ADDR_P1;
            commandSize  = addrSize+1;
            break;
        }

        case 2: {
            firstCommand = NRF24_W_REGISTER_COMMAND | NRF24_REG_RX_ADDR_P2;
            commandSize  = 2;
            break;
        }

        case 3: {
            firstCommand = NRF24_W_REGISTER_COMMAND | NRF24_REG_RX_ADDR_P3;
            commandSize  = 2;
            break;
        }

        case 4: {
            firstCommand = NRF24_W_REGISTER_COMMAND | NRF24_REG_RX_ADDR_P4;
            commandSize  = 2;
            break;
        }

        case 5: {
            firstCommand = NRF24_W_REGISTER_COMMAND | NRF24_REG_RX_ADDR_P5;
            commandSize  = 2;
            break;
        }

        default: {
            return;
        }
    }

    command = (uint8*) malloc(commandSize*sizeof(uint8));

    command[0] = firstCommand;

    for (i = 0; i < (commandSize-1); i++) {
        command[i+1] = addr[i];
    }

    nRF24_writeData(radio, command, commandSize);

    free(command);
}

void nRF24_getRxAddress(uint8 radio, uint8 pipe, uint8* data) {
    uint8  i;
    uint8  addrSize;
    uint8  tmpAddr;
    uint8* command;

    addrSize  = nRF24_getAddressSize(radio);
    addrSize += 2;

    command = (uint8*) malloc((addrSize+1)*sizeof(uint8));

    for (i = 0; i < addrSize+1; i++) {
        command[i] = 0xFF;
    }

    if (pipe == 0) {
        command[0] = NRF24_R_REGISTER_COMMAND | NRF24_REG_RX_ADDR_P0;
        nRF24_exchangeData(radio, command, command, addrSize+1);
    }

    else {
        command[0] = NRF24_R_REGISTER_COMMAND | NRF24_REG_RX_ADDR_P1;
        nRF24_exchangeData(radio, command, command, addrSize+1);

        switch (pipe) {
            case 2: {
                nRF24_readRegister(radio, NRF24_REG_RX_ADDR_P2, &tmpAddr, 1);
                command[addrSize] = tmpAddr;
                break;
            }

            case 3: {
                nRF24_readRegister(radio, NRF24_REG_RX_ADDR_P3, &tmpAddr, 1);
                command[addrSize] = tmpAddr;
                break;
            }

            case 4: {
                nRF24_readRegister(radio, NRF24_REG_RX_ADDR_P4, &tmpAddr, 1);
                command[addrSize] = tmpAddr;
                break;
            }

            case 5: {
                nRF24_readRegister(radio, NRF24_REG_RX_ADDR_P5, &tmpAddr, 1);
                command[addrSize] = tmpAddr;
                break;
            }
        }
    }

    for (i = 0; i < addrSize; i++) {
        data[i] = command[i+1];
    }

    free(command);
}


/* Register 0x10 (TX_ADDR) */
void nRF24_setTxAddress(uint8 radio, uint8* addr) {
    uint8  i;
    uint8  addrSize;
    uint8* command;

    addrSize  = nRF24_getAddressSize(radio);
    addrSize += 2;

    command = (uint8*) malloc((addrSize+1)*sizeof(uint8));

    command[0] = NRF24_W_REGISTER_COMMAND | NRF24_REG_TX_ADDR;

    for (i = 0; i < addrSize; i++) {
        command[i+1] = addr[i];
    }

    nRF24_writeData(radio, command, addrSize+1);

    free(command);
}

void nRF24_getTxAddress(uint8 radio, uint8* data) {
    uint8  i;
    uint8  addrSize;
    uint8* command;

    addrSize  = nRF24_getAddressSize(radio);
    addrSize += 2;

    command = (uint8*) malloc((addrSize+1)*sizeof(uint8));

    for (i = 0; i < addrSize+1; i++) {
        command[i] = 0xFF;
    }

    command[0] = NRF24_R_REGISTER_COMMAND | NRF24_REG_TX_ADDR;
    nRF24_exchangeData(radio, command, command, addrSize+1);

    for (i = 0; i < addrSize; i++) {
        data[i] = command[i+1];
    }

    free(command);
}


/* Registers 0x11 to 0x16 (RX_PW_Px) */
void nRF24_setRxPayloadSize(uint8 radio, uint8 pipe, uint8 size) {
    switch (pipe) {
        case 0: {
            nRF24_writeRegister(radio, NRF24_REG_RX_PW_P0, &size, 1);
            break;
        }

        case 1: {
            nRF24_writeRegister(radio, NRF24_REG_RX_PW_P1, &size, 1);
            break;
        }

        case 2: {
            nRF24_writeRegister(radio, NRF24_REG_RX_PW_P2, &size, 1);
            break;
        }

        case 3: {
            nRF24_writeRegister(radio, NRF24_REG_RX_PW_P3, &size, 1);
            break;
        }

        case 4: {
            nRF24_writeRegister(radio, NRF24_REG_RX_PW_P4, &size, 1);
            break;
        }

        case 5: {
            nRF24_writeRegister(radio, NRF24_REG_RX_PW_P5, &size, 1);
            break;
        }
    }
}

uint8 nRF24_getRxPayloadSize(uint8 radio, uint8 pipe) {
    uint8 payloadSize;

    switch (pipe) {
        case 0: {
            nRF24_readRegister(radio, NRF24_REG_RX_PW_P0, &payloadSize, 1);
            break;
        }

        case 1: {
            nRF24_readRegister(radio, NRF24_REG_RX_PW_P1, &payloadSize, 1);
            break;
        }

        case 2: {
            nRF24_readRegister(radio, NRF24_REG_RX_PW_P2, &payloadSize, 1);
            break;
        }

        case 3: {
            nRF24_readRegister(radio, NRF24_REG_RX_PW_P3, &payloadSize, 1);
            break;
        }

        case 4: {
            nRF24_readRegister(radio, NRF24_REG_RX_PW_P4, &payloadSize, 1);
            break;
        }

        case 5: {
            nRF24_readRegister(radio, NRF24_REG_RX_PW_P5, &payloadSize, 1);
            break;
        }

        default: {
            payloadSize = 0xFF;
            break;
        }
    }

    return(payloadSize);
}


/* Register 0x17 (FIFO_STATUS) */
uint8 nRF24_isTxReuseEnabled(uint8 radio) {
    uint8 fifoStatus;
    uint8 isEnabled;

    nRF24_readRegister(radio, NRF24_REG_FIFO_STATUS, &fifoStatus, 1);

    isEnabled = nRF24_getBit(fifoStatus, 6);

    return(isEnabled);
}

uint8 nRF24_isTxFIFOFull(uint8 radio) {
    uint8 fifoStatus;
    uint8 isEnabled;

    nRF24_readRegister(radio, NRF24_REG_FIFO_STATUS, &fifoStatus, 1);

    isEnabled = nRF24_getBit(fifoStatus, 5);

    return(isEnabled);
}

uint8 nRF24_isTxFIFOEmpty(uint8 radio) {
    uint8 fifoStatus;
    uint8 isEnabled;

    nRF24_readRegister(radio, NRF24_REG_FIFO_STATUS, &fifoStatus, 1);

    isEnabled = nRF24_getBit(fifoStatus, 4);

    return(isEnabled);
}

uint8 nRF24_isRxFIFOFull(uint8 radio) {
    uint8 fifoStatus;
    uint8 isEnabled;

    nRF24_readRegister(radio, NRF24_REG_FIFO_STATUS, &fifoStatus, 1);

    isEnabled = nRF24_getBit(fifoStatus, 1);

    return(isEnabled);
}

uint8 nRF24_isRxFIFOEmpty(uint8 radio) {
    uint8 fifoStatus;
    uint8 isEnabled;

    nRF24_readRegister(radio, NRF24_REG_FIFO_STATUS, &fifoStatus, 1);

    isEnabled = nRF24_getBit(fifoStatus, 0);

    return(isEnabled);
}


/* Register 0x1C (DYNPD) */
void nRF24_enableDynamicPayloadSize(uint8 radio, uint8 pipe, uint8 enable) {
    uint8 dynpd;

    nRF24_readRegister(radio, NRF24_REG_DYNPD, &dynpd, 1);

    if (enable == 0) {
        nRF24_clearBit(&dynpd, pipe);
    }
    else {
        nRF24_setBit(&dynpd, pipe);
    }

    nRF24_writeRegister(radio, NRF24_REG_DYNPD, &dynpd, 1);
}

uint8 nRF24_isDynamicPayloadSizeEnabled(uint8 radio, uint8 pipe) {
    uint8 dynpd;
    uint8 isEnabled;

    nRF24_readRegister(radio, NRF24_REG_DYNPD, &dynpd, 1);

    isEnabled = nRF24_getBit(dynpd, pipe);

    return(isEnabled);
}


/* Register 0x1D (FEATURE) */
void nRF24_allowDynamicPayloadSize(uint8 radio, uint8 allow) {
    uint8 feature;

    nRF24_readRegister(radio, NRF24_REG_FEATURE, &feature, 1);

    if (allow == 0) {
        nRF24_clearBit(&feature, 2);
    }
    else {
        nRF24_setBit(&feature, 2);
    }

    nRF24_writeRegister(radio, NRF24_REG_FEATURE, &feature, 1);
}

uint8 nRF24_isDynamicPayloadSizeAllowed(uint8 radio) {
    uint8 feature;
    uint8 isEnabled;

    nRF24_readRegister(radio, NRF24_REG_FEATURE, &feature, 1);

    isEnabled = nRF24_getBit(feature, 2);

    return(isEnabled);
}

void nRF24_enableAckPayload(uint8 radio, uint8 enable) {
    uint8 feature;

    nRF24_readRegister(radio, NRF24_REG_FEATURE, &feature, 1);

    if (enable == 0) {
        nRF24_clearBit(&feature, 1);
    }
    else {
        nRF24_setBit(&feature, 1);
    }

    nRF24_writeRegister(radio, NRF24_REG_FEATURE, &feature, 1);
}

uint8 nRF24_isAckPayloadEnabled(uint8 radio) {
    uint8 feature;
    uint8 isEnabled;

    nRF24_readRegister(radio, NRF24_REG_FEATURE, &feature, 1);

    isEnabled = nRF24_getBit(feature, 1);

    return(isEnabled);
}

void nRF24_enableDynamicAckPayload(uint8 radio, uint8 enable) {
    uint8 feature;

    nRF24_readRegister(radio, NRF24_REG_FEATURE, &feature, 1);

    if (enable == 0) {
        nRF24_clearBit(&feature, 0);
    }
    else {
        nRF24_setBit(&feature, 0);
    }

    nRF24_writeRegister(radio, NRF24_REG_FEATURE, &feature, 1);
}

uint8 nRF24_isDynamicAckPayloadEnabled(uint8 radio) {
    uint8 feature;
    uint8 isEnabled;

    nRF24_readRegister(radio, NRF24_REG_FEATURE, &feature, 1);

    isEnabled = nRF24_getBit(feature, 0);

    return(isEnabled);
}
