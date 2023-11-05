
#ifndef Black_h
#define Black_h

#include <Adafruit_NeoPixel.h>
#include "Animation.h" 

class Black : public Animation { 
  private:
   bool first =true;
  public:
    Black(Adafruit_NeoPixel &pixels, int from, int to, int r, int g, int b, int durIn16th, int none);
    void run() override ;
};
#endif