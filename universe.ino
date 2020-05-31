#include "config.h"

String localMacAddress = "N/C";

WebSocketClient webSocketClient;
Ticker ticker1,ticker5;
WiFiClient client;

boolean handshakeFailed=0;

void cb(String event, String sensor, String state){
  String str = "{\"event\":\""+event+"\",\"sensor\":\""+sensor+"\",\"state\":\""+state+"\",\"time\":"+(String)millis()+", \"macAddress\":\"" + localMacAddress + "\"}";
  Serial.print(F("Sending : "));
  Serial.println(str);
  webSocketClient.sendData(str);
}

void tick1() {
  customtick1(client, webSocketClient, localMacAddress);
}
void tick5() {
  customtick5(client, cb);
}

void wsconnect(){
  if (client.connect(WS_HOST, 3000)) {
    Serial.println(F("Connected"));
  } else {
    Serial.println(F("Connection failed."));
    ESP.restart();
  }
  // Handshake with the server
  webSocketClient.host = WS_HOST;
  webSocketClient.path = "/";
  if (webSocketClient.handshake(client)) {
    Serial.println(F("Handshake successful"));
    digitalWrite(blueLedPin, HIGH);
  } else {
    Serial.println(F("Handshake failed."));
    delay(1000);
    ESP.restart();
  }
}

void setup() {
  pinMode(blueLedPin, OUTPUT);
  digitalWrite(blueLedPin, LOW);
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  localMacAddress = WiFi.macAddress();
  customSetup();
  while (!Serial) continue;
  Serial.println();
  Serial.println(F("Connecting"));
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(F("."));
  }
  Serial.println();
  Serial.print(F("IP address: "));
  Serial.println(WiFi.localIP());
  Serial.print(F("MAC address: "));
  Serial.println(localMacAddress);
  wsconnect();
  ticker1.attach(1, tick1);
  ticker5.attach(5, tick5);
  Serial.println();
  Serial.println(F("System Ready"));
}

void loop() {
  customLoop(cb, client, webSocketClient, localMacAddress);
}
