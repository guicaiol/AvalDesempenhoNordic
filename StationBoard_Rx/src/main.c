/*** StationBoard - StationBoard main application
  ** Warthog Robotics
  ** University of Sao Paulo at Sao Carlos
  ** http://www.warthog.sc.usp.br
  ** This file is part of the Warthog Robotics Station project
  ***/


/* Includes StationBoard */
#include <StationBoard/stationboard.h>

/* Includes dsPIC libraries */
#include <p33Fxxxx.h>


/* dsPIC configuration bits */
_FOSCSEL(FNOSC_FRC & IESO_OFF)
_FOSC(FCKSM_CSECME & OSCIOFNC_ON & POSCMD_NONE  & IOL1WAY_OFF)
_FWDT(FWDTEN_OFF   & WINDIS_OFF)
_FPOR(PWMPIN_ON    & HPOL_ON      & LPOL_ON     & FPWRT_PWR1)
_FICD(ICS_PGD2     & JTAGEN_OFF)


int main() {
    /* Creates and initializes the radio station */
    stationBoard_initialize();
    
    /* Starts the radio station */
    stationBoard_start();

    /* Should never get here! */
    return(0);
}




//void configOscillator() {
//    /* Refer to "Section 7. Oscillator" for further information */
//
//    /* Configures the PLL values to get Fcy = 7.37 MHz*43/4 = 39613750 Hz */
//    PLLFBD = 41;
//    CLKDIVbits.PLLPOST = 0;
//    CLKDIVbits.PLLPRE  = 0;
//
//    /* Selects FRC with PLL as the new source */
//    __builtin_write_OSCCONH(0x01);
//
//    /* Switches the clock sources */
//    __builtin_write_OSCCONL(0x01);
//    while (OSCCONbits.OSWEN != 0) {}
//
//    /* Waits for the PLL to lock */
//    while (OSCCONbits.LOCK != 1) {}
//}
//
//
//void configLEDs() {
//    TRISBbits.TRISB6 = 1;
//    TRISBbits.TRISB7 = 1;
//    TRISBbits.TRISB8 = 1;
//    TRISBbits.TRISB9 = 1;
//
//    TRISBbits.TRISB13 = 0;
//    TRISBbits.TRISB14 = 0;
//    TRISBbits.TRISB15 = 0;
//}
//
//
///* MainBoard protocol */
//typedef struct WRMagicCommand CommandData;
//
//
///* 2011 Warthog Robotics WRMagic project protocol */
//struct WRMagicCommand {
//    uint32 nonce;
//    float  motorSpeed[4];
//    float  dribblerSpeed;
//    uint8  kickType;
//    uint8  kickPower;
//};
//
//
//#define COMMAND_CHANNEL_A 125 /* Command input main channel */
//#define COMMAND_CHANNEL_B 105 /* Command input alternative channel */
//
//#define COMMAND_PLAYER_ADDR_SIZE 5  /* Number of bytes of player address */
//#define COMMAND_PROTOCOL_SIZE    26 /* Number of bytes of the command protocol */
//
//uint8 command_playerAddress[COMMAND_PLAYER_ADDR_SIZE] = {'W','R','M','S','T'};
//uint8 command_buffer[26];
//
//void configRadio() {
//    /* Configures the radio operation mode
//       Refer to "nRF24L01/nRF24L01.h" for further information */
//    nRF24_init(0);
//
//    nRF24_setAddressSize(0, COMMAND_PLAYER_ADDR_SIZE-2);
//    nRF24_setRxAddress(0, 1, command_playerAddress);
//
//    nRF24_enableRxPipe(0,0,1);
//    nRF24_enableRxPipe(0,1,1);
//    nRF24_setRxPayloadSize(0, 0, COMMAND_PROTOCOL_SIZE);
//    nRF24_setRxPayloadSize(0, 1, COMMAND_PROTOCOL_SIZE);
//
//    nRF24_setChannel(0, COMMAND_CHANNEL_B);
//    nRF24_setDataRate(0, 0);
//
//    nRF24_setAutoRetransmitDelay(0, 0);
//    nRF24_setAutoRetransmitCount(0, 0);
//
//    nRF24_enableAutoAck(0, 0, 0);
//    nRF24_enableAutoAck(0, 1, 0);
//
//    nRF24_enableDSInt(0, 0);
//    nRF24_enableMaxRTInt(0, 0);
//
//    nRF24_setTx(0);
//
//    nRF24_powerUp(0);
//}
//
//
//void command_encodeCommand(uint8* command_buffer, CommandData* data) {
//    /* Variables */
//    uint8 i;
//
//    /* Gets the nonce */
//    memcpy((void*) command_buffer, (void*) &(data->nonce), 4);
//
//    /* Gets the motors speeds */
//    for (i = 0; i < 4; i++) {
//        memcpy((void*) command_buffer+4+4*i, (void*) &(data->motorSpeed[i]), 4);
//    }
//
//    memcpy((void*) command_buffer+20, (void*) &(data->dribblerSpeed), 4);
//
//    /* Gets kick information */
//    memcpy((void*) command_buffer+24, (void*) &(data->kickType), 1);
//    memcpy((void*) command_buffer+25, (void*) &(data->kickPower), 1);
//}
//
//
//void configUART() {
//    __builtin_write_OSCCONL(OSCCONL & 0xBF);
//    RPINR18bits.U1RXR  = 9; // Rx
//    RPINR18bits.U1CTSR = 8; // CTS
//    RPOR3bits.RP7R     = 3; // Tx
//    RPOR3bits.RP6R     = 4; // RTS
//    __builtin_write_OSCCONL(OSCCONL | 0x40);
//
//    CloseUART1();
//    /*OpenUART1(UART_EN & UART_UEN_00 &
//              UART_MODE_FLOW & UART_DIS_LOOPBACK &
//              UART_DIS_ABAUD & UART_NO_PAR_8BIT &
//              UART_BRGH_FOUR & UART_1STOPBIT,
//              UART_SYNC_BREAK_DISABLED & UART_TX_ENABLE &
//              UART_RX_OVERRUN_CLEAR & UART_INT_RX_CHAR & UART_INT_TX,
//              257);
//    ConfigIntUART1(UART_RX_INT_EN & UART_RX_INT_PR6 & UART_TX_INT_DIS);*/
//
//    U1MODEbits.UEN   = 2; // Uses Rx, Tx, CTS, RTS
//    U1MODEbits.PDSEL = 0; // 8 bit, no parity
//    U1MODEbits.STSEL = 0; // 1 stop bit
//
//    U1MODEbits.BRGH = 1;
//    U1BRG           = 85; // Baud = 38400
//
//    ConfigIntUART1(UART_RX_INT_EN & UART_RX_INT_PR6 & UART_TX_INT_DIS);
//
//    U1MODEbits.UARTEN = 1;
//
//    U1STAbits.UTXEN = 1; // Tx enabled
//}
//
//
//int main() {
//    configOscillator();
//
//    /*CommandData comando;
//    uint8 command_buffer[26];
//    uint8 player[5] = {'W','R','M','0','6'};
//    uint8 i, j;
//
//    comando.nonce = 0;
//    comando.dribblerSpeed = 0.0;
//    comando.motorSpeed[0] = 0.0;
//    comando.motorSpeed[1] = 1.0;
//    comando.motorSpeed[2] = 0.0;
//    comando.motorSpeed[3] = 0.0;
//    comando.kickPower = 0;
//    comando.kickType  = 0;
//
//
//
//    configLEDs();
//
//    configRadio();
//
//    i = nRF24_getAddressSize(0);
//
//    j = 0;*/
//
//    configUART();
//
//    while (1) {
//        /*__delay32(4000000);
//        LED_B = 1;
//        comando.nonce++;
//        command_encodeCommand(command_buffer, &comando);
//        nRF24_sendPayload(0, player, command_buffer, 26, 0);
//        LED_B = 0;*/
//    }
//
//    return(0);
//}
//
//
//void __attribute__((__interrupt__,no_auto_psv)) _U1RXInterrupt() {
//    WriteUART1(ReadUART1());
//
//    IFS0bits.U1RXIF = 0;
//}
