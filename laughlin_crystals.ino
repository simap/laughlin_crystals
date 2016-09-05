
#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel strip = Adafruit_NeoPixel(12, 0, NEO_GRB + NEO_KHZ800);


const signed char sinLookup[] = {0, 3, 6, 9, 12, 16, 19, 22, 25, 28, 31, 34,
                                 37, 40, 43, 46, 49, 51, 54, 57, 60, 63, 65, 68, 71, 73, 76, 78, 81,
                                 83, 85, 88, 90, 92, 94, 96, 98, 100, 102, 104, 106, 107, 109, 111,
                                 112, 113, 115, 116, 117, 118, 120, 121, 122, 122, 123, 124, 125, 125,
                                 126, 126, 126, 127, 127, 127, 127, 127, 127, 127, 126, 126, 126, 125,
                                 125, 124, 123, 122, 122, 121, 120, 118, 117, 116, 115, 113, 112, 111,
                                 109, 107, 106, 104, 102, 100, 98, 96, 94, 92, 90, 88, 85, 83, 81, 78,
                                 76, 73, 71, 68, 65, 63, 60, 57, 54, 51, 49, 46, 43, 40, 37, 34, 31,
                                 28, 25, 22, 19, 16, 12, 9, 6, 3, 0, -3, -6, -9, -12, -16, -19, -22,
                                 -25, -28, -31, -34, -37, -40, -43, -46, -49, -51, -54, -57, -60, -63,
                                 -65, -68, -71, -73, -76, -78, -81, -83, -85, -88, -90, -92, -94, -96,
                                 -98, -100, -102, -104, -106, -107, -109, -111, -112, -113, -115, -116,
                                 -117, -118, -120, -121, -122, -122, -123, -124, -125, -125, -126,
                                 -126, -126, -127, -127, -127, -127, -127, -127, -127, -126, -126,
                                 -126, -125, -125, -124, -123, -122, -122, -121, -120, -118, -117,
                                 -116, -115, -113, -112, -111, -109, -107, -106, -104, -102, -100, -98,
                                 -96, -94, -92, -90, -88, -85, -83, -81, -78, -76, -73, -71, -68, -65,
                                 -63, -60, -57, -54, -51, -49, -46, -43, -40, -37, -34, -31, -28, -25,
                                 -22, -19, -16, -12, -9, -6, -3
                                };


byte modes[] = {0, 1, 2, 3};


void setup() {
  // put your setup code here, to run once:
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  randomSeed(analogRead(1));
}

void randomize() {
  for (int i = 0; i < 4; i++) {
    int d = random(4);
    byte t = modes[i];

    modes[i] = modes[d];
    modes[d] = t;
  }
}

void loop() {
  int c, i;

  randomize();
  for (int m = 0; m < 4; m++) {

    switch (modes[m]) {
      case 0:
        for (c = 0; c < 128; c++) {
          setStrip(strip.Color(sinLookup[c] * 2, 0, sinLookup[c] * 2));
          strip.show();
          delay(30);
        }
        break;
      case 1:
        for (c = 0; c < 128; c++) {
          setStrip(strip.Color(0, sinLookup[c] * 2, sinLookup[c] * 2));
          strip.show();
          delay(30);
        }
        break;
      case 2:

        for (c = 0; c < 255; c++) {
          byte r = ((255 - c) * sinLookup[c / 2] * 2) >> 8;
          byte g = (c * sinLookup[c / 2] * 2) >> 8;

          setStrip(strip.Color(r, g, sinLookup[c / 2] * 2));
          strip.show();
          delay(30);
        }
        break;
      case 3:

        for (c = 0; c < 255; c++) {
          byte g = ((255 - c) * sinLookup[c / 2] * 2) >> 8;
          byte r = (c * sinLookup[c / 2] * 2) >> 8;

          setStrip(strip.Color(r, g, sinLookup[c / 2] * 2));
          strip.show();
          delay(30);
        }
        break;
    }

  }

}

void setStrip(uint32_t c) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
  }
}

