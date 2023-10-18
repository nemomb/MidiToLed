#define PIN 6
#define NUMPIXELS 16

#include <Adafruit_NeoPixel.h>
#include <Adafruit_TinyUSB.h>
#include <MIDI.h>
#include "Animation.h"

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

Adafruit_USBD_MIDI usb_midi;
MIDI_CREATE_INSTANCE(Adafruit_USBD_MIDI, usb_midi, MIDI);


//timer
static uint16_t timer_interval = 100;
static long timer_last = 0;
int timer_count = 0;

///CLock
bool clock_on = false;
//Colors
int color_r = 255;
int color_g = 255;
int color_b = 255;

Animation animation = Blinker(pixels,0, NUMPIXELS, 1);

bool blink_on = false;

uint16_t walkingdot_i = 0;

int rocket_i = 0;

void setup() {
#if defined(ARDUINO_ARCH_MBED) && defined(ARDUINO_ARCH_RP2040)
  // Manual begin() is required on core without built-in support for TinyUSB such as mbed rp2040
  TinyUSB_Device_Init(0);
#endif
  usb_midi.setStringDescriptor("MidiLed");

  MIDI.begin(MIDI_CHANNEL_OMNI);
  MIDI.setHandleNoteOn(handleNoteOn);
  MIDI.setHandleClock(handleClock);

  pixels.begin();
  Serial.begin(115200);

  while (!TinyUSBDevice.mounted()) delay(1);
}

void loop() {
  MIDI.read();
}

void handleNoteOn(byte channel, byte pitch, byte velocity) {
  switch (pitch) {
    case 61: color_r = 255 * velocity / 127; break;
    case 62: color_g = 255 * velocity / 127; break;
    case 63: color_b = 255 * velocity / 127; break;
  }

  //Log when a note is pressed.
  Serial.print("Note on: channel = ");
  Serial.print(channel);

  Serial.print(" pitch = ");
  Serial.print(pitch);

  Serial.print(" velocity = ");
  Serial.println(velocity);
}


void blink(uint16_t from, uint16_t to, uint16_t gap) {
  if (blink_on) {
    for (uint16_t i = from; i < to; i = i + gap) {
      pixels.setPixelColor(i, pixels.Color(color_r, color_g, color_b));
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
  pixels.setPixelColor(walkingdot_i, pixels.Color(color_r, color_g, color_b));
  pixels.show();
} 

void rocket(int from, int to, int length) {

  if (rocket_i >= to) { rocket_i = from; }

  clearAll();

  for (int i = rocket_i; i >= (rocket_i - length); i--) {
    int led = i;
    if (led < from) {
      led = to - 1;
    } 
    uint16_t divisor = (3 * (rocket_i - i) + 1);
    pixels.setPixelColor(i, pixels.Color(color_r / divisor, color_g / divisor, color_b / divisor));
  } 
  pixels.show();
  rocket_i++;
}

void handleClock() { 
  animation.run();  
}

void clearAll() {
  for (uint16_t i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
  }
}
