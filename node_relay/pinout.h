#ifndef PINOUT_H
#define PINOUT_H
  #ifdef BOARD_TYPE_ESP32
    #ifdef NODE_RELAY
      #define RELAY_1_PIN 32
      #define RELAY_2_PIN 33
      #define RELAY_3_PIN 25
      #define RELAY_4_PIN 26
      #define RELAY_5_PIN 27
      #define RELAY_6_PIN 14
      #define RELAY_7_PIN 15
      #define RELAY_8_PIN 13
      #define RED_BUTTON_PIN  4
      #define BLUE_BUTTON_PIN  5
      #define GREEN_BUTTON_PIN  13
      #define BLACK_BUTTON_PIN  14
      #define WHITE_BUTTON_PIN  15
      #define YELLOW_BUTTON_PIN  16
    #endif
  #endif
#endif