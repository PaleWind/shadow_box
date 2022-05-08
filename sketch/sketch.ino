#include <FastLED.h>
#include <MIDI.h>
#include <string>
#include <math.h>
//#include <shadow_box.h>

#define LED_BUILTIN 2
#define rx2 16
#define tx2 17
#define num_leds1 60
#define num_leds2 144
#define pin1 22
#define pin2 23

uint8_t hue = 0;
static uint8_t  ticks = 0;

CRGB strip1 [num_leds1];
CRGB strip2 [num_leds2];

MIDI_CREATE_INSTANCE(HardwareSerial, Serial2,  MIDI);

int bpm;
#define MINIMUM_BPM 400 // Used for debouncing
#define MAXIMUM_BPM 3000 // Used for debouncing
long minimumTapInterval = 60L * 1000 * 1000 * 10 / MAXIMUM_BPM;
long maximumTapInterval = 60L * 1000 * 1000 * 10 / MINIMUM_BPM;

volatile long firstTapTime = 0;
volatile long lastTapTime = 0;
volatile long timesTapped = 0;
long avgTapInterval = (lastTapTime - firstTapTime) / (timesTapped - 1);

//shadowBox sb;

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  Serial2.begin(31250, SERIAL_8N1, rx2, tx2);

  FastLED.addLeds<WS2812B, pin1, GRB>(strip1, num_leds1);
  FastLED.addLeds<WS2812B, pin2, GRB>(strip2, num_leds2);

  FastLED.setBrightness(40);

  MIDI.begin(MIDI_CHANNEL_OMNI);
  MIDI.setHandleNoteOn(handleNoteOn);
  MIDI.setHandleNoteOff(handleNoteOff);
  MIDI.setHandleClock(handleClock);

}

void loop()
{
  MIDI.read();

  long now = micros();
  if (timesTapped > 0 && timesTapped < 3 && (now - lastTapTime) > maximumTapInterval)
  {
    // Single taps, not enough to calculate a BPM -> ignore!
    //    Serial.println("Ignoring lone taps!");
    timesTapped = 0;
  }
  else if (timesTapped >= 3)
  {
    long avgTapInterval = (lastTapTime - firstTapTime) / (timesTapped - 1);
    long temp = (60L * 1000 * 1000 * 10 / avgTapInterval) * 0.1f;
    bpm = std::round(temp);
    timesTapped = 0;
  }
  uint8_t sinBeat = beatsin8(bpm/2, 0, num_leds1 - 1, 0, 0);
  strip1[sinBeat] = sinBeat;
  fadeToBlackBy(strip1, num_leds1, 1);
  //    uint8_t sinBeat2 = beatsin8(30, 0, num_leds2 - 1, 0, 0);
  //    strip2[sinBeat] = sinBeat2;
  //    fadeToBlackBy(strip2, num_leds2, 1);
  //
  //EVERY_N_MILLISECONDS(10) {Serial.println(sinBeat);}
  EVERY_N_MILLISECONDS(1000){Serial.println(bpm);}
  FastLED.show();
  
}

void handleClock()
{
  ticks++;
  if (ticks == 24)
  {
    tapInput();
    ticks = 0;
  }
}

void tapInput() {
  long now = micros();

  if (timesTapped == 0) {
    firstTapTime = now;
  }

  timesTapped++;
  lastTapTime = now;
}


void handleNoteOn(byte channel, byte note, byte velocity)
{
  digitalWrite(LED_BUILTIN, 1);
  //    Serial.write("ON: ");
  //    Serial.write("channel: "); Serial.write(channel);
  //    Serial.write(" note: "); Serial.write(note);
  //    Serial.write(" velocity: "); Serial.write(velocity);

  if (note == 'C')
  {
    fill_solid(strip1, num_leds1, CRGB::Green);
    fill_solid(strip2, num_leds2, CRGB::Green);
  }
  else if (velocity > 70)
  {
    fill_solid(strip1, num_leds1, CRGB::Blue);
  }
  else if (velocity < 71)
  {
    fill_solid(strip2, num_leds2, CRGB::Blue);
  }
  else
  {
    fill_solid(strip1, num_leds1, CRGB::Red);
    fill_solid(strip2, num_leds2, CRGB::Red);
  }
  FastLED.show();
}
void handleNoteOff(byte channel, byte note, byte velocity)
{
  digitalWrite(LED_BUILTIN, 0);
  //    Serial.write("Off: ");
  //    Serial.write("channel: "); Serial.write(channel);
  //    Serial.write(" note: "); Serial.write(note);
  //    Serial.write(" velocity: "); Serial.write(velocity);

  fill_solid(strip1, num_leds1, CRGB::Black);
  fill_solid(strip2, num_leds2, CRGB::Black);
  FastLED.show();
}
