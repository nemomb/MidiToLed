/*
  Animation.cpp - Library for LED Animations.
  Created by Nemo, October, 2023.
*/

#include "Arduino.h"
#include "PixelFacade.h"
#include "Animation.h"

Animation::Animation(PixelFacade &pixels, int from, int to, int r, int g, int b, int8_t durationIn16th)
    : pixels(pixels), from(from), to(to), color_r(r), color_g(g), color_b(b), durationIn16th(durationIn16th), counter(0) {
    // Other initialization, if needed
}

void Animation::setColors(int8_t r, int8_t g, int8_t b)
{
  color_r = r;
  color_g = g;
  color_b = b;
};

void Animation::run(){}; 

int Animation::incrementCounter()
{
 if(counter >= 3 * durationIn16th - 1 ){
    counter = 0;
  } else {
    counter++;
  }
};
 

