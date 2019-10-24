// Main program file for prototype 4 (luggage waiting joyful)
//
// Uses (check the tabs of your Arduino window):
//   2_users.ino    - user detection
//   2_database.ino - for the user / luggage database
//   2_led-matrix   - for luggage highlighting
//   debug.ino    - for Serial and debugging
//
// Created October 2019
// By Jan Schneider

#include <WiFiNINA.h>
#include <MQTT.h>
#include <Arduino_JSON.h>

//wifi settings
const char ssid[] = "TUvisitor";
const char pass[] = "pass";

//mqtt settings
const char mqtt_clientID[] = "Arduino Nano IOT";
const char mqtt_username[] = "connected-thing";
const char mqtt_password[] = "c784e41dd3da48d4";
WiFiClient net;
MQTTClient client;

unsigned long lastMillis = 0;
unsigned long lastJsonMillis = 0;
bool highlightStatus = false;

int sensorPin = 2;

void connect() {
  Serial.print("checking wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("+");
    delay(1000);
  }

  Serial.print("\nconnecting...");
  while (!client.connect(mqtt_clientID, mqtt_username, mqtt_password)) {
    Serial.print("x");
    delay(1000);
  }

  Serial.println("\nconnected!");

  client.subscribe("/jan");
  // client.unsubscribe("/hello");
}

void messageReceived(String &topic, String &payload) {
  Serial.println(topic + " -> " + payload);
}


void setup() {
  Serial.begin(9600);
  Serial.println("WiFi.begin");
  WiFi.begin(ssid);

  // Note: Local domain names (e.g. "Computer.local" on OSX) are not supported by Arduino.
  // You need to set the IP address directly.
  //
  // MQTT brokers usually use port 8883 for secure connections.
  client.begin("broker.shiftr.io", net);
  client.onMessage(messageReceived);

  connect();

}

void loop() {
  client.loop();
  delay(10);  // <- fixes some issues with WiFi stability

  if (!client.connected()) {
    connect();
  }

  if (30 >= analogRead(sensorPin)) {
    lastMillis = millis();
    highlightStatus = true;
    createMessage();
  }

  if (millis() - lastMillis > 5000 && highlightStatus) {
    highlightStatus = false;
    createMessage();
  }
}

void createMessage() {
  bool sendJson = true;
  if (millis() - lastJsonMillis > 500) {
    sendJson = false;
  } else if (!highlightStatus) {
    sendJson = true;
  }
  if (sendJson) {
    lastJsonMillis = millis();

    JSONVar myObject;
    JSONVar sofa;

    sofa["id"] = 0;
    sofa["sofaPosition"] = -1;
    sofa["highlightStatus"] = highlightStatus;
    myObject["sofa"] = sofa;

    String jsonString = JSON.stringify(myObject);
    
    client.publish("/jan", jsonString);
  }
}
