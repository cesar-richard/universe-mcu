void customtick5(WiFiClient client, void (&cb)(String, String, String)){
   if (client.connected()) {
    cb(F("heartbeat"),F("core"),F("alive"));
   } else {
    Serial.println(F("Client not connected"));
    delay(1000);
    ESP.restart();
   }
}