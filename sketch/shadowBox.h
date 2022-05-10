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

            void setBPM();
            void routeMIDI(struct CRGB *strip, int numLeds, Note note, byte velocity);
            void circle(struct CRGB *strip, int numLeds);
            void circleBPM(struct CRGB *strip, int numLeds);
            void tapInput();
    };