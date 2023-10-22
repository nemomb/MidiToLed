# 1 "C:\\Users\\manue\\Documents\\Arduino\\Projects\\MidiToLed\\MidiToLed\\MidiToLed.ino"


# 4 "C:\\Users\\manue\\Documents\\Arduino\\Projects\\MidiToLed\\MidiToLed\\MidiToLed.ino" 2
# 5 "C:\\Users\\manue\\Documents\\Arduino\\Projects\\MidiToLed\\MidiToLed\\MidiToLed.ino" 2
# 6 "C:\\Users\\manue\\Documents\\Arduino\\Projects\\MidiToLed\\MidiToLed\\MidiToLed.ino" 2
# 7 "C:\\Users\\manue\\Documents\\Arduino\\Projects\\MidiToLed\\MidiToLed\\MidiToLed.ino" 2
# 8 "C:\\Users\\manue\\Documents\\Arduino\\Projects\\MidiToLed\\MidiToLed\\MidiToLed.ino" 2
# 9 "C:\\Users\\manue\\Documents\\Arduino\\Projects\\MidiToLed\\MidiToLed\\MidiToLed.ino" 2
# 10 "C:\\Users\\manue\\Documents\\Arduino\\Projects\\MidiToLed\\MidiToLed\\MidiToLed.ino" 2

Adafruit_USBD_MIDI usb_midi;
midi::SerialMIDI<Adafruit_USBD_MIDI> serialMIDI(usb_midi); midi::MidiInterface<midi::SerialMIDI<Adafruit_USBD_MIDI>> MIDI((midi::SerialMIDI<Adafruit_USBD_MIDI>&)serialMIDI);;
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
Adafruit_NeoPixel pixels(16, 6, ((1 << 6) | (1 << 4) | (0 << 2) | (2)) /*|< Transmit as G,R,B*/ + 0x0000 /*|< 800 KHz data transmission*/);

Animation *animation1;
Animation *animation2;
Animation *animation3;

bool blink_on = false;

uint16_t walkingdot_i = 0;

int rocket_i = 0;

void setup()
{




  usb_midi.setStringDescriptor("MidiLed");

  MIDI.begin(0);
  MIDI.setHandleNoteOn(handleNoteOn);
  MIDI.setHandleClock(handleClock);

  pixels.begin();
  Serial.begin(115200);

    animation1 = new Blinker(pixels, 0, 1, 2, 1);
  animation2 = new WalkingDot(pixels, 2, 13, 32, 1);
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
