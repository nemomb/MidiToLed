/*
  Animation.h - LED Animations.
  Created by Nemo, October, 2023.
*/

#ifndef Flash_h
#define Flash_h

#include "PixelFacade.h"
#include "Animation.h" 

class Flash : public Animation { 
  private:
    int gap; 
    bool off = false;
  public:
    Flash(PixelFacade &pixels, int from, int to, int r, int g, int b, int durIn16th, int gap);
    void run() override ;
};
#endif