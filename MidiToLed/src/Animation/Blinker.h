/*
  Animation.h - LED Animations.
  Created by Nemo, October, 2023.
*/

#ifndef Blinker_h
#define Blinker_h

#include <Adafruit_NeoPixel.h>
#include "Animation.h" 

class Blinker : public Animation { 
  private:
    int gap; 
    bool blink_on = true;
  public:
    Blinker(Adafruit_NeoPixel &pixels, int from, int to, int r, int g, int b, int durIn16th, int gap);
    void run() override ;
};
#endif