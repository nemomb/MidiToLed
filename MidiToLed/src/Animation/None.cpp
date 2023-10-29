/*
  Animation.cpp - Library for LED Animations.
  Created by Nemo, October, 2023.
*/

#include "Arduino.h"
#include <Adafruit_NeoPixel.h>
#include "Animation.h"
#include "None.h"

None::None(Adafruit_NeoPixel &pixels, int from, int to, int r, int g, int b, int durIn16th, int none) : Animation(pixels, from, to, r, g, b, durIn16th)
{
}

void None::run()
{
  if (first)
  {
    first = false;
    for (uint16_t i = from; i < to; i++)
    {
      pixels.setPixelColor(i, pixels.Color(0, 0, 0));
    }
    pixels.show();
  }
};
