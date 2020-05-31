#ifndef LIBS_H_
#define LIBS_H_
  #include <ArduinoJson.h>
  #include <WebSocketClient.h>
  #include <Ticker.h>

  #ifdef BOARD_TYPE_ESP8266
    // https://github.com/morrissinger/ESP8266-Websocket to include in projet
    #include <ESP8266WiFi.h>
  #endif
  #ifdef BOARD_TYPE_ESP32
    // https://github.com/fburel/ESP32-Websocket to include in projet
    #include <WiFi.h>
  #endif
#endif
