/*** StationBoard - Command module implementation
  ** Warthog Robotics
  ** University of Sao Paulo at Sao Carlos
  ** http://www.warthog.sc.usp.br
  ** This file is part of the Warthog Robotics Station project
  ***/


/* Includes StationBoard */
#include <StationBoard/stationboard.h>

/* Includes module private header */
#include <StationBoard/Telemetry/telemetry_private.h>
#include <StationBoard/Telemetry/telemetry_pinout.h>

/* Includes dsPIC libraries */
#include <p33Fxxxx.h>

/* Includes C standard libraries */
#include <stdlib.h>
#include <string.h>

/* Includes nRF24L01 library */
#include <nRF24L01/nrf24l01.h>


/* Module internal variables */
uint8 telemetry_address[TELEMETRY_ADDR_SIZE] = {TELEMETRY_ADDR_BASE};
uint8 telemetry_buffer[TELEMETRY_PROTOCOL_SIZE];
uint8 telemetry_radioChannel = TELEMETRY_CHANNEL_B;

void telemetry_initialize() {
    /* Reset buffer */
    int i;
    for(i=0; i<TELEMETRY_PROTOCOL_SIZE; i++)
        telemetry_buffer[i] = 0;
    
    /* Config ports */
    telemetry_configPorts();
    
    /* Initializes the radio */
    telemetry_initializeRadio();
}

void telemetry_configPorts() {
    // IRQ do radio / input
    TRIS_R0_IRQ0 = 1;
}

void telemetry_initializeRadio() {
    /* Configures the radio (Nordic's nRF24L01+)
       Refer to "nRF24L01/nRF24L01.h" for further information */
    nRF24_init(TELEMETRY_RADIO_NUMBER);

    nRF24_setAddressSize(TELEMETRY_RADIO_NUMBER, TELEMETRY_ADDR_PREFIX_SIZE);
    nRF24_setRxAddress(TELEMETRY_RADIO_NUMBER, 1, telemetry_address);

    nRF24_setChannel(TELEMETRY_RADIO_NUMBER, telemetry_radioChannel);
    nRF24_setDataRate(TELEMETRY_RADIO_NUMBER, 0);

    nRF24_enableRxPipe(TELEMETRY_RADIO_NUMBER, 0, 1);
    nRF24_enableRxPipe(TELEMETRY_RADIO_NUMBER, 1, 1);
    nRF24_setRxPayloadSize(TELEMETRY_RADIO_NUMBER, 0, TELEMETRY_PROTOCOL_SIZE);
    nRF24_setRxPayloadSize(TELEMETRY_RADIO_NUMBER, 1, TELEMETRY_PROTOCOL_SIZE);

    nRF24_enableAutoAck(TELEMETRY_RADIO_NUMBER, 0, 0);
    nRF24_enableAutoAck(TELEMETRY_RADIO_NUMBER, 1, 0);

    nRF24_enableDSInt(TELEMETRY_RADIO_NUMBER, 0);
    nRF24_enableMaxRTInt(TELEMETRY_RADIO_NUMBER, 0);

    nRF24_setRx(TELEMETRY_RADIO_NUMBER);

    nRF24_powerUp(TELEMETRY_RADIO_NUMBER);
}


void telemetry_start() {
    /* Enables radio */
    nRF24_setRxActive(TELEMETRY_RADIO_NUMBER);
}

void telemetry_sendPayload(uint8* playerAddress, uint8 payloadSize, uint8* payload) {
    /* Sends the payload */
    nRF24_sendPayload(0, playerAddress, payload, payloadSize, 0); // TODO: Organizar para trabalhar com ACK
}

unsigned char serialBuffer[128];
unsigned char catBuffer[32];

void telemetry_taskHandler() {
    /* Variables */
    uint8 nBytes = 0;
    
    uint8 empty = nRF24_isRxFIFOEmpty(TELEMETRY_RADIO_NUMBER);
    
    /* Receives the new packet */
    if(!empty) {

        /* Gets data */
        nRF24_getReceivedPayload(TELEMETRY_RADIO_NUMBER, telemetry_buffer, &nBytes);
        
        // Send on serial
        serialInterface_sendData(nBytes, telemetry_buffer);
        
        /* DEBUG: Send on serial */
        //unsigned char buffer[128];
        //buffer[0] = '\0';
        //strcat(buffer, "RX: ");

        //int i=0;
        //for(i=0; i<nBytes; i++) {
            //unsigned char cat[16];
            //sprintf(cat, "%02X ", telemetry_buffer[i] & 0xFF);

            //strcat(buffer, cat);
        //}
        //strcat(buffer, "\r\n");
        //serialInterface_sendData(strlen(buffer), buffer);
    }
}
