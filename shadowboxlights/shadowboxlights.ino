#include <FastLED.h>
#include <vector>

#define MIDI_PIN 16 //rx2, receive midi
#define tx2 17 // future midi out/thru
#define LED_BUILTIN 2
#define LED_PIN1 23
#define LED_PIN2 22
#define OUT_PIN 21
#define num_leds1 165
#define num_leds2 19

std::vector<uint8_t> heldNotes; 
CRGB strip1[num_leds1];
CRGB strip2[num_leds2];

void setup()
{
  //Pins
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, MIDI_PIN, tx2);
  
  FastLED.addLeds<WS2812B, LED_PIN1, GRB>(strip1, num_leds1);
  FastLED.addLeds<WS2812B, LED_PIN2, GRB>(strip2, num_leds2);
  FastLED.setBrightness(40);
}

void loop()
{
  readNotes();
  for (auto note : heldNotes)
  {
    //  
    routeMIDI(note, 0);
  }
}

void readNotes()
{
  if (Serial2.available() > 2)
  {
    int noteOn = Serial2.read();
    int note =   Serial2.read();
    int velocity = Serial2.read();
    // Serial.println(noteOn); 
    // Serial.write(note); 
    // Serial.write(velocity); 
    if (noteOn == 1) 
    {
      heldNotes.push_back(note);
    }
    else if (noteOn == 0)
    {
      heldNotes.erase(std::remove(heldNotes.begin(), heldNotes.end(), note), heldNotes.end());
      clearStrip(note);
    }
  }
}

void routeMIDI(int note, int velocity)
{
  // strip 1: 1-12
  switch (note)
  {
  case 1:
    fill_solid(strip1, num_leds1, CRGB::Blue);
    FastLED.show();
    break;
  
  case 2:
    fill_solid(strip1, num_leds1, CRGB::Red);
    FastLED.show();
    break;

  case 3:
    fill_solid(strip1, num_leds1, CRGB::Green);
    FastLED.show();
    break;

  case 4:
    fill_solid(strip1, num_leds1, CRGB::White);
    FastLED.show();
    break;

  case 5:
    circle(strip1, num_leds1);
    break;

  // strip 2: 13-24   
  case 13:
    fill_solid(strip2, num_leds2, CRGB::Blue);
    FastLED.show();
    break;

  case 14:
    fill_solid(strip2, num_leds2, CRGB::Red);
    FastLED.show();
    break;

  case 15:
    fill_solid(strip2, num_leds2, CRGB::Green);
    FastLED.show();
    break;

  case 16:
    fill_solid(strip2, num_leds2, CRGB::White);
    FastLED.show();
    break;

  case 17:
    circle(strip2, num_leds2);
    break;

  default:
    break;
  }
}

void clearStrip(int note)
{
      if (note > -1 && note < 13) { fill_solid(strip1, num_leds1, CRGB::Black); }//1-12 *strip 1
 else if (note > 12 && note < 25) { fill_solid(strip2, num_leds2, CRGB::Black); }//13-24 *strip 2
//    else if (note > 24 && note < 37) { fill_solid(strip2, num_leds2, CRGB::Black); }//25-36 *strip 3
//    else if (note > 36 && note < 49) { fill_solid(strip2, num_leds2, CRGB::Black); }//37-48 *strip 4
//    else if (note > 48 && note < 61) { fill_solid(strip2, num_leds2, CRGB::Black); }//49-60 *strip 5
//    else if (note > 60 && note < 73) { fill_solid(strip2, num_leds2, CRGB::Black); }//61-72 *strip 6
//    else if (note > 72 && note < 85) { fill_solid(strip2, num_leds2, CRGB::Black); }//73-84 *strip 7
//    else if (note > 84 && note < 96) { fill_solid(strip2, num_leds2, CRGB::Black); }//85-96 *strip 8    
    
    FastLED.show();
}


void circle(struct CRGB *strip, int numLeds)
{
    //int bpm = BPM > 0 ? BPM / 2 : 30;
    uint8_t sawBeat = beat8(30);
    //map sinBeat to # of leds
    int wave = map(sawBeat, 0, 255, 0, numLeds - 1);
    //Serial.println(wave);
    strip[wave] = CRGB::White;
    //pauls a genius
    FastLED.show();
    fadeToBlackBy(strip, numLeds, 20);
}
