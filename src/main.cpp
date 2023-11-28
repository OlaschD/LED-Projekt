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

// put function declarations here:
void Punkt_L();
void Punkt_R();
void Band_L();
void Band_R();


void setup() {

	FastLED.addLeds<NEOPIXEL, 6>(leds, NUM_LEDS); // Art der LEDs,PIN-Anschluß (Name, Anzahl der LEDs)
	FastLED.setBrightness(BRIGHTNESS);                   // Setzt die Helligkeit
	Serial.begin(9600);
}

// The loop function is called in an endless loop
void loop() {  									//Add your repeated code here
	int z = 0;
	int i = 0;
  Serial.println("In der Loop . . ");
	for (z = 0; z <= 10; z++) {
		Punkt_L();
		Punkt_R();
	}
	for (i = 0; i <= 10; i++) {
		Band_L();
	    Band_R();
	}
} // Loop

void Punkt_L() {                                  // ein einzelner Punkt in Blau
	static uint8_t hue;                              // Variable für den Farbton
	for (int z = 0; z < NUM_LEDS; z++) {                // alle LEDS durchlaufen
		leds[z] = CHSV(hue + random16(), 255, 255);             // die entsprechende Led an
		FastLED.show();                         // und nun ausgeben und anzeigen
		FastLED.delay(Zeit);                                    // Zeit abwarten
		if (z <= NUM_LEDS) {                     // wenn die letzte LED erreicht
			for (int z = 0; z < NUM_LEDS; z++) {      // wieder alle durchlaufen
				leds[z] = CRGB::Black;             // schaltet alle LEDs auf aus
				FastLED.show();                 // und nun ausgeben und anzeigen
			}
		}
	}
}

void Punkt_R() {                                  // ein einzelner Punkt in Blau
	static uint8_t hue;                              // Variable für den Farbton
	for (int z = NUM_LEDS - 1; z > 0; z--) {            // alle LEDS durchlaufen
		leds[z] = CHSV(hue + random16(), 255, 255);  // die entsprechende Led an
		FastLED.show();                         // und nun ausgeben und anzeigen
		FastLED.delay(Zeit);                                    // Zeit abwarten
		if (z <= NUM_LEDS) {                     // wenn die letzte LED erreicht
			for (int z = NUM_LEDS -1; z > 0; z--) {  // wieder alle durchlaufen
				leds[z] = CRGB::Black;             // schaltet alle LEDs auf aus
				FastLED.show();                 // und nun ausgeben und anzeigen
			}
		}
	}
}

void Band_L() { // Schaltet nacheinander alle LEDs ein und anschliessend nacheinander alle wieder aus
	static uint8_t hue;                              // Variable für den Farbton
	for (int z = 0; z < NUM_LEDS; z++) {                // alle LEDS durchlaufen
		leds[z] = CHSV(hue + random16(), 255, 255);  // die entsprechende Led an
		FastLED.show();                         // und nun ausgeben und anzeigen
		FastLED.delay(Zeit);                                    // Zeit abwarten
	}
	for (int z = 0; z < NUM_LEDS; z++) {              // wieder alle durchlaufen
		leds[z] = CRGB::Black;            // schaltet alle LEDs nacheinander aus
		FastLED.show();                                 // ausgeben und anzeigen
		FastLED.delay(Zeit);                     // und wieder die Zeit abwarten
	}
}


void Band_R() { // Schaltet nacheinander alle LEDs ein und anschliessend nacheinander alle wieder aus andere Richtung
	static uint8_t hue;                              // Variable für den Farbton
	for (int z = NUM_LEDS - 1; z > -1; z--) {           // alle LEDS durchlaufen
		leds[z] = CHSV(hue + random16(), 255, 255);  // die entsprechende Led an
		FastLED.show();                         // und nun ausgeben und anzeigen
		FastLED.delay(Zeit);                                    // Zeit abwarten
	}
	for (int z = NUM_LEDS - 1; z > 0; z--) {          // wieder alle durchlaufen
		leds[z] = CRGB::Black;            // schaltet alle LEDs nacheinander aus
		FastLED.show();                                 // ausgeben und anzeigen
		FastLED.delay(Zeit);                     // und wieder die Zeit abwarten
	}
}

