// ConfigurationLoader.h
#ifndef CONFIGURATION_LOADER_H
#define CONFIGURATION_LOADER_H

#include "ArduinoJson.h"
//#include "AnimationConfigurations.h" 

class ConfigurationLoader {
public:
  ConfigurationLoader() {}

  void loadConfigFromAPI(const char* apiUrl);
};

extern ConfigurationLoader configLoader;

#endif // CONFIGURATION_LOADER_H
