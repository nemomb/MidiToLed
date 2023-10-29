/*
  Animation.h - LED Animations.
  Created by Nemo, October, 2023.
*/
#ifndef Flame_h
#define Flame_h

#include "Arduino.h"
#include <Adafruit_NeoPixel.h>
#include "Animation.h"

class Flicker : public Animation {
public:
  Flicker(Adafruit_NeoPixel &pixels, int from, int to, int r, int g, int b, int durIn16th, int intensity);
  void run() override;

private:
  int intensity; // Flicker intensity
  int counter =0;
};

#endif

