/*
  Animation.cpp - Library for LED Animations.
  Created by Nemo, October, 2023.
*/

#include "Arduino.h"
#include <Adafruit_NeoPixel.h>
#include "Animation.h"

Animation::Animation(Adafruit_NeoPixel &pixels, int from, int to,  int r, int g, int b,int8_t durationIn16th)
{
  this->pixels = pixels; 
  this->from = from;
  this->to = to;
  this->durationIn16th = durationIn16th;
  this->color_r = r;
  this->color_g = g;
  this->color_b = b;
} 

void Animation::setColors(int8_t r, int8_t g, int8_t b)
{
  color_r = r;
  color_g = g;
  color_b = b;
};

void Animation::run(){}; 
 

