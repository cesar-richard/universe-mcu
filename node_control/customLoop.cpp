void customLoop(WiFiClient client, WebSocketClient webSocketClient, void (&callback)(String, String, String)){
  btnCheck(redButtonPin, &lastRedButtonState, F("red"), callback);
  btnCheck(blueButtonPin, &lastBlueButtonState, F("blue"), callback);
  btnCheck(greenButtonPin, &lastGreenButtonState, F("green"), callback);
  btnCheck(blackButtonPin, &lastBlackButtonState, F("black"), callback);
  btnCheck(whiteButtonPin, &lastWhiteButtonState, F("white"), callback);
  btnCheck(yellowButtonPin, &lastYellowButtonState, F("yellow"), callback);
  btnCheck(greyButtonPin, &lastGreyButtonState, F("grey"), callback);
  btnCheck(keyButtonPin, &lastKeyButtonState, F("key"), callback);
  btnCheck(capButtonPin, &lastCapButtonState, F("cap"), callback);
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
        //return;
      }
      if(doc["target"].as<String>() == WiFi.macAddress()){
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
        } else if (action == "getstatus"){
          if(doc["sensor"].as<String>() == "all"){
            btnCheck(redButtonPin, &lastRedButtonState, F("red"), callback, true);
            btnCheck(blueButtonPin, &lastBlueButtonState, F("blue"), callback, true);
            btnCheck(greenButtonPin, &lastGreenButtonState, F("green"), callback, true);
            btnCheck(blackButtonPin, &lastBlackButtonState, F("black"), callback, true);
            btnCheck(whiteButtonPin, &lastWhiteButtonState, F("white"), callback, true);
            btnCheck(yellowButtonPin, &lastYellowButtonState, F("yellow"), callback, true);
            btnCheck(greyButtonPin, &lastGreyButtonState, F("grey"), callback, true);
            btnCheck(keyButtonPin, &lastKeyButtonState, F("key"), callback, true);
            btnCheck(capButtonPin, &lastCapButtonState, F("cap"), callback, true);
            callback(F("led"),"blue",digitalRead(blueLedPin)==LOW?F("off"):F("on"));
            callback(F("led"),"red",digitalRead(redLedPin)==LOW?F("off"):F("on"));
            callback(F("led"),"cap",digitalRead(capLedPin)==LOW?F("off"):F("on"));
          }
        }
      }
    }
  }
}

void btnCheck(int pin, int* lastState, String name, void (&callback)(String, String, String), bool forceSend){
  int state = digitalRead(pin);
  if (state != *lastState || forceSend) {
    if (state == LOW) {
      callback(F("button"),name,F("on"));
    } else {
      callback(F("button"),name,F("off"));
    }
    *lastState = state;
    delay(20);
  }
}