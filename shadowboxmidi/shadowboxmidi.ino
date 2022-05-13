//#include <FastLED.h>
#include <MIDI.h>
#include "shadowBox.h"
#include <vector>

#define LED_BUILTIN 2
#define MIDI_PIN 16 //rx2, receive midi
#define tx2 17 // future midi out/thru 

#define OUT_PIN 21
// #define strip_leds 165
// #define num_leds2 19
static uint8_t  ticks = 0; //midi ticks per quarter note

// Start midi-arduino-library instance on rx2 pin
MIDI_CREATE_INSTANCE(HardwareSerial, Serial2,  MIDI);
std::vector<uint8_t> heldNotes; 
shadowBox sb; 

void setup()
{
  //Pins
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  Serial2.begin(31250, SERIAL_8N1, MIDI_PIN, tx2);

  //MIDI
  MIDI.begin(MIDI_CHANNEL_OMNI);
  MIDI.setHandleNoteOn(handleNoteOn);
  MIDI.setHandleNoteOff(handleNoteOff);
  MIDI.setHandleClock(handleClock);
}

void loop()
{
  //map a method group. add to it on note-on and remove on note-off??
  //methodgroup.run
  for (auto note : heldNotes)
  {
    // Serial.write(" ");
    // Serial.print(note);  
    // Serial.write(" ");
    // sb.routeMIDI(note, 0);

  }
   
  MIDI.read();
  sb.setBPM();    
}

void handleNoteOn(byte channel, byte note, byte velocity)
{
  Serial.write(1);
  Serial.write(note);
  Serial.write(velocity);
  // Serial.println(' ');
  // Serial.write(" holding ");
  // Serial.println(note);
  // heldNotes.push_back(note);
  digitalWrite(LED_BUILTIN, 1);
}

void handleNoteOff(byte channel, byte note, byte velocity)
{
  Serial.write(0);
  Serial.write(note);
  Serial.write(velocity);

  // auto noteHeld = std::find(heldNotes.begin(),heldNotes.end(), note);
  // if (noteHeld != heldNotes.end())
  // {
  //   Serial.println(' ');
  //   Serial.write(" removing ");
  //   Serial.println(note);
  //   heldNotes.erase(noteHeld);
  // }

  digitalWrite(LED_BUILTIN, 0);
  //sb.clearStrip(note);
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
