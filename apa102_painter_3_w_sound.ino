#include "FastLED.h"
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveformSine   sine4;          //xy=211,204
AudioSynthWaveformSine   sine7;          //xy=211,322
AudioSynthWaveformSine   sine3;          //xy=215,170
AudioSynthWaveformSine   sine6;          //xy=221,276
AudioSynthWaveformSine   sine2;          //xy=222,134
AudioSynthWaveformSine   sine1;          //xy=227,98
AudioSynthWaveformSine   sine5;          //xy=228,244
AudioSynthWaveformSine   sine8;          //xy=240,363
AudioMixer4              mixer2;         //xy=377,154
AudioMixer4              mixer3;         //xy=380,260
AudioMixer4              mixer1;         //xy=543,218
AudioEffectEnvelope      envelope1;      //xy=707,221
AudioEffectDelay         delay1;         //xy=842,398
AudioMixer4              mixer4;         //xy=858,273
AudioOutputAnalog        dac1;           //xy=900,93
AudioConnection          patchCord1(sine4, 0, mixer2, 3);
AudioConnection          patchCord2(sine7, 0, mixer3, 2);
AudioConnection          patchCord3(sine3, 0, mixer2, 2);
AudioConnection          patchCord4(sine6, 0, mixer3, 1);
AudioConnection          patchCord5(sine2, 0, mixer2, 1);
AudioConnection          patchCord6(sine1, 0, mixer2, 0);
AudioConnection          patchCord7(sine5, 0, mixer3, 0);
AudioConnection          patchCord8(sine8, 0, mixer3, 3);
AudioConnection          patchCord9(mixer2, 0, mixer1, 0);
AudioConnection          patchCord10(mixer3, 0, mixer1, 1);
AudioConnection          patchCord11(mixer1, envelope1);
AudioConnection          patchCord12(envelope1, 0, mixer4, 0);
AudioConnection          patchCord13(delay1, 0, mixer4, 1);
AudioConnection          patchCord14(mixer4, delay1);
AudioConnection          patchCord15(mixer4, dac1);
// GUItool: end automatically generated code


// How many leds in your strip?
#define NUM_LEDS 64
float freq[10];
float amp[10];

byte major[65] = {1, 3, 5, 6, 8, 10, 12, 13, 15, 17, 18, 20, 22, 24, 25, 27, 29, 30, 32, 34, 36, 37, 39, 41, 42, 44, 46, 48, 49, 51, 53, 54, 56, 58, 60, 61, 63, 65, 66, 68, 70, 72, 73, 75, 77, 78, 80, 82, 84, 85, 87, 89, 90, 92, 94, 96, 97, 99, 101, 102};
const float chromatic[108] = {16.3516, 17.32391673, 18.35405043, 19.44543906, 20.60172504, 21.82676736, 23.12465449, 24.499718, 25.95654704, 27.50000365, 29.13523896, 30.86771042, 32.7032, 34.64783346, 36.70810085, 38.89087812, 41.20345007, 43.65353471, 46.24930897, 48.99943599, 51.91309407, 55.00000728, 58.27047791, 61.73542083, 65.40639999, 69.29566692, 73.4162017, 77.78175623, 82.40690014, 87.30706942, 92.49861792, 97.99887197, 103.8261881, 110.0000146, 116.5409558, 123.4708417, 130.8128, 138.5913338, 146.8324034, 155.5635124, 164.8138003, 174.6141388, 184.9972358, 195.9977439, 207.6523763, 220.0000291, 233.0819116, 246.9416833, 261.6255999, 277.1826676, 293.6648067, 311.1270248, 329.6276005, 349.2282776, 369.9944716, 391.9954878, 415.3047525, 440.0000581, 466.1638231, 493.8833665, 523.2511997, 554.3653352, 587.3296134, 622.2540496, 659.2552009, 698.4565551, 739.9889431, 783.9909755, 830.6095048, 880.0001162, 932.3276461, 987.7667329, 1046.502399, 1108.73067, 1174.659227, 1244.508099, 1318.510402, 1396.91311, 1479.977886, 1567.981951, 1661.219009, 1760.000232, 1864.655292, 1975.533466, 2093.004798, 2217.46134, 2349.318453, 2489.016198, 2637.020803, 2793.82622, 2959.955772, 3135.963901, 3322.438019, 3520.000464, 3729.310584, 3951.066931, 4186.009596, 4434.92268, 4698.636906, 4978.032395, 5274.041605, 5587.652439, 5919.911543, 6271.927802, 6644.876037, 7040.000927, 7458.621167, 7902.133861};

byte noise[8] = {};
// Define the array of leds
CRGB leds[NUM_LEDS];
byte j, g, h;
byte a1, a2, a3;
float a1f;
uint32_t prevframe, prev0;
byte pb0, b0, pb1, pb2, pb3, pb4, b1, b2, b3, b4, r1, r2, r3, r4, b8;
int16_t pot1, potmode;
byte pixb, pixblatch;
byte tick;
uint16_t bank1[64][4] = {};
byte maxb = 160;
int audiostep, seqtick, seqstep, pseqtick;
float fin, fout, fadelatch;

void setup() {


  pinMode(0, INPUT_PULLUP);
  pinMode(1, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  analogReadAveraging(41);
  analogReadResolution(10);

  AudioNoInterrupts();

  FastLED.addLeds<APA102, 11, 13, RGB, DATA_RATE_MHZ(1)>(leds, NUM_LEDS);
  //FastLED.addLeds<APA102>(leds, NUM_LEDS);

  AudioMemory(70);

  sine1.amplitude(1);
  sine2.amplitude(1);
  sine3.amplitude(1);
  sine4.amplitude(1);
  sine5.amplitude(1);
  sine6.amplitude(1);
  sine7.amplitude(1);
  sine8.amplitude(1);

  mixer1.gain(.6, .6, 0, 0);

  mixer2.gain(.25, .25, .25, .25);
  mixer3.gain(.25, .25, .25, .25);
  mixer4.gain(.5, .5, 0, 0);

  delay1.delay(0, 150);


  AudioInterrupts();


}

int curx, cury;

void loop() {
  j++;
  if (j > 64) {
    g++;
  }

  if (g > 64) {
    h++;
  }

  a2++;

  a3 += 4;



  pb0 = b0;
  b0 = digitalRead(0);
  pb1 = b1;
  b1 = digitalRead(1);
  pb2 = b2;
  b2 = digitalRead(2);
  pb3 = b3;
  b3 = digitalRead(3);
  pb4 = b4;
  b4 = digitalRead(4);

  b8 = digitalRead(8);

  if (b8 == 0) {
    for (int j = 0; j < NUM_LEDS; j++) {
      bank1[j][0] = 0;
      bank1[j][1] = 0;
      bank1[j][2] = 0;
    }
  }

  if (pb1 == 1 && b1 == 0) {
    cury -= 1;
  }

  if (pb2 == 1 && b2 == 0) {
    curx -= 1;
  }
  if (pb3 == 1 && b3 == 0) {
    cury += 1;
  }
  if (pb4 == 1 && b4 == 0) {
    curx += 1;
  }

  if (curx > 7) {
    curx = 7;
  }

  if (curx < 0) {
    curx = 0;
  }

  if (cury > 7) {
    cury = 7;
  }

  if (cury < 0) {
    cury = 0;
  }


  int bpot = analogRead(A1) / 3;

  //  maxb = map(bpot, 0, 1024, 50, 255);
  maxb = 225;


  byte pixloc = curx + (cury * 8);

  pot1 = analogRead(A0) / 1.36;
  if (pot1 < 250) {
    potmode = 0;
  }
  if (pot1 > 250 && pot1 <= 500) {
    potmode = 1;
  }
  if (pot1 > 500 && pot1 <= 550) {
    potmode = 3;
  }
  if (pot1 > 550 && pot1 <= 600) {
    potmode = 4;
  }
  if (pot1 > 650 && pot1 <= 700) {
    potmode = 5;
  }
  if (pot1 > 700 ) {
    potmode = 6;
  }

  if (b0 == 0) {
    if (potmode == 0) {
      bank1[pixloc][0] = pot1;
      bank1[pixloc][1] = 225;
      bank1[pixloc][2] = 250;
      bank1[pixloc][3] = 0;

    }
    if (potmode == 1) {

      bank1[pixloc][0] = 0;
      bank1[pixloc][1] = 0;
      bank1[pixloc][2] = pot1 - 250;
      bank1[pixloc][3] = 2;

    }

    if (potmode == 3) {
      bank1[pixloc][3] = 300;
    }

    if (potmode == 4) {
      bank1[pixloc][3] = 301;
    }

    if (potmode == 5) {
      bank1[pixloc][3] = 302;
    }

    if (potmode == 6) {
      bank1[pixloc][3] = 303;
    }

  }


  if (potmode == 0) {
    leds[pixloc].setHSV( pot1, 200, pixb);

  }
  if (potmode == 1) {
    leds[pixloc].setHSV( 0, 0, ((pot1 - 255)*pixb) >> 8);

  }

  if (potmode == 3) {
    leds[pixloc].setHSV( r1, 240, pixb);

  }
  if (potmode == 4) {
    leds[pixloc].setHSV( r2, 240, pixb);

  }

  if (potmode == 5) {
    leds[pixloc].setHSV( r3, 240, pixb);

  }

  if (potmode == 6) {
    leds[pixloc].setHSV( r4, r4, ((pixb * r4) >> 8));

  }



  for (int j = 0; j < NUM_LEDS; j++) {
    //  leds[j].setRGB( a1, 10, 10);
    if (j != pixloc) {
      if (bank1[j][0] < 256) {
        leds[j].setHSV( bank1[j][0],  bank1[j][1], (bank1[j][2] * 225) >> 8);
      }
      if (bank1[j][3] == 300) {
        bank1[j][0] = r1;
        bank1[j][2] = maxb;
        leds[j].setHSV( bank1[j][0],  225, bank1[j][2]);
      }
      if (bank1[j][3] == 301) {
        bank1[j][0] = r2;
        bank1[j][2] = maxb;
        leds[j].setHSV( bank1[j][0],  225, bank1[j][2]);
      }
      if (bank1[j][3] == 302) {
        bank1[j][0] = r3;
        bank1[j][2] = maxb;
        leds[j].setHSV( bank1[j][0],  225, bank1[j][2]);
      }
      if (bank1[j][3] == 303) {
        bank1[j][0] = r4;
        bank1[j][2] = maxb;
        leds[j].setHSV( bank1[j][0],  r3 * r4, bank1[j][2]);
      }

      if (b4 == 0 && b2 == 0) {
        bank1[j][0] = random(255);
        bank1[j][1] = random(100, 225);
        bank1[j][2] = random(100, 225);
        bank1[j][3]=0;
      }

    }
  }


  if (millis() - prevframe > 42) {
    prevframe = millis();
    FastLED.show();

    tick = 1;
    //tick++;
    if (tick > 0)
    {
      tick = 0;
      r1 = random(0, 95);
      r2 = random(75, 140);
      r3 = random(160, 255);
      r4 = random( 255);
    }


  }



  // mixer1.gain(.3, .3, .2, 0);
  if (millis() - prev0 > bpot ) {
    prev0 = millis();
    // FastLED.show();
    // Serial.print(seqstep);    Serial.print(" ");    Serial.print(maxb); Serial.print(" ");    Serial.println(pixb);
    // Serial.println(pot1);

    seqtick = !seqtick;
    if (seqtick == 1) {
      seqstep ++;
      if (seqstep > 7) {
        seqstep = 0;
      }
      envelope1.noteOn();
    }

    if (seqtick == 0) {
      envelope1.noteOff();
    }

    for (int j = 0; j < 8; j++) {
      //  leds[j].setRGB( a1, 10, 10);
      int place = j + (seqstep * 8);
      int nt1 = bank1[place][0] / 32;
      byte inh = bank1[place][2];

      if (bank1[place][2] > 0) {
        inh = 1;
      }
      if (bank1[place][2] == 0) {
        inh = 0;
      }
      freq[j] = chromatic[major[(nt1 * 5) + 20]] * inh;
      amp[j]=1;
      if (freq[j] < 100) {
        freq[j] = 0;
        amp[j]=0;
      }
      if (bank1[place][3] == 2) {
        freq[j] = 0;
        amp[j]=0;
      }

      Serial.print(place);    Serial.print(" ");    Serial.print(freq[j]); Serial.print(" ");
    }

    Serial.println();

    sine1.frequency(freq[0]);
    sine2.frequency(freq[1]);
    sine3.frequency(freq[2]);
    sine4.frequency(freq[3]);
    sine5.frequency(freq[4]);
    sine6.frequency(freq[5]);
    sine7.frequency(freq[6]);
    sine8.frequency(freq[7]);

    sine1.amplitude(amp[0]);
    sine2.amplitude(amp[1]);
    sine3.amplitude(amp[2]);
    sine4.amplitude(amp[3]);
    sine5.amplitude(amp[4]);
    sine6.amplitude(amp[5]);
    sine7.amplitude(amp[6]);
    sine8.amplitude(amp[7]);

    pixblatch = !pixblatch;

    if (pixblatch == 0) {
      int mm = constrain( maxb + 25, 100, 255);
      pixb = mm;
    }
    if (pixb > maxb) {
      //pixblatch = 1;
    }

    if (pixblatch == 1) {
      pixb = 50;
    }

    if (pixb < 100) {
      //  pixblatch = 0;
    }
  }

}
