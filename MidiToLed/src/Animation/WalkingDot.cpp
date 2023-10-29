#include "Arduino.h"
#include <Adafruit_NeoPixel.h>
#include "Animation.h"
#include "WalkingDot.h"

WalkingDot::WalkingDot(Adafruit_NeoPixel &pixels, int from, int to, int r, int g, int b, int durIn16th, int start) : Animation(pixels, from, to, r, g, b, durIn16th)
{
  this->walkingdot_i = start;
  this->increment = (float)(to - from) / (float)(6 * durationIn16th);
}

void WalkingDot::run()
{
  if ((int)walkingdot_i >= to)
  {
    pixels.setPixelColor(to - 1, pixels.Color(0, 0, 0));
    walkingdot_i = from;
    pixels.setPixelColor((int)walkingdot_i, pixels.Color(color_r, color_g, color_b));
    pixels.show();
  }
  else if (walkingdot_i_prev != (int)walkingdot_i)
  {
    pixels.setPixelColor((int)walkingdot_i_prev, pixels.Color(0, 0, 0));
    pixels.setPixelColor((int)walkingdot_i, pixels.Color(color_r, color_g, color_b));
    pixels.show();
  }
  walkingdot_i_prev = (int)walkingdot_i;
  walkingdot_i = walkingdot_i + increment;
}