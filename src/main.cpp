/*
 Beschreibung   : LED Test mit 12 LED
                : 
 Arduino     	: UNO 
 Modul ID    	: 
 Datum       	: 26.11.2023 
 Version:       : V1.0 (Änderung des Programms)
 Schaltung in	: keine
 Hardwareinfo	: DI -> 6 (Anschluß Pin 6, Steuerung, +5V , GND)
 ToDo			: Taster zum weiterschalten der Programme, Poti für die Laufgeschwindigkeit
 Status      	: OK
 Einsatz	    : Test Board
 Vorlage        : LED_9 
 Programm		: PlatformIO
 auf Gerät		: Dell-
*/

// ****************** Biblioteken einbindenn **********************************it

#include <Arduino.h>
#include <Nano_9_LED.h>
#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
#define PIN			6
#define NUMPIXEL	24
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXEL, PIN, NEO_GRB + NEO_KHZ800);
int count = 3;		// der wievielte Punkt wird angesteuert
#define DELAYVAL 500
int Durchlauf = 5;
// put function declarations here:
void Punkt_L();
void Punkt_R();
void Band_L();
void Band_R();
void Test(int wait);
void rainbowCycle(uint8_t wait);
void theaterChaseRainbow(uint8_t wait);
void colorWipe(uint32_t color, int wait);
void pulseWhite(uint8_t wait);

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

void setup() {
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif	
	// FastLED.addLeds<NEOPIXEL, 6>(leds, NUM_LEDS); // Art der LEDs,PIN-Anschluß (Name, Anzahl der LEDs)
	pixels.begin();
	pixels.setBrightness(BRIGHTNESS);                   // Setzt die Helligkeit
	Serial.begin(9600);
}

// The loop function is called in an endless loop
void loop() { 
	pixels.clear(); 
    Test(DELAYVAL);
    Serial.println(Durchlauf);
	rainbowCycle(20); 
	theaterChaseRainbow(50);
	colorWipe(127, 50);
	pulseWhite(50);
//   Serial.println("In der Loop . . ");
	for (int z = 0; z <= 10; z++) {
		// Punkt_L();
		// Punkt_R();
	}
	for (int i = 0; i <= 10; i++) {
		// Band_L();
	    // Band_R();
	}
} // Loop

void pulseWhite(uint8_t wait) {
  for(int j=0; j<256; j++) { // Ramp up from 0 to 255
    // Fill entire pixels with white at gamma-corrected brightness level 'j':
    pixels.fill(pixels.Color(0, 0, 0, pixels.gamma8(j)));
    pixels.show();
    delay(wait);
  }

  for(int j=255; j>=0; j--) { // Ramp down from 255 to 0
    pixels.fill(pixels.Color(0, 0, 0, pixels.gamma8(j)));
    pixels.show();
    delay(wait);
  }
}

void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<pixels.numPixels(); i++) { // For each pixel in strip...
    pixels.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    pixels.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}

void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < pixels.numPixels(); i=i+3) {
        pixels.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      pixels.show();

      delay(wait);

      for (uint16_t i=0; i < pixels.numPixels(); i=i+3) {
        pixels.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< pixels.numPixels(); i++) {
      pixels.setPixelColor(i, Wheel(((i * 256 / pixels.numPixels()) + j) & 255));
    }
    pixels.show();
    delay(wait);
  }
}

void Test(int wait) {
    int firstPixelHue = 0;
	for (int a = 0; a < 20; a++) 	{
		for (int b = 0; b < count; b++) {
			pixels.clear();
			for (uint8_t c = b; c < pixels.numPixels(); c += count) 			{
				int hue = firstPixelHue + c * 65536L / pixels.numPixels();
				uint32_t color = pixels.gamma32(pixels.ColorHSV(hue));
				pixels.setPixelColor(c, color);
			}
			pixels.show();
			delay(wait);
			firstPixelHue += 65536 / 90;			
		}
	}
}


/*
void Punkt_L() {                                  // ein einzelner Punkt in Blau
	static uint8_t hue;                              // Variable für den Farbton
	
	for (int z = 0; z < NUM_LEDS; z++) {                // alle LEDS durchlaufen
		leds[z] = (hue + random16(), 255, 255);             // die entsprechende Led an
		strip.show();                         // und nun ausgeben und anzeigen
		strip.delay(Zeit);                                    // Zeit abwarten
		if (z <= NUM_LEDS) {                     // wenn die letzte LED erreicht
			for (int z = 0; z < NUM_LEDS; z++) {      // wieder alle durchlaufen
				leds[z] = CRGB::Black;             // schaltet alle LEDs auf aus
				strip.show();                 // und nun ausgeben und anzeigen
			}
		}
	}
}

void Punkt_R() {                                  // ein einzelner Punkt in Blau
	static uint8_t hue;                              // Variable für den Farbton
	for (int z = NUM_LEDS - 1; z > 0; z--) {            // alle LEDS durchlaufen
		leds[z] = CHSV(hue + random16(), 255, 255);  // die entsprechende Led an
		strip.show();                         // und nun ausgeben und anzeigen
		strip.delay(Zeit);                                    // Zeit abwarten
		if (z <= NUM_LEDS) {                     // wenn die letzte LED erreicht
			for (int z = NUM_LEDS -1; z > 0; z--) {  // wieder alle durchlaufen
				leds[z] = CRGB::Black;             // schaltet alle LEDs auf aus
				strip.show();                 // und nun ausgeben und anzeigen
			}
		}
	}
}

void Band_L() { // Schaltet nacheinander alle LEDs ein und anschliessend nacheinander alle wieder aus
	static uint8_t hue;                              // Variable für den Farbton
	for (int z = 0; z < NUM_LEDS; z++) {                // alle LEDS durchlaufen
		leds[z] = CHSV(hue + random16(), 255, 255);  // die entsprechende Led an
		strip.show();                         // und nun ausgeben und anzeigen
		strip.delay(Zeit);                                    // Zeit abwarten
	}
	for (int z = 0; z < NUM_LEDS; z++) {              // wieder alle durchlaufen
		leds[z] = CRGB::Black;            // schaltet alle LEDs nacheinander aus
		strip.show();                                 // ausgeben und anzeigen
		strip.delay(Zeit);                     // und wieder die Zeit abwarten
	}
}


void Band_R() { // Schaltet nacheinander alle LEDs ein und anschliessend nacheinander alle wieder aus andere Richtung
	static uint8_t hue;                              // Variable für den Farbton
	for (int z = NUM_LEDS - 1; z > -1; z--) {           // alle LEDS durchlaufen
		leds[z] = CHSV(hue + random16(), 255, 255);  // die entsprechende Led an
		strip.show();                         // und nun ausgeben und anzeigen
		strip.delay(Zeit);                                    // Zeit abwarten
	}
	for (int z = NUM_LEDS - 1; z > 0; z--) {          // wieder alle durchlaufen
		leds[z] = CRGB::Black;            // schaltet alle LEDs nacheinander aus
		strip.show();                                 // ausgeben und anzeigen
		strip.delay(Zeit);                     // und wieder die Zeit abwarten
	}
}

*/