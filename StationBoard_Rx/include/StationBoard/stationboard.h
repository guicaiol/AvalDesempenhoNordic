/*** WRStation - Nordic Station definition
  ** Warthog Robotics
  ** University of Sao Paulo at Sao Carlos
  ** http://www.warthog.sc.usp.br
  ** This file is part of the Warthog Robotics Station project
  ***/


/* Prevents multiple definitions */
#ifndef STATIONBOARD
#define STATIONBOARD

/* Includes Modules */
#include <StationBoard/Command/command.h>
#include <StationBoard/SerialInterface/serialinterface.h>
#include <StationBoard/Telemetry/telemetry.h>

/* Includes dsPIC libraries */
#include <p33Fxxxx.h>


/* MCU configuration */
#define STATIONBOARD_Fcy 39613.750 /* Instruction clock in kHz */
#define STATIONBOARD_Tcy 25.247360 /* Instruction time in ns */


void stationBoard_initialize();
void stationBoard_start();

void stationBoard_configureOscillator();
void stationBoard_configureUnusedPeripherals();


#endif

