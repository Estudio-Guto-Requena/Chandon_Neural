#include <Arduino.h>
#include <SoftwareSerial.h>
#include <ArduinoJson.h>
#include <WiFiUdp.h>
#include <ESP8266WiFi.h>
#include <data.h>

#define RX D6
#define TX D7


WiFiUDP udp_client;
SoftwareSerial linkSerial(RX, TX);

unsigned long previousCheck = 0;
unsigned long interval = 3000;

int quality, ms_ago, attention, meditation;
String name;

void udpSend(StaticJsonDocument<512> doc) {
  udp_client.beginPacket(DEST, PORT);
  serializeJson(doc, udp_client);
  udp_client.println();
  udp_client.endPacket();
}

void WiFiStart() {
  delay(1000);
  Serial.print("Conectando em ");
  Serial.println(SSID);
  WiFi.begin(SSID, PASS);
  while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
  }
  Serial.println("Ready");
  Serial.print("IP address Host: ");
  Serial.println(WiFi.localIP());
  Serial.print("IP address Dest: ");
  Serial.println(DEST);
}

void check_wifi() {
  unsigned long currentCheck = millis();
  if ((WiFi.status() != WL_CONNECTED) && (currentCheck - previousCheck>=interval)) {
    Serial.println("Reconnecting to WiFi...");
    WiFi.disconnect();
    WiFi.reconnect();
    previousCheck = currentCheck;
  }
}

void deserialize () {
  StaticJsonDocument<512> doc;
  DeserializationError err = deserializeJson(doc, linkSerial);
  if (err == DeserializationError::Ok){
    serializeJson(doc, Serial);
    udpSend(doc);
    quality = doc["quality"].as<int>();
    ms_ago = doc["ms_ago"].as<int>();

    attention = doc["attention"].as<int>();
    meditation = doc["meditation"].as<int>();

    name = doc["name"].as<String>();
  }
  else {
    Serial.print("deserializeJson() returned ");
    Serial.println(err.c_str());
    while (linkSerial.available() > 0)linkSerial.read();
  }
}

void setup() {
  Serial.begin(57600);
  linkSerial.begin(9600);
  WiFiStart();
}

void loop() {
  if (linkSerial.available()) {
    deserialize ();
  }
}
