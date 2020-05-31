void customLoop(void (&cb)(String, String, String), WiFiClient client, WebSocketClient webSocketClient, String localMacAddress) {
  btnCheck(redButtonPin, &lastRedButtonState, F("red"), cb);
  btnCheck(blueButtonPin, &lastBlueButtonState, F("blue"), cb);
  btnCheck(greenButtonPin, &lastGreenButtonState, F("green"), cb);
  btnCheck(blackButtonPin, &lastBlackButtonState, F("black"), cb);
  btnCheck(whiteButtonPin, &lastWhiteButtonState, F("white"), cb);
  btnCheck(yellowButtonPin, &lastYellowButtonState, F("yellow"), cb);
  btnCheck(greyButtonPin, &lastGreyButtonState, F("grey"), cb);
  btnCheck(keyButtonPin, &lastKeyButtonState, F("key"), cb);
  btnCheck(capButtonPin, &lastCapButtonState, F("cap"), cb);
  if (client.connected()) {
    String json;
    webSocketClient.getData(json);
    if (json.length() > 0) {
      Serial.print(F("Recieved"));
      Serial.println(json);
      DynamicJsonDocument doc(JSON_MAXSIZE);
      DeserializationError error = deserializeJson(doc, json);
      if (error) {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.c_str());
        return;
      }
      if(doc["target"].as<String>() == localMacAddress){
        const auto action = doc["action"].as<String>();
        if(action == "led"){
          bool state = doc["on"].as<bool>();
          int ledPin;
          if(doc["led"].as<String>() == "blue"){
            digitalWrite(blueLedPin, state==true?HIGH:LOW); 
          } else if(doc["led"].as<String>() == "red"){
            digitalWrite(redLedPin, state==true?HIGH:LOW);
          } else if(doc["led"].as<String>() == "cap"){
            digitalWrite(capLedPin, state==true?HIGH:LOW);
          }
        }
      }
    }
  }
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