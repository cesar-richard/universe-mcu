#ifndef CONFIG_H_
#define CONFIG_H_
  //#define BOARD_TYPE_ESP8266 //NodeMCU 0.9 (ESP-12 Module)
  #define BOARD_TYPE_ESP32 //NodeMCU-32S

  #define NODE_CONTROL
  //#define NODE_RELAY

  #define HB_INTERVAL 10000
  #define JSON_MAXSIZE 500
  #define WIFI_SSID  "Licornes"
  #define WIFI_PASSWORD  "UnicornPowaaaaa"
  #define WS_HOST "192.168.1.29"

  #include "libs.h"
  #include "nodes.h"
#endif
