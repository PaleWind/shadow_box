#include <FastLED.h>
#include <MIDI.h>
#include "shadowBox.h"

#define LED_BUILTIN 2
#define rx2 16 //receive midi
#define tx2 17
#define pin1 23
#define pin2 22

static uint8_t  ticks = 0; //midi ticks per quarter note

// Start midi-arduino-library instance on rx2 pin
MIDI_CREATE_INSTANCE(HardwareSerial, Serial2,  MIDI);

// Strips setup
#define num_leds1 165
#define num_leds2 14
CRGB strip1 [num_leds1];
CRGB strip2 [num_leds2];
shadowBox sb;

int noteHold = 0;

void setup()
{
  //Pins
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  Serial2.begin(31250, SERIAL_8N1, rx2, tx2);

  //FastLED
  FastLED.addLeds<WS2812B, pin1, GRB>(strip1, num_leds1);
  FastLED.addLeds<WS2812B, pin2, GRB>(strip2, num_leds2);
  FastLED.setBrightness(40);

  //MIDI
  MIDI.begin(MIDI_CHANNEL_OMNI);
  MIDI.setHandleNoteOn(handleNoteOn);
  MIDI.setHandleNoteOff(handleNoteOff);
  MIDI.setHandleClock(handleClock);

}

void loop()
{
  MIDI.read();
  sb.setBPM();
  //call method group. add to it on note-on and remove on note-off
  //methodgroup.run
  if (noteHold > 0)
  {
    Serial.write("holding ");
    sb.circle(strip1, num_leds1);
  }      
}

void handleNoteOn(byte channel, byte note, byte velocity)
{
  noteHold = 1;
  sb.routeMIDI(strip1, num_leds1, channel, note, velocity);
  digitalWrite(LED_BUILTIN, 1);
  Serial.write("ON: ");
  //    Serial.write("channel: "); Serial.write(channel);
  Serial.write(" note: "); Serial.write(note);
  //    Serial.write(" velocity: "); Serial.write(velocity);
    if (note == 'C')
    {
      // while (noteHold > 0)
      // {

      // }
    }
    // else if (velocity > 70)
    // {
    //     fill_solid(strip1, num_leds1, CRGB::Blue);
    // }
    // else if (velocity < 71)
    // {
    //     fill_solid(strip1, num_leds1, CRGB::Green);
    // }
    // else
    // {
    //     fill_solid(strip1, num_leds1, CRGB::Red);
    // }
}

void handleNoteOff(byte channel, byte note, byte velocity)
{
  noteHold = 0;
  digitalWrite(LED_BUILTIN, 0);
    Serial.write("Off: ");
  //    Serial.write("channel: "); Serial.write(channel);
    //Serial.write(" note: " + note + ' ');
  //    Serial.write(" velocity: "); Serial.write(velocity);

  fill_solid(strip1, num_leds1, CRGB::Black);
  fill_solid(strip2, num_leds2, CRGB::Black);
  FastLED.show();
}

void handleClock()
{
  ticks++;
  if (ticks == 24)
  {
    sb.tapInput();
    ticks = 0;
  }
}
