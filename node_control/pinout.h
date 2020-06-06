#ifndef PINOUT_H
#define PINOUT_H
  #ifdef BOARD_TYPE_ESP32
    #ifdef NODE_CONTROL
      #define RED_LED_PIN     13
      #define CAP_LED_PIN  22
      #define RED_BUTTON_PIN  19
      #define BLUE_BUTTON_PIN  14
      #define GREEN_BUTTON_PIN  15
      #define BLACK_BUTTON_PIN  16
      #define WHITE_BUTTON_PIN  17
      #define YELLOW_BUTTON_PIN 18 
      #define GREY_BUTTON_PIN 21
      #define KEY_BUTTON_PIN  5
      #define CAP_BUTTON_PIN  4
    #endif
  #endif
#endif