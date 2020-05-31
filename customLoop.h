#ifndef CUSTOMLOOP_H_
#define CUSTOMLOOP_H_
  int lastRedButtonState,lastBlueButtonState,lastGreenButtonState,lastBlackButtonState,lastWhiteButtonState,lastYellowButtonState, lastGreyButtonState, lastKeyButtonState, lastCapButtonState = 0;
  void customLoop(WiFiClient client, WebSocketClient webSocketClient, void (&callback)(String, String, String));
  void btnCheck(int pin, int* lastState, String name, void (&callback)(String, String, String), bool forceSend=false);  
#endif