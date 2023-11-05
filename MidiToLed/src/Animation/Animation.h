/*
  Animation.h - LED Animations.
  Created by Nemo, October, 2023.
*/

#ifndef Animation_h
#define Animation_h

#include "PixelFacade.h"

class Animation
{
public:
  int8_t color_r;
  int8_t color_g; 
  int8_t color_b;
  PixelFacade& pixels;  
  int from;
  int to;
  int8_t durationIn16th;
  Animation(PixelFacade &pixels, int from, int to,  int r, int g, int b, int8_t durationIn16th);
  void setColors(int8_t r, int8_t g, int8_t b);
  virtual void run();
  int counter = 0;
  int incrementCounter();
};

#endif