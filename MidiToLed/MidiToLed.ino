#define PIN 6         
#define NUMPIXELS 16  

#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

//timer
static uint16_t interval = 100;
static long last = 0;

bool blink_on = false;

uint16_t walkingdot_i = 0;

int rocket_i = 0;

void setup() {
  pixels.begin();
}

void loop() {
  if (next()) {
    blink(2);
    //rocket(150, 70, 255, 5);
  }
}

void blink(uint16_t gap) {
  if (blink_on) {
    for (uint16_t i = 0; i < NUMPIXELS; i = i + gap) {
      pixels.setPixelColor(i, pixels.Color(255, 255, 255));
    }
  } else {
    clearAll();
  }
  pixels.show();
  blink_on = !blink_on;
}

void walkingdot() {
  pixels.setPixelColor(walkingdot_i, pixels.Color(0, 0, 0));
  walkingdot_i++;
  if (walkingdot_i >= NUMPIXELS) {
    walkingdot_i = 0;
  }
  pixels.setPixelColor(walkingdot_i, pixels.Color(0, 150, 0));
  pixels.show();
}

void rocket(uint16_t r, uint16_t g, uint16_t b, int length) {
  
  if (rocket_i >= NUMPIXELS) { rocket_i = 0; }
   
  clearAll();
   //pixels.setPixelColor(rocket_i, pixels.Color(r, g, b));
   
  for (int i = rocket_i; i >= (rocket_i - length); i--) {
     int led = i;
     if(led<0){
      led = NUMPIXELS-1;
    }
    uint16_t divisor = (3*(rocket_i-i)+1);
    pixels.setPixelColor(i, pixels.Color(r/divisor, g/divisor, b/divisor));
  }
  pixels.show();
 rocket_i++;
}

bool next() {
  if (millis() > last + interval) {
    last = millis();
    return true;
  }
  return false;
}

void clearAll() {
  for (uint16_t i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
  }
}
