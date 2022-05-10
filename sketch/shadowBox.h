#include <FastLED.h>

    enum Note: char
    {
        Fs8 = '~', 
        F8  = '}',  
        E8  = '|',  
        Ds8 = '{', 
        D8  = 'z',
        Cs8 = 'y',
        C8  = 'x',
        B7  = 'w',
        As7 = 'v',
        a7  = 'u',
        Gs7 = 't',
        G7  = 's',
        Gs3 = 'C'

    };

    class shadowBox
    {
        public:
            int BPM;
            int LED_PIN1 = 23;
            int LED_PIN2 = 22;
            int num_leds1 = 165;
            int num_leds2 = 14;
            CRGB strip1 [];
            CRGB strip2 [];

            void setBPM();
            void routeMIDI(struct CRGB *strip, int numLeds, Note note, byte velocity);
            void circle(struct CRGB *strip, int numLeds);
            void circleBPM(struct CRGB *strip, int numLeds);
            void tapInput();

            shadowBox()
            {
                // Foo foo[3];
                CRGB strip1[num_leds1];
                CRGB strip2[num_leds2];
            }
    };


// #define LED_PIN1 23
// #define LED_PIN2 22
// #define num_leds1 165
// #define num_leds2 14