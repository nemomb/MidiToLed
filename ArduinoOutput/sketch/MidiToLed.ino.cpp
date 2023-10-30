#line 1 "C:\\Users\\manue\\OneDrive\\Desktop\\tmp\\MidiToLed\\MidiToLed\\MidiToLed.ino"
#define PIN 6
#define NUMPIXELS 240
#include <Arduino.h>
#include "src/Animation/Animation.h"
#include "src/Animation/None.h"
#include "src/Animation/Blinker.h"
#include "src/Animation/WalkingDot.h"
#include "src/Animation/Flicker.h"
#include "src/Animation/Animationconfigurations.h"
#include <Adafruit_NeoPixel.h>
#include <Adafruit_TinyUSB.h>
#include <MIDI.h>

Adafruit_USBD_MIDI usb_midi;
MIDI_CREATE_INSTANCE(Adafruit_USBD_MIDI, usb_midi, MIDI);

// Colors
int color_r = 255;
int color_g = 255;
int color_b = 255;

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
const int num_animations = 6;
Animation *animations[num_animations] = {nullptr, nullptr, nullptr,nullptr, nullptr, nullptr}; //@Todo Do it right

int rocket_i = 0;
void setup()
{
#if defined(ARDUINO_ARCH_MBED) && defined(ARDUINO_ARCH_RP2040)
  // Manual begin() is required on core without built-in support for TinyUSB such as mbed rp2040
  TinyUSB_Device_Init(0);
#endif

  // usb_midi.setStringDescriptor("MidiLed");
  for (size_t i = 0; i < num_animations; i++)
  {
    animations[i] = new None(pixels, 0, 0, color_r, color_g, color_b, 0,0);
  }
  MIDI.begin(MIDI_CHANNEL_OMNI);
  MIDI.setHandleNoteOn(handleNoteOn);
  MIDI.setHandleClock(handleClock);
  while (!TinyUSBDevice.mounted())
    delay(1);
  pixels.begin();
  Serial.begin(115200);
}

void loop()
{
  MIDI.read();
}

void handleNoteOn(byte channel, byte pitch, byte velocity)
{
  Serial.println(pitch);
  switch (pitch)
  {
  case 61:
    color_r = 255 * velocity / 127;
    setColors();
    break;
  case 62:
    color_g = 255 * velocity / 127;
    setColors();
    break;
  case 63:
    color_b = 255 * velocity / 127;
    setColors();
    break;
  default:
    Serial.println("default");
    if (animationConfigs.find(pitch) != animationConfigs.end())
    {
      for (int i = 0; i < num_animations; i++)
      {
        if (animationConfigs[pitch].size() > i)
        {
          const AnimationConfig &config = animationConfigs[pitch][i];
          /*if (animations[i] != nullptr)
          {
            delete animations[i];
            animations[i] = nullptr;
          }*/
          animations[i] = createAnimation(config, pixels);
        }
      }
    }
    break;
  }
}

void handleClock()
{
  for (int i = 0; i < num_animations; i++)
  {
    if (animations[i] != nullptr)
    {
      animations[i]->run();
    }
  }
}

void setColors()
{
  for (int i = 0; i < num_animations; i++)
  {
    if (animations[i] != nullptr)
    {
      animations[i]->setColors(color_r, color_g, color_b);
    }
  }
  
};

Animation *createAnimation(const AnimationConfig &config, Adafruit_NeoPixel &pixels)
{
  if (config.className == "Blinker")
  {
    return new Blinker(pixels, config.from, config.to, color_r, color_g, color_b ,config.duration, config.specific);
  }
  else if (config.className == "WalkingDot")
  {
    return new WalkingDot(pixels, config.from, config.to, color_r, color_g, color_b ,config.duration, config.specific);
  }
  else if (config.className == "Flame")
  {
    return new Flicker(pixels, config.from, config.to, color_r, color_g, color_b ,config.duration, config.specific);
  }
  return new None(pixels, 1, 4,color_r, color_g, color_b, 8, 1);
}

