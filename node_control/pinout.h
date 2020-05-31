#ifndef PINOUT_H
#define PINOUT_H
  #ifdef BOARD_TYPE_ESP32
    #ifdef NODE_CONTROL
      #define blueLedPin     2
      #define redLedPin     13
      #define capLedPin  22
      #define redButtonPin  19
      #define blueButtonPin  14
      #define greenButtonPin  15
      #define blackButtonPin  16
      #define whiteButtonPin  17
      #define yellowButtonPin 18 
      #define greyButtonPin 21
      #define keyButtonPin  5
      #define capButtonPin  4
    #endif
  #endif
#endif