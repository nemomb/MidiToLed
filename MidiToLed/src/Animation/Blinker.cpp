/*
  Animation.cpp - Library for LED Animations.
  Created by Nemo, October, 2023.
*/

#include "Arduino.h"
#include "PixelFacade.h"
#include <Adafruit_NeoPixel.h>
#include "Animation.h"
#include "Blinker.h"

Blinker::Blinker(PixelFacade &pixels, int from, int to, int r, int g, int b, int durIn16th, int gap) : Animation(pixels, from, to, r, g, b, durIn16th) {
  this->gap = gap;
} 

void Blinker::run()
{
  if (counter == 0)
  {
    if (blink_on)
    {

      for (uint16_t i = from; i < to; i = i + gap)
      {
        pixels.setPixelColor(i, color_r, color_g, color_b); 
      }
    }
    else
    {
      for (uint16_t i = from; i < to; i = i + gap)
      {
        pixels.setPixelColor(i, 0, 0, 0);
      }
    }
    blink_on = !blink_on;
  }
  incrementCounter();
  
};
