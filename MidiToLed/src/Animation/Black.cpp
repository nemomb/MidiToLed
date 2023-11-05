#include "Arduino.h"
#include "PixelFacade.h"
#include "Animation.h"
#include "Black.h"

Black::Black(PixelFacade &pixels, int from, int to, int r, int g, int b, int durIn16th, int none) : Animation(pixels, from, to, r, g, b, durIn16th)
{
}

void Black::run()
{
  if (first)
  {
    first = false;
    for (uint16_t i = from; i < to; i++)
    {
      pixels.setPixelColor(i, 0, 0, 0);
    }
  }
};
