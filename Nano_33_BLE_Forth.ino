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
    // all done by Forth
}

void(* resetFunc) (void) = 0; //declare reset function @ address 0

void loop() {
    // ignore the loop in main()
    char IfInit = 0;
    const char *DicName = NULL;
    const char *SourceName = NULL;
    pfDoForth( DicName, SourceName, IfInit);

    // user probably typed BYE to get here

    resetFunc();  //call reset to clean up.
}
