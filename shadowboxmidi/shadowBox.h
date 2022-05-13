#include <FastLED.h>

    class shadowBox
    {
        public:
            int BPM;
            int LED_PIN1 = 23;
            int LED_PIN2 = 22;
            int num_leds1 = 165;
            int num_leds2 = 19;
            CRGB strip1 [165];
            CRGB strip2 [19];

            void setBPM();
            void routeMIDI(byte byteNote, byte velocity);
            void circle(struct CRGB *strip, int numLeds);
            void circleBPM(struct CRGB *strip, int numLeds);
            void tapInput();
            void clearStrip(byte byteNote);
    
    };


// #define LED_PIN1 23
// #define LED_PIN2 22
// #define num_leds1 165
// #define num_leds2 14
