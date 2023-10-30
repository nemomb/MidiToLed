# 1 "C:\\Users\\manue\\OneDrive\\Desktop\\tmp\\MidiToLed\\MidiToLed\\MidiToLed.ino"


# 4 "C:\\Users\\manue\\OneDrive\\Desktop\\tmp\\MidiToLed\\MidiToLed\\MidiToLed.ino" 2
# 5 "C:\\Users\\manue\\OneDrive\\Desktop\\tmp\\MidiToLed\\MidiToLed\\MidiToLed.ino" 2
# 6 "C:\\Users\\manue\\OneDrive\\Desktop\\tmp\\MidiToLed\\MidiToLed\\MidiToLed.ino" 2
# 7 "C:\\Users\\manue\\OneDrive\\Desktop\\tmp\\MidiToLed\\MidiToLed\\MidiToLed.ino" 2
# 8 "C:\\Users\\manue\\OneDrive\\Desktop\\tmp\\MidiToLed\\MidiToLed\\MidiToLed.ino" 2
# 9 "C:\\Users\\manue\\OneDrive\\Desktop\\tmp\\MidiToLed\\MidiToLed\\MidiToLed.ino" 2
# 10 "C:\\Users\\manue\\OneDrive\\Desktop\\tmp\\MidiToLed\\MidiToLed\\MidiToLed.ino" 2
# 11 "C:\\Users\\manue\\OneDrive\\Desktop\\tmp\\MidiToLed\\MidiToLed\\MidiToLed.ino" 2
# 12 "C:\\Users\\manue\\OneDrive\\Desktop\\tmp\\MidiToLed\\MidiToLed\\MidiToLed.ino" 2
# 13 "C:\\Users\\manue\\OneDrive\\Desktop\\tmp\\MidiToLed\\MidiToLed\\MidiToLed.ino" 2

Adafruit_USBD_MIDI usb_midi;
midi::SerialMIDI<Adafruit_USBD_MIDI> serialMIDI(usb_midi); midi::MidiInterface<midi::SerialMIDI<Adafruit_USBD_MIDI>> MIDI((midi::SerialMIDI<Adafruit_USBD_MIDI>&)serialMIDI);;

// Colors
int color_r = 255;
int color_g = 255;
int color_b = 255;

Adafruit_NeoPixel pixels(240, 6, ((1 << 6) | (1 << 4) | (0 << 2) | (2)) /*|< Transmit as G,R,B*/ + 0x0000 /*|< 800 KHz data transmission*/);
const int num_animations = 6;
Animation *animations[num_animations] = {nullptr, nullptr, nullptr,nullptr, nullptr, nullptr}; //@Todo Do it right

int rocket_i = 0;
void setup()
{





  // usb_midi.setStringDescriptor("MidiLed");
  for (size_t i = 0; i < num_animations; i++)
  {
    animations[i] = new None(pixels, 0, 0, color_r, color_g, color_b, 0,0);
  }
  MIDI.begin(0);
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
# 84 "C:\\Users\\manue\\OneDrive\\Desktop\\tmp\\MidiToLed\\MidiToLed\\MidiToLed.ino"
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
