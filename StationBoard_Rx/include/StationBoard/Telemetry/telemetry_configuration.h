/** SubZeroBoard - Telemetry implementation
  * Warthog Robotics
  * University of Sao Paulo at Sao Carlos
  * http://www.warthog.sc.usp.br
  * This file is part of the Warthog Robotics SubZero project
  **/


/* Prevents multiple definitions */
#ifndef SB_TELEMETRY_CONFIGURATION
#define SB_TELEMETRY_CONFIGURATION


/* Includes dsPIC33 libraries */
#include <p33Fxxxx.h>


/* Module configuration */
#define TELEMETRY_RADIO_NUMBER 0 /* The number of the telemetry (Tx) radio */

#define TELEMETRY_CHANNEL_A 125 /* Telemetry output main channel */
#define TELEMETRY_CHANNEL_B 105 /* Telemetry output alternative channel */

#define TELEMETRY_ADDR_SIZE        5                   /* Number of bytes of player address */
#define TELEMETRY_ADDR_PREFIX_SIZE 3                   /* Number of bytes of player address prefix */
#define TELEMETRY_ADDR_BASE        'W','R','R','0','0' /* Address base */

#define TELEMETRY_PROTOCOL_SIZE 32 /* Number of bytes of the telemetry protocol */

#endif
