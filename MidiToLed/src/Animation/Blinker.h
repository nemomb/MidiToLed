/*
  Animation.h - LED Animations.
  Created by Nemo, October, 2023.
*/

#ifndef Blinker_h
#define Blinker_h

#include "PixelFacade.h"
#include "Animation.h" 

class Blinker : public Animation { 
  private:
    int gap; 
    bool blink_on = true;
  public:
    Blinker(PixelFacade &pixels, int from, int to, int r, int g, int b, int durIn16th, int gap);
    void run() override ;
};
#endif