#line 1 "C:\\Users\\manue\\Documents\\Arduino\\Projects\\MidiToLed\\MidiToLed\\Blinker.h"
/*
  Animation.h - LED Animations.
  Created by Nemo, October, 2023.
*/

#ifndef Blinker_h
#define Blinker_h

#include <Adafruit_NeoPixel.h>
#include "Animation.h" 

class Blinker : public Animation { 
  private:
    int from;
    int to;
    int divisor;
    int gap; 
    int counter;
    Adafruit_NeoPixel& pixels;
    bool blink_on = false;
  public:
    Blinker(Adafruit_NeoPixel& pixels, int from, int to, int divisor, int gap);
    void run() override ;
};
#endif