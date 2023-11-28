// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef _Nano_9_LED_H_
#define _Nano_9_LED_H_

//add your includes for the project Nano_9_LED here
#include "Arduino.h"
#include <FastLED.h>
#include <math.h>

//add your function definitions for the project Nano_9_LED here
#define NUM_LEDS 12                                      // Anzahl der LEDS im Strip
#define BRIGHTNESS 25                                    // festlegen der Helligkeit
CRGBArray<NUM_LEDS> leds;                        // Definiert das Array für die LEDS
int Anz = 3;                                      // Anzahl der Durchläufe pro Punkt
int Zeit = 150;

//Do not add code below this line
#endif /* _Nano_9_LED_H_ */
