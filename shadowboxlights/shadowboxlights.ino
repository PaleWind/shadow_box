#include <FastLED.h>
#include <vector>
#include <iostream>
#include <map>

#define MIDI_PIN 16 //rx2, receive midi
#define tx2 17 // future midi out/thru
#define LED_BUILTIN 2
#define LED_PIN1 23
#define LED_PIN2 22
#define LED_PIN3 21
#define LED_PIN4 19
#define num_leds 170

std::map<int, int> heldNotes;
int bpm = 70;

CRGB strip1[num_leds];
CRGB strip2[num_leds];
CRGB strip3[num_leds];
CRGB strip4[num_leds];


void setup()
{
  //Pins
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, MIDI_PIN, tx2);
  
  FastLED.addLeds<WS2812B, LED_PIN1, GRB>(strip1, num_leds);
  FastLED.addLeds<WS2812B, LED_PIN2, GRB>(strip2, num_leds);
  FastLED.addLeds<WS2812B, LED_PIN3, GRB>(strip3, num_leds);
  FastLED.addLeds<WS2812B, LED_PIN4, GRB>(strip4, num_leds);
  FastLED.setBrightness(100);
}

void loop()
{
  readNotes();
  for (auto note : heldNotes)
  {
    routeMIDI(note.first, note.second);
  }
}

void readNotes()
{
  if (Serial2.available() > 3)
  {
    int noteOn = Serial2.read();
    int note =   Serial2.read();
    int velocity = Serial2.read();
    bpm = Serial2.read();
    //  Serial.println(noteOn); 
    //  Serial.write(note); 
    //  Serial.write(velocity); 
    if (note <49)
    {
      if (noteOn == 1) 
      {
        digitalWrite(LED_BUILTIN, 1);
        heldNotes.insert(std::make_pair(note, velocity));
      }
      else if (noteOn == 0)
      {
        digitalWrite(LED_BUILTIN, 0);
        heldNotes.erase(note);
        clearStrip(note);
      }
    }
  }
}

void routeMIDI(int note, int velocity)
{
  // strip 1: 1-12
  if (note > -1 && note < 13)
  {
    switch (note)
    {
      case 1:
        fill_solid(strip1, num_leds, CRGB::Blue);
        FastLED.show();
        break;
      
      case 2:
        fill_solid(strip1, num_leds, CRGB::Red);
        FastLED.show();
        break;

      case 3:
        fill_solid(strip1, num_leds, CRGB::Green);
        FastLED.show();
        break;

      case 4:
        //int hue = map(velocity, 0, 127, 0, 255);
        //fill_solid(strip1, num_leds, CHSV(velocity, 255, 100));
        fill_solid(strip1, num_leds, CRGB::White);
        FastLED.show();
        break;

      case 5:
        circle(strip1, velocity);
        break;

      case 6:
        breathe(strip1, velocity);
        break;
        
      case 7:
        bounce(strip1, velocity);
        break;
    }
  }
 
  // strip 2: 13-24 
  else if (note > 12 && note < 25)
  {
    switch (note)
    {
      case 13:
        fill_solid(strip2, num_leds, CRGB::Blue);
        FastLED.show();
        break;

      case 14:
        fill_solid(strip2, num_leds, CRGB::Red);
        FastLED.show();
        break;

      case 15:
        fill_solid(strip2, num_leds, CRGB::Green);
        FastLED.show();
        break;

      case 16:
        //int hue = map(velocity, 0, 127, 0, 255);
        fill_solid(strip2, num_leds, CHSV(velocity, 255, 100));
        break;

      case 17:
        circle(strip2, velocity);
        break;

      case 18:
        breathe(strip2, velocity);
        break;
      
      case 19:
        bounce(strip2, velocity);
        break;
    }
  } 

   // strip 3: 25-36
  else if (note > 24 && note < 37)
  {
    switch (note)
    {
      case 25:
        fill_solid(strip3, num_leds, CRGB::Blue);
        FastLED.show();
        break;

      case 26:
        fill_solid(strip3, num_leds, CRGB::Red);
        FastLED.show();
        break;

      case 27:
        fill_solid(strip3, num_leds, CRGB::Green);
        FastLED.show();
        break;

      case 28:
        //int hue = map(velocity, 0, 127, 0, 255);
        fill_solid(strip3, num_leds, CHSV(velocity, 255, 100));
        break;

      case 29:
        circle(strip3, velocity);
        break;

      case 30:
        breathe(strip3, velocity);
        break;
      
      case 31:
        bounce(strip3, velocity);
        break;
    }
  } 
  //strip4: 37-48 
  else if (note > 36 && note < 49)
  {
    switch (note)
    {
      case 37:
        fill_solid(strip4, num_leds, CRGB::Blue);
        FastLED.show();
        break;

      case 38:
        fill_solid(strip4, num_leds, CRGB::Red);
        FastLED.show();
        break;

      case 39:
        fill_solid(strip4, num_leds, CRGB::Green);
        FastLED.show();
        break;

      case 40:
        //int hue = map(velocity, 0, 127, 0, 255);
        fill_solid(strip4, num_leds, CHSV(velocity, 255, 100));
        break;

      case 41:
        circle(strip4, velocity);
        break;
      
      case 42:
        breathe(strip4, velocity);
        break;
      
      case 43:
        bounce(strip4, velocity);
        break;
    }
  } 

}

void clearStrip(int note)
{
      if (note > -1 && note < 13) { fill_solid(strip1, num_leds, CRGB::Black); }//1-12 *strip 1
 else if (note > 12 && note < 25) { fill_solid(strip2, num_leds, CRGB::Black); }//13-24 *strip 2
 else if (note > 24 && note < 37) { fill_solid(strip3, num_leds, CRGB::Black); }//25-36 *strip 3
 else if (note > 36 && note < 49) { fill_solid(strip4, num_leds, CRGB::Black); }//37-48 *strip 4
//    else if (note > 48 && note < 61) { fill_solid(strip2, num_leds, CRGB::Black); }//49-60 *strip 5
//    else if (note > 60 && note < 73) { fill_solid(strip2, num_leds, CRGB::Black); }//61-72 *strip 6
//    else if (note > 72 && note < 85) { fill_solid(strip2, num_leds, CRGB::Black); }//73-84 *strip 7
//    else if (note > 84 && note < 96) { fill_solid(strip2, num_leds, CRGB::Black); }//85-96 *strip 8    
    
  FastLED.show();
}

//void solidFade(struct CRGB *strip, int fadeTime, const struct CRGB& color)
//{
//  fill_solid(strip2, num_leds, color);
//  if (fadeTime < 127)
//  {
//    fadeToBlackBy(strip, num_leds, fadeTime);
//  }
//  FastLED.show();
//}

void circle(struct CRGB *strip, int color)
{
  uint8_t sawBeat = beat8(bpm);
  //map sinBeat to # of leds
  int wave = map(sawBeat, 0, 255, 0, num_leds - 1);
  int hue = map(color, 0, 127, 0, 255);
  strip[wave] = CHSV(hue, 255, 100);
  FastLED.show();
  fadeToBlackBy(strip, num_leds, 40);
}

void breathe(struct CRGB *strip, int color)
{
  uint8_t beat = beatsin8(bpm / 2);
  float wave = map(beat, 0, 255, 0, 10000);
  float hue = map(color, 0, 127, 0, 255);
  fill_solid(strip, num_leds, CHSV(hue, 255, wave * .01));
  FastLED.show();
}

void bounce(struct CRGB *strip, int color)
{
  int hue = map(color, 0, 127, 0, 255);
  uint8_t sawBeat = beatsin8(70);
  int left = map(sawBeat, 0, 255, 19, 85);
  int right = map(sawBeat, 0, 255, 169, 103);
  strip[left] = CHSV(hue, 255, 100);
  strip[right] = CHSV(hue, 255, 100);
  FastLED.show();
  fadeToBlackBy(strip, num_leds, 50);
}
