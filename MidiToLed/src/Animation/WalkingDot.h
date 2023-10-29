#ifndef WalkingDot_h
#define WalkingDot_h

#include <Adafruit_NeoPixel.h>
#include "Animation.h"

class WalkingDot : public Animation {
private:
  float walkingdot_i; 
  float increment;
  float walkingdot_i_prev =-1; 
public:
  WalkingDot(Adafruit_NeoPixel &pixels, int from, int to, int r, int g, int b, int durIn16th, int start);
  void run() override; 
};

#endif
