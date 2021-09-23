#include <Arduino.h>
#include "BluetoothSerial.h"
#include <Mindwave.h>
#include <ArduinoJson.h>
#include <HardwareSerial.h>
#include <config.h>

#define TXD2 9
#define RXD2 10

BluetoothSerial SerialBT;
HardwareSerial MySerial(1);
Mindwave mindwave;


unsigned long int last;
bool first_read = false;
unsigned int timeout = 1500;

const char *pin = "0000"; //<- standard pin would be provided by default

void neuro_connect() {
  first_read = false;
  SerialBT.disconnect();
  Serial.println("Connecting...");
  while(!SerialBT.connect(address))
      Serial.println("Failed... Make sure remote device is available and in range");
  Serial.println("Connected Succesfully!");
  last = millis();
}

void setup() {
  Serial.begin(MINDWAVE_BAUDRATE);
  MySerial.begin(9600, SERIAL_8N1, 16, 17);
  SerialBT.begin("ESP32_client", true);
  SerialBT.setPin(pin);
  Serial.println("The device started in master mode, make sure remote BT device is on!");
  neuro_connect();
}

void onMindwaveData() {
  StaticJsonDocument<512> doc;
  first_read = true;
  last = millis();
  doc["name"] = NAME;
  doc["quality"] = mindwave.quality();
  doc["ms_ago"]   = mindwave.lastUpdate();

  doc["attention"] = mindwave.attention();
  doc["meditation"] = mindwave.meditation();

  serializeJson(doc, MySerial);
  serializeJson(doc, Serial);
  Serial.println();
}


void loop() {
  mindwave.update(SerialBT,onMindwaveData);
  if(millis() - last > timeout && first_read) ESP.restart();
}
