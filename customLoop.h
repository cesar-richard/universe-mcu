#ifndef CUSTOMLOOP_H_
#define CUSTOMLOOP_H_
  int lastRedButtonState,lastBlueButtonState,lastGreenButtonState,lastBlackButtonState,lastWhiteButtonState,lastYellowButtonState, lastGreyButtonState, lastKeyButtonState, lastCapButtonState = 0;
  void customLoop(WiFiClient client, WebSocketClient webSocketClient, void (&callback)(String, String, String));
#endif
