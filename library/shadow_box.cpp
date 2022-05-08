#include <FastLED.h>
#include <MIDI.h>
#include <string>

#define LED_BUILTIN 2
#define rx2 16
#define tx2 17
#define num_leds 5
#define pin1 23
#define pin2 22

uint8_t hue = 0;
CRGB strip1 [num_leds];
CRGB strip2 [num_leds];

 MIDI_CREATE_INSTANCE(HardwareSerial, Serial2,  MIDI);
 
void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  Serial2.begin(31250, SERIAL_8N1, rx2, tx2);

  FastLED.addLeds<WS2812B, pin1, GRB>(strip1, num_leds);
  FastLED.addLeds<WS2812B, pin2, GRB>(strip2, num_leds);

  FastLED.setBrightness(40);

  MIDI.begin(MIDI_CHANNEL_OMNI);
  MIDI.setHandleNoteOn(handleNoteOn);
  MIDI.setHandleNoteOff(handleNoteOff);
}

void loop()
{
    MIDI.read();
//    fill_solid(strip1, num_leds, CRGB::Red); 
//    fill_solid(strip2, num_leds, CRGB::Red); 
//    FastLED.show();
}

void handleNoteOn(byte channel, byte note, byte velocity)
{
    digitalWrite(LED_BUILTIN, 1);
    Serial.write("ON: ");
    Serial.write("channel: "); Serial.write(channel);
    Serial.write(" note: "); Serial.write(note);
    Serial.write(" velocity: "); Serial.write(velocity);

    if (note == 'C')
    {
      fill_solid(strip1, num_leds, CRGB::Green); 
      fill_solid(strip2, num_leds, CRGB::Green); 
    }
    else if (velocity > 70)
    {
      fill_solid(strip1, num_leds, CRGB::Blue); 
    }
    else if (velocity < 71)
    {
      fill_solid(strip2, num_leds, CRGB::Blue); 
    }
    else
    {
      fill_solid(strip1, num_leds, CRGB::Red);  
      fill_solid(strip2, num_leds, CRGB::Red);  
    }
    FastLED.show();
}
void handleNoteOff(byte channel, byte note, byte velocity)
{
    digitalWrite(LED_BUILTIN, 0);
    Serial.write("Off: ");
    Serial.write("channel: "); Serial.write(channel);
    Serial.write(" note: "); Serial.write(note);
    Serial.write(" velocity: "); Serial.write(velocity);

    fill_solid(strip1, num_leds, CRGB::Black); 
    fill_solid(strip2, num_leds, CRGB::Black); 
    FastLED.show();
}
