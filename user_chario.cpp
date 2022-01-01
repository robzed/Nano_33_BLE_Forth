// Arduino Nano 33 BLE Forth
//
// Copyright (c) 2021 Rob Probin
// Code used from  LED_Display2, Copyright (c) 2020 Rob Probin
//
// For terms see LICENSE. Released under MIT license.
//

#include "user_chario.h"
#include "Arduino.h"

#ifdef __cplusplus
extern "C" {
#endif

int  sdTerminalOut( char c )
{
    Serial.write(c); // write() will return the number of bytes written, 0 or 1 in this case
                     // putchar() returns character written or EOF for failure
    return c;
}
/* We don't need to echo because getchar() echos. */
int  sdTerminalEcho( char c )
{
    return 0;
}
int  sdTerminalIn( void )
{
	while(Serial.available()==0)
	{
		// idle for a while
	    delay(20);
	}
    return Serial.read();       // character or -1 if no character available
}

int  sdQueryTerminal( void )
{
    return Serial.available()?-1:0;
}

int  sdTerminalFlush( void )
{
    Serial.flush();
    return 0;   // fflush for Linux/Windows 0 means successful completion
}

void sdTerminalInit( void )
{
    Serial.println(F("\nNano 33 BLE pForth\n"));
}

void sdTerminalTerm( void )
{
}

#ifdef __cplusplus
}
#endif
