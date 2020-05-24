//#define BOARD_TYPE_ESP8266 //NodeMCU 0.9 (ESP-12 Module)
#define BOARD_TYPE_ESP32 //NodeMCU-32S

#define RELAY_1_PIN 32
#define RELAY_2_PIN 33
#define RELAY_3_PIN 25
#define RELAY_4_PIN 26
#define RELAY_5_PIN 27
#define RELAY_6_PIN 14
#define RELAY_7_PIN 15
#define RELAY_8_PIN 13

#include <ArduinoJson.h>
#include <WebSocketClient.h>
#include <Ticker.h>

#ifdef BOARD_TYPE_ESP8266
  // https://github.com/morrissinger/ESP8266-Websocket to include in projet
  #include <ESP8266WiFi.h>
  #define blueLedPin     D0
  #define redButtonPin  D6
  #define blueButtonPin  D1
  #define greenButtonPin  D2
  #define blackButtonPin  D3
  #define whiteButtonPin  D4
  #define yellowButtonPin  D5
#endif
#ifdef BOARD_TYPE_ESP32
  // https://github.com/fburel/ESP32-Websocket to include in projet
  #include <WiFi.h>
  #define blueLedPin     2
  #define redButtonPin  4
  #define blueButtonPin  5
  #define greenButtonPin  13
  #define blackButtonPin  14
  #define whiteButtonPin  15
  #define yellowButtonPin  16
#endif


#define interval  10000
#define ssid  "Licornes"
#define wifipassword  "UnicornPowaaaaa"
#define wshost "192.168.1.29"
String localMacAddress = "N/C";
char path[] = "/";

Ticker ticker1,ticker5;
WebSocketClient webSocketClient;
WiFiClient client;

boolean handshakeFailed=0;
int redButtonState,blueButtonState,greenButtonState,blackButtonState,whiteButtonState,yellowButtonState = 0;
int lastRedButtonState,lastBlueButtonState,lastGreenButtonState,lastBlackButtonState,lastWhiteButtonState,lastYellowButtonState = 0;

void setup() {
  pinMode(blueLedPin, OUTPUT);
  digitalWrite(blueLedPin, LOW);
  Serial.begin(115200);
  WiFi.begin(ssid, wifipassword);
  localMacAddress = WiFi.macAddress();
  if(localMacAddress == "A4:CF:12:24:56:0C"){
    pinMode(RELAY_1_PIN, OUTPUT);
    pinMode(RELAY_2_PIN, OUTPUT);
    pinMode(RELAY_3_PIN, OUTPUT);
    pinMode(RELAY_4_PIN, OUTPUT);
    pinMode(RELAY_5_PIN, OUTPUT);
    pinMode(RELAY_6_PIN, OUTPUT);
    pinMode(RELAY_7_PIN, OUTPUT);
    pinMode(RELAY_8_PIN, OUTPUT);
    digitalWrite(RELAY_1_PIN, HIGH);
    digitalWrite(RELAY_2_PIN, HIGH);
    digitalWrite(RELAY_3_PIN, HIGH);
    digitalWrite(RELAY_4_PIN, HIGH);
    digitalWrite(RELAY_5_PIN, HIGH);
    digitalWrite(RELAY_6_PIN, HIGH);
    digitalWrite(RELAY_7_PIN, HIGH);
    digitalWrite(RELAY_8_PIN, HIGH);
  }else{
    pinMode(redButtonPin, INPUT_PULLUP);
    pinMode(blueButtonPin, INPUT_PULLUP);
    pinMode(greenButtonPin, INPUT_PULLUP);
    pinMode(blackButtonPin, INPUT_PULLUP);
    pinMode(whiteButtonPin, INPUT_PULLUP);
    pinMode(yellowButtonPin, INPUT_PULLUP);
  }
  while (!Serial) continue;
  Serial.println();
  Serial.println(F("Connecting"));
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(F("."));
  }
  Serial.println();
  Serial.println(F("- succesfully connected"));
  Serial.print(F("IP address: "));
  Serial.println(WiFi.localIP());
  Serial.print(F("MAC address: "));
  Serial.println(localMacAddress);
  Serial.println(F("- starting client"));
  wsconnect();
  ticker1.attach(1, tick1);
  ticker5.attach(5, tick5);
  Serial.println();
  Serial.println(F("System Ready"));
}

void loop() {
  if(localMacAddress != "A4:CF:12:24:56:0C"){
    btnCheck(redButtonPin, &lastRedButtonState, F("red"), cb);
    btnCheck(blueButtonPin, &lastBlueButtonState, F("blue"), cb);
    btnCheck(greenButtonPin, &lastGreenButtonState, F("green"), cb);
    btnCheck(blackButtonPin, &lastBlackButtonState, F("black"), cb);
    btnCheck(whiteButtonPin, &lastWhiteButtonState, F("white"), cb);
    btnCheck(yellowButtonPin, &lastYellowButtonState, F("yellow"), cb);
  }
}
void tick1(){
  if (client.connected()) {
    String json;
    webSocketClient.getData(json);
    if (json.length() > 0) {
      Serial.print(F("Recieved"));
      Serial.println(json);
      DynamicJsonDocument doc(200);
      DeserializationError error = deserializeJson(doc, json);
      if (error) {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.c_str());
        return;
      }
      if(doc["target"].as<String>() == localMacAddress){
        const auto action = doc["action"].as<String>();
        if(action == F("relay")) {
            Serial.println(action);
            int relay;
            bool state = doc["on"].as<bool>();
            switch(doc["relay"].as<int>()){
              case 1:
                relay=RELAY_1_PIN;
                break;
              case 2:
                relay=RELAY_2_PIN;
                break;
              case 3:
                relay=RELAY_3_PIN;
                break;
              case 4:
                relay=RELAY_4_PIN;
                break;
              case 5:
                relay=RELAY_5_PIN;
                break;
              case 6:
                relay=RELAY_6_PIN;
                break;
              case 7:
                relay=RELAY_7_PIN;
                break;
              case 8:
                relay=RELAY_8_PIN;
                break;
            }
            Serial.println(relay);
            digitalWrite(relay, state==true?LOW:HIGH);
            Serial.print(F("Relay "));
            Serial.print(relay);
            Serial.print(F(" to "));
            Serial.println(state==true?F("on"):F("off"));
        }
      }
    }
  }
}
void tick5(){
   if (client.connected()) {
    cb(F("heartbeat"),F("core"),F("alive"));
   } else {
    Serial.println(F("Client not connected"));
    delay(1000);
    ESP.restart();
   }
}

void cb(String event, String sensor, String state){
  String str = "{\"event\":\""+event+"\",\"sensor\":\""+sensor+"\",\"state\":\""+state+"\",\"time\":"+(String)millis()+", \"macAddress\":\"" + localMacAddress + "\"}";
  Serial.print(F("Sending : "));
  Serial.println(str);
  webSocketClient.sendData(str);
}

void btnCheck(int pin, int* lastState, String name, void (&callback)(String, String, String)){
  int state = digitalRead(pin);
  if (state != *lastState) {
    
    if (state == LOW) {
      callback(F("button"),name,F("on"));
    } else {
      callback(F("button"),name,F("off"));
    }
    *lastState = state;
    delay(20);
  }
}

void wsconnect(){
  if (client.connect(wshost, 3000)) {
    Serial.println(F("Connected"));
  } else {
    Serial.println(F("Connection failed."));
    ESP.restart();
  }
  // Handshake with the server
  webSocketClient.host = wshost;
  webSocketClient.path = path;
  if (webSocketClient.handshake(client)) {
    Serial.println(F("Handshake successful"));
    digitalWrite(blueLedPin, HIGH);
  } else {
    Serial.println(F("Handshake failed."));
    delay(1000);
    ESP.restart();
  }
}
