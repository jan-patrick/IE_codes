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
const char* clientName[1] = { "arduino-entrance" };
const String clientNameString = "arduino-entrance";

//mqtt settings
const char mqtt_clientID[] = "Arduino Nano IOT";
const char mqtt_username[] = "connected-thing";
const char mqtt_password[] = "c784e41dd3da48d4";
WiFiClient net;
MQTTClient client;

unsigned long lastMillis = 0;
unsigned long lastJsonMillis = 0;
bool highlightStatus = false;

int sensorPin = 6;
int val = 0;
int state;
int lastState = LOW;

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 0;
int id = 0;

void connect() {
  //Serial.print("checking wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    //Serial.print("+");
    delay(1000);
  }

  //Serial.print("\nconnecting...");
  while (!client.connect(mqtt_clientID, mqtt_username, mqtt_password)) {
    //Serial.print("x");
    delay(1000);
  }

  //Serial.println("\nconnected!");

  client.subscribe("/jan");
  // client.unsubscribe("/hello");
}

void messageReceived(String &topic, String &payload) {
  //Serial.println(topic + " -> " + payload);
  JSONVar myObject = JSON.parse(payload);

  // JSON.typeof(jsonVar) can be used to get the type of the var
  if (JSON.typeof(myObject) == "undefined") {
    //Serial.println("Parsing input failed!");
    return;
  }

  // myObject.hasOwnProperty(key) checks if the object contains an entry for key
  if (myObject.hasOwnProperty("from") && myObject.hasOwnProperty("to")) {
    if (strcmp((const char*) myObject["to"], "all") == 0) {
      sayHi((const char*) myObject["from"]);
    } else if (strcmp((const char*) myObject["to"], clientName[0]) == 0) {
      JSONVar arduino = (JSONVar) myObject["arduino"];
      if (JSON.typeof(arduino) == "undefined") {
        //Serial.println("Parsing input failed!");
        return;
      }
      if (arduino.hasOwnProperty("id") && arduino.hasOwnProperty("debounceDelay")) {
        //id = (int) arduino["id"];
        //if (0 > id) {
        //  debounceDelay = 0;
        //} else if (1000 < id) {
        //  id = 1000;
        //}
        debounceDelay = (int) arduino["debounceDelay"];
        if (2 > debounceDelay) {
          debounceDelay = 2;
        } else if (1000 < debounceDelay) {
          debounceDelay = 1000;
        }
      }
    }
  }

  // JSON vars can be printed using print or println
  //Serial.print("myObject = ");
  //Serial.println(myObject);

  //Serial.println();
}


void setup() {
  //Serial.begin(9600);
  //Serial.println("WiFi.begin");
  WiFi.begin(ssid);

  // Note: Local domain names (e.g. "Computer.local" on OSX) are not supported by Arduino.
  // You need to set the IP address directly.
  //
  // MQTT brokers usually use port 8883 for secure connections.
  client.begin("broker.shiftr.io", net);
  client.onMessage(messageReceived);

  connect();

  pinMode(sensorPin, INPUT);

}

void loop() {
  client.loop();
  delay(10);  // <- fixes some issues with WiFi stability
  if (!client.connected()) {
    connect();
  }

  val = digitalRead(sensorPin);

  if (val != lastState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if (HIGH == val && (millis() - lastDebounceTime) > debounceDelay) {
    if (val == lastState) {
      // reset the debouncing timer
      state = val;

      lastMillis = millis();
      highlightStatus = true;
      createMessage();
    }
  }

  if (millis() - lastMillis > 5000 && highlightStatus) {
    highlightStatus = false;
    createMessage();
  }
  lastState = val;
}

void sayHi( const char* to) {
  lastJsonMillis = millis();

  JSONVar myObject;

  myObject["from"] = clientNameString;
  myObject["to"] = to;
  myObject["debug"] = "online";

  String jsonString = JSON.stringify(myObject);

  client.publish("/jan", jsonString);

  //Serial.println(sendJson);
}

void createMessage() {
  bool sendJson = false;
  if (millis() - lastJsonMillis > 500) {
    sendJson = true;
  } //else if (!highlightStatus) {
  //  sendJson = true;
  //}
  if (sendJson == true) {
    lastJsonMillis = millis();

    JSONVar myObject;
    JSONVar sofa;

    myObject["from"] = clientNameString;
    myObject["to"] = "display";
    sofa["id"] = 0;
    sofa["sofaPosition"] = -1;
    sofa["highlightStatus"] = highlightStatus;
    myObject["sofa"] = sofa;

    String jsonString = JSON.stringify(myObject);

    client.publish("/jan", jsonString);
  }

  //Serial.println(sendJson);
}
