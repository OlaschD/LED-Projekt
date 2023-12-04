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
int count = 4;		// der wievielte Punkt wird angesteuert
#define DELAYVAL 500
int Durchlauf = 5;
// put function declarations here:

void Test(int wait);
void rainbowCycle(uint8_t wait);
void theaterChaseRainbow(uint8_t wait);
void colorWipe(uint32_t color, int wait);
void pulseWhite(uint8_t wait);
void whiteOverRainbow(int whiteSpeed, int whiteLength);
void cwipe();


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
	cwipe();
    Test(DELAYVAL);
    Serial.println(Durchlauf);
	rainbowCycle(20); 
	theaterChaseRainbow(50);
	whiteOverRainbow(75, 5);
	colorWipe(255, 50);
	// pulseWhite(50);
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

void whiteOverRainbow(int whiteSpeed, int whiteLength) {

  if(whiteLength >= pixels.numPixels()) whiteLength = pixels.numPixels() - 1;

  int      head          = whiteLength - 1;
  int      tail          = 0;
  int      loops         = 3;
  int      loopNum       = 0;
  uint32_t lastTime      = millis();
  uint32_t firstPixelHue = 0;

  for(;;) { // Repeat forever (or until a 'break' or 'return')
    for(int i=0; i<pixels.numPixels(); i++) {  // For each pixel in pixels...
      if(((i >= tail) && (i <= head)) ||      //  If between head & tail...
         ((tail > head) && ((i >= tail) || (i <= head)))) {
        pixels.setPixelColor(i, pixels.Color(0, 0, 0, 255)); // Set white
      } else {                                             // else set rainbow
        int pixelHue = firstPixelHue + (i * 65536L / pixels.numPixels());
        pixels.setPixelColor(i, pixels.gamma32(pixels.ColorHSV(pixelHue)));
      }
    }

    pixels.show(); // Update pixels with new contents
    // There's no delay here, it just runs full-tilt until the timer and
    // counter combination below runs out.

    firstPixelHue += 40; // Advance just a little along the color wheel

    if((millis() - lastTime) > whiteSpeed) { // Time to update head/tail?
      if(++head >= pixels.numPixels()) {      // Advance head, wrap around
        head = 0;
        if(++loopNum >= loops) return;
      }
      if(++tail >= pixels.numPixels()) {      // Advance tail, wrap around
        tail = 0;
      }
      lastTime = millis();                   // Save time of last movement
    }
  }
}

void cwipe() {
	for (size_t i = 0; i < count; i++)
	{
		colorWipe(pixels.Color(255,   0,   0)     , 150); // Red
    	colorWipe(pixels.Color(  0, 255,   0)     , 150); // Green
    	colorWipe(pixels.Color(  0,   0, 255)     , 150); // Blue
	}
}
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
  for(int i=0; i < pixels.numPixels(); i++) { // For each pixel in pixels...
    pixels.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    pixels.show();                          //  Update pixels to match
    delay(wait);                           //  Pause for a moment
  }
}

void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 4; q++) {
      for (uint16_t i=0; i < pixels.numPixels(); i=i+4) {
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
	for (int a = 0; a < 40; a++) 	{
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
