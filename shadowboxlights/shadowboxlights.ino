#include <FastLED.h>
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
#define scale 25   

DEFINE_GRADIENT_PALETTE( whiteout_gp ) {
    0, 234,221,145,
    7, 234,221,145,
    7, 234,217,140,
   14, 234,217,140,
   14, 237,215,135,
   21, 237,215,135,
   21, 237,213,132,
   28, 237,213,132,
   28, 237,209,127,
   35, 237,209,127,
   35, 237,207,122,
   42, 237,207,122,
   42, 237,203,119,
   49, 237,203,119,
   49, 237,201,114,
   56, 237,201,114,
   56, 237,197,109,
   63, 237,197,109,
   63, 237,199,114,
   70, 237,199,114,
   70, 237,201,117,
   77, 237,201,117,
   77, 237,203,122,
   85, 237,203,122,
   85, 239,205,127,
   92, 239,205,127,
   92, 239,207,130,
   99, 239,207,130,
   99, 239,209,135,
  106, 239,209,135,
  106, 239,211,140,
  113, 239,211,140,
  113, 242,213,144,
  120, 242,213,144,
  120, 242,215,149,
  127, 242,215,149,
  127, 242,217,155,
  134, 242,217,155,
  134, 242,219,158,
  141, 242,219,158,
  141, 244,221,164,
  148, 244,221,164,
  148, 244,223,170,
  155, 244,223,170,
  155, 244,225,174,
  162, 244,225,174,
  162, 244,227,180,
  170, 244,227,180,
  170, 247,229,186,
  177, 247,229,186,
  177, 247,231,190,
  184, 247,231,190,
  184, 247,233,197,
  191, 247,233,197,
  191, 247,235,203,
  198, 247,235,203,
  198, 249,237,207,
  205, 249,237,207,
  205, 249,239,214,
  212, 249,239,214,
  212, 249,241,221,
  219, 249,241,221,
  219, 249,244,228,
  226, 249,244,228,
  226, 252,246,233,
  233, 252,246,233,
  233, 252,248,240,
  240, 252,248,240,
  240, 252,250,247,
  247, 252,250,247,
  247, 255,255,255,
  255, 255,255,255};
CRGBPalette16 WhiteoutPalette = whiteout_gp;
DEFINE_GRADIENT_PALETTE( rgi_15_gp ) {
    0,   4,  1, 31,
   31,  55,  1, 16,
   63, 197,  3,  7,
   95,  59,  2, 17,
  127,   6,  2, 34,
  159,  39,  6, 33,
  191, 112, 13, 32,
  223,  56,  9, 35,
  255,  22,  6, 38};
CRGBPalette16 RgiPalette = rgi_15_gp;
DEFINE_GRADIENT_PALETTE( Plasma ) {
    0,   4,  2,  9,
   58,  16,  0, 47,
  122,  24,  0, 16,
  158, 144,  9,  1,
  183, 179, 45,  1,
  219, 220,114,  2,
  255, 234,137,  1};
CRGBPalette16 PlasmaPalette = Plasma;
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
DEFINE_GRADIENT_PALETTE( Sunset_Real_gp ) {
    0, 120,  0,  0,
   22, 179, 22,  0,
   51, 255,104,  0,
   85, 167, 22, 18,
  135, 100,  0,103,
  198,  16,  0,130,
  255,   0,  0,160};
CRGBPalette16 sunsetPalette = Sunset_Real_gp;
DEFINE_GRADIENT_PALETTE( rasta_gp ) {
    0, 0, 255, 0,
   40, 255, 255, 0,
   80, 255,0, 0,
   120,0, 255, 0,
   160,255, 255, 0,
   200,255,0, 0,
   255,255, 100, 0,};
CRGBPalette16 rastaPalette = rasta_gp;

const CRGBPalette16 palettes[] = {
    rainbowPalette,
    PlasmaPalette,
    sunsetPalette,
    rastaPalette,
    LavaColors_p,
    OceanColors_p,
    ForestColors_p,
    RainbowStripeColors_p,
    CloudColors_p,
    PartyColors_p,
    RgiPalette,
    WhiteoutPalette
  };
int paletteSize = sizeof(palettes)/sizeof(palettes[0]);
CRGBPalette16 currentPalette = LavaColors_p;

std::map<int, int> heldNotes;
CRGB strips[4][num_leds];
int bpm = 70;

void setup()
{
  //Pins
  pinMode(LED_BUILTIN, OUTPUT);
  //Serial.begin(115200);
  Serial2.begin(230400, SERIAL_8N1, MIDI_PIN, tx2);
  FastLED.addLeds<WS2812B, LED_PIN1, GRB>(strips[0], num_leds);
  FastLED.addLeds<WS2812B, LED_PIN2, GRB>(strips[1], num_leds);
  FastLED.addLeds<WS2812B, LED_PIN3, GRB>(strips[2], num_leds);
  FastLED.addLeds<WS2812B, LED_PIN4, GRB>(strips[3], num_leds);
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
    int bpmRead = Serial2.read();
    if (bpmRead != bpm){bpm = bpmRead;}
    //  Serial.println(noteOn); 
    //  Serial.write(note); 
    //  Serial.write(velocity); 
    if (note > 0 && note < 61)
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

//******single strip effects********
void circle(int strip, int velocity)
{
  uint8_t sawBeat = beat8(bpm);
  int wave1 = map(sawBeat, 0, 255, 0, num_leds - 1);
  //int wave2 = map(sawBeat, 0, 255, num_leds - 1, 0);
  auto hue = ColorFromPalette(rainbowPalette, map(velocity, 0, 127, 0, 255), 250, NOBLEND);
  strips[strip][wave1] = hue;
  //strips[strip][wave2] = hue;
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
  uint8_t sawBeat = beatsin8(bpm);
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
  int palette = map(velocity, 1, 127, 0, paletteSize);
  currentPalette = palettes[palette];
  for(int i = 0; i < num_leds; i++) {                                       // Just ONE loop to fill up the LED array as all of the pixels change.
    uint8_t index = inoise8(i*scale, millis()/5+i*scale);                   // Get a value from the noise function. I'm using both x and y axis.
    strips[strip][i] = ColorFromPalette(currentPalette, index, 255, LINEARBLEND);    // With that value, look up the 8 bit colour palette value and assign it to the current LED.
  }
  FastLED.show();
}

void stripes(int strip, int velocity)
{
  uint8_t beat = beatsin8( bpm, 0, 255);
  int palette = map(velocity, 1, 127, 0, paletteSize);
  for( int i = 0; i < num_leds; i++) {
    strips[strip][i] = ColorFromPalette(palettes[palette], i*2, beat+(i*10));
  }
  FastLED.show();
}

void juggle(int strip, int velocity) 
 {
  // eight colored dots, weaving in and out of sync with each other
  fadeToBlackBy( strips[strip], num_leds, 20);
  int palette = map(velocity, 1, 127, 0, paletteSize);
  uint8_t dothue = 0;
  for( int i = 0; i < 8; i++)
  {
    strips[strip][beatsin16( i+7, 0, num_leds-1 )] |= ColorFromPalette(palettes[palette], dothue, 250);
    dothue += 26;
  }  
  FastLED.show();
 }

//*********globals*******
void fillGlobal(int velocity)
{
  int index = map(velocity, 0, 127, 0, 255);
  CRGB color = ColorFromPalette(rainbowPalette, map(velocity, 0, 127, 0, 255), 250, NOBLEND);
  fill_solid(strips[0], num_leds, color);
  fill_solid(strips[1], num_leds, color);
  fill_solid(strips[2], num_leds, color);
  fill_solid(strips[3], num_leds, color);
  FastLED.show();
}

void whiteOut(int velocity)
{
  float wave = beatsin8(bpm / 16, 44, 200);
  float wave2 = beatsin8(bpm / 8, 44, 200);
  fill_palette(strips[0], num_leds, wave2, 0, WhiteoutPalette, wave, NOBLEND);
  fill_palette(strips[1], num_leds, wave2, 0, WhiteoutPalette, wave, NOBLEND);
  fill_palette(strips[2], num_leds, wave2, 0, WhiteoutPalette, wave, NOBLEND);
  fill_palette(strips[3], num_leds, wave2, 0, WhiteoutPalette, wave, NOBLEND);
  FastLED.show(); 
}

void circleGlobal(int velocity)
{
  uint8_t sawBeat = beat8(bpm);
  int wave = map(sawBeat, 0, 255, 0, num_leds - 1);
  CRGB color = ColorFromPalette(rainbowPalette, map(velocity, 0, 127, 0, 255), 250, NOBLEND);
  strips[0][wave] = color;
  strips[1][wave] = color;
  strips[2][wave] = color;
  strips[3][wave] = color;
  FastLED.show();
  clearStrips();
}

void breatheGlobal(int velocity)
{
  float wave = map(beatsin8(bpm), 0, 255, 0, 150);
  int index = map(velocity, 0, 127, 0, 255);
  fill_palette(strips[0], num_leds, index, 0, rainbowPalette, wave, NOBLEND);
  fill_palette(strips[1], num_leds, index, 0, rainbowPalette, wave, NOBLEND);
  fill_palette(strips[2], num_leds, index, 0, rainbowPalette, wave, NOBLEND);
  fill_palette(strips[3], num_leds, index, 0, rainbowPalette, wave, NOBLEND);
  FastLED.show();
}


void bounceGlobal(int velocity)
{
  uint8_t sawBeat = beatsin8(bpm);
  CRGB color = ColorFromPalette(rainbowPalette, map(velocity, 0, 127, 0, 255), 250, NOBLEND);
  int left = map(sawBeat, 0, 255, 19, 85);
  int right = map(sawBeat, 0, 255, 169, 103);
  for (auto strip : strips)
  {
    strip[left] = color;
    strip[right] = color;
  }
  FastLED.show();
  clearStrips();
}

void crossGlobal(int velocity)
{
  uint8_t wave1 = beatsin8(bpm / 2, 0, 169, 0, 0);
  uint8_t wave2 = beatsin8(bpm / 2, 0, 169, 0, 84);
  CRGB c = ColorFromPalette(rainbowPalette, map(velocity, 0, 127, 0, 255), 250, NOBLEND);
  for (auto strip : strips)
  {
    strip[wave1] = c;
    strip[wave2] = c;
  }
  FastLED.show();
  clearStrips();
}

void makeNoiseGlobal(int velocity)
{
  int palette = map(velocity, 1, 127, 0, paletteSize);
  currentPalette = palettes[palette];
  for(int i = 0; i < num_leds; i++) 
  {    
    int index = inoise8(i*scale, millis()/5+i*scale); 
    auto color = ColorFromPalette(currentPalette, index, 255, LINEARBLEND);                                  
    strips[0][i] = color; 
    strips[1][i] = color;
    strips[2][i] = color;
    strips[3][i] = color;  
  }
  FastLED.show();
}

void stripesGlobal(int velocity)
{
  uint8_t beat = beatsin8( bpm, 0, 255);
  int palette = map(velocity, 1, 127, 0, paletteSize);
  for( int i = 0; i < num_leds; i++) 
  {
    int index = inoise8(i*scale, millis()/5+i*scale);
    auto color = ColorFromPalette(palettes[palette], index, beat+(i*10));
    strips[0][i] = color; 
    strips[1][i] = color;
    strips[2][i] = color;
    strips[3][i] = color; 
  } 
  FastLED.show();
}

void juggleGlobal(int velocity) 
 {
  // eight colored dots, weaving in and out of sync with each other
  clearStrips();
  int palette = map(velocity, 1, 127, 0, paletteSize);
  uint8_t dothue = 0;
  for (auto strip : strips)
  {
    for( int i = 0; i < 8; i++)
    {
      strip[beatsin16( i+7, 0, num_leds-1 )] |= ColorFromPalette(palettes[palette], dothue, 250);
      dothue += 26;
    }
  }
    
  FastLED.show();
 }



//******beware******
void clearStrip(int note)
{
      if (note >  0 && note < 13) { fill_solid(strips[0], num_leds, CRGB::Black); }// 1-12 strip 1
 else if (note > 12 && note < 25) { fill_solid(strips[1], num_leds, CRGB::Black); }//13-24 strip 2
 else if (note > 24 && note < 37) { fill_solid(strips[2], num_leds, CRGB::Black); }//25-36 strip 3
 else if (note > 36 && note < 49) { fill_solid(strips[3], num_leds, CRGB::Black); }//37-48 strip 4
 else if (note > 48 && note < 61) { clearStrips(); }//49-60 all strips
  FastLED.show();
}

void clearStrips()
{
  fill_solid(strips[0], num_leds, CRGB::Black); 
  fill_solid(strips[1], num_leds, CRGB::Black); 
  fill_solid(strips[2], num_leds, CRGB::Black); 
  fill_solid(strips[3], num_leds, CRGB::Black); 
  FastLED.show();
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
        makeNoise(0, velocity);
        break;
      
      case 8:
        stripes(0, velocity);
        break;

      case 9:
        juggle(0, velocity);
        break;

      case 10:

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
        makeNoise(1, velocity);
        break;

      case 20:
        stripes(1, velocity);
        break;

      case 21:
        juggle(1, velocity);
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
        makeNoise(2, velocity);
        break;

      case 32:
        stripes(2, velocity);
        break;

      case 33:
        juggle(2, velocity);
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
        makeNoise(3, velocity);
        break;

      case 44:
        stripes(3, velocity);
        break;

      case 45:
        juggle(3, velocity);
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
        whiteOut(velocity);
        break;

      case 51:
        circleGlobal(velocity);
        break;

      case 52:
        breatheGlobal(velocity);
        break;

      case 53:
        bounceGlobal(velocity);
        break;

      case 54:
        crossGlobal(velocity);
        break;

      case 55:
        makeNoiseGlobal(velocity);
        break;
      
      case 56:
        stripesGlobal(velocity);
        break;

      case 57:
        juggleGlobal(velocity);
        break;
    }
  }
}
