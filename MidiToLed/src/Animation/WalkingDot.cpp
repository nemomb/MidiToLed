#include "Arduino.h"
#include "PixelFacade.h"
#include "Animation.h"
#include "WalkingDot.h"

WalkingDot::WalkingDot(PixelFacade &pixels, int from, int to, int r, int g, int b, int durIn16th, int start) : Animation(pixels, from, to, r, g, b, durIn16th)
{
  this->walkingdot_i = start;
  this->increment = (float)(to - from) / (float)(6 * durationIn16th);
}

void WalkingDot::run()
{
  if ((int)walkingdot_i >= to)
  {
    pixels.setPixelColor(to - 1, 0, 0, 0);
    walkingdot_i = from;
    pixels.setPixelColor((int)walkingdot_i, color_r, color_g, color_b);
  }
  else if (walkingdot_i_prev != (int)walkingdot_i)
  {
    pixels.setPixelColor((int)walkingdot_i_prev, 0, 0, 0);
    pixels.setPixelColor((int)walkingdot_i, color_r, color_g, color_b);
  }
  walkingdot_i_prev = (int)walkingdot_i;
  walkingdot_i = walkingdot_i + increment;
}