// Arduino Nano 33 BLE Forth
//
// Copyright (c) 2021 Rob Probin
// Code used from  LED_Display2, Copyright (c) 2020 Rob Probin
//
// For terms see LICENSE. Released under MIT license.
//

#ifdef __cplusplus
extern "C" {
#endif

int  sdTerminalOut( char c );
int  sdTerminalEcho( char c );
int  sdTerminalFlush( void );
int  sdTerminalIn( void );
int  sdQueryTerminal( void );
void sdTerminalInit( void );
void sdTerminalTerm( void );
#define sdEnableInput()     /* sdTerminalOut( PF_CHAR_XON ) */
#define sdDisableInput()    /* sdTerminalOut( PF_CHAR_XOFF ) */

#ifdef __cplusplus
}
#endif
