#include <MIDI.h>
#include <vector>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define LED_BUILTIN 2
#define BPM_PIN 4
#define MIDI_PIN 16 //rx2, receive midi
#define tx2 17 // future midi out/thru 
#define OUT_PIN 21
#define BTN_PIN 18

static uint8_t  ticks = 0; //midi ticks per quarter note
int bpm = 0;
int analogValue = 0;

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Start midi-arduino-library instance on rx2 pin
MIDI_CREATE_INSTANCE(HardwareSerial, Serial2,  MIDI);
std::vector<uint8_t> heldNotes; 

unsigned long previousMillis = 0;
const long interval = 200;  

void setup()
{
  //screen
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  display.clearDisplay();
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  
  //Pins
  pinMode(BTN_PIN, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  Serial2.begin(31250, SERIAL_8N1, MIDI_PIN, tx2);

  //MIDI
  MIDI.begin(MIDI_CHANNEL_OMNI);
  MIDI.setHandleNoteOn(handleNoteOn);
  MIDI.setHandleNoteOff(handleNoteOff);
//  MIDI.setHandleClock(handleClock);
}

void loop()
{
//  Serial.println(digitalRead(BTN_PIN));
//  digitalWrite(LED_BUILTIN, digitalRead(BTN_PIN));
  unsigned long currentMillis = millis();
  MIDI.read();
  //setBPM();  

  int read_val = 0;
  for (byte i = 0 ; i < 10 ; i++)
  {
    read_val += analogRead(4);
  }
  
  analogValue = analogValue * 0.9 + (read_val / 10) * 0.1;
  bpm = map(analogValue, 0, 4095, 0, 200);  

  //Serial2.write(bpm);
  //Serial.println(bpm);
  if (currentMillis - previousMillis >= interval)
  {
  // save the last time you blinked the LED
    previousMillis = currentMillis;

    display.clearDisplay();
    display.setCursor(5, 5);
    display.println(bpm);
    display.display(); 
  }
}

void handleNoteOn(byte channel, byte note, byte velocity)
{
  Serial.write(1);
  Serial.write(note);
  Serial.write(velocity);
  Serial.write(bpm / 2);
  
  digitalWrite(LED_BUILTIN, 1);
}

void handleNoteOff(byte channel, byte note, byte velocity)
{
  Serial.write(0);
  Serial.write(note);
  Serial.write(velocity);
  Serial.write(bpm / 2);

  digitalWrite(LED_BUILTIN, 0);
}

// void handleClock()
// {
//   ticks++;
//   if (ticks == 24)
//   {
//     tapInput();
//     ticks = 0;
//   }
// }


// // BPM related variables
// #define MINIMUM_BPM 400 // Used for debouncing
// #define MAXIMUM_BPM 3000 // Used for debouncing
// static uint8_t  ticks = 0; //midi ticks per quarter note
// long minimumTapInterval = 60L * 1000 * 1000 * 10 / MAXIMUM_BPM;
// long maximumTapInterval = 60L * 1000 * 1000 * 10 / MINIMUM_BPM;
// volatile long firstTapTime = 0;
// volatile long lastTapTime = 0;
// volatile long timesTapped = 0;
// long avgTapInterval = (lastTapTime - firstTapTime) / (timesTapped - 1);
// int BPM;

// void setBPM()
// {  
//     long now = micros();
//     if (timesTapped > 0 && timesTapped < 3 && (now - lastTapTime) > maximumTapInterval)
//     {
//         // Single taps, not enough to calculate a BPM -> ignore!
//         timesTapped = 0;
//     }
//     else if (timesTapped >= 3)
//     {
//         long avgTapInterval = (lastTapTime - firstTapTime) / (timesTapped - 1);
//         long temp = (60L * 1000 * 1000 * 10 / avgTapInterval) * 0.1f;
//         BPM = std::round(temp) / 2;
//         timesTapped = 0;
//     }
// }


// void tapInput() 
// {
//     long now = micros();
//     if (timesTapped == 0) {
//     firstTapTime = now;
//     }
//     timesTapped++;
//     lastTapTime = now;
// }
