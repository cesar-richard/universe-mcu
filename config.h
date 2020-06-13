#ifndef CONFIG_H_
#define CONFIG_H_
  //#define BOARD_TYPE_ESP8266 //NodeMCU 0.9 (ESP-12 Module)
  #define BOARD_TYPE_ESP32 //NodeMCU-32S

  
  #define NODE_CONTROL
  //#define NODE_RELAY
  //#define NODE_WEATHER
  
  #define HB_INTERVAL 10000
  #define JSON_MAXSIZE 500
  #define WIFI_SSID  "Licornes"
  #define WIFI_PASSWORD  "UnicornPowaaaaa"
  #define WS_HOST "universe-server.crichard.fr"
  #define WS_PORT 3657
  
  void cb(String event, String sensor, String state);

  #include "libs.h"
  #include "customSetup.h"
  #include "customLoop.h"
  #include "tick1.h"
  #include "tick5.h"
  #include "nodes.h"
#endif
