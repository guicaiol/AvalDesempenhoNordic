/*** StationBoard - Command module implementation
  ** Warthog Robotics
  ** University of Sao Paulo at Sao Carlos
  ** http://www.warthog.sc.usp.br
  ** This file is part of the Warthog Robotics Station project
  ***/


/* Includes StationBoard */
#include <StationBoard/stationboard.h>

/* Includes dsPIC libraries */
#include <p33Fxxxx.h>

/* Includes C standard libraries */
#include <stdlib.h>
#include <string.h>

/* Includes nRF24L01 library */
#include <nRF24L01/nrf24l01.h>


/* Module internal variables */
uint8  command_channel;
uint8  command_addressSize;
uint8* command_address = 0;


void command_initialize() {
    /* Initializes the radio */
    command_initializeRadio();
    
    uint8 stationAddress[] = {'W','R','C','S','t'};
    command_setAddress(5, stationAddress);
    
    //TODO: Create defines for the frequencies
//    command_setChannel(125); /* Channel A - Command input main channel */;;
    command_setChannel(105); /* Channel B - Command input alternative channel */
}


void command_initializeRadio() {
    /* Configures the radio operation mode
       Refer to "nRF24L01/nRF24L01.h" for further information */
    nRF24_init(0);

    nRF24_setDataRate(0, 0);

    nRF24_setAutoRetransmitDelay(0, 0);
    nRF24_setAutoRetransmitCount(0, 0);

    nRF24_enableAutoAck(0, 0, 0);
    nRF24_enableAutoAck(0, 1, 0);

    nRF24_enableDSInt(0, 0);
    nRF24_enableMaxRTInt(0, 0);

    nRF24_setTx(0);
}


void command_start() {
    nRF24_powerUp(0);
}


void command_setChannel(uint8 channel) {
    /* Sets the radio channel */
    command_channel = channel;

    /* Configures the radio */
    nRF24_setChannel(0, command_channel); // TODO: Verificar se pode trocar com o radio funcionando
}


void command_setAddress(uint8 size, uint8* address) {
    /* Sets the address size */
    command_addressSize = size;

    /* Sets the radio address */
    command_address = (uint8*) realloc(command_address, size*sizeof(uint8));
    memcpy((void*) command_address, (void*) address, size);

    /* Configures the radio */
    nRF24_setAddressSize(0, command_addressSize-2);
    nRF24_setRxAddress(0, 1, command_address); // TODO: Verificar se pode trocar com o radio funcionando
}


void command_sendPayload(uint8* playerAddress, uint8 payloadSize, uint8* payload) {
    /* Sends the payload */
    nRF24_sendPayload(0, playerAddress, payload, payloadSize, 0); // TODO: Organizar para trabalhar com ACK
}
