/*
  Animation.h - LED Animations.
  Created by Nemo, October, 2023.
*/

#ifndef Flash_h
#define Flash_h

#include <Adafruit_NeoPixel.h>
#include "Animation.h" 

class Flash : public Animation { 
  private:
    int gap; 
    bool off = false;
  public:
    Flash(Adafruit_NeoPixel &pixels, int from, int to, int r, int g, int b, int durIn16th, int gap);
    void run() override ;
};
#endif