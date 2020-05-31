#ifndef NODES_H_
#define NODES_H_
  #ifdef BOARD_TYPE_ESP8266
    //Unused for now
  #endif
  #ifdef BOARD_TYPE_ESP32
    #ifdef NODE_RELAY
      #import "node_relay/pinout.h"
      #import "node_relay/customSetup.h"
      #import "node_relay/tick1.h"
      #import "node_relay/tick5.h"
    #endif
    #ifdef NODE_CONTROL
      #import "node_control/pinout.h"
      #import "node_control/customSetup.h"
      #import "node_control/customLoop.h"
      #import "node_control/tick1.h"
      #import "node_control/tick5.h"
    #endif
  #endif
#endif
