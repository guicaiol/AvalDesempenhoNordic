/*** nRF24L01 Library - Pinout
  ** Warthog Robotics
  ** University of Sao Paulo at Sao Carlos
  ** http://www.warthog.sc.usp.br
  ** This file is part of the nRF24L01 Library project
  ***/


/* Prevents multiple definitions */
#ifndef NRF24_PINOUT
#define NRF24_PINOUT


/* Includes dsPIC33 library */
#include <p33Fxxxx.h>


/* Radio 0 pinout */
#define NRF24_MISO0_RPIN 2
#define NRF24_MOSI0_RPOR RPOR0bits.RP1R
#define NRF24_SCLK0_RPOR RPOR0bits.RP0R

#define NRF24_SS0      PORTAbits.RA1
#define NRF24_TRIS_SS0 TRISAbits.TRISA1
#define NRF24_HAS_AN_SS0 1
#if NRF24_HAS_AN_SS0
    #define NRF24_ADPCFG_SS0 AD1PCFGLbits.PCFG1
    #define NRF24_ADCS_SS0   AD1CSSLbits.CSS1
#endif

#define NRF24_CE0      PORTAbits.RA0
#define NRF24_TRIS_CE0 TRISAbits.TRISA0
#define NRF24_HAS_AN_CE0 1
#if NRF24_HAS_AN_CE0
    #define NRF24_ADPCFG_CE0 AD1PCFGLbits.PCFG0
    #define NRF24_ADCS_CE0   AD1CSSLbits.CSS0
#endif


/* Radio 1 pinout */
#define NRF24_MISO1_RPIN 2
#define NRF24_MOSI1_RPOR RPOR0bits.RP1R
#define NRF24_SCLK1_RPOR RPOR0bits.RP0R

#define NRF24_SS1      PORTAbits.RA1
#define NRF24_TRIS_SS1 TRISAbits.TRISA1
#define NRF24_HAS_AN_SS1 1
#if NRF24_HAS_AN_SS1
    #define NRF24_ADPCFG_SS1 AD1PCFGLbits.PCFG1
    #define NRF24_ADCS_SS1   AD1CSSLbits.CSS1
#endif

#define NRF24_CE1      PORTAbits.RA0
#define NRF24_TRIS_CE1 TRISAbits.TRISA0
#define NRF24_HAS_AN_CE1 1
#if NRF24_HAS_AN_CE1
    #define NRF24_ADPCFG_CE1 AD1PCFGLbits.PCFG0
    #define NRF24_ADCS_CE1   AD1CSSLbits.CSS0
#endif


#endif
