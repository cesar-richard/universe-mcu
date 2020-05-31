#ifndef CUSTOMLOOP_H_
#define CUSTOMLOOP_H_
  int lastRedButtonState,lastBlueButtonState,lastGreenButtonState,lastBlackButtonState,lastWhiteButtonState,lastYellowButtonState, lastGreyButtonState, lastKeyButtonState, lastCapButtonState = 0;
  void customLoop(void (&cb)(String, String, String), WiFiClient client, WebSocketClient webSocketClient, String localMacAddress);
  void btnCheck(int pin, int* lastState, String name, void (&callback)(String, String, String));
  #include "customLoop.cpp"
#endif