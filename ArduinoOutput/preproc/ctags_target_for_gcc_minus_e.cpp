# 1 "C:\\Users\\manue\\OneDrive\\Desktop\\tmp\\MidiToLed\\MidiToLed\\MidiToLed.ino"



# 5 "C:\\Users\\manue\\OneDrive\\Desktop\\tmp\\MidiToLed\\MidiToLed\\MidiToLed.ino" 2
# 6 "C:\\Users\\manue\\OneDrive\\Desktop\\tmp\\MidiToLed\\MidiToLed\\MidiToLed.ino" 2
# 7 "C:\\Users\\manue\\OneDrive\\Desktop\\tmp\\MidiToLed\\MidiToLed\\MidiToLed.ino" 2

# 9 "C:\\Users\\manue\\OneDrive\\Desktop\\tmp\\MidiToLed\\MidiToLed\\MidiToLed.ino" 2
# 10 "C:\\Users\\manue\\OneDrive\\Desktop\\tmp\\MidiToLed\\MidiToLed\\MidiToLed.ino" 2
# 11 "C:\\Users\\manue\\OneDrive\\Desktop\\tmp\\MidiToLed\\MidiToLed\\MidiToLed.ino" 2
# 12 "C:\\Users\\manue\\OneDrive\\Desktop\\tmp\\MidiToLed\\MidiToLed\\MidiToLed.ino" 2
# 13 "C:\\Users\\manue\\OneDrive\\Desktop\\tmp\\MidiToLed\\MidiToLed\\MidiToLed.ino" 2
# 14 "C:\\Users\\manue\\OneDrive\\Desktop\\tmp\\MidiToLed\\MidiToLed\\MidiToLed.ino" 2
# 15 "C:\\Users\\manue\\OneDrive\\Desktop\\tmp\\MidiToLed\\MidiToLed\\MidiToLed.ino" 2
# 16 "C:\\Users\\manue\\OneDrive\\Desktop\\tmp\\MidiToLed\\MidiToLed\\MidiToLed.ino" 2
# 17 "C:\\Users\\manue\\OneDrive\\Desktop\\tmp\\MidiToLed\\MidiToLed\\MidiToLed.ino" 2
# 18 "C:\\Users\\manue\\OneDrive\\Desktop\\tmp\\MidiToLed\\MidiToLed\\MidiToLed.ino" 2
# 19 "C:\\Users\\manue\\OneDrive\\Desktop\\tmp\\MidiToLed\\MidiToLed\\MidiToLed.ino" 2
# 20 "C:\\Users\\manue\\OneDrive\\Desktop\\tmp\\MidiToLed\\MidiToLed\\MidiToLed.ino" 2
# 21 "C:\\Users\\manue\\OneDrive\\Desktop\\tmp\\MidiToLed\\MidiToLed\\MidiToLed.ino" 2

//#include "WiFi.h"
//#include "HTTPClient.h"

const char *ssid = "nemo";
const char *password = "Feigelstrasse50";
const char *apiUrl = "your-API-URL";
const int MAX_BRIGHTNESS_VALUE = 4095;

const int NUM_ANIMATIONS = 15;

Adafruit_USBD_MIDI usb_midi;
midi::SerialMIDI<Adafruit_USBD_MIDI> serialMIDI(usb_midi); midi::MidiInterface<midi::SerialMIDI<Adafruit_USBD_MIDI>> MIDI((midi::SerialMIDI<Adafruit_USBD_MIDI>&)serialMIDI);;

float brightnessFactor = 1.0;
int brightness = MAX_BRIGHTNESS_VALUE;
const int chipSelect = 14; // GPIO pin 14 is connected to the SD card CS pin
// Colors
int color_r = 255;
int color_g = 255;
int color_b = 255;
hw_timer_t *timer = 
# 42 "C:\\Users\\manue\\OneDrive\\Desktop\\tmp\\MidiToLed\\MidiToLed\\MidiToLed.ino" 3 4
                   __null
# 42 "C:\\Users\\manue\\OneDrive\\Desktop\\tmp\\MidiToLed\\MidiToLed\\MidiToLed.ino"
                       ;

PixelFacade pixelFacade(240);

std::array<Animation*, NUM_ANIMATIONS> animations = {nullptr};
U8G2_SSD1306_128X32_UNIVISION_F_SW_I2C u8g2((&u8g2_cb_r0), /* clock=*/8, /* data=*/7, /* reset=*/255);

void setup()
{
    Serial.begin(115200);

Serial.println("Start setup");




  u8g2.begin();
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.clearBuffer();
  Serial.println("Start animation");
  for (size_t i = 0; i < NUM_ANIMATIONS; i++)
  {
    animations[i] = new Black(pixelFacade, 0, 0, color_r, color_g, color_b, 0, 0);
  }

   Serial.println("End animation");
  MIDI.begin(0);
  MIDI.setHandleNoteOn(handleNoteOn);
  MIDI.setHandleClock(handleClock);
  while (!TinyUSBDevice.mounted())
  Serial.println("Setup finished");

  brightness = analogRead(5);
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
