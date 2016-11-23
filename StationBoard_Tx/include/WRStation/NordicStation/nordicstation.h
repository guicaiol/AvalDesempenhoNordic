/*** WRStation - Nordic Station definition
  ** Warthog Robotics
  ** University of Sao Paulo at Sao Carlos
  ** http://www.warthog.sc.usp.br
  ** This file is part of the Warthog Robotics Station project
  ***/


/* Prevents multiple definitions */
#ifndef NORDICSTATION
#define NORDICSTATION


/* Includes WRStation */
#include <WRStation/wrstation.h>

/* Includes dsPIC libraries */
#include <p33Fxxxx.h>


/* MCU configuration */
#define NORDICSTATION_Fcy 39613.750 /* Instruction clock in kHz */
#define NORDICSTATION_Tcy 25.247360 /* Instruction time in ns */


void nordicStation_initialize();
void nordicStation_start();

void nordicStation_configureOscillator();
void nordicStation_configureUnusedPeripherals();


#endif

