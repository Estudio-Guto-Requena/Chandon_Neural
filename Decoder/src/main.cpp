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
unsigned int timeout = 2500;

const char *pin = "0000"; //<- standard pin would be provided by default

void print_mac(uint8_t mac[6]) {
  Serial.print(mac[0],HEX);
  Serial.print(":");
  Serial.print(mac[1],HEX);
  Serial.print(":");
  Serial.print(mac[2],HEX);
  Serial.print(":");
  Serial.print(mac[3],HEX);
  Serial.print(":");
  Serial.print(mac[4],HEX);
  Serial.print(":");
  Serial.print(mac[5],HEX);
}

void neuro_connect() {
  first_read = false;
  SerialBT.disconnect();
  Serial.print("Connecting to BT ");
  print_mac(address);
  Serial.println("...");
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
  if(millis() - last > timeout && first_read) ESP.restart();
  mindwave.update(SerialBT,onMindwaveData);
  first_read = true;
}
