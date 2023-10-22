#ifndef WalkingDot_h
#define WalkingDot_h

#include <Adafruit_NeoPixel.h>
#include "Animation.h"

class WalkingDot : public Animation {
private:
  int from;
  int to;
  int speed;
  float walkingdot_i; 
  int counter;
  int numberOfLeds;
  Adafruit_NeoPixel& pixels;
public:
  WalkingDot(Adafruit_NeoPixel& pixels, int from, int to, int speed, int start);
  void run() override; 
};

#endif
