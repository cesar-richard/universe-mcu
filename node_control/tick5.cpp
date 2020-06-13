void customtick5(WiFiClient client, void (&cb)(String, String, String)){
  cb(F("heartbeat"),F("core"),F("alive"));
}