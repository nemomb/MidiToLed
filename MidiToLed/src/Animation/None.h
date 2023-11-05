
#ifndef None_h
#define None_h

#include "PixelFacade.h"
#include "Animation.h" 

class None : public Animation { 
  private:
   bool first =true;
  public:
    None(PixelFacade &pixels, int from, int to, int r, int g, int b, int durIn16th, int none);
    void run() override ;
};
#endif