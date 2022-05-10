#include "shadowBox.h" 
#include <FastLED.h>

using namespace std;

//attempt to setup fastled in here
// #define LED_PIN1 23
// #define LED_PIN2 22
// #define num_leds1 165
// #define num_leds2 14
int LED_PIN1 = 23;
int LED_PIN2 = 22;
int num_leds1 = 165;
int num_leds2 = 14;
CRGB strip1 [num_leds1];
CRGB strip2 [num_leds2];
// FastLED.addLeds<WS2812B, LED_PIN1, GRB>(strip1, num_leds1);
// FastLED.addLeds<WS2812B, LED_PIN2, GRB>(strip2, num_leds2);
FastLED.setBrightness(40);

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

void shadowBox::routeMIDI(Note note, byte velocity = 0)
{
    if (note == Fs8)
    {
        fill_solid(strip1, num_leds1, CRGB::Blue);
        FastLED.show();
    }
    if (note == F8)
    {
        fill_solid(strip1, num_leds1, CRGB::Red);
        FastLED.show();
    }
    if (note == E8)
    {
        fill_solid(strip1, num_leds1, CRGB::Green);
        FastLED.show();
    }
    if (note == Ds8)
    {
        circle(strip1, num_leds1);
    }
}

clearStrip()
{
    fill_solid(strip1, num_leds1, CRGB::Black);
    fill_solid(strip2, num_leds2, CRGB::Black);
}

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



