#include <FastLED.h>

    // enum Note: char
    // {
    //     Fs8 = '~', 
    //     F8  = '}',  
    //     E8  = '|',  
    //     Ds8 = '{', 
    //     D8  = 'z',
    //     Cs8 = 'y',
    //     C8  = 'x',
    //     B7  = 'w',
    //     As7 = 'v',
    //     a7  = 'u',
    //     Gs7 = 't',
    //     G7  = 's',
    //     Gs3 = 'C'

    // };

    //     enum NoteNum: uint8_t
    // {
    //     aFs8 = 126, 
    //     aF8  = 125,  
    //     aE8  = 124,  
    //     aDs8 = 123, 
    //     aD8  = 122,
    //     aCs8 = 121,
    //     aC8  = 120,
    //     aB7  = 119,
    //     aAs7 = 118,
    //     aa7  = 117,
    //     aGs7 = 116,
    //     aG7  = 115,
    //     aGs3 = 114

    // };

    class shadowBox
    {
        public:
            int BPM;
            int LED_PIN1 = 23;
            int LED_PIN2 = 22;
            int num_leds1 = 165;
            int num_leds2 = 14;
            CRGB strip1 [165];
            CRGB strip2 [14];

            void setBPM();
            void routeMIDI(int note, byte velocity);
            void circle(struct CRGB *strip, int numLeds);
            void circleBPM(struct CRGB *strip, int numLeds);
            void tapInput();
            void clearStrip(byte note);
    
    };


// #define LED_PIN1 23
// #define LED_PIN2 22
// #define num_leds1 165
// #define num_leds2 14