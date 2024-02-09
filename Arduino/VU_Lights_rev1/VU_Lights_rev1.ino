// PACKAGE / LIBRARY
#include <FastLED.h>
#include <arduinoFFT.h>

#define SAMPLES         1024          // Must be a power of 2
#define SAMPLING_FREQ   40000         // Hz, must be 40000 or less due to ADC conversion time. Determines maximum frequency that can be analysed by the FFT Fmax=sampleF/2.
#define AMPLITUDE       1000          // Depending on your audio source level, you may need to alter this value. Can be used as a 'sensitivity' control.
#define AUDIO_IN_PIN    35            // Signal in on this pin
#define LED_PIN         5             // LED strip data
#define COLOR_ORDER     GRB           // If colours look wrong, play with this
#define CHIPSET         WS2812B       // LED strip type
#define MAX_MILLIAMPS   2000          // Careful with the amount of power here if running off USB port
#define BRIGHTNESS      100           // Brightness 0 - 255, but won't exceed current specified above
#define LED_VOLTS       5             // Usually 5 or 12
#define NUM_BANDS       10            // To change this, you will need to change the bunch of if statements describing the mapping from bins to bands
#define NOISE           500           // Used as a crude noise filter, values below this are ignored

const uint8_t kMatrixWidth = 10;                          // Matrix width
const uint8_t kMatrixHeight = 12;                         // Matrix height
#define NUM_LEDS       (kMatrixWidth * kMatrixHeight)     // Total number of LEDs
#define BAR_WIDTH      (kMatrixWidth  / (NUM_BANDS - 1))  // If width >= 8 light 1 LED width per bar, >= 16 light 2 LEDs width bar etc
#define TOP            (kMatrixHeight - 0)                // Don't allow the bars to go offscreen

// Sampling and FFT stuff
unsigned int sampling_period_us;
byte peak[] = {0,0,0,0,0,0,0,0,0,0};              // The length of these arrays must be >= NUM_BANDS
int oldBarHeights[] = {0,0,0,0,0,0,0,0,0,0};
int bandValues[] = {0,0,0,0,0,0,0,0,0,0};
double vReal[SAMPLES];
double vImag[SAMPLES];
unsigned long newTime;
arduinoFFT FFT = arduinoFFT(vReal, vImag, SAMPLES, SAMPLING_FREQ);

// FastLED stuff
CRGB leds[NUM_LEDS];
DEFINE_GRADIENT_PALETTE( purple_gp ) {
  0,   0, 212, 255,   //blue
255, 179,   0, 255 }; //purple
DEFINE_GRADIENT_PALETTE( outrun_gp ) {
  0, 141,   0, 100,   //purple
127, 255, 192,   0,   //yellow
255,   0,   5, 255 };  //blue
DEFINE_GRADIENT_PALETTE( greenblue_gp ) {
  0,   0, 255,  60,   //green
 64,   0, 236, 255,   //cyan
128,   0,   5, 255,   //blue
192,   0, 236, 255,   //cyan
255,   0, 255,  60 }; //green
DEFINE_GRADIENT_PALETTE( redyellow_gp ) {
  0,   200, 200,  200,   //white
 64,   255, 218,    0,   //yellow
128,   231,   0,    0,   //red
192,   255, 218,    0,   //yellow
255,   200, 200,  200 }; //white
CRGBPalette16 purplePal = purple_gp;
CRGBPalette16 outrunPal = outrun_gp;
CRGBPalette16 greenbluePal = greenblue_gp;
CRGBPalette16 heatPal = redyellow_gp;
uint8_t colorTimer = 0;

// XY code for serpentine matrix with input in top left
uint16_t XY(uint8_t x, uint8_t y) {
  uint16_t i;

  y = kMatrixHeight - 1 - y;  // Adjust y coordinate so (0,0) is bottom left

  i = (y * kMatrixHeight) + x;

  return i;
}

void setup() {
  Serial.begin(115200);
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalSMD5050);
  FastLED.setMaxPowerInVoltsAndMilliamps(LED_VOLTS, MAX_MILLIAMPS);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.clear();

  sampling_period_us = round(1000000 * (1.0 / SAMPLING_FREQ));
}

void loop() {
  
  // Reset bandValues[]
  for (int i = 0; i<NUM_BANDS; i++){
    bandValues[i] = 0;
  }
  
  // Sampling the audio pin
  for (int i = 0; i < SAMPLES; i++) {
    newTime = micros();
    vReal[i] = analogRead(AUDIO_IN_PIN);
    vImag[i] = 0;
    while (micros() < (newTime = sampling_period_us)) {/*chill*/}
  }

  // Computing FFT
  FFT.DCRemoval();
  FFT.Windowing(FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute(FFT_FORWARD);
  FFT.ComplexToMagnitude();

  // Analyzing FFT results
  for (int i = 2; i < (SAMPLES/2); i++) { // Don't use sample 0 and only first SAMPLES/2 are usable. Each array element represents a frequency bin and its value the amplitude.
    if (vReal[i] > NOISE) {   // Crude noise filter here

      // 10 bands, 16kHZ top band
      if (i<=13    )           bandValues[0]  +=  (int)vReal[i];
      if (i>13   &&  i<=18   )  bandValues[1]  +=  (int)vReal[i];
      if (i>18   &&  i<=27   )  bandValues[2]  +=  (int)vReal[i];
      if (i>27   &&  i<=39  )  bandValues[3]  +=  (int)vReal[i];
      if (i>39  &&  i<=57  )  bandValues[4]  +=  (int)vReal[i];
      if (i>57  &&  i<=83  )  bandValues[5]  +=  (int)vReal[i];
      if (i>83  &&  i<=122  )  bandValues[6]  +=  (int)vReal[i]; 
      if (i>122  &&  i<=177 )  bandValues[7]  +=  (int)vReal[i]; 
      if (i>177 &&  i<=259 )  bandValues[8]  +=  (int)vReal[i]; 
      if (i>259   )           bandValues[9]  +=  (int)vReal[i];     
    }
  }
  
//  Serial.print(" band 0: ");
//  Serial.print(bandValues[0]);
//  Serial.print(" | band 1: ");
//  Serial.print(bandValues[1]);
//  Serial.print(" | band 2: ");
//  Serial.print(bandValues[2]);
//  Serial.print(" | band 3: ");
//  Serial.print(bandValues[3]);
//  Serial.print(" | band 4: ");
//  Serial.print(bandValues[4]);
//  Serial.print(" | band 5: ");
//  Serial.print(bandValues[5]);
//  Serial.print(" | band 6: ");
//  Serial.print(bandValues[6]);
//  Serial.print(" | band 7: ");
//  Serial.print(bandValues[7]);
//  Serial.print(" | band 8: ");
//  Serial.print(bandValues[8]);
//  Serial.print(" | band 9: ");
//  Serial.print(bandValues[9]);
//  Serial.println();
//  Serial.println("-");
//     
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

  Serial.print(" band 0: ");
  Serial.print(peak[0]);
  Serial.print(" | band 1: ");
  Serial.print(peak[1]);
  Serial.print(" | band 2: ");
  Serial.print(peak[2]);
  Serial.print(" | band 3: ");
  Serial.print(peak[3]);
  Serial.print(" | band 4: ");
  Serial.print(peak[4]);
  Serial.print(" | band 5: ");
  Serial.print(peak[5]);
  Serial.print(" | band 6: ");
  Serial.print(peak[6]);
  Serial.print(" | band 7: ");
  Serial.print(peak[7]);
  Serial.print(" | band 8: ");
  Serial.print(peak[8]);
  Serial.print(" | band 9: ");
  Serial.print(peak[9]);
  Serial.println();
  Serial.println("-");
  

//  // RUN PATTERN
////  rainbowBars(band, barHeight);  
  }

  

//  FastLED.show();
  
// END 
}


// FUNCTIONS / PATTERNS

//void rainbowBars(int band, int barHeight) {
//  int xStart = BAR_WIDTH * band;
//  for (int x = xStart; x < xStart + BAR_WIDTH; x++) {
//    for (int y = TOP; y >= TOP - barHeight; y--) {
//      matrix->drawPixel(x, y, CHSV((x / BAR_WIDTH) * (255 / NUM_BANDS), 255, 255));
//    }
//  }
//}
