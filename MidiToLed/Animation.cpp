/*
  Animation.cpp - Library for LED Animations.
  Created by Nemo, October, 2023.
*/

#include "Arduino.h"
#include <Adafruit_NeoPixel.h>
#include "Animation.h"

void Animation::setColors(int8_t r, int8_t g, int8_t b)
{
  color_r = r;
  color_g = g;
  color_b = b;
};

void Animation::run(){};

Blinker::Blinker(Adafruit_NeoPixel pixels, int from, int to, int gap)
{
  this->from = from;
  this->to = to;
  this->gap = gap;
  this->pixels = pixels;
}

void Blinker::run()
{
  if (blink_on)
  {
    for (uint16_t i = from; i < to; i = i + gap)
    {
      pixels.setPixelColor(i, pixels.Color(color_r, color_g, color_b));
    }
  }
  else
  {
    pixels.clear();
  }
  pixels.show();
  blink_on = !blink_on;
}
