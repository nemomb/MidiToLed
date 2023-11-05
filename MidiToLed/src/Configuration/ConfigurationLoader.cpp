#include "Arduino.h"
#include <ArduinoJson.h> // https://arduinojson.org/
#include "../Animation/Animationconfigurations.h"


class ConfigurationLoader { 
public:
  ConfigurationLoader() {}

  void loadConfigFromAPI(const char* apiUrl) {
    // Make an HTTP GET request to the API to fetch the configuration data.
    // You should use your preferred library to make HTTP requests.
    // Parse the JSON response and populate the `animationConfigs` map.

    // Example JSON response:
    const char* jsonResponse = "{\"64\":[{\"Blinker\": [0, 80, 8, 1}, {\"WalkingDot\": [80, 120, 8, 4}]}," 
                              "\"65\":[{\"Blinker\": [0, 40, 2, 1}, {\"WalkingDot\": [40, 240, 8, 1}, {\"None\": [13, 16, 4, 1}]}]}";

    DynamicJsonDocument doc(1024);
    DeserializationError error = deserializeJson(doc, jsonResponse);

    if (error) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.c_str());
      return;
    }

    for (JsonPair kv : doc.as<JsonObject>()) {
      /*int key = 1;//kv.key().toInt();
      animationConfigs[key].clear(); // Clear existing configurations for this key.

      for (JsonVariant item : kv.value().as<JsonArray>()) {
        AnimationConfig config;
        config.className = item[0].as<String>();
        config.from = item[1][0].as<int>();
        config.to = item[1][1].as<int>();
        config.duration = item[1][2].as<int>();
        config.specific = item[1][3].as<int>();
        animationConfigs[key].push_back(config);
      }
      */
    }
  }
};

ConfigurationLoader configLoader;

/*
void setup() {
  // Initialize your hardware and Serial as before.
  // ...

  // Load the configuration from the API.
  configLoader.loadConfigFromAPI("https://led.kasparov.ch"); // Replace with the actual API URL.
}*/
