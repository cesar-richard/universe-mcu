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
      #define blueLedPin     2
      #define redButtonPin  4
      #define blueButtonPin  5
      #define greenButtonPin  13
      #define blackButtonPin  14
      #define whiteButtonPin  15
      #define yellowButtonPin  16
    #endif
  #endif
#endif