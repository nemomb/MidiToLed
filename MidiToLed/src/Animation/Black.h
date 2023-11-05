
#ifndef Black_h
#define Black_h

#include "PixelFacade.h" 
#include "Animation.h" 

class Black : public Animation { 
  private:
   bool first =true;
  public:
    Black(PixelFacade &pixels, int from, int to, int r, int g, int b, int durIn16th, int none);
    void run() override ;
};
#endif