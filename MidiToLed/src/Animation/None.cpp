/*
  Animation.cpp - Library for LED Animations.
  Created by Nemo, October, 2023.
*/

#include "Arduino.h"
#include "PixelFacade.h"
#include "Animation.h"
#include "None.h"

None::None(PixelFacade &pixels, int from, int to, int r, int g, int b, int durIn16th, int none) : Animation(pixels, from, to, r, g, b, durIn16th)
{
}

void None::run(){};
