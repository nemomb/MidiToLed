#define PIN 6
#define NUMPIXELS 16
#include <Arduino.h>
#include "src/Animation/Animation.h"
#include "src/Animation/Blinker.h"
#include "src/Animation/WalkingDot.h" 
#include <Adafruit_NeoPixel.h>
#include <Adafruit_TinyUSB.h>
#include <MIDI.h>

Adafruit_USBD_MIDI usb_midi;
MIDI_CREATE_INSTANCE(Adafruit_USBD_MIDI, usb_midi, MIDI);
// timer
static uint16_t timer_interval = 100;
static long timer_last = 0;
int timer_count = 0;

/// CLock
bool clock_on = false;
// Colors
int color_r = 255;
int color_g = 255;
int color_b = 255;
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

Animation *animation1;
Animation *animation2;
Animation *animation3;

bool blink_on = false;

uint16_t walkingdot_i = 0;

int rocket_i = 0;

void setup()
{
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

    animation1 = new Blinker(pixels, 0, 1, 2, 1);
  animation2 = new WalkingDot(pixels, 2, 13, 48, 1);
  animation3 = new Blinker(pixels, 15, 16, 4, 1);

  while (!TinyUSBDevice.mounted())
    delay(1);
}

void loop()
{
  MIDI.read();
}

void handleNoteOn(byte channel, byte pitch, byte velocity)
{
  switch (pitch)
  {
  case 61:
    color_r = 255 * velocity / 127;
    break;
  case 62:
    color_g = 255 * velocity / 127;
    break;
  case 63:
    color_b = 255 * velocity / 127;
    break;
  }
  animation1->setColors(color_r, color_g, color_b);
  animation2->setColors(color_r, color_g, color_b);
  animation3->setColors(color_r, color_g, color_b);

  // Log when a note is pressed.
  Serial.print("Note on: channel = ");
  Serial.print(channel);

  Serial.print(" pitch = ");
  Serial.print(pitch);

  Serial.print(" velocity = ");
  Serial.println(velocity);
}

void rocket(int from, int to, int length)
{

  if (rocket_i >= to)
  {
    rocket_i = from;
  }

 //Clear unused LEDS
  for (int i = rocket_i; i >= (rocket_i - length); i--)
  {
    int led = i;
    if (led < from)
    {
      led = to - 1;
    }
    uint16_t divisor = (3 * (rocket_i - i) + 1);
    pixels.setPixelColor(i, pixels.Color(color_r / divisor, color_g / divisor, color_b / divisor));
  }
  pixels.show();
  rocket_i++;
}

void handleClock()
{
  animation1->run();
  animation2->run(); 
  animation3->run();
}

