/*** WRStation - Nordic Station implementation
  ** Warthog Robotics
  ** University of Sao Paulo at Sao Carlos
  ** http://www.warthog.sc.usp.br
  ** This file is part of the Warthog Robotics Station project
  ***/


/* Includes WRStation */
#include <WRStation/wrstation.h>

/* Includes dsPIC libraries */
#include <p33Fxxxx.h>


void nordicStation_initialize() {
    /* Configures the MCU oscillator */
    nordicStation_configureOscillator();

    /* Sets appropriate values to the register of unused peripherals */
    nordicStation_configureUnusedPeripherals();

    /* Initializes the SerialInterface module */
    serialInterface_initialize();

    /* Initializes the Command module */
    command_initialize();
}


void nordicStation_start() {
    /* Starts the SerialInterface module */
    serialInterface_start();
    
    /* Starts the command module */
    command_start();

    /* Main loop */
    while (1) {}
}


void nordicStation_configureOscillator() {
    /* Refer to "Section 39. Oscillator (Part III)" for further information */

    /* Configures the PLL values to get Fcy = 7.37 MHz*43/4 = 39613750 Hz */
    PLLFBD = 41;
    CLKDIVbits.PLLPOST = 0;
    CLKDIVbits.PLLPRE  = 0;

    /* Selects FRC with PLL as the new source */
    __builtin_write_OSCCONH(0x01);

    /* Switches the clock sources */
    __builtin_write_OSCCONL(0x01);
    while (OSCCONbits.OSWEN != 0) {}

    /* Waits for the PLL to lock */
    while (OSCCONbits.LOCK != 1) {}
}


void nordicStation_configureUnusedPeripherals() {

}
