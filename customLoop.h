#ifndef CUSTOMLOOP_H_
#define CUSTOMLOOP_H_
  void customLoop(WiFiClient client, WebSocketClient webSocketClient, void (&callback)(String, String, String));
#endif
