// AnimationConfigurations.cpp
#include "AnimationConfigurations.h"
#include <map>
#include <string>
#include <vector>

const int TOTAL_LED_COUNT = 240;

std::map<int, std::vector<AnimationConfig>> animationConfigs = {
  //Classname, from, to, duration, specific
  {64, {
    {"Flash", 0, 120, 1, 1},
    {"Black", 120, 240, 8, 4},
    {"None", 120, 200, 8, 1},
    {"None", 200, 240, 8, 4},

  }},
  {65, {
    {"Flash", 120, 240, 1, 1},
    {"Black", 0, 120, 8, 4},
    {"None", 120, 200, 8, 1},
    {"None", 200, 240, 8, 4},
  }},
  {66, {
    {"WalkingDot", 0, 240, 8, 1},
    {"None", 1, 13, 16, 1},
    {"None", 13, 16, 4, 1}
  }},
   {67, {
    {"WalkingDot", 0, 80, 16, 1},
    {"Flame", 80, 120, 8, 8},
    {"WalkingDot", 120, 240, 4, 1}
  }},
  {68, {
    {"Flame", 0, 240, 16, 5},
    {"None", 8, 16, 8, 8},
    {"None", 13, 16, 4, 1}
  }},
};