/*** WRStation - SerialInterface module implementation
  ** Warthog Robotics
  ** University of Sao Paulo at Sao Carlos
  ** http://www.warthog.sc.usp.br
  ** This file is part of the Warthog Robotics Station project
  ***/


/* Includes WRStation */
#include <WRStation/wrstation.h>

/* Includes dsPIC libraries */
#include <p33Fxxxx.h>
#include <math.h>
#include <dma.h>
#include <uart.h>

/* Includes C standard libraries */
#include <stdlib.h>
#include <string.h>
#include <libpic30.h>


#define PAYLOAD_SIZE 28
uint8 DEST_STATION_ADDRESS[5] = {'W', 'R', 'R', 'X', '0'};

/* Module internal variables */
uint32 serialInterface_baudRate = SERIALINTERFACE_BAUD_RATE;
uint16 serialInterface_rxBuffer[64] __attribute__((space(dma),aligned(16)));
uint16 serialInterface_txBuffer[64] __attribute__((space(dma),aligned(16)));
uint8  serialInterface_txBufferDataSize;


void serialInterface_initialize() {
    /* Configures the ports used by the module */
    serialInterface_configurePorts();

    /* Configures Rx DMA */
    serialInterface_configureRxDMA();

    /* Configures Tx DMA */
    serialInterface_configureTxDMA();

    /* Initializes the UART module */
    serialInterface_initializeUART();
}


void serialInterface_configurePorts() {

}


void serialInterface_configureRxDMA() {
    /* Configures the DMA to Continuous Mode without Ping-Pong
       (Refer to "dma.h" and "Section 38. Direct Memory Access (DMA) (Part III)" for further information) */
    CloseDMA0();
    DMA0CONbits.SIZE  = 0;
    DMA0CONbits.DIR   = 0;
    DMA0CONbits.AMODE = 0;
    DMA0CONbits.MODE  = 0;

    DMA0REQbits.IRQSEL = 11;

    DMA0STA = __builtin_dmaoffset(serialInterface_rxBuffer);

    DMA0PAD = (volatile uint16) &U1RXREG;

    DMA0CNT = (PAYLOAD_SIZE - 1);

    /* Enables DMA interruption */
    ConfigIntDMA0(DMA0_INT_ENABLE & DMA0_INT_PRI_5);
}


void serialInterface_configureTxDMA() {
    /* Configures the DMA to One-Shot Mode
       (Refer to "dma.h" and "Section 38. Direct Memory Access (DMA) (Part III)" for further information) */
    CloseDMA1();
    DMA1CONbits.SIZE  = 0;
    DMA1CONbits.DIR   = 1;
    DMA1CONbits.AMODE = 0;
    DMA1CONbits.MODE  = 1;

    DMA1REQbits.IRQSEL = 12;

    DMA1STA = __builtin_dmaoffset(serialInterface_txBuffer);

    DMA1PAD = (volatile uint16) &U1TXREG;

    /* Enables DMA interruption */
    ConfigIntDMA1(DMA1_INT_DISABLE & DMA1_INT_PRI_4);
}


void serialInterface_initializeUART() {
    /* Variables */
    uint16 brg;
    float  brgFloat;

    /* Configures UART remappable pins */
    __builtin_write_OSCCONL(OSCCONL & 0xBF);
    RPINR18bits.U1RXR            = SERIALINTERFACE_MCU_RX_RPIN;
    RPINR18bits.U1CTSR           = SERIALINTERFACE_MCU_CTS_RPIN;
    SERIALINTERFACE_MCU_TX_RPOR  = 3;
    SERIALINTERFACE_MCU_RTS_RPOR = 4;
    __builtin_write_OSCCONL(OSCCONL | 0x40);

    /* Calculates BRG register according to desired baud rate */
    brgFloat = ((NORDICSTATION_Fcy*1000.0) / (4.0*serialInterface_baudRate)) - 1.0;

    /* Rounds and casts it to integer */
    brg = (uint16) floor(brgFloat);
    if ((brgFloat-floor(brgFloat)) > 0.5) {
        brg++;
    }

    /* Configures UART with flow control
       (Refer to "uart.h" and "Section 17. UART" for further information) */
    CloseUART1();

    U1MODEbits.UEN   = 2; // Uses Rx, Tx, CTS, RTS
    U1MODEbits.PDSEL = 0; // 8 bit, no parity
    U1MODEbits.STSEL = 0; // 1 stop bit

    U1MODEbits.BRGH = 1;
    U1BRG           = brg;
}


void serialInterface_start() {
    /* Starts Rx DMA */
    DMA0CONbits.CHEN = 1;

    /* Configures UART interruptions */
    ConfigIntUART1(UART_RX_INT_DIS & UART_RX_INT_PR5 & UART_TX_INT_DIS); // TODO: Passar para uma funcao melhor

    /* Enables UART module */
    U1MODEbits.UARTEN = 1;
    U1STAbits.UTXEN   = 1;
}


void serialInterface_stop() {

}


void serialInterface_sendData(uint8 size, uint8* data) {
    /* Variables */
    uint8 i;

    /* Sets the size of the data */
    serialInterface_txBufferDataSize = size;
    DMA1CNT = serialInterface_txBufferDataSize - 1;

    /* Copies the data to the buffer */
    for (i = 0; i < serialInterface_txBufferDataSize; i++) {
        serialInterface_txBuffer[i] =  data[i];
    }

    /* Starts DMA transfer */
    DMA1CONbits.CHEN  = 1;
    DMA1REQbits.FORCE = 1;
}


void __attribute__((__interrupt__,no_auto_psv)) _U1RXInterrupt() {
    char c, i;

    c = ReadUART1();
    i = 0;

    WriteUART1(c);

    IFS0bits.U1RXIF = 0;
}

void __attribute__((__interrupt__,no_auto_psv)) _DMA0Interrupt() {   
    PORTBbits.RB15 = 1; // LED
    
    /* Repeats the command to the radio */
    command_sendPayload(DEST_STATION_ADDRESS, PAYLOAD_SIZE, serialInterface_rxBuffer);
    
    /* Debug serial return */
    unsigned char buffer[128];
    buffer[0] = '\0';
    strcat(buffer, "TX: ");
    
    int i=0;
    for(i=0; i<PAYLOAD_SIZE; i++) {
        unsigned char cat[16];
        sprintf(cat, "%02X ", serialInterface_rxBuffer[i] & 0xFF);
        
        strcat(buffer, cat);
    }
    strcat(buffer, "\r\n");
    serialInterface_sendData(strlen(buffer), buffer);
    
    PORTBbits.RB15 = 0; // LED
    
    /* Clears the interrupt flag */
    IFS0bits.DMA0IF = 0;
}