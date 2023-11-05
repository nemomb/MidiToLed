#ifndef PixelFacade_h
#define PixelFacade_h


#include <Adafruit_NeoPixel.h>

class PixelFacade
{
public:
    PixelFacade(int numPixels);


    void setPixelColor(int index, uint8_t r, uint8_t g, uint8_t b);
    void show();
    uint32_t getPixelColor(int index);

private:
    int numPixels;
    Adafruit_NeoPixel pixels;
    uint32_t *pixelColors;
};

#endif
