#include <FastLED.h>
#include <iostream>
#include <map>

#define MIDI_PIN 16 //rx2, receive midi
#define tx2 17 // future midi out/thru
#define LED_BUILTIN 2
#define LED_PIN5 23
#define LED_PIN6 22
#define LED_PIN7 21
#define LED_PIN8 19
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
  247, 171,  1,190,
  248,255,255,255,
  255, 255, 255, 255};
CRGBPalette16 rainbowPalette = rainbow_gp;
DEFINE_GRADIENT_PALETTE( Sunset_Real_gp ) {
    0, 120,  0,  0,
   22, 179, 22,  0,
   51, 255,104,  0,
   85, 167, 22, 18,
  135, 100,  0,103,
  198,  16,  0,130,
  250,   0,  0,160};
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

DEFINE_GRADIENT_PALETTE( space_gp ) {
    0,  75,  1,221,
   30, 252, 73,255,
   48, 169,  0,242,
  119,   0,149,242,
  170,  43,  0,242,
  206, 252, 73,255,
  232,  78, 12,214,
  255,   0,149,242};
CRGBPalette16 spacePalette = space_gp;

DEFINE_GRADIENT_PALETTE( beach_gp ) {
    0,   2,184,188,
   33,  56, 27,162,
   66,  56, 27,162,
  122, 255,255, 45,
  150, 227, 65,  6,
  201,  67, 13, 27,
  255,  16,  1, 53};
CRGBPalette16 beachPalette = beach_gp;

DEFINE_GRADIENT_PALETTE( angelcompassion_gp ) {
    0, 121,108, 63,
   81,  48, 36, 42,
  170,   1,  4, 17,
  255,  19, 31, 50};
CRGBPalette16 compassionPalette = angelcompassion_gp;

DEFINE_GRADIENT_PALETTE( angelrepose_gp ) {
    0, 167, 57, 53,
  255,  12, 90, 99};
CRGBPalette16 reposePalette = angelrepose_gp;

DEFINE_GRADIENT_PALETTE( autumnasrai_gp ) {
    0, 148,111,115,
  127, 140,133,108,
  255,  73, 73, 82};
CRGBPalette16 autumnPalette = autumnasrai_gp;

DEFINE_GRADIENT_PALETTE( beautifuldreams_gp ) {
    0,  27, 27, 49,
   51, 126,104,138,
   76,  64, 85,133,
  127,   4, 16, 78,
  178,  64, 85,133,
  204, 126,104,138,
  255,  27, 27, 49};
CRGBPalette16 beautifulDreamsPalette = beautifuldreams_gp;

DEFINE_GRADIENT_PALETTE( catfairy_gp ) {
    0,  74,124, 85,
   76, 152,128, 44,
  127, 144, 97, 96,
  178, 100, 72,102,
  232,  78, 90,122,
  255,  78, 90,122};
CRGBPalette16 catfairyPalette = catfairy_gp;

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
    spacePalette,
    beachPalette,
    compassionPalette,
    reposePalette,
    autumnPalette,
    beautifulDreamsPalette,
    catfairyPalette,
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
  FastLED.addLeds<WS2812B, LED_PIN5, GRB>(strips[0], num_leds);
  FastLED.addLeds<WS2812B, LED_PIN6, GRB>(strips[1], num_leds);
  FastLED.addLeds<WS2812B, LED_PIN7, GRB>(strips[2], num_leds);
  FastLED.addLeds<WS2812B, LED_PIN8, GRB>(strips[3], num_leds);
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
    uint8_t noteOn = Serial2.read();
    uint8_t note =   Serial2.read();
    uint8_t velocity = Serial2.read();
    uint8_t bpmRead = Serial2.read();
    if (bpmRead != bpm){bpm = bpmRead;}
    //  Serial.println(noteOn); 
    //  Serial.write(note); 
    //  Serial.write(velocity); 
    if (note > 60 && note < 121)
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
  uint8_t wave1 = map(sawBeat, 0, 255, 0, num_leds - 1);
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
  uint8_t wave = map(beat, 0, 255, 0, 200);
  fill_palette(strips[strip], num_leds, map(velocity, 0, 127, 0, 255), 0, rainbowPalette, wave, NOBLEND);
  FastLED.show();
}

void bounce(int strip, int velocity)
{
  uint8_t left = beatsin8(bpm, 19, 84, 0, 0);
  CRGB c = ColorFromPalette(rainbowPalette, map(velocity, 0, 127, 0, 255), 250, NOBLEND);
  //int left = map(sawBeat, 0, 67, 19, 84);
  uint8_t right = map(left, 19, 84, 169, 103);
  strips[strip][left] = c;
  strips[strip][right] = c;
  FastLED.show();
  fadeToBlackBy(strips[strip], num_leds, 20);
}

void cross(int strip, int velocity)
{
  uint8_t beats = bpm / 2;
  uint8_t wave1 = beatsin8(beats, 0, 169, 0, 0);
  uint8_t wave2 = beatsin8(beats, 0, 169, 0, 85);
  CRGB c = ColorFromPalette(rainbowPalette, map(velocity, 0, 127, 0, 255), 250, NOBLEND);
  strips[strip][wave1] = c;
  strips[strip][wave2] = c;
  FastLED.show();
  fadeToBlackBy(strips[strip], num_leds, 20);
}

void makeNoise(int strip, int velocity)
{
  uint8_t palette = map(velocity, 1, 127, 0, paletteSize);
  currentPalette = palettes[palette];
  for(uint8_t i = 0; i < num_leds; i++) {                                       // Just ONE loop to fill up the LED array as all of the pixels change.
      uint8_t index = inoise8(i*scale, millis()/5+i*scale);                   // Get a value from the noise function. I'm using both x and y axis.
      strips[strip][i] = ColorFromPalette(currentPalette, index, 255, LINEARBLEND);    // With that value, look up the 8 bit colour palette value and assign it to the current LED.
  }
  FastLED.show();
}

void stripes(int strip, int velocity)
{
  uint8_t beat = beatsin8( bpm, 0, 255);
  uint8_t palette = map(velocity, 1, 127, 0, paletteSize);
  for( uint8_t i = 0; i < num_leds; i++) {
    strips[strip][i] = ColorFromPalette(palettes[palette], i*2, beat+(i*10));
  }
  FastLED.show();
}

void juggle(int strip, int velocity) 
 {
  // eight colored dots, weaving in and out of sync with each other
  fadeToBlackBy( strips[strip], num_leds, 20);
  uint8_t palette = map(velocity, 1, 127, 0, paletteSize);
  uint8_t dothue = 0;
  for( uint8_t i = 0; i < 8; i++)
  {
    strips[strip][beatsin16( i+7, 0, num_leds-1 )] |= ColorFromPalette(palettes[palette], dothue, 250);
    dothue += 26;
  }  
  FastLED.show();
 }

void scrollPaletteLeft(int strip, int velocity)
{
    uint8_t palette = map(velocity, 1, 127, 0, paletteSize);
    currentPalette = palettes[palette];
    EVERY_N_MILLISECONDS(10)
    {
        static float startIndex = 0;
        startIndex = startIndex + 1; /* motion speed */
        float colorIndex = startIndex;
        uint8_t brightness = 255;

        for( int i = 0; i < num_leds; i++) 
        {
            strips[strip][i] = ColorFromPalette( currentPalette, colorIndex, brightness, LINEARBLEND);
            colorIndex += 3;
        }
    }
    FastLED.show();
}

void scrollPaletteRight(int strip, int velocity)
{
    uint8_t palette = map(velocity, 1, 127, 0, paletteSize);
    currentPalette = palettes[palette];
    EVERY_N_MILLISECONDS(10)
    {
        static float startIndex = 0;
        startIndex = startIndex + 1; /* motion speed */
        float colorIndex = startIndex;
        uint8_t brightness = 255;

        for( int i = num_leds; i > 0; i--) 
        {
            strips[strip][i] = ColorFromPalette( currentPalette, colorIndex, brightness, LINEARBLEND);
            colorIndex += 3;
        }
    }
    FastLED.show();
}

void scrollPaletteUp(int strip, int velocity) 
{
    int palette = map(velocity, 1, 127, 0, paletteSize);
    currentPalette = palettes[palette];
    EVERY_N_MILLISECONDS(10)
    {
        static float startIndex = 0;
        startIndex = startIndex + 1; /* motion speed */
        uint8_t colorIndex = startIndex;
        uint8_t colorIndex2 = startIndex;
        uint8_t brightness = 255;

        for(int i = 19; i < 96; i++) 
//        for(int i = 8; i < 96; i++) 
        {
            strips[strip][i] = ColorFromPalette( currentPalette, colorIndex, brightness, LINEARBLEND);
            colorIndex += 3;
        }
                
        for(int i = 8; i <17; i++)
        {
            strips[strip][i] = ColorFromPalette( currentPalette, colorIndex, brightness, LINEARBLEND);
            colorIndex += 3;
        }
        for(int i = 169; i > 95; i--) 
        {
            strips[strip][i] = ColorFromPalette( currentPalette, colorIndex2, brightness, LINEARBLEND);
            colorIndex2 += 3;
        }
        for(int i = 9; i > 0; i--)
        {
            strips[strip][i] = ColorFromPalette( currentPalette, colorIndex2, brightness, LINEARBLEND);
            colorIndex2 += 3;
        }

    }
    FastLED.show();
}

void openyourmind(int strip, int velocity)
{
  int palette = map(velocity, 1, 127, 0, paletteSize);
  currentPalette = palettes[palette];
  EVERY_N_MILLISECONDS(10)
  {
    static float startIndex = 0;
    startIndex = startIndex + 1; /* motion speed */
    uint8_t colorIndex = startIndex;
    uint8_t colorIndex2 = startIndex;
    uint8_t brightness = 255;
   //left
    for(int i = 8; i > -1; i--)
    {
        strips[strip][i] = ColorFromPalette( currentPalette, colorIndex2, brightness, LINEARBLEND);
        colorIndex2 += 3;
    }
    for(int i = 169; i > 135; i--) 
    {
        strips[strip][i] = ColorFromPalette( currentPalette, colorIndex2, brightness, LINEARBLEND);
        colorIndex2 += 3;
    }
    for(int i = 94; i < 136; i++) 
    {
        strips[strip][i] = ColorFromPalette( currentPalette, colorIndex2, brightness, LINEARBLEND);
        colorIndex2 += 3;
    }
       
    //right
    for(int i = 9; i <18; i++)
    {
        strips[strip][i] = ColorFromPalette( currentPalette, colorIndex, brightness, LINEARBLEND);
        colorIndex += 3;
    }
    for(int i = 18; i < 51; i++) 
    {
        strips[strip][i] = ColorFromPalette( currentPalette, colorIndex, brightness, LINEARBLEND);
        colorIndex += 3;
    }
    for(int i = 93; i > 51; i--) 
    {
        strips[strip][i] = ColorFromPalette( currentPalette, colorIndex, brightness, LINEARBLEND);
        colorIndex += 3;
    }

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
  fadeStrips();
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
  uint8_t left = beatsin8(bpm, 19, 84, 0, 0);
  uint8_t right = map(left, 19, 84, 169, 103);
  CRGB color = ColorFromPalette(rainbowPalette, map(velocity, 0, 127, 0, 255), 250, NOBLEND);
  for (auto strip : strips)
  {
    strip[left] = color;
    strip[right] = color;
  }
  FastLED.show();
  fadeStrips();
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
  fadeStrips();
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

  for( int i = 0; i < 8; i++)
  {
    uint8_t beat = beatsin16( i+7, 0, num_leds-1 );
    strips[0][beat] |= ColorFromPalette(palettes[palette], dothue, 250);
    strips[1][beat] |= ColorFromPalette(palettes[palette], dothue, 250);
    strips[2][beat] |= ColorFromPalette(palettes[palette], dothue, 250);
    strips[3][beat] |= ColorFromPalette(palettes[palette], dothue, 250);
    dothue += 26;
  }
  
  FastLED.show();
 }

void scrollPaletteLeftGlobal(int velocity)
{
    int palette = map(velocity, 1, 127, 0, paletteSize);
    currentPalette = palettes[palette];
    EVERY_N_MILLISECONDS(10)
    {
        static float startIndex = 0;
        startIndex = startIndex + 1; /* motion speed */
        float colorIndex = startIndex;
        uint8_t brightness = 255;

        for( int i = 0; i < num_leds; i++) 
        {
            strips[0][i] = ColorFromPalette( currentPalette, colorIndex, brightness, LINEARBLEND);
            strips[1][i] = ColorFromPalette( currentPalette, colorIndex, brightness, LINEARBLEND);
            strips[2][i] = ColorFromPalette( currentPalette, colorIndex, brightness, LINEARBLEND);
            strips[3][i] = ColorFromPalette( currentPalette, colorIndex, brightness, LINEARBLEND);
            colorIndex += 3;
        }
    }
    FastLED.show();
}

void scrollPaletteRightGlobal(int velocity)
{
    uint8_t palette = map(velocity, 1, 127, 0, paletteSize);
    currentPalette = palettes[palette];
    EVERY_N_MILLISECONDS(10)
    {
        static float startIndex = 0;
        startIndex = startIndex + 1; /* motion speed */
        float colorIndex = startIndex;
        uint8_t brightness = 255;

        for( int i = num_leds; i > 0; i--) 
        {
            strips[0][i] = ColorFromPalette( currentPalette, colorIndex, brightness, LINEARBLEND);
            strips[1][i] = ColorFromPalette( currentPalette, colorIndex, brightness, LINEARBLEND);
            strips[2][i] = ColorFromPalette( currentPalette, colorIndex, brightness, LINEARBLEND);
            strips[3][i] = ColorFromPalette( currentPalette, colorIndex, brightness, LINEARBLEND);
            colorIndex += 3;
        }
    }
    FastLED.show();
}

void scrollPaletteUpGlobal(int velocity) 
{
    int palette = map(velocity, 1, 127, 0, paletteSize);
    currentPalette = palettes[palette];
    EVERY_N_MILLISECONDS(10)
    {
        static float startIndex = 0;
        startIndex = startIndex + 1; /* motion speed */
        uint8_t colorIndex = startIndex;
        uint8_t colorIndex2 = startIndex;
        uint8_t brightness = 255;

        for(int i=19;i<96;i++) 
        {
            strips[0][i] = ColorFromPalette( currentPalette, colorIndex, brightness, LINEARBLEND);
            strips[1][i] = ColorFromPalette( currentPalette, colorIndex, brightness, LINEARBLEND);
            strips[2][i] = ColorFromPalette( currentPalette, colorIndex, brightness, LINEARBLEND);
            strips[3][i] = ColorFromPalette( currentPalette, colorIndex, brightness, LINEARBLEND);
            colorIndex += 3;
        }
                
        for(int i=8;i<17;i++)
        {
            strips[0][i] = ColorFromPalette( currentPalette, colorIndex, brightness, LINEARBLEND);
            strips[1][i] = ColorFromPalette( currentPalette, colorIndex, brightness, LINEARBLEND);
            strips[2][i] = ColorFromPalette( currentPalette, colorIndex, brightness, LINEARBLEND);
            strips[3][i] = ColorFromPalette( currentPalette, colorIndex, brightness, LINEARBLEND);
            colorIndex += 3;
        }
        for(int i=169;i>95;i--) 
        {
            strips[0][i] = ColorFromPalette( currentPalette, colorIndex2, brightness, LINEARBLEND);
            strips[1][i] = ColorFromPalette( currentPalette, colorIndex2, brightness, LINEARBLEND);
            strips[2][i] = ColorFromPalette( currentPalette, colorIndex2, brightness, LINEARBLEND);
            strips[3][i] = ColorFromPalette( currentPalette, colorIndex2, brightness, LINEARBLEND);
            colorIndex2 += 3;
        }
        for(int i=9;i>0;i--)
        {
            strips[0][i] = ColorFromPalette( currentPalette, colorIndex2, brightness, LINEARBLEND);
            strips[1][i] = ColorFromPalette( currentPalette, colorIndex2, brightness, LINEARBLEND);
            strips[2][i] = ColorFromPalette( currentPalette, colorIndex2, brightness, LINEARBLEND);
            strips[3][i] = ColorFromPalette( currentPalette, colorIndex2, brightness, LINEARBLEND);
            colorIndex2 += 3;
        }

    }
    FastLED.show();
}

void openyourmindGlobal(int velocity)
{
  int palette = map(velocity, 1, 127, 0, paletteSize);
  currentPalette = palettes[palette];
  EVERY_N_MILLISECONDS(10)
  {
    static float startIndex = 0;
    startIndex = startIndex + 1; /* motion speed */
    uint8_t colorIndex = startIndex;
    uint8_t colorIndex2 = startIndex;
    uint8_t brightness = 255;
   //left
    for(int i = 8; i > -1; i--)
    {
        strips[0][i] = ColorFromPalette( currentPalette, colorIndex2, brightness, LINEARBLEND);
        strips[1][i] = ColorFromPalette( currentPalette, colorIndex2, brightness, LINEARBLEND);
        strips[2][i] = ColorFromPalette( currentPalette, colorIndex2, brightness, LINEARBLEND);
        strips[3][i] = ColorFromPalette( currentPalette, colorIndex2, brightness, LINEARBLEND);
        colorIndex2 += 3;
    }
    for(int i = 169; i > 135; i--) 
    {
        strips[0][i] = ColorFromPalette( currentPalette, colorIndex2, brightness, LINEARBLEND);
        strips[1][i] = ColorFromPalette( currentPalette, colorIndex2, brightness, LINEARBLEND);
        strips[2][i] = ColorFromPalette( currentPalette, colorIndex2, brightness, LINEARBLEND);
        strips[3][i] = ColorFromPalette( currentPalette, colorIndex2, brightness, LINEARBLEND);
        colorIndex2 += 3;
    }
    for(int i = 94; i < 136; i++) 
    {
        strips[0][i] = ColorFromPalette( currentPalette, colorIndex2, brightness, LINEARBLEND);
        strips[1][i] = ColorFromPalette( currentPalette, colorIndex2, brightness, LINEARBLEND);
        strips[2][i] = ColorFromPalette( currentPalette, colorIndex2, brightness, LINEARBLEND);
        strips[3][i] = ColorFromPalette( currentPalette, colorIndex2, brightness, LINEARBLEND);
        colorIndex2 += 3;
    }
       
    //right
    for(int i = 9; i <18; i++)
    {
        strips[0][i] = ColorFromPalette( currentPalette, colorIndex, brightness, LINEARBLEND);
        strips[1][i] = ColorFromPalette( currentPalette, colorIndex, brightness, LINEARBLEND);
        strips[2][i] = ColorFromPalette( currentPalette, colorIndex, brightness, LINEARBLEND);
        strips[3][i] = ColorFromPalette( currentPalette, colorIndex, brightness, LINEARBLEND);
        colorIndex += 3;
    }
    for(int i = 18; i < 51; i++) 
    {
        strips[0][i] = ColorFromPalette( currentPalette, colorIndex, brightness, LINEARBLEND);
        strips[1][i] = ColorFromPalette( currentPalette, colorIndex, brightness, LINEARBLEND);
        strips[2][i] = ColorFromPalette( currentPalette, colorIndex, brightness, LINEARBLEND);
        strips[3][i] = ColorFromPalette( currentPalette, colorIndex, brightness, LINEARBLEND);
        colorIndex += 3;
    }
    for(int i = 93; i > 51; i--) 
    {
        strips[0][i] = ColorFromPalette( currentPalette, colorIndex, brightness, LINEARBLEND);
        strips[1][i] = ColorFromPalette( currentPalette, colorIndex, brightness, LINEARBLEND);
        strips[2][i] = ColorFromPalette( currentPalette, colorIndex, brightness, LINEARBLEND);
        strips[3][i] = ColorFromPalette( currentPalette, colorIndex, brightness, LINEARBLEND);
        colorIndex += 3;
    }

  }
  FastLED.show();
}


//******beware******
void clearStrip(int note)
{
      if (note > 60 && note < 73) { fill_solid(strips[0], num_leds, CRGB::Black); }//73-84 strip 6
 else if (note > 72 && note < 85) { fill_solid(strips[1], num_leds, CRGB::Black); }//73-84 strip 6
 else if (note > 84 && note < 97) { fill_solid(strips[2], num_leds, CRGB::Black); }//85-96 strip 7
 else if (note > 96 && note < 109){ fill_solid(strips[3], num_leds, CRGB::Black); }//96-108strip 8 
 else if (note > 108 && note < 121) { clearStrips(); }//109-120 all strips      
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

void fadeStrips()
{
  fadeToBlackBy(strips[0], num_leds, 10);
  fadeToBlackBy(strips[1], num_leds, 10);
  fadeToBlackBy(strips[2], num_leds, 10);
  fadeToBlackBy(strips[3], num_leds, 10);
  FastLED.show();
}


void routeMIDI(int note, int velocity)
{
  // strip 5: 61-72 
  if (note > 60 && note < 73)
  {
    switch (note)
    {
      case 61:
        fill_palette(strips[0], num_leds, map(velocity, 0, 127, 0, 255), 0, rainbowPalette, 250, NOBLEND);
        FastLED.show();
        break;
      
      case 62:
        breathe(0, velocity);
        break;

      case 63:
        circle(0, velocity);
        break;

      case 64:
        bounce(0, velocity);
        break;

      case 65:
        cross(0, velocity);
        break;

      case 66:
        juggle(0, velocity);
        break;
        
      case 67:
        makeNoise(0, velocity);
        break;
      
      case 68:
        stripes(0, velocity);
        break;

      case 69:
        scrollPaletteLeft(0, velocity);
        break;

      case 70:
        scrollPaletteRight(0, velocity);
        break;
      
      case 71:
        scrollPaletteUp(0, velocity);
        break;
              
      case 72:
        openyourmind(0, velocity);
        break;
    }
  }
 
  // strip 2: 73-84 
  else if (note > 72 && note < 85)
  {
    switch (note)
    {
      case 73:
        fill_palette(strips[1], num_leds, map(velocity, 0, 127, 0, 255), 0, rainbowPalette, 250, NOBLEND);
        FastLED.show();
        break;
      
      case 74:
        breathe(1, velocity);
        break;

      case 75:
        circle(1, velocity);
        break;

      case 76:
        bounce(1, velocity);
        break;

      case 77:
        cross(1, velocity);
        break;

      case 78:
        juggle(1, velocity);
        break;
        
      case 79:
        makeNoise(1, velocity);
        break;
      
      case 80:
        stripes(1, velocity);
        break;

      case 81:
        scrollPaletteLeft(1, velocity);
        break;

      case 82:
        scrollPaletteRight(1, velocity);
        break;
      
      case 83:
        scrollPaletteUp(1, velocity);
        break;
              
      case 84:
        openyourmind(1, velocity);
        break;
    }
  } 

  //  // strip 7: 85-96
  else if (note > 84 && note < 97)
  {
    switch (note)
    {
     case 85:
        fill_palette(strips[2], num_leds, map(velocity, 0, 127, 0, 255), 0, rainbowPalette, 250, NOBLEND);
        FastLED.show();
        break;
      
      case 86:
        breathe(2, velocity);
        break;

      case 87:
        circle(2, velocity);
        break;

      case 88:
        bounce(2, velocity);
        break;

      case 89:
        cross(2, velocity);
        break;

      case 90:
        juggle(2, velocity);
        break;
        
      case 91:
        makeNoise(2, velocity);
        break;
      
      case 92:
        stripes(2, velocity);
        break;

      case 93:
        scrollPaletteLeft(2, velocity);
        break;

      case 94:
        scrollPaletteRight(2, velocity);
        break;
      
      case 95:
        scrollPaletteUp(2, velocity);
        break;
              
      case 96:
        openyourmind(2, velocity);
        break;
    }
  } 

  // //strip8: 97-108
  else if (note > 96 && note < 109)
  {
    switch (note)
    {
      case 97:
        fill_palette(strips[3], num_leds, map(velocity, 0, 127, 0, 255), 0, rainbowPalette, 250, NOBLEND);
        FastLED.show();
        break;
      
      case 98:
        breathe(3, velocity);
        break;

      case 99:
        circle(3, velocity);
        break;

      case 100:
        bounce(3, velocity);
        break;

      case 101:
        cross(3, velocity);
        break;

      case 102:
        juggle(3, velocity);
        break;
        
      case 103:
        makeNoise(3, velocity);
        break;
      
      case 104:
        stripes(3, velocity);
        break;

      case 105:
        scrollPaletteLeft(3, velocity);
        break;

      case 106:
        scrollPaletteRight(3, velocity);
        break;
      
      case 107:
        scrollPaletteUp(3, velocity);
        break;
              
      case 108:
        openyourmind(3, velocity);
        break;
    }
  } 

  // Global: 109-120
  if (note > 108 && note < 121)
  {
    switch (note)
    {
      case 109:
        fillGlobal(velocity);
        break;
      
      case 110:
        breatheGlobal(velocity);
        break;

      case 111:
        circleGlobal(velocity);
        break;

      case 112:
        bounceGlobal(velocity);
        break;

      case 113:
        whiteOut(velocity);
        break;

      case 114:
        juggleGlobal(velocity);
        break;

      case 115:
        makeNoiseGlobal(velocity);
        break;
      
      case 116:
        stripesGlobal(velocity);
        break;

      case 117:
        scrollPaletteRightGlobal(velocity);
        break;

      case 118:
        scrollPaletteLeftGlobal(velocity);
        break;

      case 119:
        scrollPaletteUpGlobal(velocity);
        break;
        
      case 120:
        openyourmindGlobal(velocity);
        break;
    }
  }
}
