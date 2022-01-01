// Arduino Nano 33 BLE Forth
//
// Copyright (c) 2021 Rob Probin
// Code used from  LED_Display2, Copyright (c) 2020 Rob Probin
//
// For terms see LICENSE. Released under MIT license.
//
// Forth engine is pForth
//          http://www.softsynth.com/pforth/
//          https://en.wikipedia.org/wiki/PForth
//          https://github.com/philburk/pforth
//

#include "pforth-master/csrc/pforth.h"

void setup() {
    Serial.begin(115200);
    // all other setup done by Forth
}

void loop() {
    // ignore the loop in main()
    char IfInit = 0;
    const char *DicName = NULL;
    const char *SourceName = NULL;
    pfDoForth( DicName, SourceName, IfInit);

    // user probably typed BYE to get here
    Serial.println("Forth exit");
	pinMode(LED_BUILTIN, OUTPUT);
    for(int i = 10; i > 0; i--) {
        digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on
    	delay(500);
        digitalWrite(LED_BUILTIN, LOW);   // turn the LED off
        delay(500);
        Serial.print("Resetting in ");
        Serial.println(i);
    }

    NVIC_SystemReset();

}
