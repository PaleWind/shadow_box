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

DEFINE_GRADIENT_PALETTE( rainbow_gp ) {
    0, 126,  1,142,
   25, 171,  1, 26,
   48, 224,  9,  1,
   71, 237,138,  1,
   94,  52,173,  1,
  117,   1,201,  1,
  140,   1,211, 54,
  163,   1,124,168,
  186,   1,  8,149,
  209,  12,  1,151,
  232,  12,  1,151,
  254, 171,  1,190,
  255, 255, 255, 255};
CRGBPalette16 rainbowPalette = rainbow_gp;

DEFINE_GRADIENT_PALETTE( fire_gp ) {
    0,   0,  0,  0,
   99, 227,  1,  1,
  130, 249,199, 95,
  155, 227,  1,  1,
  255,   0,  0,  0};
CRGBPalette16 firePalette = fire_gp;

std::map<int, int> heldNotes;
int bpm = 70;

CRGB strips[4][num_leds];

void setup()
{
  //Pins
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, MIDI_PIN, tx2);
  FastLED.addLeds<WS2812B, LED_PIN1, GRB>(strips[0], num_leds);
  FastLED.addLeds<WS2812B, LED_PIN2, GRB>(strips[1], num_leds);
  FastLED.addLeds<WS2812B, LED_PIN3, GRB>(strips[2], num_leds);
  FastLED.addLeds<WS2812B, LED_PIN4, GRB>(strips[3], num_leds);

  // FastLED.addLeds<WS2812B, LED_PIN1, GRB>(strip1, num_leds);
  // FastLED.addLeds<WS2812B, LED_PIN2, GRB>(strip2, num_leds);
  // FastLED.addLeds<WS2812B, LED_PIN3, GRB>(strip3, num_leds);
  // FastLED.addLeds<WS2812B, LED_PIN4, GRB>(strip4, num_leds);
  FastLED.setBrightness(200);
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
    bpm = Serial2.read() * 2;
    //  Serial.println(noteOn); 
    //  Serial.write(note); 
    //  Serial.write(velocity); 
    if (note < 61)
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
        fill_palette(strips[0], num_leds, map(velocity, 0, 127, 0, 255), 0, rainbowPalette, 250, NOBLEND);
        FastLED.show();
        break;
      
      case 2:
        fill_solid(strips[0], num_leds, CRGB::White);
        FastLED.show(); 
        break;

      case 3:
        circle(0, velocity);
        break;

      case 4:
        breathe(0, velocity);
        break;

      case 5:
        bounce(0, velocity);
        break;

      case 6:
        cross(0, velocity);
        break;
        
      case 7:

        break;
      
      case 8:

        break;
    }
  }
 
  // strip 2: 13-24 
  else if (note > 12 && note < 25)
  {
    switch (note)
    {
      case 13:
        fill_palette(strips[1], num_leds, map(velocity, 0, 127, 0, 255), 0, rainbowPalette, 250, NOBLEND);
        FastLED.show();
        break;

      case 14:
        fill_solid(strips[1], num_leds, CRGB::White);
        FastLED.show(); 
        break;

      case 15:
        circle(1, velocity);
        break;

      case 16:
        breathe(1, velocity);
        break;

      case 17:
        bounce(1, velocity);
        break;

      case 18:
        cross(1, velocity);
        break;
      
      case 19:
        fill_noise16(strips[1], num_leds, 1, 0, 100, 1, 1, velocity, millis() / bpm, 5);
        FastLED.show(); 
        break;
    }
  } 

  //  // strip 3: 25-36
  else if (note > 24 && note < 37)
  {
    switch (note)
    {
      case 25:
        fill_palette(strips[2], num_leds, map(velocity, 0, 127, 0, 255), 0, rainbowPalette, 250, NOBLEND);
        FastLED.show();
        break;

      case 26:
        fill_solid(strips[2], num_leds, CRGB::White);
        FastLED.show(); 
        break;

      case 27:
        circle(2, velocity);
        break;

      case 28:
        breathe(2, velocity);
        break;

      case 29:
        bounce(2, velocity);
        break;

      case 30:
        cross(2, velocity);
        break;
      
      case 31:

        break;
    }
  } 

  // //strip4: 37-48 
  else if (note > 36 && note < 49)
  {
    switch (note)
    {
      case 37:
        fill_palette(strips[3], num_leds, map(velocity, 0, 127, 0, 255), 0, rainbowPalette, 250, NOBLEND);
        FastLED.show();
        break;

      case 38:
        fill_solid(strips[3], num_leds, CRGB::White);
        FastLED.show();
        break;

      case 39:
        circle(3, velocity);
        break;

      case 40:
        breathe(3, velocity);
        break;

      case 41:
        bounce(3, velocity);
        break;
      
      case 42:
        cross(3, velocity);
        break;
      
      case 43:

        break;
    }
  } 

  // Global: 49-60
  if (note > 48 && note < 61)
  {
    switch (note)
    {
      case 49:
        fillGlobal(velocity);
        break;
      
      case 50:
        circleGlobal(velocity);
        break;

      case 51:
        breatheGlobal(velocity);
        break;

       case 52:
        bounceGlobal(velocity);
        break;

       case 53:
        crossGlobal(velocity);
        break;

      // case 54:

      //   break;
      
      // case 55:

      //   break;
    }
  }
}

void clearStrip(int note)
{
      if (note > -1 && note < 13) { fill_solid(strips[0], num_leds, CRGB::Black); }//1-12 *strip 1
 else if (note > 12 && note < 25) { fill_solid(strips[1], num_leds, CRGB::Black); }//13-24 *strip 2
 else if (note > 24 && note < 37) { fill_solid(strips[2], num_leds, CRGB::Black); }//25-36 *strip 3
 else if (note > 36 && note < 49) { fill_solid(strips[3], num_leds, CRGB::Black); }//37-48 *strip 4
 else if (note > 48 && note < 61) { clearStrips(); }//49-60 *strip 5

  FastLED.show();
}

void clearStrips()
{
  for (auto strip : strips)
  {
    fill_solid(strip, num_leds, CRGB::Black); 
  }
  FastLED.show();
}

//******single strip effects********
void circle(int strip, int velocity)
{
  uint8_t sawBeat = beat8(bpm);
  int wave = map(sawBeat, 0, 255, 0, num_leds - 1);
  int color = map(velocity, 0, 127, 0, 255);
  strips[strip][wave] = ColorFromPalette(rainbowPalette, color, 250, NOBLEND);
  FastLED.show();
  fadeToBlackBy(strips[strip], num_leds, 10);
}

void breathe(int strip, int velocity)
{
  uint8_t beat = beatsin8(bpm);
  float wave = map(beat, 0, 255, 0, 200);
  fill_palette(strips[strip], num_leds, map(velocity, 0, 127, 0, 255), 0, rainbowPalette, wave, NOBLEND);
  FastLED.show();
}

void bounce(int strip, int velocity)
{
  uint8_t sawBeat = beatsin8(70);
  CRGB c = ColorFromPalette(rainbowPalette, map(velocity, 0, 127, 0, 255), 250, NOBLEND);
  int left = map(sawBeat, 0, 255, 19, 85);
  int right = map(sawBeat, 0, 255, 169, 103);
  strips[strip][left] = c;
  strips[strip][right] = c;
  FastLED.show();
  fadeToBlackBy(strips[strip], num_leds, 30);
}

void cross(int strip, int velocity)
{
  uint8_t wave1 = beatsin8(bpm / 2, 0, 169, 0, 0);
  uint8_t wave2 = beatsin8(bpm / 2, 0, 169, 0, 85);
  CRGB c = ColorFromPalette(rainbowPalette, map(velocity, 0, 127, 0, 255), 250, NOBLEND);
  strips[strip][wave1] = c;
  strips[strip][wave2] = c;
  FastLED.show();
  fadeToBlackBy(strips[strip], num_leds, 30);
}

void makeNoise(int strip, int velocity)
{
  int wave = beatsin8(bpm / 4, velocity/2, velocity);
  for (int led=0; led<num_leds; led++)
  {
    uint8_t noise = inoise8(led * wave, 0, millis() / bpm);
    strips[strip][led] = ColorFromPalette(rainbowPalette, noise, 250, NOBLEND);
  }
}

//*********globals*******
void fillGlobal(int velocity)
{
  for (auto strip : strips)
  {
    fill_palette(strip, num_leds, map(velocity, 0, 127, 0, 255), 0, rainbowPalette, 250, NOBLEND);
  }
  FastLED.show();
}

void circleGlobal(int velocity)
{
  uint8_t sawBeat = beat8(bpm);
  int wave = map(sawBeat, 0, 255, 0, num_leds - 1);
  int color = map(velocity, 0, 127, 0, 255);
  for (auto strip : strips)
  {
    strip[wave] = ColorFromPalette(rainbowPalette, color, 250, NOBLEND);
  }
  FastLED.show();
  for (auto strip : strips)
  {
    fadeToBlackBy(strip, num_leds, 10);
  }
}

void breatheGlobal(int velocity)
{
  uint8_t beat = beatsin8(bpm);
  float wave = map(beat, 0, 255, 0, 150);
  for (auto strip : strips)
  {
    fill_palette(strip, num_leds, map(velocity, 0, 127, 0, 255), 0, rainbowPalette, wave, NOBLEND);
  }
  FastLED.show();
}

void bounceGlobal(int velocity)
{
  uint8_t sawBeat = beatsin8(bpm);
  CRGB c = ColorFromPalette(rainbowPalette, map(velocity, 0, 127, 0, 255), 250, NOBLEND);
  int left = map(sawBeat, 0, 255, 19, 85);
  int right = map(sawBeat, 0, 255, 169, 103);
  for (auto strip : strips)
  {
    strip[left] = c;
    strip[right] = c;
  }
  FastLED.show();
  for (auto strip : strips)
  {
    fadeToBlackBy(strip, num_leds, 30);
  }
}

void crossGlobal(int velocity)
{
  uint8_t wave1 = beatsin8(bpm / 2, 0, 169, 0, 0);
  uint8_t wave2 = beatsin8(bpm / 2, 0, 169, 0, 85);
  CRGB c = ColorFromPalette(rainbowPalette, map(velocity, 0, 127, 0, 255), 250, NOBLEND);
  for (auto strip : strips)
  {
    strip[wave1] = c;
    strip[wave2] = c;
  }
  FastLED.show();
  for (auto strip : strips)
  {
    fadeToBlackBy(strip, num_leds, 30);
  }
}
