int lastRedButtonState,lastBlueButtonState,lastGreenButtonState,lastBlackButtonState,lastWhiteButtonState,lastYellowButtonState, lastGreyButtonState, lastKeyButtonState, lastCapButtonState = 0;

void btnCheck(int pin, int* lastState, String name, void (&callback)(String, String, String), bool forceSend=false){
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

void customLoop(WiFiClient client, WebSocketClient webSocketClient, void (&callback)(String, String, String)){
  btnCheck(RED_BUTTON_PIN, &lastRedButtonState, F("red"), callback);
  btnCheck(BLUE_BUTTON_PIN, &lastBlueButtonState, F("blue"), callback);
  btnCheck(GREEN_BUTTON_PIN, &lastGreenButtonState, F("green"), callback);
  btnCheck(BLACK_BUTTON_PIN, &lastBlackButtonState, F("black"), callback);
  btnCheck(WHITE_BUTTON_PIN, &lastWhiteButtonState, F("white"), callback);
  btnCheck(YELLOW_BUTTON_PIN, &lastYellowButtonState, F("yellow"), callback);
  btnCheck(GREY_BUTTON_PIN, &lastGreyButtonState, F("grey"), callback);
  btnCheck(KEY_BUTTON_PIN, &lastKeyButtonState, F("key"), callback);
  btnCheck(CAP_BUTTON_PIN, &lastCapButtonState, F("cap"), callback);
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
      if(doc["target"].as<String>() == WiFi.macAddress()){
        const auto action = doc["action"].as<String>();
        if(action == "led"){
          bool state = doc["on"].as<bool>();
          if(doc["led"].as<String>() == "blue"){
            digitalWrite(LED_BUILTIN, state==true?HIGH:LOW); 
          } else if(doc["led"].as<String>() == "red"){
            digitalWrite(RED_LED_PIN, state==true?HIGH:LOW);
          } else if(doc["led"].as<String>() == "cap"){
            digitalWrite(CAP_LED_PIN, state==true?HIGH:LOW);
          }
        } else if (action == "getstatus"){
          if(doc["sensor"].as<String>() == "all"){
            btnCheck(RED_BUTTON_PIN, &lastRedButtonState, F("red"), callback, true);
            btnCheck(BLUE_BUTTON_PIN, &lastBlueButtonState, F("blue"), callback, true);
            btnCheck(GREEN_BUTTON_PIN, &lastGreenButtonState, F("green"), callback, true);
            btnCheck(BLACK_BUTTON_PIN, &lastBlackButtonState, F("black"), callback, true);
            btnCheck(WHITE_BUTTON_PIN, &lastWhiteButtonState, F("white"), callback, true);
            btnCheck(YELLOW_BUTTON_PIN, &lastYellowButtonState, F("yellow"), callback, true);
            btnCheck(GREY_BUTTON_PIN, &lastGreyButtonState, F("grey"), callback, true);
            btnCheck(KEY_BUTTON_PIN, &lastKeyButtonState, F("key"), callback, true);
            btnCheck(CAP_BUTTON_PIN, &lastCapButtonState, F("cap"), callback, true);
            callback(F("led"),"blue",digitalRead(LED_BUILTIN)==LOW?F("off"):F("on"));
            callback(F("led"),"red",digitalRead(RED_LED_PIN)==LOW?F("off"):F("on"));
            callback(F("led"),"cap",digitalRead(CAP_LED_PIN)==LOW?F("off"):F("on"));
          }
        }
      }
    }
  }
}