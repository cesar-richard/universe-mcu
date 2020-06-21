void customtick1(WiFiClient client, WebSocketClient webSocketClient, String localMacAddress){
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
      const auto action = doc["action"].as<String>();
      if(doc["target"].as<String>() == localMacAddress){
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
      } else if (action == "getstatus"){
        if(doc["sensor"].as<String>() == "all"){
          
        }
    }
  }
}