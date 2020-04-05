//https://github.com/morrissinger/ESP8266-Websocket to include
#include <ESP8266WiFi.h>
#include <WebSocketClient.h>
#include <Ticker.h>

const int[] pinArray = [D0,D1,D2,D3,D4,D5,D6,D6,D7,D8];
const bool[] stateArrey = [false,false,false,false,false,false,false,false,false];
const bool[] lastStateArrey = [false,false,false,false,false,false,false,false,false];
const char*[] nameArray = ["blueLed","blue","green","black","white","yellow","red","gray","D8"];
const int interval = 10000;
const char* ssid = "Licornes";
const char* wifipassword = "UnicornPowaaaaa";
char* wshost = "192.168.1.29";
char path[] = "/";

Ticker ticker;
WebSocketClient webSocketClient;
WiFiClient client;

boolean handshakeFailed=0;

void cb(String , String , String );
void tick();
void btnCheck(int , int* , String , void*);
void wsconnect();

void cb(String event, String sensor, String state){
  String str = "{\"event\":\""+event+"\",\"sensor\":\""+sensor+"\",\"state\":\""+state+"\",\"time\":"+(String)millis()+"}";
  Serial.println("Sending : " + str);
  webSocketClient.sendData(str);
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

void btnCheck(int index, void (&callback)(String, String, String)){
  int state = digitalRead(pin);
  if (state != *lastStateArrey[index]) {
    if (state == LOW) {
      callback("button",nameArray[index],"on");
    } else {
      callback("button",nameArray[index],"off");
    }
    *lastStateArrey[index] = state;
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
    digitalWrite(pinArray[0], HIGH);
  } else {
    Serial.println("Handshake failed.");
    delay(1000);
    ESP.restart();
  }
}

void setup() {
  digitalWrite(pinArray[0], LOW);
  Serial.begin(115200);
  WiFi.begin(ssid, wifipassword);
  pinMode(blueLedPin, OUTPUT);
  for (size_t i = 1; i < 9; i++) {
    pinMode(pinArray[i], INPUT_PULLUP);
  }
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
  for (size_t i = 1; i < 9; i++) {
    btnCheck(pinArray[i], &lastStateArrey[i], nameArray[i], cb);
  }
}
