#include "Arduino.h"
#include <Adafruit_NeoPixel.h>
#include "Animation.h"
#include "WalkingDot.h" 


WalkingDot::WalkingDot(Adafruit_NeoPixel &pixels, int from, int to, int speed, int start) : Animation(), pixels(pixels), from(from), to(to)
{
  this->pixels = pixels;
  this->from = from;
  this->to = to;
  this->walkingdot_i = start;
  this->speed = speed; 
  this->counter = 0;
  this->numberOfLeds = to - from;
}


void WalkingDot::run() {
  
     int walkingdot_i_prev = (int) walkingdot_i;
    
     walkingdot_i =  walkingdot_i + 3*speed/numberOfLeds; 
     if(walkingdot_i_prev!= (int)walkingdot_i){
        pixels.setPixelColor((int)walkingdot_i_prev, pixels.Color(0, 0, 0));
        pixels.setPixelColor((int)walkingdot_i, pixels.Color(color_r, color_g, color_b));
     }     
     if (walkingdot_i >= to) {
      walkingdot_i = from;
    }   
    
    pixels.show(); 

  

}