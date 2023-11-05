#define BRIGHTNESS_PIN 5

#define NUMPIXELS 240
#include <Arduino.h>
#include <Wire.h>
#include <U8g2lib.h>

#include "src/Animation/PixelFacade.h"
#include "src/Animation/Animation.h"
#include "src/Animation/Black.h"
#include "src/Animation/Blinker.h"
#include "src/Animation/WalkingDot.h"
#include "src/Animation/Flash.h"
#include "src/Animation/Flicker.h"
#include "src/Animation/Animationconfigurations.h"
#include <Adafruit_NeoPixel.h>
#include <Adafruit_TinyUSB.h>
#include <MIDI.h>
#include <SD.h>
#include <SPI.h>

//#include "WiFi.h"
//#include "HTTPClient.h"

const char *ssid = "nemo";
const char *password = "Feigelstrasse50";
const char *apiUrl = "your-API-URL";
const int MAX_BRIGHTNESS_VALUE = 4095;

const int NUM_ANIMATIONS = 15;

Adafruit_USBD_MIDI usb_midi;
MIDI_CREATE_INSTANCE(Adafruit_USBD_MIDI, usb_midi, MIDI);

float brightnessFactor = 1.0;
int brightness = MAX_BRIGHTNESS_VALUE;
const int chipSelect = 14; // GPIO pin 14 is connected to the SD card CS pin
// Colors
int color_r = 255;
int color_g = 255;
int color_b = 255;
hw_timer_t *timer = NULL;

PixelFacade pixelFacade(NUMPIXELS);

std::array<Animation*, NUM_ANIMATIONS> animations = {nullptr}; 
U8G2_SSD1306_128X32_UNIVISION_F_SW_I2C u8g2(U8G2_R0, /* clock=*/8, /* data=*/7, /* reset=*/U8X8_PIN_NONE);

void setup()
{
    Serial.begin(115200);

Serial.println("Start setup");
#if defined(ARDUINO_ARCH_MBED) && defined(ARDUINO_ARCH_RP2040)
  // Manual begin() is required on core without built-in support for TinyUSB such as mbed rp2040
  TinyUSB_Device_Init(0);
#endif
  u8g2.begin();
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.clearBuffer();
  Serial.println("Start animation");
  for (size_t i = 0; i < NUM_ANIMATIONS; i++)
  {
    animations[i] = new Black(pixelFacade, 0, 0, color_r, color_g, color_b, 0, 0);
  }

   Serial.println("End animation");
  MIDI.begin(MIDI_CHANNEL_OMNI);
  MIDI.setHandleNoteOn(handleNoteOn);
  MIDI.setHandleClock(handleClock);
  while (!TinyUSBDevice.mounted())
  Serial.println("Setup finished");

  brightness = analogRead(BRIGHTNESS_PIN);
  u8g2.setCursor(1, 10);
  u8g2.print("Helligkeit:");
  brightnessFactor = static_cast<float>(brightness) / static_cast<float>(MAX_BRIGHTNESS_VALUE);

  u8g2.print(brightnessFactor);
  u8g2.sendBuffer();
  Serial.println("Setup finished");
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
    color_r = calcColor(velocity);
    setColors();
    break;
  case 62:
    color_g = calcColor(velocity);
    setColors();
    break;
  case 63:
    color_b = calcColor(velocity);
    setColors();
    break;
  default:
    if (animationConfigs.find(pitch) != animationConfigs.end())
    {
      animations[0] = new Black(pixelFacade, 0, TOTAL_LED_COUNT, 0, 0, 0, 0, 0);
      animations[0]->run();
      
      for (int i = 0; i < NUM_ANIMATIONS; i++)
      {
        if (animations[i] != nullptr)
        {
          animations[i] = nullptr;
        }
        if (animationConfigs[pitch].size() > i)
        {
          const AnimationConfig &config = animationConfigs[pitch][i];
          animations[i] = createAnimation(config, pixelFacade);
        }
      }
    }
    Serial.println(ESP.getFreeHeap());
    break;
  }
}

void handleClock()
{
  for (int i = 0; i < NUM_ANIMATIONS; i++)
  {
    if (animations[i] != nullptr)
    {
      animations[i]->run();
    }
  }
  pixelFacade.show();
}

void setColors()
{

  for (int i = 0; i < NUM_ANIMATIONS; i++)
  {
    if (animations[i] != nullptr)
    {
      animations[i]->setColors(color_r, color_g, color_b);
    }
  }
};

int calcColor(int velocity)
{
  return static_cast<int>(255.0 * static_cast<float>(velocity) / 127.0 * brightnessFactor);
}

Animation *createAnimation(const AnimationConfig &config, PixelFacade &pixelFacade)
{
  if (config.className == "Blinker")
  {
    return new Blinker(pixelFacade, config.from, config.to, color_r, color_g, color_b, config.duration, config.specific);
  }
  else if (config.className == "WalkingDot")
  {
    return new WalkingDot(pixelFacade, config.from, config.to, color_r, color_g, color_b, config.duration, config.specific);
  }
  else if (config.className == "Flame")
  {
    return new Flicker(pixelFacade, config.from, config.to, color_r, color_g, color_b, config.duration, config.specific);
  }
  else if (config.className == "Flash")
  {
    return new Flash(pixelFacade, config.from, config.to, color_r, color_g, color_b, config.duration, config.specific);
  }
  else if (config.className == "Black")
  {
    return new Black(pixelFacade, config.from, config.to, color_r, color_g, color_b, config.duration, config.specific);
  }
  return new Black(pixelFacade, 1, 1, color_r, color_g, color_b, 8, 1);
}
