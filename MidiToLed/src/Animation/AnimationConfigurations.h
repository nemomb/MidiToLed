// AnimationConfigurations.h
#pragma once

#include <map>
#include <string>
#include <vector>

struct AnimationConfig {
  std::string className;
  int from;
  int to;
  int duration;
  int specific;
};

extern std::map<int, std::vector<AnimationConfig>> animationConfigs;
extern const int TOTAL_LED_COUNT;