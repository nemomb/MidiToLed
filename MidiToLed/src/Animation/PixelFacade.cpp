#include "PixelFacade.h"
#include <Adafruit_NeoPixel.h>
#define Channel_Pin 6

PixelFacade::PixelFacade(int numPixels) : numPixels(numPixels), pixels(Adafruit_NeoPixel(numPixels, Channel_Pin, NEO_GRB + NEO_KHZ800))
{
    //pixels.begin();
 
    pixelColors = new uint32_t[numPixels];
   /* for (int i = 0; i < numPixels; i++)
    {
        pixelColors[i] = pixels.Color(0, 0, 0);
    }
    pixels.show(); */
}

void PixelFacade::setPixelColor(int index, uint8_t r, uint8_t g, uint8_t b)
{
    if (index >= 0 && index < numPixels)
    {
        pixelColors[index] = pixels.Color(r, g, b);
    }
}

uint32_t PixelFacade::getPixelColor(int index)
{
    return pixelColors[index];
}

void PixelFacade::show()
{
    for (int i = 0; i < numPixels; i++)
    {
        pixels.setPixelColor(i, pixelColors[i]);
    }
    pixels.show();
}







