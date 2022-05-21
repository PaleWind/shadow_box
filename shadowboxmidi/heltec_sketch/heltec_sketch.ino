//#include <FastLED.h>
#include <MIDI.h>
#include <string>
#include <math.h>
#include <heltec.h>
//#include <shadow_box.h>

#define LED_BUILTIN 2
#define rx2 16
#define tx2 17
#define num_leds1 60
#define num_leds2 144
#define pin1 22
#define pin2 23

uint8_t hue = 0;
static uint8_t  ticks = 0;

//CRGB strip1 [num_leds1];
//CRGB strip2 [num_leds2];
HardwareSerial Pzemserial(2);
MIDI_CREATE_INSTANCE(HardwareSerial, Pzemserial,  MIDI);

//MIDI_CREATE_INSTANCE(HardwareSerial, Serial2,  MIDI);

int bpm = 140;
#define MINIMUM_BPM 400 // Used for debouncing
#define MAXIMUM_BPM 3000 // Used for debouncing
long minimumTapInterval = 60L * 1000 * 1000 * 10 / MAXIMUM_BPM;
long maximumTapInterval = 60L * 1000 * 1000 * 10 / MINIMUM_BPM;

volatile long firstTapTime = 0;
volatile long lastTapTime = 0;
volatile long timesTapped = 0;
long avgTapInterval = (lastTapTime - firstTapTime) / (timesTapped - 1);

//shadowBox sb;

void setup()
{
//Pins  
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
//  Serial2.begin(31250, SERIAL_8N1, rx2, tx2);
  
  //Pzemserial.begin(31250, SERIAL_8N1, rx2, tx2);

//MIDI
//  MIDI.begin(MIDI_CHANNEL_OMNI);
//  MIDI.setHandleNoteOn(handleNoteOn);
//  MIDI.setHandleNoteOff(handleNoteOff);
//  MIDI.setHandleClock(handleClock);

//OLED
  Heltec.begin(true /*DisplayEnable Enable*/, false /*LoRa Disable*/, true /*Serial Enable*/);
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
  Heltec.display->setFont(ArialMT_Plain_24);
}

void loop()
{
  //MIDI.read();
//
//  long now = micros();
//  if (timesTapped > 0 && timesTapped < 3 && (now - lastTapTime) > maximumTapInterval)
//  {
//    // Single taps, not enough to calculate a BPM -> ignore!
//    //    Serial.println("Ignoring lone taps!");
//    timesTapped = 0;
//  }
//  else if (timesTapped >= 3)
//  {
//    long avgTapInterval = (lastTapTime - firstTapTime) / (timesTapped - 1);
//    long temp = (60L * 1000 * 1000 * 10 / avgTapInterval) * 0.1f;
//    bpm = std::round(temp);
//    timesTapped = 0;
//  }
//  uint8_t sinBeat = beatsin8(140, 0, 140 , 0, 0);

  
  EVERY_N_MILLISECONDS(10)
  {
      digitalWrite(LED_BUILTIN, 1);
    //Serial.println(sinBeat); 
    Heltec.display->clear();
    Heltec.display->drawString(0, 0, "BPM: " + String(bpm));
    Heltec.display->display();
  
  }
  EVERY_N_MILLISECONDS(1000){Serial.println(bpm);}
  FastLED.show();  
}

void handleClock()
{
  ticks++;
  if (ticks == 24)
  {
    tapInput();
    ticks = 0;
  }
}

void tapInput() {
  long now = micros();
  if (timesTapped == 0) {
    firstTapTime = now;
  }
  timesTapped++;
  lastTapTime = now;
}


void handleNoteOn(byte channel, byte note, byte velocity)
{
  digitalWrite(LED_BUILTIN, 1);
  Serial.write(1);
  Serial.write(note);
  Serial.write(velocity);
}
void handleNoteOff(byte channel, byte note, byte velocity)
{
  digitalWrite(LED_BUILTIN, 0);
  Serial.write(0);
  Serial.write(note);
  Serial.write(velocity);
}
