#line 1 "C:\\Users\\manue\\Documents\\Arduino\\Projects\\MidiToLed\\MidiToLed\\Animation.cpp"
/*
  Animation.cpp - Library for LED Animations.
  Created by Nemo, October, 2023.
*/

#include "Arduino.h"
#include <Adafruit_NeoPixel.h>
#include "Animation.h"

void Animation::setColors(int8_t r, int8_t g, int8_t b)
{
  color_r = r;
  color_g = g;
  color_b = b;
};

void Animation::run(){}; 
 

