#include <FastLED.h>

    class shadowBox
    {
        public:
            int BPM;

            void setBPM();
            void routeMIDI(struct CRGB *strip, int numLeds, byte channel, byte note, byte velocity);
            void circle(struct CRGB *strip, int numLeds);
            void circleBPM(struct CRGB *strip, int numLeds);
            void tapInput();
    };

