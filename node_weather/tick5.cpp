void customtick5(WiFiClient client, void (&cb)(String, String, String)){
   if (client.connected()) {
    cb(F("heartbeat"),F("core"),F("alive"));
    if (!tasksEnabled) {
     // Wait 2 seconds to let system settle down
     delay(2000);
     // Enable task that will read values from the DHT sensor
     tasksEnabled = true;
     if (tempTaskHandle != NULL) {
    		vTaskResume(tempTaskHandle);
    	}
    }
    yield();
   } else {
    Serial.println(F("Client not connected"));
    delay(1000);
    ESP.restart();
   }
}