/*
  Animation.h - LED Animations.
  Created by Nemo, October, 2023.
*/

#ifndef Animation_h
#define Animation_h

#include <Adafruit_NeoPixel.h>

class Animation {
  public:
  int8_t color_r;
  int8_t color_g;
  int8_t color_b;
  void setColors(int8_t r, int8_t g, int8_t b);
  virtual void run();
};

class Blinker : public Animation{
  bool from;
  int to;
  int gap;
  Adafruit_NeoPixel pixels;
  bool blink_on = false;
  public:
  Blinker(Adafruit_NeoPixel pixels, int from, int to, int gap);

  void run();
};
#endif