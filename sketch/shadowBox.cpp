#include "shadowBox.h" 
#include <FastLED.h>

using namespace std;

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
// std::map<std::string, FnPtr> functionMap;
// functionMap[] = circle;

// void setFunctionMap()
// {

// }


void shadowBox::setBPM()
{
    long now = micros();
    if (timesTapped > 0 && timesTapped < 3 && (now - lastTapTime) > maximumTapInterval)
    {
        // Single taps, not enough to calculate a BPM -> ignore!
        //    Serial.println("Ignoring lone taps!");
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

void shadowBox::routeMIDI(struct CRGB *strip, int numLeds, Note note, byte velocity = 0)
{
    if (note == Fs8)
    {
        fill_solid(strip, numLeds, CRGB::Blue);
        FastLED.show();
    }
    if (note == F8)
    {
        fill_solid(strip, numLeds, CRGB::Red);
        FastLED.show();
    }
    if (note == E8)
    {
        fill_solid(strip, numLeds, CRGB::Green);
        FastLED.show();
    }
    // }
    // else if (velocity > 70)
    // {
    //     fill_solid(strip, numLeds, CRGB::Blue);
    // }
    // else if (velocity < 71)
    // {
    //     fill_solid(strip, numLeds, CRGB::Green);
    // }
    // else
    // {
    //     fill_solid(strip, numLeds, CRGB::Red);
     
}

void shadowBox::circle(struct CRGB *strip, int numLeds)
{
    //variable = (condition) ? expressionTrue : expressionFalse;
    int bpm = BPM > 0 ? BPM / 2 : 30;
    uint8_t sawBeat = beat8(bpm);
    //map sinBeat to # of leds
    int wave = map(sawBeat, 0, 255, 0, numLeds - 1);
    //Serial.println(wave);
    strip[wave] = CRGB::White;
    //pauls a genius
    FastLED.show();
    fadeToBlackBy(strip, numLeds, 2);
}

void shadowBox::circleBPM(struct CRGB *strip, int numLeds)
{
    uint8_t sawBeat = beat8(BPM);
    //map sinBeat to # of leds
    int wave = map(sawBeat, 0, 255, 0, numLeds - 1);
    //Serial.println(wave);
    strip[wave] = CRGB::White;
    
    //FastLED.show();
    fadeToBlackBy(strip, numLeds, 10);
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



