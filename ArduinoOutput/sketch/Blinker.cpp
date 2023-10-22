#line 1 "C:\\Users\\manue\\Documents\\Arduino\\Projects\\MidiToLed\\MidiToLed\\Blinker.cpp"
/*
  Animation.cpp - Library for LED Animations.
  Created by Nemo, October, 2023.
*/

#include "Arduino.h"
#include <Adafruit_NeoPixel.h>
#include "Animation.h"
#include "Blinker.h"

Blinker::Blinker(Adafruit_NeoPixel &pixels, int from, int to, int speed, int gap) : Animation(), pixels(pixels), from(from), to(to), gap(gap)
{
  this->pixels = pixels;
  this->from = from;
  this->to = to;
  this->gap = gap;
  this->speed = speed;  
  this->counter = 0;
}

void Blinker::run()
{
  if (counter == 0)
  {
    if (blink_on)
    {
      for (uint16_t i = from; i < to; i = i + gap)
      {
        pixels.setPixelColor(i, pixels.Color(color_r, color_g, color_b)); 
      }
    }
    else
    {
      for (uint16_t i = from; i < to; i = i + gap)
      {
        pixels.setPixelColor(i, pixels.Color(0, 0, 0));
      }
    }
    pixels.show();
    blink_on = !blink_on;
  }
  if(counter >= 3 * speed - 1 ){
    counter = 0;
  } else {
    counter++;
  }
};
