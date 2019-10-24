// Main program file for prototype 2 (luggage finding support)
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

  // publish a message roughly every second.
  if (millis() - lastMillis > 5000) {
    lastMillis = millis();
    client.publish("/jan", "world");
    demoCreation();
  }
}

void demoCreation() {
  Serial.println("creation");
  Serial.println("========");

  JSONVar myObject;
  JSONVar sofa;

  
  sofa["id"] = 0;
  sofa["sofaPosition"] = -1;
  sofa["highlightStatus"] = true;
  
  myObject["test"] = "world";
  myObject["sofa"] = sofa;
  //myObject["x"] = 42;

  Serial.print("myObject.keys() = ");
  Serial.println(myObject.keys());

  // JSON.stringify(myVar) can be used to convert the json var to a String
  String jsonString = JSON.stringify(myObject);

  Serial.print("JSON.stringify(myObject) = ");
  Serial.println(jsonString);

  Serial.println();

  // myObject.keys() can be used to get an array of all the keys in the object
  JSONVar keys = myObject.keys();

  for (int i = 0; i < keys.length(); i++) {
    JSONVar value = myObject[keys[i]];

    Serial.print("JSON.typeof(myObject[");
    Serial.print(keys[i]);
    Serial.print("]) = ");
    Serial.println(JSON.typeof(value));

    Serial.print("myObject[");
    Serial.print(keys[i]);
    Serial.print("] = ");
    Serial.println(value);

    Serial.println();
  }

  Serial.println();

  // setting a value to undefined can remove it from the object
  myObject["x"] = undefined;

  // you can also change a value
  myObject["hello"] = "there!";

  Serial.print("myObject = ");
  Serial.println(myObject);
}
