/*
  Animation.cpp - Library for LED Animations.
  Created by Nemo, October, 2023.
*/

#include "Arduino.h"
#include <Adafruit_NeoPixel.h>
#include "Animation.h"
#include "Flash.h"

Flash::Flash(Adafruit_NeoPixel &pixels, int from, int to, int r, int g, int b, int durIn16th, int gap) : Animation(pixels, from, to, r, g, b, durIn16th)
{
  this->off = false;
  this->gap = gap;
}

void Flash::run()
{
  if (!off)
  {
    for (uint16_t i = from; i < to; i = i + 1)
    {
      pixels.setPixelColor(i, pixels.Color(color_r, color_g, color_b));
    }
  }
  else
  {
    for (uint16_t i = from; i < to; i = i + 1)
    {
      uint32_t pixelColor = pixels.getPixelColor(i);
      uint8_t red = (pixelColor >> 16) & 0xFF;
      uint8_t green = (pixelColor >> 8) & 0xFF;
      uint8_t blue = pixelColor & 0xFF;
      pixels.setPixelColor(i, pixels.Color(0, 0, 0));
    }
  }
  pixels.show();

  if(counter >= 3 * durationIn16th - 1 || off){
    off=true;
  } else {
    counter++;
  }
};
