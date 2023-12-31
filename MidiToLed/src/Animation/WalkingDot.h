#ifndef WalkingDot_h
#define WalkingDot_h

#include "PixelFacade.h"
#include "Animation.h"

class WalkingDot : public Animation {
private:
  float walkingdot_i; 
  float increment;
  float walkingdot_i_prev =-1; 
public:
  WalkingDot(PixelFacade &pixels, int from, int to, int r, int g, int b, int durIn16th, int start);
  void run() override; 
};

#endif
