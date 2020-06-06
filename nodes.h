#ifndef NODES_H_
#define NODES_H_
  #ifdef BOARD_TYPE_ESP8266
    //unused for now
  #endif
  #ifdef BOARD_TYPE_ESP32
    #ifndef ESP32
      #pragma message(THIS PROGRAM IS FOR ESP32 ONLY!)
      #error Select ESP32 board.
    #endif
    #ifdef NODE_RELAY
      #include "node_relay/pinout.h"
      #include "node_relay/customSetup.cpp"
      #include "node_relay/customLoop.cpp"
      #include "node_relay/tick1.cpp"
      #include "node_relay/tick5.cpp"
    #endif
    #ifdef NODE_CONTROL
      #include "node_control/pinout.h"
      #include "node_control/customSetup.cpp"
      #include "node_control/customLoop.cpp"
      #include "node_control/tick1.cpp"
      #include "node_control/tick5.cpp"
    #endif
    #ifdef NODE_WEATHER
      #include "node_weather/pinout.h"
      #include "node_weather/customSetup.cpp"
      #include "node_weather/customLoop.cpp"
      #include "node_weather/tick1.cpp"
      #include "node_weather/tick5.cpp"
    #endif
  #endif
#endif
