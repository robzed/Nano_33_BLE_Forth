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

#define _FS_LOGLEVEL_               1
#define NANO33BLE_FS_SIZE_KB        256

#define FORCE_REFORMAT              false

// Default USING_LITTLEFS. Uncomment to not USING_LITTLEFS => USING_FATFS.
//#define USING_LITTLEFS              false

#include <FS_Nano33BLE.h>

FileSystem_MBED *myFS;


#include "pforth-master/csrc/pforth.h"

void setup() {
    Serial.begin(115200);
	pinMode(LED_BUILTIN, OUTPUT);
	// allow 2 seconds for us to connect with serial terminal
    for(int i = 10; i > 0; i--) {
        digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on
    	delay(100);
        digitalWrite(LED_BUILTIN, LOW);   // turn the LED off
        delay(100);
    }

    myFS = new FileSystem_MBED();

    if (!myFS->init())
    {
      Serial.println("FS Mount Failed");

      return;
    }
    // all other setup done by Forth
}

void loop() {
    // ignore the loop in main()
    char IfInit = 0;
    const char *DicName = NULL;
    const char *SourceName = NULL;
    ThrowCode err = pfDoForth( DicName, SourceName, IfInit);

    // user probably typed BYE to get here
    Serial.print("Forth exit, code = ");
    Serial.println(err);
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


mbed::LittleFileSystem& get_FileSystem(void) {
	return fs;
}

