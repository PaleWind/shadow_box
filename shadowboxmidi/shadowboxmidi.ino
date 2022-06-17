#include <MIDI.h>
#include <vector>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <arduinoFFT.h>


#define SAMPLES         1024          // Must be a power of 2
#define SAMPLING_FREQ   40000         // Hz, must be 40000 or less due to ADC conversion time. Determines maximum frequency that can be analysed by the FFT Fmax=sampleF/2.
#define AMPLITUDE       1000          // Depending on your audio source level, you may need to alter this value. Can be used as a 'sensitivity' control.
#define AUDIO_IN_PIN    36            // Signal in on this pin
#define NUM_BANDS       8            // To change this, you will need to change the bunch of if statements describing the mapping from bins to bands
#define NOISE           500           // Used as a crude noise filter, values below this are ignored
#define TOP            (167 - 0) 

// Sampling and FFT stuff
unsigned int sampling_period_us;
byte peak[] = {0,0,0,0,0,0,0,0};              // The length of these arrays must be >= NUM_BANDS
int oldBarHeights[] = {0,0,0,0,0,0,0,0};
int bandValues[] = {0,0,0,0,0,0,0,0};double vReal[SAMPLES];
double vImag[SAMPLES];
unsigned long newTime;
arduinoFFT FFT = arduinoFFT(vReal, vImag, SAMPLES, SAMPLING_FREQ);

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define LED_BUILTIN 2
#define BPM_PIN 4
#define MIDI_PIN 16 //rx2, receive midi
#define tx2 17 // future midi out/thru 
#define OUT_PIN 21

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

int val =0;
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
 //pinMode(BTN_PIN, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(230400);
  Serial2.begin(31250, SERIAL_8N1, MIDI_PIN, tx2);

  //MIDI
  MIDI.begin(1);
  MIDI.setHandleNoteOn(handleNoteOn);
  MIDI.setHandleNoteOff(handleNoteOff);
//  MIDI.setHandleClock(handleClock);
  //mic
  sampling_period_us = round(1000000 * (1.0 / SAMPLING_FREQ));
}

void loop()
{
  //setBPM();
  unsigned long currentMillis = millis();    
  int read_val = 0;
  for (byte i = 0 ; i < 10 ; i++)
  {
    read_val += analogRead(4);
  }
  //bpm smoothing
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

  if (bom > 5)
  {
    MIDI.read();  
  } 
  else {
    frequencyDotRead();
  }
}


void handleNoteOn(byte channel, byte note, byte velocity)
{
  Serial.write(1);
  Serial.write(note);
  Serial.write(velocity);
  Serial.write(bpm);
  
  digitalWrite(LED_BUILTIN, 1);
}

void handleNoteOff(byte channel, byte note, byte velocity)
{
  Serial.write(0);
  Serial.write(note);
  Serial.write(velocity);
  Serial.write(bpm);

  digitalWrite(LED_BUILTIN, 0);
}


void frequencyDotRead()
{
  // Reset bandValues[]
  for (int i = 0; i<NUM_BANDS; i++){
    bandValues[i] = 0;
  }

  // Sample the audio pin
  for (int i = 0; i < SAMPLES; i++) {
    newTime = micros();
    vReal[i] = analogRead(AUDIO_IN_PIN); // A conversion takes about 9.7uS on an ESP32
    vImag[i] = 0;
    while ((micros() - newTime) < sampling_period_us) { /* chill */ }
  }

  // Compute FFT
  FFT.DCRemoval();
  FFT.Windowing(FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute(FFT_FORWARD);
  FFT.ComplexToMagnitude();

  // Analyse FFT results
  for (int i = 2; i < (SAMPLES/2); i++){       // Don't use sample 0 and only first SAMPLES/2 are usable. Each array element represents a frequency bin and its value the amplitude.
    if (vReal[i] > NOISE) {                    // Add a crude noise filter

    //8 bands, 12kHz top band
      if (i<=3 )           bandValues[0]  += (int)vReal[i];
      if (i>3   && i<=6  ) bandValues[1]  += (int)vReal[i];
      if (i>6   && i<=13 ) bandValues[2]  += (int)vReal[i];
      if (i>13  && i<=27 ) bandValues[3]  += (int)vReal[i];
      if (i>27  && i<=55 ) bandValues[4]  += (int)vReal[i];
      if (i>55  && i<=112) bandValues[5]  += (int)vReal[i];
      if (i>112 && i<=229) bandValues[6]  += (int)vReal[i];
      if (i>229          ) bandValues[7]  += (int)vReal[i];
    }
  }

  // Process the FFT data into bar heights
  for (byte band = 0; band < NUM_BANDS; band++) {

    // Scale the bars for the display
    int barHeight = bandValues[band] / AMPLITUDE;
    if (barHeight > TOP) barHeight = TOP;

    // Small amount of averaging between frames
    barHeight = ((oldBarHeights[band] * 1) + barHeight) / 2;

    // Move peak up
    if (barHeight > peak[band]) {
      peak[band] = min(TOP, barHeight);
    }

    //launch effects
    Serial.write(band);
    Serial.write(bandValues[band]);
    Serial.write(peak[band]);
    Serial.write(bpm);

    digitalWrite(LED_BUILTIN, 1);

    // Save oldBarHeights for averaging later
    oldBarHeights[band] = barHeight;
  }

  // Decay peak
  EVERY_N_MILLISECONDS(60) {
    for (byte band = 0; band < NUM_BANDS; band++)
      if (peak[band] > 0) peak[band] -= 1;
    colorTimer++;
  }
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
