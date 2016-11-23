/*** WRStation - Command module definition
  ** Warthog Robotics
  ** University of Sao Paulo at Sao Carlos
  ** http://www.warthog.sc.usp.br
  ** This file is part of the Warthog Robotics Station project
  ***/


/* Prevents multiple definitions */
#ifndef COMMAND
#define COMMAND


/* Includes WRStation */
#include <StationBoard/stationboard.h>

/* Includes module's pinout */
#include <StationBoard/Command/command_pinout.h>

/* Includes dsPIC libraries */
#include <p33Fxxxx.h>

/* Includes nRF24L01 library */
#include <nRF24L01/nrf24l01.h>


void command_initialize();
void command_initializeRadio();
void command_start();

void command_setChannel(uint8 channel);
void command_setAddress(uint8 size, uint8* address);

void command_sendPayload(uint8* playerAddress, uint8 payloadSize, uint8* payload);


#endif
