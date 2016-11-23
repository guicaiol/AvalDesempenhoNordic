/*** WRStation - SerialInterface module definition
  ** Warthog Robotics
  ** University of Sao Paulo at Sao Carlos
  ** http://www.warthog.sc.usp.br
  ** This file is part of the Warthog Robotics Station project
  ***/


/* Prevents multiple definitions */
#ifndef SERIALINTERFACE_PINOUT
#define SERIALINTERFACE_PINOUT


/* Includes WRStation */
#include <StationBoard/stationboard.h>

/* Includes dsPIC libraries */
#include <p33Fxxxx.h>


/* UART pinout */
#define SERIALINTERFACE_MCU_RX_RPIN  9
#define SERIALINTERFACE_MCU_CTS_RPIN 8
#define SERIALINTERFACE_MCU_TX_RPOR  RPOR3bits.RP7R
#define SERIALINTERFACE_MCU_RTS_RPOR RPOR3bits.RP6R

#define SERIALINTERFACE_MCU_RX      PORTBbits.RB9
#define SERIALINTERFACE_TRIS_MCU_RX TRISBbits.TRISB9
#define SERIALINTERFACE_HAS_AN_MCU_RX 0
#if SERIALINTERFACE_HAS_AN_MCU_RX
    #define SERIALINTERFACE_ADPCFG_MCU_RX
    #define SERIALINTERFACE_ADCS_MCU_RX
#endif

#define SERIALINTERFACE_MCU_CTS      PORTBbits.RB8
#define SERIALINTERFACE_TRIS_MCU_CTS TRISBbits.TRISB8
#define SERIALINTERFACE_HAS_AN_MCU_CTS 0
#if SERIALINTERFACE_HAS_AN_MCU_CTS
    #define SERIALINTERFACE_ADPCFG_MCU_CTS
    #define SERIALINTERFACE_ADCS_MCU_CTS
#endif

#define SERIALINTERFACE_MCU_TX      PORTBbits.RB7
#define SERIALINTERFACE_TRIS_MCU_TX TRISBbits.TRISB7
#define SERIALINTERFACE_HAS_AN_MCU_TX 0
#if SERIALINTERFACE_HAS_AN_MCU_TX
    #define SERIALINTERFACE_ADPCFG_MCU_TX
    #define SERIALINTERFACE_ADCS_MCU_TX
#endif

#define SERIALINTERFACE_MCU_RTS      PORTBbits.RB6
#define SERIALINTERFACE_TRIS_MCU_RTS TRISBbits.TRISB6
#define SERIALINTERFACE_HAS_AN_MCU_RTS 0
#if SERIALINTERFACE_HAS_AN_MCU_RTS
    #define SERIALINTERFACE_ADPCFG_MCU_RTS
    #define SERIALINTERFACE_ADCS_MCU_RTS
#endif


#endif
