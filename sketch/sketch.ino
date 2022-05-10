#include <FastLED.h>
#include <MIDI.h>
#include "shadowBox.h"
#include <vector>

#define LED_BUILTIN 2
#define MIDI_PIN 16 //rx2, receive midi
#define tx2 17 // future midi out/thru 
#define LED_PIN1 23
#define LED_PIN2 22

static uint8_t  ticks = 0; //midi ticks per quarter note

// Start midi-arduino-library instance on rx2 pin
MIDI_CREATE_INSTANCE(HardwareSerial, Serial2,  MIDI);

// Strips setup
#define num_leds1 165
#define num_leds2 14
CRGB strip1 [num_leds1];
CRGB strip2 [num_leds2];
shadowBox sb;

std::vector<Note> heldNotes;

void setup()
{
  //Pins
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  Serial2.begin(31250, SERIAL_8N1, MIDI_PIN, tx2);

  //FastLED
  FastLED.addLeds<WS2812B, LED_PIN1, GRB>(strip1, num_leds1);
  FastLED.addLeds<WS2812B, LED_PIN2, GRB>(strip2, num_leds2);
  FastLED.setBrightness(40);

  //MIDI
  MIDI.begin(MIDI_CHANNEL_OMNI);
  MIDI.setHandleNoteOn(handleNoteOn);
  MIDI.setHandleNoteOff(handleNoteOff);
  MIDI.setHandleClock(handleClock);

}

void loop()
{
    //map a method group. add to it on note-on and remove on note-off
  //methodgroup.run
  
  for (int i=0;i<heldNotes.size();i++)
  {
    sb.routeMIDI(strip1, num_leds1, heldNotes[i], 0);
  }
    // for_each(heldNotes.begin(), arr1.end(), printx2);
    // sb.routeMIDI(strip1, num_leds1, heldNotes, 0);
 
  MIDI.read();
  sb.setBPM();        
}

void handleNoteOn(byte channel, byte note, byte velocity)
{
  heldNotes.push_back((Note)note);
  //sb.routeMIDI(strip1, num_leds1, channel, note, velocity);
  digitalWrite(LED_BUILTIN, 1);
  Serial.write("ON: ");
   //    Serial.write("channel: "); Serial.write(channel);
  Serial.write(" note: "); Serial.write(note); Serial.write(' ');
  Serial.print(note); Serial.write(' ');
  //    Serial.write(" velocity: "); Serial.write(velocity);

}

void handleNoteOff(byte channel, byte note, byte velocity)
{
  auto noteHeld = std::find(heldNotes.begin(),heldNotes.end(), note);
  if (noteHeld != heldNotes.end()) {
    heldNotes.erase(noteHeld);
  }

  digitalWrite(LED_BUILTIN, 0);
    Serial.write("Off: "); Serial.write(note); Serial.println(' ');
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
