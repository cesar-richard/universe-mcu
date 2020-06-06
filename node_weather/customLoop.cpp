void customLoop(WiFiClient client, WebSocketClient webSocketClient, void (&callback)(String, String, String)){
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
        if (action == "getstatus"){
          if(doc["sensor"].as<String>() == "all"){
            callback(F("led"),"blue",digitalRead(LED_BUILTIN)==LOW?F("off"):F("on"));
          }
        }
      }
    }
  }
}