#include <FastLED.h>
#include <vector>

#define MIDI_PIN 16 //rx2, receive midi
#define tx2 17 // future midi out/thru
#define LED_BUILTIN 2
#define LED_PIN5 23
#define LED_PIN6 22
#define LED_PIN7 21
#define LED_PIN8 19
#define num_leds 165

std::vector<uint8_t> heldNotes; 

CRGB strip5[num_leds];
CRGB strip6[num_leds];
CRGB strip7[num_leds];
CRGB strip8[num_leds];

void setup()
{
  //Pins
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, MIDI_PIN, tx2);
  
  FastLED.addLeds<WS2812B, LED_PIN5, GRB>(strip5, num_leds);
  FastLED.addLeds<WS2812B, LED_PIN6, GRB>(strip6, num_leds);
  FastLED.addLeds<WS2812B, LED_PIN7, GRB>(strip7, num_leds);
  FastLED.addLeds<WS2812B, LED_PIN8, GRB>(strip8, num_leds);
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
    Serial.write(noteOn); 
    Serial.write(note); 
    Serial.write(velocity); 
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
  // strip 5: 49-60
  if (note > 48 && note < 61)
  {
    switch (note)
    {
    case 49:
      fill_solid(strip5, num_leds, CRGB::Blue);
      FastLED.show();
      break;
    
    case 50:
      fill_solid(strip5, num_leds, CRGB::Red);
      FastLED.show();
      break;

    case 51:
      fill_solid(strip5, num_leds, CRGB::Green);
      FastLED.show();
      break;

    case 52:
      fill_solid(strip5, num_leds, CRGB::White);
      FastLED.show();
      break;

    case 53:
      circle(strip5, num_leds);
      break;
    }
  }
 

  // strip 2: 61-72 
  else if (note > 60 && note < 73)
  {
    switch (note)
    {
      case 61:
        fill_solid(strip6, num_leds, CRGB::Blue);
        FastLED.show();
        break;

      case 62:
        fill_solid(strip6, num_leds, CRGB::Red);
        FastLED.show();
        break;

      case 63:
        fill_solid(strip6, num_leds, CRGB::Green);
        FastLED.show();
        break;

      case 64:
        fill_solid(strip6, num_leds, CRGB::White);
        FastLED.show();
        break;

      case 65:
        circle(strip6, num_leds);
        break;
    }
  } 

   // strip 3: 73-84
  else if (note > 72 && note < 84)
  {
    switch (note)
    {
      case 73:
        fill_solid(strip7, num_leds, CRGB::Blue);
        FastLED.show();
        break;

      case 74:
        fill_solid(strip7, num_leds, CRGB::Red);
        FastLED.show();
        break;

      case 75:
        fill_solid(strip7, num_leds, CRGB::Green);
        FastLED.show();
        break;

      case 76:
        fill_solid(strip7, num_leds, CRGB::White);
        FastLED.show();
        break;

      case 77:
        circle(strip7, num_leds);
        break;
    }
  } 
  //strip8: 85-96 
  else if (note > 84 && note < 97)
  {
    switch (note)
    {
      case 85:
        fill_solid(strip8, num_leds, CRGB::Blue);
        FastLED.show();
        break;

      case 86:
        fill_solid(strip8, num_leds, CRGB::Red);
        FastLED.show();
        break;

      case 87:
        fill_solid(strip8, num_leds, CRGB::Green);
        FastLED.show();
        break;

      case 88:
        fill_solid(strip8, num_leds, CRGB::White);
        FastLED.show();
        break;

      case 89:
        circle(strip8, num_leds);
        break;
    }
  } 

}

void clearStrip(int note)
{
      if (note > 48 && note < 61) { fill_solid(strip5, num_leds, CRGB::Black); }//49-60 *strip 5
 else if (note > 60 && note < 73) { fill_solid(strip6, num_leds, CRGB::Black); }//61-72 *strip 6
 else if (note > 72 && note < 85) { fill_solid(strip7, num_leds, CRGB::Black); }//73-84 *strip 7
 else if (note > 84 && note < 96) { fill_solid(strip8, num_leds, CRGB::Black); }//85-96 *strip 8    
    
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
