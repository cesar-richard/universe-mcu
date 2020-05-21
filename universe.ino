//https://github.com/morrissinger/ESP8266-Websocket to include
#include <ESP8266WiFi.h>
#include <WebSocketClient.h>
#include <Ticker.h>

#define WIFI_SSID "Licornes"
#define WIFI_PASSWORD "UnicornPowaaaaa"
#define blueLedPin     2
#define redButtonPin  4
#define blueButtonPin  5
#define greenButtonPin  13
#define blackButtonPin  14
#define whiteButtonPin  15
#define yellowButtonPin  16
#define relayPin   17
#define interval  10000
#define wshost "192.168.1.29"
#define path "/"

Ticker ticker;
WebSocketClient webSocketClient;
WiFiClient client;

boolean handshakeFailed=0;
int redButtonState,blueButtonState,greenButtonState,blackButtonState,whiteButtonState,yellowButtonState = 0;
int lastRedButtonState,lastBlueButtonState,lastGreenButtonState,lastBlackButtonState,lastWhiteButtonState,lastYellowButtonState = 0;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, wifipassword);
  pinMode(relayPin, OUTPUT);
  pinMode(blueLedPin, OUTPUT);
  pinMode(redButtonPin, INPUT_PULLUP);
  pinMode(blueButtonPin, INPUT_PULLUP);
  pinMode(greenButtonPin, INPUT_PULLUP);
  pinMode(blackButtonPin, INPUT_PULLUP);
  pinMode(whiteButtonPin, INPUT_PULLUP);
  pinMode(yellowButtonPin, INPUT_PULLUP);
  digitalWrite(blueLedPin, LOW);
  while (!Serial) continue;
  Serial.println();
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("- succesfully connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("- starting client");
  wsconnect();
  ticker.attach(5, tick);
  Serial.println();
  Serial.println("System Ready");
}

void loop() {
  btnCheck(redButtonPin, &lastRedButtonState, "red", cb);
  btnCheck(blueButtonPin, &lastBlueButtonState, "blue", cb);
  btnCheck(greenButtonPin, &lastGreenButtonState, "green", cb);
  btnCheck(blackButtonPin, &lastBlackButtonState, "black", cb);
  btnCheck(whiteButtonPin, &lastWhiteButtonState, "white", cb);
  btnCheck(yellowButtonPin, &lastYellowButtonState, "yellow", cb); 
}

void tick(){
   if (client.connected()) {
    String data;
    /*webSocketClient.getData(data);    
    if (data.length() > 0) {
      Serial.println(data);
    }*/
    cb("heartbeat","core","alive");
   } else {
    Serial.println("Client not connected");
    delay(1000);
    ESP.restart();
   }
}

void cb(String event, String sensor, String state){
  String str = "{\"event\":\""+event+"\",\"sensor\":\""+sensor+"\",\"state\":\""+state+"\",\"time\":"+(String)millis()+"}";
  Serial.println("Sending : " + str);
  webSocketClient.sendData(str);
}

void btnCheck(int pin, int* lastState, String name, void (&callback)(String, String, String)){
  int state = digitalRead(pin);
  if (state != *lastState) {
    
    if (state == LOW) {
      callback("button",name,"on");
    } else {
      callback("button",name,"off");
    }
    *lastState = state;
    delay(20);
  }
}

void wsconnect(){
  if (client.connect(wshost, 3000)) {
    Serial.println("Connected");
  } else {
    Serial.println("Connection failed.");
    ESP.restart();
  }
  // Handshake with the server
  webSocketClient.host = wshost;
  webSocketClient.path = path;
  if (webSocketClient.handshake(client)) {
    Serial.println("Handshake successful");
    digitalWrite(blueLedPin, HIGH);
  } else {
    Serial.println("Handshake failed.");
    delay(1000);
    ESP.restart();
  }
}
