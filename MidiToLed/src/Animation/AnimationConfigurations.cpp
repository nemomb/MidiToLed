// AnimationConfigurations.cpp
#include "AnimationConfigurations.h"
#include <map>
#include <string>
#include <vector>

std::map<int, std::vector<AnimationConfig>> animationConfigs = {
  //Classname, from, to, duration, specific
  {64, {
    {"Blinker", 0, 1, 120, 1},
    {"WalkingDot", 120, 240, 4, 4},
    {"Blinker", 13, 16, 4, 1}
  }},
  {65, {
    {"Blinker", 0, 120, 2, 1},
    {"None", 1, 13, 16, 1},
    {"None", 13, 16, 4, 1}
  }},
  {66, {
    {"WalkingDot", 0, 120, 8, 1},
    {"None", 1, 13, 16, 1},
    {"None", 13, 16, 4, 1}
  }},
   {67, {
    {"WalkingDot", 0, 60, 16, 1},
    {"WalkingDot", 60, 120, 8, 8},
    {"None", 13, 16, 4, 1}
  }},
  {68, {
    {"Flame", 0, 120, 16, 5},
    {"None", 8, 16, 8, 8},
    {"None", 13, 16, 4, 1}
  }},
};