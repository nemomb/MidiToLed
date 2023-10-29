
#ifndef None_h
#define None_h

#include <Adafruit_NeoPixel.h>
#include "Animation.h" 

class None : public Animation { 
  private:
   bool first =true;
  public:
    None(Adafruit_NeoPixel &pixels, int from, int to, int r, int g, int b, int durIn16th, int none);
    void run() override ;
};
#endif