#include "Arduino.h"
#include "PixelFacade.h"
#include "Animation.h"
#include "Flicker.h" 

Flicker::Flicker(PixelFacade &pixels, int from, int to, int r, int g, int b, int durIn16th, int intensity) : Animation(pixels, from, to, r,g,b, durIn16th) {
  if (intensity <= 0) {
    intensity = 1; // Set a minimum intensity
  }
  this->intensity = intensity;

}

void Flicker::run() {
      Serial.println(intensity);

  int flicker = random(1, intensity + 1);
  if (counter % flicker == 0) {
    for (uint16_t i = from; i < to; i++) {
      int r = color_r - flicker;
      int g = color_g - flicker / 2;
      int b = color_b;
      r = max(0, r);
      g = max(0, g);
      g = max(0, b);
      pixels.setPixelColor(i, r, g, b);
    }
  } else {
    for (uint16_t i = from; i < to; i++) {
      pixels.setPixelColor(i, 0, 0, 0);
    }
  }

  counter = (counter + 1) % (3 * durationIn16th);
}
