#include "shadowBox.h" 
#include <FastLED.h>

using namespace std;

#define num_leds1 165
#define num_leds2 19
CRGB strip1 [num_leds1];
CRGB strip2 [num_leds2];


// BPM related variables
#define MINIMUM_BPM 400 // Used for debouncing
#define MAXIMUM_BPM 3000 // Used for debouncing
static uint8_t  ticks = 0; //midi ticks per quarter note
long minimumTapInterval = 60L * 1000 * 1000 * 10 / MAXIMUM_BPM;
long maximumTapInterval = 60L * 1000 * 1000 * 10 / MINIMUM_BPM;
volatile long firstTapTime = 0;
volatile long lastTapTime = 0;
volatile long timesTapped = 0;
long avgTapInterval = (lastTapTime - firstTapTime) / (timesTapped - 1);
int BPM;
// std::map<std::string, FnPtr> functionMap; ?????
// functionMap[] = circle; ????

// void setFunctionMap() ?????
// {
//                PROBLY NOT
// }

void shadowBox::setBPM()
{  
    long now = micros();
    if (timesTapped > 0 && timesTapped < 3 && (now - lastTapTime) > maximumTapInterval)
    {
        // Single taps, not enough to calculate a BPM -> ignore!
        timesTapped = 0;
    }
    else if (timesTapped >= 3)
    {
        long avgTapInterval = (lastTapTime - firstTapTime) / (timesTapped - 1);
        long temp = (60L * 1000 * 1000 * 10 / avgTapInterval) * 0.1f;
        shadowBox::BPM = std::round(temp);
        timesTapped = 0;
    }
}

void shadowBox::routeMIDI(byte byteNote, byte velocity)
{
    int note = (int)byteNote;
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
        fill_solid(strip1, num_leds2, CRGB::Green);
        FastLED.show();
        break;
    
    case 4:
        fill_solid(strip1, num_leds1, CRGB::White);
        FastLED.show();
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
    default:
        break;
    }

    // else if (note == 2)
    // {
    //     fill_solid(strip1, num_leds1, CRGB::Red);
    //     FastLED.show();
    // }
    // else if (note == 3)
    // {
    //     fill_solid(strip1, num_leds1, CRGB::Green);
    //     FastLED.show();
    // }
    // else if (note == 4)
    // {
    //     fill_solid(strip1, num_leds1, CRGB::White);
    //     FastLED.show();
    // }
    // else if (note == 5)
    // {
    //     //circle(strip1, num_leds1);
    // }

    // // strip 2: 13-24
    // else if (note == 13)
    // {
    //     fill_solid(strip2, num_leds2, CRGB::Blue);
    //     FastLED.show();
    // }
    // else if (note == 14)
    // {
    //     fill_solid(strip2, num_leds2, CRGB::Red);
    //     FastLED.show();
    // }
    // else if (note == 15)
    // {
    //     fill_solid(strip2, num_leds2, CRGB::Green);
    //     FastLED.show();
    // }
    // else if (note == 16)
    // {
    //     fill_solid(strip2, num_leds2, CRGB::White);
    //     FastLED.show();
    // }
    // else if (note == 17)
    // {
    //     //circle(strip2, num_leds2);
    // }
}

void shadowBox::clearStrip(byte byteNote)
{
    int note = (int)byteNote;
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

// void blackOut()
// {
//     for(auto strip : allStrips)
//     {
//         fill_solid(strip, num_leds1, CRGB::Black);
//     }
// }


void shadowBox::circle(struct CRGB *strip, int numLeds)
{
    //int bpm = BPM > 0 ? BPM / 2 : 30;
    uint8_t sawBeat = beat8(BPM > 0 ? BPM / 2 : 30);
    //map sinBeat to # of leds
    int wave = map(sawBeat, 0, 255, 0, numLeds - 1);
    //Serial.println(wave);
    strip[wave] = CRGB::White;
    //pauls a genius
    FastLED.show();
    fadeToBlackBy(strip, numLeds, 20);
}

void shadowBox::circleBPM(struct CRGB *strip, int numLeds)
{
    uint8_t sawBeat = beat8(BPM);
    //map sinBeat to # of leds
    int wave = map(sawBeat, 0, 255, 0, numLeds - 1);
    //Serial.println(wave);
    strip[wave] = CRGB::White;
    
    //FastLED.show();
    fadeToBlackBy(strip, numLeds, 200);
}

void shadowBox::tapInput() 
{
    long now = micros();
    if (timesTapped == 0) {
    firstTapTime = now;
    }
    timesTapped++;
    lastTapTime = now;
}
