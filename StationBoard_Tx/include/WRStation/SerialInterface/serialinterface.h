/*** WRStation - SerialInterface module definition
  ** Warthog Robotics
  ** University of Sao Paulo at Sao Carlos
  ** http://www.warthog.sc.usp.br
  ** This file is part of the Warthog Robotics Station project
  ***/


/* Prevents multiple definitions */
#ifndef SERIALINTERFACE
#define SERIALINTERFACE


/* Includes WRStation */
#include <WRStation/wrstation.h>

/* Includes module's pinout and protocol */
#include <WRStation/SerialInterface/serialinterface_pinout.h>
#include <WRStation/SerialInterface/serialinterface_protocol.h>

/* Includes dsPIC libraries */
#include <p33Fxxxx.h>


/* Module configuration */
#define SERIALINTERFACE_BAUD_RATE 1000000


void serialInterface_initialize();
void serialInterface_configurePorts();
void serialInterface_initializeUART();
void serialInterface_configureRxDMA();
void serialInterface_configureTxDMA();
void serialInterface_start();
void serialInterface_stop();

void serialInterface_sendData(unsigned char size, unsigned char* data);


#endif
